package com.airesume.controller;


import com.airesume.mapper.SessionMapper;
import com.airesume.pojo.SessionContent;
import com.airesume.pojo.User;
import com.airesume.repository.UserRepository;
import com.airesume.service.ChatSessionService;
import com.airesume.service.UserService;
import com.airesume.utils.JwtUtils;
import com.airesume.utils.TokenContext;
import io.jsonwebtoken.Claims;
import jakarta.servlet.http.HttpServletRequest;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Slf4j
@RestController
public class LoginController {

    @Autowired
    private UserService userService;
    @Autowired
    private ChatSessionService chatSessionService;
    @Autowired
    private SessionMapper sessionMapper;



    @PostMapping("/login")
    public ResponseEntity<?> login(@RequestBody Map<String, String> credentials) {

        log.info("登录请求：{} ", credentials);
        String username = credentials.get("username");
        String password = credentials.get("password");

        if (userService.authenticate(username, password)) {
            // 获取用户角色
            User user = userService.findByUsername(username);
            String roles = user.getRoles();
            // 更新用户登录时间
            user.setResentLoginTime(LocalDateTime.now());
            userService.updateUser(user);

            // 生成JWT令牌
            Map<String, Object> claims = new HashMap<>();
            claims.put("username", username);
            claims.put("roles", roles); // 添加角色信息
            String token = JwtUtils.generateJwt(claims);

            // 返回token
            Map<String, String> response = new HashMap<>();
            response.put("token", token);
            return ResponseEntity.ok(response);
        } else {
            return ResponseEntity.status(401).body("用户名或密码错误");
        }
    }

    @PostMapping("/register")
    public ResponseEntity<?> register(@RequestBody Map<String, String> credentials) {
        String name = credentials.get("name");
        String username = credentials.get("username");
        String password = credentials.get("password");

        // 验证输入
        if (name == null || name.trim().isEmpty()) {
            return ResponseEntity.badRequest().body("姓名不能为空");
        }
        if (username == null || username.trim().isEmpty()) {
            return ResponseEntity.badRequest().body("用户名不能为空");
        }
        if (password == null || password.trim().isEmpty()) {
            return ResponseEntity.badRequest().body("密码不能为空");
        }

        // 检查用户名是否已存在
        if (userService.findByUsername(username) != null) {
            return ResponseEntity.badRequest().body("用户名已存在");
        }

        // 创建新用户
        User newUser = new User();
        newUser.setName(name);
        newUser.setUsername(username);
        newUser.setPassword(password);
        newUser.setRoles("ROLE_USER"); // 默认角色为普通用户
        newUser.setResentLoginTime(LocalDateTime.now());

        // 保存用户
        userService.save(newUser);

        // 自动登录新用户
        Map<String, Object> claims = new HashMap<>();
        claims.put("username", username);
        claims.put("roles", "ROLE_USER");
        String token = JwtUtils.generateJwt(claims);

        Map<String, String> response = new HashMap<>();
        response.put("token", token);

        return ResponseEntity.ok(response);
    }

    @PostMapping("/logout")
    public ResponseEntity<?> logout(@RequestBody Map<String, String> request) {
        String sessionId = request.get("sessionId");
        if (sessionId != null && !(sessionId.isEmpty())) {
            log.info("{}：退出登录请求 ", TokenContext.getCurrentUserName());

            //Map<String,String> result=chatSessionService.getResumeResult(sessionId);
            List<SessionContent> messageList = chatSessionService.getNewSessionHistory(sessionId);
            for (SessionContent message : messageList) {
                message.setSessionId(sessionId);
            }
            // 保存聊天记录到数据库
            try {
                sessionMapper.insertContent(messageList);
            } catch (Exception e) {
                log.error("保存会话内容失败: {}", e.getMessage());
            }
        }else{
            log.info("sessionId为空，用户没有发生对话");
        }

        return ResponseEntity.ok("退出成功");
    }
}
