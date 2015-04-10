`timescale 1ns / 1ps

module memory_I2C(
        clk,
        r_addr,
        r_data,
        w_enable,
        w_addr,
        w_data
    );
    input clk;
    input w_enable;
    input [7:0] w_addr;
    input [7:0] r_addr;
    input [15:0] w_data;
    output wire [15:0] r_data;
    reg [15:0] my_memory [0:255];
    
    always@(posedge clk)begin
        if (w_enable==1) begin
            my_memory[w_addr] <= w_data;
        end
    end
    assign r_data = my_memory[r_addr];
    
endmodule
