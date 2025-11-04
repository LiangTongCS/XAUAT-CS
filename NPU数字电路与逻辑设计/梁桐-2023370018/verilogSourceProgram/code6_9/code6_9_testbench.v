`timescale 1ns/1ps

module code6_9_testbench;

  reg clk_test, Resetn_test, w1_test, w2_test;
  wire z_test;

  initial begin
    clk_test = 0;
    Resetn_test = 0;
    w1_test = 0;
    w2_test = 0;
  end

  always #10 clk_test  = ~clk_test ;

  initial begin
    #10;
    Resetn_test = 1;
    w1_test = 0;    
    w2_test = 0;
    #20 w1_test = 1;w2_test = 0;
    #20 w1_test = 0;w2_test = 1;
    #20 w1_test = 1;w2_test = 0;
    #20 w1_test = 0;w2_test = 1;
    //90ns之后是题目示例数据
    #20 w1_test = 0;w2_test = 1;
    #20 w1_test = 1;w2_test = 1;
    #20 w1_test = 1;w2_test = 1;
    #20 w1_test = 0;w2_test = 0;
    #20 w1_test = 1;w2_test = 1;//此处z开始为1
    #20 w1_test = 1;w2_test = 0;
    #20 w1_test = 1;w2_test = 1;
    #20 w1_test = 0;w2_test = 0;
    #20 w1_test = 0;w2_test = 0;
    #20 w1_test = 0;w2_test = 0;//此处z开始为1
    #20 w1_test = 1;w2_test = 1;
    #20 w1_test = 1;w2_test = 1;
    #20 w1_test = 0;w2_test = 1;

    #20 w1_test = 1;w2_test = 0;
    #20 w1_test = 0;w2_test = 1;
    #20 w1_test = 1;w2_test = 0;
    #20 w1_test = 0;w2_test = 1;
    #20 w1_test = 0;w2_test = 0;
    #20 w1_test = 0;w2_test = 0;
    #20 w1_test = 0;w2_test = 0;
    #20 w1_test = 0;w2_test = 0;
    #20 w1_test = 1;w2_test = 1;

    #20 w1_test = 0;w2_test = 1;
    Resetn_test = 0;//测试复位信号
    #20 w1_test = 1;w2_test = 1;
    #20 w1_test = 1;w2_test = 1;
    #20 w1_test = 1;w2_test = 1;
    #20 w1_test = 1;w2_test = 1;
    #20 w1_test = 0;w2_test = 0;
    #20 w1_test = 1;w2_test = 1;
    #20 w1_test = 1;w2_test = 1;
    #20 w1_test = 0;w2_test = 0;
  end

  code6_9 UUT_code6_9 (
    .Clock(clk_test),
    .Resetn(Resetn_test),
    .w1(w1_test),
    .w2(w2_test),
    .z(z_test)
  );
endmodule
