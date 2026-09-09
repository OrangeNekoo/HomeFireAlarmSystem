/* web/main.js */
const state = {
  nodes: {
    2: { online: false, temp: null, hum: null },
    3: { online: false, gas: null, do: null },
  },
  alarm: { on: false, src: 0 },
  loss: {},                    // node -> {lost, total}
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
  if (m.type === "loss") state.loss[m.node] = m;
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
  const l2 = state.loss[2];
  $("loss-info").textContent = l2 ? `节点2丢包 ${l2.lost}/${l2.total}` : "丢包率 --";
  $("alarm-banner").hidden = !state.alarm.on;
  $("btn-test-off").hidden = !state.alarm.on;
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

/* ================= 3D：元素核心 ================= */
let scene, camera, renderer, coreGroup;
const particles = {};                 // name -> {points, speed, radius, base}
const P_CONF = [
  { key: "temp", name: "pyro",  color: 0xef7938, radius: 2.0, count: 400, dir: 1 },
  { key: "hum",  name: "hydro", color: 0x4cc2f1, radius: 2.6, count: 350, dir: -1 },
  { key: "gas",  name: "anemo", color: 0x74c2a8, radius: 3.2, count: 300, dir: 1 },
];
function makeParticles(conf) {
  const geo = new THREE.BufferGeometry();
  const pos = new Float32Array(conf.count * 3);
  for (let i = 0; i < conf.count; i++) {
    const a = Math.random() * Math.PI * 2;
    const r = conf.radius * (0.9 + Math.random() * 0.2);
    pos[i * 3] = Math.cos(a) * r;
    pos[i * 3 + 1] = (Math.random() - 0.5) * 0.8;
    pos[i * 3 + 2] = Math.sin(a) * r;
  }
  geo.setAttribute("position", new THREE.BufferAttribute(pos, 3));
  const mat = new THREE.PointsMaterial({
    color: conf.color, size: 0.07, transparent: true, opacity: 0.75,
    blending: THREE.AdditiveBlending, depthWrite: false,
  });
  const points = new THREE.Points(geo, mat);
  points.userData = { angle: 0, dir: conf.dir };
  return points;
}
function init3D() {
  const box = document.getElementById("stage3d");
  scene = new THREE.Scene();
  camera = new THREE.PerspectiveCamera(50, box.clientWidth / box.clientHeight, 0.1, 100);
  camera.position.set(0, 1.6, 7);
  renderer = new THREE.WebGLRenderer({ antialias: true, alpha: true });
  renderer.setSize(box.clientWidth, box.clientHeight);
  renderer.setPixelRatio(window.devicePixelRatio);
  box.appendChild(renderer.domElement);
  // 元素核心：金色线框八面体 + 深蓝内芯
  coreGroup = new THREE.Group();
  const wire = new THREE.LineSegments(
    new THREE.EdgesGeometry(new THREE.OctahedronGeometry(1.15)),
    new THREE.LineBasicMaterial({ color: 0xd3bc8e }));
  const inner = new THREE.Mesh(
    new THREE.OctahedronGeometry(0.95),
    new THREE.MeshBasicMaterial({ color: 0x1a2b4d, transparent: true, opacity: 0.9 }));
  coreGroup.add(wire, inner);
  coreGroup.position.y = 0.2;
  scene.add(coreGroup);
  P_CONF.forEach(c => { const p = makeParticles(c); particles[c.name] = p; scene.add(p); });
  // 鼠标拖拽旋转
  let drag = null;
  box.addEventListener("pointerdown", e => drag = e.clientX);
  window.addEventListener("pointermove", e => {
    if (drag === null) return;
    coreGroup.rotation.y += (e.clientX - drag) * 0.01; drag = e.clientX;
  });
  window.addEventListener("pointerup", () => drag = null);
  window.addEventListener("resize", () => {
    camera.aspect = box.clientWidth / box.clientHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(box.clientWidth, box.clientHeight);
  });
  animate();
}
function animate() {
  requestAnimationFrame(animate);
  coreGroup.rotation.y += 0.004;
  coreGroup.rotation.x = Math.sin(Date.now() / 4000) * 0.15;
  // 数据驱动粒子：温度→火速度、湿度→水亮度、气体→风速度
  const n2 = state.nodes[2], n3 = state.nodes[3];
  const tBoost = n2.temp ? (n2.temp - 20) / 30 : 0;          // 20~50℃ → 0~1
  const hAlpha = n2.hum ? 0.35 + Math.min(n2.hum, 100) / 200 : 0.35;
  const gBoost = n3.gas ? Math.min(n3.gas, 1200) / 1200 : 0;
  spin(particles.pyro, 0.006 + tBoost * 0.03);
  spin(particles.hydro, 0.005);
  spin(particles.anemo, 0.004 + gBoost * 0.04);
  particles.hydro.material.opacity = hAlpha;
  // 报警扩散：火粒子膨胀脉冲
  if (state.alarm.on) {
    const s = 1 + 0.25 * Math.sin(Date.now() / 120);
    particles.pyro.scale.set(s, s, s);
  } else particles.pyro.scale.set(1, 1, 1);
  renderer.render(scene, camera);
}
function spin(p, step) {
  const pos = p.geometry.attributes.position;
  const { dir } = p.userData;
  for (let i = 0; i < pos.count; i++) {
    const x = pos.getX(i), z = pos.getZ(i);
    pos.setX(i, x * Math.cos(step * dir) - z * Math.sin(step * dir));
    pos.setZ(i, x * Math.sin(step * dir) + z * Math.cos(step * dir));
  }
  pos.needsUpdate = true;
}
let alarmFxOn = false;
function burstFx(on) {
  if (on === alarmFxOn) return;
  alarmFxOn = on;
  if (on) {
    const ov = document.getElementById("burst-overlay");
    ov.style.transition = "none"; ov.style.opacity = 1;      // 爆发闪
    requestAnimationFrame(() => {
      ov.style.transition = "opacity .9s ease-out"; ov.style.opacity = 0;
    });
  }
}
onAlarmFx = burstFx;                   // 覆盖任务 11 的空实现
init3D();
