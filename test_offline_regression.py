from pathlib import Path

ROOT = Path(__file__).parent


def test_timer_enables_t1_channel0_compare_interrupt():
    source = (ROOT / "Common/timer.c").read_text(encoding="gbk")
    assert "T1CCTL0 = 0x44" in source
    assert "T1CCTL0 |= 0x04" not in source
    assert "T1CCTL0 |= 0x40" not in source
    assert "T1CC0L = 249" in source
    assert "T1CTL = 0x0E" in source

def test_master_renders_temperature_node_offline_instead_of_cached_values():
    source = (ROOT / "Master/main.c").read_text(encoding="gbk")
    values_block = source.split("static void draw_values", 1)[1].split("static void draw_main_page", 1)[0]
    assert "if(!n2.online)" in values_block
    assert "LCD_P8x16Str(32, 2, (u8 *)\":\")" in values_block
    assert "LCD_P8x16Str(32, 4, (u8 *)\":\")" in values_block
    assert "LCD_P16x16Ch(40, 2, 14)" in values_block
    assert "LCD_P16x16Ch(56, 2, 15)" in values_block
    assert "LCD_P16x16Ch(40, 4, 14)" in values_block
    assert "LCD_P16x16Ch(56, 4, 15)" in values_block
    assert values_block.count("LCD_WrDat(0x00)") >= 2


def test_master_offline_path_refreshes_entire_screen_once():
    source = (ROOT / "Master/main.c").read_text(encoding="gbk")
    offline_block = source.split("static void check_offline", 1)[1].split("void main", 1)[0]
    assert "csv_send_status(2, 0)" in offline_block
    assert "csv_send_status(3, 0)" in offline_block
    assert "if(!alarm_on) draw_values();" not in offline_block
    assert "draw_main_page();" in offline_block
    assert "redraw" in offline_block
    assert "now - n2.last_ms >= OFFLINE_TIMEOUT_MS" in offline_block
    assert "now - n3.last_ms >= OFFLINE_TIMEOUT_MS" in offline_block


def test_frontend_tracks_master_status_from_serial_heartbeat():
    source = (ROOT / "web/main.js").read_text(encoding="utf-8")
    assert "master: { online: false }" in source
    assert "state.master.online = m.online" in source
    assert '$("card-master").querySelector(".node-state").textContent' in source
    assert "state.master.online = true" in source
    assert "state.master.online = false" in source
