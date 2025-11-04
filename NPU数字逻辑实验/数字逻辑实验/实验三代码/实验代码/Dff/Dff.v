module Dff(
input D,
input clk,
input rstn,  
input En,
output reg Q
);

always@(posedge clk , negedge rstn)
	if(!rstn)
		Q <= 0;
	else if(En)
		Q <= D;
endmodule