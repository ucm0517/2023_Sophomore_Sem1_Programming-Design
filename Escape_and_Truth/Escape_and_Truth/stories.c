#include <stdio.h>
#include <string.h>
#include< stdbool.h>
#include <windows.h>
#include <time.h>
#include <mmsystem.h>  // PlaySound 함수를 사용하기 위해 추가
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

// WAV 파일 재생을 중지하는 함수
void stop_sound0()
{
    // NULL 값을 이용하여 PlaySound 함수 호출하여 중지
    PlaySound(NULL, NULL, SND_ASYNC);
}

// 키보드 효과음
void keyboard(const char* filename, bool loop)
{
    LPCTSTR sound_file = L"C:\\BGM\\키보드소리.wav";  // 효과음 파일 경로를 직접 지정

    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
}
// 한글자씩 출력
void print_char_by_char(char* str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        printf("%c", str[i]);
        fflush(stdout);
        Sleep(30);  // 30 밀리세컨드 간격으로 문자 출력
    }
    printf("\n");
}

// 엔터를 입력받아야 다음 문장으로 넘어감
void wait_for_enter() {
    printf(" ");
    while (getchar() != '\n');
}

// 칼 그림
void draw_case()
{

    printf("                                                     ■■■                                           \n");
    printf("                                                       ■■                                          \n");
    printf("                                                      ■■■                                           \n");
    printf("                              ■■■■                     ■■■                                           \n");
    printf("                            ■■■■■■                  ■■■■                                           \n");
    printf("                           ■■■■■■■                   ■■■■                                              \n");
    printf("                           ■■■■■■■                ■■■■                                          \n");
    printf("                             ■■■■■■■         ■■■■                                        \n");
    printf("                               ■■■■■■■  ■■■■■\033[31m   \033[0m                                     \n");
    printf("                               ■■■■■■■■■■■■■\033[31m     \033[0m                                    \n");
    printf("                              ■■■■■■■■■■■■■\033[31m    \033[0m                                                       \n");
    printf("                            ■■■■■■■■■■■■■■\033[31m        \033[0m                                                        \n");
    printf("         ■■■             ■■■■■■■■\033[31m■■■■■■■  \033[0m                                                                \n");
    printf("          ■■■           ■■■■■■■■\033[31m■■■■■■■■    \033[0m                                                                  \n");
    printf("           ■■■■        ■■■■  ■■■■\033[31m■■■■■■■■      \033[0m                                                           \n");
    printf("            ■■■■       ■■■■     ■■■\033[31m■■■■■■■■       \033[0m                                                         \n");
    printf("               ■■■■   ■■■■       ■■■■■\033[31m■■■■■■          \033[0m                                                 \n");
    printf("                  ■■■■■■■          ■■■\033[31m■■■■■■■■        \033[0m                                                    \n");
    printf("                     ■■■■               ■■■■\033[31m■■■■■■■      \033[0m                                                   \n");
    printf("                                             ■■\033[31m■■■■■■■■\033[0m■                                          \n");
    printf("                                               ■■■■\033[31m■■■■■\033[0m■■■                                           \n");
    printf("                                               ■■■■■■■■■■■■■                                             \n");
    printf("                                                 ■■■■■■■■■■■■■■■                                   \n");
    printf("                                              ■■■■■■■      ■■■■■■■■                                 \n");
    printf("                                              ■■■■■              ■■■■■■■                       \n");
    printf("                                              ■■■■■■               ■■■■■■                                 \n");
    printf("                                               ■■■■■                   ■■■■■■                            \n");
    printf("                                                ■■■■■■                      ■■■■■                         \n");
    printf("                                                 ■■■■■■■                     ■■■■                      \n");
    printf("                                                  ■■■■■■■■                 ■■■■■                      \n");
    printf("                                                       ■■■■■■■                ■■■■                   \n");
    printf("                                                           ■■■■■■                ■■■         \n");
    printf("                                                                ■■■■■■            ■■■                   \n");
    printf("                                                                   ■■■■■■         ■■■                  \n");
    printf("                                                                        ■■■■■       ■■■■                  \n");
    printf("                                                                            ■■■        ■■■■■               \n");
    printf("                                                                              ■■                    \n");
    printf("                                                                                ■                    \n");
    printf("                                                                                ■                    \n");


}

// 철창 그림
void drawcc() {
    printf("\n\n");
    printf("                      ============================================================================\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ==================================================================+=========\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ============================================================================\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ||       ||       ||       ||        ||        ||       ||       ||       ||\n");
    printf("                      ============================================================================\n\n");
}

