HOLE IN THE WALL

DESCRIPTION

Nowadays, almost every gaming platform has some kind of video feedback that enhances the interaction with the game. Games franchises like Just Dance, miCoach and Wii Sports are becoming more attractive because they offer not only a different interface to play but also a new form of exercise at home. Developing a game using image processing on a FPGA is a relevant task since many of the current Kinect sensors perform part of the image processing on embedded systems. This pre-processing has the advantage of removing part of the processing from the main processor of the platform.
The main idea of this project is to re-create a Japanese game show called 'Nokabe', known in the West as 'Avoid the Wall' or 'Hole in the Wall'. In this game, a player must avoid a wall that comes towards him. The only way to do that is to fit on different shapes and sizes of holes on the wall. 
In order to reach this objective, a Nexys 4 DDR board is used. This board contains a Xilinx Artix-7 FPGA, which is connected to OV7670 camera module and a VGA monitor. 


HOW TO USE

Download and open the Vivado project. From the Vivado main window, launch SDK. Program the FPGA and then program the C code on Microblaze.
Use the switches to reset, start or change the level of the game.



Repository structure

HoleInTheWall: main Vivado project
	Vivado project:
	HoleInTheWall.v: top level design, instantiates block diagram and other sources.
	Hole_wrapper: HDL wrapper for block diagram.
	display.v: seven segment display controller.
	debounce.v: push button debouncer.
SDK project:
	prototype/src
	MicroblazeController.c: main program, contains game flow control.
	audioip.h:
	cameraConfig.h:
	config.h:
	create_wall.h:
	ImgProc_config.h:
	lscript.ld: C linker.
	platform.h:
	vdmaConfig:
	prototype_bsp: generated Board Support Package files.

Authors

GUSTAVO MAIA FERREIRA
HEYANG WANG
JOAO MARCUS RAMOS BACALHAU



