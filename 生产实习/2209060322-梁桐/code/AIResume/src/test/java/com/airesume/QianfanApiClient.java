package com.airesume;

import okhttp3.*;
import com.google.gson.*;
import java.io.IOException;

public class QianfanApiClient {
    private static final String API_URL = "https://qianfan.baidubce.com/v2/chat/completions";
    private static final String API_KEY = "bce-v3/ALTAK-xjbBfLcX55rnN7ECgOrnq/19ac0edce1133e8301784ac3676e6d0ebf630cb7"; // 替换为你的API Key

    public static void main(String[] args) throws IOException {
        String response = callQianfanApi("你是哪个大模型，由哪个公司开发");
        System.out.println("AI回复: " + response);
    }

    public static String callQianfanApi(String userInput) throws IOException {
        // 1. 构建请求体（JSON格式）
        JsonObject requestBody = new JsonObject();
        requestBody.addProperty("model", "ernie-3.5-8k"); // 可替换为ernie-4.0-turbo-8k等模型
        
        JsonArray messages = new JsonArray();
        messages.add(createMessage("system", "请回答问题"));
        messages.add(createMessage("user", userInput));
        requestBody.add("messages", messages);

        // 2. 配置HTTP客户端
        OkHttpClient client = new OkHttpClient();
        RequestBody body = RequestBody.create(
            requestBody.toString(),
            MediaType.parse("application/json; charset=utf-8")
        );

        // 3. 添加认证头
        Request request = new Request.Builder()
            .url(API_URL)
            .post(body)
            .addHeader("Authorization", "Bearer " + API_KEY)
            .addHeader("Content-Type", "application/json")
            .build();

        // 4. 发送请求并解析响应
        try (Response response = client.newCall(request).execute()) {
            if (!response.isSuccessful()) throw new IOException("请求失败: " + response.code());
            
            JsonObject jsonResponse = JsonParser.parseString(response.body().string()).getAsJsonObject();
            return jsonResponse.getAsJsonArray("choices")
                .get(0).getAsJsonObject()
                .getAsJsonObject("message")
                .get("content").getAsString();
        }
    }

    private static JsonObject createMessage(String role, String content) {
        JsonObject message = new JsonObject();
        message.addProperty("role", role);
        message.addProperty("content", content);
        return message;
    }
}