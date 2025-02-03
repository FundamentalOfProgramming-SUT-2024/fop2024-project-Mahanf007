#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_mixer.h>
#include <locale.h>
int locker=0;
int error;
int floorr=1;
int counterY=0;
int counterl=0;
int counterB=0;
int counterG=0;
int counterdagger=0;
int counterwand=0;
int counterarrow=0;
int counterf=0;
int counterF=0;
int health=100;
int j=0;
int modes=0;
int modeu=1;
int def=1;
int counterD=5;
int counterQ=10;
int counterI=15;
int counterS=20;
int counterU=25;
int countert=0;
const char* songs[3] = {
    "1.mp3",
    "2.mp3",
    "3.mp3"
};
typedef struct{
    char username[70];
    char password[70];
    char email[100];
} user;
typedef struct{
    char username[70];
    int rank;
    int totalscore;
    int savedgold;
    int totalgame; 
}point;
int diff=1;
int color;
char player[70];
void endgame();
void playMusic(const char* filePath){
    if (SDL_Init(SDL_INIT_AUDIO)<0) {
        printw("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        refresh();
        getch();
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printw("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        refresh();
        getch();
        return;
    }

    Mix_Music *music = Mix_LoadMUS(filePath);
    if (music == NULL) {
        printw("Failed to load music file! SDL_mixer Error: %s\n", Mix_GetError());
        refresh();
        getch();
        return;
    } 
    Mix_PlayMusic(music, -1);
}
void list(){
    mvprintw(0,85,"Y: %d,low,5",counterY);
    mvprintw(1,85,"/: %d,high,12",counterdagger);
    mvprintw(2,85,"!: %d,high,15",counterwand);
    mvprintw(0,95,">: %d,high,5",counterarrow);
    mvprintw(1,95,"l: %d,low,10",counterl);
    char s=getch();
    if(s=='s'){
        char o=getch();
        if(o=='Y'){
            def=1;
            if(counterY) mvprintw(2,85,"Y set to default");
            else{
                mvprintw(2,85,"not enough");
            }
        }
        if(o=='/'){
            def=2;
            if(counterdagger) mvprintw(2,85,"/ set to default");
            else{
                mvprintw(2,85,"not enough");
            }
        }
        if(o=='!'){
            def=3;
            if(counterwand) mvprintw(2,85,"! set to default");
            else{
                mvprintw(2,85,"not enough");
            }
        }
        if(o=='>'){
            def=4;
            if(counterarrow) mvprintw(2,85,"> set to default");
            else{
                mvprintw(2,85,"not enough");
            }
        }
        if(o=='l'){
            def=5;
            if(counterl) mvprintw(2,85,"l set to default");
            else{
                mvprintw(2,85,"not enough");
            }
        }
        getch();
    }
    mvprintw(0,85,"                        ");
    mvprintw(1,85,"                        ");
    mvprintw(2,85,"                        ");
}
void customprint(int x,int y,char c){
    if(color==1){
        start_color();
        init_pair(3, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(3));
        mvprintw(x,y,"%c",c);
        attroff(COLOR_PAIR(3));
    }
    else if(color==2){
        start_color();
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        attron(COLOR_PAIR(2));
        mvprintw(x,y,"%c",c);
        attroff(COLOR_PAIR(2));
    }
    else if(color==3){
        start_color();
        init_pair(5, COLOR_GREEN, COLOR_BLACK);
        attron(COLOR_PAIR(5));
        mvprintw(x,y,"%c",c);
        attroff(COLOR_PAIR(5));
    }
    else{
        mvprintw(x,y,"%c",c);
    }
}
void movevcor(int pos,int x,int h,int k,int l){
    int u=h+5;
    int v=k;
    while(h!=x+l||k!=pos){
        int check=0;
        int p;
        char c=mvinch(k+1,h+1);
        char x=mvinch(k+1,h);
        char z=mvinch(k+1,h-1);
        char a=mvinch(k,h-1);
        char d=mvinch(k,h+1);
        char e=mvinch(k-1,h+1);
        char w=mvinch(k-1,h);
        char q=mvinch(k-1,h-1);
        char m=getch();
        switch(m){
        case 'c':
            if(c=='#'){
                mvaddch(k,h,'#');
                customprint(k+1,h+1,'H');
                h++;
                k++;
                check=1;
            }
            break;
        case 'x':
            if(x=='#'){
               mvaddch(k,h,'#');
               customprint(k+1,h,'H');
               k++;
               check=1;
            }
            break;
        case 'z':
            if(z=='#'){
               mvaddch(k,h,'#');
               customprint(k+1,h-1,'H');
               k++;
               h--;
               check=1;
            }
            break;
        case 'a':
            if(a=='#'){
               mvaddch(k,h,'#');
               customprint(k,h-1,'H');
               h--;
               check=1;
            }
            break;
        case 'd':
            if(d=='#'){
               mvaddch(k,h,'#');
               customprint(k,h+1,'H');
               h++;
               check=1;
            }
            break;
        case 'e':
            if(e=='#'){
               mvaddch(k,h,'#');
               customprint(k-1,h+1,'H');
               k--;
               h++;
               check=1;
            }
            break;
        case 'w':
            if(w=='#'){
               mvaddch(k,h,'#');
               customprint(k-1,h,'H');
               k--;
               check=1;
            }
            break;
        case 'q':
            if(q=='#'){
               mvaddch(k,h,'#');
               customprint(k-1,h-1,'H');
               k--;
               h--;
               check=1;
            }
            break;
        default:
            break;
        }
        if(check){
            char temp1=mvinch(v,u+1);
            char temp2=mvinch(v+1,u);
            char temp3=mvinch(v-1,u);
            char temp4=mvinch(v,u-1);          
            if(temp1=='.'){
                mvprintw(v,u+1,"#");
                u++;
            }
            else if(temp2=='.'){
                ++v;
                mvprintw(v,u,"#");
            }
            else if(temp3=='.'){
                --v;
                mvprintw(v,u,"#");
            }
            else if(temp4=='.'){
                --u;
                mvprintw(v,u,"#");
            }
        }
    }
}
void movecor(int pos,int x,int h,int k){
    int u=h+5;
    int v=k;
    while(h+1!=x||k!=pos){
        int check=0;
        int p;
        char c=mvinch(k+1,h+1);
        char x=mvinch(k+1,h);
        char z=mvinch(k+1,h-1);
        char a=mvinch(k,h-1);
        char d=mvinch(k,h+1);
        char e=mvinch(k-1,h+1);
        char w=mvinch(k-1,h);
        char q=mvinch(k-1,h-1);
        char m=getch();
        switch(m){
        case 'c':
            if(c=='#'){
                mvaddch(k,h,'#');
                customprint(k+1,h+1,'H');
                h++;
                k++;
                check=1;
            }
            break;
        case 'x':
            if(x=='#'){
               mvaddch(k,h,'#');
               customprint(k+1,h,'H');
               k++;
               check=1;
            }
            break;
        case 'z':
            if(z=='#'){
               mvaddch(k,h,'#');
               customprint(k+1,h-1,'H');
               k++;
               h--;
            }
            break;
        case 'a':
            if(a=='#'){
               mvaddch(k,h,'#');
               customprint(k,h-1,'H');
               h--;
            }
            break;
        case 'd':
            if(d=='#'){
               mvaddch(k,h,'#');
               customprint(k,h+1,'H');
               h++;
               check=1;
            }
            break;
        case 'e':
            if(e=='#'){
               mvaddch(k,h,'#');
               customprint(k-1,h+1,'H');
               k--;
               h++;
               check=1;
            }
            break;
        case 'w':
            if(w=='#'){
               mvaddch(k,h,'#');
               customprint(k-1,h,'H');
               k--;
               check=1;
            }
            break;
        case 'q':
            if(q=='#'){
               mvaddch(k,h,'#');
               customprint(k-1,h-1,'H');
               k--;
               h--;
            }
            break;
        default:
            break;
        }
        if(check){
            char temp1=mvinch(v,u+1);
            char temp2=mvinch(v+1,u);
            char temp3=mvinch(v-1,u);
            char temp4=mvinch(v,u-1);          
            if(temp1=='.'){
                mvprintw(v,u+1,"#");
                u++;
            }
            else if(temp2=='.'){
                ++v;
                mvprintw(v,u,"#");
            }
            else if(temp3=='.'){
                --v;
                mvprintw(v,u,"#");
            }
            else if(temp4=='.'){
                --u;
                mvprintw(v,u,"#");
            }
        }
    }
}
void movercor(int pos,int x,int h,int k,int l){
    int u=h-4;
    int v=k;
    while(1){
        if(h==x+l+1) break;
        int check=0;
        int p;
        char c=mvinch(k+1,h+1);
        char x=mvinch(k+1,h);
        char z=mvinch(k+1,h-1);
        char a=mvinch(k,h-1);
        char d=mvinch(k,h+1);
        char e=mvinch(k-1,h+1);
        char w=mvinch(k-1,h);
        char q=mvinch(k-1,h-1);
        char m=getch();
        switch(m){
        case 'c':
            if(c=='#'){
                mvaddch(k,h,'#');
                customprint(k+1,h+1,'H');
                h++;
                k++;
            }
            break;
        case 'x':
            if(x=='#'){
               mvaddch(k,h,'#');
               customprint(k+1,h,'H');
               k++;
               check=1;
            }
            break;
        case 'z':
            if(z=='#'){
               mvaddch(k,h,'#');
               customprint(k+1,h-1,'H');
               k++;
               h--;
               check=1;
            }
            break;
        case 'a':
            if(a=='#'){
               mvaddch(k,h,'#');
               customprint(k,h-1,'H');
               h--;
               check=1;
            }
            break;
        case 'd':
            if(d=='#'){
               mvaddch(k,h,'#');
               customprint(k,h+1,'H');
               h++;
            }
            break;
        case 'e':
            if(e=='#'){
               mvaddch(k,h,'#');
               customprint(k-1,h+1,'H');
               k--;
               h++;
            }
            break;
        case 'w':
            if(w=='#'){
               mvaddch(k,h,'#');
               customprint(k-1,h,'H');
               k--;
               check=1;
            }
            break;
        case 'q':
            if(q=='#'){
               mvaddch(k,h,'#');
               customprint(k-1,h-1,'H');
               k--;
               h--;
               check=1;
            }
            break;
        default:
            break;
        }
        if(check){
            char temp1=mvinch(v,u+1);
            char temp2=mvinch(v+1,u);
            char temp3=mvinch(v-1,u);
            char temp4=mvinch(v,u-1);          
            if(temp1=='.'){
                mvprintw(v,u+1,"#");
                u++;
            }
            else if(temp2=='.'){
                ++v;
                mvprintw(v,u,"#");
            }
            else if(temp3=='.'){
                --v;
                mvprintw(v,u,"#");
            }
            else if(temp4=='.'){
                --u;
                mvprintw(v,u,"#");
            }
        }
    }
}
void blackprint(int x,int y,char *c){
    start_color();
    init_pair(7, COLOR_BLACK, COLOR_BLACK);
    attron(COLOR_PAIR(7));
    mvprintw(x,y,"%s",c);
    attroff(COLOR_PAIR(7));
}
void drawh2cor(int x,int y,int pos,int k,int h,int l){
    int kc=k;
    int hc=h;
    int deltay=abs(pos-k);
    int deltax=abs(h-x-l);
    mvprintw(k,h-4,"#####");
    blackprint(k,h-9,".....");
    if(pos<k){
        while(deltay--){
            blackprint(kc,h-9,".");
        }
    }
    else{
        while(deltay--){
            blackprint(++kc,h-9,".");
        }
    }
    deltax=deltax-10;
    hc=hc-9;
    while(deltax--){
        blackprint(kc,--hc,".");
    }
    movercor(pos,x,h,k,l);
}
void drawh1cor(int x,int y,int pos,int k,int h){
    int kc=k;
    int hc=h;
    int deltay=abs(pos-k);
    int deltax=abs(h-x);
    mvprintw(k,h+1,"#####");
    blackprint(k,h+6,".....");
    if(pos<k){
        while(deltay--){
            blackprint(--kc,h+10,".");
        }
    }
    else{
        while(deltay--){
            blackprint(++kc,h+10,".");
        }
    }
    deltax=deltax-11;
    hc=hc+10;
    while(deltax--){
        blackprint(kc,++hc,".");
    }
    movecor(pos,x,h,k);
}
void drawvcor(int x,int y,int pos,int k,int h,int l){
    int kc=k;
    int hc=h;
    int deltay=pos-k;
    mvprintw(k,h+1,"#####");
    while(deltay--){
        blackprint(++kc,h+5,".");
    }
    hc=hc+5;
    int deltax=abs(hc-x-l);
    while(deltax--){
        blackprint(kc,--hc,".");
    }
    movevcor(pos,x,h,k,l);
}
void printrooms(int x,int y,int l,int w,int pos){
    for(int i=0;i<l;i++){
        mvprintw(y,x+i,"-");
    }
    for(int i=0;i<l;i++){
        mvprintw(y+w-1,x+i,"-");
    }
    for(int i=0;i<w;i++){
        mvprintw(y+i,x,"|");
    }
    for(int i=0;i<w;i++){
        mvprintw(y+i,x+l,"|");
    }
    if(rand()%4){
        mvprintw(pos,x+l,"+");
    }
    else{
        locker=1;
        start_color();
        init_pair(3, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(3));
        mvprintw(pos,x+l,"@");
        attroff(COLOR_PAIR(5));
    }
    for(int i=1;i<l;i++){
        for(int j=1;j<w-1;j++){
            if(rand()%4) mvprintw(y+j,x+i,".");
            else{
                int g=rand()%(8*(diff));
                if(g==1) mvprintw(y+j,x+i,"f");
                else if(g==2) mvprintw(y+j,x+i,"Y");
                else if(g==3) mvprintw(y+j,x+i,"/");
                else if(g==4) mvprintw(y+j,x+i,"!");
                else if(g==5) mvprintw(y+j,x+i,">");
                else if(g==6) mvprintw(y+j,x+i,"l");
                else if(g==7) mvprintw(y+j,x+i,"F");
                else{
                    mvprintw(y+j,x+i,"O");
                }
                if(rand()%(3*diff)==1) mvprintw(y+j,x+i,"G");
                if(rand()%(6*diff)==2) mvprintw(y+j,x+i,"B");
                if(rand()%(9/diff)==0) mvprintw(y+j,x+i,"*");
                g=rand()%20;
                if(g==0) mvprintw(y+j,x+i,"D");
                if(g==1) mvprintw(y+j,x+i,"Q");
                if(g==2) mvprintw(y+j,x+i,"I");
                if(g==3) mvprintw(y+j,x+i,"S");
                if(g==4) mvprintw(y+j,x+i,"U");
                if(g==5) mvprintw(y+j,x+i,"t");
            }
        }
    }
    if(locker){
        int tmp1=rand()%(l-3)+x+1;
        int tmp2=rand()%(w-3)+y+1;
        start_color();
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        attron(COLOR_PAIR(4));
        mvprintw(tmp2,tmp1,"&");
        attroff(COLOR_PAIR(4));
    }
}
void printrrooms(int x,int y,int l,int w,int pos){
    for(int i=0;i<l;i++){
        mvprintw(y,x+i,"-");
    }
    for(int i=0;i<l;i++){
        mvprintw(y+w-1,x+i,"-");
    }
    for(int i=0;i<w;i++){
        mvprintw(y+i,x,"|");
    }
    for(int i=0;i<w;i++){
        mvprintw(y+i,x+l,"|");
    }
    if(rand()%4){
        mvprintw(pos,x,"+");
    }
    else{
        locker=1;
        start_color();
        init_pair(3, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(3));
        mvprintw(pos,x,"@");
        attroff(COLOR_PAIR(5));
    }
    for(int i=1;i<l;i++){
        for(int j=1;j<w-1;j++){
            if(rand()%4) mvprintw(y+j,x+i,".");
            else{
                int g=rand()%(8*diff);
                if(g==1) mvprintw(y+j,x+i,"f");
                else if(g==2) mvprintw(y+j,x+i,"Y");
                else if(g==3) mvprintw(y+j,x+i,"/");
                else if(g==4) mvprintw(y+j,x+i,"!");
                else if(g==5) mvprintw(y+j,x+i,">");
                else if(g==6) mvprintw(y+j,x+i,"l");
                else if(g==7) mvprintw(y+j,x+i,"F");
                else{
                    mvprintw(y+j,x+i,"O");
                }
                if(rand()%(3*diff)==1) mvprintw(y+j,x+i,"G");
                if(rand()%(6*diff)==2) mvprintw(y+j,x+i,"B");
                if(rand()%(9/diff)==0)  mvprintw(y+j,x+i,"*");
                g=rand()%20;
                if(g==0) mvprintw(y+j,x+i,"D");
                if(g==1) mvprintw(y+j,x+i,"Q");
                if(g==2) mvprintw(y+j,x+i,"I");
                if(g==3) mvprintw(y+j,x+i,"S");
                if(g==4) mvprintw(y+j,x+i,"U");
            }
        }
    }
    if(locker){
        int tmp1=rand()%(l-3)+x+1;
        int tmp2=rand()%(w-3)+y+1;
        start_color();
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        attron(COLOR_PAIR(4));
        mvprintw(tmp2,tmp1,"&");
        attroff(COLOR_PAIR(4));
    }
}
void lock(int p){
    mvprintw(0,0,"                                               ");
    mvprintw(0,0,"enter you password");
    int pp;
    scanw("%d",&pp);
    if(rand()%20){
        if(pp==p){
            locker=0;
            return;
        }
        else{
            mvprintw(0,0,"                                          ");
            if(!error){
                start_color();
                init_pair(6, COLOR_YELLOW, COLOR_BLACK);
                attron(COLOR_PAIR(6));
                mvprintw(0,0,"yellow alert");
                attroff(COLOR_PAIR(6));
                error++;
                return;
            }
            else if(error==1){
                start_color();
                init_pair(3, COLOR_RED, COLOR_BLACK);
                attron(COLOR_PAIR(3));
                mvprintw(0,0,"red alert");
                attroff(COLOR_PAIR(3));
                error++;
                return;
            }
            return;
        }
    }
    else{
        if(pp==(p%10)*1000+((p/10)%10)*100+((p/100)%10)*10+(p/1000)%10){
        locker=0;
        return;
        }
        else{
            mvprintw(0,0,"                                          ");
            if(error==0){
                start_color();
                init_pair(6, COLOR_YELLOW, COLOR_BLACK);
                attron(COLOR_PAIR(6));
                mvprintw(0,0,"yellow alert");
                attroff(COLOR_PAIR(6));
                error++;
                return;
            }
            else if(error==1){
                start_color();
                init_pair(3, COLOR_RED, COLOR_BLACK);
                attron(COLOR_PAIR(3));
                mvprintw(0,0,"red alert");
                attroff(COLOR_PAIR(3));
                error++;
                return;
            }
            return;
        }
    }   
}
void moveroom(int pos,int x,int l,int h,int k){
    while(1){
        if(h==x+l&&k==pos&&!locker) break;
        int p;
        char c=mvinch(k+1,h+1);
        char x=mvinch(k+1,h);
        char z=mvinch(k+1,h-1);
        char a=mvinch(k,h-1);
        char d=mvinch(k,h+1);
        char e=mvinch(k-1,h+1);
        char w=mvinch(k-1,h);
        char q=mvinch(k-1,h-1);
        if(c=='D'||x=='D'||z=='D'||a=='D'||d=='D'||e=='D'||w=='D'||q=='D'){
            health--;
            mvprintw(0,70,"health: %d",health);
            mvprintw(0,0,"you got damage              ");
            if(health<=0){
                j=1;
                endgame();
                return;
            }
        }
        if(c=='Q'||x=='Q'||z=='Q'||a=='Q'||d=='Q'||e=='Q'||w=='Q'||q=='Q'){
            health--;
            mvprintw(0,70,"health: %d",health);
            mvprintw(0,0,"you got damage              ");
            if(health<=0){
                j=1;
                endgame();
                return;
            }
        }
        if(c=='I'||x=='I'||z=='I'||a=='I'||d=='I'||e=='I'||w=='I'||q=='I'){
            health--;
            mvprintw(0,70,"health: %d",health);
            mvprintw(0,0,"you got damage               ");
            if(health<=0){
                j=1;
                endgame();
                return;
            }
        }
        if(c=='S'||x=='S'||z=='S'||a=='S'||d=='S'||e=='S'||w=='S'||q=='S'){
            health--;
            mvprintw(0,70,"health: %d",health);
            mvprintw(0,0,"you got damage                ");
            modes=1;
            if(health<=0){
                j=1;
                endgame();
                return;
            }
        }
        if(c=='U'||x=='U'||z=='U'||a=='U'||d=='U'||e=='U'||w=='U'||q=='U'){
            health--;
            mvprintw(0,70,"health: %d",health);
            mvprintw(0,0,"you got damage                 ");
            if(health<=0){
                j=1;
                endgame();
                return;
            }
        }
        char m=getch();
        switch(m){
        case 'c':
            if(c!='O'&&c!='|'&&c!='-'&&c!='D'&&c!='Q'&&c!='I'&&c!='S'&&c!='U'){
                if(c=='&'){
                    p=rand()%8999+1000;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(c=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(c=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(c=='l') counterl++;
                if(c=='B') counterB++;
                if(c=='G') counterG++;
                if(c=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(c=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(c=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
                mvaddch(k,h,'.');
                customprint(k+1,h+1,'H');
                //if(modes) mvprintw(k+1,h,"S");
                h++;
                k++;
            }
            break;
        case 'x':
            if(x!='O'&&x!='|'&&x!='-'&&x!='D'&&x!='Q'&&x!='I'&&x!='S'&&x!='U'){
                if(x=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(x=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(x=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(x=='l') counterl++;
                if(x=='B') counterB++;
                if(x=='G') counterG++;
                if(x=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(x=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(x=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h-1,"S");
               customprint(k+1,h,'H');
               k++;
            }
            break;
        case 'z':
            if(z!='O'&&z!='|'&&z!='-'&&z!='D'&&z!='Q'&&z!='I'&&z!='S'&&z!='U'){
                if(z=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(z=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(z=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(z=='l') counterl++;
                if(z=='B') counterB++;
                if(z=='G') counterG++;
                if(z=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(z=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(z=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h-2,"S");
               customprint(k+1,h-1,'H');
               k++;
               h--;
            }
            break;
        case 'a':
            if(a!='O'&&a!='|'&&a!='-'&&a!='D'&&a!='Q'&&a!='I'&&a!='S'&&a!='U'){
                if(a=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(a=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(a=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(a=='l') counterl++;
                if(a=='B') counterB++;
                if(a=='G') counterG++;
                if(a=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(a=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(a=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h-2,"S");
               customprint(k,h-1,'H');
               h--;
            }
            break;
        case 'd':
            if(d!='O'&&d!='|'&&d!='-'&&d!='D'&&d!='Q'&&d!='I'&&d!='S'&&d!='U'){
                if(d=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(d=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(d=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(d=='l') counterl++;
                if(d=='B') counterB++;
                if(d=='G') counterG++;
                if(d=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(d=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(d=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h,"S");
               customprint(k,h+1,'H');
               h++;
            }
            break;
        case 'e':
            if(e!='O'&&e!='|'&&e!='-'&&e!='D'&&e!='Q'&&e!='I'&&e!='S'&&e!='U'){
                if(e=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(e=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(e=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(e=='l') counterl++;
                if(e=='B') counterB++;
                if(e=='G') counterG++;
                if(e=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(e=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(e=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h,"S");
               customprint(k-1,h+1,'H');
               k--;
               h++;
            }
            break;
        case 'w':
            if(w!='O'&&w!='|'&&w!='-'&&w!='D'&&w!='Q'&&w!='I'&&w!='S'&&w!='U'){
                if(w=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(w=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(w=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(w=='l') counterl++;
                if(w=='B') counterB++;
                if(w=='G') counterG++;
                if(w=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(w=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(w=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h-1,"S");
               customprint(k-1,h,'H');
               k--;
            }
            break;
        case 'q':
            if(q!='O'&&q!='|'&&q!='-'&&q!='D'&&q!='Q'&&q!='I'&&q!='S'&&q!='U'){
                if(q=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(q=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(q=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(q=='l') counterl++;
                if(q=='B') counterB++;
                if(q=='G') counterG++;
                if(q=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(q=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(q=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h-2,"S");
               customprint(k-1,h-1,'H');
               k--;
               h--;
            }
        case 'i':
            list();
            break;
        case ' ':
            if(def==1||def==5){
                if(c!='|'&&c!='-') mvprintw(k+1,h+1,".");
                if(x!='|'&&x!='-') mvprintw(k+1,h,".");
                if(z!='|'&&z!='-') mvprintw(k+1,h-1,".");
                if(a!='|'&&a!='-') mvprintw(k,h-1,".");
                if(d!='|'&&d!='-') mvprintw(k,h+1,".");
                if(e!='|'&&e!='-') mvprintw(k-1,h+1,".");
                if(w!='|'&&w!='-') mvprintw(k-1,h,".");
                if(q!='|'&&q!='-') mvprintw(k-1,h-1,".");
                mvprintw(0,0,"enemy killed                  ");
                break;
            }
            else{
                if(def==2) counterdagger--;
                if(def==3) counterwand--;
                if(def==4) counterarrow--;
                char dir=getch();
                if(dir=='d'){
                    if(d!='|'&&d!='-') mvprintw(k,h+1,".");
                }
                if(dir=='w'){
                    if(w!='|'&&w!='-') mvprintw(k-1,h,".");
                }
                if(dir=='a'){
                    if(a!='|'&&a!='-') mvprintw(k,h-1,".");
                }
                if(dir=='x'){
                    if(x!='|'&&x!='-') mvprintw(k+1,h,".");
                }
                mvprintw(0,0,"enemy killed                     ");
                break;
            }         
        default:
            break;
        }
    }
}
void moverroom(int pos,int x,int l,int h,int k){
    while(1){
        if(h==x&&k==pos&&!locker) break;
        int p;
        char c=mvinch(k+1,h+1);
        char x=mvinch(k+1,h);
        char z=mvinch(k+1,h-1);
        char a=mvinch(k,h-1);
        char d=mvinch(k,h+1);
        char e=mvinch(k-1,h+1);
        char w=mvinch(k-1,h);
        char q=mvinch(k-1,h-1);
        if(c=='D'||x=='D'||z=='D'||a=='D'||d=='D'||e=='D'||w=='D'||q=='D'){
            health--;
            mvprintw(0,70,"health: %d",health);
            mvprintw(0,0,"you got damage                ");
            if(health<=0){
                j=1;
                endgame();
                return;
            }
        }
        if(c=='Q'||x=='Q'||z=='Q'||a=='Q'||d=='Q'||e=='Q'||w=='Q'||q=='Q'){
            health--;
            mvprintw(0,70,"health: %d",health);
            mvprintw(0,0,"you got damage               ");
            if(health<=0){
                j=1;
                endgame();
                return;
            }
        }
        if(c=='I'||x=='I'||z=='I'||a=='I'||d=='I'||e=='I'||w=='I'||q=='I'){
            health--;
            mvprintw(0,70,"health: %d",health);
            mvprintw(0,0,"you got damage                ");
            if(health<=0){
                j=1;
                endgame();
                return;
            }
        }
        if(c=='S'||x=='S'||z=='S'||a=='S'||d=='S'||e=='S'||w=='S'||q=='S'){
            health--;
            mvprintw(0,70,"health: %d",health);
            mvprintw(0,0,"you got damage              ");
            modes=1;
            if(health<=0){
                j=1;
                endgame();
                return;
            }
        }
        if(c=='U'||x=='U'||z=='U'||a=='U'||d=='U'||e=='U'||w=='U'||q=='U'){
            health--;
            modeu=1;
            mvprintw(0,70,"health: %d",health);
            mvprintw(0,0,"you got damage               ");
            if(health<=0){
                j=1;
                endgame();
                return;
            }
        }
        char m=getch();
        switch(m){
        case 'c':
            if(c!='O'&&c!='|'&&c!='-'&&c!='D'&&c!='Q'&&c!='I'&&c!='S'&&c!='U'){
                if(c=='&'){
                    p=rand()%8999+1000;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(c=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(c=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(c=='l') counterl++;
                if(c=='B') counterB++;
                if(c=='G') counterG++;
                if(c=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(c=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(c=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
                mvaddch(k,h,'.');
                //if(modes) mvprintw(k+1,h,"S");
                customprint(k+1,h+1,'H');
                h++;
                k++;
            }
            break;
        case 'x':
            if(x!='O'&&x!='|'&&x!='-'&&x!='D'&&x!='Q'&&x!='I'&&x!='S'&&x!='U'){
                if(x=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(x=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(x=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(x=='l') counterl++;
                if(x=='B') counterB++;
                if(x=='G') counterG++;
                if(x=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(x=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(x=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h-1,"S");
               customprint(k+1,h,'H');
               k++;
            }
            break;
        case 'z':
            if(z!='O'&&z!='|'&&z!='-'&&z!='D'&&z!='Q'&&z!='I'&&z!='S'&&z!='U'){
                if(z=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(z=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(z=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(z=='l') counterl++;
                if(z=='B') counterB++;
                if(z=='G') counterG++;
                if(z=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(z=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(z=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h-2,"S");
               customprint(k+1,h-1,'H');
               k++;
               h--;
            }
            break;
        case 'a':
            if(a!='O'&&a!='|'&&a!='-'&&a!='D'&&a!='Q'&&a!='I'&&a!='S'&&a!='U'){
                if(a=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(a=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(a=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(a=='l') counterl++;
                if(a=='B') counterB++;
                if(a=='G') counterG++;
                if(a=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(a=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(a=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h-2,"S");
               customprint(k,h-1,'H');
               h--;
            }
            break;
        case 'd':
            if(d!='O'&&d!='|'&&d!='-'&&d!='D'&&d!='Q'&&d!='I'&&d!='S'&&d!='U'){
                if(d=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(d=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(d=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(d=='l') counterl++;
                if(d=='B') counterB++;
                if(d=='G') counterG++;
                if(d=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(d=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(d=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h,"S");
               customprint(k,h+1,'H');
               h++;
            }
            break;
        case 'e':
            if(e!='O'&&e!='|'&&e!='-'&&e!='D'&&e!='Q'&&e!='I'&&e!='S'&&e!='U'){
                if(e=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(e=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(e=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(e=='l') counterl++;
                if(e=='B') counterB++;
                if(e=='G') counterG++;
                if(e=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(e=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(e=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h,"S");
               customprint(k-1,h+1,'H');
               k--;
               h++;
            }
            break;
        case 'w':
            if(w!='O'&&w!='|'&&w!='-'&&w!='D'&&w!='Q'&&w!='I'&&w!='S'&&w!='U'){
                if(w=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(w=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(w=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(w=='l') counterl++;
                if(w=='B') counterB++;
                if(w=='G') counterG++;
                if(w=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(w=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(w=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h-1,"S");
               customprint(k-1,h,'H');
               k--;
            }
            break;
        case 'q':
            if(q!='O'&&q!='|'&&q!='-'&&q!='D'&&q!='Q'&&q!='I'&&q!='S'&&q!='U'){
                if(q=='&'){
                    p=rand()%9999;
                    mvprintw(0,0,"your password can be recursive too %d",p);
                }
                if(q=='@'){
                    lock(p);
                    if(locker){
                        error++;
                        break;
                    }
                }
                if(q=='Y') counterY++;
                if(c=='/') counterdagger=counterdagger+2;
                if(c=='!') counterwand++;
                if(c=='>') counterarrow=counterarrow+5;
                if(q=='l') counterl++;
                if(q=='B') counterB++;
                if(q=='G') counterG++;
                if(q=='*'){
                    health--;
                    if(health<=0){
                        endgame();
                        j=1;
                        return;
                    }
                    mvprintw(0,70,"health: %d",health);
                }
                if(q=='f'){
                    if(health==10) counterf++;
                    else{
                        health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                if(q=='F'){
                    if(health==10) counterF++;
                    else{
                        health++;
                        if(health!=10) health++;
                        mvprintw(0,70,"health: %d",health);
                    }
                }
                mvprintw(1,70,"Gold:%d",counterB*3+counterG);
               mvaddch(k,h,'.');
               //if(modes) mvprintw(k+1,h-2,"S");
               customprint(k-1,h-1,'H');
               k--;
               h--;
            }
            break;
        case 'i':
            list();
            break;
        case ' ':
            if(def==1||def==5){
                if(c!='|'&&c!='-') mvprintw(k+1,h+1,".");
                if(x!='|'&&x!='-') mvprintw(k+1,h,".");
                if(z!='|'&&z!='-') mvprintw(k+1,h-1,".");
                if(a!='|'&&a!='-') mvprintw(k,h-1,".");
                if(d!='|'&&d!='-') mvprintw(k,h+1,".");
                if(e!='|'&&e!='-') mvprintw(k-1,h+1,".");
                if(w!='|'&&w!='-') mvprintw(k-1,h,".");
                if(q!='|'&&q!='-') mvprintw(k-1,h-1,".");
                mvprintw(0,0,"enemy killed                  ");
                break;
            }
            else{
                if(def==2) counterdagger--;
                if(def==3) counterwand--;
                if(def==4) counterarrow--;
                char dir=getch();
                if(dir=='d'){
                    if(d!='|'&&d!='-') mvprintw(k,h+1,".");
                }
                if(dir=='w'){
                    if(w!='|'&&w!='-') mvprintw(k-1,h,".");
                }
                if(dir=='a'){
                    if(a!='|'&&a!='-') mvprintw(k,h-1,".");
                }
                if(dir=='x'){
                    if(x!='|'&&x!='-') mvprintw(k+1,h,".");
                }
                mvprintw(0,0,"enemy killed                     ");
                break;
            }    
        default:
            break;
        }
    }
}
void displayMainMenu();
int validateemail(char *email){
    int len=strlen(email);
    int i=0;
    int counter=0;
    while(*(email+i)!='\0'){
        if(*(email+i)=='@'){
            counter++;
        }
        i++;
    }
    if(counter!=1) return 0;
    else{
        i=0;
        while(*(email+i)!='@'){
            i++;
        }
        int counter2=0;
        while(*(email+i)!='\0'){
            if(*(email+i)=='.'){
                counter2++;
            }
            i++;
        }
        if(counter2!=1) return 0;
        return 1;
    }
}
int validatePassword(char *password){
    int upper= 0,lower=0,digit=0;
    int len=strlen(password);
    if(len<7) return 0;
    for (int i=0;i<len;i++){
        if(password[i]>='A'&&password[i]<='Z') upper=1;
        if(password[i]>='a'&&password[i]<='z') lower=1;
        if(password[i]>='0'&&password[i]<='9') digit=1;
    }
    return upper && lower && digit;
}
int generaterandom(char *password,int length){
    const char charset[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charsetSize=strlen(charset);
    if(length < 1) return 0;
    srand(time(NULL));
    for (int i=0;i<length;i++){
        password[i]=charset[rand() % charsetSize];
    }
    password[length]='\0';
    return 1;
}
void newgame();
void loadgame();
int compare(const void *a, const void *b){ 
    point *temp1 = (point*)a;
    point *temp2 = (point*)b;
    return temp2->totalscore - temp1->totalscore;
}
void leaderboard(){
    clear();
    FILE *file=fopen("point.txt","r");
    char line[100];
    point c[100];
    int i=0;
    while(fgets(line,sizeof(line),file)){
        sscanf(line,"%49[^,],%d,%d,%d,%d\n",c[i].username,&c[i].rank,&c[i].totalscore,&c[i].savedgold,&c[i].totalgame);
        i++;
    }
    fclose(file);
    qsort(c,i,sizeof(point),compare);
    start_color();
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    int j=0;
    while(j<8){
        if(!strcmp(c[j].username,player)) break;
        j++;
    }
    if(j!=8) mvprintw(2*j,70,"<-----");
    mvprintw(0,0, "    (LEGEND) 1.user name:%s, totalscore:%d ,rank:1, savedgold:%d",c[0].username,c[0].totalscore,c[0].savedgold);
    mvprintw(2,0, "    (GOAT) 2.user name:%s, totalscore:%d ,rank:2, savedgold:%d",c[1].username,c[1].totalscore,c[1].savedgold);
    mvprintw(4,0, "    (KING) 3.user name:%s, totalscore:%d ,rank:3, savedgold:%d",c[2].username,c[2].totalscore,c[2].savedgold);
    attroff(COLOR_PAIR(2));
    refresh();
    i=i-3;
    if(i-->0) mvprintw(6,0, "4.user name:%s, totalscore:%d ,rank:4, savedgold:%d",c[3].username,c[3].totalscore,c[3].savedgold);
    if(i-->0)mvprintw(8,0, "5.user name:%s, totalscore:%d ,rank:5, savedgold:%d",c[4].username,c[4].totalscore,c[4].savedgold);
    if(i-->0)mvprintw(10,0,"6.user name:%s, totalscore:%d ,rank:6, savedgold:%d",c[5].username,c[5].totalscore,c[5].savedgold);
    if(i-->0)mvprintw(12,0,"7.user name:%s, totalscore:%d ,rank:7, savedgold:%d",c[6].username,c[6].totalscore,c[6].savedgold);
    if(i-->0)mvprintw(14,0,"8.user name:%s, totalscore:%d ,rank:8, savedgold:%d",c[7].username,c[7].totalscore,c[7].savedgold);
    refresh();
    getch();    
}
void profile(char* usern){
    int col,row;
    getmaxyx(stdscr,row,col);
    echo();
    int choice;
    int counter=0;
    FILE *file=fopen("point.txt","r");
    char line[100];
    char fileusername[70];
    int filerank;
    int filetotalscore;
    int filesavedgold;
    int filetotalgame;
    while(fgets(line,sizeof(line),file)){
        sscanf(line,"%49[^,],%d,%d,%d,%d\n",fileusername,&filerank,&filetotalscore,&filesavedgold,&filetotalgame);
        if(!strcmp(usern,fileusername)){
            fclose(file);
            break;
        }
    }
    clear();
    mvprintw(row/2-7,col/2-10, "Profile");
    mvprintw(row/2-5,col/2-10, "Username: %s",usern);
    mvprintw(row/2-3,col/2-10, "Rank: %d",filerank);
    mvprintw(row/2-1,col/2-10, "Totalscore: %d",filetotalscore);
    mvprintw(row/2+1,col/2-10, "Savedgold: %d",filesavedgold);
    mvprintw(row/2+3,col/2-10, "Totalgame: %d",filetotalgame);
    refresh();
    getch();    
}
void herocolor(){
    int col,row;
    getmaxyx(stdscr,row,col);
    echo();
    int choice;
    int counter=0;
    while(17){
        if(counter) break;
        clear();
        mvprintw(row/2-7,col/2-10, "Color menu");
        mvprintw(row/2-5,col/2-10, "1. Red");
        mvprintw(row/2-3,col/2-10, "2. Blue");
        mvprintw(row/2-1,col/2-10, "3. Green");
        mvprintw(row/2+1,col/2-10, "4. White");
        mvprintw(row/2+3,col/2-10, "5. Back");
        mvprintw(row/2+5,col/2-10, "Enter your choice: ");
        refresh();
        scanw("%d",&choice);
        switch(choice){
            case 1:
                color=1;
                mvprintw(row/2+5,col/2-10, "Hero color set to Red");
                getch();
                counter++;
                break;
            case 2:
                color=2;
                mvprintw(row/2+5,col/2-10, "Hero color set to Blue");
                getch();
                counter++;
                break;
            case 3:
                color=3;
                mvprintw(row/2+5,col/2-10, "Hero color set to Green");
                getch();
                counter++;
                break;
            case 4:
                color=4;
                mvprintw(row/2+5,col/2-10, "Hero color set to White");
                getch();
                counter++;
                break;
            case 5:
                counter++;
                break;   
            default:
                mvprintw(row/2+7,col/2-10,"Invalid choice.");
                getch();
        }
    }
}
void difficulty(){
    int col,row;
    getmaxyx(stdscr,row,col);
    echo();
    int choice;
    int counter=0;
    while(17){
        if(counter) break;
        clear();
        mvprintw(row/2-7,col/2-10, "Difficulty");
        mvprintw(row/2-5,col/2-10, "1. easy");
        mvprintw(row/2-3,col/2-10, "2. medium");
        mvprintw(row/2-1,col/2-10, "3. Hard");
        mvprintw(row/2+1,col/2-10, "4. Back");
        mvprintw(row/2+3,col/2-10, "Enter your choice: ");
        refresh();
        scanw("%d",&choice);
        switch(choice){
            case 1:
                diff=1;
                mvprintw(row/2+5,col/2-10, "Difficulty set to easy");
                getch();
                counter++;
                break;
            case 2:
                diff=2;
                mvprintw(row/2+5,col/2-10, "Difficulty set to medium");
                getch();
                counter++;
                break;
            case 3:
                diff=3;
                mvprintw(row/2+5,col/2-10, "Difficulty set to Hard");
                getch();
                counter++;
                break;
            case 4:
                counter++;
                break;
            default:
                mvprintw(row/2+7,col/2-10,"Invalid choice.");
                getch();
        }
    }
}
void music(){
   int col,row;
    getmaxyx(stdscr,row,col);
    echo();
    int choice;
    int counter=0;
    while(17){
        if(counter) break;
        clear();
        mvprintw(row/2-7,col/2-10, "Music");
        mvprintw(row/2-5,col/2-10, "1. music 1");
        mvprintw(row/2-3,col/2-10, "2. music 2");
        mvprintw(row/2-1,col/2-10, "3. music 3");
        mvprintw(row/2+1,col/2-10, "4. Back");
        mvprintw(row/2+3,col/2-10, "Enter your choice: ");
        refresh();
        scanw("%d",&choice);
        switch(choice){
            case 1:
                playMusic(songs[1]);
                counter++;
                break;
            case 2:
                playMusic(songs[2]);
                getch();
                counter++;
                break;
            case 3:
                playMusic(songs[3]);
                getch();
                counter++;
                break;
            case 4:
                counter++;
                break;
            default:
                mvprintw(row/2+7,col/2-10,"Invalid choice.");
                getch();
        }
    } 
}
void settings(){
    int col,row;
    getmaxyx(stdscr,row,col);
    echo();
    int choice;
    int counter=0;
    while(17){
        if(counter) break;
        clear();
        mvprintw(row/2-7,col/2-10, "Settings");
        mvprintw(row/2-5,col/2-10, "1. Difficulty");
        mvprintw(row/2-3,col/2-10, "2. music");
        mvprintw(row/2-1,col/2-10, "3. Hero color");
        mvprintw(row/2+1,col/2-10, "4. Back");
        mvprintw(row/2+3,col/2-10, "Enter your choice: ");
        refresh();
        scanw("%d",&choice);
        switch(choice){
            case 1:
                difficulty();
                break;
            case 2:
                music();
                break;
            case 3:
                herocolor();
                break;
            case 4:
                counter++;
                break;
            default:
                mvprintw(row/2+7,col/2-10,"Invalid choice.");
                getch();
        }
    }
}
void gamemenu(char* usern){
    int col,row;
    getmaxyx(stdscr,row,col);
    echo();
    int choice;
    int counter=0;
    while(17){
        if(counter) break;
        clear();
        mvprintw(0,0, "%s",usern);
        mvprintw(row/2-7,col/2-10, "Game menu");
        mvprintw(row/2-5,col/2-10, "1. New Game");
        mvprintw(row/2-3,col/2-10, "2. Continue Game");
        mvprintw(row/2-1,col/2-10, "3. Leaderboard");
        mvprintw(row/2+1,col/2-10, "4. Settings");
        mvprintw(row/2+3,col/2-10, "5. Profile");
        mvprintw(row/2+5,col/2-10, "6. Back");
        mvprintw(row/2+7,col/2-10, "Enter your choice: ");
        refresh();
        scanw("%d",&choice);
        switch(choice){
            case 1:
                j=0;
                newgame();
                break;
            case 2:
                loadgame();
                break;
            case 3:
                leaderboard();
                break;
            case 4:
                settings();
                break;
            case 5:
                if(!strcmp("Guest",usern)){
                    mvprintw(row/2+9,col/2-10,"can't access here as a Guest.");
                    getch();
                    break;
                }
                profile(usern);
                break;    
            case 6:
                counter++;
                break;   
            default:
                mvprintw(row/2+9,col/2-10,"Invalid choice.");
                getch();
        }
    }
}
int authenticater(char *username,char *password){
    FILE *file = fopen("info.txt","r");
    char line[200];
    char fileusername[70],filepass[70],fileemail[100];
    while(fgets(line,sizeof(line),file)){
        sscanf(line,"%49[^,],%49[^,],%99[^\n]",fileusername,filepass,fileemail);
        if(!strcmp(username,fileusername)&&!strcmp(password,filepass)){
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
void restore(){
    int col,row;
    char username[70],email[100];
    getmaxyx(stdscr,row,col);
    clear();
    mvprintw(row/2-7,col/2-10, "restore password");
    mvprintw(row/2-5,col/2-10, "username: ");
    echo();
    getstr(username);
    mvprintw(row/2-3,col/2-10, "email: ");
    getstr(email);
    FILE *file = fopen("info.txt","r");
    char line[200];
    char fileusername[70],filepass[70],fileemail[100];
    while(fgets(line,sizeof(line),file)){
        sscanf(line,"%49[^,],%49[^,],%99[^\n]",fileusername,filepass,fileemail);
        if(!strcmp(username,fileusername)&&!strcmp(email,fileemail)){
            fclose(file);
            mvprintw(row/2-1,col/2-10,"%s",filepass);
            getch();
            return;
        }
    }
    fclose(file);
    mvprintw(row/2-1,col/2-10,"there is no user.");
    getch();
    return;
}
int check(char *username){
    FILE *file = fopen("info.txt","r");
    char line[200];
    char fileusername[70],filepass[70],fileemail[100];
    while(fgets(line,sizeof(line),file)){
        sscanf(line,"%49[^,],%49[^,],%99[^\n]",fileusername,filepass,fileemail);
        if(!strcmp(username,fileusername)){
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}
void createnewuser(){
    clear();
    user newuser;
    point new;
    int col,row;
    getmaxyx(stdscr,row,col);
    while(17){
        char passwordConfirm[70];
        clear();
        mvprintw(row/2-5,col/2-10,"Create New User");
        mvprintw(row/2-3,col/2-10,"Enter username: ");
        echo();
        getstr(newuser.username);
        if(!check(newuser.username)){
            mvprintw(row/2-2,col/2-10,"this user name has been taken.");
            getch();
            continue;
        }
        mvprintw(row/2-7,col/2-30,"to create random password type random in both password and confirm password.");
        noecho();
        mvprintw(row/2-1,col/2-10,"Enter password: ");
        getstr(newuser.password);
        mvprintw(row/2,col/2-10, "Confirm password: ");
        getstr(passwordConfirm);
        if(strcmp(newuser.password,passwordConfirm)){
            mvprintw(row/2+1,col/2-10, "Passwords do not match.");
            getch();
        }
        else if(!strcmp(newuser.password,"random")){
            char randpass[70];
            generaterandom(randpass,10);
            strcpy(newuser.password,randpass);
            mvprintw(row/2+1,col/2-10,"your password is:%s",randpass);
            break;
        } 
        else if(!validatePassword(newuser.password)){
            mvprintw(row/2+1,col/2-40, "Password must be at least 7 characters and include uppercase,lowercase,and a digit.");
            getch();
        }
        else{
            break;
        }
    }
    mvprintw(row/2+3,col/2-10, "Enter email: ");
    echo();
    getstr(newuser.email);
    strcpy(new.username,newuser.username);
    new.rank=0;
    new.totalscore=0;
    new.savedgold=0;
    new.totalgame=0;
    while(!validateemail(newuser.email)){
        mvprintw(row/2+4,col/2-10, "Invalid email format.");
        getstr(newuser.email);
    }
    FILE *file=fopen("info.txt","a");
    fprintf(file,"%s,%s,%s\n",newuser.username,newuser.password,newuser.email);
    fclose(file);
    FILE *file1=fopen("point.txt","a");
    fprintf(file1,"%s,%d,%d,%d,%d\n",new.username,new.rank,new.totalscore,new.savedgold,new.totalgame);
    fclose(file1);
    mvprintw(row/2+5,col/2-10, "User created successfully!");
    getch();
}
void loginuser(){
    clear();
    char username[70],password[70];
    int col,row;
    getmaxyx(stdscr,row,col);
    int check=0;
    while(17){
        clear();
        mvprintw(row/2-7,col/2-10, "Login user");
        mvprintw(row/2-5,col/2-10, "username: ");
        echo();
        getstr(username);
        mvprintw(row/2-3,col/2-10, "password: ");
        noecho();
        getstr(password);
        if(authenticater(username, password)){
            mvprintw(row/2,col/2-10, "Login successful.");
            check++;
            strcpy(player,username);
            break;
        } 
        else{
            mvprintw(row/2,col/2-10, "Invalid username or password.");
            break;
        }
    }
    getch();
    if(check) gamemenu(username);
}
void loginmenu(){
    clear();
    int choice;
    int col,row;
    getmaxyx(stdscr,row,col);
    echo();
    int counter=0;
    char guest[70]="Guest";
    while(17){
        if(counter) break;
        clear();
        mvprintw(row/2-5,col/2-10, "Login menu");
        mvprintw(row/2-3,col/2-10, "1. Login with username");
        mvprintw(row/2-1,col/2-10, "2. play as a Guest");
        mvprintw(row/2+1,col/2-10, "3. restore password");
        mvprintw(row/2+3,col/2-10, "4. Back");
        mvprintw(row/2+5,col/2-10, "Enter your choice: ");
        refresh();
        scanw("%d",&choice);
        switch(choice){
            case 1:
                loginuser();
                break;
            case 2:
                strcpy(player,"Guest");
                gamemenu(guest);
                break;
            case 3:
                restore();
                break;
            case 4:
                counter++;
                break;   
            default:
                mvprintw(row/2+7,col/2-10,"Invalid choice.");
                getch();
        }
    }
}
void displayMainMenu(){
    clear();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    int choice;
    while(17){
        int col,row;
        getmaxyx(stdscr,row,col);
        clear();
        mvprintw(row/2-7,col/2-14, "After register,login to play rogue!");
        mvprintw(row/2-5,col/2-10, "Main menu");
        mvprintw(row/2-3,col/2-10, "1. Create New User");
        mvprintw(row/2-1,col/2-10, "2. Login User");
        mvprintw(row/2+1,col/2-10, "3. Exit");
        mvprintw(row/2+4,col/2-10, "Enter your choice: ");
        refresh();
        scanw("%d",&choice);
        switch(choice){
            case 1:
                createnewuser();
                break;
            case 2:
                loginmenu();
                break;
            case 3:
                return;
            default:
                mvprintw(row/2+5,col/2-10,"Invalid choice.");
                getch();
        }
    }
}
void endgame(){
    FILE *file=fopen("point.txt","r");
    char line[100];
    char fileusername[50];
    int filerank;
    int filetotalscore;
    int filesavedgold;
    int filetotalgame;
    while(fgets(line,sizeof(line),file)){
        sscanf(line,"%49[^,],%d,%d,%d,%d\n",fileusername,&filerank,&filetotalscore,&filesavedgold,&filetotalgame);
        if(!strcmp(player,fileusername)){
            fclose(file);
            FILE *file1=fopen("point.txt","a");
            fprintf(file1,"%s,%d,%d,%d,%d\n",player,filerank,filetotalscore+counterB*3+counterG,filesavedgold+counterB*3+counterG,filetotalgame+1);
            break;
        }
    }
    clear();
    if(j){
        mvprintw(5,30,"YOU WON");
        mvprintw(6,30,"gold: %d",counterB*3+counterG);
    }
    else{
        mvprintw(5,30,"YOU LOSE");
        mvprintw(6,30,"gold: %d",counterB*3+counterG);
    }
    getch();
    locker=0;
    error=0;
    floorr=1;
    counterY=0;
    counterl=0;
    counterB=0;
    counterG=0;
    counterdagger=0;
    counterwand=0;
    counterarrow=0;
    counterf=0;
    j=0;
    health=10;
    clear();
}
void newgame(){
    clear();
    mvprintw(0,70,"health: %d",health);
    mvprintw(1,70,"Gold:%d",counterB*3+counterG);
    noecho();
    int col,row;
    getmaxyx(stdscr,row,col);
    modes=0;
    int x1=3+rand()%5;
    int y1=3+rand()%5;
    int l1=9+rand()%4;
    int w1=5+rand()%3;
    int door_y1=1+rand()%(w1-3)+y1;
    printrooms(x1,y1,l1,w1,door_y1);
    int x=rand()%3+x1+1;
    int y=rand()%3+y1+1;
    char c=mvinch(y,x);
    if(c!='&'){
        customprint(y,x,'H');
    }
    else{
        customprint(y,x+1,'H');
        x++;
    }
    moveroom(door_y1,x1,l1,x,y);
    if(j) return;
    error=0;
    int x2=3+rand()%5+col/3;
    int y2=3+rand()%5;
    int l2=9+rand()%4;
    int w2=5+rand()%3;
    int door_y2=rand()%(w2-3)+y2+1;
    drawh1cor(x2,y2,door_y2,door_y1,x1+l1);
    int door_y3=rand()%(w2-3)+y2+1;    
    printrooms(x2,y2,l2,w2,door_y3);
    mvprintw(door_y2,x2,"+");
    mvprintw(door_y2,x2-1,"#");
    modes=0;
    moveroom(door_y3,x2,l2,x2,door_y2);
    if(j) return;
    error=0;
    int x3=3+rand()%5+2*col/3;
    int y3=3+rand()%5;
    int l3=9+rand()%4;
    int w3=5+rand()%3;
    int door_y4=rand()%(w3-3)+y3+1;
    drawh1cor(x3,y3,door_y4,door_y3,x2+l2);
    int door_y5=rand()%(w3-3)+y3+1;    
    printrooms(x3,y3,l3,w3,door_y5);
    mvprintw(door_y4,x3,"+");
    mvprintw(door_y4,x3-1,"#"); 
    modes=0;   
    moveroom(door_y5,x3,l3,x3,door_y4);
    if(j) return;
    error=0;
    int x4=3+rand()%5+2*col/3;
    int y4=3+rand()%5+row/2;
    int l4=9+rand()%4;
    int w4=5+rand()%3;
    int door_y6=rand()%(w4-3)+y4+1;
    drawvcor(x4,y4,door_y6,door_y5,x3+l3,l4);
    int door_y7=rand()%(w4-3)+y4+1;
    printrrooms(x4,y4,l4,w4,door_y7);
    mvprintw(door_y6,x4+l4,"+");
    modes=0;
    moverroom(door_y7,x4,l4,x4+l4,door_y6);
    if(j) return;
    error=0;
    int x5=3+rand()%5+col/3;
    int y5=3+rand()%5+row/2;
    int l5=9+rand()%4;
    int w5=5+rand()%3;
    int door_y8=rand()%(w5-3)+y5+1;
    drawh2cor(x5,y5,door_y8,door_y7,x4,l5);
    int door_y9=rand()%(w5-3)+y5+1;
    printrrooms(x5,y5,l5,w5,door_y9);
    mvprintw(door_y8,x5+l5,"+");
    mvprintw(door_y8,x5+l5+1,"#");
    modes=0;    
    moverroom(door_y9,x5,l5,x5+l5,door_y8);
    if(j) return;
    error=0;
    int x6=3+rand()%5;
    int y6=3+rand()%5+row/2;
    int l6=9+rand()%4;
    int w6=5+rand()%3;
    int door_y10=rand()%(w6-3)+y6+1;
    drawh2cor(x6,y6,door_y10,door_y9,x5,l6);
    int door_y11=rand()%(w6-3)+y6+1;
    if(floorr<4){
        printrrooms(x6,y6,l6,w6,door_y11);
        mvprintw(door_y10,x6+l6+1,"#");
        mvprintw(door_y10,x6+l6,"+");
        mvprintw(door_y11,x6,"X");
        modes=0;    
        moverroom(door_y11,x6,l6,x6+l6,door_y10);
        if(j) return;
        floorr++;
    }
    else{
        start_color();
        start_color();
        init_pair(8, COLOR_MAGENTA, COLOR_BLACK);
        attron(COLOR_PAIR(8));
        printrrooms(x6,y6,l6,w6,door_y11);
        attroff(COLOR_PAIR(8));
        mvprintw(door_y10,x6+l6,"+");
        mvprintw(door_y10,x6+l6+1,"#");
        mvprintw(door_y11,x6,"0");  
        modes=0;  
        moverroom(door_y11,x6,l6,x6+l6,door_y10);
        if(j){
            endgame();
            return;
        }
        endgame();
    }
    if(!j) newgame();
}
void loadgame(){
    clear();
    getch();
}
int main(){
    srand(time(NULL));
    initscr();
    cbreak();
    curs_set(0);
    displayMainMenu();
    endwin();
    return 0;
}

