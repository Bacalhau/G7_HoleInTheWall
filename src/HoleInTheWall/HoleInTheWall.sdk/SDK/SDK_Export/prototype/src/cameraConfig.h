/**
*----------- CAMERA OV7670 CONFIGURATION  --------------
*REGISTERS TO WRITE
*
*1) mem[0]: add a new configuration command to block memory
*Bits
*|31------------24|23------------16|15------------8|7------------0|
*|    not used    |memory position |camera register|register value|
*Check default values and camera datasheet before changing anything.
*
*
*2) mem[1]: enable/reset active high
*This block has 3 resets: AXI reset, MicroBlaze reset and Push-Button reset. This is the MicroBlaze reset, which can be used as enable.
*
*|31-------------1|   0   |
*|    not used    |resetMB|
*Run camera configuration.
*Every time some register is written, this register is checked. If valid, camera configuration is run.
*
*How to use it:
*a) Initial camera configuration or changing more than one configuration: set 0 before writing anything. Pulse to 1. Not required, but recommended pulse back to 0.
*b) Change only one configuration: if bit is 1 from before, just write the camera configuration. If not, pulse from 0 to 1 as before.
*
*
*SUGESTION OF USE
*
*Call config_OV7670() at the beginning of main.
*Default configuration is enough for VGA RGB444.
*Configuration is run sequentially. Thus, writing at an upper address will overwrite a lower address for the same camera register.
*
*/

volatile unsigned int * mem = (unsigned int*) XPAR_I2C_CONFIG_0_S00_AXI_BASEADDR; // not a good name


