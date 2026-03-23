package com.airesume.mapper;

import com.airesume.pojo.Session;
import com.airesume.pojo.SessionContent;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

import java.time.LocalDateTime;
import java.util.List;

@Mapper
public interface SessionMapper {
    /**
     * 插入session
     */
    @Insert("insert into session(session_id, user_name, start_time, resume_result) values(#{sessionId}, #{username},#{startTime},#{resumeResult})")
    void insertSession(String sessionId, String username, LocalDateTime startTime,String resumeResult);

    /**
     *  查询用户所有session
     * @param username
     * @return
     */
    @Select("SELECT * FROM session WHERE user_name = #{username} ORDER BY start_time DESC")
    List<Session> selectSessionsByUser(String username);
    /**
     * 插入session内容
     * @param contentList 会话内容列表
     */
    void insertContent(List<SessionContent> contentList);

    /**
     * 查询session,包括对话内容
     * @param sessionId
     * @return
     */
    Session selectSession(String sessionId);

}
