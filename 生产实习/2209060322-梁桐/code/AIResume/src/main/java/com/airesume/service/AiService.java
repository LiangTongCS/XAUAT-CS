package com.airesume.service;

import com.airesume.pojo.SessionContent;

import java.util.List;
import java.util.Map;

public interface AiService {

    public Map<String, String> callAiAPI(String prompt);

    public String generateResponse(List<SessionContent> history, Map<String, String> resumeResult);
}
