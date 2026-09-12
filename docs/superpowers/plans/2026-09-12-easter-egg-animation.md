# 彩蛋动画联动实现计划

> **面向 AI 代理的工作者：** 必需子技能：使用 subagent-driven-development（推荐）或 executing-plans 逐任务实现此计划。步骤使用复选框（`- [ ]`）语法来跟踪进度。

**目标：** 为 CC2530 三节点火灾报警系统增加由主节点 P0.1 按键触发、三块 OLED 与网页同步播放并可再次停止的独立彩蛋动画。

**架构：** 主节点用去抖后的 P0.1 按下沿切换 `easter_on`，通过 RF `cmd=0x04` 广播 `[state]`，同时以 `E,0/E,1` CSV 上报桥接层；两个从节点本地使用固件内置的 30 帧 64×64 位图按 100 ms 播放。网页收到桥接的 `easterEgg` JSON 后本地播放 30 帧 128×64 JPG 和 MP3，停止时恢复当前监控/报警视图。

**技术栈：** IAR 8.10 CC2530 C（GBK 源文件）、Python 3.11 unittest、原生 HTML/CSS/JS，现有 `pyserial`/`websockets` 桥接。

**规格：** `docs/superpowers/specs/2026-09-12-easter-egg-animation-design.md`；同时遵循 `docs/superpowers/specs/2026-09-08-home-fire-alarm-design.md` 的 RF、OLED、时基和编码约束。

## 全局约束

- 三个 OLED 使用仓库实际的 4 线软件 SPI 引脚：SCL=P1.2、SDA=P1.3、RST=P1.7、DC=P0.0；不得按 STM32 示例的 I2C 接线改动现有驱动。
- 固件动画固定为 STM32 `cat[][512]` 的 30 帧 64×64 数据；保留原数组实际顺序（第 5、6 帧交换），存放在 Flash，不分配 15 KB RAM。
- 网页动画使用下载目录 `图片素材/128_64/WPS图片批量处理/` 的 30 张 128×64 JPG，按显式帧序列播放；MP3 发布到 `web/music/`，不使用 `._*.mp3`。
- 新 RF 命令为 `0x04`，广播 payload 仅 1 字节状态；不改变报警 `0x03`、数据 `0x01`、对时 `0x02`。
- P0.1 按下为低电平；主节点以 10 ms 采样、约 30 ms 稳定确认，只在释放到按下的稳定边沿切换。
- 彩蛋期间继续采集、收发、报警判决和串口上报；只暂停 OLED 正常页面刷新；退出时按最新报警状态重绘。
- Python 与网页文件使用 UTF-8；CC2530 C 文件使用仓库现有 GBK 编码；commit 信息若由用户要求提交时使用简体中文 conventional commits。
- 测试必须覆盖协议校验、RF/按键状态机源级逻辑、网页帧顺序和音乐拒播分支；IAR 编译与真实硬件现象需单独记录，不能用 Python 测试冒充。

## 文件清单与职责

- 创建：`tools/extract_easter_frames.py`，从 STM32 `main.c` 提取并校验 30×512B 数组，生成 `Common/easter_frames.c/.h`。
- 创建：`Common/easter_frames.c`、`Common/easter_frames.h`，Flash 中的 64×64 帧数据和帧数常量。
- 修改：`Common/oled.c`、`Common/oled.h`，增加清屏并居中绘制 64×64 位图的接口。
- 修改：`Master/Master.ewp`、`TempNode/TempNode.ewp`、`GasNode/GasNode.ewp`，加入 `easter_frames.c` 源文件和头文件搜索路径（若工程当前组已覆盖 Common，只需补源文件）。
- 修改：`Master/main.c`，P0.1 初始化/去抖、彩蛋状态机、RF `0x04` 广播、主节点播放和退出恢复。
- 修改：`Master/csv.c`、`Master/csv.h`，`E,0/E,1` 上报函数。
- 修改：`TempNode/main.c`、`GasNode/main.c`，接收 `0x04`、100 ms 本地播放、退出恢复。
- 修改：`bridge.py`，解析 `E` 上行 CSV 并广播 `easterEgg` JSON。
- 修改：`test_bridge.py`，增加 `E` 校验/解析测试和桥接未知格式回归测试。
- 创建：`web/easter/128_64/frame-*.jpg`，网页 30 帧静态资源。
- 创建：`web/music/落泪 - DJ小小智.mp3`，网页可访问音乐资源。
- 修改：`web/index.html`、`web/main.js`、`web/style.css`，动画覆盖层、帧预加载、状态边沿、音乐播放/停止和拒播提示。
- 修改：`README.md`，补充 P0.1 接线、彩蛋演示步骤、网页资源和硬件联调说明。

