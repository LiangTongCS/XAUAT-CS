// CliUI.java
package io.codescience.ui;
import io.codescience.model.User;
import io.codescience.service.UserService;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class CliUI {
    private final UserService service = new UserService();

    public CliUI() {
        initSampleData();
    }

    private void initSampleData() {
        // 添加示例用户数据
        User user1 = new User("张三", "Male", 25, "zhangsan@example.com", "13800138001");
        User user2 = new User("李四", "Female", 28, "lisi@example.com", "13800138002");
        User user3 = new User("王五", "Male", 30, "wangwu@example.com", "13800138003");

        service.addUser(user1);
        service.addUser(user2);
        service.addUser(user3);

        System.out.println("示例数据初始化完成");
    }

    public void start() {
        System.out.println("用户管理系统启动（输入help查看命令帮助）");
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.print("\n> ");
            String input = scanner.nextLine().trim();
            if (input.isEmpty())
                continue;

            String[] args = input.split(" ");
            try {
                switch (args[0]) {
                    case "user":
                        handleUserCommand(args);
                        break;
                    case "exit":
                        System.out.println("系统退出");
                        return;
                    case "help":
                        printHelp();
                        break;
                    default:
                        System.out.println("未知命令");
                }
            } catch (Exception e) {
                System.out.println("错误: " + e.getMessage());
            }
        }
    }

    private void handleUserCommand(String[] args) {
        if (args.length < 2) {
            throw new IllegalArgumentException("命令不完整");
        }

        switch (args[1]) {
            case "add":
                addUserFlow(args);
                break;
            case "delete":
                deleteUserFlow(args);
                break;
            case "list":
                listUsersFlow(args);
                break;
            case "update":
                updateUserFlow(args);
                break;
            default:
                throw new IllegalArgumentException("未知命令: " + args[1]);
        }
    }

    private void addUserFlow(String[] args) {
        Map<String, String> params = parseParams(args);
        User user = new User(
                params.get("name"),
                params.get("gender"),
                Integer.parseInt(params.get("age")),
                params.get("email"),
                params.get("phone"));
        service.addUser(user);
        System.out.println("用户添加成功，ID: " + user.getId());
    }

    private Map<String, String> parseParams(String[] args) {
        Map<String, String> params = new HashMap<>();
        for (int i = 2; i < args.length; i++) {
            if (args[i].startsWith("--")) {
                String key = args[i].substring(2);
                params.put(key, args[++i]);
            }
        }
        return params;
    }

    private void printHelp() {
        System.out.println("可用命令：");
        System.out.println("user list");
        System.out.println("user add --name <姓名> --gender <性别> --age <年龄> --email <邮箱> --phone <电话>");
        System.out.println("user delete --id <用户ID>");
        System.out.println("user update --id <用户ID> [--name <姓名>] [--gender <性别>] [--age <年龄>] [--email <邮箱>] [--phone <电话>]");
        System.out.println("exit");
    }

    private void deleteUserFlow(String[] args) {
        Map<String, String> params = parseParams(args);
        String userId = params.get("id");
        if (userId == null) {
            throw new IllegalArgumentException("缺少用户ID参数");
        }
        try {
            int id = Integer.parseInt(userId);
            service.deleteUser(id);
            System.out.println("用户删除成功");
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("用户ID必须是数字");
        }
    }

    private void listUsersFlow(String[] args) {
        var users = service.listUsers();
        if (users.isEmpty()) {
            System.out.println("当前没有用户");
            return;
        }
        System.out.println("用户列表：");
        for (User user : users) {
            System.out.printf("ID: %d, 姓名: %s, 性别: %s, 年龄: %d, 邮箱: %s, 电话: %s%n",
                    user.getId(),
                    user.getName(),
                    user.getGender(),
                    user.getAge(),
                    user.getEmail(),
                    user.getPhone());
        }
    }

    private void updateUserFlow(String[] args) {
        Map<String, String> params = parseParams(args);
        String userId = params.get("id");
        if (userId == null) {
            throw new IllegalArgumentException("缺少用户ID参数");
        }

        try {
            int id = Integer.parseInt(userId);
            User user = service.getUser(id);
            if (user == null) {
                throw new IllegalArgumentException("用户不存在");
            }

            // 更新用户信息
            if (params.containsKey("name"))
                user.setName(params.get("name"));
            if (params.containsKey("gender"))
                user.setGender(params.get("gender"));
            if (params.containsKey("age"))
                user.setAge(Integer.parseInt(params.get("age")));
            if (params.containsKey("email"))
                user.setEmail(params.get("email"));
            if (params.containsKey("phone"))
                user.setPhone(params.get("phone"));

            service.updateUser(id, user);
            System.out.println("用户信息更新成功");
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("用户ID必须是数字");
        }
    }
}