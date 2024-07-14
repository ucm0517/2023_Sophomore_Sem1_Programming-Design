#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>  // PlaySound 함수를 사용하기 위해 추가
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

#define WIDTH 100
#define HEIGHT 25

// WAV 파일을 재생하는 함수
void play_sound3(const char* filename, BOOL loop)
{
    LPCTSTR sound_file = L"C:\\BGM\\스테이지3.wav";  // 유니코드 문자열을 사용하는 경우

    // WAV 파일 재생
    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
}

// WAV 파일 재생을 중지하는 함수
void stop_sound3()
{
    // NULL 값을 이용하여 PlaySound 함수 호출하여 중지
    PlaySound(NULL, NULL, SND_ASYNC);
}

// 게임 오버 시 효과음을 출력하고 배경음악을 멈추는 함수
void handle_game_over3()
{
    LPCTSTR sound_file = L"C:\\BGM\\gameover.wav";  // 효과음 파일 경로를 직접 지정

    PlaySound(sound_file, NULL, SND_ASYNC);
}

void handle_success3()
{
    LPCTSTR sound_file = L"C:\\BGM\\success.wav";  // 효과음 파일 경로를 직접 지정

    PlaySound(sound_file, NULL, SND_ASYNC);
}

// 캐릭터 위치
float fireboyX;
float fireboyY[] = { 23, 21, 18, 15, 13, 10, 8, 6, 5, 4 };
float fireboyJumpStartY[] = { 23, 21, 18, 15, 13, 10, 8, 6, 5, 4 }; // Fireboy의 점프 시작 위치를 전역 변수로 선언
float watergirlX;
float watergirlY[] = { 23, 21, 18, 15, 13, 10, 8, 6, 5, 4 };
float watergirlJumpStartY[] = { 23, 21, 18, 15, 13, 10, 8, 6, 5, 4 }; // Fireboy의 점프 시작 위치를 전역 변수로 선언

const float groundJumpHeight = 5; // 점프 높이
const float platformJumpHeight = 5; // 플랫폼에서의 점프 높이
const float groundY[] = { 23, 21, 18, 15, 13, 10, 8, 6, 5, 4 };     // 착지할 지면의 Y 좌표

// 스위치 활성화 여부
bool switchActive = false;
bool isOnSwitch = false;

// 각 캐릭터의 탈출 상태를 전역 변수로 저장
bool fireboyExited = false;
bool watergirlExited = false;

float fireboyJumpHeightToUse; // 전역 변수 초기화
float watergirlJumpHeightToUse; // 전역 변수 초기화

// 아이템 위치(구현x)
float fireboyItemX, fireboyItemY;
float watergirlItemX, watergirlItemY;
bool fireboyItem = false;
bool watergirlItem = false;


// 출구 위치
float exitX;
float exitY;
float exitDisplayY;

// 포탈 정보
typedef struct {
    int in_x, in_y;
    int out_x, out_y;
} PORTAL_INFO;
PORTAL_INFO portal_info[10];
int portal_count = 0;


//불바다 물바다 구조체 선언
struct ObstacleInfo
{
    int startX;
    int endX;
    int y;
};

//물바다 불바다 위치
struct ObstacleInfo obstacles[8] = {
    {60, 73, 8},
    {51, 68, 18},
    {5, 18, 8},
    {33, 49, 18}
};

// 스위치 정보
typedef struct {
    int x, y;
}SWITCH_INFO;

// 스위치 정보 초기화
SWITCH_INFO switch_info[] = {
    { 8, 13 } // 스위치 위치 설정
};
int switch_count = sizeof(switch_info) / sizeof(SWITCH_INFO);

// 캐릭터 이동 속도
const float moveSpeed = 1;

// 캐릭터 상태
bool fireboyJumping = false;
bool watergirlJumping = false;

//플랫폼 구조체
typedef struct Platform {
    int height;
    int start;
    int length;
    int jumpHeight;
    int obstacleType;  // 0: None, 1: 물바다, 2: 불바다
} Platform;

