//@梁桐-学号2023370018-2班
package StudentSystem1;
import java.io.File;
import java.util.List;
import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;
public class DoctoralStudent extends StudentInfo{
    private String supervisor;
    private String researchFields;
    public DoctoralStudent(String studentNumber,String studentName,String gander, String birthday, String academy, String major,String supervisor,String researchFields) {
        super(studentNumber,studentName,gander,birthday,academy,major);
        this.supervisor = supervisor;
        this.researchFields = researchFields;
    }

    public String getSupervisor() {
        return supervisor;
    }

    public String getResearchFields() {
        return researchFields;
    }

    @Override
    public void displayInfo() {
        System.out.println("<studentInfo>\n\t<studentNumber>" + getStudentNumber() + "</studentNumber>\n\t<studentName>" + getStudentName() +
                "</studentName>\n\t<gander>" + getGander() + "</gander>\n\t<birthday>" + getBirthday() + "</birthday>\n\t<academy>" +
                getAcademy() + "</academy>\n\t<major>" + getMajor() + "</major>\n\t<supervisor>" + getSupervisor() + "</supervisor>\n\t<researchFields>" +
                getResearchFields() + "</researchFields>\n</studentInfo>");
    }



    // 静态方法，从XML文件中加载博士生信息
    public static void loadDoctoralStudents(String xmlFilePath, List<StudentInfo> studentList) {
        try {
            // 创建XML读取器
            SAXReader reader = new SAXReader();
            // 读取XML文档
            Document document = reader.read(new File(xmlFilePath));

            // 获取根元素
            Element rootElement = document.getRootElement();
            // 获取所有学生信息元素
            List<Element> studentElements = rootElement.elements("studentInfo");

            // 遍历学生信息元素列表
            for (Element studentElement : studentElements) {
                // 从XML元素中获取各个属性的值
                String studentNumber = studentElement.elementText("studentNumber");
                String studentName = studentElement.elementText("studentName");
                String gander = studentElement.elementText("gander");
                String birthday = studentElement.elementText("birthday");
                String academy = studentElement.elementText("academy");
                String major = studentElement.elementText("major");
                String supervisor = studentElement.elementText("supervisor");
                String researchFields = studentElement.elementText("researchFields");

                // 创建博士生对象并添加到列表中
                DoctoralStudent doctoralStudent = new DoctoralStudent(studentNumber, studentName, gander, birthday, academy, major, supervisor, researchFields);
                studentList.add(doctoralStudent);
            }
        } catch (DocumentException e) {
            e.printStackTrace();
        }
    }

}