package com.airesume.repository;

import com.airesume.pojo.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Repository
// 只需继承一个接口，就免费获得了成千上万行代码的功能
public interface UserRepository extends JpaRepository<User, Integer>, JpaSpecificationExecutor<User> {


    public User findByUsername(String username);

    @Query("select u.roles from User u where u.username=?1")
    public String findRolesByUsername(String username);


    public List<User> findAll();
    @Query("select u.password from User u where u.username =?1")
    String findPasswordByUsername(String username);
    public void deleteUserByUsername(String username);


}