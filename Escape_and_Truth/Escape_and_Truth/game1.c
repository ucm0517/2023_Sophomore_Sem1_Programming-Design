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

#define WIDTH 24
#define HEIGHT 18
#define LIMIT_TIME 100  // 제한 시간 (초)

int x = 0, y = 0;  // 처음 위치 지정
int game_over = 0;
int score = 0;

// 한붓그리기 그림을 배열로 구현
int picture[HEIGHT][WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
int initial_picture[HEIGHT][WIDTH]; // 초기 그림 저장용 배열

int board[HEIGHT][WIDTH] = { 0 };

// 커서 숨기기 함수
void hide_cursor(bool hide)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(output, &cursorInfo);
    cursorInfo.bVisible = !hide;
    SetConsoleCursorInfo(output, &cursorInfo);
}
void gotoxy(int x, int y)  // 커서이동 함수 부분
{
    COORD XY = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}

// 게임 보드 구현 함수
void draw_board(int remaining_time)
{
    COORD pos = { 0,0 };  // 커서 위치 설정
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);  // 표준 출력 핸들 가져오기

    int startX = (140 - WIDTH * 2) / 2;  // 보드 시작 X 좌표 계산
    int startY = (30 - HEIGHT) / 2;  // 보드 시작 Y 좌표 계산
    int textStartX = startX + WIDTH + 6;  // 텍스트 시작 X 좌표 계산

    pos.X = startX;
    pos.Y = startY;

    SetConsoleCursorPosition(output, pos);  // 커서 위치로 이동

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == y && j == x)
            {
                printf("\033[34m■\033[0m");  // 움직일 도형을 파란색으로 출력
            }
            else if (initial_picture[i][j])
            {
                printf("■");  // 지나갈 도형
            }
            else if (board[i][j])
            {
                printf("\033[36m■\033[0m");  // 지나간 도형은 하늘색으로 출력
            }
            else
            {
                printf("\033[1;32m^\033[0m");  // 빈 공간 출력
            }
        }
        pos.Y++;  // 커서 행 위치 증가
        pos.X = startX;
        SetConsoleCursorPosition(output, pos);  // 커서 위치로 이동
    }

    // 게임 설명 출력
    pos.X = textStartX;
    pos.Y = startY;
    SetConsoleCursorPosition(output, pos);
    printf("방향키를 움직여 사각형을 모두 지나가세요.");

    // 남은 시간 출력
    pos.Y++;
    SetConsoleCursorPosition(output, pos);
    printf("남은 시간: %d초            ", remaining_time);

    // 이동 횟수 출력
    pos.Y++;
    SetConsoleCursorPosition(output, pos);
    printf("이동 횟수: %d", score);
}

// 방향키 범위 제한 함수(그림을 벗어나면 실패)
int check_valid_move(int nx, int ny)
{
    if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT || !initial_picture[ny][nx] || board[ny][nx])
    {
        return 0;
    }
    return 1;
}

// 성공 or 실패 검사 함수
int check_success()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (initial_picture[i][j] == 1)
            {
                return 0; // 한붓그리기 실패
            }
        }
    }
    return 1; // 한붓그리기 성공
}

// 초기 그림을 저장하는 함수
void save_initial_picture()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            initial_picture[i][j] = picture[i][j];
        }
    }
}

// 게임 초기화 함수
void reset_game()
{
    x = 0;  // x 좌표 초기화
    y = 0;  // y 좌표 초기화
    game_over = 0;  // 게임 오버 상태 초기화
    score = 0;  // 이동 회수 초기화

    // 초기 그림 복원
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            picture[i][j] = initial_picture[i][j];
            board[i][j] = 0;
        }
    }
}

// WAV 파일을 재생하는 함수
void play_sound1(const char* filename, BOOL loop)
{
    LPCTSTR sound_file = L"C:\\BGM\\스테이지1.wav";  // 유니코드 문자열을 사용하는 경우

    // WAV 파일 재생
    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
}

// WAV 파일 재생을 중지하는 함수
void stop_sound1()
{
    // NULL 값을 이용하여 PlaySound 함수 호출하여 중지
    PlaySound(NULL, NULL, SND_ASYNC);
}

// 게임 오버 시 효과음을 출력하고 배경음악을 멈추는 함수
void handle_game_over1()
{
    LPCTSTR sound_file = L"C:\\BGM\\gameover.wav";  // 효과음 파일 경로를 직접 지정

    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME);
}

void handle_success1()
{
    LPCTSTR sound_file = L"C:\\BGM\\success.wav";  // 효과음 파일 경로를 직접 지정

    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME);
}

// Windows 환경에서 콘솔 창을 지우는 함수
void clear_console() {
    system("cls");
}