// 증거물품
void evidence()
{
    printf("\n\n");
    printf("             \033[1;32m---------------------------------------------------------------------------------------------\033[0m\n\n");
    printf("                           *------------*                 /|              *----       ----*\n");
    printf("                           |            |                / |             /                 \\\n");
    printf("                           | *--------* |               /  |            /                   \\\n");
    printf("                           | |        | |              /   |           /                     \\\n");
    printf("                           | |        | |             /    |          /                       \\\n");
    printf("                           | |        | |            /     |         *-----               -----*\n");
    printf("                           | |        | |           /      |               |             |\n");
    printf("                           | *--------* |          /       |               |             |\n");
    printf("                           |            |         /        |               |             |\n");
    printf("                           |    play    |        /         |               |             |\n");
    printf("                           |            |       *----------*               |             |\n");
    printf("                           |            |           |  |                   |             |\n");
    printf("                           |            |           |  |                   |             |\n");
    printf("                           *------------*           *--*                   *-------------*\n\n");
    printf("                               녹음기            피 묻은 칼                  피 묻은 옷\n\n");
    printf("             \033[1;32m---------------------------------------------------------------------------------------------\033[0m\n");
    
    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("\n\t\t\t\t축하합니다. 증거물품을 획득하였습니다. (계속하려면 Enter)");
    stop_sound0();
    wait_for_enter();
    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("\n\n증거물품을 획득한 송중기는 무죄를 입증하기 위한 증언을 수집하기로 결심한다. (계속하려면 Enter)");
    stop_sound0();
    wait_for_enter();
    return 0;
}

void story1() {
    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\t\t    2023년 6월 12일 오후 2시에 성결대저택에서 살인사건이 발생했다. (계속하려면 Enter)");
    stop_sound0();
    wait_for_enter();

    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("\t이 대저택에는 송양철 회장, 첫째 송영기, 둘째 송동기, 막내 아들 송중기가 살고있었다. (계속하려면 Enter)");
    stop_sound0();
    wait_for_enter();

    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("\t\t\t얼마 전 회장님이 세상을 떠나고, 둘째 송동기가 유산을 상속받았다. (계속하려면 Enter)");
    stop_sound0();
    wait_for_enter();
    Sleep(100);

    system("cls");
    draw_case();  // 두번째 그림 호출
    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("둘째 송동기가 칼에 찔려 사망한 상태로 발견된다. (계속하려면 Enter)"); 
    stop_sound0();
    wait_for_enter();
    Sleep(100);

    system("cls");
    drawcc();  // 세번째 그림 호출
    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("경찰은 사건 발생 당시 집에 있던 셋째 송중기를 유력 용의자로 체포하여 감옥에 가둔다. (계속하려면 Enter)");
    stop_sound0();
    wait_for_enter();

    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("누명을 쓴 송중기는 감옥을 탈출하여 무죄를 입증하기로 결심한다. (계속하려면 Enter)");
    stop_sound0();
    wait_for_enter();

    Sleep(500);
    system("cls");
    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t자물쇠를 풀고 철창 밖으로 탈출하세요. (계속하려면 Enter)");
    stop_sound0();
    wait_for_enter();
    return 0;
}

void story2() { //one_drawing 후에 출력되는 스토리
    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("\n\n자물쇠를 풀고 철창에서 나온 송중기는 간수의 총알을 피해 감옥을 탈출하기로 한다. (계속하려면 Enter)");
    stop_sound0();
    wait_for_enter();

    Sleep(500);
    system("cls");
    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t간수의 총알을 피해 감옥을 탈출하세요. (계속하려면 Enter)");
    stop_sound0();
    wait_for_enter();
    return 0;
}

void story3() {
    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("\n\n\n총알을 피해 감옥을 탈출한 송중기는 무죄를 입증하기 위한 증거물품을 수집하기로 결심한다. (계속하려면 Enter)");
    stop_sound0();
    wait_for_enter();

    Sleep(500);
    system("cls");
    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t비서와 협동하여 증거물품을 획득하세요. (계속하려면 Enter)");
    stop_sound0();
    wait_for_enter();
    return 0;
}

void story4() {
    keyboard("C:\\BGM\\키보드소리.wav", false);
    print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t증언을 수집해 무죄를 입증하세요. (계속하려면 Enter)");
    stop_sound0();
    wait_for_enter();
    return 0;
}

void story5() {  // 결말
    keyboard("C:\\BGM\\키보드소리.wav", false);
    printf("\n\t\t\t\t\t\t\t  전말\n\n\n\n\n");
    print_char_by_char("인물: 첫째(범인), 둘째(사망), 셋째(플레이어)");
    print_char_by_char("\n\n부유한 가정에서 태어난 세 형제가 있었다.");
    print_char_by_char("\n회장님이 돌아가시고 유언장을 확인하는데, 둘째가 회사를 상속받게 된다는 내용이 적혀 있었다.");
    print_char_by_char("\n이에 첫째는 질투와 분노로 인해 둘째를 실수로 칼로 찔러 죽이게 된다.");
    print_char_by_char("\n첫째는 위협만 줄 뿐 죽일 생각이 없었기에 당황하게 되고, 자신의 흔적을 지운다.");
    print_char_by_char("\n첫째는 자신의 범죄를 숨기기 위해 셋째에서 누명을 씌우고 감옥에 가둔다.");
    print_char_by_char("\n\n\n\n\t\t\t\t\t\t잠시후 게임이 종료됩니다..");
    stop_sound0();
    Sleep(3000);
    return 0;
}