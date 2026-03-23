package com.airesume.config;

import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class CorsConfig implements WebMvcConfigurer {
    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/**") // 对所有接口生效
                .allowedOrigins("http://localhost:63342") // 允许的前端源（必须明确指定，不能用*+credentials）
                .allowedMethods("GET", "POST", "PUT", "DELETE", "OPTIONS") // 允许的HTTP方法（包含预检请求的OPTIONS）
                .allowedHeaders("*") // 允许的请求头
                .exposedHeaders("*") // 允许前端读取的响应头
                .allowCredentials(true) // 是否允许携带Cookie（根据需求选择）
                .maxAge(3600); // 预检请求的缓存时间（秒），减少重复预检
    }
}