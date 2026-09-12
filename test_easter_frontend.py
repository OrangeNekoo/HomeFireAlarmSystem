from pathlib import Path

ROOT = Path(__file__).parent


def test_frontend_has_easter_overlay_and_audio():
    html = (ROOT / "web/index.html").read_text(encoding="utf-8")
    js = (ROOT / "web/main.js").read_text(encoding="utf-8")
    assert 'id="easter-overlay"' in html
    assert 'id="easter-audio"' in html
    assert "easterEgg" in js
    assert "setInterval" in js
    assert "audio.play()" in js
    assert "currentTime = 0" in js


def test_frontend_uses_explicit_firmware_frame_order():
    js = (ROOT / "web/main.js").read_text(encoding="utf-8")
    assert "[1, 2, 3, 4, 6, 5, 7" in js


def test_frontend_stops_and_resets_easter_media():
    js = (ROOT / "web/main.js").read_text(encoding="utf-8")
    assert "clearInterval(easterTimer)" in js
    assert "audio.pause()" in js
    assert "easter-overlay" in js
    assert "easter-enable-audio" in js
