// cd Documents\Checkers

#include <stdlib.h>
#include <stdio.h>


#include "position.h"

int main()
{
	pieces_t * positions[8][8];
	Zero( positions );
	int xCurrent, yCurrent, xNext, yNext;
	
	pieces_t * player1[12] = {NULL};
	pieces_t * player2[12] = {NULL};
	//To change this must adjust king settings in Move,
	// .. and maybe more ..
	if ( Init_Player( 2, player1 ) == -1 || 
		 Init_Player( 1, player2 ) == -1 )
			exit(0);
	int score[2] = {12, 12};
	
	
	Init_Position( positions, player1, player2 ); 
	
	//Test_Init( positions, player1, player2 ); //Strictly for testing
	//PiecePrint( positions );
	DrawBoard( positions );
	
	int CurPlayer =1;
	
	while(1)
	{ 
		int check = 0;
		while ( check != 2 )
		{
			if ( check == 0 )
				printf("Player %d: Select a game piece (x y): ", CurPlayer );
			
			check = scanf( "%d %d", &xCurrent, &yCurrent );
			fseek( stdin, 0, SEEK_END );
			xCurrent--; yCurrent--;
			if ( check != 2 )
			{
				printf("Bad input, try again: ");
				check = 1;
			}
			else if ( check == 2 &&
				 Check_Select( xCurrent, yCurrent, 
							   CurPlayer, positions ) != 0 )
			{	
				printf("Bad input, try again: ");
				check = 1;
			}
			else
			{
				printf("Select a location (x y): ");
				check = scanf( "%d %d", &xNext, &yNext );
				fseek( stdin, 0, SEEK_END );
				xNext--; yNext--;
				if ( check != 2 )
				{
					printf("Bad input, reselect game piece: ");
					check = 1;
				}
				if ( check == 2 &&
					Check_Dest( xCurrent, yCurrent,
								xNext, yNext,
								CurPlayer, positions ) != 0 )
				{
					printf("Bad input(%d), reselect game piece: ", 
								Check_Dest( xCurrent, yCurrent,
								xNext, yNext,
								CurPlayer, positions ) );
					check = 1;
				}
			}
		}
		
		//Perform Movement
		int capture = Move( xCurrent, yCurrent, xNext, yNext, score, positions );
		
		//Draw Board	PiecePrint( positions );
		DrawBoard( positions );
		
		//Check for additional capture(s)
		xCurrent = xNext;		yCurrent = yNext;
		check = 0;
		while( capture == 1 )
		{
			fseek( stdin, 0, SEEK_END );
			printf("Additional capture(s) possible! Select location: (x y): ");
			while ( check != 2)
			{
				check = scanf( "%d %d", &xNext, &yNext );
				fseek( stdin, 0, SEEK_END );
				xNext--; yNext--;
				if ( check != 2 )
				{
					printf("Bad input, select another location: ");
					check = 1;
				}
				if ( check == 2 &&	Check_Dest( xCurrent, yCurrent,
									xNext, yNext,
									CurPlayer, positions ) != 0 )
				{
					printf("Bad input(%d), select another location: ", 
								Check_Dest( xCurrent, yCurrent,
								xNext, yNext,
								CurPlayer, positions ) );
					check = 1;
				}
			}
			//Move and update board
			capture = Move( xCurrent, yCurrent, xNext, yNext, score, positions );
			DrawBoard( positions );
		}
		
		//Check score
		if ( score[0] == 0 ) {
			printf("Player 2 wins!");
			break;
		}
		else if ( score[1] == 0 ) {
			printf("Player 1 wins!");
			break;
		}
		//Switch player turns
		if ( CurPlayer == 1 )		CurPlayer = 2;
			else					CurPlayer = 1;	
	}
	return 0;
}