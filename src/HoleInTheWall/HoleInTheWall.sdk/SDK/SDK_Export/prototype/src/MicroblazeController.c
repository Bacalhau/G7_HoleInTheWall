/***************************** Include Files ************************/
#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xtmrctr.h"
#include "xintc.h"
#include "xgpio.h"

#include "xil_exception.h"
#include "create_wall.h"//Library that deals with the  Wall and different screens.
#include "audioip.h"//Library for the audio output
#include "cameraConfig.h"//Library for the Camera
#include "vdmaConfig.h"//Library for the Camera
#include "ImgProc_config.h"//Library for the Camera



/********************* Define *************************/
//PRINT
#define PRINT xil_printf
//TIMER
#define TMRCTR_DEVICE_IDXPAR_TMRCTR_0_DEVICE_ID
#define INTC_DEVICE_IDXPAR_INTC_0_DEVICE_ID
#define TMRCTR_INTERRUPT_IDXPAR_INTC_0_TMRCTR_0_VEC_ID
#define TIMER_CNTR_0 0
#define RESET_VALUE 0xFF67697F //100ms

/********************* Function Prototypes *************************/

void TimerCounterHandler(void *CallBackRef, u8 TmrCtrNumber);//TIMER INTERRUPT FUNCTION
void print(char *str);
int wallhit(unsigned int * camera_frame,unsigned int * wall_frame,unsigned int * Threshold_Frame,unsigned int * write_Frame);
void pb_int_handler(void *baseaddr_p);
int create_base_wall_vector(unsigned int * begin,int original_f_width,int original_f_height,int img_step);//CREATE WALL VECTOR
int copy_base_wall(unsigned int * copy, unsigned int * paste, int img_step, unsigned int * camera_frame,unsigned int * wall_frame,unsigned int * write_Frame);// COPY THE WALL ORIGINAL VETOR
int create_hole_vector(unsigned int * begin,int original_f_width,int original_f_height,int img_step);// CREATES HOLES
void init_INTC ();
void init_GPIO ();
void init_TIMER ();
void enable_GPIO_int ();
void enable_TIMER_int ();
void start_INTC ();
void disable_GPIO_int ();
void disable_TIMER_int ();



/********************** GLOBAL Variable Definitions ************************/
int level=0,flag_menu=0,flag_control=0,enableButtonInterrupt=0,flag_first=0,countWinTimes=0,countTimeStep=0;
volatile unsigned int * memptr = (unsigned int*) XPAR_MIG_7SERIES_0_BASEADDR;// Pointer to the external memory
volatile unsigned int * AR = (unsigned int*) XPAR_TFT_0_BASEADDR;//TFT CONFIGURE PARAMETER
volatile unsigned int * CR = (unsigned int*) XPAR_TFT_0_BASEADDR + 0x4;//TFT CONFIGURE PARAMETER
volatile unsigned int * intc = (unsigned int*) XPAR_MICROBLAZE_0_AXI_INTC_BASEADDR;
volatile int TimerExpired;
volatile unsigned int * displayAddr = 0x40000000;

static XGpio PushBt;
static XIntc myIntc;
static XTmrCtr Timer;