---

### 任务 1：提取动画资源并扩展 OLED 绘制接口

**文件：**
- 创建：`tools/extract_easter_frames.py`、`Common/easter_frames.c`、`Common/easter_frames.h`
- 修改：`Common/oled.c`、`Common/oled.h`
- 测试：`test_easter_resources.py`（新建，PC 端资源/源文本测试）
- 修改：三个 `.ewp` 工程源文件列表

- [ ] **步骤 1：编写失败的资源测试**

```python
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
```

- [ ] **步骤 2：运行测试确认失败**

运行：`Python311\python.exe -m pytest test_easter_resources.py -q`

预期：FAIL，因为 `Common/easter_frames.*`、测试文件和网页帧清单尚不存在。

- [ ] **步骤 3：实现提取器、帧数组和 OLED 接口**

实现 `tools/extract_easter_frames.py`：定位 STM32 `cat[][512]` 的 30 个初始化块，严格校验每块 512 个字节，按源码块顺序输出 C 数组；命令行参数接收输入 `main.c` 和输出目录，默认拒绝数量或长度不匹配。生成的头文件提供：

```c
#define EASTER_FRAME_WIDTH 64
#define EASTER_FRAME_HEIGHT 64
#define EASTER_FRAME_BYTES 512
#define EASTER_FRAME_COUNT 30
extern const unsigned char easter_frames[EASTER_FRAME_COUNT][EASTER_FRAME_BYTES];
```

在 `oled.h` 增加：

```c
void LCD_DrawBitmap64(const unsigned char *bitmap);
```

在 `oled.c` 中实现：先清空整屏，再按 8 页写入 x=32..95 的 64 列；位图输入为逐行 MSB-first，转换为 SSD1306 页格式后直接发送，函数不使用 1 KB 以上临时缓冲。实现后把新源文件加入三个 `.ewp` 的 Common 源文件组。

复制网页 128×64 JPG 到 `web/easter/128_64/`，由网页显式数组引用顺序，元素顺序为：`1,2,3,4,6,5,7,...,30`。复制 MP3 到 `web/music/`，不复制 Finder 元数据文件。

- [ ] **步骤 4：运行测试确认通过**

运行：`Python311\python.exe -m pytest test_easter_resources.py -q`

预期：资源数量为 30，固件字节数为 15360，网页清单存在且顺序显式。

运行：`python tools/extract_easter_frames.py --check "C:/Users/orangeneko/Downloads/我很臭吗？/keil/OLEDTest/user/main.c"`

预期：输出 30 frames × 512 bytes，并以成功状态退出。

- [ ] **步骤 5：检查任务变更**

运行：`git diff --check`，并确认新增资源、工程文件和测试文件均在预期路径；不在此步骤创建 Git commit，保留变更供后续统一审查。


---

### 任务 2：主节点按键、状态机与 RF/CSV 广播

**文件：**
- 修改：`Master/main.c`、`Master/csv.c`、`Master/csv.h`
- 修改：`test_bridge.py`（仅加入串口消息预期的源级回归断言）
- 测试：`test_easter_firmware_contract.py`（新建，PC 源级契约测试）

- [ ] **步骤 1：编写失败的主节点契约测试**

```python
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
```

- [ ] **步骤 2：运行测试确认失败**

运行：`Python311\python.exe -m pytest test_easter_firmware_contract.py -q`

预期：FAIL，因为正式固件尚无 P0.1、`easter_on`、`cmd=0x04` 和 `E` 上报。