// 플랫폼 배열
Platform platforms[] = {
    {21, 20, 6, 5},
    {21, 75, 6, 5},
    {18, 27, 47, 5},   //불바다+물(아이템), 물바다+불(아이템)  아이템 구현x
    {15, 20, 6, 5},
    {15, 75, 6, 5},
    {13, 5, 13, 5},      //스위치 설정 발판(누르면 불 물바다 '-'로 출력)
    {13, 83, 12, 5},
    {10, 20, 6, 5},
    {10, 75, 6, 5},
    {8, 5, 13, 5},     //물바다
    {8, 60, 13, 5},    //불바다
    {5, 20, 6, 5},      //P(포탈) 들어가는 곳  23  높이 2
    {4, 91, 9, 5},     //E(탈출구)
    {6, 76, 13, 5}
};

int numPlatforms = sizeof(platforms) / sizeof(Platform);

// 커서 숨기기 함수
void hide_cursor3(bool hide)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(output, &cursorInfo);
    cursorInfo.bVisible = !hide;
    SetConsoleCursorInfo(output, &cursorInfo);
}

// 방향키 입력 처리 함수
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
                fireboyX -= moveSpeed; // 왼쪽으로 이동
            break;
        case 'd':
        case 'D':
            if (fireboyX < 140)
                fireboyX += moveSpeed; // 오른쪽으로 이동
            break;
        case 'w':
        case 'W':
            if (!fireboyJumping)
            {
                if (fireboyY[0] == groundY[0])
                {
                    fireboyJumping = true; // 점프 시작
                }
                else
                {
                    // 플랫폼 위에 있는지 확인
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
                        fireboyJumping = true; // 점프 시작
                }
            }
            break;
        case 224: // 화살표 키 입력
            input = _getwch(); // 다음 문자 입력 받기
            switch (input)
            {
            case 75: // 왼쪽 화살표
                if (watergirlX > 0)
                    watergirlX -= moveSpeed; // 왼쪽으로 이동
                break;
            case 77: // 오른쪽 화살표
                if (watergirlX > 0)
                    watergirlX += moveSpeed; // 오른쪽으로 이동
                break;
            case 72: // 위쪽 화살표
                if (!watergirlJumping)
                {
                    if (watergirlY[0] == groundY[0])
                    {
                        watergirlJumping = true; // 점프 시작
                    }
                    else
                    {
                        // 플랫폼 위에 있는지 확인
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
                            watergirlJumping = true; // 점프 시작
                    }
                }
                break;
            default:
                break;
            }
            break;
        case 'q':
        case 'Q':
            exit(0); // 프로그램 종료
            break;
        default:
            break;
        }
    }
}

// 점프 도중 플랫폼 위에 있는지 확인하는 함수
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

// 플랫폼 충돌 검사
void checkPlatformCollision(Platform platforms[], int numPlatforms)
{
    for (int index = 0; index < sizeof(fireboyJumpStartY) / sizeof(fireboyJumpStartY[0]); index++) {
        if (fireboyJumping)
        {
            // 점프 중인 Fireboy의 플랫폼 충돌 검사
            for (int i = 0; i < numPlatforms; i++)
            {
                if (fireboyX >= platforms[i].start && fireboyX < platforms[i].start + platforms[i].length
                    && fireboyY[index] + 1 >= platforms[i].height && fireboyY[index] < platforms[i].height) // 캐릭터가 플랫폼 아래에서 점프하는 경우를 체크
                {
                    fireboyJumping = false; // 점프 중지
                    fireboyY[index] = fireboyJumpStartY[index]; // 캐릭터는 원래 위치로 돌아감
                    break;
                }
                else if (fireboyX >= platforms[i].start && fireboyX < platforms[i].start + platforms[i].length
                    && fireboyY[index] + 1 == platforms[i].height && fireboyY[index] <= fireboyJumpStartY[index] - fireboyJumpHeightToUse)
                {
                    fireboyJumping = false;
                    fireboyY[index] = platforms[i].height - 1; // 플랫폼 위에 올라감
                    fireboyJumpStartY[index] = fireboyY[index]; // 점프 시작 위치를 플랫폼의 높이로 설정
                    break;
                }
            }
        }
    }

    for (int index = 0; index < sizeof(watergirlJumpStartY) / sizeof(watergirlJumpStartY[0]); index++) {
        if (watergirlJumping)
        {
            // 점프 중인 Fireboy의 플랫폼 충돌 검사
            for (int i = 0; i < numPlatforms; i++)
            {
                if (watergirlX >= platforms[i].start && watergirlX < platforms[i].start + platforms[i].length
                    && watergirlY[index] + 1 >= platforms[i].height && watergirlY[index] < platforms[i].height) // 캐릭터가 플랫폼 아래에서 점프하는 경우를 체크
                {
                    watergirlJumping = false; // 점프 중지
                    watergirlY[index] = watergirlJumpStartY[index]; // 캐릭터는 원래 위치로 돌아감
                    break;
                }
                else if (watergirlX >= platforms[i].start && watergirlX < platforms[i].start + platforms[i].length
                    && watergirlY[index] + 1 == platforms[i].height && watergirlY[index] <= watergirlJumpStartY[index] - watergirlJumpHeightToUse)
                {
                    watergirlJumping = false;
                    watergirlY[index] = platforms[i].height - 1; // 플랫폼 위에 올라감
                    watergirlJumpStartY[index] = watergirlY[index]; // 점프 시작 위치를 플랫폼의 높이로 설정
                    break;
                }
            }
        }
    }
}

