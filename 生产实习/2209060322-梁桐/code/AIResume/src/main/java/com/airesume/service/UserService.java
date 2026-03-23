package com.airesume.service;




import com.airesume.pojo.User;
import com.airesume.repository.UserRepository;
import jakarta.persistence.criteria.Predicate;
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;


@Service
public class UserService {

    @Autowired
    private UserRepository userRepository;



    public List<User> getAllUsers() {
        return userRepository.findAll();
    }

    public User createUser(User user) {
        // 加密密码
        //
        user.setResentLoginTime(null);
        return userRepository.save(user);
    }

    public void deleteUser(Integer id) {
        userRepository.deleteById(id);
    }

    public User updateUser(User user) {
        User existing = userRepository.findById(user.getId()).orElse(null);
        if (existing == null) return null;

        // 只更新允许修改的字段
        existing.setName(user.getName());
        existing.setRoles(user.getRoles());

        // 如果提供了新密码，则更新
        if (user.getPassword() != null && !user.getPassword().isEmpty()) {
            existing.setPassword(user.getPassword());
        }

        return userRepository.save(existing);
    }

    /**
     * 条件查询,分页查询
     * @param username 用户名
     * @param role 角色
     * @param page  页码
     * @param size  页大小
     * @return
     */
    // 条件查询,分页查询
    public Page<User> searchUsers(String username, String role, int page, int size) {
        Pageable pageable = PageRequest.of(page, size);

        // 构建查询条件
        Specification<User> spec = (root, query, cb) -> {
            List<Predicate> predicates = new ArrayList<>();

            if (username != null && !username.isEmpty()) {
                predicates.add((Predicate) cb.like(root.get("username"), "%" + username + "%"));
            }

            if (role != null && !role.isEmpty()) {
                predicates.add(cb.equal(root.get("roles"), role));
            }

            return cb.and(predicates.toArray(new Predicate[0]));
        };

        return userRepository.findAll(spec, pageable);
    }
    /**
     * 登录认证，数据库查询
     * @param username 唯一用户名
     * @param password 密码
     * @return 认证成功返回true，否则返回false
     */
    public boolean authenticate(String username, String password) {
        String storedPassword = userRepository.findPasswordByUsername(username);
        return storedPassword != null && storedPassword.equals(password);
    }

    public String getRolesByUsername(String username) {
        return userRepository.findRolesByUsername(username);
    }

    public User findByUsername(String username) {
        return userRepository.findByUsername(username);
    }

    public User getUserById(Integer id) {
        return userRepository.findById(id).orElse(null);
    }

    public void save(User newUser) {
        userRepository.save(newUser);
    }
}