- [ ] **步骤 3：实现主节点最小状态机**

在 `Master/main.c` 中新增独立状态：

```c
#define EASTER_BUTTON P0_1
static u8 easter_on = 0;
static u8 easter_frame = 0;
static u32 easter_next_ms = 0;
```

增加 `easter_button_init()`：清除 P0.1 外设选择、设为输入并打开对应上拉；增加 `easter_button_poll()`：每 10 ms 采样，30 ms 稳定后确认，只有稳定释放到按下才执行 `easter_set(!easter_on)`。`easter_set()` 更新状态、在开始时绘制第一帧并安排下一帧，在停止时调用 `draw_alarm_page()` 或 `draw_main_page()`，然后打包 `frame_pack(buf, NODE_ID, 0xFF, 0x04, &state, 1)` 发送并调用 `csv_send_easter()`。`easter_tick(now)` 在彩蛋开启且到期时绘制当前帧、循环帧号，不调用阻塞延时。

将按钮轮询放入主循环 10 ms 调度；保留现有 `handle_rf()`、`judge_alarm()`、`check_offline()` 和传感器/串口逻辑。所有正常 OLED 刷新点增加 `if(!easter_on)` 守卫；报警变量仍更新，彩蛋停止时根据最新值恢复。

在 `csv.h/c` 增加 `csv_send_easter(u8 on)`，生成 `E,1` 或 `E,0` 后复用 `csv_send_body()`。

- [ ] **步骤 4：运行测试确认通过**

运行：`Python311\python.exe -m pytest test_easter_firmware_contract.py test_bridge.py -q`

预期：所有源级契约和既有桥接测试通过。

在 IAR GUI 中分别对 `Master` 执行 Rebuild All；若找到 `IarBuild.exe`，运行：`"<IarBuild.exe>" HomeFireAlarmSystem.eww -build Master`。预期 0 error；若工具不存在，记录未执行而不伪造结果。

- [ ] **步骤 5：检查任务变更**

运行：`git diff --check`，并确认主节点源文件、CSV 头文件和契约测试均在预期路径；不在此步骤创建 Git commit，保留变更供后续统一审查。


---

### 任务 3：温湿度和气体节点接收并播放彩蛋

**文件：**
- 修改：`TempNode/main.c`、`GasNode/main.c`
- 测试：扩展 `test_easter_firmware_contract.py`
- 修改：`TempNode/TempNode.ewp`、`GasNode/GasNode.ewp`（确认包含帧资源源文件）

- [ ] **步骤 1：编写失败的从节点契约测试**

```python
from pathlib import Path

ROOT = Path(__file__).parent

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
```

- [ ] **步骤 2：运行测试确认失败**

运行：`Python311\python.exe -m pytest test_easter_firmware_contract.py -q`

预期：FAIL，因为两个从节点没有 `0x04` 处理和动画状态。

- [ ] **步骤 3：实现两个从节点的非阻塞播放**

在两个 `main.c` 中分别新增 `easter_on`、`easter_frame`、`easter_next_ms`，在 `handle_rf()` 的报警分支旁增加：仅当 `cmd == 0x04 && n == 1` 且状态变化时切换；开始时清屏并立即绘制第 0 帧，停止时按 `page_alarm` 调用报警页或主页面。增加同签名 `easter_tick(u32 now)`，以 100 ms 周期调用 `LCD_DrawBitmap64(easter_frames[easter_frame])`，帧号回到 0。

把 `easter_tick` 放入各自主循环，并给时间、数值、预热完成等 OLED 刷新点增加 `!easter_on` 条件。不要包住 `DHT11_Read`、ADC 采样、`send_report`、`handle_rf` 或 LED 报警逻辑；这保证彩蛋期间链路继续工作。对于报警广播，仍更新 `page_alarm`，但彩蛋开启时不立即改屏。

- [ ] **步骤 4：运行测试确认通过**

运行：`Python311\python.exe -m pytest test_easter_firmware_contract.py -q`

预期：从节点契约测试通过。

