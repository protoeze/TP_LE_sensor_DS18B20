#include<stdio.h>
#define  NEGRO 30
#define  ROJO 31
#define  VERDE 32
#define  MARRON  33
#define  AZUL 34
#define  PURPURA 35
#define  CYAN 36
#define BLANCO 37
#define AMARILLO 38


#define  negro 30
#define  rojo 31
#define  verde 32
#define  marron  33
#define  azul 34
#define  purpura 35
#define cyan 36
#define blanco 37
#define amarillo 38
#define normal 0
#define brillante 1
#define oscuro 2

//atributos especiales
#define italico 3
#define subrrayado 4
#define parpadealento 5
#define parpadearapido 6
#define videoinverso 7
#define tachado 9


#ifdef __linux__
#include<stdbool.h>
#include<sys/ioctl.h>
#include<asm/ioctls.h>
#include <termios.h>
#include<fcntl.h>
#include <unistd.h>

#include<signal.h>
#include<assert.h>

#include "termios.h"
//#include<string.h>

void cursoroff()
{

printf("\033[?25l");

}
void cursoron()
{


printf("\033[?25h");

}


void gotoxy(int x,int y)
{
printf("\033[%d;%dH",y,x);
fflush(stdin);

}



void clrscr()
{
 printf("\033[2J");

}


int kbhit() {
   static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;

}

int getch(void)
{      struct termios oldattr, newattr;
       int ch;
       tcgetattr( STDIN_FILENO, &oldattr );
       newattr = oldattr;
       newattr.c_lflag &= (~( ICANON | ECHO ));
       tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
       ch = getchar();
       tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
       return ch;
}





int getche(void)
{      struct termios oldattr, newattr;
       int ch;
       tcgetattr( STDIN_FILENO, &oldattr );
       newattr = oldattr;
       newattr.c_lflag &= (~( ICANON ));
       tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
       ch = getchar();
       tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
       return ch;
}





void setcolor(int CFRE,int CFON)
{

if(CFRE == amarillo)
    printf("\033[1;%d;%dm",marron,CFON+10);
else
  if(CFON==amarillo)
      printf("\033[1;%d;%dm",CFRE,marron+10);
  else
    if((CFRE==amarillo)&&(CFON==amarillo))
      printf("\033[1;%d;%dm",marron,marron+10);
else
  printf("\033[1;%d;%dm",CFRE,CFON+10);



}





void setcolorext(int CFRE,int CFON,int efecto)
{
printf("\033[%d;%d;%dm",efecto,CFRE,CFON+10);

}


void clreol()
{

 printf("\033[0K");
}

#elif _WIN32
#include<stdlib.h>
#include<string.h>
#include <conio.h>
//#include<windows.h>



void clrscr()
{
    system("cls");

}


void gotoxy(int x,int y)
{
static unsigned char bsys=0;
if(bsys==0)
{
 system("");
 bsys=1;
}
printf("\033[%d;%dH",y,x);
fflush(stdin);
}

 void setcolor(int CFRE,int CFON)
{
static unsigned char bsys=0;
if(bsys==0)
{
 system("");
 bsys=1;
}

if(CFRE == amarillo)
    printf("\033[1;%d;%dm",marron,CFON+10);
else
  if(CFON==amarillo)
      printf("\033[1;%d;%dm",CFRE,marron+10);
  else
    if((CFRE==amarillo)&&(CFON==amarillo))
      printf("\033[1;%d;%dm",marron,marron+10);
else
  printf("\033[1;%d;%dm",CFRE,CFON+10);


}

void setcolorext(int CFRE,int CFON,int efecto)
{
static unsigned char bsys=0;
if(bsys==0)
{
 system("");
 bsys=1;
}
printf("\033[%d;%d;%dm",efecto,CFRE,CFON+10);
}

void clreol()
{
static unsigned char bsys=0;
if(bsys==0)
{
 system("");
 bsys=1;
}

 printf("\033[0K");
}
void cursoroff()
{
static unsigned char bsys=0;
if(bsys==0)
{
 system("");
 bsys=1;
}

printf("\033[?25l");

}
void cursoron()
{
static unsigned char bsys=0;
if(bsys==0)
{
 system("");
 bsys=1;
}

printf("\033[?25h");

}





#endif
