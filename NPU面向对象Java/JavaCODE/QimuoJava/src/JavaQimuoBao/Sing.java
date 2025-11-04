package JavaQimuoBao;

public class Sing {
    private String name;
    private static Sing sing1;
    private Sing(){
        name = "NCKOCEWM";
    }
    public static Sing getSing1(){
        if(sing1 == null){
             sing1 = new Sing();
        }
        return sing1;
    }
    public String getName(){
        return name;
    }
}