分别对 `TempNode`、`GasNode` 执行 IAR Rebuild All；预期各自 0 error。硬件验收记录：收到 `0x04` 后两个终端 OLED 在约 100 ms 内开始循环；停止后若报警存在显示报警页，否则显示监控页；采样和心跳继续。

- [ ] **步骤 5：检查任务变更**

运行：`git diff --check`，并确认两个从节点、两个工程文件和契约测试均在预期路径；不在此步骤创建 Git commit，保留变更供后续统一审查。


---

### 任务 4：桥接层解析彩蛋事件

**文件：**
- 修改：`bridge.py`
- 修改：`test_bridge.py`

- [ ] **步骤 1：编写失败的桥接测试**

```python
def test_parse_easter_start_and_stop():
    from bridge import parse_line, xor_cs
    for on in (0, 1):
        body = f"E,{on}"
        assert parse_line(body + "*" + xor_cs(body)) == {
            "type": "easterEgg", "on": bool(on)
        }

def test_bad_easter_payload_is_rejected():
    from bridge import parse_line, xor_cs
    body = "E,2"
    assert parse_line(body + "*" + xor_cs(body)) is None
```

- [ ] **步骤 2：运行测试确认失败**

运行：`Python311\python.exe -m pytest test_bridge.py::test_parse_easter_start_and_stop test_bridge.py::test_bad_easter_payload_is_rejected -q`

预期：FAIL，因为 `parse_line()` 尚不认识 `E`。

- [ ] **步骤 3：实现严格 E 消息解析**

在 `bridge.py:parse_line()` 的既有消息分支中增加 `f[0] == "E" and len(f) == 2`，仅接受字段为字符串 `0` 或 `1`，返回 `{"type": "easterEgg", "on": f[1] == "1"}`。不要改变 `build_downlink()`，确保网页没有伪造硬件按键的下行命令。现有校验失败、字段长度错误和非数字异常继续返回 `None`。

- [ ] **步骤 4：运行完整 Python 测试**

运行：`Python311\python.exe -m unittest test_bridge -v`

预期：原有测试与新增 E 消息测试全部 PASS。

- [ ] **步骤 5：检查任务变更**

运行：`git diff --check`，并确认 `bridge.py` 与桥接测试均在预期路径；不在此步骤创建 Git commit，保留变更供后续统一审查。


---

### 任务 5：网页动画、音乐、集成文档与验证

**文件：**
- 修改：`web/index.html`、`web/main.js`、`web/style.css`
- 修改：`README.md`
- 测试：扩展 `test_easter_resources.py`，新建 `test_easter_frontend.py`

- [ ] **步骤 1：编写失败的前端契约测试**

```python
from pathlib import Path

ROOT = Path(__file__).parent

def test_frontend_has_easter_overlay_and_audio():
    html = (ROOT / "web/index.html").read_text(encoding="utf-8")
    js = (ROOT / "web/main.js").read_text(encoding="utf-8")
    assert 'id="easter-overlay"' in html
    assert 'id="easter-audio"' in html
    assert "easterEgg" in js
    assert "requestAnimationFrame" in js or "setInterval" in js
    assert "audio.play()" in js
    assert "currentTime = 0" in js

def test_frontend_uses_explicit_firmware_frame_order():
    js = (ROOT / "web/main.js").read_text(encoding="utf-8")
    assert "[1, 2, 3, 4, 6, 5, 7" in js
```

- [ ] **步骤 2：运行测试确认失败**

运行：`Python311\python.exe -m pytest test_easter_frontend.py -q`

预期：FAIL，因为页面没有彩蛋覆盖层、音频元素和播放逻辑。

- [ ] **步骤 3：实现网页状态机和媒体控制**

在 `index.html` 增加隐藏覆盖层、固定尺寸 128×64 动画 `<img>`、音乐 `<audio id="easter-audio" loop preload="auto" src="music/落泪 - DJ小小智.mp3">` 和一次性音乐启用按钮。覆盖层使用 `position: fixed`、明确 z-index，不改变底层监控布局。

在 `main.js` 中增加：

