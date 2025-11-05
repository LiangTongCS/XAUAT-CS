# Shiyan3 - 用户管理系统

## 📋 项目简介

这是一个基于 Spring Boot 的用户管理系统，实现了用户信息的增删改查功能。项目采用了现代化的 Java 开发技术栈，包括 Spring Boot、MyBatis、MySQL 等技术，提供了 RESTful API 接口和命令行界面两种交互方式。

## 🛠️ 技术栈

- **框架**: Spring Boot 3.5.3
- **数据库**: MySQL 8.x
- **ORM 框架**: MyBatis 3.5.9
- **构建工具**: Maven
- **JDK 版本**: Java 17
- **数据库连接**: MySQL Connector/J

## 📁 项目结构

```
shiyan3/
├── src/
│   ├── main/
│   │   ├── java/
│   │   │   └── io/
│   │   │       └── codescience/
│   │   │           ├── Shiyan3Application.java      # Spring Boot 启动类
│   │   │           ├── config/
│   │   │           │   └── DatabaseConfig.java     # 数据库配置
│   │   │           ├── controller/
│   │   │           │   └── UserController.java     # REST API 控制器
│   │   │           ├── model/
│   │   │           │   └── User.java               # 用户实体类
│   │   │           ├── repository/
│   │   │           │   ├── UserRepository.java     # 用户仓库接口
│   │   │           │   ├── UserRepositoryImpl.java # 用户仓库实现
│   │   │           │   ├── UserMapper.java         # MyBatis 映射接口
│   │   │           │   └── MyBatisUserRepository.java # MyBatis 实现
│   │   │           ├── service/
│   │   │           │   └── UserService.java        # 用户业务逻辑
│   │   │           └── ui/
│   │   │               └── CliUI.java              # 命令行界面
│   │   └── resources/
│   │       ├── application.properties              # 应用配置
│   │       ├── mybatis-config.xml                  # MyBatis 配置
│   │       └── mapper/
│   │           └── UserMapper.xml                  # SQL 映射文件
│   └── test/
│       └── java/
│           └── io/
│               └── codescience/
│                   └── Shiyan3ApplicationTests.java # 测试类
├── pom.xml                                         # Maven 配置文件
└── README.md                                       # 项目说明文档
```

## 🚀 快速开始

### 环境要求

- JDK 17 或更高版本
- MySQL 8.x
- Maven 3.6+
- IDE (推荐 IntelliJ IDEA 或 Eclipse)

### 数据库准备

1. **启动 MySQL 服务**

   ```bash
   # Windows
   net start mysql

   # Linux/macOS
   sudo systemctl start mysql
   ```

2. **创建数据库**

   ```sql
   CREATE DATABASE user_management;
   USE user_management;

   CREATE TABLE users (
       id INT AUTO_INCREMENT PRIMARY KEY,
       name VARCHAR(100) NOT NULL,
       gender VARCHAR(10) NOT NULL,
       age INT NOT NULL,
       email VARCHAR(255),
       phone VARCHAR(20)
   );
   ```

3. **配置数据库连接**

   根据你的 MySQL 配置，修改 `src/main/java/io/codescience/config/DatabaseConfig.java` 中的数据库连接信息：

   ```java
   public static final String URL = "jdbc:mysql://localhost:3306/user_management?useSSL=false&serverTimezone=UTC";
   public static final String USER = "your_username";
   public static final String PASSWORD = "your_password";
   ```

### 运行项目

1. **克隆项目**

   ```bash
   git clone [项目地址]
   cd shiyan3
   ```

2. **编译项目**

   ```bash
   mvn clean compile
   ```

3. **运行 Spring Boot 应用**

   ```bash
   mvn spring-boot:run
   ```

   或者在 IDE 中直接运行 `Shiyan3Application.java` 主类

4. **验证启动**

   访问 http://localhost:8080，如果看到 Spring Boot 默认页面说明启动成功。

## 🔧 功能特性

### 用户管理功能

- ✅ **创建用户**: 添加新的用户信息
- ✅ **查询用户**: 支持查询所有用户和根据 ID 查询特定用户
- ✅ **更新用户**: 修改现有用户信息
- ✅ **删除用户**: 根据 ID 删除用户
- ✅ **数据验证**: 对用户输入进行合法性检验

### 用户属性

- **id**: 用户唯一标识符（自动生成）
- **name**: 用户姓名（必填）
- **gender**: 性别（必填）
- **age**: 年龄（必填，非负数）
- **email**: 邮箱地址（可选）
- **phone**: 电话号码（可选）

## 📡 API 接口文档

### 基础 URL

```
http://localhost:8080/api/users
```

### 接口列表

#### 1. 获取所有用户

- **URL**: `GET /api/users`
- **描述**: 获取系统中所有用户信息
- **响应示例**:

```json
[
  {
    "id": 1,
    "name": "张三",
    "gender": "Male",
    "age": 25,
    "email": "zhangsan@example.com",
    "phone": "13800138001"
  },
  {
    "id": 2,
    "name": "李四",
    "gender": "Female",
    "age": 28,
    "email": "lisi@example.com",
    "phone": "13800138002"
  }
]
```

#### 2. 创建用户

- **URL**: `POST /api/users`
- **描述**: 创建新用户
- **请求体示例**:

```json
{
  "name": "王五",
  "gender": "Male",
  "age": 30,
  "email": "wangwu@example.com",
  "phone": "13800138003"
}
```

