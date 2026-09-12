/* web/main.js */
const state = {
  nodes: {
    2: { online: false, temp: null, hum: null },
    3: { online: false, gas: null, do: null },
  },
  alarm: { on: false, src: 0 },
  hist: { temp: [], hum: [], gas: [] },
  demo: false,
};

const $ = id => document.getElementById(id);
const clockEl = $("clock"), linkEl = $("link-info");

/* ---------- WebSocket ---------- */
let ws = null, wsTimer = null;
function connectWS() {
  try { ws = new WebSocket("ws://localhost:8081"); } catch (e) { enterDemo(); return; }
  ws.onopen = () => {
    clearInterval(wsTimer);
    linkEl.textContent = "已连接"; linkEl.className = "online";
    $("card-master").classList.add("online");
    if (state.demo) exitDemo();
    ws.send(JSON.stringify({ type: "setTime" }));   // 连上即对时
  };
  ws.onmessage = e => handleMsg(JSON.parse(e.data));
  ws.onclose = () => { linkEl.textContent = "未连接 · 演示模式"; linkEl.className = "offline";
    $("card-master").classList.remove("online");
    wsTimer = setTimeout(connectWS, 3000); };
}
function sendCmd(obj) {
  if (ws && ws.readyState === 1) ws.send(JSON.stringify(obj));
  else if (state.demo) applyDemoCmd(obj);           // 演示模式下本地生效
}

/* ---------- 消息处理 ---------- */
function handleMsg(m) {
  if (m.type === "data" && m.node === 2) { state.nodes[2] = { online: true, temp: m.temp, hum: m.hum };
    pushHist("temp", m.temp); pushHist("hum", m.hum); }
  if (m.type === "data" && m.node === 3) { state.nodes[3] = { online: true, gas: m.gas, do: m.do };
    pushHist("gas", m.gas); }
  if (m.type === "status" && state.nodes[m.node]) { state.nodes[m.node].online = m.online; }
  if (m.type === "alarm") state.alarm = { on: m.on, src: m.src };
  if (m.type === "threshold") { $("th-temp").value = m.temp; $("th-gas").value = m.gas; }
  render();
}

/* ---------- 演示模式 ---------- */
let demoTimer = null;
function enterDemo() { if (state.demo) return; state.demo = true; $("demo-badge").hidden = false;
  demoTimer = setInterval(demoTick, 1000); demoTick(); render(); }
function exitDemo() { state.demo = false; $("demo-badge").hidden = true;
  clearInterval(demoTimer); state.demoAlarmAt = 0; }
function demoTick() {
  const t = 25 + Math.sin(Date.now() / 9000) * 2 + Math.random() * 0.4;
  const h = 60 + Math.sin(Date.now() / 7000) * 4;
  let g = 420 + Math.sin(Date.now() / 5000) * 40;
  if (state.demoAlarmAt && Date.now() > state.demoAlarmAt) g = 900 + Math.random() * 200; // 演示报警爬升
  handleMsg({ type: "data", node: 2, temp: +t.toFixed(1), hum: +h.toFixed(1) });
  handleMsg({ type: "data", node: 3, gas: Math.round(g), do: g > 600 ? 1 : 0 });
  handleMsg({ type: "alarm", on: g > 600, src: 2 });
}
function applyDemoCmd(obj) {
  if (obj.type === "testAlarm") state.demoAlarmAt = obj.on ? Date.now() : 0;
  if (obj.type === "setThreshold") handleMsg({ type: "threshold", temp: obj.temp, gas: obj.gas });
}

/* ---------- 渲染 ---------- */
function pushHist(k, v) { const a = state.hist[k]; a.push(v); if (a.length > 60) a.shift(); }
function drawCurve(canvas, arr, color) {
  const ctx = canvas.getContext("2d"); ctx.clearRect(0, 0, canvas.width, canvas.height);
  if (arr.length < 2) return;
  const min = Math.min(...arr), max = Math.max(...arr), span = (max - min) || 1;
  ctx.strokeStyle = color; ctx.lineWidth = 1.5; ctx.beginPath();
  arr.forEach((v, i) => {
    const x = i / (arr.length - 1) * canvas.width;
    const y = canvas.height - 4 - (v - min) / span * (canvas.height - 8);
    i ? ctx.lineTo(x, y) : ctx.moveTo(x, y);
  });
  ctx.stroke();
}
function render() {
  const n2 = state.nodes[2], n3 = state.nodes[3];
  $("card-temp").classList.toggle("online", n2.online);
  $("card-temp-data").textContent = n2.online ? `${n2.temp} ℃ / ${n2.hum} %` : "-- ℃ / -- %";
  $("card-gas").classList.toggle("online", n3.online);
  $("card-gas-data").textContent = n3.online ? `ADC ${n3.gas}` : "ADC --";
  $("v-temp").textContent = n2.temp ?? "--";
  $("v-hum").textContent = n2.hum ?? "--";
  $("v-gas").textContent = n3.gas ?? "--";
  drawCurve($("c-temp"), state.hist.temp, getComputedStyle(document.body).getPropertyValue("--pyro"));
  drawCurve($("c-hum"), state.hist.hum, getComputedStyle(document.body).getPropertyValue("--hydro"));
  drawCurve($("c-gas"), state.hist.gas, getComputedStyle(document.body).getPropertyValue("--anemo"));
  $("alarm-banner").hidden = !state.alarm.on;
  $("btn-test-off").hidden = !(state.alarm.on && state.alarm.src === 3);
  document.querySelectorAll(".node-card").forEach(c => c.classList.remove("alarm"));
  if (state.alarm.on) { $("card-temp").classList.add("alarm"); $("card-gas").classList.add("alarm"); }
  onAlarmFx(state.alarm.on);          // 任务 12 实现；本任务先提供空函数
}
function onAlarmFx() {}               // 任务 12 覆盖

/* ---------- 控制台 ---------- */
$("btn-thresh").onclick = () => sendCmd({ type: "setThreshold",
  temp: +$("th-temp").value, gas: +$("th-gas").value });
$("btn-test").onclick = () => sendCmd({ type: "testAlarm", on: true });
$("btn-test-off").onclick = () => sendCmd({ type: "testAlarm", on: false });

/* ---------- 时钟 ---------- */
setInterval(() => {
  const d = new Date(), p = n => String(n).padStart(2, "0");
  clockEl.textContent = `${d.getFullYear()}-${p(d.getMonth() + 1)}-${p(d.getDate())} ${p(d.getHours())}:${p(d.getMinutes())}:${p(d.getSeconds())}`;
}, 1000);

connectWS();
setTimeout(() => { if (!ws || ws.readyState !== 1) enterDemo(); }, 2000);  // 2s 连不上进演示
