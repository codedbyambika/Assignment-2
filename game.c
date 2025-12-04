#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void clear_screen_fast(){
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD topLeft={0, 0};
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD cells;
    GetConsoleScreenBufferInfo(h, &csbi);
    cells=csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(h, ' ', cells, topLeft, &written);
    FillConsoleOutputAttribute(h, csbi.wAttributes, cells, topLeft, &written);
    SetConsoleCursorPosition(h, topLeft);
}

int main(){
    srand(time(0));
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize=1;
    cursor.bVisible=FALSE;
    SetConsoleCursorInfo(h, &cursor);
    int x=1;                                 // player lane
    int step=0;                              // obstacle position
    int obstaclePos=rand() % 3;
    int lives=3;
    int bulletStep=-1;                       // -1 = no bullet
    int bulletLane=-1;
    printf("Controls: A = left, D = right, W = shoot\n");
    printf("Avoid the X and shoot it! Press any key to start...\n");
    _getch();
    while(lives > 0){
        if(_kbhit()){
            char ch = _getch();
            if(ch=='a' && x > 0) x--;      
            if(ch=='d' && x < 2) x++;      
            if(ch=='w' && bulletStep==-1){
                bulletLane=x;
                bulletStep=9;
            }
        }
        clear_screen_fast();
        printf("Lives: %d\n",lives);
        printf("|--- --- ---|\n");                      // DRAW ROWS
        for(int i=0;i<10;i++){
            if(i==step){                            // obstacle
                if(obstaclePos==0)
                    printf("| X         |\n");
                else if(obstaclePos == 1)
                    printf("|     X     |\n");
                else
                    printf("|         X |\n");
            }
            else if(i==bulletStep){                 // bullet
                if(bulletLane==0)
                    printf("| *         |\n");
                else if(bulletLane==1)
                    printf("|     *     |\n");
                else
                    printf("|         * |\n");
            }
            else{
                printf("|           |\n");
            }
        }
        if(x==0)                              // PLAYER
            printf("| o         |\n");
        else if(x==1)
            printf("|     o     |\n");
        else
            printf("|         o |\n");
        if(bulletStep==step && bulletLane==obstaclePos){          // Bullet hits obstacle
            bulletStep=-1;
            step=0;
            obstaclePos=rand() % 3;
        }
        if(bulletStep!=-1){                                  // Move bullet up
            bulletStep--;
            if(bulletStep<0) bulletStep=-1;
        }
        if(step==10){                                         // Collision with player
            if(x==obstaclePos){
                lives--;
                if(lives==0) break;
            }
            step=0;
            obstaclePos=rand() % 3;
        }
        else{
            step++;
        }
        Sleep(150);
    }
    printf("\nGAME OVER!\n");
    return 0;
}