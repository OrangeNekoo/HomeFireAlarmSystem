from pathlib import Path
import re

ROOT = Path(__file__).parent


def test_generated_frames_have_expected_shape_and_order():
    source = (ROOT / "Common/easter_frames.c").read_text(encoding="ascii")
    assert "EASTER_FRAME_COUNT 30" in (ROOT / "Common/easter_frames.h").read_text(encoding="ascii")
    values = re.findall(r"0x[0-9A-Fa-f]{2}", source)
    assert len(values) == 30 * 512
    assert "frame-6" in source and "frame-5" in source


def test_web_frame_manifest_is_explicit():
    source = (ROOT / "web/main.js").read_text(encoding="utf-8")
    assert "frame-1.jpg" in source
    assert "frame-6.jpg" in source
    assert "frame-5.jpg" in source
