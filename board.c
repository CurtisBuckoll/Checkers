#include <stdlib.h>
#include <stdio.h>

#include "board.h"

//Called by DrawBoard()
void Draw_line(unsigned int size)
{
	for (int x=0; x < (size*8); x++)
	{
		if ( x%size == 0 )	printf("|");
		else				printf("-");
	}
	printf("|\n");
}

//Called by DrawBoard()
void Draw_space(unsigned int size, int * fill)
{
	for (int x=0; x < (size*8) ; x++)
	{
		if ( x%size == 0 )
		{
			(*fill)++;
			printf("|");
		}
		else if ( (*fill)%2 == 0)
			printf(" ");
		else
			printf("*");
	}
	printf("|\n");
}

//Called by DrawBoard()
void Draw_mid(unsigned int size, int y)
{
	for (int x=0; x < (size*8) ; x++)
	{
		if ( x%size == 0)	printf("|");
		else			printf(" ");
	}
	printf("|\n");
}


//Print gameboard to screen
void DrawBoard( )
{
	int fill = 1;
	int size = 6; //Fixed size
	if ( size!= 2 && size != 4 && size != 6) 
	{
		printf("ERROR: WRONG BOARD SIZE");
		exit(0);
	}
	
	for (int i=0; i<2; i++) printf("\n");
		
	for (int y=0; y < (size*8)+1 ; y++)
	{
		if ( y%size == 0 )
		{
			Draw_line( size+2 );
			fill++;
		}
		else
			Draw_space( size+2, &fill );
	}
}