#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <mmsystem.h>  // PlaySound 함수를 사용하기 위해 추가
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

// 음소거 설정을 저장하는 변수
bool isMuted = false;

// WAV 파일 재생을 중지하는 함수
void stop_sound()
{
    // NULL 값을 이용하여 PlaySound 함수 호출하여 중지
    PlaySound(NULL, NULL, SND_ASYNC);
}

//효과음
void handle_click(const char* filename, bool loop)
{
    if (!isMuted) { // 음소거가 아닐 때만 재생
        LPCTSTR sound_file = L"C:\\BGM\\클릭.wav";  // 효과음 파일 경로를 직접 지정

        PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
    }
}

void printGameStartScreen(int selectedOption) {
    system("cls"); // 콘솔 화면을 지우는 명령어
    printf("                                                                                              \n");
    printf("                                                                                              \n");
    printf("                          \033[1;32mEEEEEEEE  SSSSSSS  CCCCCCCCC       AAA       PPPPPPPP   EEEEEEEE\033[0m    \n");
    printf("                          \033[1;32mEEE       SSS      CCC           AA   AA     PPP  PPP   EEE\033[0m         \n");
    printf("                          \033[1;32mEEEEEEEE   SSS     CCC          AAAAAAAAA    PPPPPPPP   EEEEEEE\033[0m     \n");
    printf("                          \033[1;32mEEE          SSS   CCC         AAA     AAA   PPP        EEE\033[0m         \n");
    printf("                          \033[1;32mEEEEEEEE  SSSSSSS  CCCCCCCCC  AAA       AAA  PPP        EEEEEEEE\033[0m    \n\n");

    printf("                    \033[1;32mAAAAAAA    NNN   NNN  DDDDDDDD\033[0m     \033[1;32mTTTTTTTTT  RRRRRRRR   UUU   UUU TTTTTTTTT  HHH   HHH\033[0m\n");
    printf("                   \033[1;32mAA     AA   NNNN  NNN  DD     DD\033[0m       \033[1;32mTTT     RR    RRR  UUU   UUU    TTT     HHH   HHH\033[0m\n");
    printf("                  \033[1;32mAAAAAAAAAAA  NNNNN NNN  DD     DD\033[0m       \033[1;32mTTT     RRRRRRRR   UUU   UUU    TTT     HHHHHHHHH\033[0m\n");
    printf("                  \033[1;32mAA       AA  NNN NNNNN  DD     DD\033[0m       \033[1;32mTTT     RR  RR     UUU   UUU    TTT     HHH   HHH\033[0m\n");
    printf("                 \033[1;32mAA         AA NNN  NNNN  DDDDDDDD\033[0m        \033[1;32mTTT     RR   RRR    UUUUUUU     TTT     HHH   HHH\033[0m\n\n\n\n\n\n");

    // 게임시작버튼
    if (selectedOption == 1)
        printf("                                                   \033[1;32m=>\033[0m 게임 시작\n");
    else
        printf("                                                        게임 시작\n");

    // 사운드설정
    if (selectedOption == 2)
        printf("                                                   \033[1;32m=>\033[0m 사운드설정\n");
    else
        printf("                                                        사운드설정\n");

    // 종료
    if (selectedOption == 3)
        printf("                                                   \x1b[1;32m=>\x1b[0m 종료\n");
    else
        printf("                                                        종료\n");

    printf("\n\n\n\n");
    printf("                                                %s\n", (selectedOption == 1 || selectedOption == 2 || selectedOption == 3) ? "막내의 무죄를 증명하라" : "");

}

void printSoundSettingsScreen(int selectedOption) {
    system("cls");
    printf("  \033[1;32m*********************************************************************************************************************\033[0m\n");
    printf("\n");
    printf("                                                       사운드 설정\n\n\n\n\n\n\n\n");

    printf("\n");
    if (selectedOption == 1)
        printf("                                             \033[1;32m=>\033[0m  음소거\n");
    else
        printf("                                                   음소거\n");

    if (selectedOption == 2)
        printf("                                             \033[1;32m=>\033[0m  음소거 해제\n");
    else
        printf("                                                   음소거 해제\n");


    // 이전 화면으로 돌아가기
    if (selectedOption == 3)
        printf("                                             \033[1;32m=>\033[0m  이전 화면으로 돌아가기\n");
    else
        printf("                                                   이전 화면으로 돌아가기\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("  \033[1;32m*********************************************************************************************************************\033[0m\n");
}

void startscreen() {


    int selectedOption = 1;
    int soundSelectedOption = 1; // 사운드 설정 메뉴에서 선택된 옵션
    bool isSoundSettingsSelected = false; // 사운드 설정 화면으로 이동 여부를 저장하는 변수
    bool isGameOver = false;

    while (!isGameOver) {
        if (isSoundSettingsSelected) {
            printSoundSettingsScreen(soundSelectedOption);
            handle_click("C:\\BGM\\클릭.wav", false); // 클릭 효과음 재생
            int key = _getch();

            if (key == 224) { // 확장키
                key = _getch();
                if (key == 72) { // 위쪽 화살표

                    if (soundSelectedOption > 1)
                        soundSelectedOption--;
                }
                else if (key == 80) { // 아래쪽 화살표

                    if (soundSelectedOption < 3)
                        soundSelectedOption++;
                }
            }
            else if (key == 13) { // 엔터 키

                switch (soundSelectedOption) {
                case 1:
                    printf("음소거\n");
                    isMuted = true; // 음소거 상태로 설정
                    stop_sound(); // 배경음 중지
                    break;
                case 2:
                    printf("음소거 해제\n");
                    isMuted = false; // 음소거 해제
                    break;
                case 3:
                    isSoundSettingsSelected = false; // 이전 화면으로 돌아가기
                    handle_click("C:\\BGM\\클릭.wav", false); // 클릭 효과음 재생
                    break;
                }
            }
        }
        else {
            printGameStartScreen(selectedOption);

            int key = _getch();
            if (key == 224) { // 확장키
                key = _getch();
                if (key == 72) { // 위쪽 화살표
                    if (selectedOption > 1)
                        selectedOption--;
                    handle_click("C:\\BGM\\클릭.wav", false); // 클릭 효과음 재생
                }
                else if (key == 80) { // 아래쪽 화살표
                    if (selectedOption < 3)
                        selectedOption++;
                    handle_click("C:\\BGM\\클릭.wav", false); // 클릭 효과음 재생
                }
            }
            else if (key == 13) { // 엔터 키
                switch (selectedOption) {
                case 1:
                    printf("게임 시작\n");
                    // 게임 시작 로직 작성
                    isGameOver = true;
                    break;
                case 2:
                    isSoundSettingsSelected = true; // 사운드 설정 화면으로 이동
                    soundSelectedOption = 1; // 사운드 설정 메뉴의 기본 선택 항목을 1로 설정
                    handle_click("C:\\BGM\\클릭.wav", false); // 클릭 효과음 재생
                    break;
                case 3:
                    printf("게임 종료\n");
                    // 게임 종료 로직 작성
                    isGameOver = true;
                    break;
                }
            }
            else if (key == 27) { // ESC 키
                printf("ESCAPE\n");
                // ESCAPE 로직 작성
                isGameOver = true;
            }
        }
    }
    return 0;
}