package com.airesume.utils;

public class TokenContext {
    // 使用ThreadLocal存储当前用户ID
    private static final ThreadLocal<String> currentUserName = new ThreadLocal<>();
    // 使用ThreadLocal存储当前用户角色
    private static final ThreadLocal<String> currentUserRole = new ThreadLocal<>();

    public static String getCurrentUserRole() {
        return currentUserRole.get();
    }

    public static void setCurrentUserRole(String role) {

        currentUserRole.set(role);
    }

    public static String getCurrentUserName() {
        return currentUserName.get();
    }

    public static void setCurrentUserName(String username) {
        currentUserName.set(username);
    }

    // 请求完成后清理上下文
    public static void clear() {
        currentUserName.remove();
        currentUserRole.remove();
    }
}