int main()
{
	/********************** Main Variables ************************/
	int i=0,count_lvl_time=0,flag_win=0;

	/********************** Pointers For The Most Important Images ************************/

	volatile unsigned int * openScreen = memptr + 1*IMG_SIZE;
	volatile unsigned int * writeFrame = memptr + 2*IMG_SIZE;
	volatile unsigned int * readFrame = memptr + 3*IMG_SIZE;
	volatile unsigned int * cameraFrame = memptr + 4*IMG_SIZE;
	volatile unsigned int * ThresholdFrame = memptr + 5*IMG_SIZE;

	volatile unsigned int * winFrame = memptr + 6*IMG_SIZE;
	volatile unsigned int * loseFrame = memptr + 7*IMG_SIZE;
	volatile unsigned int * origWallAddrs = memptr + 10*IMG_SIZE; // new pointer
	volatile unsigned int * startWallAddrs = memptr + 21*IMG_SIZE; // changed pointer


	/********************** End of Main Variables ************************/

	/********************** Configurations and first calculations ************************/
	init_platform();
	config_OV7670();
	config_vdma();
	erase_memory(memptr,ImgProc,32); // new
	processing();

	// configuration Image Processing Block
	ImgProc[0] = (int)cameraFrame; // camera
	ImgProc[1] = (int)readFrame; // one colour image
	ImgProc[2] = (int)writeFrame; // output: image in the middle of memory (ensure no conflict with walls for now)

	ImgProc[5] = 0x100; // ensure bit 0 is zero
	ImgProc[5] = 0x111; // pulse bit 0 to 1, set bit 1 high (run constantly), set bit 2 high (perform operation)
	ImgProc[5] = 0x110; // finish bit 0 pulse, keep other bits the same

	screen_color(openScreen,0x000000FF);// START SCREEN IS BLUE

	rand();
	srand(2);

	screen_color(winFrame,0x0000FF00);// WIN SCREEN IS GREEN
	screen_color(loseFrame,0x00FF0000);// LOSE SCREEN IS RED

	init_INTC ();
	init_GPIO ();
	init_TIMER ();
	enable_GPIO_int ();
	enable_TIMER_int ();
	start_INTC ();

	//Wall creation function
	create_base_wall_vector(origWallAddrs,original_frame_width,original_frame_height,image_step);

	*AR = (unsigned int)openScreen;
	*displayAddr = (unsigned int)(level+1);
	flag_menu=1;

	/********************** End Configurations and first calculations ************************/

	while(1)//OUTER LOOP OF THE GAME (CONTAINS MENU AND CONTROL)
	{
		flag_first=0;
		while(flag_menu==1)
		{
			if(flag_first==0)
			{
				XTmrCtr_Stop(&Timer,TIMER_CNTR_0);
				*AR = (unsigned int)openScreen;
				song3();//Menu Song
				flag_first=1;
				PRINT("\nPLAY SONG3");
			}
			//Basically wait for the interruption set the level and release the flag_menu.
		}

		flag_first=0;
		while(flag_control==1)
		{
			if(flag_first==0)
			{
				ImgProc[5] = 0x100;

				while(ImgProc[6]!=0x1)
				{

				}

				flag_first=1;
				copy_base_wall(origWallAddrs,startWallAddrs,image_step,cameraFrame,readFrame,writeFrame);
				create_hole_vector(startWallAddrs,original_frame_width,original_frame_height,image_step);

				if(level==0){count_lvl_time=7;}
				if(level==1){count_lvl_time=6;}
				if(level==2){count_lvl_time=5;}
				if(level==3){count_lvl_time=4;}
				if(level==4){count_lvl_time=3;}

				XTmrCtr_Start(&Timer, TIMER_CNTR_0);
				PRINT("\nLVL SETUP AND TIME START");
				if((level==0)||(level==1)){song7();}
				if((level==2)||(level==3)){song4();}
				if(level==4){song5();}

				ImgProc[5] = 0x100; // ensure bit 0 is zero
				ImgProc[5] = 0x111; // pulse bit 0 to 1, set bit 1 high (run constantly), set bit 2 high (perform operation)
				ImgProc[5] = 0x110; // finish bit 0 pulse, keep other bits the same
			}
			if(TimerExpired>=count_lvl_time)
			{
				*displayAddr = (unsigned int)(level+1);
				TimerExpired=0;
				countTimeStep++;
				if(countTimeStep>11)
				{
					countTimeStep=0;
					flag_win=wallhit(cameraFrame,readFrame,ThresholdFrame,writeFrame);
					*AR = (unsigned int)ThresholdFrame;
					for(i=0;i<=20000000;i++);//TIME TO SEE THE THRESHOLD

					if(flag_win==0)
					{
						song2();
						level=0;
						*AR = (unsigned int)loseFrame;
						for(i=0;i<=60000000;i++);//TIME AJUST FOR THE MUSIC
					}
					else if(flag_win==1)
					{
						song6();
						*AR = (unsigned int)winFrame;
						for(i=0;i<=80000000;i++);//TIME AJUST FOR THE MUSIC
						countWinTimes++;
						if(countWinTimes>=3)
						{
							level++;
							if(level>=4){level=4;}
							countWinTimes=0;
							PRINT("\nLVL UP!!");
						}
					}
					flag_first=0;
				}
				else
				{
					readFrame = startWallAddrs + ((countTimeStep-1)*IMG_SIZE);
					ImgProc[1] = (unsigned int)(readFrame);
					*AR = (unsigned int)(writeFrame);
				}

			}
		}
	}

PRINT("End of Main\n");
return 0;//RETURN OF MAIN
}//END OF MAIN


void TimerCounterHandler(void *CallBackRef, u8 TmrCtrNumber) //TIMER INTERRUPT FUNCTION
{
	XTmrCtr *InstancePtr = (XTmrCtr *)CallBackRef;
	if (XTmrCtr_IsExpired(InstancePtr, TmrCtrNumber))
	{
		TimerExpired++;
		if(TimerExpired>=100)
		{
			TimerExpired=0;
		}
	}
}


