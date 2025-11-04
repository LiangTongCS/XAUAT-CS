package StudentSystem1;
import java.io.*;
import java.util.*;
public class UndergraduateStudent extends StudentInfo {
    private String tutor;

    public UndergraduateStudent(String studentNumber, String studentName, String gander, String birthday,
                                String academy, String major, String tutor) {
        super(studentNumber, studentName, gander, birthday, academy, major);
        this.tutor = tutor;
    }

    public String getTutor() {
        return tutor;
    }

    @Override
    public void displayInfo() {
        System.out.println(getStudentNumber() + "_" + getStudentName() + "_" + getGander() + "_" + getBirthday() + "_"
                + getAcademy() + "_" + getMajor() + "_" + getTutor());
    }

    public String displayInfo1() {
        return (getStudentNumber() + "_" + getStudentName() + "_" + getGander() + "_" + getBirthday() + "_"
                + getAcademy() + "_" + getMajor() + "_" + getTutor());
    }

    // 从文件中加载本科生信息并添加到 studentList 列表中
    public static void loadUndergraduateStudents(String txtFilePath, List<StudentInfo> studentList) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader(txtFilePath));
            String line;
            while ((line = reader.readLine()) != null) {
                String[] usInfo = line.split("_");

                // 检查数组长度
                if (usInfo.length >= 7) {
                    studentList.add(new UndergraduateStudent(usInfo[0], usInfo[1], usInfo[2], usInfo[3], usInfo[4], usInfo[5],
                            usInfo[6]));
                } else {

                   System.out.println("行的元素个数不足: " + line);
                }
            }
            reader.close();
        } catch (IOException e) {
            throw new RuntimeException("读取文件时发生错误：" + e.getMessage());
        }
    }

}




















































