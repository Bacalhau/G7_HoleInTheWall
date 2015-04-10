//Copyright 1986-2014 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2014.1 (win64) Build 881834 Fri Apr  4 14:15:54 MDT 2014
//Date        : Mon Mar 23 22:26:05 2015
//Host        : Gustavo running 64-bit major release  (build 9200)
//Command     : generate_target Hole_wrapper.bd
//Design      : Hole_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module Hole_wrapper
   (Config_Done,
    DDR2_addr,
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
    I2C_SCLK,
    I2C_SDAT,
    USB_Uart_rxd,
    USB_Uart_txd,
    ampPWM,
    ampSD,
    clk100,
    clk25,
    d,
    display,
    enable,
    href,
    pclk,
    push_button,
    resend,
    reset,
    rst,
    sys_clock,
    tft_hsync,
    tft_vga_b,
    tft_vga_g,
    tft_vga_r,
    tft_vsync,
    vsync);
  output Config_Done;
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
  output I2C_SCLK;
  inout I2C_SDAT;
  input USB_Uart_rxd;
  output USB_Uart_txd;
  output ampPWM;
  output ampSD;
  output clk100;
  output clk25;
  input [7:0]d;
  output [31:0]display;
  input enable;
  input href;
  input pclk;
  input [4:0]push_button;
  input resend;
  input reset;
  input rst;
  input sys_clock;
  output tft_hsync;
  output [5:0]tft_vga_b;
  output [5:0]tft_vga_g;
  output [5:0]tft_vga_r;
  output tft_vsync;
  input vsync;

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
  wire I2C_SCLK;
  wire I2C_SDAT;
  wire USB_Uart_rxd;
  wire USB_Uart_txd;
  wire ampPWM;
  wire ampSD;
  wire clk100;
  wire clk25;
  wire [7:0]d;
  wire [31:0]display;
  wire enable;
  wire href;
  wire pclk;
  wire [4:0]push_button;
  wire resend;
  wire reset;
  wire rst;
  wire sys_clock;
  wire tft_hsync;
  wire [5:0]tft_vga_b;
  wire [5:0]tft_vga_g;
  wire [5:0]tft_vga_r;
  wire tft_vsync;
  wire vsync;

Hole Hole_i
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
        .I2C_SCLK(I2C_SCLK),
        .I2C_SDAT(I2C_SDAT),
        .USB_Uart_rxd(USB_Uart_rxd),
        .USB_Uart_txd(USB_Uart_txd),
        .ampPWM(ampPWM),
        .ampSD(ampSD),
        .clk100(clk100),
        .clk25(clk25),
        .d(d),
        .display(display),
        .enable(enable),
        .href(href),
        .pclk(pclk),
        .push_button(push_button),
        .resend(resend),
        .reset(reset),
        .rst(rst),
        .sys_clock(sys_clock),
        .tft_hsync(tft_hsync),
        .tft_vga_b(tft_vga_b),
        .tft_vga_g(tft_vga_g),
        .tft_vga_r(tft_vga_r),
        .tft_vsync(tft_vsync),
        .vsync(vsync));
endmodule
