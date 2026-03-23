package com.airesume.pojo;

import lombok.Data;

/**
 * 会话消息
 */
@Data
public class SessionContent {

    private Integer id;
    private String sessionId;

    private String role;
    private String content;
//记录是否是新消息
    private boolean isNew;

    public SessionContent() {
    }

//    public SessionContent(String sessionId, String role, String content) {
//        this.sessionId = sessionId;
//        this.role = role;
//        this.content = content;
//    }

    public SessionContent(String role, String content, boolean isNew) {
        this.role = role;
        this.content = content;
        this.isNew = isNew;
    }

    public SessionContent(Integer id, String sessionId, String role, String content) {
        this.id = id;
        this.sessionId = sessionId;
        this.role = role;
        this.content = content;
        this.isNew = false;
    }

    public boolean getNew() {
        return isNew;
    }
}
