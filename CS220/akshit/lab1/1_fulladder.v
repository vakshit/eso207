module onebitfulladder(
  a, b, carryin,
  sum, carryout
);
input a, b, carryin;
output sum, carryout;

xor(sum, a, b, carryin);
xor (t1, a,b);
and (t2, a,b);
and (t3, t1, carryin);
or (carryout, t2, t3);

endmodule

module onebitfulladder_tb;
  reg a, b, carryin;

  wire carryout, sum;
  onebitfulladder uut(a, b, carryin, sum, carryout);

  initial begin 
    // $dumpfile("dump.vcd");
    // $dumpvars(0, onebitfulladder_tb);

    a <= 0;
    b <= 0;
    carryin <= 0;
    #10;

    a <= 0;
    b <= 1;
    carryin <= 0;
    #10;

    a <= 1;
    b <= 0;
    carryin <= 0;
    #10;

    a <= 1;
    b <= 1;
    carryin <= 0;
    #10;

    a <= 0;
    b <= 0;
    carryin <= 1;
    #10;

    a <= 0;
    b <= 1;
    carryin <= 1;
    #10;

    a <= 1;
    b <= 0;
    carryin <= 1;
    #10;

    a <= 1;
    b <= 1;
    carryin <= 1;
    #10;

    $display("Test complete");
  end
endmodule

module fulladder(
  a, b, carryin,
  sum, carryout
);
  parameter bits = 32;
  input [bits-1:0] a, b;
  input carryin;
  output [bits-1:0] sum;
  output carryout;

  wire [bits:0] carry;
  genvar i;
  assign carry[0] = carryin;

  generate
    for (i=0;i<bits;i= i+1) begin
      onebitfulladder f(a[i], b[i], carry[i], sum[i], carry[i+1]);
    end
    assign carryout = carry[bits];
  endgenerate

endmodule

module fulladder_tb;
  reg [31:0] a, b;
  reg carryin;
  wire [31:0] sum;
  wire carryout;

  fulladder uut(a, b, carryin, sum, carryout);

  initial begin

    $dumpfile("dump.vcd");
    $dumpvars(0, fulladder_tb);

    a = 32'd20;
    b = 32'd40;
    carryin = 1;
    #10

    a = 2;
    b = 4;
    carryin = 1;
    #10

    a = 10;
    b = 10;
    carryin = 1;
    #10

    a = 1000000;
    b = 1000000;
    carryin = 0;
    #10;
  end

endmodule