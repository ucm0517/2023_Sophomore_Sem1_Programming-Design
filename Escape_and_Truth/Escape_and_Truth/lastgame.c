#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <mmsystem.h>  // PlaySound 함수를 사용하기 위해 추가
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

#define GAME_TIME 30
#define MAX_CHOICES 2

void clearConsole4() {
    system("cls");
}


// WAV 파일을 재생하는 함수
void play_sound4(const char* filename, BOOL loop)
{
    LPCTSTR sound_file = L"C:\\BGM\\스테이지4.wav";  // 유니코드 문자열을 사용하는 경우

    // WAV 파일 재생
    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
}

// WAV 파일 재생을 중지하는 함수
void stop_sound4()
{
    // NULL 값을 이용하여 PlaySound 함수 호출하여 중지
    PlaySound(NULL, NULL, SND_ASYNC);
}
// WAV 파일을 재생하는 함수
void play_success(const char* filename, BOOL loop)
{
    LPCTSTR sound_file = L"C:\\BGM\\결말.wav";  // 유니코드 문자열을 사용하는 경우

    // WAV 파일 재생
    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
}

// 게임 오버 시 효과음을 출력하고 배경음악을 멈추는 함수
void handle_game_over4()
{
    LPCTSTR sound_file = L"C:\\BGM\\gameover2.wav";  // 효과음 파일 경로를 직접 지정

    PlaySound(sound_file, NULL, SND_ASYNC);
}

void handle_success4()
{
    LPCTSTR sound_file = L"C:\\BGM\\success.wav";  // 효과음 파일 경로를 직접 지정

    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME);
}

