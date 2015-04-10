/*
 * create_wall.c
 *
 *  Created on: 2015-3-10
 *      Author: hy
 */

#include "create_wall.h"
//#include "ImgProc_config.h"

int hole_x_codinate(int max_width)
{
	return rand()%max_width+1;
}

int hole_position(int hole_size, int original_f_width,int rand_old)
{
	int rand_aux = 0, rand_value = 0,pos_x = 0;
	int number_of_positions=31;
	int step = original_f_width/number_of_positions, aux = 0;
	rand_old = rand_old/step;
	while (rand_aux<5)
	{
		rand_value = (rand() % number_of_positions);
		if (rand_value > rand_old)
		{
			rand_aux = rand_value - rand_old;
		}
		else
		{
			rand_aux = rand_old - rand_value;
		}
	}

	rand_old = rand_value;
	rand_aux = 0;
	pos_x = rand_value*step;
	if (pos_x >= (original_f_width - hole_size))
	{
		pos_x = original_f_width - hole_size;
	}

	return pos_x;
}

int adjust_hole_width(int original_width,int level)
{
	if(level>5)
	{
		level = 5;
	}
	return original_width-20*level;
}

int adjust_hole_height(int original_height,int level)
{
	if(level>5)
	{
		level = 5;
	}
	return original_height-20*level;
}

int image_black(unsigned int * img)
{
	int i=0;
	for (i = 0; i < IMG_SIZE; i++)
	{
		img[i] = 0x00000000;
	}
	return 0;
}

unsigned int pixel32_color8(unsigned int pixel, int select)// function to extract colour from a pixel word
{
	unsigned int color=0;
	if (select == 0)//RED
	{
		color = (pixel & 0x00FF0000) >> 16;
		return color;
	}
	else if (select == 1)//GREEN
	{
		color = (pixel & 0x0000FF00) >> 8;
		return color;
	}
	else if (select == 2)//BLUE
	{
		color = (pixel & 0x000000FF);
		return color;
	}
	return 256;
}


int initial_screen(unsigned int *screen)
{
	int i=0;
	for (i = 0; i < IMG_SIZE; i++)
		{
			screen[i] = 0x000000FF;//BLUE
		}
	return 0;
}

int screen_color(unsigned int *screen,int color)
{
	int i;
	for (i = 0; i < IMG_SIZE; i++)
		{
			screen[i] = color;
		}
	return 0;
}

// OLD
/*int erase_memory(unsigned int *begin_mem,int images)
{
	int i=0;
	for (i = 0; i < images*IMG_SIZE; i++)
	{
		begin_mem[i] = 0x00000000;
	}
	return 0;
}*/

// NEW
int erase_memory(unsigned int *begin_mem, unsigned int *ImgProcBlock, int images)
{
	int i=0;

	write_black (); // write black configuration for Image Processing block. From "ImgProc_config.h"

    ImgProcBlock[0] = 0x84000000; // something
	ImgProcBlock[1] = 0x84200000; // something

	// loop through memory
	for (i=0; i<images; i++)
	{

		ImgProcBlock[2] = begin_mem + i*IMG_SIZE;

		ImgProcBlock[5] = 0x100; // ensure bit 0 is zero
		ImgProcBlock[5] = 0x101; // pulse bit 0 to 1, set bit 1 low (run one frame), set bit 2 high (perform operation)
		ImgProcBlock[5] = 0x100; // finish bit 0 pulse, keep other bits the same

		while(ImgProcBlock[6]!=0x1){} // wait until frame is finished

	}

	return 0;
}

