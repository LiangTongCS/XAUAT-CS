package com.airesume.controller;


import com.airesume.annotation.RequirePermission;
import com.airesume.pojo.Log;
import com.airesume.pojo.User;
import com.airesume.service.LogService;
import com.airesume.service.UserService;
import com.airesume.utils.TokenContext;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/users")
public class UserController {

    @Autowired
    private UserService userService;
    @Autowired
    private LogService logService;

    @GetMapping
    public ResponseEntity<List<User>> getAllUsers() {
        return ResponseEntity.ok(userService.getAllUsers());
    }
    //创建用户
    @PostMapping
    public ResponseEntity<User> createUser(@RequestBody User user) {
        User returnUser=userService.createUser(user);
        Log log = new Log(TokenContext.getCurrentUserName(),"创建用户:"+returnUser.toString(), LocalDateTime.now());
        logService.saveLog(log);
        return ResponseEntity.ok(returnUser);
    }

    //回显用户信息
    @GetMapping("/{id}")
    public ResponseEntity<User> getUserById(@PathVariable Integer id) {
        return ResponseEntity.ok(userService.getUserById(id));
    }

    //修改用户信息
    @PutMapping("/{id}")
    public ResponseEntity<User> updateUser(@PathVariable Integer id, @RequestBody User user) {
        Log log = new Log(TokenContext.getCurrentUserName(),"修改用户:"+user.toString(), LocalDateTime.now());
        logService.saveLog(log);

        user.setId(id);
        return ResponseEntity.ok(userService.updateUser(user));
    }
    @RequirePermission("ROLE_ROOT")
    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteUser(@PathVariable Integer id) {
        Log log = new Log(TokenContext.getCurrentUserName(),"删除用户:"+userService.getUserById(id), LocalDateTime.now());
        logService.saveLog(log);
        userService.deleteUser(id);
        return ResponseEntity.ok().build();
    }

    //分页查询用户信息
    @GetMapping("/search")
    public ResponseEntity<Map<String, Object>> searchUsers(
            @RequestParam(required = false) String username,
            @RequestParam(required = false) String role,
            @RequestParam(defaultValue = "0") int page,
            @RequestParam(defaultValue = "10") int size) {

        Page<User> userPage = userService.searchUsers(username, role, page, size);

        Map<String, Object> response = new HashMap<>();
        response.put("users", userPage.getContent());
        response.put("currentPage", userPage.getNumber());
        response.put("totalItems", userPage.getTotalElements());
        response.put("totalPages", userPage.getTotalPages());

        return ResponseEntity.ok(response);
    }
}