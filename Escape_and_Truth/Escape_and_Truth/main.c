#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <mmsystem.h>  // PlaySound �Լ��� ����ϱ� ���� �߰�
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

#include "game1.h"
#include "game2.h"
#include "startscreen.h"
#include "game3.h"
#include "lastgame.h"
#include "stories.h"

void main() {

	startscreen();  // ���� ȭ��
	Sleep(500);
	system("cls");
	story1();  // ���丮1
	Sleep(500);
	one_drawing();  // ��������1
	story2();  // ���丮2
	Sleep(1000);
	system("cls");
	DodgeBullets();  // ��������2
	story3();  // ���丮3
	Sleep(2000);
	system("cls");
	WaterFire_Game();  // ��������3
	Sleep(2000);
	system("cls");
	evidence();  // ���Ź�ǰ
	Sleep(1000);
	system("cls");
	story4();  // ���丮4
	Sleep(1000);
	system("cls");
	Detective();  // ���� ��������
	Sleep(1000);
	system("cls");
	story5();  // �ḻ

	return 0;
}