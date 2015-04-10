`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2014/05/23 15:37:54
// Design Name: 
// Module Name: debounce
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module debounce(
    clk,
    i,
    o,
    input_limit,
    output_limit
    );
    
	output reg o;
	input i,clk;
    reg[32:0]c;
    reg[32:0]D;
    initial c = 32'b0;
    initial D = 32'd0;
    input [31:0]input_limit,output_limit;
    wire [31:0]upper_limit_input;  //for  debouncer output
    wire [31:0]upper_limit_output; //for the push button input
    assign upper_limit_input=input_limit;
    assign upper_limit_output=output_limit;
    
 always@(posedge clk)begin   
   if(i==1)
   begin
     if (o==1)
       begin
	   if(D==upper_limit_input)
       o <= 0;
       else
       o <= 1;
       D <= D+1;
	   end
	 else
	 begin
	 if(c==upper_limit_output)
      o <= 1;
     else
      o <= 0;
      c <= c+1;
	  end
   end 
   else begin
     c <= 32'b0;
     o <= 0;
	 D <=0;
    end
  end  
endmodule