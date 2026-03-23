package com.airesume.pojo;

import jakarta.persistence.*;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;

@Data
@Entity
public class User {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY) // 主键生成策略：自增 (MySQL IDENTITY, H2 通常也是)
    private Integer id;

    private String name;

    @Column(unique = true,nullable = false) // 唯一索引,非空约束
    private String username;
    @Column(nullable = false) // 非空约束
    private String password;

    private String roles;

    private LocalDateTime resentLoginTime;

    public User(String name, String username, String password, String roles) {
        this.name = name;
        this.username = username;
        this.password = password;
        this.roles = roles;
        this.resentLoginTime = LocalDateTime.now();
    }

    public User() {
    }

}
