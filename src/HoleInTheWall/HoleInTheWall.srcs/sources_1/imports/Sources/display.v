`timescale 1 ps / 1 ps
// FSM to use 8 segment display

module display(clk, reset, valid, number, segments, digit);

parameter iN = 18; //number of bits of counter i
parameter jN = 3; //number of bits of counter j

input clk, reset, valid;
input [4*2**jN-1:0] number;
output [7:0] segments;
output [2**jN-1:0] digit;

wire [2**jN-1:0] digit;
wire [7:0] segments;

wire [1:0] state; //state of FSM
wire end_i, count_i, count_j;


control CONTROL(clk, reset, valid, end_i, count_i, count_j, state);
datapath DATAPATH(clk, reset, state, number, count_i, count_j, end_i, segments, digit);

endmodule