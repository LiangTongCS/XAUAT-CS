`timescale 1ns/1ps 
module shared_tb;
reg a_test;
reg b_test;
reg c_test;
reg d_test;
reg m_test;
wire s1_test;
wire s0_test;

initial
m_test=0;

always #160 m_test=~m_test;

initial
begin
a_test=0;
b_test=0;
c_test=0;
d_test=0;

#10
a_test=0;
b_test=0;
c_test=0;
d_test=1;

#10
a_test=0;
b_test=0;
c_test=1;
d_test=0;

#10
a_test=0;
b_test=0;
c_test=1;
d_test=1;

#10
a_test=0;
b_test=1;
c_test=0;
d_test=0;

#10
a_test=0;
b_test=1;
c_test=0;
d_test=1;

#10
a_test=0;
b_test=1;
c_test=1;
d_test=0;

#10
a_test=0;
b_test=1;
c_test=1;
d_test=1;

#10
a_test=1;
b_test=0;
c_test=0;
d_test=0;

#10
a_test=1;
b_test=0;
c_test=0;
d_test=1;

#10
a_test=1;
b_test=0;
c_test=1;
d_test=0;

#10
a_test=1;
b_test=0;
c_test=1;
d_test=1;

#10
a_test=1;
b_test=1;
c_test=0;
d_test=0;

#10
a_test=1;
b_test=1;
c_test=0;
d_test=1;

#10
a_test=1;
b_test=1;
c_test=1;
d_test=0;

#10
a_test=1;
b_test=1;
c_test=1;
d_test=1;

#10
a_test=0;
b_test=0;
c_test=0;
d_test=0;

#10
a_test=0;
b_test=0;
c_test=0;
d_test=1;

#10
a_test=0;
b_test=0;
c_test=1;
d_test=0;

#10
a_test=0;
b_test=0;
c_test=1;
d_test=1;

#10
a_test=0;
b_test=1;
c_test=0;
d_test=0;

#10
a_test=0;
b_test=1;
c_test=0;
d_test=1;

#10
a_test=0;
b_test=1;
c_test=1;
d_test=0;

#10
a_test=0;
b_test=1;
c_test=1;
d_test=1;

#10
a_test=1;
b_test=0;
c_test=0;
d_test=0;

#10
a_test=1;
b_test=0;
c_test=0;
d_test=1;

#10
a_test=1;
b_test=0;
c_test=1;
d_test=0;

#10
a_test=1;
b_test=0;
c_test=1;
d_test=1;

#10
a_test=1;
b_test=1;
c_test=0;
d_test=0;

#10
a_test=1;
b_test=1;
c_test=0;
d_test=1;

#10
a_test=1;
b_test=1;
c_test=1;
d_test=0;

#10
a_test=1;
b_test=1;
c_test=1;
d_test=1;


end

shared UUT_shared_tb(.a(a_test),.b(b_test),.c(c_test),.d(d_test),.m(m_test),.s1(s1_test),.s0(s0_test));

endmodule
