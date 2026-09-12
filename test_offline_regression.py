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
    assert "LCD_P16x16Ch(32, 2, 14)" in values_block
    assert "LCD_P16x16Ch(48, 2, 15)" in values_block


def test_master_offline_path_refreshes_display_even_when_alarm_active():
    source = (ROOT / "Master/main.c").read_text(encoding="gbk")
    offline_block = source.split("static void check_offline", 1)[1].split("void main", 1)[0]
    assert "csv_send_status(2, 0)" in offline_block
    assert "csv_send_status(3, 0)" in offline_block
    assert "if(!alarm_on) draw_values();" not in offline_block
    assert "draw_values();" in offline_block
    assert "now - n2.last_ms >= OFFLINE_TIMEOUT_MS" in offline_block
    assert "now - n3.last_ms >= OFFLINE_TIMEOUT_MS" in offline_block


def test_frontend_status_messages_are_not_overridden_by_stale_data():
    source = (ROOT / "web/main.js").read_text(encoding="utf-8")
    assert "lastDataTs" in source
    assert "OFFLINE_TIMEOUT_MS" in source
    assert "setInterval(checkNodeFreshness" in source
    assert "!node.offlineByStatus" in source
    assert "offlineByStatus = !m.online" in source
    assert 'querySelector(".node-state").textContent' in source
    assert 'n2.online ? "状态：ONLINE" : "状态：OFFLINE"' in source
    assert 'n3.online ? "状态：ONLINE" : "状态：OFFLINE"' in source
