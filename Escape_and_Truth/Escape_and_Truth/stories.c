#include <stdio.h>
#include <string.h>
#include< stdbool.h>
#include <windows.h>
#include <time.h>
#include <mmsystem.h>  // PlaySound �Լ��� ����ϱ� ���� �߰�
#include <tchar.h>
#pragma comment(lib, "winmm.lib")

// WAV ���� ����� �����ϴ� �Լ�
void stop_sound0()
{
    // NULL ���� �̿��Ͽ� PlaySound �Լ� ȣ���Ͽ� ����
    PlaySound(NULL, NULL, SND_ASYNC);
}

// Ű���� ȿ����
void keyboard(const char* filename, bool loop)
{
    LPCTSTR sound_file = L"C:\\BGM\\Ű����Ҹ�.wav";  // ȿ���� ���� ��θ� ���� ����

    PlaySound(sound_file, NULL, SND_ASYNC | SND_FILENAME | (loop ? SND_LOOP : 0));
}
// �ѱ��ھ� ���
void print_char_by_char(char* str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        printf("%c", str[i]);
        fflush(stdout);
        Sleep(30);  // 30 �и������� �������� ���� ���
    }
    printf("\n");
}

// ���͸� �Է¹޾ƾ� ���� �������� �Ѿ
void wait_for_enter() {
    printf(" ");
    while (getchar() != '\n');
}

// Į �׸�
void draw_case()
{

    printf("                                                     ����                                           \n");
    printf("                                                       ���                                          \n");
    printf("                                                      ����                                           \n");
    printf("                              �����                     ����                                           \n");
    printf("                            �������                  �����                                           \n");
    printf("                           ��������                   �����                                              \n");
    printf("                           ��������                �����                                          \n");
    printf("                             ��������         �����                                        \n");
    printf("                               ��������  ������\033[31m   \033[0m                                     \n");
    printf("                               ��������������\033[31m     \033[0m                                    \n");
    printf("                              ��������������\033[31m    \033[0m                                                       \n");
    printf("                            ���������������\033[31m        \033[0m                                                        \n");
    printf("         ����             ���������\033[31m��������  \033[0m                                                                \n");
    printf("          ����           ���������\033[31m���������    \033[0m                                                                  \n");
    printf("           �����        �����  �����\033[31m���������      \033[0m                                                           \n");
    printf("            �����       �����     ����\033[31m���������       \033[0m                                                         \n");
    printf("               �����   �����       ������\033[31m�������          \033[0m                                                 \n");
    printf("                  ��������          ����\033[31m���������        \033[0m                                                    \n");
    printf("                     �����               �����\033[31m��������      \033[0m                                                   \n");
    printf("                                             ���\033[31m���������\033[0m��                                          \n");
    printf("                                               �����\033[31m������\033[0m����                                           \n");
    printf("                                               ��������������                                             \n");
    printf("                                                 ����������������                                   \n");
    printf("                                              ��������      ���������                                 \n");
    printf("                                              ������              ��������                       \n");
    printf("                                              �������               �������                                 \n");
    printf("                                               ������                   �������                            \n");
    printf("                                                �������                      ������                         \n");
    printf("                                                 ��������                     �����                      \n");
    printf("                                                  ���������                 ������                      \n");
    printf("                                                       ��������                �����                   \n");
    printf("                                                           �������                ����         \n");
    printf("                                                                �������            ����                   \n");
    printf("                                                                   �������         ����                  \n");
    printf("                                                                        ������       �����                  \n");
    printf("                                                                            ����        ������               \n");
    printf("                                                                              ���                    \n");
    printf("                                                                                ��                    \n");
    printf("                                                                                ��                    \n");


}

// öâ �׸�
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

// ���Ź�ǰ
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
    printf("                               ������            �� ���� Į                  �� ���� ��\n\n");
    printf("             \033[1;32m---------------------------------------------------------------------------------------------\033[0m\n");
    
    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("\n\t\t\t\t�����մϴ�. ���Ź�ǰ�� ȹ���Ͽ����ϴ�. (����Ϸ��� Enter)");
    stop_sound0();
    wait_for_enter();
    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("\n\n���Ź�ǰ�� ȹ���� ���߱�� ���˸� �����ϱ� ���� ������ �����ϱ�� ����Ѵ�. (����Ϸ��� Enter)");
    stop_sound0();
    wait_for_enter();
    return 0;
}

