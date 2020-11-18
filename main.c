#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE_MARKER    "  ○ "
#define BLACK_MARKER    "  ● "
#define EMPTY_MARKER    "     "
#define ABLE_MARKER "  .  "
#define WHITE    0
#define BLACK    1
#define EMPTY    2
#define PLAYABLE 3
#define FALSE 0
#define TRUE  1

const char *row_names = "01234567";
const char *col_names = "01234567";

char board[8][8];
int playable_direction[8][8][8];
int player1,player2;
int game_ended = FALSE;
int skipped_turn = FALSE;
int wrong_move = FALSE;
int has_valid_move = FALSE;
int scores[2];
int black_score = 2;

void init_game( )
{
    memset( board, EMPTY, sizeof( board ) );
    board[3][3] = BLACK;
    board[4][4] = BLACK;
    board[3][4] = WHITE;
    board[4][3] = WHITE;
    scores[WHITE] = 2;
    scores[BLACK] = 2;
    player1 = BLACK;
}

int valid_position( int i, int j )
{
    if ( i < 0 || i >= 8 || j < 0 || j >= 8 ) return FALSE;
    return TRUE;
}

int distance( int i1, int j1, int i2, int j2 )
{
    int di = abs( i1 - i2 ), dj = abs( j1 - j2 );
    if ( di > 0 ) return di;
    return dj;
}



void mark_playable_positions( )
{
	int i,j;
    has_valid_move = FALSE;
    for ( i=0; i<8; ++i )
    {
        for ( j=0; j<8; ++j )
        {
            if ( board[i][j] == PLAYABLE )
                board[i][j] = EMPTY;
            if ( able( i, j ) )
            {
                board[i][j] = PLAYABLE;
                has_valid_move = TRUE;
            }
        }
    }
}
void capture_pieces(int i, int j)
{
	int player2 = (player1 + 1) % 2;
	int position_1, position_2;

	// Capture UL diagonal
	if (playable_direction[i][j][0])
	{
		position_1 = i - 1, position_2 = j - 1;
		while (board[position_1][position_2] == player2)
		{
			board[position_1][position_2] = player1;
			scores[player1]++;
			scores[player2]--;
			position_1 -= 1;
			position_2 -= 1;
		}
	}

	// Capture UP path
	if (playable_direction[i][j][1])
	{
		position_1 = i - 1, position_2 = j;
		while (board[position_1][position_2] == player2)
		{
			board[position_1][position_2] = player1;
			scores[player1]++;
			scores[player2]--;
			position_1 -= 1;
		}
	}

	// Capture UR diagonal
	if (playable_direction[i][j][2])
	{
		position_1 = i - 1, position_2 = j + 1;
		while (board[position_1][position_2] == player2)
		{
			board[position_1][position_2] = player1;
			scores[player1]++;
			scores[player2]--;
			position_1 -= 1;
			position_2 += 1;
		}
	}

	// Capture LEFT path
	if (playable_direction[i][j][3])
	{
		position_1 = i, position_2 = j - 1;
		while (board[position_1][position_2] == player2)
		{
			board[position_1][position_2] = player1;
			scores[player1]++;
			scores[player2]--;
			position_2 -= 1;
		}
	}

	// Capture RIGHT path
	if (playable_direction[i][j][4])
	{
		position_1 = i, position_2 = j + 1;
		while (board[position_1][position_2] == player2)
		{
			board[position_1][position_2] = player1;
			scores[player1]++;
			scores[player2]--;
			position_2 += 1;
		}
	}

	// Capture DL diagonal
	if (playable_direction[i][j][5])
	{
		position_1 = i + 1, position_2 = j - 1;
		while (board[position_1][position_2] == player2)
		{
			board[position_1][position_2] = player1;
			scores[player1]++;
			scores[player2]--;
			position_1 += 1;
			position_2 -= 1;
		}
	}

	// Capture DOWN path
	if (playable_direction[i][j][6])
	{
		position_1 = i + 1, position_2 = j;
		while (board[position_1][position_2] == player2)
		{
			board[position_1][position_2] = player1;
			scores[player1]++;
			scores[player2]--;
			position_1 += 1;
		}
	}

	// Capture DR diagonal
	if (playable_direction[i][j][7])
	{
		position_1 = i + 1, position_2 = j + 1;
		while (board[position_1][position_2] == player2)
		{
			board[position_1][position_2] = player1;
			scores[player1]++;
			scores[player2]--;
			position_1 += 1;
			position_2 += 1;
		}
	}
}
int able(int i, int j)
{
	memset(playable_direction[i][j], 0, 8);
	if (!valid_position(i, j)) return FALSE;
	if (board[i][j] != EMPTY) return FALSE;
	int playable = FALSE;

	int player2 = (player1 + 1) % 2;

	// Test UL diagonal
	int position_1 = i - 1, position_2 = j - 1;
	while (valid_position(position_1, position_2) && board[position_1][position_2] == player2)
	{
		position_1 -= 1;
		position_2 -= 1;
	}
	if (valid_position(position_1, position_2) && distance(i, j, position_1, position_2) > 1 && board[position_1][position_2] == player1)
	{
		playable_direction[i][j][0] = 1;
		playable = TRUE;
	}

	// Test UP path
	position_1 = i - 1, position_2 = j;
	while (valid_position(position_1, position_2) && board[position_1][position_2] == player2)
		position_1 -= 1;

	if (valid_position(position_1, position_2) && distance(i, j, position_1, position_2) > 1 && board[position_1][position_2] == player1)
	{
		playable_direction[i][j][1] = 1;
		playable = TRUE;
	}

	// Test UR diagonal
	position_1 = i - 1, position_2 = j + 1;
	while (valid_position(position_1, position_2) && board[position_1][position_2] == player2)
	{
		position_1 -= 1;
		position_2 += 1;
	}
	if (valid_position(position_1, position_2) && distance(i, j, position_1, position_2) > 1 && board[position_1][position_2] == player1)
	{
		playable_direction[i][j][2] = 1;
		playable = TRUE;
	}

	// Test LEFT path
	position_1 = i, position_2 = j - 1;
	while (valid_position(position_1, position_2) && board[position_1][position_2] == player2)
		position_2 -= 1;

	if (valid_position(position_1, position_2) && distance(i, j, position_1, position_2) > 1 && board[position_1][position_2] == player1)
	{
		playable_direction[i][j][3] = 1;
		playable = TRUE;
	}

	// Test RIGHT path
	position_1 = i, position_2 = j + 1;
	while (valid_position(position_1, position_2) && board[position_1][position_2] == player2)
		position_2 += 1;

	if (valid_position(position_1, position_2) && distance(i, j, position_1, position_2) > 1 && board[position_1][position_2] == player1)
	{
		playable_direction[i][j][4] = 1;
		playable = TRUE;
	}

	// Test DL diagonal
	position_1 = i + 1, position_2 = j - 1;
	while (valid_position(position_1, position_2) && board[position_1][position_2] == player2)
	{
		position_1 += 1;
		position_2 -= 1;
	}
	if (valid_position(position_1, position_2) && distance(i, j, position_1, position_2) > 1 && board[position_1][position_2] == player1)
	{
		playable_direction[i][j][5] = 1;
		playable = TRUE;
	}

	// Test DOWN path
	position_1 = i + 1, position_2 = j;
	while (valid_position(position_1, position_2) && board[position_1][position_2] == player2)
		position_1 += 1;

	if (valid_position(position_1, position_2) && distance(i, j, position_1, position_2) > 1 && board[position_1][position_2] == player1)
	{
		playable_direction[i][j][6] = 1;
		playable = TRUE;
	}

	// Test DR diagonal
	position_1 = i + 1, position_2 = j + 1;
	while (valid_position(position_1, position_2) && board[position_1][position_2] == player2)
	{
		position_1 += 1;
		position_2 += 1;
	}
	if (valid_position(position_1, position_2) && distance(i, j, position_1, position_2) > 1 && board[position_1][position_2] == player1)
	{
		playable_direction[i][j][7] = 1;
		playable = TRUE;
	}
	return playable;
}