//DEFAULT CAMERA CONFIGURATION
void config_OV7670() {
	
	mem[1] = 0;
	
	mem[0] = 0x000000;
	mem[0] = 0x010000;
	mem[0] = 0x023a04;
	mem[0] = 0x033dc8;
	mem[0] = 0x041e31;
	mem[0] = 0x056b00;
	mem[0] = 0x0632b6;
	mem[0] = 0x071713;
	mem[0] = 0x081801;
	mem[0] = 0x091902;
	mem[0] = 0x0A1a7a;
	mem[0] = 0x0B030a;
	mem[0] = 0x0C0c00;
	mem[0] = 0x0D3e00;
	mem[0] = 0x0E7000;
	mem[0] = 0x0F7100;
	mem[0] = 0x107211;
	mem[0] = 0x117300;
	mem[0] = 0x12a202;
	mem[0] = 0x131180;
	mem[0] = 0x147a20;
	mem[0] = 0x157b1c;
	mem[0] = 0x167c28;
	mem[0] = 0x177d3c;
	mem[0] = 0x187e55;
	mem[0] = 0x197f68;
	mem[0] = 0x1A8076;
	mem[0] = 0x1B8180;
	mem[0] = 0x1C8288;
	mem[0] = 0x1D838f;
	mem[0] = 0x1E8496;
	mem[0] = 0x1F85a3;
	mem[0] = 0x2086af;
	mem[0] = 0x2187c4;
	mem[0] = 0x2288d7;
	mem[0] = 0x2389e8;
	mem[0] = 0x2413e0;
	mem[0] = 0x250000;
	mem[0] = 0x261000;
	mem[0] = 0x270d00;
	mem[0] = 0x281428;
	mem[0] = 0x29a505;
	mem[0] = 0x2Aab07;
	mem[0] = 0x2B2475;
	mem[0] = 0x2C2563;
	mem[0] = 0x2D26a5;
	mem[0] = 0x2E9f78;
	mem[0] = 0x2Fa068;
	mem[0] = 0x30a103;
	mem[0] = 0x31a6df;
	mem[0] = 0x32a7df;
	mem[0] = 0x33a8f0;
	mem[0] = 0x34a990;
	mem[0] = 0x35aa94;
	mem[0] = 0x3613ef;
	mem[0] = 0x370e61;
	mem[0] = 0x380f4b;
	mem[0] = 0x391602;
	mem[0] = 0x3A2102;
	mem[0] = 0x3B2291;
	mem[0] = 0x3C2907;
	mem[0] = 0x3D330b;
	mem[0] = 0x3E350b;
	mem[0] = 0x3F371d;
	mem[0] = 0x403871;
	mem[0] = 0x41392a;
	mem[0] = 0x423c78;
	mem[0] = 0x434d40;
	mem[0] = 0x444e20;
	mem[0] = 0x456900;
	mem[0] = 0x467419;
	mem[0] = 0x478d4f;
	mem[0] = 0x488e00;
	mem[0] = 0x498f00;
	mem[0] = 0x4A9000;
	mem[0] = 0x4B9100;
	mem[0] = 0x4C9200;
	mem[0] = 0x4D9600;
	mem[0] = 0x4E9a80;
	mem[0] = 0x4Fb084;
	mem[0] = 0x50b10c;
	mem[0] = 0x51b20e;
	mem[0] = 0x52b382;
	mem[0] = 0x53b80a;
	mem[0] = 0x544314;
	mem[0] = 0x5544f0;
	mem[0] = 0x564534;
	mem[0] = 0x574658;
	mem[0] = 0x584728;
	mem[0] = 0x59483a;
	mem[0] = 0x5A5988;
	mem[0] = 0x5B5a88;
	mem[0] = 0x5C5b44;
	mem[0] = 0x5D5c67;
	mem[0] = 0x5E5d49;
	mem[0] = 0x5F5e0e;
	mem[0] = 0x606404;
	mem[0] = 0x616520;
	mem[0] = 0x626605;
	mem[0] = 0x639404;
	mem[0] = 0x649508;
	mem[0] = 0x659508;
	mem[0] = 0x666d55;
	mem[0] = 0x676e11;
	mem[0] = 0x686f9f;
	mem[0] = 0x696a40;
	mem[0] = 0x6A0140;
	mem[0] = 0x6B0240;
	mem[0] = 0x6C13e7;
	mem[0] = 0x6D1500;
	mem[0] = 0x6E4f80;
	mem[0] = 0x6F5080;
	mem[0] = 0x705100;
	mem[0] = 0x715222;
	mem[0] = 0x72535e;
	mem[0] = 0x735480;
	mem[0] = 0x74589e;
	mem[0] = 0x754108;
	mem[0] = 0x763f00;
	mem[0] = 0x777505;
	mem[0] = 0x7876e1;
	mem[0] = 0x794c00;
	mem[0] = 0x7A7701;
	mem[0] = 0x7B4b09;
	mem[0] = 0x7Cc9F0;
	mem[0] = 0x7D4138;
	mem[0] = 0x7E5640;
	mem[0] = 0x7F3411;
	mem[0] = 0x803b02;
	mem[0] = 0x81a489;
	mem[0] = 0x829600;
	mem[0] = 0x839730;
	mem[0] = 0x849820;
	mem[0] = 0x859930;
	mem[0] = 0x869a84;
	mem[0] = 0x879b29;
	mem[0] = 0x889c03;
	mem[0] = 0x899d4c;
	mem[0] = 0x8A9e3f;
	mem[0] = 0x8B7804;
	mem[0] = 0x8C7901;
	mem[0] = 0x8Dc8f0;
	mem[0] = 0x8E790f;
	mem[0] = 0x8Fc800;
	mem[0] = 0x907910;
	mem[0] = 0x91c87e;
	mem[0] = 0x92790a;
	mem[0] = 0x93c880;
	mem[0] = 0x94790b;
	mem[0] = 0x95c801;
	mem[0] = 0x96790c;
	mem[0] = 0x97c80f;
	mem[0] = 0x98790d;
	mem[0] = 0x99c820;
	mem[0] = 0x9A7909;
	mem[0] = 0x9Bc880;
	mem[0] = 0x9C7902;
	mem[0] = 0x9Dc8c0;
	mem[0] = 0x9E7903;
	mem[0] = 0x9Fc840;
	mem[0] = 0xA07905;
	mem[0] = 0xA1c830;
	mem[0] = 0xA27926;
	mem[0] = 0xA30903;
	mem[0] = 0xA43b42;
	mem[0] = 0xA58c02;
	mem[0] = 0xA640d0;
	mem[0] = 0xA71204;

	mem[0] = 0xA81e11; // mirror
	mem[0] = 0xA90000;
	mem[0] = 0xAA0000;
	mem[0] = 0xAB0000;
	mem[0] = 0xAC0000;
	mem[0] = 0xAD0000;
	mem[0] = 0xAE0000;
	mem[0] = 0xAF0000;
	mem[0] = 0xB00000;
	mem[0] = 0xB10000;
	mem[0] = 0xB20000;
	mem[0] = 0xB30000;
	mem[0] = 0xB40000;
	mem[0] = 0xB50000;
	mem[0] = 0xB60000;
	mem[0] = 0xB70000;
	mem[0] = 0xB80000;
	mem[0] = 0xB90000;
	mem[0] = 0xBA0000;
	mem[0] = 0xBB0000;
	mem[0] = 0xBC0000;
	mem[0] = 0xBD0000;
	mem[0] = 0xBE0000;
	mem[0] = 0xBF0000;
	mem[0] = 0xC00000;
	mem[0] = 0xC10000;
	mem[0] = 0xC20000;
	mem[0] = 0xC30000;
	mem[0] = 0xC40000;
	mem[0] = 0xC50000;
	mem[0] = 0xC60000;
	mem[0] = 0xC70000;
	mem[0] = 0xC80000;
	mem[0] = 0xC90000;
	mem[0] = 0xCA0000;
	mem[0] = 0xCB0000;
	mem[0] = 0xCC0000;
	mem[0] = 0xCD0000;
	mem[0] = 0xCE0000;
	mem[0] = 0xCF0000;
	mem[0] = 0xD00000;
	mem[0] = 0xD10000;
	mem[0] = 0xD20000;
	mem[0] = 0xD30000;
	mem[0] = 0xD40000;
	mem[0] = 0xD50000;
	mem[0] = 0xD60000;
	mem[0] = 0xD70000;
	mem[0] = 0xD80000;
	mem[0] = 0xD90000;
	mem[0] = 0xDA0000;
	mem[0] = 0xDB0000;
	mem[0] = 0xDC0000;
	mem[0] = 0xDD0000;
	mem[0] = 0xDE0000;
	mem[0] = 0xDF0000;
	mem[0] = 0xE00000;
	mem[0] = 0xE10000;
	mem[0] = 0xE20000;
	mem[0] = 0xE30000;
	mem[0] = 0xE40000;
	mem[0] = 0xE50000;
	mem[0] = 0xE60000;
	mem[0] = 0xE70000;
	mem[0] = 0xE80000;
	mem[0] = 0xE90000;
	mem[0] = 0xEA0000;
	mem[0] = 0xEB0000;
	mem[0] = 0xEC0000;
	mem[0] = 0xED0000;
	mem[0] = 0xEE0000;
	mem[0] = 0xEF0000;
	mem[0] = 0xF00000;
	mem[0] = 0xF10000;
	mem[0] = 0xF20000;
	mem[0] = 0xF30000;
	mem[0] = 0xF40000;
	mem[0] = 0xF50000;
	mem[0] = 0xF60000;
	mem[0] = 0xF70000;
	mem[0] = 0xF80000;
	mem[0] = 0xF90000;
	mem[0] = 0xFA0000;
	mem[0] = 0xFB0000;
	mem[0] = 0xFC0000;
	mem[0] = 0xFD0000;
	mem[0] = 0xFE0000;
	mem[0] = 0xFF0000;

	mem[1] = 1;
	mem[1] = 0;
	//PRINT("Finished camera configuration\n");

}