```js
const EASTER_ORDER = [1, 2, 3, 4, 6, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15,
  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30];
let easterTimer = null, easterIndex = 0;
```

添加 `setEaster(on)`：状态未变化直接返回；开始时显示覆盖层、预加载 `EASTER_ORDER.map(n => new Image())`、每 100 ms 更新 `<img>.src`，调用 `audio.play().catch(...)`；拒播时显示按钮，按钮点击后重试并隐藏提示。停止时清理定时器、隐藏覆盖层、暂停音频、`audio.currentTime = 0`、清除提示并调用 `render()`。`handleMsg()` 对 `m.type === "easterEgg"` 调用 `setEaster(m.on)`；`render()` 不得按普通数据更新重置帧。演示模式可通过 `handleMsg({type:"easterEgg", on:true/false})` 做本地验证，但不得在每次 demo tick 重复触发。

在 `style.css` 增加覆盖层、动画图像和按钮样式，使用现有黑框/红色/黄色平面色，不引入新的渐变或大面积装饰元素。

README 增加接线表 P0.1、彩蛋启动/停止演示步骤、网页媒体资源路径、浏览器拒播提示和 IAR 三工程重编译说明。

- [ ] **步骤 4：运行静态和 Python 测试**

运行：`Python311\python.exe -m pytest test_easter_resources.py test_easter_frontend.py test_easter_firmware_contract.py test_bridge.py -q`

预期：全部 PASS。

运行：`git diff --check`

预期：无空白错误。

- [ ] **步骤 5：启动桥接并进行浏览器黑盒验证**

运行：`Python311\python.exe bridge.py COM3`（将 `COM3` 替换为实际串口；会启动 HTTP 8080 和 WebSocket 8081，不修改固件）。浏览器打开 `http://localhost:8080`，通过真实 P0.1 观察：首次按下收到 `E,1`，网页覆盖层按 30 帧顺序播放并尝试音乐；再次按下收到 `E,0`，网页停止、音乐复位、监控页恢复。若浏览器拒绝自动播放，点击提示按钮后验证音乐开始。使用浏览器测试工具或开发者控制台检查帧索引没有因数据消息重置。

若硬件未连接，使用网页演示模式仅验证覆盖层、帧顺序、开始/停止、拒播恢复和监控渲染不崩溃，并在结果中明确标记为演示验证。

- [ ] **步骤 6：三工程构建与最终状态检查**

分别对 `Master`、`TempNode`、`GasNode` 执行 IAR Rebuild All；记录每个工程的错误数、代码/数据占用和是否出现 Flash 溢出。运行：`git status --short`，确认 `music/` 原有未跟踪内容未被删除，`web/music/` 和网页帧资源已按计划加入。

- [ ] **步骤 7：检查任务变更**

运行：`git diff --check` 和 `git status --short`，确认网页、文档和测试资源均在预期路径；不在此步骤创建 Git commit，保留变更供后续统一审查。


---

## 计划自检

- 规格第 2 节资源：任务 1 提取固件帧、任务 5 复制网页帧和音乐，并保留 5/6 交换顺序。
- 规格第 3 节 RF：任务 2 广播 `0x04`，任务 3 接收并幂等处理。
- 规格第 4 节按键：任务 2 实现 P0.1 输入、10 ms 采样、30 ms 去抖和按下沿。
- 规格第 5 节 CSV/桥：任务 2 生成 `E`，任务 4 解析并广播 JSON。
- 规格第 6 节从节点：任务 3 暂停 OLED 页面但继续采集、RF、报警和上报。
- 规格第 7 节网页：任务 5 实现覆盖层、显式帧序列、音乐、拒播提示和停止清理。
- 规格第 8 节错误处理：任务 3/4/5 覆盖重复状态、错误校验、缺失媒体和播放期间数据更新。
- 规格第 9 节验收：任务 5 包含 Python、静态、浏览器、IAR 与硬件记录；不把无法执行的硬件验证标为通过。
- 已扫描计划中的占位符：没有使用“待定”“TODO”“后续实现”或“添加适当的错误处理”等空泛步骤；每个实现步骤给出具体文件、符号、断言和命令。
