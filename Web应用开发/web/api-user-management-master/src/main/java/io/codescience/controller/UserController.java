package io.codescience.controller;

import io.codescience.model.User;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.*;

@RestController
@RequestMapping("/api/users")
public class UserController {

    // 模拟内存数据存储
    private final Map<Integer, User> userMap = new HashMap<>();
    private int currentId = 1;

    // 获取所有用户
    @GetMapping
    public ResponseEntity<List<User>> getAllUsers() {
        return ResponseEntity.ok(new ArrayList<>(userMap.values()));
    }

    // 创建用户
    @PostMapping
    public ResponseEntity<User> createUser(@RequestBody User user) {
        user.setId(currentId++);
        userMap.put(user.getId(), user);
        return ResponseEntity.ok(user);
    }

    // 获取指定 ID 用户
    @GetMapping("/{id}")
    public ResponseEntity<User> getUserById(@PathVariable Integer id) {
        User user = userMap.get(id);
        if (user != null) {
            return ResponseEntity.ok(user);
        }
        return ResponseEntity.notFound().build();
    }

    // 更新用户
    @PutMapping("/{id}")
    public ResponseEntity<?> updateUser(@PathVariable Integer id, @RequestBody User updatedUser) {
        User existing = userMap.get(id);
        if (existing == null) {
            return ResponseEntity.notFound().build();
        }
        updatedUser.setId(id);
        userMap.put(id, updatedUser);
        return ResponseEntity.ok().build();
    }

    // 删除用户
    @DeleteMapping("/{id}")
    public ResponseEntity<?> deleteUser(@PathVariable Integer id) {
        if (userMap.remove(id) != null) {
            return ResponseEntity.ok().build();
        }
        return ResponseEntity.notFound().build();
    }
}