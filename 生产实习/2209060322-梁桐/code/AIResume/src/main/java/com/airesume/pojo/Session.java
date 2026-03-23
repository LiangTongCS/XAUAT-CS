package com.airesume.pojo;

import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;

@Data
public class Session {
    private Integer id;
    private String sessionId;
    private String username;
    private String resumeResult;

    private LocalDateTime startTime;

    private List<SessionContent> contentList;

    public Session() {
    }

    public Session( String sessionId, String username, LocalDateTime startTime, List<SessionContent> content) {
        this.sessionId = sessionId;
        this.username = username;
        this.startTime = startTime;
        this.contentList = content;
    }

    public Session(Integer id, String sessionId, String username, String resumeResult, LocalDateTime startTime, List<SessionContent> contentList) {
        this.id = id;
        this.sessionId = sessionId;
        this.username = username;
        this.resumeResult = resumeResult;
        this.startTime = startTime;
        this.contentList = contentList;
    }
}
