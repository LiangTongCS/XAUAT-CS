package com.airesume;

import com.airesume.mapper.SessionMapper;
import com.airesume.pojo.Session;
import com.airesume.pojo.User;
import com.airesume.service.UserService;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.List;

@SpringBootTest
class AiResumeApplicationTests {

    @Autowired
    private UserService userService;
    @Autowired
    private SessionMapper sessionMapper;


    //@Test
    void getAllUsers() {
        List<User> allUsers = userService.getAllUsers();
        for (User user : allUsers) {
            System.out.println(user.toString());
        }
    }

    //@Test
    void getUserByName() {
        User userByName = userService.findByUsername("admin");
        System.out.println(userByName.toString());
    }

    //@Test
    void getUserById() {
        User userById = userService.getUserById(1);
        System.out.println(userById.toString());
    }

    @Test
    void SessionTest() {
        String sessionId = "a2edc28d-eed6-4ad0-a891-e67a86e1ac0f";
        Session session = sessionMapper.selectSession(sessionId);
        System.out.println(session.toString());
    }


}
