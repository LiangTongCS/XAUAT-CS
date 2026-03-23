package com.airesume.pojo;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import lombok.Data;

@Entity
@Data
public class RoleAuthority {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)// 主键自增长
    private Integer id;
    private String role;
    private String authority;


    public RoleAuthority() {
    }

    public RoleAuthority(String role, String authority) {
        this.role = role;
        this.authority = authority;
    }
}
