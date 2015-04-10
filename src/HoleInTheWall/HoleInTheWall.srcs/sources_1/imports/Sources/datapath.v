`timescale 1 ps / 1 ps
// FSM to use 8 segment display

module datapath(clk, reset, state, number, count_i, count_j, end_i, segments, digit);

parameter iN = 18; //number of bits of counter i
parameter jN = 3; //number of bits of counter j
parameter start=2'b00, display=2'b01, count=2'b10;

input clk, reset;
input count_i, count_j;
input [1:0] state;
input [4*2**jN-1:0] number;
output [7:0] segments;
output [2**jN-1:0] digit;
output end_i;

reg [iN-1:0] i; //counter for cycles displaying each digit
reg [jN-1:0] j; //counter for number of digits
reg end_i;
reg [2**jN-1:0] digit;
reg [7:0] segments;
reg [3:0] bits;

always @( posedge clk or posedge reset)
   begin
     if (reset)
       begin
         i <= 0;
       end 
     else
       begin   
			if (count_i)
				begin
				i <= i + 1;
				end
			else
				begin
				i <= 0;
				end
       end
		 end_i = &i;
   end
	
	always @( posedge clk or posedge reset)
   begin
     if (reset)
       begin
         j <= 0;
       end 
     else
       begin   
			if (count_j)
				begin
				j <= j + 1;
				end
			else
				begin
				j <= j;
				end
       end
   end
	  
always @(j, state)
	if (state==start)
		begin
		digit = 8'hFF;
		bits = 4'h0;
		end
	else
		begin
		case (j)
			 3'h0: 
			 begin
			 digit = 8'hFE;
			 bits = number [3:0];
			 end
			 3'h1: 
			 begin
			 digit = 8'hFD;
			 bits = number [7:4];
			 end
			 3'h2: 
			 begin
			 digit = 8'hFB;
			 bits = number [11:8];
			 end
			 3'h3: 
			 begin
			 digit = 8'hF7;
			 bits = number [15:12];
			 end
			 3'h4: 
			 begin
			 digit = 8'hEF;
			 bits = number [19:16];
			 end
			 3'h5: 
			 begin
			 digit = 8'hDF;
			 bits = number [23:20];
			 end
			 3'h6: 
			 begin
			 digit = 8'hBF;
			 bits = number [27:24];
			 end
			 3'h7: 
			 begin
			 digit = 8'h7F;
			 bits = number [31:28];
			 end
		endcase
	end
	
always @(bits)
	case (bits)
		 4'h0: segments = 8'hc0;
		 4'h1: segments = 8'hf9;
		 4'h2: segments = 8'ha4;
		 4'h3: segments = 8'hb0;
		 4'h4: segments = 8'h99;
		 4'h5: segments = 8'h92;
		 4'h6: segments = 8'h82;
		 4'h7: segments = 8'hf8;
		 4'h8: segments = 8'h80;
		 4'h9: segments = 8'h90;
		 4'ha: segments = 8'h88;
		 4'hb: segments = 8'h00;
		 4'hc: segments = 8'hc6;
		 4'hd: segments = 8'h40;
		 4'he: segments = 8'h86;
		 4'hf: segments = 8'h8e;
	endcase


endmodule