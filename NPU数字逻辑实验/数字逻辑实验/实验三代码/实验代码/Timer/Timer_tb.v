`timescale 1ns/1ps
module Timer_tb;
reg Reset_test;
reg CLK_test;
reg E_test;
wire [24:0]Q_test;
wire Sign_test;

initial
CLK_test=0;

always #25 CLK_test=~CLK_test;

initial
begin
Reset_test=1;
E_test=0;

#1
Reset_test=0;
E_test=1;

end

Timer UUT_Timer_tb(.Reset(Reset_test),.CLK(CLK_test),.E(E_test),.Q(Q_test),.Sign(Sign_test));

endmodule