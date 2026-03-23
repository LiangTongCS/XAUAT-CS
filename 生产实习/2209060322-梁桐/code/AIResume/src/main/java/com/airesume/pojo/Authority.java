package com.airesume.pojo;


import jakarta.persistence.*;
import lombok.Data;

@Entity
@Data
public class Authority {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;
    @Column(unique = true,nullable = false)//非空，唯一
    private String authority;
    private String description;

    public Authority() {
    }
    public Authority( String authority, String description) {
        this.authority = authority;
        this.description = description;
    }
}
