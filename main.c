#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE_MARKER    "  �� "
#define BLACK_MARKER    "  �� "
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

int main( )//������ �����ϴ� ���� �Լ� 
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


void mark_playable_positions( )//���� ������ �� �ִ� ���� ǥ�� 
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

void draw( )//�������� �׸��� �Լ� 
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

void display_wrong_move( )//���� �� ���� ������ ����ڰ� ���� ������ ��� 
{
    if ( wrong_move )
    {
    	printf("\n");
        printf( "���� �� ���� �����Դϴ�. \n\n" );
  
        wrong_move = FALSE;
    }
}

void display_current_player( )//���� ������ ����ڸ� ǥ���ϰ� �� ������� ���ʿ� �µ��� ���� ���� ���߾� �ش�. 
{
    printf( "�̹� ���ʴ� :" );
    if ( player1 == WHITE )
        printf( "%s �Դϴ�", WHITE_MARKER );
    else
        printf( "%s �Դϴ�", BLACK_MARKER );
    printf( "\n" );
}

void change_current_player( )//����ڴ� 2���̹Ƿ� ������ ���� ���� ���ʸ� �ν��Ѵ� 
{
    player1 = ( player1 + 1 ) % 2;
}

void prompt_move( int *p_row, int *p_column )
{
    printf( "�� [0-7] �� �� [0-7] �� ��� ����� �Բ� �Է��� �ּ���.  (eg.: 2 4).\n" );
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

void display_winner( )//���� ��� ���� �Ŀ� �¸��� ����ڸ� ǥ���Ѵ�. 
{
    printf( "Final score:\n%s: %d %s: %d\n", WHITE_MARKER, scores[WHITE], BLACK_MARKER, scores[BLACK] );
    if ( scores[WHITE] > scores[BLACK] )
        printf( "%s �¸�.\n", WHITE_MARKER );
    else if ( scores[WHITE] < scores[BLACK] )
        printf( "%s �¸�.\n", BLACK_MARKER );
    else
        printf("���º�.\n" );
}

void display_score( )//���� ���� ǥ�� 
{
    printf( "%s: %d %s: %d\n", WHITE_MARKER, scores[WHITE], BLACK_MARKER, scores[BLACK] );
}

void capture_pieces(int i, int j)//������ ���⿡  �� ����  
{
	int player2 = (player1 + 1) % 2;
	int position_1, position_2;

	// ���� �� �밢�� 
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

	// ��ĭ üũ 	
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

	// ������ ��ĭ üũ 
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

	// ���� ĭ üũ
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

	// ������ �Ʒ� �缱 üũ
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

	// �Ʒ� ĭ üũ
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

	// ������ �Ʒ� ĭ üũ
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




