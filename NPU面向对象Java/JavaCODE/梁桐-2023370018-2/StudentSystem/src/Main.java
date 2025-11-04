import StudentSystem1.StudentManagementSystem;

import java.util.Scanner;

/**
 * 主类，程序入口
 */
public class Main {
    /**
     * 主函数，程序启动入口
     *
     * @param args 命令行参数
     */
    public static void main(String[] args) {
        StudentManagementSystem sms = new StudentManagementSystem();
        Scanner scanner = new Scanner(System.in);
        sms.LoadAll();

        while (true) {
            System.out.println("[A]打印全部学生信息");
            System.out.println("[B]新增一个本科生");
            System.out.println("[C]新增一个研究生");
            System.out.println("[D]新增一个博士生");
            System.out.println("[E]按学号查找学生");
            System.out.println("[F]按姓名查找学生");
            System.out.println("[G]学生排序");
            System.out.println("[Q]退出");

            System.out.print("请选择操作：");
            String choice = scanner.nextLine().toUpperCase();

            switch (choice) {
                case "A":
                    sms.displayAllStudents();
                    break;
                case "B":
                    sms.addUndergraduateStudentToTxt();
                    break;
                case "C":
                    sms.addGraduateStudentToJsonFile();
                    break;
                case "D":
                    sms.addDoctoralStudent();
                    break;
                case "E":
                    System.out.print("请输入学号：");
                    String studentNumberE = scanner.nextLine();
                    sms.findStudentByNumber(studentNumberE);
                    break;
                case "F":
                    System.out.print("请输入姓名：");
                    String studentNameF = scanner.nextLine();
                    sms.findStudentsByName(studentNameF);
                    break;
                case "G":
                    sms.sortStudents();
                    break;
                case "Q":
                    System.exit(0);
                    break;
                default:
                    System.out.println("无效的操作，请重新输入。");
            }
        }
    }
}