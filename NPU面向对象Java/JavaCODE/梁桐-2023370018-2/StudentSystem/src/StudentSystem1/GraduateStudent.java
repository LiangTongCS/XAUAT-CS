package StudentSystem1;

import java.util.*;
import com.alibaba.fastjson2.*;
import java.io.*;
public class GraduateStudent extends StudentInfo {
    private String supervisor;

    public GraduateStudent(String studentNumber, String studentName, String gander, String birthday, String academy, String major, String supervisor) {
        super(studentNumber, studentName, gander, birthday, academy, major);
        this.supervisor = supervisor;
    }

    public String getSupervisor() {
        return supervisor;
    }

    @Override
    public void displayInfo() {
        System.out.println("{\"studentNumber\":\"" + getStudentNumber() + "\",\"studentName\":\"" + getStudentName() + "\",\"gander\":\"" + getGander() +
                "\",\"birthday\":\"" + getBirthday() + "\",\"academy\":\"" + getAcademy() + "\",\"major\":\"" + getMajor() + "\",\"supervisor\":\"" + getSupervisor() + "\"}");
    }

    // 从 JSON 文件中加载研究生信息并添加到 studentList 列表中
    public static void loadGraduateStudents(String jsonFilePath, List<StudentInfo> studentList) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader(jsonFilePath));
            StringBuilder jsonContent = new StringBuilder();
            String line;
            // 逐行读取 JSON 文件内容
            while ((line = reader.readLine()) != null) {
                jsonContent.append(line);
            }
            reader.close();

            // 将 JSON 字符串解析为 JSONArray
            JSONArray jsonArray = JSON.parseArray(jsonContent.toString());
            // 遍历 JSONArray，解析每个研究生信息并添加到 studentList 中
            for (Object obj : jsonArray) {
                JSONObject jsonObject = (JSONObject) obj;
                String studentNumber = jsonObject.getString("studentNumber");
                String studentName = jsonObject.getString("studentName");
                String gander = jsonObject.getString("gander");
                String birthday = jsonObject.getString("birthday");
                String academy = jsonObject.getString("academy");
                String major = jsonObject.getString("major");
                String supervisor = jsonObject.getString("supervisor");

                // 创建 GraduateStudent 对象并添加到 studentList
                GraduateStudent graduateStudent = new GraduateStudent(studentNumber, studentName, gander, birthday, academy, major, supervisor);
                studentList.add(graduateStudent);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


}
