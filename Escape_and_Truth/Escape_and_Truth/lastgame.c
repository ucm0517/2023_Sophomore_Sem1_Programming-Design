#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <mmsystem.h>  // PlaySound �Լ��� ����ϱ� ���� �߰�
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

#define GAME_TIME 30
#define MAX_CHOICES 2

void clearConsole4() {
    system("cls");
}


// WAV ������ ����ϴ� �Լ�
void play_sound4(const char* filename, BOOL loop)
{
    LPCTSTR sound_file = L"C:\\BGM\\��������4.wav";  // �����ڵ� ���ڿ��� ����ϴ� ���

    // WAV ���� ���
    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
}

// WAV ���� ����� �����ϴ� �Լ�
void stop_sound4()
{
    // NULL ���� �̿��Ͽ� PlaySound �Լ� ȣ���Ͽ� ����
    PlaySound(NULL, NULL, SND_ASYNC);
}
// WAV ������ ����ϴ� �Լ�
void play_success(const char* filename, BOOL loop)
{
    LPCTSTR sound_file = L"C:\\BGM\\�ḻ.wav";  // �����ڵ� ���ڿ��� ����ϴ� ���

    // WAV ���� ���
    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
}

// ���� ���� �� ȿ������ ����ϰ� ��������� ���ߴ� �Լ�
void handle_game_over4()
{
    LPCTSTR sound_file = L"C:\\BGM\\gameover2.wav";  // ȿ���� ���� ��θ� ���� ����

    PlaySound(sound_file, NULL, SND_ASYNC);
}

void handle_success4()
{
    LPCTSTR sound_file = L"C:\\BGM\\success.wav";  // ȿ���� ���� ��θ� ���� ����

    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME);
}

void keyboard4(const char* filename, bool loop)
{
    LPCTSTR sound_file = L"C:\\BGM\\Ű����Ҹ�.wav";  // ȿ���� ���� ��θ� ���� ����

    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
}