void drawLock() {
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\033[1;30m         ##########    \033[0m\n");
    printf("\033[1;30m        ###      ###   \033[0m\n");
    printf("\033[1;30m      ###          ###\033[0m\n");
    printf("\033[1;30m     ###            ###\033[0m\n");
    printf("\033[1;30m    ###              ###\033[0m\n");
    printf("\033[1;30m    ###              ###\033[0m\n");
    printf("\033[1;30m    ####################\033[0m\n");
    printf("\033[1;30m    ####################\033[0m\n");
    printf("\033[1;30m    ########    ########\033[0m\n");
    printf("\033[1;30m    ######## ###########\033[0m\n");
    printf("\033[1;30m    ########    ########\033[0m\n");
    printf("\033[1;30m    ######## ###########\033[0m\n");
    printf("\033[1;30m    #######      #######\033[0m\n");
    printf("\033[1;30m    #######      #######\033[0m\n");
    printf("\033[1;30m    ####################\033[0m\n");
    printf("\033[1;30m    ####################\033[0m\n");
}
void drawLockopen() {
    // 커서를 원하는 위치로 이동
    COORD pos = { 0, 7 };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);

    printf("\033[1;30m                          ##########    \033[0m\n");
    printf("\033[1;30m                         ###      ###   \033[0m\n");
    printf("\033[1;30m                       ###          ###\033[0m\n");
    printf("\033[1;30m                      ###            ###\033[0m\n");
    printf("\033[1;30m                     ###              ###\033[0m\n");
    printf("\033[1;30m                     ###              ###\033[0m\n");
    printf("\033[1;30m    ####################\033[0m\n");
    printf("\033[1;30m    ####################\033[0m\n");
    printf("\033[1;30m    ########    ########\033[0m\n");
    printf("\033[1;30m    ######## ###########\033[0m\n");
    printf("\033[1;30m    ########    ########\033[0m\n");
    printf("\033[1;30m    ######## ###########\033[0m\n");
    printf("\033[1;30m    #######      #######\033[0m\n");
    printf("\033[1;30m    #######      #######\033[0m\n");
    printf("\033[1;30m    ####################\033[0m\n");
    printf("\033[1;30m    ####################\033[0m\n");
}

// 스테이지1 시작 애니메이션
void drawStageAnimation1()
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
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE      11\n");
        printf("                               S             T       A      A    G          E           1 1\n");
        printf("                               S             T       A      A    G          E          1  1\n");
        printf("                               S             T       A      A    G          E             1\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE       1\n");
        printf("                                    S        T       A      A    G      G   E             1\n");
        printf("                                    S        T       A      A    G      G   E             1\n");
        printf("                                    S        T       A      A    G      G   E             1 \n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE   11111111\n");

        Sleep(500); // 0.5초 지연

        // 콘솔 화면 색상 변경 (빨간색)
        system("cls"); // 콘솔 화면 지우기
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("\n\n\n\n\n\n\n\n\n\n"); // 애니메이션 공간 확보
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE      11\n");
        printf("                               S             T       A      A    G          E           1 1\n");
        printf("                               S             T       A      A    G          E          1  1\n");
        printf("                               S             T       A      A    G          E             1\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE       1\n");
        printf("                                    S        T       A      A    G      G   E             1\n");
        printf("                                    S        T       A      A    G      G   E             1\n");
        printf("                                    S        T       A      A    G      G   E             1 \n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE   11111111\n");

        Sleep(500); // 0.5초 지연

        // 애니메이션 지속 시간을 체크하여 반복문 종료
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

