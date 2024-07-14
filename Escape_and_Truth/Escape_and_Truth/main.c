#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <mmsystem.h>  // PlaySound 함수를 사용하기 위해 추가
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

#include "game1.h"
#include "game2.h"
#include "startscreen.h"
#include "game3.h"
#include "lastgame.h"
#include "stories.h"

void main() {

	startscreen();  // 시작 화면
	Sleep(500);
	system("cls");
	story1();  // 스토리1
	Sleep(500);
	one_drawing();  // 스테이지1
	story2();  // 스토리2
	Sleep(1000);
	system("cls");
	DodgeBullets();  // 스태이지2
	story3();  // 스토리3
	Sleep(2000);
	system("cls");
	WaterFire_Game();  // 스테이지3
	Sleep(2000);
	system("cls");
	evidence();  // 증거물품
	Sleep(1000);
	system("cls");
	story4();  // 스토리4
	Sleep(1000);
	system("cls");
	Detective();  // 최종 스테이지
	Sleep(1000);
	system("cls");
	story5();  // 결말

	return 0;
}