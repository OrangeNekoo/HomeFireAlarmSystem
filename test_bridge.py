# -*- coding: utf-8 -*-
"""bridge.py 纯逻辑单元测试：Python311\\python.exe -m unittest test_bridge -v"""
import unittest
from bridge import xor_cs, parse_line, build_downlink

class TestChecksum(unittest.TestCase):
    def test_known_values(self):
        self.assertEqual(xor_cs("D,2,25,0,61,0"), "5A")
        self.assertEqual(xor_cs("D,3,812,1"), "51")
        self.assertEqual(xor_cs("S,2,ONLINE"), "6E")
        self.assertEqual(xor_cs("A,1,2"), "42")
        self.assertEqual(xor_cs("L,2,3,128"), "5A")
        self.assertEqual(xor_cs("T,45,600"), "63")
        self.assertEqual(xor_cs("SET,50,700"), "70")
        self.assertEqual(xor_cs("TEST,1"), "0B")
        self.assertEqual(xor_cs("TIME,26,9,8,16,30,0"), "24")

class TestParseLine(unittest.TestCase):
    def test_data_temp(self):
        self.assertEqual(parse_line("D,2,25,0,61,0*5A"),
                         {"type": "data", "node": 2, "temp": 25.0, "hum": 61.0})
    def test_data_gas(self):
        self.assertEqual(parse_line("D,3,812,1*51"),
                         {"type": "data", "node": 3, "gas": 812, "do": 1})
    def test_status(self):
        self.assertEqual(parse_line("S,2,ONLINE*6E"),
                         {"type": "status", "node": 2, "online": True})
        self.assertEqual(parse_line("S,3,OFFLINE*21"),
                         {"type": "status", "node": 3, "online": False})
    def test_alarm(self):
        self.assertEqual(parse_line("A,1,2*42"),
                         {"type": "alarm", "on": True, "src": 2})
    def test_loss_and_threshold(self):
        self.assertEqual(parse_line("L,2,3,128*5A"),
                         {"type": "loss", "node": 2, "lost": 3, "total": 128})
        self.assertEqual(parse_line("T,45,600*63"),
                         {"type": "threshold", "temp": 45, "gas": 600})
    def test_bad_checksum_rejected(self):
        self.assertIsNone(parse_line("D,2,25,0,61,0*FF"))
        self.assertIsNone(parse_line("D,2,25,0,61,0"))
        self.assertIsNone(parse_line("GARBAGE*00"))

class TestBuildDownlink(unittest.TestCase):
    def test_set_threshold(self):
        self.assertEqual(build_downlink({"type": "setThreshold", "temp": 50, "gas": 700}),
                         b"SET,50,700*70\r\n")
    def test_test_alarm(self):
        self.assertEqual(build_downlink({"type": "testAlarm", "on": True}),
                         b"TEST,1*0B\r\n")
        self.assertEqual(build_downlink({"type": "testAlarm", "on": False}),
                         b"TEST,0*0A\r\n")
    def test_set_time(self):
        import bridge
        from unittest.mock import patch
        fake = type("Tm", (), {"tm_year": 2026, "tm_mon": 9, "tm_mday": 8,
                               "tm_hour": 16, "tm_min": 30, "tm_sec": 0})()
        with patch.object(bridge.time, "localtime", return_value=fake):
            self.assertEqual(build_downlink({"type": "setTime"}),
                             b"TIME,26,9,8,16,30,0*24\r\n")
    def test_unknown_rejected(self):
        self.assertIsNone(build_downlink({"type": "nonsense"}))
    def test_malformed_raises(self):
        # 畸形输入会抛异常（防护在 bridge.ws_handler 层捕获后 continue），
        # 此处断言 build_downlink 本身抛出，防止未来改成静默返回导致防护失效
        self.assertRaises((KeyError, ValueError, TypeError),
                          build_downlink, {"type": "setThreshold"})        # 缺 temp/gas 键
        self.assertRaises((KeyError, ValueError, TypeError),
                          build_downlink, {"type": "setThreshold",
                                           "temp": None, "gas": None})     # None
        self.assertRaises((KeyError, ValueError, TypeError),
                          build_downlink, {"type": "setThreshold",
                                           "temp": "abc", "gas": 700})     # 非数字
        self.assertIsNone(build_downlink({"type": 123}))                   # 非字符串 type 安全返回 None

if __name__ == "__main__":
    unittest.main()
