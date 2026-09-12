from pathlib import Path

ROOT = Path(__file__).parent


def test_master_declares_button_and_easter_command():
    source = (ROOT / "Master/main.c").read_text(encoding="gbk")
    assert "P0_1" in source
    assert "0x04" in source
    assert "easter_on" in source
    assert "csv_send_easter" in source


def test_master_has_debounced_press_edge():
    source = (ROOT / "Master/main.c").read_text(encoding="gbk")
    assert "30" in source
    assert "easter_button" in source
    assert "easter_broadcast" in source


def test_csv_serializer_contains_easter_messages():
    source = (ROOT / "Master/csv.c").read_text(encoding="gbk")
    assert "E,1" in source and "E,0" in source


def test_terminal_nodes_handle_easter_command_and_keep_sampling():
    for path, marker in [("TempNode/main.c", "DHT11_Read"), ("GasNode/main.c", "ADC_Avg6")]:
        source = (ROOT / path).read_text(encoding="gbk")
        assert "cmd == 0x04" in source
        assert "easter_on" in source
        assert "LCD_DrawBitmap64" in source
        assert "100" in source
        assert marker in source


def test_terminal_exit_restores_alarm_or_main_page():
    for path in ("TempNode/main.c", "GasNode/main.c"):
        source = (ROOT / path).read_text(encoding="gbk")
        assert "draw_alarm_page" in source and "draw_main_page" in source
