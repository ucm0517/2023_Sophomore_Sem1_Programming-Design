#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <mmsystem.h>  // PlaySound �Լ��� ����ϱ� ���� �߰�
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

// ���Ұ� ������ �����ϴ� ����
bool isMuted = false;

// WAV ���� ����� �����ϴ� �Լ�
void stop_sound()
{
    // NULL ���� �̿��Ͽ� PlaySound �Լ� ȣ���Ͽ� ����
    PlaySound(NULL, NULL, SND_ASYNC);
}

//ȿ����
void handle_click(const char* filename, bool loop)
{
    if (!isMuted) { // ���ҰŰ� �ƴ� ���� ���
        LPCTSTR sound_file = L"C:\\BGM\\Ŭ��.wav";  // ȿ���� ���� ��θ� ���� ����

        PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
    }
}

void printGameStartScreen(int selectedOption) {
    system("cls"); // �ܼ� ȭ���� ����� ��ɾ�
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

    // ���ӽ��۹�ư
    if (selectedOption == 1)
        printf("                                                   \033[1;32m=>\033[0m ���� ����\n");
    else
        printf("                                                        ���� ����\n");

    // ���弳��
    if (selectedOption == 2)
        printf("                                                   \033[1;32m=>\033[0m ���弳��\n");
    else
        printf("                                                        ���弳��\n");

    // ����
    if (selectedOption == 3)
        printf("                                                   \x1b[1;32m=>\x1b[0m ����\n");
    else
        printf("                                                        ����\n");

    printf("\n\n\n\n");
    printf("                                                %s\n", (selectedOption == 1 || selectedOption == 2 || selectedOption == 3) ? "������ ���˸� �����϶�" : "");

}

void printSoundSettingsScreen(int selectedOption) {
    system("cls");
    printf("  \033[1;32m*********************************************************************************************************************\033[0m\n");
    printf("\n");
    printf("                                                       ���� ����\n\n\n\n\n\n\n\n");

    printf("\n");
    if (selectedOption == 1)
        printf("                                             \033[1;32m=>\033[0m  ���Ұ�\n");
    else
        printf("                                                   ���Ұ�\n");

    if (selectedOption == 2)
        printf("                                             \033[1;32m=>\033[0m  ���Ұ� ����\n");
    else
        printf("                                                   ���Ұ� ����\n");


    // ���� ȭ������ ���ư���
    if (selectedOption == 3)
        printf("                                             \033[1;32m=>\033[0m  ���� ȭ������ ���ư���\n");
    else
        printf("                                                   ���� ȭ������ ���ư���\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("  \033[1;32m*********************************************************************************************************************\033[0m\n");
}

void startscreen() {


    int selectedOption = 1;
    int soundSelectedOption = 1; // ���� ���� �޴����� ���õ� �ɼ�
    bool isSoundSettingsSelected = false; // ���� ���� ȭ������ �̵� ���θ� �����ϴ� ����
    bool isGameOver = false;

    while (!isGameOver) {
        if (isSoundSettingsSelected) {
            printSoundSettingsScreen(soundSelectedOption);
            handle_click("C:\\BGM\\Ŭ��.wav", false); // Ŭ�� ȿ���� ���
            int key = _getch();

            if (key == 224) { // Ȯ��Ű
                key = _getch();
                if (key == 72) { // ���� ȭ��ǥ

                    if (soundSelectedOption > 1)
                        soundSelectedOption--;
                }
                else if (key == 80) { // �Ʒ��� ȭ��ǥ

                    if (soundSelectedOption < 3)
                        soundSelectedOption++;
                }
            }
            else if (key == 13) { // ���� Ű

                switch (soundSelectedOption) {
                case 1:
                    printf("���Ұ�\n");
                    isMuted = true; // ���Ұ� ���·� ����
                    stop_sound(); // ����� ����
                    break;
                case 2:
                    printf("���Ұ� ����\n");
                    isMuted = false; // ���Ұ� ����
                    break;
                case 3:
                    isSoundSettingsSelected = false; // ���� ȭ������ ���ư���
                    handle_click("C:\\BGM\\Ŭ��.wav", false); // Ŭ�� ȿ���� ���
                    break;
                }
            }
        }
        else {
            printGameStartScreen(selectedOption);

            int key = _getch();
            if (key == 224) { // Ȯ��Ű
                key = _getch();
                if (key == 72) { // ���� ȭ��ǥ
                    if (selectedOption > 1)
                        selectedOption--;
                    handle_click("C:\\BGM\\Ŭ��.wav", false); // Ŭ�� ȿ���� ���
                }
                else if (key == 80) { // �Ʒ��� ȭ��ǥ
                    if (selectedOption < 3)
                        selectedOption++;
                    handle_click("C:\\BGM\\Ŭ��.wav", false); // Ŭ�� ȿ���� ���
                }
            }
            else if (key == 13) { // ���� Ű
                switch (selectedOption) {
                case 1:
                    printf("���� ����\n");
                    // ���� ���� ���� �ۼ�
                    isGameOver = true;
                    break;
                case 2:
                    isSoundSettingsSelected = true; // ���� ���� ȭ������ �̵�
                    soundSelectedOption = 1; // ���� ���� �޴��� �⺻ ���� �׸��� 1�� ����
                    handle_click("C:\\BGM\\Ŭ��.wav", false); // Ŭ�� ȿ���� ���
                    break;
                case 3:
                    printf("���� ����\n");
                    // ���� ���� ���� �ۼ�
                    isGameOver = true;
                    break;
                }
            }
            else if (key == 27) { // ESC Ű
                printf("ESCAPE\n");
                // ESCAPE ���� �ۼ�
                isGameOver = true;
            }
        }
    }
    return 0;
}