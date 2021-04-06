#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<Windows.h>
#include<mmsystem.h>
#include "graphics.h"
#pragma comment(lib, "Winmm.lib")

#define  INIT     100
#define  WIDTH     30

#define  DOWN      80
#define  LEFT      75
#define  RIGHT     77
#define  ROTATE      72
#define  EXIT      27
#define    PUSH_DOWN 32    
#define PAUSE 'p'

#define  DELAY_SHIFT   35

void     Make_Block(int c_index, int r_index, int mode);

char    Sel_Blk[][4][4] = {
	/*첫 번째 블록*/
	{ { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 1, 1, 0 }, { 0, 0, 0, 0 } },
	{ { 1, 1, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 0, 0, 0, 0 } },
	{ { 1, 1, 1, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 1, 0 }, { 0, 0, 1, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 0 } },
	/* 두 번째 블록  */
	{ { 0, 0, 0, 0 }, { 0, 0, 1, 0 }, { 1, 1, 1, 0 }, { 0, 0, 0, 0 } },
	{ { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 1, 0, 0 }, { 0, 0, 0, 0 } },
	{ { 1, 1, 1, 0 }, { 1, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
	{ { 0, 1, 1, 0 }, { 0, 0, 1, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 0 } },
	/* 세 번째 블록  */
	{ { 0, 0, 0, 0 }, { 0, 1, 0, 0 }, { 1, 1, 1, 0 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0, 1, 0, 0 } },
	{ { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 0 }, { 0, 1, 0, 0 } },
	{ { 0, 0, 0, 0 }, { 0, 1, 0, 0 }, { 1, 1, 0, 0 }, { 0, 1, 0, 0 } },
	/* 네 번째 블록 */
	{ { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 } },
	{ { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1 }, { 0, 0, 0, 0 } },
	{ { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 } },
	{ { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1 }, { 0, 0, 0, 0 } },
	/* 다섯 번째 블록 */
	{ { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
	{ { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
	{ { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
	{ { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
	/* 여섯 번째 블록  */
	{ { 0, 0, 0, 0 }, { 0, 1, 1, 0 }, { 1, 1, 0, 0 }, { 0, 0, 0, 0 } },
	{ { 0, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 0 }, { 0, 1, 1, 0 }, { 1, 1, 0, 0 }, { 0, 0, 0, 0 } },
	{ { 0, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 0 } },
	/* 일곱 번째 블록  */
	{ { 0, 0, 0, 0 }, { 1, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 1, 0 }, { 0, 1, 1, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 0, 0 }, { 1, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 0 } },
	{ { 0, 0, 1, 0 }, { 0, 1, 1, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, 0 } },
};
int rv1, rv2, rv3, Ax = 0, Ay = 0;
int SCORE = 0, check_down = 0, check, START;
int numscore = 0, combo=0,maxcombo=0;
char score[20] = { '0', '0', '0', '0', '0', '0', '0', '0' }, chpause[20] = {"PAUSE"};
int ROW = 0, COL = 0;
int **position;
void Block_Making(int c_cur, int r_cur, int mode)
{
	int i, j, temp;
	if (mode)
	{
		rv1 = rand() % 100;
		if (rv1 < 14)
		{
			rv2 = 1;
			rv3 = rv2 + 1;
		}
		else if (rv1 < 29)
		{
			rv2 = 2;
			rv3 = rv2 + 1;
		}
		else if (rv1 < 44)
		{
			rv2 = 3;
			rv3 = rv2 + 1;
		}
		else if (rv1 < 59)
		{
			rv2 = 4;
			rv3 = rv2 + 1;
		}
		else if (rv1 < 74)
		{
			rv2 = 5;
			rv3 = rv2 + 1;
		}
		else if (rv1 < 89)
		{
			rv2 = 6;
			rv3 = rv2 + 1;
		}
		else
		{
			rv2 = 0;
			rv3 = rv2 + 1;
		}

		rv2 = rv2 * 4;
	}
	for (i = 0; i < 4; i++)
	{
		temp = c_cur;
		for (j = 0; j < 4; j++)
		{
			if (Sel_Blk[rv2][i][j] == 1)
			{
				Make_Block(temp, i + r_cur, rv3);
			}
			temp++;
			
		}
	}
}
void Block_down(int del_row)
{
	int i, j;

	for (i = del_row; i >= 1; i--)
	{
		for (j = 1; j < COL + 1; j++)
		{

			position[i][j] = position[i - 1][j];
			
		}
	}
	for (i = 0; i < ROW; i++)
	{
		for (j = 1; j < COL + 1; j++)
		{
			Make_Block(j, i, position[i][j]);

		}
	}
	if (check == 0)
	{
		Beep(523, 100);
		Sleep(100);
		Beep(587, 100);
		Sleep(100);
		Beep(1046, 100);
		Sleep(100);
		if (combo == 0)
		{
			setcolor(WHITE);
			outtextxy(INIT + WIDTH*COL + 1 + 40 + WIDTH, INIT + ROW + 1 - WIDTH + 100, "1 COMBO    ");
			numscore++;
		}
		else if (combo == 1)
		{
			setcolor(WHITE);
			outtextxy(INIT + WIDTH*COL + 1 + 40 + WIDTH, INIT + ROW + 1 - WIDTH + 100, "2 COMBO !   ");
			numscore += 3;
		}
		else if (combo == 2)
		{
			setcolor(WHITE);
			outtextxy(INIT + WIDTH*COL + 1 + 40 + WIDTH, INIT + ROW + 1 - WIDTH + 100, "3 COMBO !!  ");
			numscore += 5;
		}
		else if (combo == 3)
		{
			setcolor(WHITE);
			outtextxy(INIT + WIDTH*COL + 1 + 40 + WIDTH, INIT + ROW + 1 - WIDTH + 100, "4 COMBO !!!");
			numscore += 10;
		}

		j = 100000;
		for (i = 0; i < 6; i++)
		{
			score[i] = ((numscore / j) % 10) + 48;
			j /= 10;
		}
		setcolor(WHITE);
		outtextxy(INIT + WIDTH*COL + 1 + 85 + WIDTH, INIT + ROW + 1 - WIDTH, score);
		combo++;
	}
}
void Block_control()
{
	int i, j, k, sum = 0;
	for (i = ROW - 1; i >= 1; i--)
	{
		for (k = 0; k < 4; k++)
		{

			sum = 0;
			for (j = 1; j < COL + 1; j++)
			{
				if (position[i][j] != 0)
				{
					sum++;
					if (sum == COL)
					{
						Block_down(i);
					}
				}
			}
		}
	}
}


void Block_delete(int c_cur, int r_cur)
{
	int i, j, temp;
	for (i = 0; i < 4; i++)
	{
		temp = c_cur;
		for (j = 0; j < 4; j++)
		{
			if (Sel_Blk[rv2][i][j] == 1)
			{
				Make_Block(temp, i + r_cur, 0);
			}
			temp++;
		}
	}
}
int Overlap(int Ax, int Ay)
{
	int i, j, temp = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (Sel_Blk[rv2][i][j] == 1 && position[Ax + i][Ay + j] != 0)
			{
				temp = 1; 
			}
		}
	}
	return temp;
}

void  main()
{
	int  i, j, c_cur, r_cur, next = 0, l_cur = 0, temp = 0, temp2 = 0;
	int brk = 0;
	int DELAY_MSEC;
	char ch, score_name[20] = { "Score: " };
	while (1)
	{
		printf("Select the level(speed) \n[1: faster] [2: mideum] [3: slowly] \n");
		scanf("%d", &DELAY_MSEC);
		if (DELAY_MSEC == 1 || DELAY_MSEC == 2 || DELAY_MSEC == 3)
			break;
	}
	DELAY_MSEC *= 250;
	while (1)
	{
		printf("ROW and COL (10~25) \nEnter ROW: ");
		scanf("%d", &ROW);
		printf("Enter COL: ");
		scanf("%d", &COL);
		if (ROW >= 10 && ROW <= 25 && COL >= 10 && COL <= 25)
			break;
	}
	PlaySound("sound.wav", NULL, SND_ASYNC | SND_LOOP);
	//C드라이브 \a폴더에 있는 wav파일을 비동기적+반복재생
	//SND_ASYNC 비동기적 재생, 재생중에도 프로그램이 멈추지 않고 돌아감
	//SND_LOOP 반복재생 SND_ASYNC랑 같이 사용해야댐 

	START = COL / 2;
	srand(time(NULL));
	position = (int**)calloc(sizeof(int*), ROW + 1);
	for (i = 0; i < ROW + 1; i++)
		position[i] = (int *)calloc(sizeof(int), COL + 2);

	
	initwindow(COL*WIDTH + 500, ROW*WIDTH + 200, "Sample");

	setcolor(WHITE);

//	line(INIT - 1 + 30, INIT, INIT - 1 + 30, (INIT + WIDTH*ROW + 1));
//	line((INIT + WIDTH*COL + 1 + 30), INIT, (INIT + WIDTH*COL + 1 + 30), (INIT + WIDTH*ROW + 1));
//	line(INIT - 1 + 30, (INIT + WIDTH*ROW + 1), (INIT + WIDTH*COL + 1 + 30), (INIT + WIDTH*ROW + 1));


	line((INIT + WIDTH*COL + 1 + 30) + 30, INIT - 10, (INIT + WIDTH*COL + 1 + 30) + 30, (INIT + ROW + 1));
	line((INIT + WIDTH*COL + 1 + 30) + 300, INIT - 10, (INIT + WIDTH*COL + 1 + 30) + 300, (INIT + ROW + 1));
	line((INIT + WIDTH*COL + 1 + 30) + 300, INIT - 10, (INIT + WIDTH*COL + 1 + 30) + 30, INIT - 10);                        // top line
	line((INIT + WIDTH*COL + 1 + 30) + 30, (INIT + ROW + 1), (INIT + WIDTH*COL + 1 + 30) + 300, (INIT + ROW + 1));      // bottom line
	outtextxy(INIT + WIDTH*COL + 1 + 40 + WIDTH, INIT + ROW + 1 - WIDTH, score_name);
	outtextxy(INIT + WIDTH*COL + 1 + 85 + WIDTH, INIT + ROW + 1 - WIDTH, score);
	outtextxy(INIT + WIDTH*COL + 1 + 40 + WIDTH, INIT + ROW + 1 - WIDTH + 100, "0 COMBO");

	for (i = 0; i < ROW + 1; i++)
	{
		for (j = 0; j < COL + 2; j++)
		{
			
			if (i != ROW && j != 0 && j != COL + 1)
			{
				position[i][j] = 0;
				Make_Block(j, i, 0);
			}
			else
				position[i][j] = 1;
		}
	}
	
	c_cur = START; 
	r_cur = 0; 
	Block_Making(c_cur, r_cur, 1);
	for (;;){
		if (kbhit())
		{
			ch = getch();
			combo = 0;
			if (ch == DOWN)
			{
				next = r_cur + 1;
				temp = Overlap(next, c_cur);

				if (temp == 1)
				{
					int game_over = 0;
					game_over = Overlap(0, START);

					if (!game_over)
					{
						for (i = 0; i < 4; i++)
						{
							temp2 = c_cur;
							for (j = 0; j < 4; j++)
							{
								if (Sel_Blk[rv2][i][j] == 1)
								{
									position[i + r_cur][temp2] = rv3;
								}
								temp2++;
							}
						}
						Block_control();
						temp = 0;
						c_cur = START;
						r_cur = 0;
						Block_Making(c_cur, r_cur, 1);
					}
					else
					{
						setcolor(WHITE);
						outtextxy(INIT * 2, INIT + WIDTH*(ROW + 1), "!!   GAME OVER   !!");
						outtextxy(INIT * 2, INIT + WIDTH*(ROW + 2), "!!      Press  [ESC]     !!");
						PlaySound(NULL, NULL, NULL);
						PlaySound("death.wav", NULL, SND_ASYNC | SND_LOOP);
						break;
					}

				}
				else
				{
					Block_delete(c_cur, r_cur);
					Block_Making(c_cur, next, 0);
					r_cur = next;
				}
				delay(DELAY_SHIFT);
			}
			if (ch == LEFT)
			{
				next = c_cur - 1;
				temp = Overlap(r_cur, next);
			
				if (!temp) 
				{
					Block_delete(c_cur, r_cur);
					Block_Making(next, r_cur, 0);
					c_cur = next;
					delay(DELAY_SHIFT);
				}
				temp = 0;
			}
			if (ch == RIGHT)
			{
				next = c_cur + 1;
				temp = Overlap(r_cur, next);
	
				if (!temp)
				{
					Block_delete(c_cur, r_cur);
					Block_Making(next, r_cur, 0);
					c_cur = next;
					delay(DELAY_SHIFT);
				}
				temp = 0;
			}
			if (ch == ROTATE)
			{
				int temp3 = rv2;
				temp2 = rv2 / 4;
				temp2 *= 4;
				if ((rv2 + 1) <= (temp2 + 3))
					temp2 = rv2 + 1;
				rv2 = temp2;
				temp = Overlap(r_cur, c_cur);
				
				if (!temp)
				{
					rv2 = temp3;
					Block_delete(c_cur, r_cur);
					rv2 = temp2;
					Block_Making(c_cur, r_cur, 0);
					delay(DELAY_SHIFT);
				}
				else
					rv2 = temp3;
				temp = 0;
			}

			if (ch == PUSH_DOWN)
			{
				for (i = 0;; i++)
				{
					next = r_cur + 1 + i;

					temp = Overlap(next, c_cur);

					if (temp == 1)
					{
						r_cur = next - 1;
						int game_over = 0;//gogo
						game_over = Overlap(0, START);

						if (!game_over)
						{
							for (i = 0; i < 4; i++)
							{
								temp2 = c_cur;
								for (j = 0; j < 4; j++)
								{
									if (Sel_Blk[rv2][i][j] == 1)
									{
										position[i + r_cur][temp2] = rv3;
									}
									temp2++;
								}
							}
							Block_control();
							temp = 0;
							c_cur = START;
							r_cur = 0;
							Block_Making(c_cur, r_cur, 1);
						}
						else
						{
							setcolor(WHITE);
							outtextxy(INIT * 2, INIT + WIDTH*(ROW + 1), "!!   GAME OVER   !!");
							outtextxy(INIT * 2, INIT + WIDTH*(ROW + 2), "!!      Press  [ESC]     !!");
							PlaySound(NULL, NULL, NULL);
							PlaySound("death.wav", NULL, SND_ASYNC | SND_LOOP);
							brk = 1;
							break;
						}
						check = 1;
						Block_down(r_cur);
						check = 0;
						break;
					}
				}
				if (brk == 1)			break;
				
				Beep(587, 100);
				Sleep(100);
			}
			if (ch == PAUSE)
			{
				setcolor(WHITE);
				outtextxy(INIT + WIDTH*COL + 1 + 40 + WIDTH, INIT + ROW + 1 - WIDTH+200, chpause);
				while (1)
				{

					ch = getch();
					if (ch == PAUSE)
					{
						break;
					}
				}
				outtextxy(INIT + WIDTH*COL + 1 + 40 + WIDTH, INIT + ROW + 1 - WIDTH + 200, "                  ");
			}
		}

		else
		{
			delay(DELAY_MSEC);
			next = r_cur + 1;
			temp = Overlap(next, c_cur);
		
			if (temp == 1)
			{
				int game_over = 0;
				game_over = Overlap(0, START);
				
				if (!game_over)
				{
					for (i = 0; i < 4; i++)
					{
						temp2 = c_cur;
						for (j = 0; j < 4; j++)
						{
							if (Sel_Blk[rv2][i][j] == 1)
							{
								position[i + r_cur][temp2] = rv3;
							}
							temp2++;
						}
					}
					Block_control();

					temp = 0;
					c_cur = START;
					r_cur = 0;
					Block_Making(c_cur, r_cur, 1);
				}
				else
				{
					setcolor(WHITE);
					outtextxy(INIT * 2, INIT + WIDTH*(ROW + 1), "!!   GAME OVER   !!");
					outtextxy(INIT * 2, INIT + WIDTH*(ROW + 2), "!!      Press  [ESC]     !!");
					PlaySound(NULL, NULL, NULL);
					PlaySound("death.wav", NULL, SND_ASYNC | SND_LOOP);
					break;
				}

			}
			else
			{
				Block_delete(c_cur, r_cur);
				Block_Making(c_cur, next, 0);
				r_cur = next;
			}
		}
	}
	while (1){
		if (kbhit()){
			ch = getch();
			if (ch == EXIT)
			{
				exit(1);
			}
		}
	}
}
void  Make_Block(int c_index, int r_index, int mode)    
{
	int X, Y, mov[8];

	X = c_index;
	Y = r_index; 


	mov[0] = INIT + X*WIDTH;      mov[1] = INIT + Y*WIDTH;
	mov[2] = INIT + X*WIDTH;      mov[3] = INIT + (Y + 1)*WIDTH;
	mov[4] = INIT + (X + 1)*WIDTH;  mov[5] = INIT + (Y + 1)*WIDTH;
	mov[6] = INIT + (X + 1)*WIDTH;  mov[7] = INIT + Y*WIDTH;

	if (mode == 0){
		setcolor(BLACK);
		setfillstyle(SOLID_FILL, LIGHTGRAY);
	}
	else if (mode == 1){
		setcolor(RED);
		setfillstyle(SOLID_FILL, RED);
	}
	else if (mode == 2){
		setcolor(RED);
		setfillstyle(SOLID_FILL, YELLOW);
	}

	else if (mode == 3){
		setcolor(YELLOW);
		setfillstyle(SOLID_FILL, GREEN);
	}
	else if (mode == 4){
		setcolor(YELLOW);
		setfillstyle(SOLID_FILL, BLUE);
	}
	else if (mode == 5){
		setcolor(YELLOW);
		setfillstyle(SOLID_FILL, BLACK);
	}
	else if (mode == 6){
		setcolor(YELLOW);
		setfillstyle(SOLID_FILL, WHITE);
	}
	else if (mode == 7){
		setcolor(YELLOW);
		setfillstyle(SOLID_FILL, MAGENTA);
	}

	fillpoly(4, mov);
}