int wallhit(unsigned int * camera_frame,unsigned int * wall_frame,unsigned int * Threshold_Frame,unsigned int * write_Frame)
{
	int i=0,j=0,k=0,count_user=0,count_wall_hit=0;

	ImgProc[5] = 0x100; // ensure bit 0 is zero

	while(ImgProc[6]!=0x1)
	{

	}

	threshold_interaction();

	ImgProc[0] = (int)camera_frame; // camera
	ImgProc[1] = (int)wall_frame; // one colour image
	ImgProc[2] = (int)Threshold_Frame; // output: image in the middle of memory (ensure no conflict with walls for now)

	ImgProc[5] = 0x101; // pulse bit 0 to 1, set bit 1 high (run constantly), set bit 2 high (perform operation)
	ImgProc[5] = 0x100; // finish bit 0 pulse, keep other bits the same



	ImgProc[5] = 0x100; // ensure bit 0 is zero

	while(ImgProc[6]!=0x1)
	{

	}



	ImgProc[0] = (int)camera_frame; // camera
	ImgProc[1] = (int)wall_frame; // one colour image
	ImgProc[2] = (int)write_Frame; // output: image in the middle of memory (ensure no conflict with walls for now)

	processing();


	for (j = 160; j < 480; j++)//MASK ON THE SECOND FRAME
	{
			for (k = 0; k < 640; k++)//MASK ON THE SECOND FRAME
			{
				i=(j*1024)+k;

				if(Threshold_Frame[i]==0x00FFFFFF)//white
				{
					count_user++;
				}
				else if(Threshold_Frame[i]==0x00808080)//gray
				{
					count_wall_hit++;
				}
			}
	}
	/*
	for (i = 160*1024;i<IMG_SIZE; i++)
	{
		if(Threshold_Frame[i]==0x00FFFFFF)//white
		{
			count_user++;
		}
		else if(Threshold_Frame[i]==0x00808080)//gray
		{
			count_wall_hit++;
		}
	}
	*/
	PRINT("%d",count_wall_hit);
	if(count_wall_hit<5000)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}


void pb_int_handler(void *baseaddr_p)
{
        int dsr;

        //DSR contains the INFORMATION of which button was depressed, so we can switch on its value.
        dsr = XGpio_DiscreteRead(&PushBt, 1);

        switch(dsr) {

            case 16:// LEVEL ++ (UP)
            	if(enableButtonInterrupt==0)
            	{
            		level++;
            		if(level>=4)
            		{
            			level=4;
            		}
            	}
                break;

            case 0x8:// LEVEL -- (DOWN)
            	if(enableButtonInterrupt==0)
            	{
            		level--;
            		if(level<=0)
            		{
            			level=0;
            		}
            	}
                break;

            case 0x4:// START (LEFT)
            	if(enableButtonInterrupt==0)
            	   {
            		flag_menu=0;
            		flag_control=1;
            		enableButtonInterrupt=1;
                   }
                break;

            case 0x2:// CAMERA


                break;

            case 0x1:// RESET (CENTER)

            		flag_menu=1;
            		flag_control=0;
            		enableButtonInterrupt=0;
            		countWinTimes=0;
            		level=0;
            		TimerExpired=0;
            		flag_first=0;
            		countTimeStep=0;

                break;

            default :  PRINT("");

        }

        *displayAddr = (unsigned int)(level+1);
        //Clear the interrupt both in the Gpio instance as well as the interrupt controller
        XGpio_InterruptClear(&PushBt, 0xff);
        XIntc_Acknowledge(&myIntc,XPAR_MICROBLAZE_0_AXI_INTC_AXI_GPIO_PUSH_BUTTONS_IP2INTC_IRPT_INTR);
 }

void init_INTC ()
{
	PRINT("Setting up interrupt controller...\r\n");
	XIntc_Initialize(&myIntc, XPAR_INTC_0_DEVICE_ID);
}

void init_GPIO ()
{
	PRINT("Setting up GPIO...\r\n");
	XGpio_Initialize(&PushBt, XPAR_AXI_GPIO_PUSH_BUTTONS_DEVICE_ID);
	XGpio_SetDataDirection(&PushBt,1,0xfffffff);
	//set pb as input port ,the first 1 means for channel 1, the second 0xff means set all wire as input
	PRINT("Register the interrupt...\r\n");
	XIntc_Connect(&myIntc, XPAR_MICROBLAZE_0_AXI_INTC_AXI_GPIO_PUSH_BUTTONS_IP2INTC_IRPT_INTR,(XInterruptHandler)pb_int_handler,&PushBt);
}

void init_TIMER ()
{
	PRINT("Setting up TIMER...\r\n");
	XTmrCtr_Initialize(&Timer, XPAR_TMRCTR_0_DEVICE_ID);
	XIntc_Connect(&myIntc, XPAR_MICROBLAZE_0_AXI_INTC_AXI_TIMER_0_INTERRUPT_INTR,(XInterruptHandler)XTmrCtr_InterruptHandler,&Timer);
}