int create_wall(unsigned int x,unsigned int y,unsigned int high,unsigned int width,unsigned int * wall,int hole_x,int hole_width,int hole_height)
{
	unsigned int i=0,xf=0,yf=0,k=0,aux_r=0,w=0,aux_c=0,c=0;
	unsigned int begin=0,final=0,row_step=0,colum_step=0,size_line=0,flag=0;
	int x_hole=0,scale_hole_width=0,scale_hole_height=0,j=0;

	image_black(wall);

	xf = x+width;
	yf = y+high;

	begin =(y*1024)+x;
	final =(yf*1024)+xf;
	if(final>IMG_SIZE)
	{
		final=IMG_SIZE;
	}
	if(begin>IMG_SIZE)
	{
		begin=IMG_SIZE;
	}


	colum_step = (unsigned int)(xf-x)/10;
	row_step = (unsigned int)(yf-y)/10;

	if(width<=high)
	{
		size_line=(unsigned int)(width/120);
	}
	else
	{
		size_line=(unsigned int)(high/120);
	}

	if(size_line==0)
	{
		size_line=1;
	}

	w=0;
	k=0;
	c=0;
	aux_r=row_step*w;
	aux_c=colum_step*c;

	for (i = begin; i <= final; i++)
	{
		if((i>=begin+(k*1024))&&(i<=(begin+(k*1024)+width)))
		{
			wall[i] = 0x00B97A57;//Wall Color
			//ROWS
			if((k>=aux_r)&&(k<=aux_r+size_line))
			{
				wall[i] = 0x00FFFFFF;//White line
				if(k==aux_r+size_line)
				{
					w++;
					aux_r=row_step*w;
					if(flag==0)
					{
						flag=1;
					}
					else
					{
						flag=0;
					}
				}
			}



			//COL
			if((i>=begin+(k*1024)+aux_c)&&(i<=(begin+aux_c+(k*1024)+size_line)))
			{
					if(flag==1)
					{
						wall[i] = 0x00FFFFFF;//White line
						if(i==(begin+aux_c+(k*1024)+size_line))
						{
							c = c+2;
							aux_c=colum_step*c;
						}
					}
					else
					{
						wall[i] = 0x00FFFFFF;//White line
						if(i==(begin+aux_c+(k*1024)+size_line))
						{
							if(c==0)
							{
								c=1;
							}
							else
							{
								c=c+2;
							}
							aux_c=colum_step*c;
						}
					}

			}
			if(i==(begin+(k*1024)+width))
			{
				k++;
				aux_c=0;
				c=0;
			}



		}

	}

	x_hole=(xf-x)*hole_x/640+x;
	scale_hole_width=hole_width*width/original_frame_width;
	scale_hole_height=hole_height*high/original_frame_height;
	begin =((yf-scale_hole_height)*1024)+x_hole;
	final =(yf*1024)+scale_hole_width+x_hole;
	for(i=0;i<=scale_hole_height;i++)
	{
		for(j=0;j<scale_hole_width;j++)
		{
			wall[begin+i*1024+j]=0x00000000;
		}

	}
	return 0;
}

// 2 new functions

int create_wall_no_hole(unsigned int x,unsigned int y,unsigned int high,unsigned int width,unsigned int * wall)
{
	unsigned int i=0,xf=0,yf=0,k=0,aux_r=0,w=0,aux_c=0,c=0;
	unsigned int begin=0,final=0,row_step=0,colum_step=0,size_line=0,flag=0;

	image_black(wall);

	xf = x+width;
	yf = y+high;

	begin =(y*1024)+x;
	final =(yf*1024)+xf;
	if(final>IMG_SIZE)
	{
		final=IMG_SIZE;
	}
	if(begin>IMG_SIZE)
	{
		begin=IMG_SIZE;
	}


	colum_step = (unsigned int)(xf-x)/10;
	row_step = (unsigned int)(yf-y)/10;

	if(width<=high)
	{
		size_line=(unsigned int)(width/120);
	}
	else
	{
		size_line=(unsigned int)(high/120);
	}

	if(size_line==0)
	{
		size_line=1;
	}

	w=0;
	k=0;
	c=0;
	aux_r=row_step*w;
	aux_c=colum_step*c;

	for (i = begin; i <= final; i++)
	{
		if((i>=begin+(k*1024))&&(i<=(begin+(k*1024)+width)))
		{
			wall[i] = 0x00B97A57;//Wall Color
			//ROWS
			if((k>=aux_r)&&(k<=aux_r+size_line))
			{
				wall[i] = 0x00FFFFFF;//White line
				if(k==aux_r+size_line)
				{
					w++;
					aux_r=row_step*w;
					if(flag==0)
					{
						flag=1;
					}
					else
					{
						flag=0;
					}
				}
			}



			//COL
			if((i>=begin+(k*1024)+aux_c)&&(i<=(begin+aux_c+(k*1024)+size_line)))
			{
					if(flag==1)
					{
						wall[i] = 0x00FFFFFF;//White line
						if(i==(begin+aux_c+(k*1024)+size_line))
						{
							c = c+2;
							aux_c=colum_step*c;
						}
					}
					else
					{
						wall[i] = 0x00FFFFFF;//White line
						if(i==(begin+aux_c+(k*1024)+size_line))
						{
							if(c==0)
							{
								c=1;
							}
							else
							{
								c=c+2;
							}
							aux_c=colum_step*c;
						}
					}

			}
			if(i==(begin+(k*1024)+width))
			{
				k++;
				aux_c=0;
				c=0;
			}
		}
	}

	return 0;
}

int create_hole(unsigned int x,unsigned int y,unsigned int high,unsigned int width,unsigned int * wall,int hole_x,int hole_width,int hole_height)
{
	unsigned int i=0,xf=0,yf=0;
	unsigned int begin=0,final=0,flag=0;
	int x_hole=0,scale_hole_width=0,scale_hole_height=0,j=0;

	xf = x+width;
	yf = y+high;

	x_hole=(xf-x)*hole_x/640+x;
	scale_hole_width=hole_width*width/original_frame_width;
	scale_hole_height=hole_height*high/original_frame_height;
	begin =((yf-scale_hole_height)*1024)+x_hole;
	final =(yf*1024)+scale_hole_width+x_hole;
	for(i=0;i<=scale_hole_height;i++)
	{
		for(j=0;j<scale_hole_width;j++)
		{
			wall[begin+i*1024+j]=0x00000000;
		}

	}
	return 0;
}
