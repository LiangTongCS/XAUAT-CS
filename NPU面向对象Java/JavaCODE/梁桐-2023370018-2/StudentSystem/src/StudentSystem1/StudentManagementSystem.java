package StudentSystem1;
import com.alibaba.fastjson2.JSON;
import com.alibaba.fastjson2.JSONArray;
import com.alibaba.fastjson2.JSONObject;
import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.OutputFormat;
import org.dom4j.io.SAXReader;
import org.dom4j.io.XMLWriter;
import java.io.*;
import java.util.*;
import java.lang.*;
/**
 * 学生管理系统类
 */
public class StudentManagementSystem {


    static List<StudentInfo> studentList111 = new ArrayList<>();
    static List<StudentInfo> studentList112 = new ArrayList<>();
    static List<StudentInfo> studentList113 = new ArrayList<>();
    //加载文件
    public static void LoadAll(){
        UndergraduateStudent.loadUndergraduateStudents("us.txt", studentList111);
        GraduateStudent.loadGraduateStudents("gs.json", studentList112);
        DoctoralStudent.loadDoctoralStudents("ds.xml", studentList113);
    }

    /**
     * 显示所有学生信息
     */
    public static void displayAllStudents() {
        for (StudentInfo student : studentList111) {
            student.displayInfo();
        }
        for (StudentInfo student : studentList112) {
            student.displayInfo();
        }
        for (StudentInfo student : studentList113) {
            student.displayInfo();
        }
    }

