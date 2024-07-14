#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>  // PlaySound �Լ��� ����ϱ� ���� �߰�
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

#define WIDTH 100
#define HEIGHT 25

// WAV ������ ����ϴ� �Լ�
void play_sound3(const char* filename, BOOL loop)
{
    LPCTSTR sound_file = L"C:\\BGM\\��������3.wav";  // �����ڵ� ���ڿ��� ����ϴ� ���

    // WAV ���� ���
    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
}

// WAV ���� ����� �����ϴ� �Լ�
void stop_sound3()
{
    // NULL ���� �̿��Ͽ� PlaySound �Լ� ȣ���Ͽ� ����
    PlaySound(NULL, NULL, SND_ASYNC);
}

// ���� ���� �� ȿ������ ����ϰ� ��������� ���ߴ� �Լ�
void handle_game_over3()
{
    LPCTSTR sound_file = L"C:\\BGM\\gameover.wav";  // ȿ���� ���� ��θ� ���� ����

    PlaySound(sound_file, NULL, SND_ASYNC);
}

void handle_success3()
{
    LPCTSTR sound_file = L"C:\\BGM\\success.wav";  // ȿ���� ���� ��θ� ���� ����

    PlaySound(sound_file, NULL, SND_ASYNC);
}

// ĳ���� ��ġ
float fireboyX;
float fireboyY[] = { 23, 21, 18, 15, 13, 10, 8, 6, 5, 4 };
float fireboyJumpStartY[] = { 23, 21, 18, 15, 13, 10, 8, 6, 5, 4 }; // Fireboy�� ���� ���� ��ġ�� ���� ������ ����
float watergirlX;
float watergirlY[] = { 23, 21, 18, 15, 13, 10, 8, 6, 5, 4 };
float watergirlJumpStartY[] = { 23, 21, 18, 15, 13, 10, 8, 6, 5, 4 }; // Fireboy�� ���� ���� ��ġ�� ���� ������ ����

const float groundJumpHeight = 5; // ���� ����
const float platformJumpHeight = 5; // �÷��������� ���� ����
const float groundY[] = { 23, 21, 18, 15, 13, 10, 8, 6, 5, 4 };     // ������ ������ Y ��ǥ

// ����ġ Ȱ��ȭ ����
bool switchActive = false;
bool isOnSwitch = false;

// �� ĳ������ Ż�� ���¸� ���� ������ ����
bool fireboyExited = false;
bool watergirlExited = false;

float fireboyJumpHeightToUse; // ���� ���� �ʱ�ȭ
float watergirlJumpHeightToUse; // ���� ���� �ʱ�ȭ

// ������ ��ġ(����x)
float fireboyItemX, fireboyItemY;
float watergirlItemX, watergirlItemY;
bool fireboyItem = false;
bool watergirlItem = false;


// �ⱸ ��ġ
float exitX;
float exitY;
float exitDisplayY;

// ��Ż ����
typedef struct {
    int in_x, in_y;
    int out_x, out_y;
} PORTAL_INFO;
PORTAL_INFO portal_info[10];
int portal_count = 0;


//�ҹٴ� ���ٴ� ����ü ����
struct ObstacleInfo
{
    int startX;
    int endX;
    int y;
};

//���ٴ� �ҹٴ� ��ġ
struct ObstacleInfo obstacles[8] = {
    {60, 73, 8},
    {51, 68, 18},
    {5, 18, 8},
    {33, 49, 18}
};

// ����ġ ����
typedef struct {
    int x, y;
}SWITCH_INFO;

// ����ġ ���� �ʱ�ȭ
SWITCH_INFO switch_info[] = {
    { 8, 13 } // ����ġ ��ġ ����
};
int switch_count = sizeof(switch_info) / sizeof(SWITCH_INFO);

// ĳ���� �̵� �ӵ�
const float moveSpeed = 1;

// ĳ���� ����
bool fireboyJumping = false;
bool watergirlJumping = false;

//�÷��� ����ü
typedef struct Platform {
    int height;
    int start;
    int length;
    int jumpHeight;
    int obstacleType;  // 0: None, 1: ���ٴ�, 2: �ҹٴ�
} Platform;

