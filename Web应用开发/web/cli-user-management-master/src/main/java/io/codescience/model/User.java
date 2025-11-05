package io.codescience.model;

import jakarta.persistence.*;
import jakarta.validation.constraints.*;

@Entity
@Table(name = "users")
public class User {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    @NotBlank(message = "姓名不能为空")
    @Size(max = 50, message = "姓名长度不能超过50个字符")
    @Column(nullable = false, length = 50)
    private String name;

    @NotBlank(message = "性别不能为空")
    @Size(max = 10, message = "性别长度不能超过10个字符")
    @Column(nullable = false, length = 10)
    private String gender;

    @Min(value = 0, message = "年龄不能为负数")
    @Column(nullable = false)
    private int age;

    @Email(message = "邮箱格式不正确")
    @Size(max = 100, message = "邮箱长度不能超过100个字符")
    @Column(nullable = false, length = 100)
    private String email;

    @Size(max = 20, message = "电话长度不能超过20个字符")
    @Column(nullable = false, length = 20)
    private String phone;

    public User() {
    }

    public User(String name, String gender, int age, String email, String phone) {
        validateInput(name, "姓名");
        validateInput(gender, "性别");
        validateAge(age);
        this.name = name;
        this.gender = gender;
        this.age = age;
        this.email = email;
        this.phone = phone;
    }

    private void validateInput(String value, String field) {
        if (value == null || value.trim().isEmpty()) {
            throw new IllegalArgumentException(field + "不能为空");
        }
    }

    private void validateAge(int age) {
        if (age < 0) {
            throw new IllegalArgumentException("年龄不能为负数");
        }
    }

    // Getters and Setters
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }
}