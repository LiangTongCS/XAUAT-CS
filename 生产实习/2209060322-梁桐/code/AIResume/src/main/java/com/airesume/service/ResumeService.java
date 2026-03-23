package com.airesume.service;

import com.airesume.mapper.SessionMapper;
import com.airesume.pojo.SessionContent;
import com.airesume.utils.FileUtils;
import com.airesume.utils.TokenContext;
import jakarta.annotation.Resource;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;

@Service
public class ResumeService {


    @Resource(name="deepseekService")
    private AiService deepSeekService;
    @Resource(name="wenxinService")
    private AiService wenxinService;
//    @Autowired
//    private DeepSeekService deepSeekService;
//    @Autowired
//    private WenxinService wenxinService;
    @Autowired
    private ChatSessionService chatSessionService;
    @Autowired
    private SessionMapper sessionMapper;

    /**
     * 分析简历
     * @param file 简历文件
     * @return 分析结果和会话ID
     * @throws Exception
     */
    public Map<String, Object> analyzeResume(MultipartFile file) throws Exception {
        // 创建新会话
        String sessionId = chatSessionService.createSession();

        // 读取文件内容
        String content = FileUtils.readFileContent(file);
        // 根据配置选择 AI 服务
        String aiService = System.getProperty("ai.service", "deepseek");

        // 构造AI提示
        String prompt = "请分析以下简历内容，提取以下信息并以JSON格式返回："
                + "姓名、联系方式、教育经历、工作经历、技能,驼峰式命名法，首字母小写如name，contact，education，workExperience，skills等等。"
                + "同时给出简历质量评分qualityScore（1-10分）和改进建议improvementSuggestions，命名方式如上。"
                + "\n\n简历内容：\n" + content;


        Map<String, String> result ;
        //大模型选择
        if ("wenxin".equalsIgnoreCase(aiService)) {
            // 使用文心一言
             result = wenxinService.callAiAPI(prompt);

        } else {

             result = deepSeekService.callAiAPI(prompt);
        }

        // 保存简历结果到会话
        chatSessionService.saveResumeResult(sessionId, result);
        // 保存到会话到数据库
        sessionMapper.insertSession(sessionId, TokenContext.getCurrentUserName(), LocalDateTime.now(),result.get("content"));

        // 添加初始消息到会话历史
        chatSessionService.addMessage(sessionId, new SessionContent("user", "已上传简历",true));
        chatSessionService.addMessage(sessionId, new SessionContent("assistant", "简历分析完成",true));

        // 返回结果和会话ID
        Map<String, Object> response = new HashMap<>(result);
        response.put("sessionId", sessionId);
        return response;
    }
}