// �÷��� �迭
Platform platforms[] = {
    {21, 20, 6, 5},
    {21, 75, 6, 5},
    {18, 27, 47, 5},   //�ҹٴ�+��(������), ���ٴ�+��(������)  ������ ����x
    {15, 20, 6, 5},
    {15, 75, 6, 5},
    {13, 5, 13, 5},      //����ġ ���� ����(������ �� ���ٴ� '-'�� ���)
    {13, 83, 12, 5},
    {10, 20, 6, 5},
    {10, 75, 6, 5},
    {8, 5, 13, 5},     //���ٴ�
    {8, 60, 13, 5},    //�ҹٴ�
    {5, 20, 6, 5},      //P(��Ż) ���� ��  23  ���� 2
    {4, 91, 9, 5},     //E(Ż�ⱸ)
    {6, 76, 13, 5}
};

int numPlatforms = sizeof(platforms) / sizeof(Platform);

// Ŀ�� ����� �Լ�
void hide_cursor3(bool hide)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(output, &cursorInfo);
    cursorInfo.bVisible = !hide;
    SetConsoleCursorInfo(output, &cursorInfo);
}

// ����Ű �Է� ó�� �Լ�
void handleInput()
{
    if (_kbhit())
    {
        int input = _getwch();
        switch (input)
        {
        case 'a':
        case 'A':
            if (fireboyX > 0)
                fireboyX -= moveSpeed; // �������� �̵�
            break;
        case 'd':
        case 'D':
            if (fireboyX < 140)
                fireboyX += moveSpeed; // ���������� �̵�
            break;
        case 'w':
        case 'W':
            if (!fireboyJumping)
            {
                if (fireboyY[0] == groundY[0])
                {
                    fireboyJumping = true; // ���� ����
                }
                else
                {
                    // �÷��� ���� �ִ��� Ȯ��
                    bool onPlatform = false;
                    for (int i = 0; i < numPlatforms; i++)
                    {
                        if (fireboyX >= platforms[i].start && fireboyX < platforms[i].start + platforms[i].length && fireboyY[0] + 1 == platforms[i].height)
                        {
                            onPlatform = true;
                            break;
                        }
                    }

                    if (onPlatform)
                        fireboyJumping = true; // ���� ����
                }
            }
            break;
        case 224: // ȭ��ǥ Ű �Է�
            input = _getwch(); // ���� ���� �Է� �ޱ�
            switch (input)
            {
            case 75: // ���� ȭ��ǥ
                if (watergirlX > 0)
                    watergirlX -= moveSpeed; // �������� �̵�
                break;
            case 77: // ������ ȭ��ǥ
                if (watergirlX > 0)
                    watergirlX += moveSpeed; // ���������� �̵�
                break;
            case 72: // ���� ȭ��ǥ
                if (!watergirlJumping)
                {
                    if (watergirlY[0] == groundY[0])
                    {
                        watergirlJumping = true; // ���� ����
                    }
                    else
                    {
                        // �÷��� ���� �ִ��� Ȯ��
                        bool onPlatform = false;
                        for (int i = 0; i < numPlatforms; i++)
                        {
                            if (watergirlX >= platforms[i].start && watergirlX < platforms[i].start + platforms[i].length && watergirlY[0] + 1 == platforms[i].height)
                            {
                                onPlatform = true;
                                break;
                            }
                        }

                        if (onPlatform)
                            watergirlJumping = true; // ���� ����
                    }
                }
                break;
            default:
                break;
            }
            break;
        case 'q':
        case 'Q':
            exit(0); // ���α׷� ����
            break;
        default:
            break;
        }
    }
}

// ���� ���� �÷��� ���� �ִ��� Ȯ���ϴ� �Լ�
bool isOnPlatform(float x, float y, Platform platforms[], int numPlatforms)
{
    for (int i = 0; i < numPlatforms; i++)
    {
        if (x >= platforms[i].start && x < platforms[i].start + platforms[i].length && y + 1 == platforms[i].height)
        {
            return true;
        }
    }
    return false;
}

