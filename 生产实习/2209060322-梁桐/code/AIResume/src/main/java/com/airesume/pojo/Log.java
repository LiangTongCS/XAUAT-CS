package com.airesume.pojo;

import jakarta.persistence.*;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@Entity
public class Log {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer logId;
    @Column(nullable = false)
    private String username;
    private String logContent;
    private LocalDateTime logDate;

    public Log() {
    }

    public Log(String username, String logContent, LocalDateTime logDate) {
        this.username = username;
        this.logContent = logContent;
        this.logDate = logDate;
    }
}
