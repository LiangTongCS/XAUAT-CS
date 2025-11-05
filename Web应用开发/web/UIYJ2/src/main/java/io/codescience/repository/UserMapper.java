package io.codescience.repository;

import io.codescience.model.User;
import java.util.List;
import java.util.Optional;

public interface UserMapper {
    void insert(User user);
    Optional<User> findById(int id);
    List<User> findAll();
    void deleteById(int id);
    void update(User user);
}