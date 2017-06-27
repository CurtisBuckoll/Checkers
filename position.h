/* Functions for creating/destroying/updating 
 * game piece positions */


typedef struct {
	int player;
	int isKing;
} pieces_t;


//Print player number at location if there is a piece at loc.
// * For building/testing program *
void PiecePrint( pieces_t * posit_P[][8] );

//Custom starting location of game pieces
// * For building/testing program *
void Test_Init( pieces_t * positions[][8], 
				pieces_t * player1[], 
				pieces_t * player2[] );

//Set board coordinates to NULL
void Zero( pieces_t * list[][8] );

//Create the game pieces for player x
int Init_Player(int player, pieces_t * list[] );

//Initialized board pieces for start of game
void Init_Position( pieces_t * posit_P[][8], 
					pieces_t * player1[], 
					pieces_t * player2[] );

//Return 1 if another capture is valid, 0 if not
int Capture_Again( int xCur, int yCur, 
				   int pl, pieces_t * b[][8] );

//Conducts movement of piece and capturing
int Move( int xCur, int yCur,
		  int xNex, int yNex, int score[],
		  pieces_t * board[][8] );

//Checks a piece selection
int Check_Select( int xCur, int yCur, int player,
				  pieces_t * board[][8] );

/* Checks piece destination - return -1 if not valid
 * Checks for valid with/without jumps */
int Check_Dest( int xCur, int yCur,
				int xNex, int yNex, int player,
				pieces_t * board[][8] );

//Draws the gameboard with current mapping
void DrawBoard( pieces_t * board[][8] );