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

#define WIDTH 24
#define HEIGHT 18
#define LIMIT_TIME 100  // ���� �ð� (��)

int x = 0, y = 0;  // ó�� ��ġ ����
int game_over = 0;
int score = 0;

// �Ѻױ׸��� �׸��� �迭�� ����
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
int initial_picture[HEIGHT][WIDTH]; // �ʱ� �׸� ����� �迭

int board[HEIGHT][WIDTH] = { 0 };

// Ŀ�� ����� �Լ�
void hide_cursor(bool hide)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(output, &cursorInfo);
    cursorInfo.bVisible = !hide;
    SetConsoleCursorInfo(output, &cursorInfo);
}
void gotoxy(int x, int y)  // Ŀ���̵� �Լ� �κ�
{
    COORD XY = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}

// ���� ���� ���� �Լ�
void draw_board(int remaining_time)
{
    COORD pos = { 0,0 };  // Ŀ�� ��ġ ����
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);  // ǥ�� ��� �ڵ� ��������

    int startX = (140 - WIDTH * 2) / 2;  // ���� ���� X ��ǥ ���
    int startY = (30 - HEIGHT) / 2;  // ���� ���� Y ��ǥ ���
    int textStartX = startX + WIDTH + 6;  // �ؽ�Ʈ ���� X ��ǥ ���

    pos.X = startX;
    pos.Y = startY;

    SetConsoleCursorPosition(output, pos);  // Ŀ�� ��ġ�� �̵�

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == y && j == x)
            {
                printf("\033[34m��\033[0m");  // ������ ������ �Ķ������� ���
            }
            else if (initial_picture[i][j])
            {
                printf("��");  // ������ ����
            }
            else if (board[i][j])
            {
                printf("\033[36m��\033[0m");  // ������ ������ �ϴû����� ���
            }
            else
            {
                printf("\033[1;32m^\033[0m");  // �� ���� ���
            }
        }
        pos.Y++;  // Ŀ�� �� ��ġ ����
        pos.X = startX;
        SetConsoleCursorPosition(output, pos);  // Ŀ�� ��ġ�� �̵�
    }

    // ���� ���� ���
    pos.X = textStartX;
    pos.Y = startY;
    SetConsoleCursorPosition(output, pos);
    printf("����Ű�� ������ �簢���� ��� ����������.");

    // ���� �ð� ���
    pos.Y++;
    SetConsoleCursorPosition(output, pos);
    printf("���� �ð�: %d��            ", remaining_time);

    // �̵� Ƚ�� ���
    pos.Y++;
    SetConsoleCursorPosition(output, pos);
    printf("�̵� Ƚ��: %d", score);
}

// ����Ű ���� ���� �Լ�(�׸��� ����� ����)
int check_valid_move(int nx, int ny)
{
    if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT || !initial_picture[ny][nx] || board[ny][nx])
    {
        return 0;
    }
    return 1;
}

// ���� or ���� �˻� �Լ�
int check_success()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (initial_picture[i][j] == 1)
            {
                return 0; // �Ѻױ׸��� ����
            }
        }
    }
    return 1; // �Ѻױ׸��� ����
}

// �ʱ� �׸��� �����ϴ� �Լ�
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

// ���� �ʱ�ȭ �Լ�
void reset_game()
{
    x = 0;  // x ��ǥ �ʱ�ȭ
    y = 0;  // y ��ǥ �ʱ�ȭ
    game_over = 0;  // ���� ���� ���� �ʱ�ȭ
    score = 0;  // �̵� ȸ�� �ʱ�ȭ

    // �ʱ� �׸� ����
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            picture[i][j] = initial_picture[i][j];
            board[i][j] = 0;
        }
    }
}

// WAV ������ ����ϴ� �Լ�
void play_sound1(const char* filename, BOOL loop)
{
    LPCTSTR sound_file = L"C:\\BGM\\��������1.wav";  // �����ڵ� ���ڿ��� ����ϴ� ���

    // WAV ���� ���
    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
}

// WAV ���� ����� �����ϴ� �Լ�
void stop_sound1()
{
    // NULL ���� �̿��Ͽ� PlaySound �Լ� ȣ���Ͽ� ����
    PlaySound(NULL, NULL, SND_ASYNC);
}

// ���� ���� �� ȿ������ ����ϰ� ��������� ���ߴ� �Լ�
void handle_game_over1()
{
    LPCTSTR sound_file = L"C:\\BGM\\gameover.wav";  // ȿ���� ���� ��θ� ���� ����

    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME);
}

void handle_success1()
{
    LPCTSTR sound_file = L"C:\\BGM\\success.wav";  // ȿ���� ���� ��θ� ���� ����

    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME);
}

// Windows ȯ�濡�� �ܼ� â�� ����� �Լ�
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
    // Ŀ���� ���ϴ� ��ġ�� �̵�
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