// �÷��� �浹 �˻�
void checkPlatformCollision(Platform platforms[], int numPlatforms)
{
    for (int index = 0; index < sizeof(fireboyJumpStartY) / sizeof(fireboyJumpStartY[0]); index++) {
        if (fireboyJumping)
        {
            // ���� ���� Fireboy�� �÷��� �浹 �˻�
            for (int i = 0; i < numPlatforms; i++)
            {
                if (fireboyX >= platforms[i].start && fireboyX < platforms[i].start + platforms[i].length
                    && fireboyY[index] + 1 >= platforms[i].height && fireboyY[index] < platforms[i].height) // ĳ���Ͱ� �÷��� �Ʒ����� �����ϴ� ��츦 üũ
                {
                    fireboyJumping = false; // ���� ����
                    fireboyY[index] = fireboyJumpStartY[index]; // ĳ���ʹ� ���� ��ġ�� ���ư�
                    break;
                }
                else if (fireboyX >= platforms[i].start && fireboyX < platforms[i].start + platforms[i].length
                    && fireboyY[index] + 1 == platforms[i].height && fireboyY[index] <= fireboyJumpStartY[index] - fireboyJumpHeightToUse)
                {
                    fireboyJumping = false;
                    fireboyY[index] = platforms[i].height - 1; // �÷��� ���� �ö�
                    fireboyJumpStartY[index] = fireboyY[index]; // ���� ���� ��ġ�� �÷����� ���̷� ����
                    break;
                }
            }
        }
    }

    for (int index = 0; index < sizeof(watergirlJumpStartY) / sizeof(watergirlJumpStartY[0]); index++) {
        if (watergirlJumping)
        {
            // ���� ���� Fireboy�� �÷��� �浹 �˻�
            for (int i = 0; i < numPlatforms; i++)
            {
                if (watergirlX >= platforms[i].start && watergirlX < platforms[i].start + platforms[i].length
                    && watergirlY[index] + 1 >= platforms[i].height && watergirlY[index] < platforms[i].height) // ĳ���Ͱ� �÷��� �Ʒ����� �����ϴ� ��츦 üũ
                {
                    watergirlJumping = false; // ���� ����
                    watergirlY[index] = watergirlJumpStartY[index]; // ĳ���ʹ� ���� ��ġ�� ���ư�
                    break;
                }
                else if (watergirlX >= platforms[i].start && watergirlX < platforms[i].start + platforms[i].length
                    && watergirlY[index] + 1 == platforms[i].height && watergirlY[index] <= watergirlJumpStartY[index] - watergirlJumpHeightToUse)
                {
                    watergirlJumping = false;
                    watergirlY[index] = platforms[i].height - 1; // �÷��� ���� �ö�
                    watergirlJumpStartY[index] = watergirlY[index]; // ���� ���� ��ġ�� �÷����� ���̷� ����
                    break;
                }
            }
        }
    }
}

