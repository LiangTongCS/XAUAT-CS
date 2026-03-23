# AIResume 接口文档

## 约定
- 所有需要认证的接口需在请求头携带：`Authorization: Bearer <JWT>`
- 响应体默认为 JSON。错误响应遵循统一格式：
```json
{
  "timestamp": "2025-09-16T10:00:00Z",
  "status": 401,
  "error": "Unauthorized",
  "message": "令牌无效或已过期",
  "path": "/chat"
}
```

## 认证与账号

### 登录
- 方法：POST `/login`
- 请求体：
```json
{ "username": "admin", "password": "123456" }
```
- 成功响应：
```json
{ "token": "<jwt-token>" }
```
- 失败：`401 用户名或密码错误`

### 注册
- 方法：POST `/register`
- 请求体：
```json
{ "name": "张三", "username": "zhangsan", "password": "123456" }
```
- 成功响应：同登录，返回 `token`
- 失败：`400`（姓名/用户名/密码为空，或用户名已存在）

### 退出登录并持久化本次会话
- 方法：POST `/logout`
- 请求体：
```json
{ "sessionId": "b2d7e9d4-..." }
```
- 成功响应：`"退出成功"`

## AI 服务管理

### 切换 AI 服务提供方
- 方法：POST `/set-ai-service`
- 请求体：
```json
{ "service": "deepseek" }
```
- 可选值：`deepseek` | `wenxin`
- 成功响应：`"AI服务已切换为: deepseek"`
- 失败：`400 无效的AI服务`

## 对话与会话

### 发送对话消息（自动创建或继续会话）
- 方法：POST `/chat`
- 认证：需要
- 请求体：
```json
{
  "sessionId": "",  
  "message": "请根据我上传的简历给出面试问题建议"
}
```
- 响应：
```json
{
  "sessionId": "b2d7e9d4-...",
  "response": "基于你的项目经历，建议准备以下问题：..."
}
```
- 说明：`sessionId` 为空时将创建新会话并入库；服务端会自动注入简历分析上下文。

## 简历分析

### 上传简历并分析
- 方法：POST `/analyze`
- 认证：需要
- 权限：`ROLE_ADMIN` 或 `ROLE_ROOT`
- 请求：`multipart/form-data`
  - 字段：`resume`（文件：pdf/docx）
- 响应示例：
```json
{
  "content": "解析后的关键要点...",
  "extra": {
    "skills": ["Java","Spring","MySQL"],
    "education": "XXXX大学 本科",
    "workYears": 3
  }
}
```
- 失败：`403 Forbidden`（无权限）、`500 分析失败`

## 用户管理（/api/users）

### 列表
- 方法：GET `/api/users`
- 响应：`User[]`

### 新增
- 方法：POST `/api/users`
- 请求体：
```json
{ "name": "李四", "username": "lisi", "password": "123456", "roles": "ROLE_USER" }
```
- 响应：`User`

### 查询单个
- 方法：GET `/api/users/{id}`
- 响应：`User`

### 修改
- 方法：PUT `/api/users/{id}`
- 请求体：`User`
- 响应：`User`

### 删除
- 方法：DELETE `/api/users/{id}`
- 权限：`ROLE_ROOT`
- 响应：`200 OK`（空体）

### 分页搜索
- 方法：GET `/api/users/search`
- 查询参数：
  - `username`（可选）
  - `role`（可选）
  - `page`（默认0）
  - `size`（默认10）
- 响应：
```json
{
  "users": [ {"id":1, "username":"admin", "roles":"ROLE_ROOT"} ],
  "currentPage": 0,
  "totalItems": 15,
  "totalPages": 2
}
```

## 错误码与语义
- 400 Bad Request：参数缺失/非法（注册、切换 AI 服务等）
- 401 Unauthorized：未携带/无效 JWT、Token 过期
- 403 Forbidden：权限不足（需 `@RequirePermission`）
- 404 Not Found：资源不存在（如用户）
- 500 Internal Server Error：服务端异常（外部 AI 调用失败、简历解析异常等）

## 安全与最佳实践
- 生产环境将敏感配置（数据库口令、AI Key、JWT 密钥）改为环境变量或密钥管理服务，不要写入仓库。
- 前端需在所有受保护接口请求头携带 `Authorization: Bearer <JWT>`。
- 上传文件需在服务端校验类型与大小（`spring.servlet.multipart.*` 已限制为 5MB）。


