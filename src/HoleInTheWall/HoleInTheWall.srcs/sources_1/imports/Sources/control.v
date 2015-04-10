`timescale 1 ps / 1 ps
// FSM to use 8 segment display

module control(clk, reset, valid, end_i, count_i, count_j, state_out);

input clk, reset, valid, end_i;
output count_i, count_j;
output [1:0] state_out;

wire [1:0] state_out;

reg [1:0] state; //state of FSM

reg count_i, count_j;

parameter start=2'b00, display=2'b01, count=2'b10;

always @(state) 
     begin
          case (state)
               start:
							begin
							count_i = 0;
							count_j = 0;
							end
               display:
							begin
							count_i = 1;
							count_j = 0;
							end
               count:	
							begin
							count_i = 0;
							count_j = 1;
							end
               default:
							begin
							count_i = 0;
							count_j = 0;
							end
          endcase
     end

always @(posedge clk or posedge reset)
     begin
          if (reset)
               state = start;
          else
               case (state)
                    start:
								if (valid)
									begin
									state = display;
									end
								else
									begin
									state = start;
									end
                    display:
                         if (end_i)
                              state = count;
                         else
                              state = display;
                    count:
                         state = display;
               endcase
     end

assign state_out = state;
	  
endmodule