//���� ����
void handleJump()
{

    float fireboyJumpHeightToUse = groundJumpHeight;
    float watergirlJumpHeightToUse = groundJumpHeight;
    bool onPlatform = false;

    for (int index = 0; index < sizeof(fireboyY) / sizeof(fireboyY[0]); index++) {
        if (!fireboyJumping && isOnPlatform(fireboyX, fireboyY[index], platforms, numPlatforms)) {
            fireboyJumpStartY[index] = fireboyY[index];
            fireboyJumpHeightToUse = platformJumpHeight; // �÷��������� ���� ���̷� ����
        }
        else if (!fireboyJumping && fireboyY[index] >= groundY[0]) // ���鿡 �ִ� ���
        {
            fireboyJumpStartY[index] = fireboyY[index];
            fireboyJumpHeightToUse = groundJumpHeight; // ���� ���̸� ���� ���� ���̷� �ʱ�ȭ
        }


        else if (fireboyY[index] >= groundY[0])
        {
            fireboyJumpHeightToUse = groundJumpHeight;
        }

        if (fireboyJumping)
        {
            fireboyY[index] -= moveSpeed;

            if (fireboyY[index] <= fireboyJumpStartY[index] - fireboyJumpHeightToUse)
            {
                fireboyJumping = false;
                onPlatform = false;
                for (int i = 0; i < numPlatforms; i++)
                {
                    if (fireboyX >= platforms[i].start && fireboyX < platforms[i].start + platforms[i].length && fireboyY[index] + moveSpeed >= platforms[i].height
                        && fireboyY[index] <= fireboyJumpStartY[index] - fireboyJumpHeightToUse)
                    {
                        onPlatform = true;
                        fireboyJumpHeightToUse = platforms[i].jumpHeight;
                        break;
                    }
                }
                if (!onPlatform)
                {
                    fireboyY[index] += moveSpeed;
                }
            }
        }
        else if (fireboyY[index] < groundY[0] && !_kbhit())
        {
            onPlatform = false;
            for (int i = 0; i < numPlatforms; i++)
            {
                if (fireboyX >= platforms[i].start && fireboyX < platforms[i].start + platforms[i].length && fireboyY[index] + moveSpeed == platforms[i].height)
                {
                    onPlatform = true;
                    fireboyJumpHeightToUse = platforms[i].jumpHeight;
                    break;
                }
            }

            if (!onPlatform)
            {
                fireboyY[index] += moveSpeed;
                if (fireboyY[index] > groundY[0])
                {
                    fireboyY[index] = groundY[0];
                    fireboyJumpHeightToUse = groundJumpHeight;
                }
            }
        }
    }

    // Watergirl�� ���� ���� ó��
    for (int index = 0; index < sizeof(watergirlY) / sizeof(watergirlY[0]); index++) {
        if (!watergirlJumping && isOnPlatform(watergirlX, watergirlY[index], platforms, numPlatforms)) {
            watergirlJumpStartY[index] = watergirlY[index];
            watergirlJumpHeightToUse = platformJumpHeight; // �÷��������� ���� ���̷� ����
        }
        else if (!watergirlJumping && watergirlY[index] >= groundY[0]) // ���鿡 �ִ� ���
        {
            watergirlJumpStartY[index] = watergirlY[index];
            watergirlJumpHeightToUse = groundJumpHeight; // ���� ���̸� ���� ���� ���̷� �ʱ�ȭ
        }


        else if (watergirlY[index] >= groundY[0])
        {
            watergirlJumpHeightToUse = groundJumpHeight;
        }

        if (watergirlJumping)
        {
            watergirlY[index] -= moveSpeed;

            if (watergirlY[index] <= watergirlJumpStartY[index] - watergirlJumpHeightToUse)
            {
                watergirlJumping = false;
                onPlatform = false;
                for (int i = 0; i < numPlatforms; i++)
                {
                    if (watergirlX >= platforms[i].start && watergirlX < platforms[i].start + platforms[i].length && watergirlY[index] + moveSpeed >= platforms[i].height
                        && watergirlY[index] <= watergirlJumpStartY[index] - watergirlJumpHeightToUse)
                    {
                        onPlatform = true;
                        watergirlJumpHeightToUse = platforms[i].jumpHeight;
                        break;
                    }
                }
                if (!onPlatform)
                {
                    watergirlY[index] += moveSpeed;
                }
            }
        }
        else if (watergirlY[index] < groundY[0] && !_kbhit())
        {
            onPlatform = false;
            for (int i = 0; i < numPlatforms; i++)
            {
                if (watergirlX >= platforms[i].start && watergirlX < platforms[i].start + platforms[i].length && watergirlY[index] + moveSpeed == platforms[i].height)
                {
                    onPlatform = true;
                    watergirlJumpHeightToUse = platforms[i].jumpHeight;
                    break;
                }
            }

            if (!onPlatform)
            {
                watergirlY[index] += moveSpeed;
                if (watergirlY[index] > groundY[0])
                {
                    watergirlY[index] = groundY[0];
                    watergirlJumpHeightToUse = groundJumpHeight;
                }
            }
        }
    }
}

// ������ �浹 �˻�
void checkItemCollision()
{
    // Fireboy�� ������ �浹 �˻�
    if (fireboyX == fireboyItemX && fireboyY[0] == fireboyItemY)
    {
        fireboyItem = true;
        fireboyItemX = -1;
        fireboyItemY = -1;
    }

    // Watergirl�� ������ �浹 �˻�
    if (watergirlX == watergirlItemX && watergirlY[0] == watergirlItemY)
    {
        watergirlItem = true;
        watergirlItemX = -1;
        watergirlItemY = -1;
    }
}