void clear4() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD topLeft = { 0, 0 };
    SetConsoleCursorPosition(hConsole, topLeft);
}
void hideCursor4() {
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void drawStageAnimation4()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    time_t startTime = time(NULL);  // �ִϸ��̼� ���� �ð�
    int animationDuration = 3;  // �ִϸ��̼� ���� �ð�(��)

    while (1) {
        system("cls"); // �ܼ� ȭ�� �����

        printf("\n\n\n\n"); // �ִϸ��̼� ���� Ȯ��

        // "STAGE 1" �ܾ ǥ���ϴ� ASCII ��Ʈ (���)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("\n\n\n\n\n\n"); // �ִϸ��̼� ���� Ȯ��
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE       4 4\n");
        printf("                               S             T       A      A    G          E            4  4\n");
        printf("                               S             T       A      A    G          E           4   4\n");
        printf("                               S             T       A      A    G          E          4    4\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE   4444444444\n");
        printf("                                    S        T       A      A    G      G   E               4\n");
        printf("                                    S        T       A      A    G      G   E               4\n");
        printf("                                    S        T       A      A    G      G   E               4\n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE         4\n");

        Sleep(500); // 0.5�� ����

        // �ܼ� ȭ�� ���� ���� (������)
        system("cls"); // �ܼ� ȭ�� �����
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("\n\n\n\n\n\n\n\n\n\n"); // �ִϸ��̼� ���� Ȯ��
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE       4 4\n");
        printf("                               S             T       A      A    G          E            4  4\n");
        printf("                               S             T       A      A    G          E           4   4\n");
        printf("                               S             T       A      A    G          E          4    4\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE   4444444444\n");
        printf("                                    S        T       A      A    G      G   E               4\n");
        printf("                                    S        T       A      A    G      G   E               4\n");
        printf("                                    S        T       A      A    G      G   E               4\n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE         4\n");

        Sleep(500); // 0.5�� ����

        // �ִϸ��̼� ���� �ð��� üũ�Ͽ� �ݺ��� ����
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

void printGameScreen4(int selectedOption, int prevSelectedOption, int remainingTime) {
    clear4();

    printf("\n\n\n\n");
    printf("                                    5���� ���� �� ��¥ ���� 2���� �����ϼ���.\n\n\n");
    printf("                           \033[1;32m---------------------------------------------------------------\033[0m\n\n");
    printf("                             %s%s  ��: ��°�� �濡�� �ο�� �Ҹ��� ��Ⱦ��!\n\n", (selectedOption == 1) ? "\033[1;32m>\033[0m" : " ", (prevSelectedOption == 1) ? " \033[1;32m * \033[0m" : "");
    printf("                             %s%s  ���絵���: �� �濡�� �ο�� �Ҹ��� �� ������!\n\n", (selectedOption == 2) ? "\033[1;32m>\033[0m" : " ", (prevSelectedOption == 2) ? "\033[1;32m*\033[0m" : "");
    printf("                             %s%s  ���� ���: ��ҿ� ���� ��ȭ ��ȭ�� ������ ���̰� ���Ҿ��!\n\n", (selectedOption == 3) ? "\033[1;32m>\033[0m" : " ", (prevSelectedOption == 3) ? "\033[1;32m*\033[0m" : "");
    printf("                             %s%s  ù° ��ȥ��: ����� �߻��� �� �ð��� ���� ���� �־����!\n\n", (selectedOption == 4) ? "\033[1;32m>\033[0m" : " ", (prevSelectedOption == 4) ? "\033[1;32m*\033[0m" : "");
    printf("                             %s%s  �� �� ���: â���� Į�� ��� �ִ� �Ƿ翧�� �������..\n\n", (selectedOption == 5) ? "\033[1;32m>\033[0m" : " ", (prevSelectedOption == 5) ? "\033[1;32m*\033[0m" : "");
    printf("                           \033[1;32m---------------------------------------------------------------\033[0m\n\n\n");
    printf("                                                  ���� �ð�: %d��\n\n", remainingTime);
}


void Detective() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor4();
    play_sound4("C:\\BGM\\��������4.wav", TRUE);
    int selectedOption = 1;
    int prevSelectedOption = -1; // ���� ���� �׸��� �����ϴ� ����
    bool isGameOver = false;
    bool isEnding1 = false;
    int numChoices = 0;
    int numTrueChoices = 0;

    drawStageAnimation4();  // ��������4 �ִϸ��̼� ���
    clearConsole4();

    time_t startTime = time(NULL);
    int remainingTime = GAME_TIME;
    time_t currentTime = time(NULL);
    int prevTime = (int)currentTime;

    

    while (!isGameOver && numChoices < MAX_CHOICES) {

        currentTime = time(NULL);
        if ((int)currentTime - prevTime >= 1) {
            remainingTime = GAME_TIME - (int)(currentTime - startTime);
            prevTime = (int)currentTime;
        }

        printGameScreen4(selectedOption, prevSelectedOption, remainingTime);

        if (_kbhit()) {
            int key = _getch();
            if (key == 224) { // Ȯ��Ű
                key = _getch();
                if (key == 72) { // ���� ȭ��ǥ
                    if (selectedOption > 1)
                        selectedOption--;
                }
                else if (key == 80) { // �Ʒ��� ȭ��ǥ
                    if (selectedOption < 5)
                        selectedOption++;
                }
            }
            else if (key == 13) { // ���� Ű
                switch (selectedOption) {
                case 1:
                case 5:
                    numTrueChoices++;
                case 2:
                case 3:
                case 4:
                    numChoices++;
                    if (numChoices == MAX_CHOICES && numTrueChoices == MAX_CHOICES) {
                        isEnding1 = true;
                        isGameOver = true;
                    }
                    else if (numChoices == MAX_CHOICES && numTrueChoices < MAX_CHOICES) {
                        handle_game_over4();
                        keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
                        print_char_by_char("\t\t\t\t\t\t  �߸��� �����Դϴ�.\n");
                        print_char_by_char("\t\t\t   ������ �ٽ� �����Ͽ� �ḻ�� �����Ͻðڽ��ϱ�? (y �Ǵ� n �Է� �� Enter): ");
                        stop_sound0();
                        char response;
                        scanf(" %c", &response);

                        while (response != 'y' && response != 'Y' && response != 'n' && response != 'N') {
                            keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
                            print_char_by_char("\n�߸��� ���ڸ� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���: ");
                            stop_sound0();
                            scanf(" %c", &response);
                        }

                        if (response == 'y' || response == 'Y') {
                            play_sound4("C:\\BGM\\�ḻ", TRUE);

                            startTime = time(NULL);
                            system("cls");
                            numChoices = 0;
                            numTrueChoices = 0;
                            selectedOption = 1; // ���� �׸� �ʱ�ȭ
                            prevSelectedOption = -1; // ���� ���� �׸� �ʱ�ȭ
                            continue;
                        }
                        else {
                            isGameOver = true;
                        }
                    }
                    break;
                default:
                    printf("\n�߸��� �����Դϴ�. �ٽ� �����ϼ���.\n");
                    _getch();
                    break;
                }
                // ���� ���� �׸� ����
                prevSelectedOption = selectedOption;
            }
        }

        if (remainingTime <= 0) {
            isGameOver = true;
        }
        clear4();
    }

    if (isEnding1) {
        stop_sound4();
        system("cls");
        play_success("C:\\BGM\\�ḻ", TRUE);
        print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t     ���� ������ �����Ͽ����ϴ�.\n");
        print_char_by_char("\t\t\t\t      ���ΰ��� ������ ���� ������ ���� �Ǿ����ϴ�.\n\n");
        Sleep(3000);
        stop_sound4();
    }
    else {
        stop_sound4();

        system("cls");
        keyboard4("C:\\BGM\\Ű����Ҹ�.wav", false);
        print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t      ���� ������ �����Ͽ����ϴ�.\n");
        print_char_by_char("\t\t\t\t        ���ΰ��� ���� �ǰ��� �ް� �Ǿ����ϴ�.\n\n");
        Sleep(3000);
        stop_sound4();
    }
    prevSelectedOption = -1;

    return 0;
}