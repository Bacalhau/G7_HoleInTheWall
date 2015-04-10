/**
*----------- VDMA CONFIGURATION  --------------
*REGISTERS TO WRITE
*1) vdma[12]: VDMA control register.
*2) vdma[43]: initial memory address to write to.
*3) vdma[42]: number of bytes per line in memory.
*4) vdma[41]: number of pixels per line in memory, defined in bytes.
*5) vdma[40]: number of lines in memory.
*
*SUGESTION OF USE
*Run programming in the same sequence as default. VDMA will be active only after vdma[40] is written.
*vdma[43] is the register that will be changed during frame sync.
**/

volatile unsigned int * vdma = (unsigned int*) XPAR_AXI_VDMA_0_BASEADDR;

void config_vdma()
{	
	//DEFAULT VDMA CONFIGURATION
	vdma[12] = 0x0000000B; // also try 0x1. If it works, use this.
	vdma[43] = 0x80800000;
	vdma[42] = 4*1024;
	vdma[41] = 4*640;
	vdma[40] = 512;
}
