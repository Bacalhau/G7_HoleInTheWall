`timescale 1ns / 1ps

module HoleInTheWall
   (DDR2_addr,
    DDR2_ba,
    DDR2_cas_n,
    DDR2_ck_n,
    DDR2_ck_p,
    DDR2_cke,
    DDR2_cs_n,
    DDR2_dm,
    DDR2_dq,
    DDR2_dqs_n,
    DDR2_dqs_p,
    DDR2_odt,
    DDR2_ras_n,
    DDR2_we_n,
    USB_Uart_rxd,
    USB_Uart_txd,
    ampPWM,
    ampSD,
    OV7670_VSYNC,
    OV7670_HREF,
    OV7670_PCLK,
    OV7670_SIOC,
    OV7670_SIOD,
    OV7670_XCLK,
    OV7670_D,
    resetI2C,
    reseth,
    sys_clock,
    tft_hsync,
    tft_vga_b,
    tft_vga_g,
    tft_vga_r,
    tft_vsync,
    LED,
    seg,
    dig,
    pwdn,
    BTNC,
    BTNU,
    BTND,
    BTNR,
    BTNL);
  output [12:0]DDR2_addr;
  output [2:0]DDR2_ba;
  output DDR2_cas_n;
  output [0:0]DDR2_ck_n;
  output [0:0]DDR2_ck_p;
  output [0:0]DDR2_cke;
  output [0:0]DDR2_cs_n;
  output [1:0]DDR2_dm;
  inout [15:0]DDR2_dq;
  inout [1:0]DDR2_dqs_n;
  inout [1:0]DDR2_dqs_p;
  output [0:0]DDR2_odt;
  output DDR2_ras_n;
  output DDR2_we_n;
  input USB_Uart_rxd;
  output USB_Uart_txd;
  output ampPWM;
  output ampSD;
  input reseth;
  input sys_clock;
  output tft_hsync;
  output [3:0]tft_vga_b;
  output [3:0]tft_vga_g;
  output [3:0]tft_vga_r;
  output tft_vsync;
  input OV7670_VSYNC;
  input OV7670_HREF;
  input OV7670_PCLK;
  output OV7670_SIOC;
  inout OV7670_SIOD;
  output OV7670_XCLK;
  input [7:0] OV7670_D;
  output resetI2C;
  output pwdn;
  output [3:0] LED;
  output [7:0] seg;
  output [7:0] dig;
  input BTNU, BTND, BTNL, BTNR, BTNC;

  wire Config_Done;
  wire [12:0]DDR2_addr;
  wire [2:0]DDR2_ba;
  wire DDR2_cas_n;
  wire [0:0]DDR2_ck_n;
  wire [0:0]DDR2_ck_p;
  wire [0:0]DDR2_cke;
  wire [0:0]DDR2_cs_n;
  wire [1:0]DDR2_dm;
  wire [15:0]DDR2_dq;
  wire [1:0]DDR2_dqs_n;
  wire [1:0]DDR2_dqs_p;
  wire [0:0]DDR2_odt;
  wire DDR2_ras_n;
  wire DDR2_we_n;
  wire USB_Uart_rxd;
  wire USB_Uart_txd;
  wire ampPWM;
  wire ampSD;
  wire clk100;
  wire clk25;
  wire [31:0]number;
  wire [4:0]push_button;
  wire resend;
  wire reseth;
  wire reset;
  wire sys_clock;
  wire tft_hsync;
  wire [3:0]tft_vga_b;
  wire [3:0]tft_vga_g;
  wire [3:0]tft_vga_r;
  wire tft_vsync;
  wire [5:0]tft_vga_b_aux;
  wire [5:0]tft_vga_g_aux;
  wire [5:0]tft_vga_r_aux;
  wire [4:0]push_button;
  wire BTNU, BTND, BTNL, BTNR, BTNC;
  wire [3:0] LED;
  wire [7:0] seg;
  wire [7:0] dig;
  
  assign LED = {3'b0,Config_Done};
  assign resetI2C = 1;
  assign pwdn = 0;
  assign OV7670_XCLK = clk25;
  assign reset = !reseth; 
  
debounce   btn_debounceU(
      .clk(clk100),
      .i(BTNU),
      .o(push_button[4]),
      .input_limit(32'h4fffff),
      .output_limit(32'hff)
);

debounce   btn_debounceD(
      .clk(clk100),
      .i(BTND),
      .o(push_button[3]),
      .input_limit(32'h4fffff),
      .output_limit(32'hff)
);

debounce   btn_debounceL(
      .clk(clk100),
      .i(BTNL),
      .o(push_button[2]),
      .input_limit(32'h4fffff),
      .output_limit(32'hff)
);

debounce   btn_debounceR(
      .clk(clk100),
      .i(BTNR),
      .o(push_button[1]),
      .input_limit(32'h4fffff),
      .output_limit(32'hff)
);

debounce   btn_debounceC(
      .clk(clk100),
      .i(BTNC),
      .o(push_button[0]),
      .input_limit(32'h4fffff),
      .output_limit(32'hff)
);

assign resend = push_button[1];

Hole_wrapper Hole_wrapper_i
       (.Config_Done(Config_Done),
        .DDR2_addr(DDR2_addr),
        .DDR2_ba(DDR2_ba),
        .DDR2_cas_n(DDR2_cas_n),
        .DDR2_ck_n(DDR2_ck_n),
        .DDR2_ck_p(DDR2_ck_p),
        .DDR2_cke(DDR2_cke),
        .DDR2_cs_n(DDR2_cs_n),
        .DDR2_dm(DDR2_dm),
        .DDR2_dq(DDR2_dq),
        .DDR2_dqs_n(DDR2_dqs_n),
        .DDR2_dqs_p(DDR2_dqs_p),
        .DDR2_odt(DDR2_odt),
        .DDR2_ras_n(DDR2_ras_n),
        .DDR2_we_n(DDR2_we_n),
        .I2C_SCLK(OV7670_SIOC),
        .I2C_SDAT(OV7670_SIOD),
        .USB_Uart_rxd(USB_Uart_rxd),
        .USB_Uart_txd(USB_Uart_txd),
        .ampPWM(ampPWM),
        .ampSD(ampSD),
        .clk100(clk100),
        .clk25(clk25),
        .d({OV7670_D}),
        .display(number),
        .enable(1),
        .href(OV7670_HREF),
        .pclk(OV7670_PCLK),
        .push_button(push_button),
        .resend(resend),
        .reset(reset),
        .rst(0),
        .sys_clock(sys_clock),
        .tft_hsync(tft_hsync),
        .tft_vga_b(tft_vga_b_aux),
        .tft_vga_g(tft_vga_g_aux),
        .tft_vga_r(tft_vga_r_aux),
        .tft_vsync(tft_vsync),
        .vsync(OV7670_VSYNC));
        
display display(
        .clk(clk100),
        .reset(0),
        .valid(1),
        .number(number),
        .segments(seg),
        .digit(dig)
        );
        
assign tft_vga_b = tft_vga_b_aux[5:2];
assign tft_vga_g = tft_vga_g_aux[5:2];
assign tft_vga_r = tft_vga_r_aux[5:2];
        
endmodule
