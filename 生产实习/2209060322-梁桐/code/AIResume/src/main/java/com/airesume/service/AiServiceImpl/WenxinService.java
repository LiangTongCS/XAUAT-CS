package com.airesume.service.AiServiceImpl;

import com.airesume.pojo.SessionContent;
import com.airesume.service.AiService;
import com.google.gson.*;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.*;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestClientException;
import org.springframework.web.client.RestTemplate;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Service("wenxinService")
@Slf4j
public class WenxinService implements AiService {

    @Value("${wenxin.api.key}")
    private String apiKey;

    @Value("${wenxin.api.url}")
    private String apiUrl;

    /**
     * 调用文心一言 API（使用千帆API Key直接认证）
     *
     * @param prompt 用户输入
     * @return AI 生成的响应
     */
    @Override
    public Map<String, String> callAiAPI(String prompt) {
        // 1. 清理API Key中的空白字符
        String cleanApiKey = apiKey.trim().replaceAll("\\s", "");

        // 2. 构建请求头
        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_JSON);
        headers.set("Authorization", "Bearer " + cleanApiKey);

        // 3. 构建请求体
        JsonObject requestBody = new JsonObject();
        requestBody.addProperty("model", "ernie-3.5-8k"); // 默认模型

        JsonArray messages = new JsonArray();
        messages.add(createMessage("user", prompt));
        requestBody.add("messages", messages);

        // 4. 创建HTTP实体
        HttpEntity<String> entity = new HttpEntity<>(requestBody.toString(), headers);

        // 5. 发送请求
        RestTemplate restTemplate = new RestTemplate();
        try {
            ResponseEntity<Map> response = restTemplate.postForEntity(apiUrl, entity, Map.class);

            // 6. 解析响应 - 适配千帆API的实际响应结构
            if (response.getStatusCode() == HttpStatus.OK && response.getBody() != null) {
                Map<String, Object> responseBody = response.getBody();

                // 检查错误码
                if (responseBody.containsKey("error_code")) {
                    throw new RuntimeException("API返回错误: " +
                            responseBody.get("error_msg") + " (code: " +
                            responseBody.get("error_code") + ")");
                }

                // 千帆API返回结构：直接包含result字段
                if (responseBody.containsKey("result")) {
                    String result = (String) responseBody.get("result");

                    // 清理JSON字符串（去除可能的代码块标记）
                    String cleanedResult = result.replace("```json", "").replace("```", "").trim();

                    Map<String, String> resultMap = new HashMap<>();
                    resultMap.put("content", cleanedResult);
                    return resultMap;
                }

                // 如果没有result字段，尝试OpenAI兼容结构
                if (responseBody.containsKey("choices")) {
                    Map<String, Object> firstChoice = ((Map<String, Object>) ((java.util.List<?>) responseBody.get("choices")).get(0));
                    Map<String, Object> message = (Map<String, Object>) firstChoice.get("message");
                    String content = (String) message.get("content");

                    Map<String, String> resultMap = new HashMap<>();
                    resultMap.put("content", content);
                    return resultMap;
                }

                throw new RuntimeException("API返回格式异常，未找到result或choices字段");
            }
            throw new RuntimeException("调用文心一言千帆 API 失败: " + response.getBody());
        } catch (RestClientException e) {
            throw new RuntimeException("API请求失败: " + e.getMessage(), e);
        }
    }

    /**
     * 创建消息对象
     */
    private JsonObject createMessage(String role, String content) {
        JsonObject message = new JsonObject();
        message.addProperty("role", role);
        message.addProperty("content", content);
        return message;
    }

    /**
     * 生成对话回复
     *
     * @param history      对话历史
     * @param resumeResult 简历分析结果
     * @return
     */
    // 新增对话生成方法
    @Override
    public String generateResponse(List<SessionContent> history, Map<String, String> resumeResult) {
        // 构造包含简历上下文的提示
        StringBuilder prompt = new StringBuilder();

        // 添加简历信息（如果有）
        if (resumeResult != null) {
            prompt.append("以下是当前分析的简历信息：\n");
            prompt.append(resumeResult.get("content")).append("\n");
        }

        // 添加对话历史
        prompt.append("对话历史：\n");
        for (SessionContent msg : history) {
            prompt.append(msg.getRole()).append(": ").append(msg.getContent()).append("\n");
        }
        prompt.append("\n请根据以上信息回复用户：");

        log.info("千帆 API调用：{}", prompt.toString());
        // 调用千帆 API
        Map<String, String> response = callAiAPI(prompt.toString());
        return response.get("content");
    }
}