// 게임 실패 애니메이션
void drawGame1OverAnimation() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    time_t startTime = time(NULL);  // 애니메이션 시작 시간
    int animationDuration = 3;  // 애니메이션 지속 시간(초)

    while (1) {
        printf("\n\n\n\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("\n");
        printf("                                    GGGGGGG     AAAAAAAA    MMMM    MMMMM    EEEEEE\n");
        printf("                                   G            A      A    M   M   M   M    E\n");
        printf("                                   G            A      A    M   M   M   M    E\n");
        printf("                                   G            A      A    M   M   M   M    E\n");
        printf("                                   G    GGG     AAAAAAAA    M    M M    M    EEEEE\n");
        printf("                                   G      G     A      A    M     M     M    E\n");
        printf("                                   G      G     A      A    M     M     M    E\n");
        printf("                                   G      G     A      A    M     M     M    E\n");
        printf("                                    GGGGGGG     A      A    M           M    EEEEEE\n");

        Sleep(500);

        printf("\n\n\n\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("                                    OO0O0OO0       V     V      EEEEEEE      RRRRRR\n");
        printf("                                    O      0       V     V      E            R    R\n");
        printf("                                    O      0       V     V      E            R    R\n");
        printf("                                    O      0       V     V      E            R    R\n");
        printf("                                    O      O       V     V      EEEEEE       RRRRRR\n");
        printf("                                    O      O       V     V      E            R     R\n");
        printf("                                    O      O        V   V       E            R     R\n");
        printf("                                    O      O        V   V       E            R      R\n");
        printf("                                    0OO0OOO0         V V        EEEEEEE      R       R\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        Sleep(500);
        system("cls");
        // 애니메이션 지속 시간을 체크하여 반복문 종료
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

// main 함수
void one_drawing() {


    COORD bufferSize = { 100, 10000 }; // 가로, 세로
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

    system("mode con cols=140 lines=30");

   
    hide_cursor(true);  // 커서 숨기기
    save_initial_picture();  // 초기 그림 저장

    // 배경음 재생
    play_sound1("C:\\BGM\\스테이지1.wav", TRUE);

    drawStageAnimation1();  // 스테이지1 애니메이션 출력
    clear_console();
    time_t start_time = time(NULL);  // 현재 시간을 시작 시간으로 설정
    drawLock(); // drawLock 출력

    while (!game_over)  // 게임 오버가 아니면 반복
    {
        int elapsed_time = time(NULL) - start_time;  // 경과 시간 계산
        int remaining_time = LIMIT_TIME - elapsed_time;  // 남은 시간 계산

        if (remaining_time <= 0)  // 제한 시간이 지났을 경우
        {
            remaining_time = 0;  // 남은 시간을 0으로 설정
            game_over = 0;  // 게임 종료
            break;  // 반복문 종료
        }
        draw_board(remaining_time);  // 게임 보드판 호출


        if (_kbhit())  // 키 입력이 있는 경우
        {
            int ch = _getch();  // 키 값 읽어옴
            int nx = x, ny = y;  // 새 좌표를 현재 좌표로 초기화

            if (ch == 224)
            {
                switch (_getch())
                {
                case 72:  // 상
                    ny--;
                    break;
                case 80:  // 하 
                    ny++;
                    break;
                case 75:  // 좌
                    nx--;
                    break;
                case 77:  // 우
                    nx++;
                    break;
                default:
                    continue;  // 방향키가 아닌 경우, 다음 반복으로 건너뛰기
                }
            }
            else
            {
                continue;  // 특수 키가 아닌 경우, 다음 반복으로 건너뛰기
            }

            if (check_valid_move(nx, ny))  // 방향키 이동이 있는 경우
            {
                x = nx;  // x 좌표를 새 x 좌표로 업데이트
                y = ny;  // y 좌표를 새 y 좌표로 업데이트
                initial_picture[y][x] = 0;  // 도형이 그려진 위치를 0으로 설정하여 지움
                board[y][x] = 1;  // 보드의 해당 위치를 1로 설정하여 기록
                score++;  // 이동 회수 증가

                if (check_success())  // 한붓 그리기 성공 시
                {
                    game_over = 1;  // 게임 종료
                    break;  // 반복문 종료
                }
            }
            else
            {  // 한붓 그리기 실패 시
                game_over = 0;  // 게임 종료

                break;  // 반복문 종료
            }
        }
    }

    // 배경음 중지
    stop_sound();

    hide_cursor(false);  // 커서 보이기
    draw_board(0);  // 최종 게임판 그림

    if (game_over)
    {
        printf("\n\t\t\t\t\t\t\t\t\t    게임 성공!\n\n");
        printf("\n\t\t\t\t\t\t\t\t\t    곧 자물쇠가 풀립니다.");
        handle_success1();
        Sleep(2000); // 효과음 재생 시간 동안 대기
        drawLockopen(); // drawLockopen 출력
    }
    else
    {
        printf("\n\n");
        clear_console();
        drawGame1OverAnimation();


        handle_game_over1(); // 효과음 재생

        while (1) {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t   게임을 다시 시작하시겠습니까? (y/n) ");
            printf("\n\n                                          ('n' 입력 시 게임이 바로 종료됩니다.)\n");

            char choice = '\0';

            while (choice != 'y' && choice != 'n') {
                choice = _getch();
                if (choice == 'y' || choice == 'Y') {
                    clear_console();  // 콘솔 창 지우기
                    printf("\033[2J\033[H"); // 화면을 지우는 ANSI 이스케이프 시퀀스 출력
                    save_initial_picture();  // 초기 그림 저장
                    reset_game();  // 게임 초기화
                    start_time = time(NULL);  // 경과 시간 초기화
                    draw_board(0);  // 보드 다시 그리기
                    one_drawing();  // 게임 다시 시작(메인 함수 다시 호출)
                    break;
                }
                else if (choice == 'n' || choice == 'N') {
                    game_over = 1;
                    exit(1);
                }
            }
            if (game_over) {
                break;
            }
        }
        return 0;
    }
}