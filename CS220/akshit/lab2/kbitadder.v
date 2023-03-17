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

// module 2to1mux(
//   select, s0, s1

// );

// endmodule

module mjolnir #(parameter bits = 32) (
  a, b, carryin,
  sum, carryout
);
  // parameter bits = 32;
  input [bits-1:0] a, b;
  input carryin;
  output reg [bits-1:0] sum;
  output reg carryout;
  wire c, c0, c1;
  wire [bits/2-1:0] stemp0, stemp1, stemp;

  // last half sum done c0 carryput 
  fulladder #(bits/2) f0(a[bits/2-1:0], b[bits/2-1:0], carryin, stemp, c);

  // added with 0 and 1 carries
  fulladder #(bits/2) f1(a[bits-1:bits/2], b[bits-1:bits/2], 1'b0, stemp0, c0);

  fulladder #(bits/2) f2(a[bits-1:bits/2], b[bits-1:bits/2], 1'b1, stemp1, c1);
  
  always @* begin
    if (c0==1) begin
      sum = {stemp1, stemp};
      carryout = c1;
    end
    else begin
      sum = {stemp0, stemp};
      carryout = c0;
    end
  end
endmodule

module mjolnor_tb;
  parameter bits = 32;
  reg [bits-1:0]a, b;
  reg carryin;
  wire [bits-1:0]sum;
  wire carryout;

  mjolnir #(bits) uut(a, b, carryin, sum , carryout);

  initial begin
    $dumpfile("dump.vcd");
    $dumpvars(0, mjolnor_tb);

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