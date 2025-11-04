package StudentSystem1;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public abstract class StudentInfo {
    private String studentNumber;
    private String studentName;
    private String gander;
    private String birthday;
    private String academy;
    private String major;
    private int ageInt;

    public StudentInfo(String studentNumber,String studentName, String gander, String birthday, String academy, String major) {
        this.studentNumber = studentNumber;
        this.studentName = studentName;
        this.gander = gander;
        this.birthday = birthday;
        this.academy = academy;
        this.major = major;
    }
    public abstract void displayInfo();
    public String getStudentNumber() {
        return studentNumber;
    }

    public String getGander() {
        return gander;
    }

    public String getBirthday() {
        return birthday;
    }

    public String getAcademy() {
        return academy;
    }

    public String getMajor() {
        return major;
    }

    public String getStudentName() {
        return studentName;
    }
    public int getAgeInt(){

                String input = birthday;

                // 定义匹配模式
                String pattern = "(\\d{4})年(\\d{2})月(\\d{2})日";
                Pattern regex = Pattern.compile(pattern);

                // 创建匹配器
                Matcher matcher = regex.matcher(input);

        ageInt = 0;
                // 检查是否匹配
                if (matcher.find()) {
                    // 提取年、月、日
                    String year = matcher.group(1);
                    String month = matcher.group(2);
                    String day = matcher.group(3);

                    // 转换为整数
                    int yearInt = Integer.parseInt(year);
                    int monthInt = Integer.parseInt(month);
                    int dayInt = Integer.parseInt(day);

                    ageInt = yearInt * 10000 + monthInt * 100 + dayInt;
            }
        return ageInt;
    }






}
