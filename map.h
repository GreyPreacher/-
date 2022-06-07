#ifndef MAP_H
#define MAP_H

#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<math.h>
#include <windows.h>
#include<stdlib.h>
#include<graphics.h>
#include <easyx.h>
#include<mmsystem.h>//多媒体库

void draw_menu();  //主菜单的绘制
void draw_developer();  //开发人员图的绘制
void main_loop();  //主菜单的循环
void draw_ranking();  //绘制排行榜
int game();       //进入游戏，正式游玩
void asnake();
void process();
void movedir();
void foodmove();

#endif 