// ��Ż �浹 �˻�
void checkPortalCollision()
{
    for (int i = 0; i < portal_count; i++)
    {
        // Fireboy�� ��Ż �浹 �˻�
        if ((fireboyX == portal_info[i].in_x && fireboyY[0] == portal_info[i].in_y) ||
            (fireboyX == portal_info[i].out_x && fireboyY[0] == portal_info[i].out_y && fireboyJumping))
        {
            fireboyX = (fireboyX == portal_info[i].in_x) ? portal_info[i].out_x : portal_info[i].in_x;
            fireboyY[0] = (fireboyY[0] == portal_info[i].in_y) ? portal_info[i].out_y : portal_info[i].in_y;
            break;
        }

        // Watergirl�� ��Ż �浹 �˻�
        if ((watergirlX == portal_info[i].in_x && watergirlY[0] == portal_info[i].in_y) ||
            (watergirlX == portal_info[i].out_x && watergirlY[0] == portal_info[i].out_y && watergirlJumping))
        {
            watergirlX = (watergirlX == portal_info[i].in_x) ? portal_info[i].out_x : portal_info[i].in_x;
            watergirlY[0] = (watergirlY[0] == portal_info[i].in_y) ? portal_info[i].out_y : portal_info[i].in_y;
            break;
        }
    }
}

// ���� ���� Ȯ��
bool checkGameOver()
{

    // ����ġ�� Ȱ��ȭ�Ǿ����� ���� ���� ĳ���Ͱ� ��ֹ��� �浹���� �� ���� ����
    if (!switchActive) {
        // Fireboy�� ���ٴ� �浹 �˻�
        if ((fireboyY[0] == 17 && fireboyX >= 33 && fireboyX < 49) || (fireboyY[0] == 7 && fireboyX >= 5 && fireboyX < 17))
        {
            return true;
        }

        // watergirl�� �ҹٴ� �浹 �˻�
        if ((watergirlY[0] == 17 && watergirlX >= 51 && watergirlX < 68) || (watergirlY[0] == 7 && watergirlX >= 60 && watergirlX < 72))
        {
            return true;
        }
    }
    return false;
}

void drawGameInfo3() {
    hide_cursor3(true);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition;
    cursorPosition.X = WIDTH + 3;
    cursorPosition.Y = 4;  // Start at this Y position
    int lines = 9;  // The number of lines you are going to print

    for (int i = 0; i < lines; i++) {
        SetConsoleCursorPosition(hConsole, cursorPosition);
        switch (i) {
        case 0:
            printf("\033[31m��  \033[31m�Ҽҳ�\033[0m \n");
            break;
        case 1:
            printf("\033[31m(����Ű: \033[0m \033[31mw a d)\033[0m\n");
            break;
        case 2:
            printf("\033[34m��  \033[34m���ҳ�\033[0m \n");
            break;
        case 3:
            printf("\033[34m(����Ű: \033[0m \033[34m�� �� ��)\033[0m \n");
            break;
        case 4:
            printf("E  Ż�ⱸ \n");
            break;
        case 5:
            printf("P  ��Ż \n");
            break;
        case 6:
            printf("S  ����ġ \n");
            break;
        case 7:
            printf("\033[31m~\033[0m   \033[31m�ҹٴ�\033[0m\n");
            break;
        case 8:
            printf("\033[34m~\033[0m   \033[34m���ٴ�\033[0m\n");
            break;
        default:
            break;
        }
        cursorPosition.Y += 2;  // Increment the Y position after each line
    }
}

