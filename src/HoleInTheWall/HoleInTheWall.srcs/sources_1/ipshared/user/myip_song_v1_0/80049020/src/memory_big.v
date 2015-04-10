module memory_big(
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
    input [31:0] w_data;
    output wire [31:0] r_data;
    reg [31:0] my_memory [0:255]; //255 32bit wide register   
    
    always@(posedge clk)begin
        if (w_enable==1) begin
            my_memory[w_addr] <= w_data;
        end
    end
    assign r_data = my_memory[r_addr];
    
endmodule