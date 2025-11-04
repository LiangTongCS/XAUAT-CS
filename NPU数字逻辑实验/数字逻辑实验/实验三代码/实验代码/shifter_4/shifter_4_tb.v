`timescale 1ns/1ps
module shifter_4_tb;
reg [3:0]R_test;
reg L_test;
reg w_test;
reg clk_test;
wire [3:0]Q_test;

initial 
begin
R_test = 4'b0;
L_test = 0;
w_test = 0;
clk_test = 0;

#10
L_test = 1;
R_test=4'b0011;

#20
L_test = 0;

#100
L_test = 1;
R_test=4'b1111;
#20
L_test = 0;

#100
L_test = 1;
R_test = 4'b0101;
#20
L_test = 0;
end

always#10 clk_test = ~clk_test ;

shifter_4 UUT_shifter_4_tb(.R(R_test),.L(L_test),.w(w_test),.clk(clk_test),.Q(Q_test));

endmodule
