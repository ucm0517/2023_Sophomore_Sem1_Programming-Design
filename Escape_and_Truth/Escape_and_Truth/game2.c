#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <mmsystem.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

#define WIDTH 40
#define HEIGHT 20
#define BULLET_MIN 1
#define BULLET_MAX 2
#define BULLET_DELAY 500 // 밀리초 단위로 지정 (500밀리초 = 0.5초)
#define GAME_TIME_LIMIT 10 // 제한 시간 (초 단위)

void clearConsole() {
    system("cls");
}

void playSoundEffect(const char* filename, BOOL loop) {
    LPCTSTR soundFile = L"C:\\BGM\\스테이지2.wav";

    PlaySound(soundFile, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
}

void stopSoundEffect() {
    PlaySound(NULL, NULL, SND_ASYNC);
}

void playGameOverSoundEffect() {
    LPCTSTR soundFile = L"C:\\BGM\\gameover.wav";

    PlaySound(soundFile, NULL, SND_ASYNC | SND_FILENAME);
}

void playSuccessSoundEffect() {
    LPCTSTR soundFile = L"C:\\BGM\\success.wav";

    PlaySound(soundFile, NULL, SND_ASYNC | SND_FILENAME);
}

void gotoxy2(int x, int y) {
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void printSafe(int x, int y, const char* str, int w, int h) {
    if (x >= 0 && x + strlen(str) <= w && y >= 0 && y < h) {
        gotoxy2(x, y);
        printf("%s", str);
    }
    else if (x < 0) {
        gotoxy2(0, y);
        for (int i = -x; i < strlen(str); i++) {
            if (y >= 0 && y < h) putchar(str[i]);
            y++;
        }
    }
    else if (x + strlen(str) > w) {
        gotoxy2(w - strlen(str), y);
        for (int i = 0; i < w - x; i++) {
            if (y >= 0 && y < h) putchar(str[i]);
            y++;
        }
    }
    else if (y < 0) {
        gotoxy2(x, 0);
        for (int i = 0; i < strlen(str); i++) {
            if (x + i >= 0 && x + i < w) putchar(str[i]);
        }
    }
    else if (y >= h) {
        gotoxy2(x, h - 1);
        for (int i = 0; i < strlen(str); i++) {
            if (x + i >= 0 && x + i < w) putchar(str[i]);
        }
    }
}

void drawGame(int playerX, int playerY, int bulletX[], int bulletY[], int bulletCount, int exitX, int exitY, int remainingTime) {
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { 0,0 };

    int startX = (140 - WIDTH * 2) / 2;
    int startY = (30 - HEIGHT) / 2;

    pos.X = startX;
    pos.Y = startY;

    char gameBoard[HEIGHT][WIDTH];

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            gameBoard[y][x] = ' ';
        }
    }

    gameBoard[playerY][playerX] = 'P';
    gameBoard[exitY][exitX] = 'E';
    for (int i = 0; i < bulletCount; i++) {
        gameBoard[bulletY[i]][bulletX[i]] = '*';
    }

    for (int i = 0; i < WIDTH + 2; i++) {
        SetConsoleCursorPosition(output, pos);
        printf("\033[1;32m=\033[0m");
        pos.X++;
    }

    pos.X = startX;
    pos.Y = startY + 1;
    for (int y = 0; y < HEIGHT; y++) {
        SetConsoleCursorPosition(output, pos);
        printf("\033[1;32m‡\033[0m");
        pos.X = startX + 1;
        for (int x = 0; x < WIDTH; x++) {
            SetConsoleCursorPosition(output, pos);
            if (gameBoard[y][x] == '*')
                printf("\033[1;31m%c\033[0m", gameBoard[y][x]);
            else
                printf("%c", gameBoard[y][x]);
            pos.X++;
        }
        SetConsoleCursorPosition(output, pos);
        printf("\033[1;32m‡\033[0m");
        pos.X = startX;
        pos.Y++;
        SetConsoleCursorPosition(output, pos);
    }

    for (int i = 0; i < WIDTH + 2; i++) {
        SetConsoleCursorPosition(output, pos);
        printf("\033[1;32m=\033[0m");
        pos.X++;
    }

    pos.X = startX + WIDTH + 4;
    pos.Y = startY;
    pos.Y += 3;
    SetConsoleCursorPosition(output, pos);
    printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t총알을 피해 감옥 밖으로 탈출하세요.\n");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t(P: 플레이어, E: 출구)\n");
    pos.Y += 3;
    SetConsoleCursorPosition(output, pos);
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t제한 시간: %d초 \n", remainingTime);
}

