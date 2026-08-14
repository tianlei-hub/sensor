/**
 * @file    bridge.js
 * @brief   OneNET 数据桥接服务 —— 让浏览器看板绕过跨域拿到真实设备数据
 *
 * 为什么需要它：
 *   浏览器直接 fetch https://iot-api.heclouds.com 会被 CORS 拦截，
 *   且密钥不能暴露到前端。本脚本在本地持有密钥、完成 HMAC-SHA1
 *   签名并调 OneNET API，再把结果通过本地 HTTP 服务（已开 CORS）提供给
 *   dashboard.html 的「OneNET 实时」模式。
 *
 * 用法：
 *   1. 改下方 CONFIG 里的 deviceKey / product_id / device_name
 *   2. 运行：  node bridge.js
 *   3. 打开 dashboard.html，数据源切到「OneNET 实时」
 *
 * 注意：deviceKey 是敏感凭据，仓库公开前务必移除或改读环境变量。
 */
'use strict';

const http  = require('http');
const https = require('https');
const crypto = require('crypto');

/* ==================== 配置（按你的账号修改） ==================== */
const CONFIG = {
  /* 查询设备属性（res 含 devices/{device}）必须用「设备级密钥」——
   * 即设备详情页的 Device Key，不是产品 access_key（用 access_key 会返回 10403）。 */
  deviceKey:  'QUJRVXJrMXhsNWE5ZVA5YUJkVGZGOXpYMnlLNzNKMXA=',
  productId:  'GRy0CBnliY',   // 产品 ID
  deviceName: 'test1',        // 设备名称
  port:       8080            // 本地服务端口
};

/* ==================== OneNET 安全鉴权 token ==================== */
function buildToken() {
  const version = '2018-10-31';
  const method  = 'sha1';
  const res     = `products/${CONFIG.productId}/devices/${CONFIG.deviceName}`;
  const et      = Math.floor(Date.now() / 1000) + 3600;   // 1 小时有效期
  // stringForSignature = et + "\n" + method + "\n" + res + "\n" + version
  const msg  = `${et}\n${method}\n${res}\n${version}`;
  // sign = base64(hmac_sha1(base64decode(deviceKey), msg))
  const key  = Buffer.from(CONFIG.deviceKey, 'base64');
  const sign = crypto.createHmac('sha1', key).update(msg).digest('base64');
  // res 与 sign 需 URL 编码（/ → %2F，= → %3D）
  return `version=${version}&res=${encodeURIComponent(res)}&et=${et}&method=${method}&sign=${encodeURIComponent(sign)}`;
}

/* ==================== 查询设备最新属性 ==================== */
function queryDeviceProperty(cb) {
  const path = `/thingmodel/query-device-property?product_id=${CONFIG.productId}&device_name=${CONFIG.deviceName}`;
  const req = https.request({
    host: 'iot-api.heclouds.com',
    path: path,
    method: 'GET',
    headers: { 'Authorization': buildToken() }
  }, (res) => {
    let body = '';
    res.on('data', (c) => { body += c; });
    res.on('end', () => {
      let j;
      try { j = JSON.parse(body); }
      catch (e) { return cb(new Error('JSON 解析失败: ' + body.slice(0, 200))); }
      // 成功时 code=0；鉴权失败 code=10403 等
      if (j.code === 0 || j.code === 'onenet_common_success' || j.code_no === '000000') {
        cb(null, j.data);
      } else {
        cb(new Error('OneNET 错误: ' + (j.msg || j.message || j.code || JSON.stringify(j))));
      }
    });
  });
  req.on('error', cb);
  req.end();
}

/* 把 OneNET 属性数组映射成看板字段（value 为字符串，需 parseFloat） */
function parseProps(data) {
  const out = { temperature: null, humidity: null, light: null, ts: Date.now() };
  const arr = data && (Array.isArray(data) ? data : (data.data || data.properties || data.list));
  if (!Array.isArray(arr)) return out;
  for (const it of arr) {
    const id = String(it.identifier || it.id || it.name || '').toLowerCase();
    if (id.includes('temperature')) out.temperature = parseFloat(it.value);
    else if (id.includes('humidity')) out.humidity = parseFloat(it.value);
    else if (id.includes('light'))    out.light    = parseFloat(it.value);
  }
  return out;
}

/* ==================== HTTP 服务 ==================== */
const server = http.createServer((req, res) => {
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setHeader('Access-Control-Allow-Methods', 'GET, OPTIONS');
  res.setHeader('Content-Type', 'application/json; charset=utf-8');

  if (req.method === 'OPTIONS') { res.writeHead(204); return res.end(); }
  if (req.url.startsWith('/api/latest')) {
    queryDeviceProperty((err, data) => {
      if (err) {
        res.writeHead(502);
        return res.end(JSON.stringify({ online: false, error: err.message }));
      }
      res.writeHead(200);
      res.end(JSON.stringify(Object.assign({ online: true }, parseProps(data))));
    });
    return;
  }
  res.writeHead(404);
  res.end(JSON.stringify({ error: 'not found' }));
});

server.listen(CONFIG.port, () => {
  console.log(`[bridge] OneNET 数据桥接已启动: http://localhost:${CONFIG.port}/api/latest`);
  console.log(`[bridge] 产品=${CONFIG.productId} 设备=${CONFIG.deviceName}`);
});
