#include<iostream>
#include<ctime>
#include<conio.h>
#include<Windows.h>

using namespace std;

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define BACK 98
#define m 109
#define h 179

HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

void rand(unsigned int Game[4][4]);
void table(unsigned int Game[4][4]);
void switchGame(unsigned int Game[4][4]);
void up(unsigned int Game[4][4]);
void down(unsigned int Game[4][4]);
void left(unsigned int Game[4][4]);
void right(unsigned int Game[4][4]);
bool check(unsigned int Game[4][4]);
void save(unsigned int Game[4][4]);
void load(unsigned int Game[4][4]);
void saveback(unsigned int Back[4][4], unsigned int Game[4][4]);
void loadback(unsigned int Back[4][4], unsigned int Game[4][4]);
void savetopscore();
void printtopscore();
void savebestscore();
void loadbestscore();

int i=0, j=0, k=0;
char key=114;
bool did=0;
char win=0;
unsigned int score=0, scoreback=0, topscore=0, tmp=0;

int main() {
    system("mode con lines=18 cols=36");
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 1;
    cursor.bVisible = 0;
    SetConsoleCursorInfo(hCon,&cursor);

    srand(time(NULL));
    unsigned int Game[4][4];
    unsigned int Back[4][4];

    while(key==114) {
        score=0;
        loadbestscore();
        win=0;
        for(i=0; i<4; i++) {
            for(j=0; j<4; j++) {
                Game[i][j]=0;
            }
        }
        rand(Game);
        rand(Game);
        bool menu = 0;
        while(1) {
            system("cls");
            printf("Score: %d", score);
            if(score>topscore) {
                topscore=score;
            }
            printf("       MAX Score: %d\n", topscore);
            table(Game);
            printf("\n              \"b\" - back\n");
            key=24;
            printf("            %c\n",key);
            key=27;
            printf(" Control: %c", key--);
            key--;
            printf(" %c ",key);
            key++;
            printf("%c ", key);
            if(menu) {
                printf("    Esc - exit\n");
                printf("                    \"r\" - restart\n");
                printf("                    \"s\" - save\n");
                printf("                    \"l\" - load\n");
                printf("                    \"t\" - top score\n");
            }
            else
                printf("     \"m\" - menu\n");
            if(win==1) {
                printf("   CONGRITULATIONS!\n     YOU WON!\n    YOUR SCORE: %d\n", score);
                printf(" Keep playing? Press space");
                while(key!=27&&key!=114&&key!=32)
                    key=getch();
                win++;
                if(key==32)
                    continue;
                break;
            }
            key=getch();
            if(menu)
                if(key==27||key==114)
                    break;
            if(key==-35)
                key=getch();
            did=0;
            switch(key) {
            case UP:
                saveback(Back, Game);
                up(Game);
                break;
            case DOWN:
                saveback(Back, Game);
                down(Game);
                break;
            case LEFT:
               saveback(Back, Game);
               left(Game);
                break;
            case RIGHT:
                saveback(Back, Game);
                right(Game);
                break;
            case BACK:
                loadback(Back, Game);
                break;
            case m:
                if(menu)
                    menu=0;
                else
                    menu=1;
                continue;
            case 108:
                if(menu) {
                    load(Game);
                    menu=0;
                }
                continue;
            case 115:
                if(menu) {
                    save(Game);
                    menu=0;
                }
            default:
                continue;
            case 116:
                if(menu) {
                    printtopscore();
                    menu=0;
                }
                continue;
            }
            if(did)
                rand(Game);
            if(!did)
                if(check(Game)) {
                    savetopscore();
                    savebestscore();
                    printf("\n       GAME OVER\n   YOUR SCORE: %d\n", score);
                    printf("\nEsc - exit, \"r\" - restart\n");
                    while(key!=27&&key!=114)
                        key=getch();
                    break;

                }
        }
    }
}

void rand(unsigned int Game[4][4]) {
    did=0;
    while(1) {
        i=rand()%4, j=rand()%4;
        if(Game[i][j]==0) {
            if(rand()%10>0) {
                Game[i][j]=2;
            }
            else {
                Game[i][j]=4;
            }
            break;
        }
        did=1;
    }
}

