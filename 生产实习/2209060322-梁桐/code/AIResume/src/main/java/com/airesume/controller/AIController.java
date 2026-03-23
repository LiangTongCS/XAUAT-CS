package com.airesume.controller;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import java.util.Map;

@RestController
public class AIController {

    @PostMapping("/set-ai-service")
    public ResponseEntity<?> setAIService(@RequestBody Map<String, String> request) {
        String service = request.get("service");
        if ("deepseek".equals(service) || "wenxin".equals(service)) {
            //设置系统属性，所有线程共享
            System.setProperty("ai.service", service);
            return ResponseEntity.ok("AI服务已切换为: " + service);
        }
        return ResponseEntity.badRequest().body("无效的AI服务");
    }
}