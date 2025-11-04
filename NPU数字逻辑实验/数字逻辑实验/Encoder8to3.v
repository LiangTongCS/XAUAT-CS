module Encoder8to3(input [7:0] data_in,output reg [2:0] code_out );

  always_comb begin
    case (data_in)
      8'b00000001: code_out = 3'b000;
      8'b00000010: code_out = 3'b001;
      8'b00000100: code_out = 3'b010;
      8'b00001000: code_out = 3'b011;
      8'b00010000: code_out = 3'b100;
      8'b00100000: code_out = 3'b101;
      8'b01000000: code_out = 3'b110;
      8'b10000000: code_out = 3'b111;
      default: code_out = 3'b000; // 默认情况，全为零
    endcase
  end

endmodule
