package com.airesume;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
@MapperScan("com.airesume.mapper")
public class AiResumeApplication {

    public static void main(String[] args) {
        SpringApplication.run(AiResumeApplication.class, args);
    }

}
