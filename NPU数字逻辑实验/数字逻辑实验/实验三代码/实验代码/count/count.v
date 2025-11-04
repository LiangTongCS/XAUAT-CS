module count(
	input [3:0] R,
	input clk,
	input L,
	input En,
	input up_down,
	input rstn,
	output reg [3:0]Q
);

always@(posedge clk)
	if(!rstn)
		Q <= 0;
	else if(L)
		Q <= R;
	else if(En)
		Q <= Q + (up_down ? 1 : -1);
endmodule