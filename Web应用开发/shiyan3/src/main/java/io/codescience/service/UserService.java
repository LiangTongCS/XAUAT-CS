// UserService.java
package io.codescience.service;

import io.codescience.model.User;
import org.springframework.stereotype.Service;

import java.util.*;

@Service
public class UserService {
    private final Map<Integer, User> userMap = new HashMap<>();
    private int currentId = 1;

    public List<User> getAllUsers() {
        return new ArrayList<>(userMap.values());
    }

    public User createUser(User user) {
        user.setId(currentId++);
        userMap.put(user.getId(), user);
        return user;
    }

    public User getUserById(Integer id) {
        return userMap.get(id);
    }

    public boolean updateUser(Integer id, User updatedUser) {
        if (!userMap.containsKey(id)) {
            return false;
        }
        updatedUser.setId(id);
        userMap.put(id, updatedUser);
        return true;
    }

    public boolean deleteUser(Integer id) {
        return userMap.remove(id) != null;
    }
}