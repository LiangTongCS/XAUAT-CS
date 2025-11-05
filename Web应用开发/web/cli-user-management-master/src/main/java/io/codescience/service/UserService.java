package io.codescience.service;

import io.codescience.model.User;
import io.codescience.repository.HibernateUserRepositoryImpl;
import io.codescience.repository.UserRepository;

import java.util.List;
import java.util.Optional;

public class UserService {
    private final UserRepository repository;

    public UserService() {
        this.repository = new HibernateUserRepositoryImpl();
    }

    public User addUser(User user) {
        return repository.save(user);
    }

    public User getUser(int id) {
        return repository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("用户不存在"));
    }

    public List<User> listUsers() {
        return repository.findAll();
    }

    public void deleteUser(int id) {
        if (!repository.findById(id).isPresent()) {
            throw new IllegalArgumentException("用户不存在");
        }
        repository.deleteById(id);
    }

    public void updateUser(int id, User user) {
        if (!repository.findById(id).isPresent()) {
            throw new IllegalArgumentException("用户不存在");
        }
        user.setId(id);
        repository.update(user);
    }
}