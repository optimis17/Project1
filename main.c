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

const char *row_names = "";
const char *col_names = "";

char board[8][8];
int playable_direction[8][8][8];
int player1,player2;
int game_ended = FALSE;
int skipped_turn = FALSE;
int wrong_move = FALSE;
int has_valid_move = FALSE;
int scores[2];
int black_score = 2;

int main( )//게임을 진행하는 메인 함수 
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


void mark_playable_positions( )//돌을 뒤집을 수 있는 공간 표시 
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

void draw( )//보드판을 그리는 함수 
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

void display_wrong_move( )//놓을 수 없는 공간에 사용자가 돌을 놓았을 경우 
{
    if ( wrong_move )
    {
    	printf("\n");
        printf( "놓을 수 없는 공간입니다. \n\n" );
  
        wrong_move = FALSE;
    }
}

void display_current_player( )//현재 차례인 사용자를 표시하고 그 사용자의 차례에 맞도록 돌의 색을 맞추어 준다. 
{
    printf( "이번 차례는 :" );
    if ( player1 == WHITE )
        printf( "%s 입니다", WHITE_MARKER );
    else
        printf( "%s 입니다", BLACK_MARKER );
    printf( "\n" );
}

void change_current_player( )//사용자는 2명이므로 다음과 같이 다음 차례를 인식한다 
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

void display_winner( )//돌을 모두 놓은 후에 승리한 사용자를 표시한다. 
{
    printf( "Final score:\n%s: %d %s: %d\n", WHITE_MARKER, scores[WHITE], BLACK_MARKER, scores[BLACK] );
    if ( scores[WHITE] > scores[BLACK] )
        printf( "%s 승리.\n", WHITE_MARKER );
    else if ( scores[WHITE] < scores[BLACK] )
        printf( "%s 승리.\n", BLACK_MARKER );
    else
        printf("무승부.\n" );
}

void display_score( )//현재 점수 표시 
{
    printf( "%s: %d %s: %d\n", WHITE_MARKER, scores[WHITE], BLACK_MARKER, scores[BLACK] );
}

void capture_pieces(int i, int j)//선택한 방향에  돌 놓기  
{
	int player2 = (player1 + 1) % 2;
	int position_1, position_2;

	// 왼쪽 위 대각선 
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

	// 위칸 체크 	
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

	// 오른쪽 위칸 체크 
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

	// 왼쪽 칸 체크
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

	// 오른쪽 아래 사선 체크
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

	// 아래 칸 체크
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

	// 오른쪽 아래 칸 체크
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




