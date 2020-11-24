#define FALSE 0
#define TRUE  1


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


int able(int i, int j)//놓을 수 있는 칸인지 체크하는 함수 
{
	memset(playable_direction[i][j], 0, 8);
	if (!valid_position(i, j)) return FALSE;
	if (board[i][j] != EMPTY) return FALSE;
	int playable = FALSE;

	int player2 = (player1 + 1) % 2;

	// 왼쪽 위 대각선 체크
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

	// 위칸 체크 
	position_1 = i - 1, position_2 = j;
	while (valid_position(position_1, position_2) && board[position_1][position_2] == player2)
		position_1 -= 1;

	if (valid_position(position_1, position_2) && distance(i, j, position_1, position_2) > 1 && board[position_1][position_2] == player1)
	{
		playable_direction[i][j][1] = 1;
		playable = TRUE;
	}

	
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

	// 왼쪽 칸 체크 
	position_1 = i, position_2 = j - 1;
	while (valid_position(position_1, position_2) && board[position_1][position_2] == player2)
		position_2 -= 1;

	if (valid_position(position_1, position_2) && distance(i, j, position_1, position_2) > 1 && board[position_1][position_2] == player1)
	{
		playable_direction[i][j][3] = 1;
		playable = TRUE;
	}

	// 오른쪽 칸 체크 
	position_1 = i, position_2 = j + 1;
	while (valid_position(position_1, position_2) && board[position_1][position_2] == player2)
		position_2 += 1;

	if (valid_position(position_1, position_2) && distance(i, j, position_1, position_2) > 1 && board[position_1][position_2] == player1)
	{
		playable_direction[i][j][4] = 1;
		playable = TRUE;
	}

	// 오른쪽 아래 사선 체크 
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

	// 아래 칸 체크 
	position_1 = i + 1, position_2 = j;
	while (valid_position(position_1, position_2) && board[position_1][position_2] == player2)
		position_1 += 1;

	if (valid_position(position_1, position_2) && distance(i, j, position_1, position_2) > 1 && board[position_1][position_2] == player1)
	{
		playable_direction[i][j][6] = 1;
		playable = TRUE;
	}

	// 오른쪽 아래 칸 체크 
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

