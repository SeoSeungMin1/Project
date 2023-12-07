#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45
#define CLOUD_BOTTOM_Y 15
#define CLOUD_BOTTOM_X 45
#define FALSE 0
#define TRUE 1

enum {
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_SKYBLUE,
    DARK_RED,
    DARK_VIOLET,
    DARK_YELLOW,
    GRAY,
    DARK_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE,
};

void SetConsoleView();
void CursorView(char show);
void SetColor(unsigned short text);
void GotoXY(int x, int y);
int GetKeyDown();
int IsCollision(const int treeX, const int dinoY);
void DrawDino(int dinoY);
void DrawTree(int treeX);
void DrawGameOver(const int score);
void DrawBird(int birdX);
void DrawCloud(int cloudX);


void SetConsoleView() {
    system("mode con : cols=120 lines=120");
    system("title 구글 공룡 게임 [By. SSM]");
    CursorView(FALSE);
}

void CursorView(char show) {
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

void SetColor(unsigned short text) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

void GotoXY(int x, int y) {
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int GetKeyDown() {
    if (_kbhit() != 0) return _getch();
    return FALSE;
}
int IsCollision(const int treeX, const int dinoY) {
    GotoXY(0, 0);
    printf("treeX : %d, dinoY : %d", treeX, dinoY);
    if (treeX <= 8 && treeX >= 4 && dinoY > 8) return TRUE;

    return FALSE;
}

void DrawCloud(int cloudX) {
    SetColor(DARK_GRAY);
    GotoXY(cloudX, CLOUD_BOTTOM_Y);
    printf("  _  ");
    GotoXY(cloudX, CLOUD_BOTTOM_Y + 1);
    printf(" ( ` ");
    GotoXY(cloudX, CLOUD_BOTTOM_Y + 2);
    printf("  ` )");
    GotoXY(cloudX, CLOUD_BOTTOM_Y + 3);
    printf("  -  ");
}

void DrawDino(int dinoY) {
    SetColor(VIOLET);
    GotoXY(0, dinoY);
    static int legFlag = TRUE;
    printf("        $$$$$$$ \n");
    printf("       $$ $$$$$$\n");
    printf("       $$$$$$$$$\n");
    printf("$      $$$      \n");
    printf("$$     $$$$$$$  \n");
    printf("$$$   $$$$$     \n");
    printf(" $$  $$$$$$$$$$ \n");
    printf("$$\n");
    SetColor(WHITE);
    printf("$$$");
    SetColor(VIOLET);
    printf("$$$     \n");
    printf("  $$$");
    SetColor(GREEN);
    printf("$$$");
    SetColorVIOLET);
    printf("$    \n");
    printf("    $$$$$$$$    \n");
    printf("     $$         ");
    if (legFlag) {
        printf("     $    $$$   \n");
        printf("     $$         ");
        legFlag = FALSE;
    }
    else {
        printf("     $$$  $     \n");
        printf("          $$    ");
        legFlag = TRUE;
    }
}

void DrawTree(int treeX) {
    SetColor(GREEN);
    GotoXY(treeX, TREE_BOTTOM_Y);
    printf("$$$$");
    GotoXY(treeX, TREE_BOTTOM_Y + 1);
    printf("$$$$");
    GotoXY(treeX, TREE_BOTTOM_Y + 2);
    printf("$$$$");
    SetColor(DARK_YELLOW);
    GotoXY(treeX, TREE_BOTTOM_Y + 3);
    printf("$$$$");
    GotoXY(treeX, TREE_BOTTOM_Y + 4);
    printf("$$$$");
}

void DrawBird(int birdX) {
    SetColor(DARK_YELLOW);
    GotoXY(birdX, TREE_BOTTOM_Y);
    printf("  \\ \\\\");
    GotoXY(birdX, TREE_BOTTOM_Y + 1);
    printf(" (o><)");
    GotoXY(birdX, TREE_BOTTOM_Y + 2);
    printf("   )/");
    GotoXY(birdX, TREE_BOTTOM_Y + 3);
    printf(" ('')");
}

void DrawGameOver(const int score) {
    system("cls");
    SetColor(YELLOW);
    int x = 16, y = 8;
    GotoXY(x, y);

    printf("===================================");
    GotoXY(x, y + 1);
    printf("==========G A M E O V E R==========");
    GotoXY(x, y + 2);
    printf("===================================");
    GotoXY(x, y + 5);
    printf("SCORE : %d", score);
    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
}

int main() {
    SetConsoleView();

    srand((unsigned int)time(NULL));

    const int jumpHeight = 5;
    int jumpVelocity = jumpHeight;
    int jumpTime = 0;

    while (TRUE) {
        int isJumping = FALSE;
        int isBottom = TRUE;
        const int gravity = 1;

        int dinoY = DINO_BOTTOM_Y;
        int treeX = TREE_BOTTOM_X;
        int cloudX = CLOUD_BOTTOM_X;

        int score = 0;
        clock_t start, curr;
        start = clock();

        while (TRUE) {
            if (IsCollision(treeX, dinoY) || IsCollision(cloudX, dinoY)) break;

            if (GetKeyDown() == ' ' && isBottom) {
                isJumping = TRUE;
                isBottom = FALSE;
                jumpTime = 0;
                jumpVelocity = jumpHeight;
            }

            if (isJumping && jumpTime < jumpHeight) {
                dinoY -= jumpVelocity;
                jumpTime++;
                jumpVelocity -= gravity;
            }
            else {
                isJumping = FALSE;
                if (dinoY < DINO_BOTTOM_Y) {
                    dinoY += gravity;
                }
                else {
                    dinoY = DINO_BOTTOM_Y;
                    isBottom = TRUE;
                    jumpVelocity = jumpHeight;
                }
            }

            treeX -= 2;
            if (treeX <= 0) treeX = TREE_BOTTOM_X;

            cloudX -= 1;
            if (cloudX <= 0) cloudX = CLOUD_BOTTOM_X;

            if (dinoY <= 3) isJumping = FALSE;

            int obstacleType = rand() % 3;
            if (obstacleType == 0) {
                DrawTree(treeX);
                DrawDino(dinoY);
            }
            else if (obstacleType == 1) {
                DrawBird(treeX);
            }
            else {
                DrawCloud(cloudX);
                DrawDino(dinoY);
            }

            curr = clock();
            if (((curr - start) / CLOCKS_PER_SEC) >= 1) {
                score++;
                start = clock();
            }

            Sleep(30);
            system("cls");

            SetColor(WHITE);
            GotoXY(22, 0);
            printf("Score : %d ", score);

            GotoXY(2, 2);
            printf("Jump: Space Key");
        }

        DrawGameOver(score);
    }

    return FALSE;
}