- **响应示例**:

```json
{
  "id": 3,
  "name": "王五",
  "gender": "Male",
  "age": 30,
  "email": "wangwu@example.com",
  "phone": "13800138003"
}
```

#### 3. 根据 ID 获取用户

- **URL**: `GET /api/users/{id}`
- **描述**: 根据用户 ID 获取特定用户信息
- **路径参数**: `id` - 用户 ID
- **响应示例**:

```json
{
  "id": 1,
  "name": "张三",
  "gender": "Male",
  "age": 25,
  "email": "zhangsan@example.com",
  "phone": "13800138001"
}
```

#### 4. 更新用户

- **URL**: `PUT /api/users/{id}`
- **描述**: 更新指定 ID 的用户信息
- **路径参数**: `id` - 用户 ID
- **请求体示例**:

```json
{
  "name": "张三（已更新）",
  "gender": "Male",
  "age": 26,
  "email": "zhangsan_updated@example.com",
  "phone": "13800138001"
}
```

#### 5. 删除用户

- **URL**: `DELETE /api/users/{id}`
- **描述**: 删除指定 ID 的用户
- **路径参数**: `id` - 用户 ID
- **响应**: HTTP 200 OK（删除成功）

## 🖥️ 命令行界面

项目还提供了命令行界面（CLI）用于用户管理，可以通过运行 `CliUI` 类来使用：

### 主要功能菜单

```
用户管理系统
1. 查看所有用户
2. 根据ID查找用户
3. 添加用户
4. 更新用户
5. 删除用户
6. 退出
```

### 使用方法

1. 在 IDE 中运行 `CliUI.java` 的 `main` 方法
2. 根据菜单提示选择相应功能
3. 按照提示输入相关信息

## 🧪 测试

### 运行单元测试

```bash
mvn test
```

### API 测试工具推荐

可以使用以下工具测试 API 接口：

1. **Postman**: 图形化 API 测试工具
2. **curl**: 命令行工具

   ```bash
   # 获取所有用户
   curl -X GET http://localhost:8080/api/users

   # 创建用户
   curl -X POST http://localhost:8080/api/users \
     -H "Content-Type: application/json" \
     -d '{"name":"测试用户","gender":"Male","age":25,"email":"test@example.com","phone":"13800138000"}'
   ```

3. **HTTPie**: 现代化命令行 HTTP 客户端

   ```bash
   # 获取所有用户
   http GET localhost:8080/api/users

   # 创建用户
   http POST localhost:8080/api/users name="测试用户" gender="Male" age:=25 email="test@example.com" phone="13800138000"
   ```

## 📊 数据库设计

### users 表结构

| 字段名 | 数据类型     | 约束                        | 描述           |
| ------ | ------------ | --------------------------- | -------------- |
| id     | INT          | PRIMARY KEY, AUTO_INCREMENT | 用户唯一标识符 |
| name   | VARCHAR(100) | NOT NULL                    | 用户姓名       |
| gender | VARCHAR(10)  | NOT NULL                    | 性别           |
| age    | INT          | NOT NULL                    | 年龄           |
| email  | VARCHAR(255) | NULL                        | 邮箱地址       |
| phone  | VARCHAR(20)  | NULL                        | 电话号码       |

### 索引建议

```sql
-- 为常用查询字段添加索引
CREATE INDEX idx_name ON users(name);
CREATE INDEX idx_email ON users(email);
```

## 🔍 故障排除

### 常见问题及解决方案

#### 1. 数据库连接失败

**问题**: `java.sql.SQLException: Access denied for user`
**解决方案**:

- 检查 MySQL 服务是否启动
- 验证数据库用户名和密码
- 确认数据库已创建
- 检查数据库 URL 格式

#### 2. 端口占用

**问题**: `Port 8080 was already in use`
**解决方案**:

- 修改 `application.properties` 中的端口：
  ```properties
  server.port=8081
  ```
- 或者终止占用 8080 端口的进程

#### 3. Maven 依赖下载失败

**问题**: 依赖包下载失败
**解决方案**:

```bash
# 清理并重新下载依赖
mvn clean install -U
```

#### 4. Java 版本不兼容

**问题**: `java.lang.UnsupportedClassVersionError`
**解决方案**:

- 确保使用 Java 17 或更高版本
- 检查 `JAVA_HOME` 环境变量设置

## 🚧 开发计划

### 待实现功能

- [ ] 用户认证和授权
- [ ] 分页查询支持
- [ ] 用户搜索功能
- [ ] 数据导入导出
- [ ] 用户头像上传
- [ ] 操作日志记录
- [ ] Web 前端界面
- [ ] API 文档自动生成（Swagger）

### 性能优化

- [ ] 数据库连接池配置
- [ ] 缓存机制集成（Redis）
- [ ] 数据库查询优化
- [ ] API 响应速度优化

## 📝 开发规范

### 代码风格

- 遵循 Java 命名规范
- 使用适当的注释
- 保持代码简洁和可读性
- 异常处理要完整

### Git 提交规范

```
feat: 新功能
fix: 修复bug
docs: 文档更新
style: 代码格式调整
refactor: 代码重构
test: 测试相关
chore: 构建过程或辅助工具的变动
```

## 📄 许可证

本项目仅用于学习和教育目的。

## 🙏 致谢

感谢老师的悉心指导和同学们的帮助支持。

---

**最后更新时间**: 2025 年 7 月 3 日
