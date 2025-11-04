module count_tb;
reg [3:0] R_test;
reg clk_test;
reg L_test;
reg En_test;
reg up_down_test;
reg rstn_test;
wire [3:0] Q_test;
initial
begin
R_test = 4'b0000;
clk_test = 0;
L_test = 1;
En_test = 1;
up_down_test =1;
rstn_test = 1;
#50
L_test = 0;
#200
rstn_test = 0;
#100
rstn_test = 1;
end

always #10 clk_test = ~clk_test;
count UUT_count_tb(.R(R_test),.clk(clk_test),.L(L_test),.En(En_test),.up_down(up_down_test),.rstn(rstn_test),.Q(Q_test));
endmodule