    public void addUndergraduateStudentToTxt(){
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("us.txt", true))) {
            Scanner scanner = new Scanner(System.in);
            System.out.println("请输入新本科生的信息（格式：studentNumber_studentName_gander_birthday_academy_major_tutor）：");
            String newStudentInfo = scanner.nextLine();
            String[] newStudentArray = newStudentInfo.split("_");
            writer.write(newStudentInfo);
            writer.newLine(); // 添加新行
            System.out.println("新本科生信息已成功添加并写入文件。");
        } catch (IOException e) {
            throw new RuntimeException("写入文件时发生错误：" + e.getMessage());
        }
        LoadAll();
    }
    // 添加一个研究生到 gs.json 文件
    public  void addGraduateStudentToJsonFile() {
        try {
            Scanner scanner = new Scanner(System.in);

            // 获取用户输入的研究生信息
            System.out.println("请输入研究生信息（格式：学号_姓名_性别_生日_学院_专业_导师）：");
            String input = scanner.nextLine();
            String[] studentInfo = input.split("_");

            // 创建 GraduateStudent 对象
            GraduateStudent newGraduateStudent = new GraduateStudent(studentInfo[0], studentInfo[1], studentInfo[2],
                    studentInfo[3], studentInfo[4], studentInfo[5], studentInfo[6]);

            // 读取原有的 JSON 数据
            JSONArray jsonArray = new JSONArray();
            File file = new File("gs.json");
            if (file.exists()) {
                BufferedReader reader = new BufferedReader(new FileReader("gs.json"));
                StringBuilder jsonContent = new StringBuilder();
                String line;
                while ((line = reader.readLine()) != null) {
                    jsonContent.append(line);
                }
                jsonArray = JSON.parseArray(jsonContent.toString());
                reader.close();
            }

            // 将新研究生信息转换为 JSON 对象
            JSONObject newStudentJson = new JSONObject();
            newStudentJson.put("studentNumber", newGraduateStudent.getStudentNumber());
            newStudentJson.put("studentName", newGraduateStudent.getStudentName());
            newStudentJson.put("gander", newGraduateStudent.getGander());
            newStudentJson.put("birthday", newGraduateStudent.getBirthday());
            newStudentJson.put("academy", newGraduateStudent.getAcademy());
            newStudentJson.put("major", newGraduateStudent.getMajor());
            newStudentJson.put("supervisor", newGraduateStudent.getSupervisor());

            // 将新学生信息添加到 JSON 数组
            jsonArray.add(newStudentJson);

            // 将更新后的 JSON 数组写入 gs.json 文件
            FileWriter fileWriter = new FileWriter("gs.json");
            fileWriter.write(jsonArray.toJSONString());
            fileWriter.close();

            System.out.println("研究生信息已成功添加到 gs.json 文件。");
        } catch (IOException e) {
            e.printStackTrace();
        }
        LoadAll();
    }

    // 新增的方法，用于添加博士生并更新ds.xml文件
    public static void addDoctoralStudent() {
        Scanner scanner = new Scanner(System.in);

        // 读取现有ds.xml文件
        Document document = readXmlFile("ds.xml");

        // 创建新的博士生元素
        Element newStudentElement = document.getRootElement().addElement("studentInfo");

        // 获取用户输入的博士生信息
        System.out.print("请输入新博士生信息（学号_姓名_性别_生日_学院_专业_导师_研究方向）：");
        String input = scanner.nextLine();
        String[] infoArray = input.split("_");

        // 设置新博士生的各个属性
        newStudentElement.addElement("studentNumber").setText(infoArray[0]);
        newStudentElement.addElement("studentName").setText(infoArray[1]);
        newStudentElement.addElement("gander").setText(infoArray[2]);
        newStudentElement.addElement("birthday").setText(infoArray[3]);
        newStudentElement.addElement("academy").setText(infoArray[4]);
        newStudentElement.addElement("major").setText(infoArray[5]);
        newStudentElement.addElement("supervisor").setText(infoArray[6]);
        newStudentElement.addElement("researchFields").setText(infoArray[7]);

        // 将新博士生对象添加到列表中
        DoctoralStudent doctoralStudent = new DoctoralStudent(infoArray[0], infoArray[1], infoArray[2], infoArray[3], infoArray[4], infoArray[5], infoArray[6], infoArray[7]);
        studentList113.add(doctoralStudent);

        // 将更新后的document写回ds.xml文件
        writeXmlFile("ds.xml", document);
    }

    // 读取XML文件
    public static Document readXmlFile(String xmlFilePath) {
        try {
            SAXReader reader = new SAXReader();
            return reader.read(new File(xmlFilePath));
        } catch (DocumentException e) {
            throw new RuntimeException("无法读取XML文件", e);
        }
    }

    // 将Document写回XML文件
    private static void writeXmlFile(String xmlFilePath, Document document) {
        try (FileWriter fileWriter = new FileWriter(xmlFilePath)) {
            OutputFormat format = OutputFormat.createPrettyPrint();
            XMLWriter writer = new XMLWriter(fileWriter, format);
            writer.write(document);
            writer.close();
        } catch (IOException e) {
            throw new RuntimeException("无法写入XML文件", e);
        }
    }


    /**
     * 按学号查找学生
     *
     * @param studentNumber 学号
     */
    public static void findStudentByNumber(String studentNumber) {
        for (StudentInfo student : studentList111) {
            if (student.getStudentNumber().equals(studentNumber)) {
                student.displayInfo();
                return;
            }
        }
        for (StudentInfo student : studentList112) {
            if (student.getStudentNumber().equals(studentNumber)) {
                student.displayInfo();
                return;
            }
        }
        for (StudentInfo student : studentList113) {
            if (student.getStudentNumber().equals(studentNumber)) {
                student.displayInfo();
                return;
            }
        }
        System.out.println("未找到学号为 " + studentNumber + " 的学生。");
    }

    /**
     * 按姓名查找学生
     *
     * @param studentName 姓名
     */
    public static void findStudentsByName(String studentName) {
        for (StudentInfo student : studentList111) {
            if (student.getStudentName().equals(studentName)) {
                student.displayInfo();
            }
        }
        for (StudentInfo student : studentList112) {
            if (student.getStudentName().equals(studentName)) {
                student.displayInfo();
            }
        }
        for (StudentInfo student : studentList113) {
            if (student.getStudentName().equals(studentName)) {
                student.displayInfo();
            }
        }
    }



    public static void sortStudents(){
        for (int i = 0; i < studentList111.size() - 1; i++) {
            for (int j = 0; j < studentList111.size() - i - 1; j++) {
                // 如果相邻元素顺序错误，交换它们
                if (studentList111.get(j).getAgeInt() > studentList111.get(j + 1).getAgeInt()) {
                    StudentInfo temp = studentList111.get(j);
                    studentList111.set(j, studentList111.get(j + 1));
                    studentList111.set(j + 1, temp);
                }
            }
        }
        for (int i1 = 0; i1 < studentList112.size() - 1; i1++) {
            for (int j1 = 0; j1 < studentList112.size() - i1 - 1; j1++) {
                // 如果相邻元素顺序错误，交换它们
                if (studentList112.get(j1).getAgeInt() > studentList112.get(j1 + 1).getAgeInt()) {
                    StudentInfo temp = studentList112.get(j1);
                    studentList112.set(j1, studentList112.get(j1 + 1));
                    studentList112.set(j1 + 1, temp);
                }
            }
        }
        for (int i2 = 0; i2 < studentList113.size() - 1; i2++) {
            for (int j2 = 0; j2 < studentList113.size() - i2 - 1; j2++) {
                // 如果相邻元素顺序错误，交换它们
                if (studentList113.get(j2).getAgeInt() > studentList113.get(j2 + 1).getAgeInt()) {
                    StudentInfo temp = studentList113.get(j2);
                    studentList113.set(j2, studentList113.get(j2 + 1));
                    studentList113.set(j2 + 1, temp);
                }
            }
        }
        displayAllStudents();

    }

}