void keyboard4(const char* filename, bool loop)
{
    LPCTSTR sound_file = L"C:\\BGM\\키보드소리.wav";  // 효과음 파일 경로를 직접 지정

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

    time_t startTime = time(NULL);  // 애니메이션 시작 시간
    int animationDuration = 3;  // 애니메이션 지속 시간(초)

    while (1) {
        system("cls"); // 콘솔 화면 지우기

        printf("\n\n\n\n"); // 애니메이션 공간 확보

        // "STAGE 1" 단어를 표현하는 ASCII 아트 (흰색)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("\n\n\n\n\n\n"); // 애니메이션 공간 확보
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE       4 4\n");
        printf("                               S             T       A      A    G          E            4  4\n");
        printf("                               S             T       A      A    G          E           4   4\n");
        printf("                               S             T       A      A    G          E          4    4\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE   4444444444\n");
        printf("                                    S        T       A      A    G      G   E               4\n");
        printf("                                    S        T       A      A    G      G   E               4\n");
        printf("                                    S        T       A      A    G      G   E               4\n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE         4\n");

        Sleep(500); // 0.5초 지연

        // 콘솔 화면 색상 변경 (빨간색)
        system("cls"); // 콘솔 화면 지우기
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("\n\n\n\n\n\n\n\n\n\n"); // 애니메이션 공간 확보
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE       4 4\n");
        printf("                               S             T       A      A    G          E            4  4\n");
        printf("                               S             T       A      A    G          E           4   4\n");
        printf("                               S             T       A      A    G          E          4    4\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE   4444444444\n");
        printf("                                    S        T       A      A    G      G   E               4\n");
        printf("                                    S        T       A      A    G      G   E               4\n");
        printf("                                    S        T       A      A    G      G   E               4\n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE         4\n");

        Sleep(500); // 0.5초 지연

        // 애니메이션 지속 시간을 체크하여 반복문 종료
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

void printGameScreen4(int selectedOption, int prevSelectedOption, int remainingTime) {
    clear4();

    printf("\n\n\n\n");
    printf("                                    5개의 증언 중 진짜 증언 2개를 선택하세요.\n\n\n");
    printf("                           \033[1;32m---------------------------------------------------------------\033[0m\n\n");
    printf("                             %s%s  비서: 둘째의 방에서 싸우는 소리가 들렸어요!\n\n", (selectedOption == 1) ? "\033[1;32m>\033[0m" : " ", (prevSelectedOption == 1) ? " \033[1;32m * \033[0m" : "");
    printf("                             %s%s  가사도우미: 전 방에서 싸우는 소리를 못 들었어요!\n\n", (selectedOption == 2) ? "\033[1;32m>\033[0m" : " ", (prevSelectedOption == 2) ? "\033[1;32m*\033[0m" : "");
    printf("                             %s%s  운전 기사: 평소에 둘이 전화 통화할 때마다 사이가 좋았어요!\n\n", (selectedOption == 3) ? "\033[1;32m>\033[0m" : " ", (prevSelectedOption == 3) ? "\033[1;32m*\033[0m" : "");
    printf("                             %s%s  첫째 약혼녀: 사건이 발생한 그 시간에 저랑 같이 있었어요!\n\n", (selectedOption == 4) ? "\033[1;32m>\033[0m" : " ", (prevSelectedOption == 4) ? "\033[1;32m*\033[0m" : "");
    printf("                             %s%s  옆 집 사람: 창문에 칼을 들고 있는 실루엣이 보였어요..\n\n", (selectedOption == 5) ? "\033[1;32m>\033[0m" : " ", (prevSelectedOption == 5) ? "\033[1;32m*\033[0m" : "");
    printf("                           \033[1;32m---------------------------------------------------------------\033[0m\n\n\n");
    printf("                                                  제한 시간: %d초\n\n", remainingTime);
}


void Detective() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor4();
    play_sound4("C:\\BGM\\스테이지4.wav", TRUE);
    int selectedOption = 1;
    int prevSelectedOption = -1; // 이전 선택 항목을 저장하는 변수
    bool isGameOver = false;
    bool isEnding1 = false;
    int numChoices = 0;
    int numTrueChoices = 0;

    drawStageAnimation4();  // 스테이지4 애니메이션 출력
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
            if (key == 224) { // 확장키
                key = _getch();
                if (key == 72) { // 위쪽 화살표
                    if (selectedOption > 1)
                        selectedOption--;
                }
                else if (key == 80) { // 아래쪽 화살표
                    if (selectedOption < 5)
                        selectedOption++;
                }
            }
            else if (key == 13) { // 엔터 키
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
                        keyboard("C:\\BGM\\키보드소리.wav", false);
                        print_char_by_char("\t\t\t\t\t\t  잘못된 증언입니다.\n");
                        print_char_by_char("\t\t\t   증언을 다시 선택하여 결말을 변경하시겠습니까? (y 또는 n 입력 후 Enter): ");
                        stop_sound0();
                        char response;
                        scanf(" %c", &response);

                        while (response != 'y' && response != 'Y' && response != 'n' && response != 'N') {
                            keyboard("C:\\BGM\\키보드소리.wav", false);
                            print_char_by_char("\n잘못된 문자를 입력하였습니다. 다시 입력하세요: ");
                            stop_sound0();
                            scanf(" %c", &response);
                        }

                        if (response == 'y' || response == 'Y') {
                            play_sound4("C:\\BGM\\결말", TRUE);

                            startTime = time(NULL);
                            system("cls");
                            numChoices = 0;
                            numTrueChoices = 0;
                            selectedOption = 1; // 선택 항목 초기화
                            prevSelectedOption = -1; // 이전 선택 항목 초기화
                            continue;
                        }
                        else {
                            isGameOver = true;
                        }
                    }
                    break;
                default:
                    printf("\n잘못된 선택입니다. 다시 선택하세요.\n");
                    _getch();
                    break;
                }
                // 이전 선택 항목 저장
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
        play_success("C:\\BGM\\결말", TRUE);
        print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t     무죄 입증에 성공하였습니다.\n");
        print_char_by_char("\t\t\t\t      주인공은 누명을 벗고 자유의 몸이 되었습니다.\n\n");
        Sleep(3000);
        stop_sound4();
    }
    else {
        stop_sound4();

        system("cls");
        keyboard4("C:\\BGM\\키보드소리.wav", false);
        print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t      무죄 입증에 실패하였습니다.\n");
        print_char_by_char("\t\t\t\t        주인공은 유죄 판결을 받게 되었습니다.\n\n");
        Sleep(3000);
        stop_sound4();
    }
    prevSelectedOption = -1;

    return 0;
}