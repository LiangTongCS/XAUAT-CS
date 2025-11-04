package JavaQimuoBao;

import java.util.Date;
import java.io.*;
import java.io.IOException;
import java.text.*;
import java.util.*;
import java.util.ArrayList;

public class Product {
    private String code;
    private String description;
    private Date productDate;
    private String sheIfLife;
    private double price;
    public Product(String code,String description,Date productDate,String sheIfLife,double price){
        this.code = code;
        this.description = description;
        this.productDate = productDate;
        this.sheIfLife = sheIfLife;
        this.price = price;
    }

    public String getCode() {
        return code;
    }

    public String getDescription() {
        return description;
    }

    public Date getProductDate() {
        return productDate;
    }

    public String getSheIfLife() {
        return sheIfLife;
    }

    public double getPrice() {
        return price;
    }

    public static void main(String[] args) {
        // 获取当前日期和时间

        Date Date1 = new Date();
        Product product = new Product("123","难喝",Date1,"5年",7.812);
         /*
        System.out.println(product.getCode() + "\n" + product.getDescription() + "\n"+ product.getProductDate() + "\n"+ product.getSheIfLife() + "\n" );


        String ceuistring = new String("我是个二狗");
        String ceuis = new String("我是个二狗");
        System.out.println(ceuis.equals(ceuistring));
        System.out.println(String.valueOf(product.getPrice()));
        String pricestr = String.valueOf(product.getPrice());
        System.out.println(String.valueOf(product.getPrice()) + pricestr + 1.237740914);
*/
        float ceuibaozhuang = 321.9f;
        Integer obj = new Integer((int)ceuibaozhuang);
        System.out.println(obj);
        int i = Integer.parseInt("123");
        Integer obj2 = 1234;
       // BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        //String input = stdIn.readLine();
//        Scanner s = new Scanner(System.in);
//        String putin = s.nextLine();
//        //System.out.printf("%s\n",putin);
//        System.out.printf("%s\n",putin);
//        int putin2 = s.nextInt();
//        System.err.printf("%d",putin2);
//        String[] arr = new String[5];
//        try(BufferedReader read1 = new BufferedReader(new InputStreamReader(System.in))){
//
//            String arr1 = read1.readLine();
//            int flag = 0;
//            while (arr1 != null)
//            {
//
//                arr[flag] = arr1;
//                arr1 = read1.readLine();
//                flag++;
//                if(flag == 5){
//                    read1.close();
//                    break;
//                }
//
//            }
//        }catch(IOException e1){
//            e1.printStackTrace();
//        }
//        for(String aa1 : arr){
//            System.out.println(aa1);
//
//        }
//
//
//        String dateString = "2002年09月29日";
//
//        // 定义日期格式
//        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy年MM月dd日");
//
//        try {
//            // 将字符串转换为Date类型
//            Date date = dateFormat.parse(dateString);
//
//            // 打印转换后的Date对象
//            System.out.println(date);
//        } catch (ParseException e) {
//            e.printStackTrace();
//        }

        Sing A = Sing.getSing1();
        System.out.println(A.getName());


    }
}