void table(unsigned int Game[4][4]) {
    HANDLE hnd;
    hnd=GetStdHandle(STD_OUTPUT_HANDLE);

    char up[]={218, 196, 196, 196, 196, 196, 194, 196, 196, 196, 196, 196, 194,
               196, 196, 196, 196, 196, 194, 196, 196, 196, 196, 196, 191, 0};
    char dw[]={192, 196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 193,
               196, 196, 196, 196, 196, 193, 196, 196, 196, 196, 196, 217, 0};
    char mid[]={195, 196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 197,
                196, 196, 196, 196, 196, 197, 196, 196, 196, 196, 196, 180, 0};

    printf("%s",up);
    printf("\n% c",(char)h);

    for(i=0; i<1; i++) {
        for(j=0; j<4; j++) {
            switchGame(Game);
        }
        printf("\n");
    }
    for(i=1; i<4; i++) {
        printf("%s\n",mid);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);

        for(j=0; j<4; j++) {
            switchGame(Game);
        }
        printf("\n");
    }
    printf("%s",dw);
}

void switchGame(unsigned int Game[4][4]) {
    HANDLE hnd;
    hnd=GetStdHandle(STD_OUTPUT_HANDLE);

    int num;
    num=Game[i][j];
    switch(num) {
    case 0:
        printf("     ");
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 2:
        SetConsoleTextAttribute(hnd, 8);
        printf("  %d  ",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 4:
        SetConsoleTextAttribute(hnd, 7);
        printf("  %d  ",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 8:
        SetConsoleTextAttribute(hnd, 6);
        printf("  %d  ",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 16:
        SetConsoleTextAttribute(hnd, 14);
        printf("  %d ",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 32:
        SetConsoleTextAttribute(hnd, 2);
        printf("  %d ",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 64:
        SetConsoleTextAttribute(hnd, 10);
        printf("  %d ",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 128:
        SetConsoleTextAttribute(hnd, 3);
        printf(" %d ",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 256:
        SetConsoleTextAttribute(hnd, 11);
        printf(" %d ",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 512:
        SetConsoleTextAttribute(hnd, 1);
        printf(" %d ",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 1024:
        SetConsoleTextAttribute(hnd, 9);
        printf(" %d",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 2048:
        SetConsoleTextAttribute(hnd, 4);
        printf(" %d",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 4096:
        SetConsoleTextAttribute(hnd, 12);
        printf(" %d",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 8192:
        SetConsoleTextAttribute(hnd, 5);
        printf(" %d",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 16384:
        SetConsoleTextAttribute(hnd, 13);
        printf("%d",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 32768:
        SetConsoleTextAttribute(hnd, 7);
        printf("%d",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
        break;
    case 65536:
        SetConsoleTextAttribute(hnd, 15);
        printf("%d",Game[i][j]);
        SetConsoleTextAttribute(hnd, 15);
        printf("%c",(char) h);
    }
}

void up(unsigned int Game[4][4]) {
    for(j=0; j<4; j++) {
        for(i=0; i<4; i++) {
            for(k=i+1; k<4; k++) {
                if(Game[k][j]!=0) {
                    if(Game[i][j]==0) {
                        Game[i][j]=Game[k][j];
                        Game[k][j]=0;
                        did=1;
                    }
                    else {
                        if(Game[i][j]==Game[k][j]) {
                            Game[i][j]+=Game[k][j];
                            Game[k][j]=0;
                            int num=Game[i][j];
                            score+=num;
                            if(num==2048) {
                                win++;
                            }
                            did=1;
                        }
                        else
                            break;
                    }
                }
            }
        }
    }
}

void down(unsigned int Game[4][4]) {
    for(j=3; j>=0; j--) {
        for(i=3; i>=0; i--) {
            for(k=i-1; k>=0; k--) {
                if(Game[k][j]!=0) {
                    if(Game[i][j]==0) {
                        Game[i][j]=Game[k][j];
                        Game[k][j]=0;
                        did=1;
                    }
                    else {
                        if(Game[i][j]==Game[k][j]) {
                            Game[i][j]+=Game[k][j];
                            Game[k][j]=0;
                            int num=Game[i][j];
                            score+=num;
                            if(num==2048) {
                                win++;
                            }
                            did=1;
                        }
                        else
                            break;
                    }
                }
            }
        }
    }
}

void right(unsigned int Game[4][4]) {
    for(i=0; i<4; i++) {
        for(j=3; j>=0; j--) {
            for(k=j-1; k>=0; k--) {
                if(Game[i][k]!=0) {
                    if(Game[i][j]==0) {
                        Game[i][j]=Game[i][k];
                        Game[i][k]=0;
                        did=1;
                    }
                    else {
                        if(Game[i][j]==Game[i][k]) {
                            Game[i][j]+=Game[i][k];
                            Game[i][k]=0;
                            int num=Game[i][j];
                            score+=num;
                            if(num==2048) {
                                win++;
                            }
                            did=1;
                        }
                        else
                            break;
                    }
                }
            }
        }
    }
}

void left(unsigned int Game[4][4]) {
    for(i=0; i<4; i++) {
        for(j=0; j<4; j++) {
            for(k=j+1; k<4; k++) {
                if(Game[i][k]!=0) {
                    if(Game[i][j]==0) {
                        Game[i][j]=Game[i][k];
                        Game[i][k]=0;
                        did=1;
                    }
                    else {
                        if(Game[i][j]==Game[i][k]) {
                            Game[i][j]+=Game[i][k];
                            Game[i][k]=0;
                            int num=Game[i][j];
                            score+=num;
                            if(num==2048) {
                                win++;
                            }
                            did=1;
                        }
                        else
                            break;
                    }
                }
            }
        }
    }
}

bool check(unsigned int Game[4][4]) {
    unsigned int Check[4][4];
    int i,j;
    for(i=0; i<4; i++) {
        for(j=0; j<4; j++) {
            Check[i][j]=Game[i][j];
        }
    }
    unsigned int score0=score;
    up(Check);
    right(Check);
    down(Check);
    left(Check);

    score=score0;
    for(i=0; i<4; i++) {
        for(j=0; j<4; j++) {
            if(Check[i][j]!=Game[i][j])
                return 0;
        }
    }
    return 1;
}

void save(unsigned int Game[4][4]) {
    FILE *save;
    save=fopen("save.dat", "w");
    for(i=0; i<4; i++) {
        for(j=0; j<4; j++) {
            fprintf(save,"%5d\n", Game[i][j]);
        }
    }
    fprintf(save,"\n%d", score);
    fclose(save);
}

void load(unsigned int Game[4][4]) {
    FILE *load;
    load=fopen("save.dat", "r");
    if(load==NULL) {
        printf("Error");
    }
    else {
        for(i=0; i<4; i++) {
            for(j=0; j<4; j++) {
                fscanf(load,"%d", &Game[i][j]);
            }
        }
        fscanf(load,"%d",&score);
        fclose(load);
    }
    if(score>20000)
            win=2;
}

void saveback(unsigned int Back[4][4], unsigned int Game[4][4]) {
    scoreback=score;
    for(i=0; i<4; i++) {
        for(j=0; j<4; j++) {
            Back[i][j]=Game[i][j];
        }
    }
}

void loadback(unsigned int Back[4][4], unsigned int Game[4][4]) {
    score=scoreback;
    for(i=0; i<4; i++) {
        for(j=0; j<4; j++) {
            Game[i][j]=Back[i][j];
        }
    }
}

void savetopscore() {
    int top[10];
    FILE* s;

    s=fopen("score.dat", "r");
    for(i=0; i<10; i++) {
        fscanf(s,"%d", &top[i]);
    }
    if(score<top[9]) {
        fclose(s);
        return;
    }
    else {
        top[9]=score;
        fclose(s);
    }

    for(i=10-1; i>=0; --i) {
        for(j=0; j<i; ++j) {
            if(top[j]<top[j+1]) {
                tmp=top[j];
                top[j]=top[j+1];
                top[j+1]=tmp;
            }
        }
    }

    s=fopen("score.dat", "w");
    for(i=0; i<10; i++) {
        fprintf(s,"%d\n", top[i]);
    }
    fclose(s);
}

void printtopscore() {
    int i;
    FILE* s;
    s=fopen("score.dat", "r");
    printf("Top score:\n");
    for(i=0; i<10; i++) {
        fscanf(s,"%d", &tmp);
        if(i<9) {
            printf("  %d.", i+1);
            printf(" %2d\n", tmp);
        }
        else {
            printf(" %d.", i+1);
            printf(" %d\n", tmp);
        }
    }
    getch();
}

void savebestscore() {
    FILE* s;
    s=fopen("best.dat", "w");
    fprintf(s,"%d\n", topscore);
    fclose(s);
}

void loadbestscore() {
    FILE* s;
    s=fopen("best.dat", "r");
    fscanf(s,"%d\n", &tmp);
    topscore=tmp;
    fclose(s);
}
