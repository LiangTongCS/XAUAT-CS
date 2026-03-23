package com.airesume.model;

import lombok.Data;


public class ChatMessage {
    private String role; // "user" 或 "assistant"
    private String content;

    // 构造函数、getter和setter
    public ChatMessage() {}
    
    public ChatMessage(String role, String content) {
        this.role = role;
        this.content = content;
    }

    public String getRole() {
        return role;
    }

    public void setRole(String role) {
        this.role = role;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }
// getter和setter省略...
}