// stage 1 시작 애니메이션
void drawStageAnimation()
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
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE      2222\n");
        printf("                               S             T       A      A    G          E           2    2\n");
        printf("                               S             T       A      A    G          E          2      2\n");
        printf("                               S             T       A      A    G          E                2\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE         2\n");
        printf("                                    S        T       A      A    G      G   E              2\n");
        printf("                                    S        T       A      A    G      G   E            2\n");
        printf("                                    S        T       A      A    G      G   E           2   \n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE    22222222 \n");

        Sleep(500); // 0.5초 지연

        // 콘솔 화면 색상 변경 (빨간색)
        system("cls"); // 콘솔 화면 지우기
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("\n\n\n\n\n\n\n\n\n\n"); // 애니메이션 공간 확보
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE      2222\n");
        printf("                               S             T       A      A    G          E           2    2\n");
        printf("                               S             T       A      A    G          E          2      2\n");
        printf("                               S             T       A      A    G          E                2\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE         2\n");
        printf("                                    S        T       A      A    G      G   E              2\n");
        printf("                                    S        T       A      A    G      G   E            2\n");
        printf("                                    S        T       A      A    G      G   E           2   \n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE    22222222 \n");

        Sleep(500); // 0.5초 지연

        // 애니메이션 지속 시간을 체크하여 반복문 종료
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

