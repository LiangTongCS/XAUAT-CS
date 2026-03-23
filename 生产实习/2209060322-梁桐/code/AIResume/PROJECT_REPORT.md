# AIResume 项目报告

## 1. 项目背景
- 项目名称：AIResume
- 定位：面向求职者/HR 的 AI 简历分析与智能对话服务。
- 目标：解析 PDF/Word 简历，结构化关键信息；结合上下文进行多轮对话；可切换 DeepSeek/文心千帆等模型。
- 受众：个人求职者、HR、职业咨询服务机构。

## 2. 技术选型
- 后端：Spring Boot 3.5.5（Java 17）、Spring MVC、Spring Data JPA、MyBatis
- 数据库：MySQL 8.x
- 安全：JWT、拦截器 + 自定义权限注解
- AI 接入：DeepSeek、文心千帆（可热切换）
- 文档处理：Apache PDFBox、Apache POI
- 构建：Maven

## 3. 系统架构
- 分层：Controller / Service / Repository & Mapper / Utils
- 关键模块：
  - 鉴权与权限：`LoginInterceptor`、`JwtUtils`、`@RequirePermission`、`TokenContext`
  - 对话与会话：`ChatController`、`ChatSessionService`、`AiService`（DeepSeek/Wenxin）
  - 简历分析：`ResumeController`、`ResumeService`
  - 用户管理与日志：`UserController`、`UserService`、`LogService`、`UserRepository`、`LogRepository`
- 典型流程：登录签发 JWT → 上传简历 → 解析结果入上下文 → 对话融合上下文 → 退出落库会话历史。

## 4. 功能分析
- 认证与注册：`/login`、`/register`，签发含 `username`、`roles` 的 JWT。
- 权限控制：全局拦截业务接口，方法级 `@RequirePermission` 精确授权；`/analyze` 需 `ROLE_ADMIN|ROLE_ROOT`。
- 对话能力：`/chat` 自动创建或继续会话，拼接简历上下文，选择 DeepSeek/文心生成回复。
- 简历分析：支持 PDF/Word 上传解析，抽取关键点并回填对话上下文。
- 用户管理：CRUD 与分页检索；关键操作写审计日志。

## 5. 接口与示例
- 详见 `API.md`：覆盖认证/对话/简历分析/用户管理，含请求/响应示例与错误码说明。

## 6. 技术亮点
- 可插拔多模型路由（`AiService` 抽象 + 运行时切换）。
- 上下文增强提示工程（简历解析结果 + 会话历史）。
- 声明式权限（注解 + 拦截器），降低控制器样板代码。
- JPA 与 MyBatis 混合数据访问，兼顾敏捷与性能。
- 线程安全用户上下文（ThreadLocal 注入）。
- 预留流式输出能力（SSE/流式响应）。

## 7. 部署与运行
- 依赖：JDK 17、MySQL、Maven
- 配置：`application.properties`（端口、DB、AI URL/Key、文件大小限制、CORS）
- 启动：`mvn spring-boot:run` 或运行 `AiResumeApplication` 主类。
- 建议：生产环境使用环境变量/密钥管家注入敏感配置。

## 8. 安全与合规
- 敏感信息：避免仓库明文保存 AI Key/DB 口令；统一密钥管理。
- JWT：使用稳定签名密钥（或 RS256），支持密钥轮转；设置合理过期与刷新。
- 密码：使用 BCrypt 等强哈希存储。
- 校验与异常：引入 Hibernate Validator 与全局异常处理器，统一错误返回。

## 9. 性能与扩展
- 外部大模型调用为关键链路；建议增加缓存、超时重试、熔断与限流。
- 会话历史分页与归档；可引入 Redis/消息队列缓冲峰值。
- 前端可启用 SSE/WebSocket 获取流式回复提升体验。

## 10. 测试与质量
- 单元：`UserService`、`ResumeService`、`AiService` Mock 测试。
- 集成：登录鉴权、权限注解、简历上传解析、对话流程。
- 安全：CORS、日志脱敏、错误回显最小化。

## 11. 风险与改进
- 配置与密钥：改用环境变量/密钥服务；移除仓库明文。
- 统一返回：定义标准响应模型与错误码枚举，完善 `@ControllerAdvice`。
- 观测性：结构化日志、Tracing、指标与告警。
- 体验：对话结果流式输出；AI 服务降级与兜底回答。

## 12. 附录
- 代码入口：`com.airesume.AiResumeApplication`
- 关键文档：`arch.md`、`API.md`

