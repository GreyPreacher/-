#include"map.h"
#define _CRT_SECURE_NO_WARNINGS

static int goal=695;
static int GAME_OVER=0;

typedef struct coor
{
    int x;
    int y;
}coor;

struct snake
{
    int num;
    coor loc[500];
    char dir;

}snake;

struct food
{
    coor loc;
    int flag;
}food;

enum way
{
    right=72,
    left=75,
    down=77,
    up=80
};


int game(){
	initgraph(700, 500);
    asnake(); 
    while (1){       
        process();
        while (_kbhit()){
			movedir();
		}
        if (food.flag == 0){
			foodmove();
		}
		if(GAME_OVER==1){
			return goal;
		}
    }
    closegraph();
}

void asnake(){	
    snake.num = 3;
    snake.dir = right;
    snake.loc[2].x = 0;
    snake.loc[2].y = 0;
    snake.loc[1].x = 10;
    snake.loc[1].y = 0;
    snake.loc[0].x = 20;
    snake.loc[0].y = 0;
    food.flag = 0;
}

void foodmove(){   	
	food.loc.x = rand() % 70*10;
    food.loc.y = rand() % 50*10;
    food.flag = 1;

    for (int i = 0; i > snake.num; i++){
		if (food.loc.x == snake.loc[i].x && food.loc.y == snake.loc[i].y){
			food.loc.x = rand() % 70*10;
            food.loc.y = rand() % 50*10;
        }
    }
}
void process(){	
	IMAGE bg;
	loadimage(&bg,_T("image/snakebg.jpg"));
	putimage(0, 0, &bg);

    fillrectangle(food.loc.x, food.loc.y, food.loc.x + 10, food.loc.y + 10);

    for (int i = 0; i < snake.num; i++){
        setlinecolor(BLACK);
        fillrectangle(snake.loc[i].x, snake.loc[i].y, snake.loc[i].x + 10, snake.loc[i].y + 10);        
    }

	setbkmode(0);
	TCHAR score_hint[]=_T("当前得分:");
    outtextxy(510, 20, score_hint);
	TCHAR score[5];
	_stprintf(score,_T("%d"),goal);
    outtextxy(600, 20, score);

    for (int i = 1; i < snake.num; i++)
    {
        if (snake.loc[0].x > 700 || snake.loc[0].x < 0 || snake.loc[0].y > 500 || snake.loc[0].y<0
		||snake.loc[0].x == snake.loc[i].x &&snake.loc[0].y == snake.loc[i].y){	
	
			TCHAR tishi1[]=_T("Game Over");
			outtextxy(250, 250, tishi1);
			TCHAR tishi2[]=_T("请按回车键退出游戏 ");
			outtextxy(150, 300, tishi2);
			getchar();
			GAME_OVER=1;
			break;
        }
    }

    if (snake.loc[0].x == food.loc.x && snake.loc[0].y == food.loc.y)
    {
        snake.num++;
        food.flag = 0;
        goal += 5;
    }

    for (int i = snake.num-1; i >0; i--)
    {
        snake.loc[i].x = snake.loc[i-1].x;
        snake.loc[i].y = snake.loc[i-1].y;
    }

    switch (snake.dir)
    {
    case right:
        snake.loc[0].x += 10;
        break;
    case left:
        snake.loc[0].x -= 10;
        break;
    case down:
        snake.loc[0].y += 10;
        break;
    case up:
        snake.loc[0].y -= 10;
        break;
    }
    Sleep(40); 
}

void movedir()
{
    char ch = 0;
    ch = _getch();
    switch (ch)
    {
    case 72:
        snake.dir = up;
        break;
    case 75: 
        snake.dir = left;
        break;
    case 77:       
        snake.dir = right;
        break;
    case 80:
        snake.dir = down;
        break;
    }
}
