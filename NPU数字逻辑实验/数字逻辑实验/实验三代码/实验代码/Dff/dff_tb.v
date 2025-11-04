`timescale 1ns/1ps
module dff_tb;
reg D_test;
reg clk_test;
reg rstn_test;
reg En_test;
wire Q_test;


initial 
begin
D_test = 0;
clk_test = 0;
rstn_test = 0;
En_test = 0;
end

always#10 clk_test = ~clk_test;
always#7 D_test = ~D_test;
always#50 rstn_test = ~rstn_test;
always#100 En_test = ~En_test;

dff UUT_dff_tb(.D(D_test),.clk(clk_test),.rstn(rstn_test),.En(En_test),.Q(Q_test));

endmodule