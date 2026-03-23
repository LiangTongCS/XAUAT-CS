package com.airesume.service;


import com.airesume.mapper.SessionMapper;
import com.airesume.pojo.Session;
import com.airesume.pojo.SessionContent;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

@Slf4j
@Service
public class ChatSessionService {
    // 存储会话历史，key: sessionId, value: 消息列表
    private final Map<String, List<SessionContent>> sessions = new ConcurrentHashMap<>();
    
    // 存储简历分析结果，key: sessionId
    private final Map<String, Map<String, String>> resumeResults = new ConcurrentHashMap<>();

    @Autowired
    private SessionMapper sessionMapper;

    // 创建新会话
    public String createSession() {
        String sessionId = UUID.randomUUID().toString();
        sessions.put(sessionId, new ArrayList<>());
        return sessionId;
    }

    // 添加消息到会话
    public void addMessage(String sessionId, SessionContent message) {
        if (sessions.containsKey(sessionId)) {
            sessions.get(sessionId).add(message);
        }

    }

    // 获取会话历史
    public List<SessionContent> getSessionHistory(String sessionId) {
        return sessions.getOrDefault(sessionId, new ArrayList<>());
    }
    //获取新会话历史
    public List<SessionContent> getNewSessionHistory(String sessionId) {
        List<SessionContent> contentList =sessions.get(sessionId);
        List<SessionContent> newContentList = new ArrayList<>();
        for(SessionContent content:contentList){
            if(content.getNew())
                newContentList.add(content);
        }
        return newContentList;
    }

    // 保存简历分析结果
    public void saveResumeResult(String sessionId, Map<String, String> result) {
        resumeResults.put(sessionId, result);
    }

    // 获取简历分析结果
    public Map<String, String> getResumeResult(String sessionId) {
        return resumeResults.get(sessionId);
    }

    //从数据库中获取会话历史和简历分析结果
    @Transactional
    public void addSessionHistoryFromDB(Session session) {

        String resumeResult = session.getResumeResult();
        String sessionId = session.getSessionId();
        // 从数据库中获取会话历史
        List<SessionContent> contentList = session.getContentList();
        //反转消息列表
        Collections.reverse(contentList);
        log.info("contentList: " + contentList);
        // 保存简历分析结果到内存
        Map<String, String> result = new HashMap<String, String>();
        result.put("content", resumeResult);
        resumeResults.put(sessionId,result);
        // 保存会话历史到内存
        sessions.put(sessionId, contentList);
    }
}