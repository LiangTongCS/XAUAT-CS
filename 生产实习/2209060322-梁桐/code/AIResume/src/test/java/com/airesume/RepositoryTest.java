package com.airesume;

import com.airesume.service.UserService;
import org.junit.Test;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestClientException;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.util.UriComponentsBuilder;

import java.util.Map;


public class RepositoryTest {


    @Value("${wenxin.api.key}")
    private String apiKey;

    @Value("${wenxin.api.secret}")
    private String apiSecret;

    @Value("${wenxin.api.url}")
    private String apiUrl;

    // 缓存 access token
    private String accessToken;
    private long tokenExpireTime;

    /**
     * 获取文心一言的 access token
     */

    @Test
    public void  getAccessToken() {
        if (accessToken != null && System.currentTimeMillis() < tokenExpireTime) {
            System.out.println("使用缓存的 access token: " + accessToken);
        }

        String tokenUrl = "https://aip.baidubce.com/oauth/2.0/token";
        RestTemplate restTemplate = new RestTemplate();

        // 使用URI模板避免拼接错误
        String requestUrl = UriComponentsBuilder.fromHttpUrl(tokenUrl)
                .queryParam("grant_type", "client_credentials")
                .queryParam("client_id", "bce-v3/ALTAK-xjbBfLcX55rnN7ECgOrnq/19ac0edce1133e8301784ac3676e6d0ebf630cb7")
                .queryParam("client_secret", "55da127ed5d4425aa423c67f8a05494c")
                .toUriString();

        try {
            ResponseEntity<Map> response = restTemplate.getForEntity(requestUrl, Map.class);

            if (response.getStatusCode() == HttpStatus.OK) {
                Map<String, Object> body = response.getBody();
                if (body != null && body.containsKey("access_token")) {
                    accessToken = (String) body.get("access_token");
                    long expiresIn = Long.parseLong(body.get("expires_in").toString());
                    tokenExpireTime = System.currentTimeMillis() + (expiresIn - 300) * 1000;
                    System.out.println("获取新的 access token: " + accessToken);
                }
                // 增加错误信息提取
                throw new RuntimeException("Token获取失败: " + body.getOrDefault("error_description", "Unknown error"));
            }
            throw new RuntimeException("HTTP状态异常: " + response.getStatusCode());
        } catch (RestClientException e) {
            throw new RuntimeException("Token请求失败: " + e.getMessage(), e);
        }
    }

}