// 게임 성공 애니메이션
void drawGameSuccessAnimation() {
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

        // "GAME" 단어를 표현하는 ASCII 아트 (흰색)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("\n\n\n\n\n");
        printf("                                      GGGGGGG     AAAAAAAA    MMMM     MMMM    EEEEEEE\n");
        printf("                                     G            A      A    M  M     M  M    E\n");
        printf("                                     G            A      A    M  M     M  M    E\n");
        printf("                                     G            A      A    M  M     M  M    E\n");
        printf("                                     G    GGGG    AAAAAAAA    M    M M    M    EEEEEEE\n");
        printf("                                     G       G    A      A    M     M     M    E\n");
        printf("                                     G       G    A      A    M     M     M    E\n");
        printf("                                     G       G    A      A    M     M     M    E\n");
        printf("                                      GGGGGGG     A      A    M           M    EEEEEEE\n");

        Sleep(500); // 0.5초 지연

        system("cls"); // 콘솔 화면 지우기

        printf("\n\n\n\n"); // 애니메이션 공간 확보

        // 단어를 오른쪽으로 이동시키는 애니메이션 (빨간색)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("\n\n\n\n\n");
        printf("                                SSSSSS   U     U  CCCCCC  CCCCCCC  EEEEEE   SSSSSS  SSSSSS\n");
        printf("                                S        U     U  C       C        E        S       S\n");
        printf("                                S        U     U  C       C        E        S       S\n");
        printf("                                S        U     U  C       C        E        S       S\n");
        printf("                                SSSSSS   U     U  C       C        EEEE     SSSSSS  SSSSSS\n");
        printf("                                     S   U     U  C       C        E             S       S\n");
        printf("                                     S   U     U  C       C        E             S       S\n");
        printf("                                     S   U     U  C       C        E             S       S\n");
        printf("                                SSSSSS    UUUUU   CCCCCC  CCCCCCC  EEEEEE   SSSSSS  SSSSSS\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 기본색으로 되돌리기

        Sleep(500); // 0.5초 지연

        // 애니메이션 지속 시간을 체크하여 반복문 종료
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

// 게임 실패 애니메이션
void drawGame2OverAnimation() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    time_t startTime = time(NULL);  // 애니메이션 시작 시간
    int animationDuration = 3;  // 애니메이션 지속 시간(초)

    while (1) {
        clearConsole();

        printf("\n\n\n\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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

        // 애니메이션 지속 시간을 체크하여 반복문 종료
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

// 메인 함수
int DodgeBullets() {
    COORD bufferSize = { 100, 10000 };
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
    system("mode con cols=140 lines=30");

    playSoundEffect("C:\\BGM\\스테이지2.wav", TRUE);

    int gameElapsedTime = 0;
    int playerX = 0;
    int playerY = 0;
    int bulletX[WIDTH * 2 + HEIGHT * 2];
    int bulletY[WIDTH * 2 + HEIGHT * 2];
    int bulletDirectionX[WIDTH * 2 + HEIGHT * 2];
    int bulletDirectionY[WIDTH * 2 + HEIGHT * 2];
    int bulletCount = 0;
    int isGameOver = 0;
    int lastBulletTime = 0;
    int startTime = time(NULL);
    char choice;

    hideCursor();
    drawStageAnimation();
    clearConsole();

    startTime = time(NULL);

    while (!isGameOver) {
        int x = playerX;
        int y = playerY;

        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            if (y > 0) y--;
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            if (y < HEIGHT - 1) y++;
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            if (x > 0) x--;
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            if (x < WIDTH - 1) x++;
        }

        playerX = x;
        playerY = y;

        int exitX = WIDTH - 1;
        int exitY = HEIGHT - 1;

        int elapsedTime = time(NULL) - startTime;

        int remainingTime = GAME_TIME_LIMIT - elapsedTime;

        gameElapsedTime = time(NULL) - startTime;

        drawGame(playerX, playerY, bulletX, bulletY, bulletCount, exitX, exitY, remainingTime);

        for (int i = 0; i < bulletCount; i++) {
            if (bulletX[i] == playerX && bulletY[i] == playerY) {
                isGameOver = 1;
                break;
            }
        }

        if (isGameOver) {
            stopSoundEffect();
            playGameOverSoundEffect();
            printf("\n\t\t\t\t\t\t\t\t\t  게임 오버! \n");
            drawGame2OverAnimation();

            while (1) {

                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t      다시 시작하시겠습니까? (y/n): \n");
                printf("\n\t\t\t\t\t  ('n' 입력 시 게임이 바로 종료됩니다.)\n");

                choice = _getch();

                if (choice == 'y' || choice == 'Y') {

                    playSoundEffect("C:\\BGM\\스테이지2.wav", TRUE);
                    playerX = 0;
                    playerY = 0;
                    bulletCount = 0;
                    isGameOver = 0;
                    lastBulletTime = 0;
                    startTime = time(NULL);
                    system("cls");
                    break;
                }
                else if (choice == 'n' || choice == 'N') {
                    isGameOver = 1;
                    exit(1);
                    break;
                }

                clearConsole();
            }

            if (isGameOver || choice == 'y' || choice == 'Y') {
                continue;
            }
        }


        if (playerX == exitX && playerY == exitY) {
            stopSoundEffect();
            playSuccessSoundEffect();
            Sleep(2000);
            time_t endTime = time(NULL);
            drawGameSuccessAnimation();
            printf("\n\n\t\t\t\t\t\t       게임 성공!\n");
            printf("\n\t\t\t\t\t\t     걸린 시간: %d초\n", gameElapsedTime);
            isGameOver = 1;
            break;
        }

        if (remainingTime <= 0) {
            stopSoundEffect();
            playGameOverSoundEffect();
            drawGame2OverAnimation();
            while (1) {
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t      제한 시간이 초과되었습니다.\n");
                printf("\n\t\t\t\t\t      다시 시작하시겠습니까? (y/n): \n");
                printf("\n\t\t\t\t\t  ('n' 입력 시 게임이 바로 종료됩니다.)\n");

                choice = _getch();
                clearConsole();

                if (choice == 'y' || choice == 'Y') {
                    playSoundEffect("C:\\BGM\\스테이지2.wav", TRUE);
                    playerX = 0;
                    playerY = 0;
                    bulletCount = 0;
                    isGameOver = 0;
                    lastBulletTime = 0;
                    startTime = time(NULL);
                    break;
                }
                else if (choice == 'n' || choice == 'N') {
                    isGameOver = 1;
                    exit(1);
                }

                clearConsole();
            }

            if (isGameOver || choice == 'y' || choice == 'Y') {
                continue;
            }
        }

        int currentTime = GetTickCount();
        if (currentTime - lastBulletTime >= BULLET_DELAY) {
            lastBulletTime = currentTime;
            int numNewBullets = rand() % (BULLET_MAX - BULLET_MIN + 1) + BULLET_MIN;
            for (int i = 0; i < numNewBullets; i++) {
                if (bulletCount < WIDTH * 2 + HEIGHT * 2) {
                    int side = rand() % 4;
                    int startX, startY;
                    int directionX, directionY;
                    if (side == 0) {
                        startX = rand() % WIDTH;
                        startY = 0;
                        directionX = 0;
                        directionY = 1;
                    }
                    else if (side == 1) {
                        startX = rand() % WIDTH;
                        startY = HEIGHT - 1;
                        directionX = 0;
                        directionY = -1;
                    }
                    else if (side == 2) {
                        startX = 0;
                        startY = rand() % HEIGHT;
                        directionX = 1;
                        directionY = 0;
                    }
                    else {
                        startX = WIDTH - 1;
                        startY = rand() % HEIGHT;
                        directionX = -1;
                        directionY = 0;
                    }

                    bulletX[bulletCount] = startX;
                    bulletY[bulletCount] = startY;
                    bulletDirectionX[bulletCount] = directionX;
                    bulletDirectionY[bulletCount] = directionY;
                    bulletCount++;
                }
            }
        }

        for (int i = 0; i < bulletCount; i++) {
            bulletX[i] += bulletDirectionX[i];
            bulletY[i] += bulletDirectionY[i];
            if (bulletX[i] < 0 || bulletX[i] >= WIDTH || bulletY[i] < 0 || bulletY[i] >= HEIGHT) {
                for (int j = i + 1; j < bulletCount; j++) {
                    bulletX[j - 1] = bulletX[j];
                    bulletY[j - 1] = bulletY[j];
                    bulletDirectionX[j - 1] = bulletDirectionX[j];
                    bulletDirectionY[j - 1] = bulletDirectionY[j];
                }
                bulletCount--;
                i--;
            }
        }

        Sleep(20);
    }

    return 0;
}