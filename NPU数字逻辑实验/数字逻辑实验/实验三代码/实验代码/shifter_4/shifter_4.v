module shifter_4(R,L,w,clk,Q);
input [3:0] R;
input L,w,clk;
output reg[3:0]Q;
integer k;

always@(posedge clk)
	if(L)
		Q <= R;
	else
		begin
			for(k = 0; k < 3; k = k + 1)
				Q[k] <=Q[k+1];
			Q[3] <= w;
		end

endmodule