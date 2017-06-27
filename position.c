#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "position.h"

/* pieces_t pointer functions */

//Print player number at location if there is a piece at loc.
// *For building this program*
void PiecePrint( pieces_t * posit_P[][8] )
{
	for (int y=0; y<8; y++)
	{
		for (int x=0; x<8; x++)
		{
			if ( posit_P[x][y] == NULL )
				printf("0 ");
			else
				//printf("1 ");
				printf("%d ", posit_P[x][y]->player );
		}
		printf("\n");
	}
}

//Custom starting location of game pieces
// * For building/testing program *
void Test_Init( pieces_t * positions[][8], 
				pieces_t * player1[], 
				pieces_t * player2[] )
{
	positions[5][5]->isKing = 1;
	positions[4][4] = positions[2][2];
	//positions[2][2] = NULL;
	//positions[5][1] = NULL;
	//positions[1][1] = NULL;
	positions[1][5] = NULL;
	positions[2][4] = positions[0][0];
	positions[5][3] = positions[7][7];
}


//Set board coordinates to NULL
void Zero( pieces_t * list[][8] )
{
	for (int y=0; y<8; y++)
	{
		for (int x=0; x<8; x++)
			list[x][y] = NULL;
	}
}

//Create player pieces (fixed arr len 12) return -1 if fail.
int Init_Player(int player, pieces_t * list[] )
{
	for( int i=0; i<12; i++ )
	{
		list[i] = malloc( sizeof(pieces_t));
		if ( list[i] == NULL )
			return -1;
		list[i]->player = player;
		list[i]->isKing = 0;
	}
	return 0;
}

//Put pieces in starting location
void Init_Position( pieces_t * posit_P[][8], 
					pieces_t * player1[], 
					pieces_t * player2[] )
{
	int fill=0;
	int p1 = 0;
	int p2 = 0;
	for ( int y=0; y<3; y++)
	{
		fill++;
		//Player 1
		for ( int x=0; x<8; x++)
		{
			fill++;
			if ( fill%2 == 0)
			{
				posit_P[x][y] = player1[p1];
				p1++;
			}
		}
		//Player 2
		for ( int x=0; x<8; x++)
		{
			fill++;
			if ( fill%2 == 1) 
			{
				posit_P[x][y+5] = player2[p2];
				p2++;
			}
		}
	}
}

//Checks a piece selection
int Check_Select( int xCur, int yCur, int player,
				  pieces_t * board[][8] )
{
	if ( xCur > 7 || xCur < 0 || yCur > 7 || yCur < 0 )
		return -1;
	
	if ( board[xCur][yCur] == NULL ||
		 board[xCur][yCur]->player != player )
			return -1;
	else
		return 0;
}

/* Checks piece destination - return -1 if not valid
 * Checks for valid move with/without capture */
int Check_Dest( int xCur, int yCur,
				int xNex, int yNex, int player,
				pieces_t * board[][8] )
{
	int xDist = abs( xCur - xNex );
	int yDist = abs( yCur - yNex );
	
	//If nex is outside board
	if ( xNex > 7 || xNex < 0 || yNex > 7 || yNex < 0 )
		return -1;
	
	//If out of range or filled spot is targeted
	if ( board[xNex][yNex] != NULL || xDist != yDist || 
		 xDist > 2 || xDist == 0)
			return -2;
	
	//if capture is not valid
	int xMid = (xCur + xNex)/2;
	int yMid = (yCur + yNex)/2;
	if ( xDist == 2 && ( board[xMid][yMid] == NULL ||
		 board[xMid][yMid]->player == player ) )
		return -3;
		
	//if not King
	if ( player == 1 && yNex > yCur && 
		 board[xCur][yCur]->isKing == 0 )
			 return -4;
	if ( player == 2 && yNex < yCur && 
		 board[xCur][yCur]->isKing == 0 )
			 return -5;
			 
	return 0;
}

