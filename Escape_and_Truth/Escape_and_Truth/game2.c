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
#define BULLET_DELAY 500 // �и��� ������ ���� (500�и��� = 0.5��)
#define GAME_TIME_LIMIT 10 // ���� �ð� (�� ����)

void clearConsole() {
    system("cls");
}

void playSoundEffect(const char* filename, BOOL loop) {
    LPCTSTR soundFile = L"C:\\BGM\\��������2.wav";

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
        printf("\033[1;32m��\033[0m");
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
        printf("\033[1;32m��\033[0m");
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
    printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t�Ѿ��� ���� ���� ������ Ż���ϼ���.\n");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t(P: �÷��̾�, E: �ⱸ)\n");
    pos.Y += 3;
    SetConsoleCursorPosition(output, pos);
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t���� �ð�: %d�� \n", remainingTime);
}

// stage 1 ���� �ִϸ��̼�
void drawStageAnimation()
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
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE      2222\n");
        printf("                               S             T       A      A    G          E           2    2\n");
        printf("                               S             T       A      A    G          E          2      2\n");
        printf("                               S             T       A      A    G          E                2\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE         2\n");
        printf("                                    S        T       A      A    G      G   E              2\n");
        printf("                                    S        T       A      A    G      G   E            2\n");
        printf("                                    S        T       A      A    G      G   E           2   \n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE    22222222 \n");

        Sleep(500); // 0.5�� ����

        // �ܼ� ȭ�� ���� ���� (������)
        system("cls"); // �ܼ� ȭ�� �����
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("\n\n\n\n\n\n\n\n\n\n"); // �ִϸ��̼� ���� Ȯ��
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE      2222\n");
        printf("                               S             T       A      A    G          E           2    2\n");
        printf("                               S             T       A      A    G          E          2      2\n");
        printf("                               S             T       A      A    G          E                2\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE         2\n");
        printf("                                    S        T       A      A    G      G   E              2\n");
        printf("                                    S        T       A      A    G      G   E            2\n");
        printf("                                    S        T       A      A    G      G   E           2   \n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE    22222222 \n");

        Sleep(500); // 0.5�� ����

        // �ִϸ��̼� ���� �ð��� üũ�Ͽ� �ݺ��� ����
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

// ���� ���� �ִϸ��̼�
void drawGameSuccessAnimation() {
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

        // "GAME" �ܾ ǥ���ϴ� ASCII ��Ʈ (���)
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

        Sleep(500); // 0.5�� ����

        system("cls"); // �ܼ� ȭ�� �����

        printf("\n\n\n\n"); // �ִϸ��̼� ���� Ȯ��

        // �ܾ ���������� �̵���Ű�� �ִϸ��̼� (������)
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
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // �⺻������ �ǵ�����

        Sleep(500); // 0.5�� ����

        // �ִϸ��̼� ���� �ð��� üũ�Ͽ� �ݺ��� ����
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

// ���� ���� �ִϸ��̼�
void drawGame2OverAnimation() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    time_t startTime = time(NULL);  // �ִϸ��̼� ���� �ð�
    int animationDuration = 3;  // �ִϸ��̼� ���� �ð�(��)

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

        // �ִϸ��̼� ���� �ð��� üũ�Ͽ� �ݺ��� ����
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

// ���� �Լ�
int DodgeBullets() {
    COORD bufferSize = { 100, 10000 };
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
    system("mode con cols=140 lines=30");

    playSoundEffect("C:\\BGM\\��������2.wav", TRUE);

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
            printf("\n\t\t\t\t\t\t\t\t\t  ���� ����! \n");
            drawGame2OverAnimation();

            while (1) {

                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t      �ٽ� �����Ͻðڽ��ϱ�? (y/n): \n");
                printf("\n\t\t\t\t\t  ('n' �Է� �� ������ �ٷ� ����˴ϴ�.)\n");

                choice = _getch();

                if (choice == 'y' || choice == 'Y') {

                    playSoundEffect("C:\\BGM\\��������2.wav", TRUE);
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
            printf("\n\n\t\t\t\t\t\t       ���� ����!\n");
            printf("\n\t\t\t\t\t\t     �ɸ� �ð�: %d��\n", gameElapsedTime);
            isGameOver = 1;
            break;
        }

        if (remainingTime <= 0) {
            stopSoundEffect();
            playGameOverSoundEffect();
            drawGame2OverAnimation();
            while (1) {
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t      ���� �ð��� �ʰ��Ǿ����ϴ�.\n");
                printf("\n\t\t\t\t\t      �ٽ� �����Ͻðڽ��ϱ�? (y/n): \n");
                printf("\n\t\t\t\t\t  ('n' �Է� �� ������ �ٷ� ����˴ϴ�.)\n");

                choice = _getch();
                clearConsole();

                if (choice == 'y' || choice == 'Y') {
                    playSoundEffect("C:\\BGM\\��������2.wav", TRUE);
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