void draw( )
{	
	int i,j;
    printf( "     %c     %c     %c     %c     %c     %c     %c     %c\n", col_names[0], col_names[1], col_names[2], col_names[3], col_names[4], col_names[5], col_names[6], col_names[7] );
    printf( "   _____ _____ _____ _____ _____ _____ _____ _____\n" );
    for ( i=0; i<8; ++i )
    {
        printf( "  |     |     |     |     |     |     |     |     |\n" );
        printf( "%c |", row_names[i] );
        for ( j=0; j<8; ++j )
        {
            if ( board[i][j] == WHITE )
            {
                printf( "%s", WHITE_MARKER );
            } else if ( board[i][j] == BLACK )
            {
                printf( "%s", BLACK_MARKER );
            } else if ( board[i][j] == PLAYABLE )
            {
                printf( "%s", ABLE_MARKER );
            } else
            {
                printf( "%s", EMPTY_MARKER );
            }
            printf("|");
        }
        printf( "\n" );
        printf( "  |_____|_____|_____|_____|_____|_____|_____|_____|\n" );
    }
    printf( "\n" );
}

void display_wrong_move( )
{
    if ( wrong_move )
    {
    	printf("\n");
        printf( "놓을 수 없는 공간입니다. \n\n" );
  
        wrong_move = FALSE;
    }
}

void display_current_player( )
{
    printf( "이번 차례는 :" );
    if ( player1 == WHITE )
        printf( "%s 입니다", WHITE_MARKER );
    else
        printf( "%s 입니다", BLACK_MARKER );
    printf( "\n" );
}

void change_current_player( )
{
    player1 = ( player1 + 1 ) % 2;
}

void prompt_move( int *p_row, int *p_column )
{
    printf( "행 [0-7] 과 열 [0-7] 을 띄어 쓰기와 함께 입력해 주세요.  (eg.: 2 4).\n" );
    scanf( "%d %d", p_row, p_column );
}



void make_next_move( )
{
    int row, column;
    prompt_move( &row, &column );
    if ( valid_position( row, column ) && board[row][column] == PLAYABLE )
    {
        board[row][column] = player1;
        scores[player1]++;
        capture_pieces( row, column );
        change_current_player(  );
    }
    else wrong_move = TRUE;
}

void display_winner( )
{
    printf( "Final score:\n%s: %d %s: %d\n", WHITE_MARKER, scores[WHITE], BLACK_MARKER, scores[BLACK] );
    if ( scores[WHITE] > scores[BLACK] )
        printf( "%s 승리.\n", WHITE_MARKER );
    else if ( scores[WHITE] < scores[BLACK] )
        printf( "%s 승리.\n", BLACK_MARKER );
    else
        printf( "Draw game.\n" );
}

void display_score( )
{
    printf( "%s: %d %s: %d\n", WHITE_MARKER, scores[WHITE], BLACK_MARKER, scores[BLACK] );
}

int main( )
{
    init_game();
    while ( !game_ended ){
        if ( !wrong_move ) mark_playable_positions( );
        if ( !has_valid_move )
        {
            if ( skipped_turn )
            {
                game_ended = 1;
                draw( );
                continue;
            }
            skipped_turn = 1;
            change_current_player( );
            continue;
        }
        skipped_turn = 0;
        draw( );
        display_score( );
        display_current_player( );
        display_wrong_move( );
        make_next_move( );
    }
    display_winner( );
}