void drawGame3() {

    // �÷��� �迭
    Platform platforms[] = {
        {21, 20, 6, 5},
        {21, 75, 6, 5},
        {18, 27, 47, 5},   //�ҹٴ�+��(������), ���ٴ�+��(������)  ������ ����x
        {15, 20, 6, 5},
        {15, 75, 6, 5},
        {13, 5, 13, 5},      //����ġ ���� ����(������ �� ���ٴ� '-'�� ���)
        {13, 83, 12, 5},
        {10, 20, 6, 5},
        {10, 75, 6, 5},
        {8, 5, 13, 5},     //���ٴ�
        {8, 60, 13, 5},    //�ҹٴ�
        {5, 20, 6, 5},      //P(��Ż) ���� ��  23  ���� 2
        {4, 91, 9, 5},     //E(Ż�ⱸ)
        {6, 76, 13, 5}
    };

    int numPlatforms = sizeof(platforms) / sizeof(Platform);

    // ������ ��ġ �迭 (����x)
    int itemPositions[][2] = {
        {18, 42}, // ������ ������
        {8, 10},   // �Ķ��� ������
        {18, 57},
        {8, 65}
    };

    int numItems = sizeof(itemPositions) / sizeof(itemPositions[0]);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(hConsole, cursorPosition);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {

            if (i == 0 || i == HEIGHT - 1) {
                printf("\033[1;32m-\033[0m");
            }
            else if (j == 0 || j == WIDTH - 1) {
                printf("\033[1;32m��\033[0m");

            }
            else {
                int isObstacle = 0;
                // ��ֹ� Ȯ��
                for (int k = 0; k < 4; k++) {
                    if ((i + 1) == obstacles[k].y && j >= obstacles[k].startX && j < obstacles[k].endX) {
                        isObstacle = k + 1; // ��ֹ� ��ȣ ���� (1 ~ 4)
                        break;
                    }
                }
                int isPlatform = 0;
                bool isPortal = false;
                // ��Ż �׸���             // ��Ż �Ա� (5, 23), �ⱸ (3, 92)
                for (int p = 0; p < portal_count; p++) {
                    if ((i + 1) == portal_info[p].in_y && j == portal_info[p].in_x) // ��Ż �Ա�
                    {
                        printf("P");
                        isPortal = true;
                        break;
                    }
                    else if ((i + 1) == portal_info[p].out_y && j == portal_info[p].out_x) // ��Ż �ⱸ
                    {
                        printf("P");
                        isPortal = true;
                        break;
                    }
                }

                if (!isPortal) {  // ��Ż�� �׷����� ���� ��쿡�� �Ʒ� ���� ����
                    if ((i + 1) == switch_info[0].y && j == switch_info[0].x) {
                        // Fireboy �Ǵ� Watergirl�� ����ġ ��ġ�� �ִ��� Ȯ��
                        if (j == (int)fireboyX && i == (int)fireboyY[0]) {
                            switchActive = true;
                        }
                        if (j == (int)watergirlX && i == (int)watergirlY[0]) {
                            switchActive = true;
                        }

                        printf("S");  // ����ġ S ���
                        j++;  // ���� �� ���ڸ� ����� ��, ���� ���� �ǳʶپ ���ڰ� ����� ǥ��(��µ� �׸� ������ �� ����) 
                    }
                    else if (i + 1 == exitDisplayY && j == exitX) {
                        printf("E");  //Ż�ⱸ E ���
                        j++;  // ���� �� ���ڸ� ����� ��, ���� ���� �ǳʶپ ���ڰ� ����� ǥ��(��µ� �׸� ������ �� ����) 
                    }
                    // ��ֹ� ó��
                    if (isObstacle) {
                        if (switchActive) {
                            printf("\033[1;32m-\033[0m"); // �� ���� (Ȱ��ȭ�� ����ġ)
                        }
                        else {
                            // ��ֹ� ���� ó��
                            if (isObstacle <= 2) { // ù��°, �ι�° ��ֹ��� �ҹٴ�
                                printf("\033[31m~\033[0m"); // �ҹٴ�
                            }
                            else { // ����°, �׹�° ��ֹ��� ���ٴ�
                                printf("\033[34m~\033[0m"); // ���ٴ�
                            }
                        }
                    }
                    else {
                        int platformIndex = -1;

                        for (int k = 0; k < numPlatforms; k++) {
                            if (i == platforms[k].height && j >= platforms[k].start && j < platforms[k].start + platforms[k].length) {
                                platformIndex = k;
                                break;
                            }
                        }

                        if (platformIndex != -1) {
                            if (platforms[platformIndex].obstacleType == 1) { // ���ٴ�
                                if (switchActive) {
                                    printf("\033[1;32m-\033[0m");
                                }
                                else {
                                    printf("\033[34m~\033[0m");  // ���ٴ�
                                }
                            }
                            else if (platforms[platformIndex].obstacleType == 2) { // �ҹٴ�
                                if (switchActive) {
                                    printf("\033[1;32m-\033[0m");
                                }
                                else {
                                    printf("\033[31m~\033[0m");  // �ҹٴ�
                                }
                            }
                            else {
                                printf("\033[1;32m-\033[0m");
                            }
                        }
                        else {
                            if (j == (int)fireboyX && i == (int)fireboyY[0]) {
                                if (fireboyItem)
                                    printf("\033[31m��\033[0m");  // ������ ĳ���͡�
                                else
                                    printf("\033[31m��\033[0m");  // ������ ĳ���͡�
                            }
                            else if (j == (int)watergirlX && i == (int)watergirlY[0]) {
                                if (watergirlItem)
                                    printf("\033[34m��\033[0m");  // �Ķ��� ĳ����
                                else
                                    printf("\033[34m��\033[0m");  // �Ķ��� ĳ����
                            }
                            else {
                                int isItem = 0;
                                for (int k = 0; k < numItems; k++) {
                                    if (i + 1 == itemPositions[k][0] && j == itemPositions[k][1]) {
                                        isItem = 1;
                                        break;
                                    }
                                }
                                if (isItem) {
                                    if ((i + 1 == 18 && j == 42) || (i + 1 == 8 && j == 10)) {
                                        printf("\033[31m��\033[0m");  // ������ ������(����x)
                                        j++; // ���� �� ���ڸ� ����� ��, ���� ���� �ǳʶپ ���ڰ� ����� ǥ��(��µ� �׸� ������ �� ����) 
                                    }
                                    else if ((i + 1 == 18 && j == 57) || (i + 1 == 8 && j == 65)) {
                                        printf("\033[34m��\033[0m");  // �Ķ��� ������(����x)
                                        j++; // ���� �� ���ڸ� ����� ��, ���� ���� �ǳʶپ ���ڰ� ����� ǥ��(��µ� �׸� ������ �� ����) 
                                    }
                                }
                                else if (j == WIDTH - 1) {
                                    printf("\033[1;32ml\033[0m\n");
                                }
                                else {
                                    printf(" ");
                                }
                            }
                        }
                    }
                }
                else if (j == WIDTH - 1) {
                    printf("\n");
                }
            }
        }
        printf("\n");
    }
    drawGameInfo3();
}

