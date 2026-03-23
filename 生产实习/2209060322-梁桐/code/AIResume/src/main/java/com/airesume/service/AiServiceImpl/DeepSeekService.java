package com.airesume.service.AiServiceImpl;

import com.airesume.pojo.SessionContent;
import com.airesume.service.AiService;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.*;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.servlet.mvc.method.annotation.StreamingResponseBody;


import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.*;

@Service("deepseekService")
@Slf4j
public class DeepSeekService implements AiService {

    @Value("${deepseek.api.key}")
    private String apiKey;

    @Value("${deepseek.api.url}")
    private String apiUrl;

    private final ObjectMapper objectMapper = new ObjectMapper();

    /**
     * 调用DeepSeek API
     *
     * @param prompt 用户输入
     * @return DeepSeek API返回的结果
     */
    @Override
    public Map<String, String> callAiAPI(String prompt) {
        //
        RestTemplate restTemplate = new RestTemplate();
        //设置请求体
        Map<String, Object> requestMap = new HashMap<>();
        requestMap.put("model", "deepseek-chat");

        List<Map<String, String>> messages = new ArrayList<>();
        Map<String, String> message = new HashMap<>();
        message.put("role", "user");
        message.put("content", prompt);
        messages.add(message);

        requestMap.put("messages", messages);


        try {
            String requestBody = objectMapper.writeValueAsString(requestMap);

            // 设置请求头
            HttpHeaders headers = new HttpHeaders();
            headers.set("Authorization", "Bearer " + apiKey);
            headers.setContentType(MediaType.APPLICATION_JSON);

            // 发送请求
            HttpEntity<String> entity = new HttpEntity<>(requestBody, headers);

            ResponseEntity<Map> response = restTemplate.postForEntity(apiUrl, entity, Map.class);

            // 从响应体中提取内容
            Map<String, Object> responseBody = response.getBody();

            //System.out.println("AI 返回的结果: "+responseBody);

            if (responseBody != null) {
                // 获取choices数组（可能有多个结果）
                List<Map<String, Object>> choices = (List<Map<String, Object>>) responseBody.get("choices");

                if (choices != null && !choices.isEmpty()) {
                    // 获取第一个choice
                    Map<String, Object> firstChoice = choices.get(0);

                    // 获取message对象
                    Map<String, Object> AImessage = (Map<String, Object>) firstChoice.get("message");

                    if (AImessage != null) {
                        // 最终提取回复内容
                        String result = (String) AImessage.get("content");
                        Map<String, String> responseMap = new HashMap<>();
                        responseMap.put("content", result);
                        return responseMap;

                    }
                }
            }
            System.out.println("DeepSeek API调用失败！");
            return null;
        } catch (JsonProcessingException e) {
            log.error("JSON序列化失败", e);
            return null;
        }
    }

    /**
     * 流式调用DeepSeek API
     * @param prompt 用户输入
     * @return StreamingResponseBody
     */
    public StreamingResponseBody streamResumeAnalysis(String prompt) {
        return outputStream -> {
            try {
                // 构造请求体
                Map<String, Object> requestBody = new HashMap<>();
                requestBody.put("model", "deepseek-chat");
                requestBody.put("stream", true);

                Map<String, String> message = new HashMap<>();
                message.put("role", "user");
                message.put("content", prompt);
                requestBody.put("messages", new Object[]{message});

                // 设置请求头
                HttpHeaders headers = new HttpHeaders();
                headers.set("Authorization", "Bearer " + apiKey);
                headers.setContentType(MediaType.APPLICATION_JSON);
                headers.setAccept(Collections.singletonList(MediaType.APPLICATION_STREAM_JSON));

                // 发送请求
                RestTemplate restTemplate = new RestTemplate();
                restTemplate.execute(
                        apiUrl,
                        HttpMethod.POST,
                        request -> {
                            request.getHeaders().putAll(headers);
                            request.getBody().write(new ObjectMapper().writeValueAsBytes(requestBody));
                        },
                        response -> {
                            try (InputStream body = response.getBody();
                                 BufferedReader reader = new BufferedReader(new InputStreamReader(body))) {

                                String line;
                                while ((line = reader.readLine()) != null) {
                                    if (line.startsWith("data: ")) {
                                        String json = line.substring(6);
                                        if (json.equals("[DONE]")) break;

                                        // 解析响应
                                        JsonNode node = new ObjectMapper().readTree(json);
                                        JsonNode choices = node.get("choices");
                                        if (choices != null && choices.size() > 0) {
                                            JsonNode delta = choices.get(0).get("delta");
                                            if (delta != null) {
                                                JsonNode content = delta.get("content");
                                                if (content != null && !content.isNull()) {
                                                    // 将内容写入输出流
                                                    outputStream.write(content.asText().getBytes());
                                                    outputStream.flush();
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            return null;
                        }
                );
            } catch (Exception e) {
                outputStream.write(("Error: " + e.getMessage()).getBytes());
            } finally {
                outputStream.close();
            }
        };
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
//            prompt.append("联系方式: ").append(resumeResult.get("contact")).append("\n");
//            prompt.append("教育经历: ").append(resumeResult.get("education")).append("\n");
//            prompt.append("工作经历: ").append(resumeResult.get("workExperience")).append("\n");
//            prompt.append("技能: ").append(resumeResult.get("skills")).append("\n\n");
        }

        // 添加对话历史
        prompt.append("对话历史：\n");
        for (SessionContent msg : history) {
            prompt.append(msg.getRole()).append(": ").append(msg.getContent()).append("\n");
        }
        prompt.append("\n请根据以上信息回复用户：");

        log.info("DeepSeek API调用：{}", prompt.toString());
        //log.info("DeepSeek API调用2：{}", prompt);
        // 调用DeepSeek API
        Map<String, String> response = callAiAPI(prompt.toString());
        return response.get("content");
    }
}