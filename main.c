#include <othello.h>

struct Gameboard{ 
	unsigned char board[64]; 
 	unsigned score[3];// 0 : empty 1 : white 2 : black unsigned hint; 
 	unsigned hint;
  
};
void DisplayBoard(Gameboard &board)
{
	unsigned int ui,uj;
	system("cls");
	printf(" 1 2 3 4 5 6 7 8 ");
	printf(" ¡Ü : ¡Û = %d : %d\n", board.score[1], board.score[2]);

	for(ui = 0 ; ui < 8 ; ui++)
	{
		printf(" +----+----+----+----+----+----+----+----+\n");
		printf(" %c |", ui+'a');
		for(uj=0;uj<8;uj++)
		{
			unsigned char v= board.board[ui*8+uj];
			if(v==1)
				printf(" ¡Ü |");
			else if(v==2)
				printf(" ¡Û |");
			else if(v==0)
				printf(" ¡Ø |")
			else 
				printf("    |");
		}
		putchar('\n');

	}
	printf(" +----+----+----+----+----+----+----+----+\n");


}

void PutBoard(Gameboard &board, unsigned int index, unsigned int turn)
{
	unsigned int ui;
	unsigned int r;
	unsigned int ant i=(turn ^ 0x3);
	static int dxy[8] = { -8, -7, 1, 9, 8, 7, -1, -9 };

	if(index != 64) { 
		board.board[index] = turn; 
		board.score[0]--; 
		board.score[turn]++; 
		for(ui = 0 ; ui < 8 ; ui++) 
		{	r = index + dxy[ui]; 
			int k; 
			for( k = 1 ; k < limit[index][ui] ; ++k)
			{ 	if(board.board[r] != anti) 
					break;
				r += dxy[ui]; 
			} 
			if(board.board[r] == turn)
			{
				while(--k) 
				{ 	r -= dxy[ui]; 
					board.board[r] = turn; 
					board.score[turn]++; 
					board.score[anti]--; 
				} 
			} 
		} 
	}
	if(index != 64)
	{
		board.board[index]=turn;
		board.score[0]--;
		board.score[turn]++;
		for(ui=0;ui<8;ui++)
		{
			r=index+dxy[ui];
			int k;
			for(k=1;k<limit[index][ui];++k)
			{
				if(board.board[r]!=anti)
					break;
				r+=dxy[ui];
			}
			
			if(board.board[r]==turn)
			{
				while(--k)
				{
					r-=dxy[ui];
					board.board[r]=turn;
					board.score[turn]++;
					board.score[ant i]--;
					
				}
			}
		}
	}
	
	
	
	board.hint = 0;
	for(index=0;index<64;index++)
	{
		if(board.board[index]!=3&&board.board[index]!=0)
			continue;
		board.board[index]=3;
		for(ui=0;ui<8<ui++)
		{
			r=index+dxy[ui];
			int k;
			for(k=1;k<limint[index][ui];k++)
			{
				if(board.board[r]!=turn)
					break;
				r+=dxy[ui];
			}
			if(k!=1&&board.board[r]==ant i)
			{
				board.board[index]=0;
				board.hint++;
				break;
			}
			}	
		
	}	
}

void()

