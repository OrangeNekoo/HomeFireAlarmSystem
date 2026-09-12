from pathlib import Path

ROOT = Path(__file__).parent


def test_easter_frames_are_explicit_code_memory_data():
    source = (ROOT / "Common/easter_frames.c").read_text(encoding="ascii")
    header = (ROOT / "Common/easter_frames.h").read_text(encoding="ascii")
    assert "const unsigned char __code easter_frames" in source
    assert "extern const unsigned char __code easter_frames" in header


def test_bitmap_api_reads_code_memory_and_terminals_use_no_frame_ram_copy():
    oled_h = (ROOT / "Common/oled.h").read_text(encoding="gbk")
    oled_c = (ROOT / "Common/oled.c").read_text(encoding="gbk")
    assert "const unsigned char __code *bitmap" in oled_h
    assert "const unsigned char __code *bitmap" in oled_c
    for path in (ROOT / "Master/main.c", ROOT / "TempNode/main.c", ROOT / "GasNode/main.c"):
        source = path.read_text(encoding="gbk")
        assert "easter_bitmap" not in source
