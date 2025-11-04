module Timer(Reset,CLK,E,Q,Sign);
	input Reset,CLK,E;
	output reg [24:0]Q=25'b000000000000000;
	output reg Sign;

	always@(posedge Reset,posedge CLK)
		if(Reset)
			Q<=0;
		else if(E)
			begin
				if(Q<20000000)
					begin
					Q<=Q+1;
					Sign=0;
					end
				else if(Q>=20000000)
					begin
					Sign=1;
					Q<=0;
					end
			end
endmodule