void enable_GPIO_int ()
{
	XGpio_InterruptGlobalEnable(&PushBt);
	XGpio_InterruptEnable(&PushBt, 0xfffffff);
	XIntc_EnableIntr(&myIntc,XPAR_MICROBLAZE_0_AXI_INTC_AXI_GPIO_PUSH_BUTTONS_IP2INTC_IRPT_INTR );
}

void enable_TIMER_int ()
{
	XIntc_Enable(&myIntc, XPAR_MICROBLAZE_0_AXI_INTC_AXI_TIMER_0_INTERRUPT_INTR);
	XTmrCtr_SetHandler(&Timer,TimerCounterHandler,&Timer);
	XTmrCtr_SetOptions(&Timer, TIMER_CNTR_0,XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);
	XTmrCtr_SetResetValue(&Timer, TIMER_CNTR_0, RESET_VALUE);
	XTmrCtr_Start(&Timer, TIMER_CNTR_0);
}

void start_INTC ()
{
	PRINT("Start the interrupt controller...\r\n");
	XIntc_Start(&myIntc, XIN_REAL_MODE);
	XIntc_MasterEnable(&myIntc);
	microblaze_enable_interrupts();
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_M_AXI_I_EXCEPTION,(XExceptionHandler)XIntc_InterruptHandler,&myIntc);
	Xil_ExceptionEnable();
	*(intc+2)=0xffffffff;   //enable the interrupt
	*(intc+20)=0xffffffff;  //enable fast interrupt mode
}

void disable_GPIO_int ()
{
	XIntc_Disable(&myIntc,(int)&PushBt);
}

void disable_TIMER_int ()
{
	XIntc_Disable(&myIntc,(int)&Timer);
}

int create_base_wall_vector(unsigned int * begin,int original_f_width,int original_f_height,int img_step)
{

	int i=0,image_x=0,image_y=0,image_height_step=0,image_width_step=0;
	volatile unsigned int * image_wall;

	//WALL RATE OF GROW
	image_height_step=original_f_height/img_step;
	image_width_step=original_f_width/img_step;

	for(i=0;i<=img_step;i++)
	{
		image_wall = begin + (i*IMG_SIZE);
		image_x=320-(i*image_width_step)/2;
		image_y=240-(i*image_height_step)/2;
		create_wall_no_hole(image_x,image_y,i*image_height_step,i*image_width_step,image_wall);
	}

	return 0;
}

int copy_base_wall(unsigned int * copy, unsigned int * paste, int img_step, unsigned int * camera_frame,unsigned int * wall_frame,unsigned int * write_Frame)
{
	int i = 0;

	copy_img1 ();

	for(i=0;i<=img_step;i++)
	{
		ImgProc[0] = (int)(copy + i*IMG_SIZE); // copy
		ImgProc[2] = (int)(paste + i*IMG_SIZE); // paste

		ImgProc[5] = 0x100; // ensure bit 0 is zero
		ImgProc[5] = 0x101; // pulse bit 0 to 1, set bit 1 low (run one frame), set bit 2 high (perform operation)
		ImgProc[5] = 0x100; // finish bit 0 pulse, keep other bits the same

		while(ImgProc[6]!=0x1){} // wait until frame is finished
	}

	ImgProc[0] = (int)camera_frame; // camera
	ImgProc[1] = (int)wall_frame; // one colour image
	ImgProc[2] = (int)write_Frame; // output: image in the middle of memory (ensure no conflict with walls for now)

	processing();

	return 0;
}

int create_hole_vector(unsigned int * begin,int original_f_width,int original_f_height,int img_step)
{

	int hole_x=0,hole_width=0,hole_height=0,i=0,image_x=0,image_y=0,image_height_step=0,image_width_step=0;
	volatile unsigned int * image_wall;

	//WALL RATE OF GROW
	image_height_step=original_f_height/img_step;
	image_width_step=original_f_width/img_step;

    hole_x=hole_x_codinate(original_f_width-240);  // the original width of the frame is 640
	hole_width=adjust_hole_width(original_hole_width,level);   //160 is the original_width
	hole_height=adjust_hole_height(original_hole_height,level);  //240 is the original height

	for(i=0;i<=img_step;i++)
	{
		image_wall = begin + (i*IMG_SIZE);
		image_x=320-(i*image_width_step)/2;
		image_y=240-(i*image_height_step)/2;
		create_hole(image_x,image_y,i*image_height_step,i*image_width_step,image_wall,hole_x,hole_width,hole_height);
	}

	return 0;
}
