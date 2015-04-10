`timescale 1ns / 1ps

module memory_pixel(
        clk,
        r_addr,
        r_data,
        r_addr2,
        r_data2,
        r_addr3,
        r_data3,
        w_enable,
        w_addr,
        w_data
    );
    input clk;
    input w_enable;
    input [7:0] w_addr;
    input [7:0] r_addr;
    input [7:0] r_addr2;
    input [7:0] r_addr3;
    input [3:0] w_data;
    output wire [3:0] r_data;
    output wire [3:0] r_data2;
    output wire [3:0] r_data3;
    reg [3:0] my_memory [0:255];
    
    always@(posedge clk)begin
        if (w_enable==1) begin
            my_memory[w_addr] <= w_data;
        end
    end
    assign r_data = my_memory[r_addr];
    assign r_data2 = my_memory[r_addr2];
    assign r_data3 = my_memory[r_addr3];
    
endmodule
