package com.airesume.controller;

import com.airesume.annotation.RequirePermission;
import com.airesume.service.ResumeService;

import com.airesume.utils.TokenContext;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.util.Map;

@Slf4j
@RestController
public class ResumeController {

    @Autowired
    private ResumeService resumeService;

    @RequirePermission({"ROLE_ADMIN", "ROLE_ROOT"})
    @PostMapping("/analyze")
    public ResponseEntity<?> analyzeResume(@RequestParam("resume") MultipartFile file) {
        System.out.println("收到简历文件: " + file.getOriginalFilename());
        try {

            // 直接返回对象而不是字符串
            Map<String, Object> result = resumeService.analyzeResume(file);
            log.info("来自user：{}，API：{}，简历分析完成，返回结果: {}",TokenContext.getCurrentUserName(),System.getProperty("ai.service") ,result);

            return ResponseEntity.ok(result);

            //log.info("简历分析完成，返回: " + response);
            //return response;
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.internalServerError().body("分析失败");
        }
    }


}