// ��������1 ���� �ִϸ��̼�
void drawStageAnimation1()
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
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE      11\n");
        printf("                               S             T       A      A    G          E           1 1\n");
        printf("                               S             T       A      A    G          E          1  1\n");
        printf("                               S             T       A      A    G          E             1\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE       1\n");
        printf("                                    S        T       A      A    G      G   E             1\n");
        printf("                                    S        T       A      A    G      G   E             1\n");
        printf("                                    S        T       A      A    G      G   E             1 \n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE   11111111\n");

        Sleep(500); // 0.5�� ����

        // �ܼ� ȭ�� ���� ���� (������)
        system("cls"); // �ܼ� ȭ�� �����
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("\n\n\n\n\n\n\n\n\n\n"); // �ִϸ��̼� ���� Ȯ��
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE      11\n");
        printf("                               S             T       A      A    G          E           1 1\n");
        printf("                               S             T       A      A    G          E          1  1\n");
        printf("                               S             T       A      A    G          E             1\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE       1\n");
        printf("                                    S        T       A      A    G      G   E             1\n");
        printf("                                    S        T       A      A    G      G   E             1\n");
        printf("                                    S        T       A      A    G      G   E             1 \n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE   11111111\n");

        Sleep(500); // 0.5�� ����

        // �ִϸ��̼� ���� �ð��� üũ�Ͽ� �ݺ��� ����
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

// ���� ���� �ִϸ��̼�
void drawGame1OverAnimation() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    time_t startTime = time(NULL);  // �ִϸ��̼� ���� �ð�
    int animationDuration = 3;  // �ִϸ��̼� ���� �ð�(��)

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
        // �ִϸ��̼� ���� �ð��� üũ�Ͽ� �ݺ��� ����
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

// main �Լ�
void one_drawing() {


    COORD bufferSize = { 100, 10000 }; // ����, ����
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

    system("mode con cols=140 lines=30");

   
    hide_cursor(true);  // Ŀ�� �����
    save_initial_picture();  // �ʱ� �׸� ����

    // ����� ���
    play_sound1("C:\\BGM\\��������1.wav", TRUE);

    drawStageAnimation1();  // ��������1 �ִϸ��̼� ���
    clear_console();
    time_t start_time = time(NULL);  // ���� �ð��� ���� �ð����� ����
    drawLock(); // drawLock ���

    while (!game_over)  // ���� ������ �ƴϸ� �ݺ�
    {
        int elapsed_time = time(NULL) - start_time;  // ��� �ð� ���
        int remaining_time = LIMIT_TIME - elapsed_time;  // ���� �ð� ���

        if (remaining_time <= 0)  // ���� �ð��� ������ ���
        {
            remaining_time = 0;  // ���� �ð��� 0���� ����
            game_over = 0;  // ���� ����
            break;  // �ݺ��� ����
        }
        draw_board(remaining_time);  // ���� ������ ȣ��


        if (_kbhit())  // Ű �Է��� �ִ� ���
        {
            int ch = _getch();  // Ű �� �о��
            int nx = x, ny = y;  // �� ��ǥ�� ���� ��ǥ�� �ʱ�ȭ

            if (ch == 224)
            {
                switch (_getch())
                {
                case 72:  // ��
                    ny--;
                    break;
                case 80:  // �� 
                    ny++;
                    break;
                case 75:  // ��
                    nx--;
                    break;
                case 77:  // ��
                    nx++;
                    break;
                default:
                    continue;  // ����Ű�� �ƴ� ���, ���� �ݺ����� �ǳʶٱ�
                }
            }
            else
            {
                continue;  // Ư�� Ű�� �ƴ� ���, ���� �ݺ����� �ǳʶٱ�
            }

            if (check_valid_move(nx, ny))  // ����Ű �̵��� �ִ� ���
            {
                x = nx;  // x ��ǥ�� �� x ��ǥ�� ������Ʈ
                y = ny;  // y ��ǥ�� �� y ��ǥ�� ������Ʈ
                initial_picture[y][x] = 0;  // ������ �׷��� ��ġ�� 0���� �����Ͽ� ����
                board[y][x] = 1;  // ������ �ش� ��ġ�� 1�� �����Ͽ� ���
                score++;  // �̵� ȸ�� ����

                if (check_success())  // �Ѻ� �׸��� ���� ��
                {
                    game_over = 1;  // ���� ����
                    break;  // �ݺ��� ����
                }
            }
            else
            {  // �Ѻ� �׸��� ���� ��
                game_over = 0;  // ���� ����

                break;  // �ݺ��� ����
            }
        }
    }

    // ����� ����
    stop_sound();

    hide_cursor(false);  // Ŀ�� ���̱�
    draw_board(0);  // ���� ������ �׸�

    if (game_over)
    {
        printf("\n\t\t\t\t\t\t\t\t\t    ���� ����!\n\n");
        printf("\n\t\t\t\t\t\t\t\t\t    �� �ڹ��谡 Ǯ���ϴ�.");
        handle_success1();
        Sleep(2000); // ȿ���� ��� �ð� ���� ���
        drawLockopen(); // drawLockopen ���
    }
    else
    {
        printf("\n\n");
        clear_console();
        drawGame1OverAnimation();


        handle_game_over1(); // ȿ���� ���

        while (1) {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t   ������ �ٽ� �����Ͻðڽ��ϱ�? (y/n) ");
            printf("\n\n                                          ('n' �Է� �� ������ �ٷ� ����˴ϴ�.)\n");

            char choice = '\0';

            while (choice != 'y' && choice != 'n') {
                choice = _getch();
                if (choice == 'y' || choice == 'Y') {
                    clear_console();  // �ܼ� â �����
                    printf("\033[2J\033[H"); // ȭ���� ����� ANSI �̽������� ������ ���
                    save_initial_picture();  // �ʱ� �׸� ����
                    reset_game();  // ���� �ʱ�ȭ
                    start_time = time(NULL);  // ��� �ð� �ʱ�ȭ
                    draw_board(0);  // ���� �ٽ� �׸���
                    one_drawing();  // ���� �ٽ� ����(���� �Լ� �ٽ� ȣ��)
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