// Windows ȯ�濡�� �ܼ� â�� ����� �Լ�
void clear_console3() {
    system("cls");
}

// ����ġ �浹 �˻�
void checkSwitchCollision()
{
    // Fireboy�� ����ġ �浹 �˻�
    if (fireboyX == switch_info[0].x && fireboyY[0] == switch_info[0].y)
    {
        if (!switchActive && !isOnSwitch) {
            switchActive = true;

            // ��� ��ֹ��� ����
            for (int i = 0; i < 4; i++) {
                obstacles[i].startX = -1;
                obstacles[i].endX = -1;
                obstacles[i].y = -1;
            }
            // ��� �÷����� ��ֹ� Ÿ�� ����
            for (int i = 0; i < numPlatforms; i++) {
                platforms[i].obstacleType = 0;
            }
        }
        isOnSwitch = true;
    }
    // Watergirl�� ����ġ �浹 �˻�
    else if (watergirlX == switch_info[0].x && watergirlY[0] == switch_info[0].y)
    {
        if (!switchActive && !isOnSwitch) {
            switchActive = true;

            // ��� ��ֹ��� ����
            for (int i = 0; i < 4; i++) {
                obstacles[i].startX = -1;
                obstacles[i].endX = -1;
                obstacles[i].y = -1;
            }
            // ��� �÷����� ��ֹ� Ÿ�� ����
            for (int i = 0; i < numPlatforms; i++) {
                platforms[i].obstacleType = 0;
            }
        }
        isOnSwitch = true;
    }
    else {
        isOnSwitch = false;
    }
}

