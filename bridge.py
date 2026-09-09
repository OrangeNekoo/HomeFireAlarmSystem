#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""家庭火灾报警系统串口桥：CC2530 主节点 CSV <-> 网页 WebSocket JSON"""
import asyncio
import json
import os
import sys
import threading
import time
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer

import serial
import websockets

WS_PORT = 8081
HTTP_PORT = 8080
WEB_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "web")
clients = set()          # 当前连接的 WebSocket

def xor_cs(text: str) -> str:
    cs = 0
    for ch in text:
        cs ^= ord(ch)
    return f"{cs:02X}"

def parse_line(line: str):
    """'D,2,25,0,61,0,*5A' -> dict；校验失败/不认识返回 None"""
    if "*" not in line:
        return None
    body, cs = line.rsplit("*", 1)
    if xor_cs(body) != cs.strip().upper():
        return None
    f = body.split(",")
    try:
        if f[0] == "D":
            if len(f) == 6:      # D,2,25,0,61,0  温湿度
                return {"type": "data", "node": int(f[1]),
                        "temp": int(f[2]) + int(f[3]) / 10,
                        "hum": int(f[4]) + int(f[5]) / 10}
            if len(f) == 4:      # D,3,812,1  气体
                return {"type": "data", "node": int(f[1]),
                        "gas": int(f[2]), "do": int(f[3])}
            return None
        if f[0] == "S" and len(f) == 3:
            return {"type": "status", "node": int(f[1]), "online": f[2] == "ONLINE"}
        if f[0] == "A" and len(f) == 3:
            return {"type": "alarm", "on": f[1] == "1", "src": int(f[2])}
        if f[0] == "L" and len(f) == 4:
            return {"type": "loss", "node": int(f[1]),
                    "lost": int(f[2]), "total": int(f[3])}
        if f[0] == "T" and len(f) == 3:
            return {"type": "threshold", "temp": int(f[1]), "gas": int(f[2])}
    except (ValueError, IndexError):
        return None
    return None

def build_downlink(msg: dict):
    """网页 JSON -> 串口字节行（含校验）；不认识返回 None"""
    t = msg.get("type")
    if t == "setThreshold":
        body = f"SET,{int(msg['temp'])},{int(msg['gas'])}"
    elif t == "testAlarm":
        body = f"TEST,{1 if msg.get('on') else 0}"
    elif t == "setTime":
        now = time.localtime()
        body = (f"TIME,{now.tm_year - 2000},{now.tm_mon},{now.tm_mday},"
                f"{now.tm_hour},{now.tm_min},{now.tm_sec}")
    else:
        return None
    return (body + "*" + xor_cs(body) + "\r\n").encode("ascii")

class Bridge:
    def __init__(self, port: str):
        self.ser = serial.Serial(port, 115200, timeout=1)
        self.loop = None

    def reader_thread(self):
        """串口读线程：逐行解析 -> WS 广播（带桥端时间戳）"""
        buf = b""
        while True:
            data = self.ser.read(64)
            if not data:
                continue
            buf += data
            while b"\n" in buf:
                line, buf = buf.split(b"\n", 1)
                text = line.decode("ascii", "ignore").strip()
                if not text:
                    continue
                msg = parse_line(text)
                if msg:
                    msg["ts"] = time.time()
                    asyncio.run_coroutine_threadsafe(self.broadcast(msg), self.loop)

    async def broadcast(self, msg: dict):
        if clients:
            text = json.dumps(msg, ensure_ascii=False)
            await asyncio.gather(*(c.send(text) for c in clients),
                                 return_exceptions=True)

    async def ws_handler(self, ws):
        clients.add(ws)
        try:
            async for raw in ws:
                try:
                    msg = json.loads(raw)
                except json.JSONDecodeError:
                    continue
                try:
                    frame = build_downlink(msg)
                except (KeyError, ValueError, TypeError, AttributeError):
                    continue
                if frame:
                    self.ser.write(frame)
        finally:
            clients.discard(ws)

def main():
    port = sys.argv[1] if len(sys.argv) > 1 else None
    if not port:
        from serial.tools import list_ports
        print("用法: Python311\\python.exe bridge.py COM口")
        print("可用串口:", [p.device for p in list_ports.comports()] or "无")
        sys.exit(1)
    bridge = Bridge(port)
    loop = asyncio.new_event_loop()
    bridge.loop = loop
    threading.Thread(target=bridge.reader_thread, daemon=True).start()

    def http_worker():
        os.chdir(WEB_DIR)
        ThreadingHTTPServer(("0.0.0.0", HTTP_PORT),
                            SimpleHTTPRequestHandler).serve_forever()
    threading.Thread(target=http_worker, daemon=True).start()

    print(f"串口 {port} 已连接")
    print(f"网页  http://localhost:{HTTP_PORT}")
    print(f"WS    ws://localhost:{WS_PORT}")

    async def serve():
        async with websockets.serve(bridge.ws_handler, "0.0.0.0", WS_PORT):
            await asyncio.Future()
    loop.run_until_complete(serve())

if __name__ == "__main__":
    main()