//점프 로직
void handleJump()
{

    float fireboyJumpHeightToUse = groundJumpHeight;
    float watergirlJumpHeightToUse = groundJumpHeight;
    bool onPlatform = false;

    for (int index = 0; index < sizeof(fireboyY) / sizeof(fireboyY[0]); index++) {
        if (!fireboyJumping && isOnPlatform(fireboyX, fireboyY[index], platforms, numPlatforms)) {
            fireboyJumpStartY[index] = fireboyY[index];
            fireboyJumpHeightToUse = platformJumpHeight; // 플랫폼에서의 점프 높이로 설정
        }
        else if (!fireboyJumping && fireboyY[index] >= groundY[0]) // 지면에 있는 경우
        {
            fireboyJumpStartY[index] = fireboyY[index];
            fireboyJumpHeightToUse = groundJumpHeight; // 점프 높이를 지면 점프 높이로 초기화
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

    // Watergirl의 점프 동작 처리
    for (int index = 0; index < sizeof(watergirlY) / sizeof(watergirlY[0]); index++) {
        if (!watergirlJumping && isOnPlatform(watergirlX, watergirlY[index], platforms, numPlatforms)) {
            watergirlJumpStartY[index] = watergirlY[index];
            watergirlJumpHeightToUse = platformJumpHeight; // 플랫폼에서의 점프 높이로 설정
        }
        else if (!watergirlJumping && watergirlY[index] >= groundY[0]) // 지면에 있는 경우
        {
            watergirlJumpStartY[index] = watergirlY[index];
            watergirlJumpHeightToUse = groundJumpHeight; // 점프 높이를 지면 점프 높이로 초기화
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

// 아이템 충돌 검사
void checkItemCollision()
{
    // Fireboy와 아이템 충돌 검사
    if (fireboyX == fireboyItemX && fireboyY[0] == fireboyItemY)
    {
        fireboyItem = true;
        fireboyItemX = -1;
        fireboyItemY = -1;
    }

    // Watergirl과 아이템 충돌 검사
    if (watergirlX == watergirlItemX && watergirlY[0] == watergirlItemY)
    {
        watergirlItem = true;
        watergirlItemX = -1;
        watergirlItemY = -1;
    }
}

// 포탈 충돌 검사
void checkPortalCollision()
{
    for (int i = 0; i < portal_count; i++)
    {
        // Fireboy와 포탈 충돌 검사
        if ((fireboyX == portal_info[i].in_x && fireboyY[0] == portal_info[i].in_y) ||
            (fireboyX == portal_info[i].out_x && fireboyY[0] == portal_info[i].out_y && fireboyJumping))
        {
            fireboyX = (fireboyX == portal_info[i].in_x) ? portal_info[i].out_x : portal_info[i].in_x;
            fireboyY[0] = (fireboyY[0] == portal_info[i].in_y) ? portal_info[i].out_y : portal_info[i].in_y;
            break;
        }

        // Watergirl과 포탈 충돌 검사
        if ((watergirlX == portal_info[i].in_x && watergirlY[0] == portal_info[i].in_y) ||
            (watergirlX == portal_info[i].out_x && watergirlY[0] == portal_info[i].out_y && watergirlJumping))
        {
            watergirlX = (watergirlX == portal_info[i].in_x) ? portal_info[i].out_x : portal_info[i].in_x;
            watergirlY[0] = (watergirlY[0] == portal_info[i].in_y) ? portal_info[i].out_y : portal_info[i].in_y;
            break;
        }
    }
}

// 게임 오버 확인
bool checkGameOver()
{

    // 스위치가 활성화되어있지 않을 때만 캐릭터가 장애물에 충돌했을 때 게임 오버
    if (!switchActive) {
        // Fireboy와 물바다 충돌 검사
        if ((fireboyY[0] == 17 && fireboyX >= 33 && fireboyX < 49) || (fireboyY[0] == 7 && fireboyX >= 5 && fireboyX < 17))
        {
            return true;
        }

        // watergirl와 불바다 충돌 검사
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
            printf("\033[31m♀  \033[31m불소년\033[0m \n");
            break;
        case 1:
            printf("\033[31m(방향키: \033[0m \033[31mw a d)\033[0m\n");
            break;
        case 2:
            printf("\033[34m♀  \033[34m물소녀\033[0m \n");
            break;
        case 3:
            printf("\033[34m(방향키: \033[0m \033[34m← ↑ →)\033[0m \n");
            break;
        case 4:
            printf("E  탈출구 \n");
            break;
        case 5:
            printf("P  포탈 \n");
            break;
        case 6:
            printf("S  스위치 \n");
            break;
        case 7:
            printf("\033[31m~\033[0m   \033[31m불바다\033[0m\n");
            break;
        case 8:
            printf("\033[34m~\033[0m   \033[34m물바다\033[0m\n");
            break;
        default:
            break;
        }
        cursorPosition.Y += 2;  // Increment the Y position after each line
    }
}

void drawGame3() {

    // 플랫폼 배열
    Platform platforms[] = {
        {21, 20, 6, 5},
        {21, 75, 6, 5},
        {18, 27, 47, 5},   //불바다+물(아이템), 물바다+불(아이템)  아이템 구현x
        {15, 20, 6, 5},
        {15, 75, 6, 5},
        {13, 5, 13, 5},      //스위치 설정 발판(누르면 불 물바다 '-'로 출력)
        {13, 83, 12, 5},
        {10, 20, 6, 5},
        {10, 75, 6, 5},
        {8, 5, 13, 5},     //물바다
        {8, 60, 13, 5},    //불바다
        {5, 20, 6, 5},      //P(포탈) 들어가는 곳  23  높이 2
        {4, 91, 9, 5},     //E(탈출구)
        {6, 76, 13, 5}
    };

    int numPlatforms = sizeof(platforms) / sizeof(Platform);

    // 아이템 위치 배열 (구현x)
    int itemPositions[][2] = {
        {18, 42}, // 빨간색 아이템
        {8, 10},   // 파란색 아이템
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
                printf("\033[1;32mㅣ\033[0m");

            }
            else {
                int isObstacle = 0;
                // 장애물 확인
                for (int k = 0; k < 4; k++) {
                    if ((i + 1) == obstacles[k].y && j >= obstacles[k].startX && j < obstacles[k].endX) {
                        isObstacle = k + 1; // 장애물 번호 저장 (1 ~ 4)
                        break;
                    }
                }
                int isPlatform = 0;
                bool isPortal = false;
                // 포탈 그리기             // 포탈 입구 (5, 23), 출구 (3, 92)
                for (int p = 0; p < portal_count; p++) {
                    if ((i + 1) == portal_info[p].in_y && j == portal_info[p].in_x) // 포탈 입구
                    {
                        printf("P");
                        isPortal = true;
                        break;
                    }
                    else if ((i + 1) == portal_info[p].out_y && j == portal_info[p].out_x) // 포탈 출구
                    {
                        printf("P");
                        isPortal = true;
                        break;
                    }
                }

                if (!isPortal) {  // 포탈이 그려지지 않은 경우에만 아래 로직 실행
                    if ((i + 1) == switch_info[0].y && j == switch_info[0].x) {
                        // Fireboy 또는 Watergirl이 스위치 위치에 있는지 확인
                        if (j == (int)fireboyX && i == (int)fireboyY[0]) {
                            switchActive = true;
                        }
                        if (j == (int)watergirlX && i == (int)watergirlY[0]) {
                            switchActive = true;
                        }

                        printf("S");  // 스위치 S 출력
                        j++;  // 이중 폭 문자를 출력할 때, 다음 셀을 건너뛰어서 문자가 제대로 표시(출력된 그림 깨지는 것 방지) 
                    }
                    else if (i + 1 == exitDisplayY && j == exitX) {
                        printf("E");  //탈출구 E 출력
                        j++;  // 이중 폭 문자를 출력할 때, 다음 셀을 건너뛰어서 문자가 제대로 표시(출력된 그림 깨지는 것 방지) 
                    }
                    // 장애물 처리
                    if (isObstacle) {
                        if (switchActive) {
                            printf("\033[1;32m-\033[0m"); // 빈 공간 (활성화된 스위치)
                        }
                        else {
                            // 장애물 색상 처리
                            if (isObstacle <= 2) { // 첫번째, 두번째 장애물은 불바다
                                printf("\033[31m~\033[0m"); // 불바다
                            }
                            else { // 세번째, 네번째 장애물은 물바다
                                printf("\033[34m~\033[0m"); // 물바다
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
                            if (platforms[platformIndex].obstacleType == 1) { // 물바다
                                if (switchActive) {
                                    printf("\033[1;32m-\033[0m");
                                }
                                else {
                                    printf("\033[34m~\033[0m");  // 물바다
                                }
                            }
                            else if (platforms[platformIndex].obstacleType == 2) { // 불바다
                                if (switchActive) {
                                    printf("\033[1;32m-\033[0m");
                                }
                                else {
                                    printf("\033[31m~\033[0m");  // 불바다
                                }
                            }
                            else {
                                printf("\033[1;32m-\033[0m");
                            }
                        }
                        else {
                            if (j == (int)fireboyX && i == (int)fireboyY[0]) {
                                if (fireboyItem)
                                    printf("\033[31m♀\033[0m");  // 빨간색 캐릭터♀
                                else
                                    printf("\033[31m♀\033[0m");  // 빨간색 캐릭터♀
                            }
                            else if (j == (int)watergirlX && i == (int)watergirlY[0]) {
                                if (watergirlItem)
                                    printf("\033[34m♀\033[0m");  // 파란색 캐릭터
                                else
                                    printf("\033[34m♀\033[0m");  // 파란색 캐릭터
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
                                        printf("\033[31m㉿\033[0m");  // 빨간색 아이템(구현x)
                                        j++; // 이중 폭 문자를 출력할 때, 다음 셀을 건너뛰어서 문자가 제대로 표시(출력된 그림 깨지는 것 방지) 
                                    }
                                    else if ((i + 1 == 18 && j == 57) || (i + 1 == 8 && j == 65)) {
                                        printf("\033[34m㉿\033[0m");  // 파란색 아이템(구현x)
                                        j++; // 이중 폭 문자를 출력할 때, 다음 셀을 건너뛰어서 문자가 제대로 표시(출력된 그림 깨지는 것 방지) 
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

// Windows 환경에서 콘솔 창을 지우는 함수
void clear_console3() {
    system("cls");
}

// 스위치 충돌 검사
void checkSwitchCollision()
{
    // Fireboy와 스위치 충돌 검사
    if (fireboyX == switch_info[0].x && fireboyY[0] == switch_info[0].y)
    {
        if (!switchActive && !isOnSwitch) {
            switchActive = true;

            // 모든 장애물을 제거
            for (int i = 0; i < 4; i++) {
                obstacles[i].startX = -1;
                obstacles[i].endX = -1;
                obstacles[i].y = -1;
            }
            // 모든 플랫폼의 장애물 타입 변경
            for (int i = 0; i < numPlatforms; i++) {
                platforms[i].obstacleType = 0;
            }
        }
        isOnSwitch = true;
    }
    // Watergirl과 스위치 충돌 검사
    else if (watergirlX == switch_info[0].x && watergirlY[0] == switch_info[0].y)
    {
        if (!switchActive && !isOnSwitch) {
            switchActive = true;

            // 모든 장애물을 제거
            for (int i = 0; i < 4; i++) {
                obstacles[i].startX = -1;
                obstacles[i].endX = -1;
                obstacles[i].y = -1;
            }
            // 모든 플랫폼의 장애물 타입 변경
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

//stage 3 시작 애니메이션
void drawStageAnimation3()
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
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE     33333\n");
        printf("                               S             T       A      A    G          E          3     3\n");
        printf("                               S             T       A      A    G          E                3\n");
        printf("                               S             T       A      A    G          E              3\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE     33\n");
        printf("                                    S        T       A      A    G      G   E              3\n");
        printf("                                    S        T       A      A    G      G   E                3\n");
        printf("                                    S        T       A      A    G      G   E                3   \n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE     33333 \n");

        Sleep(500); // 0.5초 지연

        // 콘솔 화면 색상 변경 (빨간색)
        system("cls"); // 콘솔 화면 지우기
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("\n\n\n\n\n\n\n\n\n\n"); // 애니메이션 공간 확보
        printf("                               SSSSSS    TTTTTTTTT   AAAAAAAA    GGGGGGGG   EEEEEEE     33333\n");
        printf("                               S             T       A      A    G          E          3     3\n");
        printf("                               S             T       A      A    G          E                3\n");
        printf("                               S             T       A      A    G          E              3\n");
        printf("                               SSSSSS        T       AAAAAAAA    G    GGGG  EEEEEEE     33\n");
        printf("                                    S        T       A      A    G      G   E              3\n");
        printf("                                    S        T       A      A    G      G   E                3\n");
        printf("                                    S        T       A      A    G      G   E                3   \n");
        printf("                               SSSSSS        T       A      A    GGGGGGGG   EEEEEEE     33333 \n");

        Sleep(500); // 0.5초 지연

        // 애니메이션 지속 시간을 체크하여 반복문 종료
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= animationDuration) {
            break;
        }
    }
}

// 게임 루프
void gameLoop()
{
    bool gameClear = false;
    // 배경음악 재생
    play_sound3("C:\\BGM\\스테이지3.wav", TRUE);
    while (true)
    {
        // 키 입력 처리
        handleInput();

        // 점프 처리    
        handleJump();

        // 플랫폼 충돌 검사
        checkPlatformCollision(platforms, numPlatforms);

        // 포탈 충돌 검사
        checkPortalCollision();

        // 스위치 충돌 검사
        checkSwitchCollision();

        // 각 캐릭터의 탈출 상태 확인
        if ((int)fireboyX == exitX && (int)fireboyY[0] == exitY)
            fireboyExited = true;
        if ((int)watergirlX == exitX && (int)watergirlY[0] == exitY)
            watergirlExited = true;

        // 게임 클리어 확인
        if (fireboyExited && watergirlExited) {
            gameClear = true;
            break;
        }

        // 게임 오버 확인
        if (checkGameOver()) {
            handle_game_over3();
            printf("\n\n\n\n\n게임 오버! \n");
            Sleep(1000);  // 1초 대기
            while (1) {
                printf("다시 시작하시겠습니까? (y/n): ");

                char choice = '\0';

                while (choice != 'y' && choice != 'n') {
                    choice = _getch();
                    if (choice == 'y' || choice == 'Y') {
                        // 게임을 다시 시작하기 위해 변수 초기화
                        play_sound3("C:\\BGM\\스테이지3.wav", TRUE);
                        // 스위치 활성화 여부
                        bool switchActive = false;
                        bool isOnSwitch = false;
                        //캐릭터 위치 초기화
                        fireboyX = 5;
                        fireboyY[0] = 23;
                        watergirlX = 94;
                        watergirlY[0] = 23;
                        break;
                    }
                    else if (choice == 'n' || choice == 'N') {
                        printf("게임 종료\n");
                        return; // 게임 종료
                    }
                }

                // 콘솔 창 지우기
                clear_console3();
                if (checkGameOver || choice == 'y' || choice == 'Y') {
                    break;
                }
            }
        }
        // 화면 그리기
        drawGame3();
    }
    if (gameClear) {
        stop_sound3();
        // 게임 성공 효과음 재생
        handle_success3();
        printf("\n\n\n\n\n게임 성공!\n");
        Sleep(2000);  // 2초 대기
    }
}

void WaterFire_Game()
{

    COORD bufferSize = { 100, 10000 }; // 가로, 세로
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

    system("mode con cols=140 lines=30");

    hide_cursor3(true);  // 커서 숨기기
    drawStageAnimation3();
    clear_console3();

    fireboyX = 5;
    fireboyY[0] = 23;
    watergirlX = 94;
    watergirlY[0] = 23;

    exitX = 97;
    exitDisplayY = groundY[9]; // 화면에 출력하기 위한 물리적 위치
    exitY = groundY[9] - 1;   // 충돌 감지를 위한 논리적 위치

    // 포탈 정보 설정
    portal_info[portal_count].in_x = 23;
    portal_info[portal_count].in_y = 3;
    portal_info[portal_count].out_x = 92;
    portal_info[portal_count].out_y = 2;
    portal_count++;

    gameLoop();
    return 0;
}