//stage 3 ���� �ִϸ��̼�
void drawStageAnimation3()
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
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE     33333\n");
        printf("                               S             T       A      A    G          E          3     3\n");
        printf("                               S             T       A      A    G          E                3\n");
        printf("                               S             T       A      A    G          E              3\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE     33\n");
        printf("                                    S        T       A      A    G      G   E              3\n");
        printf("                                    S        T       A      A    G      G   E                3\n");
        printf("                                    S        T       A      A    G      G   E                3   \n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE     33333 \n");

        Sleep(500); // 0.5�� ����

        // �ܼ� ȭ�� ���� ���� (������)
        system("cls"); // �ܼ� ȭ�� �����
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("\n\n\n\n\n\n\n\n\n\n"); // �ִϸ��̼� ���� Ȯ��
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE     33333\n");
        printf("                               S             T       A      A    G          E          3     3\n");
        printf("                               S             T       A      A    G          E                3\n");
        printf("                               S             T       A      A    G          E              3\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE     33\n");
        printf("                                    S        T       A      A    G      G   E              3\n");
        printf("                                    S        T       A      A    G      G   E                3\n");
        printf("                                    S        T       A      A    G      G   E                3   \n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE     33333 \n");

        Sleep(500); // 0.5�� ����

        // �ִϸ��̼� ���� �ð��� üũ�Ͽ� �ݺ��� ����
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

// ���� ����
void gameLoop()
{
    bool gameClear = false;
    // ������� ���
    play_sound3("C:\\BGM\\��������3.wav", TRUE);
    while (true)
    {
        // Ű �Է� ó��
        handleInput();

        // ���� ó��    
        handleJump();

        // �÷��� �浹 �˻�
        checkPlatformCollision(platforms, numPlatforms);

        // ��Ż �浹 �˻�
        checkPortalCollision();

        // ����ġ �浹 �˻�
        checkSwitchCollision();

        // �� ĳ������ Ż�� ���� Ȯ��
        if ((int)fireboyX == exitX && (int)fireboyY[0] == exitY)
            fireboyExited = true;
        if ((int)watergirlX == exitX && (int)watergirlY[0] == exitY)
            watergirlExited = true;

        // ���� Ŭ���� Ȯ��
        if (fireboyExited && watergirlExited) {
            gameClear = true;
            break;
        }

        // ���� ���� Ȯ��
        if (checkGameOver()) {
            handle_game_over3();
            printf("\n\n\n\n\n���� ����! \n");
            Sleep(1000);  // 1�� ���
            while (1) {
                printf("�ٽ� �����Ͻðڽ��ϱ�? (y/n): ");

                char choice = '\0';

                while (choice != 'y' && choice != 'n') {
                    choice = _getch();
                    if (choice == 'y' || choice == 'Y') {
                        // ������ �ٽ� �����ϱ� ���� ���� �ʱ�ȭ
                        play_sound3("C:\\BGM\\��������3.wav", TRUE);
                        // ����ġ Ȱ��ȭ ����
                        bool switchActive = false;
                        bool isOnSwitch = false;
                        //ĳ���� ��ġ �ʱ�ȭ
                        fireboyX = 5;
                        fireboyY[0] = 23;
                        watergirlX = 94;
                        watergirlY[0] = 23;
                        break;
                    }
                    else if (choice == 'n' || choice == 'N') {
                        printf("���� ����\n");
                        return; // ���� ����
                    }
                }

                // �ܼ� â �����
                clear_console3();
                if (checkGameOver || choice == 'y' || choice == 'Y') {
                    break;
                }
            }
        }
        // ȭ�� �׸���
        drawGame3();
    }
    if (gameClear) {
        stop_sound3();
        // ���� ���� ȿ���� ���
        handle_success3();
        printf("\n\n\n\n\n���� ����!\n");
        Sleep(2000);  // 2�� ���
    }
}

void WaterFire_Game()
{

    COORD bufferSize = { 100, 10000 }; // ����, ����
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

    system("mode con cols=140 lines=30");

    hide_cursor3(true);  // Ŀ�� �����
    drawStageAnimation3();
    clear_console3();

    fireboyX = 5;
    fireboyY[0] = 23;
    watergirlX = 94;
    watergirlY[0] = 23;

    exitX = 97;
    exitDisplayY = groundY[9]; // ȭ�鿡 ����ϱ� ���� ������ ��ġ
    exitY = groundY[9] - 1;   // �浹 ������ ���� ���� ��ġ

    // ��Ż ���� ����
    portal_info[portal_count].in_x = 23;
    portal_info[portal_count].in_y = 3;
    portal_info[portal_count].out_x = 92;
    portal_info[portal_count].out_y = 2;
    portal_count++;

    gameLoop();
    return 0;
}