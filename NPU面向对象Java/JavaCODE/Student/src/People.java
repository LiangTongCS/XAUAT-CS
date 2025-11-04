public class People {
    private int age;
    private String name;

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}

class Test{
    public static void main(String[] args){
        Student student = new Student();
        student.setUsername("刘郎");
        String username = student.getUsername();
        System.out.println((username));

    }
}