//Return 1 if another capture is valid, 0 if not
int Capture_Again( int xCur, int yCur, 
				   int pl, pieces_t * b[][8] )
{
	int CurPlayer = b[xCur][yCur]->player;
	int xMid = 0;
	int yMid = 0;
	
	//Check top right
	if ( Check_Dest( xCur, yCur, xCur+2, yCur-2, pl, b ) == 0 )
	{
		//printf("TOP RIGHT\n");
		return 1;
	}
	//Check bottom right
	if ( Check_Dest( xCur, yCur, xCur+2, yCur+2, pl, b ) == 0 )
	{
		//printf("BOT RIGHT\n");
		return 1;
	}
	//Check top left
	if ( Check_Dest( xCur, yCur, xCur-2, yCur-2, pl, b ) == 0 )
	{
		//printf("TOP LEFT\n");
		return 1;
	}
	//Check bottom left
	if ( Check_Dest( xCur, yCur, xCur-2, yCur+2, pl, b ) == 0 )
	{
		//printf("BOT LEFT\n");
		return 1;
	}

	return 0;
}

//Conducts movement of piece/capture
int Move( int xCur, int yCur,
		  int xNex, int yNex, 
		  int score[],
		  pieces_t * board[][8] )
{
	
	//Move piece
	board[xNex][yNex] = board[xCur][yCur];
	board[xCur][yCur] = NULL;
	
	//Check if should King piece
	if (yNex == 0 && board[xNex][yNex]->player == 1 &&
		board[xNex][yNex]->isKing == 0 )
			board[xNex][yNex]->isKing = 1;
			
	if (yNex == 7 && board[xNex][yNex]->player == 2 &&
		board[xNex][yNex]->isKing == 0 )
			board[xNex][yNex]->isKing = 1; 
	
	//Remove a captured piece
	int xDist = abs( xCur - xNex );
	int xMid = (xCur + xNex)/2;
	int yMid = (yCur + yNex)/2;
	if ( xDist == 2 )
	{
		//Adjust score count
		score[ ( board[xMid][yMid]-> player ) - 1 ]--;

		//Destroy game piece
		free( board[xCur][yCur] );
		board[xMid][yMid] = NULL;
	
		//Return 1 to indicate additional moves
		if ( Capture_Again( xNex, yNex, board[xNex][yNex]->player, 
							board ) == 1 )
			return 1;
	}
	
	return 0;
}


/* 			DRAW FUNCTIONS 			*/


//Called by DrawBoard()
void Draw_line(unsigned int size, pieces_t * board[][8])
{
	printf("      ");
	for (int x=0; x < (size*8); x++)
	{
		if ( x%size == 0 )	printf("|");
		else				printf("-");
	}
	printf("|\n");
}

//Called by DrawBoard()
void Draw_space(unsigned int size, int y, int yCor, int * fill, 
				pieces_t * board[][8] )
{	
	if ( y %(size - 5) == 0 )	printf("   %d  ", yCor+1);
		else					printf("      ");
			
	int xCor = -1;
	for (int x=0; x < (size*8) ; x++)
	{
		if ( x%size == 0 )
		{
			(*fill)++;
			xCor++;
			printf("|");
		}
		else if ( (*fill)%2 == 0)
			printf("*");
		else if ( y %(size - 5) == 0 )
		{
			if ( board[xCor][yCor] != NULL )
			{
				if ( board[xCor][yCor]->isKing == 0 )
					printf(" ( %d ) ", board[xCor][yCor]->player );
				else
					printf("(( %d ))", board[xCor][yCor]->player );
			}
			else 
				printf("       ");
			x+=6;
		}
		else
			printf(" ");
	}
	printf("|\n");
}

//Print gameboard to screen
void DrawBoard( pieces_t * board[][8] )
{
	int fill = 1;
	int size = 6; //Fixed size
	
	for (int i=0; i<20; i++) printf("\n");
	
	int yCor = -1;
	
	//Draw Top Header
	printf("          ");
	for (int i=1; i<9; i++)
		printf("%d       ", i);
	printf("\n\n");
	
	//Draw Main
	for (int y=0; y < (size*8)+1 ; y++)
	{
		if ( y%size == 0 )
		{
			Draw_line( size+2, board );
			fill++;
			yCor++;
		}
		else
			Draw_space( size+2, y, yCor, &fill, board );
	}
}