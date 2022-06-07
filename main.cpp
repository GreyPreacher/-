#include "map.h"
#pragma comment(lib,"winmm.lib")

int main(){
	initgraph(700, 500);
	PlaySound(L"music/青石巷.wav",nullptr,SND_FILENAME | SND_ASYNC | SND_LOOP); 
	draw_menu();
	main_loop();
	printf("请按回车键退出\n");
	getchar();
	return 0;
}
