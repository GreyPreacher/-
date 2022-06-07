#include "map.h"

void main_loop(){
	int flag=0;  //设置flag确认当前的状态，防止进入无限内嵌的循环中
	int goal=0;
	while(1){
		MOUSEMSG m;
		m = GetMouseMsg();
		if(m.uMsg==WM_LBUTTONDOWN){
			if(m.x>=550 && m.x<=630 && m.y<=325 && m.y>=290){//退出游戏选项
				closegraph();
				break;
			}
			else if(m.x>=550 && m.x<=630 && m.y<=225 && m.y>=190){//排行榜选项
				cleardevice();
				flag=2;
				draw_ranking();
				break;
			}
			else if(m.x>=550 && m.x<=630 && m.y<=275 && m.y>=240){//开发者显示选项
				cleardevice();
				draw_developer();
				flag=3;
				break;
			}
			else if(m.x>=550 && m.x<=630 && m.y>=140 && m.y<=175){//开始游戏选项
				flag=1;
				cleardevice();
				goal=game();
				break;
			}
		}
	}
	if (flag==2){
		while(1){
			MOUSEMSG m;
			m = GetMouseMsg();
			if(m.uMsg==WM_LBUTTONDOWN){
				if(m.x>=240 && m.x<=400 && m.y>=440 && m.y<=475){
					cleardevice();
					draw_menu();
					flag=5;
					break;
				}
			}
		}
	}
	if (flag==3){
		while(1){
			MOUSEMSG m;
			m = GetMouseMsg();
			if(m.uMsg==WM_LBUTTONDOWN){
				if(m.x>=240 && m.x<=400 && m.y>=345 && m.y<=370){
					cleardevice();
					draw_menu();
					flag=5;
					break;
				}
			}
		}
	}
	if(flag==5){
		main_loop();
	}
	if(flag==1){
		cleardevice();
		IMAGE bg;
		loadimage(&bg,_T("image/snakebg.jpg"));
		putimage(0, 0, &bg);

		settextcolor(BLACK);
		settextstyle(48, 0, _T("黑体"));
		TCHAR tishi1[]=_T("您的得分为：");
		outtextxy(100,150, tishi1);
		TCHAR score[5];
		_stprintf(score,_T("%d"),goal);
		outtextxy(400,150, score);
		FILE *fp;
		errno_t err;
		if ((err = fopen_s(&fp, "ranking.txt", "r")) !=0)
		{
			TCHAR error[]=_T("Cannot open the file!");
			outtextxy(200,300,error);
			getchar();
			exit(0);                           
		}
		int num[8];
		for (int i = 0; i < 8; i++) {
			fscanf_s(fp, "%d", &num[i]);
		}
		fclose(fp);
		int rank=8;
		for (int i=0;i<8;i++){
			if (goal>num[i]){
				TCHAR congradulation[]=_T("恭喜您登上排行榜");
				outtextxy(100,250, congradulation);
				rank=i;
				break;
			}
		}
		if(rank<8){
			for(int i=7;i>rank;i--){
				num[i]=num[i-1];
			}
			num[rank]=goal;
			if ((err = fopen_s(&fp, "ranking.txt", "w")) !=0){
				TCHAR error[]=_T("Cannot open the file!");
				outtextxy(200,300,error);
				getchar();
				exit(0);                           
			}
			for(int i=0;i<8;i++){
				fprintf(fp,"%d\n",num[i]);
			}
			fclose(fp);
		}
		settextstyle(16, 0, _T("宋体"));
		TCHAR exit[]=_T("请按回车键退出");
		outtextxy(300,400, exit);
		getchar();
		closegraph();
	}
}

void draw_menu(){
	IMAGE bg;
	loadimage(&bg,_T("image/snakebg.jpg"));
	putimage(0, 0, &bg);
	IMAGE main_menu;
	loadimage(&main_menu,_T("image/main_menu.jpg"));
	putimage(0,0,&main_menu);

	setbkmode(1);
	setlinecolor(BLACK);
	settextcolor(BLACK);
	settextstyle(21, 0, _T("宋体"));
	TCHAR tishi1[]=_T("开始游戏");
	TCHAR tishi2[]=_T("排行榜");
	TCHAR tishi3[]=_T("开发人员");
	TCHAR tishi4[]=_T("退出游戏");
	outtextxy(555,150,tishi1);
	outtextxy(555,200,tishi2);
	outtextxy(555,250,tishi3);
	outtextxy(555,300,tishi4);
}

void draw_ranking(){
	IMAGE sand;
	loadimage(&sand,_T("image/developer_background.jpg"));
	putimage(0,0,&sand);

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	setlinecolor(BLACK);

	FILE *fp;
	errno_t err;
	if ((err = fopen_s(&fp, "ranking.txt", "r")) !=0)
    {
        TCHAR error[]=_T("Cannot open the file!");
		outtextxy(200,300,error);
		getchar();
        exit(0);                           
    }
	int num[8];
	for (int i = 0; i < 8; i++) {
		fscanf_s(fp, "%d", &num[i]);
    }
	fclose(fp);
	settextstyle(16, 0, _T("宋体"));
	TCHAR announcement[]=_T("排行榜");
	outtextxy(285,100,announcement);

	TCHAR n1[]=_T("1");
	TCHAR n2[]=_T("2");
	TCHAR n3[]=_T("3");
	TCHAR n4[]=_T("4");
	TCHAR n5[]=_T("5");
	TCHAR n6[]=_T("6");
	TCHAR n7[]=_T("7");
	TCHAR n8[]=_T("8");
	outtextxy(200,150,n1);
	outtextxy(200,180,n2);
	outtextxy(200,210,n3);
	outtextxy(200,240,n4);
	outtextxy(200,270,n5);
	outtextxy(200,300,n6);
	outtextxy(200,330,n7);
	outtextxy(200,360,n8);

	TCHAR rank1[5];
	_stprintf(rank1,_T("%d"),num[0]);
	TCHAR rank2[5];
	_stprintf(rank2,_T("%d"),num[1]);
	TCHAR rank3[5];
	_stprintf(rank3,_T("%d"),num[2]);
	TCHAR rank4[5];
	_stprintf(rank4,_T("%d"),num[3]);
	TCHAR rank5[5];
	_stprintf(rank5,_T("%d"),num[4]);
	TCHAR rank6[5];
	_stprintf(rank6,_T("%d"),num[5]);
	TCHAR rank7[5];
	_stprintf(rank7,_T("%d"),num[6]);
	TCHAR rank8[5];
	_stprintf(rank8,_T("%d"),num[7]);
	outtextxy(400,150,rank1);
	outtextxy(400,180,rank2);
	outtextxy(400,210,rank3);
	outtextxy(400,240,rank4);
	outtextxy(400,270,rank5);
	outtextxy(400,300,rank6);
	outtextxy(400,330,rank7);
	outtextxy(400,360,rank8);

	rectangle(240,440,400,475);
	TCHAR tishi3[]=_T("点击此处回到主界面");
	outtextxy(250,450,tishi3);
}

void draw_developer(){
	IMAGE sand;
	loadimage(&sand,_T("image/developer_background.jpg"));
	putimage(0,0,&sand);

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(16, 0, _T("宋体"));
	TCHAR tishi1[]=_T("信息管理学院 张宵霆 191810245");
	outtextxy(250,220,tishi1);
	TCHAR tishi2[]=_T("外国语学院   肖滃然 181108123");
	outtextxy(250,260,tishi2);

	setlinecolor(BLACK);
	rectangle(240,340,400,375);
	TCHAR tishi3[]=_T("点击此处回到主界面");
	outtextxy(250,350,tishi3);
}
