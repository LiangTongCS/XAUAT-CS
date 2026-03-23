package com.airesume.controller;


import com.airesume.mapper.SessionMapper;
import com.airesume.pojo.Session;
import com.airesume.pojo.SessionContent;
import com.airesume.service.AiService;
import com.airesume.service.ChatSessionService;

import com.airesume.utils.TokenContext;
import com.fasterxml.jackson.databind.ObjectMapper;
import jakarta.annotation.Resource;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;


/**
 * 聊天控制器
 **/
@Slf4j
@RestController
public class ChatController {

    @Resource(name = "deepseekService")
    private AiService deepSeekService;
    @Resource(name = "wenxinService")
    private AiService wenxinService;

    @Autowired
    private ChatSessionService chatSessionService;
    @Autowired
    private SessionMapper sessionMapper;

    @PostMapping("/chat")
    public ResponseEntity<?> handleChat(@RequestBody Map<String, String> request) {
        String sessionId = request.get("sessionId");
        String message = request.get("message");

        // 如果没有sessionId，创建新会话
        if (sessionId == null || sessionId.isEmpty()) {
            sessionId = chatSessionService.createSession();
            // 保存到会话到数据库
            sessionMapper.insertSession(sessionId, TokenContext.getCurrentUserName(), LocalDateTime.now(), null);
        }

        // 添加用户消息到会话历史
        chatSessionService.addMessage(sessionId, new SessionContent("user", message,true));

        // 获取简历分析结果（如果有）
        Map<String, String> resumeResult = chatSessionService.getResumeResult(sessionId);

        // 获取会话历史
        List<SessionContent> history = chatSessionService.getSessionHistory(sessionId);

        // 根据配置选择 AI 服务
        String aiService = System.getProperty("ai.service", "deepseek");

        String response;
        //大模型选择
        if ("wenxin".equalsIgnoreCase(aiService)) {
            // 使用文心一言
            response = wenxinService.generateResponse(history, resumeResult);

        } else {

            response = deepSeekService.generateResponse(history, resumeResult);
        }
        // 调用DeepSeek API
        //String response = deepSeekService.generateResponse(history, resumeResult);

        // 添加AI回复到会话历史
        chatSessionService.addMessage(sessionId, new SessionContent("assistant", response,true));

        log.info("user: {}, API: {}, sessionId: {}, message: {}, response: {}", TokenContext.getCurrentUserName(), System.getProperty("ai.service"), sessionId, message, response);
        // 返回响应
        Map<String, Object> result = new HashMap<>();
        result.put("sessionId", sessionId);
        result.put("response", response);

        return ResponseEntity.ok(result);
    }


    @GetMapping("/history")
    public ResponseEntity<?> getChatHistory() {
        String username = TokenContext.getCurrentUserName();

        try {
            // 查询用户的所有会话
            List<Session> sessions = sessionMapper.selectSessionsByUser(username);

            // 简化会话信息，只返回必要数据
            List<Map<String, Object>> history = sessions.stream()
                    .map(session -> {
                        Map<String, Object> item = new HashMap<>();
                        item.put("sessionId", session.getSessionId());
                        item.put("startTime", session.getStartTime());
                        item.put("resumeName", extractResumeName(session.getResumeResult()));
                        return item;
                    })
                    .collect(Collectors.toList());

            return ResponseEntity.ok(history);
        } catch (Exception e) {
            return ResponseEntity.status(500).body("获取历史对话失败");
        }
    }

    // 从简历结果中提取姓名
    private String extractResumeName(String resumeResult) {
        if (resumeResult == null || resumeResult.isEmpty()) {
            return "普通对话";
        }

        try {
            Map<String, Object> resultMap = new ObjectMapper().readValue(resumeResult, Map.class);
            if (resultMap.containsKey("name")) {
                if (resultMap.get("name").equals(""))
                    return "哈基米的简历分析";
                else {
                    return resultMap.get("name") + "的简历分析";
                }
            }
        } catch (
                Exception e) {
            // 忽略解析错误
        }
        return "简历分析";
    }

    @GetMapping("/session/{sessionId}")
    public ResponseEntity<?> getSession(@PathVariable String sessionId) {
        try {
            Session session = sessionMapper.selectSession(sessionId);
            log.info("session: {}", session);

            // 验证当前用户是否有权访问此会话
            if (!session.getUsername().equals(TokenContext.getCurrentUserName())) {
                return ResponseEntity.status(403).body("无权访问此会话");
            }
            chatSessionService.addSessionHistoryFromDB(session);

            return ResponseEntity.ok(session);
        } catch (Exception e) {
            return ResponseEntity.status(500).body("获取会话失败");
        }
    }
}