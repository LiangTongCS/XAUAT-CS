module code6_9(Clock, Resetn, w1, w2, z);

  input Clock, Resetn, w1, w2;
  output reg z;
  reg [2:1] y, Y;
  wire s;
  // 状态定义
  parameter [2:1] A = 2'b00, B = 2'b01, C = 2'b10, D = 2'b11;

  // 定义下一个状态和输出的组合电路
  assign s = w1 ^ w2;

  // 状态迁移逻辑
  always @(s, y)
    case (y)
      // 状态A
      A: if (s) begin
           Y = A; // 下一个状态为A
           z = 0; // 输出z为0
         end
         else begin
           Y = B; // 下一个状态为B
           z = 0; // 输出z为0
         end
      // 状态B
      B: if (s) begin
           Y = A; // 下一个状态为A
           z = 0; // 输出z为0
         end
         else begin
           Y = C; // 下一个状态为C
           z = 0; // 输出z为0
         end
      // 状态C
      C: if (s) begin
           Y = A; // 下一个状态为A
           z = 0; // 输出z为0
         end
         else begin
           Y = D; // 下一个状态为D
           z = 0; // 输出z为0
         end
      // 状态D
      D: if (s) begin
           Y = A; // 下一个状态为A
           z = 0; // 输出z为0
         end
         else begin
           Y = D; // 下一个状态为D
           z = 1; // 输出z为1
         end
    endcase

  // 定义时序块
  always @(negedge Resetn or posedge Clock)
    if (Resetn == 0)
      y <= A; // 复位时将状态置为A
    else
      y <= Y; // 根据组合逻辑计算得到的下一个状态更新y
endmodule
