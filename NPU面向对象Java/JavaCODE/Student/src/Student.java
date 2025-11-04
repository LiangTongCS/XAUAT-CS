 class Student{
    private String username;

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }
}

class Test1{
    public static void main(String[] args){
        Student student = new Student();
        student.setUsername("刘郎");
        String username = student.getUsername();
        System.out.println((username));

    }
}



