void story1() {
    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\t\t    2023�� 6�� 12�� ���� 2�ÿ� ��������ÿ��� ���λ���� �߻��ߴ�. (����Ϸ��� Enter)");
    stop_sound0();
    wait_for_enter();

    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("\t�� �����ÿ��� �۾�ö ȸ��, ù° �ۿ���, ��° �۵���, ���� �Ƶ� ���߱Ⱑ ����־���. (����Ϸ��� Enter)");
    stop_sound0();
    wait_for_enter();

    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("\t\t\t�� �� ȸ����� ������ ������, ��° �۵��Ⱑ ������ ��ӹ޾Ҵ�. (����Ϸ��� Enter)");
    stop_sound0();
    wait_for_enter();
    Sleep(100);

    system("cls");
    draw_case();  // �ι�° �׸� ȣ��
    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("��° �۵��Ⱑ Į�� ��� ����� ���·� �߰ߵȴ�. (����Ϸ��� Enter)"); 
    stop_sound0();
    wait_for_enter();
    Sleep(100);

    system("cls");
    drawcc();  // ����° �׸� ȣ��
    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("������ ��� �߻� ��� ���� �ִ� ��° ���߱⸦ ���� �����ڷ� ü���Ͽ� ������ ���д�. (����Ϸ��� Enter)");
    stop_sound0();
    wait_for_enter();

    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("������ �� ���߱�� ������ Ż���Ͽ� ���˸� �����ϱ�� ����Ѵ�. (����Ϸ��� Enter)");
    stop_sound0();
    wait_for_enter();

    Sleep(500);
    system("cls");
    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t�ڹ��踦 Ǯ�� öâ ������ Ż���ϼ���. (����Ϸ��� Enter)");
    stop_sound0();
    wait_for_enter();
    return 0;
}

void story2() { //one_drawing �Ŀ� ��µǴ� ���丮
    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("\n\n�ڹ��踦 Ǯ�� öâ���� ���� ���߱�� ������ �Ѿ��� ���� ������ Ż���ϱ�� �Ѵ�. (����Ϸ��� Enter)");
    stop_sound0();
    wait_for_enter();

    Sleep(500);
    system("cls");
    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t������ �Ѿ��� ���� ������ Ż���ϼ���. (����Ϸ��� Enter)");
    stop_sound0();
    wait_for_enter();
    return 0;
}

void story3() {
    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("\n\n\n�Ѿ��� ���� ������ Ż���� ���߱�� ���˸� �����ϱ� ���� ���Ź�ǰ�� �����ϱ�� ����Ѵ�. (����Ϸ��� Enter)");
    stop_sound0();
    wait_for_enter();

    Sleep(500);
    system("cls");
    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t�񼭿� �����Ͽ� ���Ź�ǰ�� ȹ���ϼ���. (����Ϸ��� Enter)");
    stop_sound0();
    wait_for_enter();
    return 0;
}

void story4() {
    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    print_char_by_char("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t������ ������ ���˸� �����ϼ���. (����Ϸ��� Enter)");
    stop_sound0();
    wait_for_enter();
    return 0;
}

void story5() {  // �ḻ
    keyboard("C:\\BGM\\Ű����Ҹ�.wav", false);
    printf("\n\t\t\t\t\t\t\t  ����\n\n\n\n\n");
    print_char_by_char("�ι�: ù°(����), ��°(���), ��°(�÷��̾�)");
    print_char_by_char("\n\n������ �������� �¾ �� ������ �־���.");
    print_char_by_char("\nȸ����� ���ư��ð� �������� Ȯ���ϴµ�, ��°�� ȸ�縦 ��ӹް� �ȴٴ� ������ ���� �־���.");
    print_char_by_char("\n�̿� ù°�� ������ �г�� ���� ��°�� �Ǽ��� Į�� �� ���̰� �ȴ�.");
    print_char_by_char("\nù°�� ������ �� �� ���� ������ �����⿡ ��Ȳ�ϰ� �ǰ�, �ڽ��� ������ �����.");
    print_char_by_char("\nù°�� �ڽ��� ���˸� ����� ���� ��°���� ������ ����� ������ ���д�.");
    print_char_by_char("\n\n\n\n\t\t\t\t\t\t����� ������ ����˴ϴ�..");
    stop_sound0();
    Sleep(3000);
    return 0;
}