
#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>



#endif
#include "fserie.h"
#include "utiles.h"
#include<stdint.h>
volatile int16_t tbase;
void imprimir(int x, int y, char *pal);
void imprimirext(int x, int y, char *pal, void *font);

float adquirir(float);
               //static void key(unsigned char key, int x, int y);
static void key(unsigned char key, int x, int y);

void pantalla();
void mousepress(int button, int state, int x, int y);

int mouse_x,mouse_y,WINDOWSIZE;


volatile bool fgraf=true;


static void resize(int width, int height)
{
    glViewport(0, 0, width, height);

    glClearColor(0,0.8,0.8,1);
    glClear(GL_COLOR_BUFFER_BIT);
    pantalla();
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity() ;
    glFlush();


}
static void dibujar()
{
//float t;
float Tm,Tm0;
static float t=0;
static int reta=0;
static float Tmant=20;
static float tant=0;
int16_t cmux;
//se reemplazo el while por un if
//pues gluTmainloop repite  a la función


if(t==0)
{

glClearColor(0,0.8,0.8,1);
glClear(GL_COLOR_BUFFER_BIT);

pantalla();
}
glLineWidth(1);
//glPointSize(1);
glColor3f(0,0,0);

//******comienzo del dibujo de grafico basado en punros****

    if(t<600)
    {


    glBegin(GL_LINES);

    Tm=adquirir(t);


   if(Tm > -1000)
   {


    glVertex2f(tant,Tmant*2.0);
    glVertex2f(t,Tm*2.0);



    Tmant=Tm;
    tant=t;
    t=t+1;
   }

  glEnd();

    }
 else
    {
      t=0;
      tant=0;
    }

 glFlush();
//}
//******fin del grafico de puntos

glutPostRedisplay();
}





int main(int argc, char *argv[])
{
//****Aqui va el menu de ingreso del puerto serie y
//y el llamado a initserie***

int tecla, puerto;


setcolor(blanco, negro);
    gotoxy(2,2);

    printf("Pulse 0 para salir");

    gotoxy(3,3);
    printf("Ingrese puerto COM");
    scanf("%d", &puerto);

    initserie(puerto, 9600);

    tecla = ' ';

 tbase=10;//tiempo base de 10 mseg si usa timer0
  gotoxy(20,6);
    printf("Tiempo base:%3d",tbase);


  glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);

     glutInitWindowSize(650,650);

    glutInitWindowPosition(650,0);
    glutCreateWindow("graficos para el Proyecto");
    glutReshapeFunc(resize);
    gluOrtho2D(-50,650,-300,300);

    glutKeyboardFunc(key);
    glutDisplayFunc(dibujar);
      glutMainLoop();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////




cursoron();
closeserie();
 return 0;
}

static void key(unsigned char key, int x, int y)
{

    switch (key)
    {
        case 27 :
        case '0':
         exit(0);

    //aqui va el código que le permite pulsar las teclas y generar transmisiones hacia el puerto serie

    }
    gotoxy(20,6);
    printf("Tiempo base:%4d",tbase);

    glutPostRedisplay();
}

void mousepress(int button, int state, int x, int y) {


  if(state == GLUT_DOWN) {

    mouse_x = x;
    mouse_y = y;
    //(x,y) are in window coordinates, where the origin is in the upper
    //left corner; our reference system has the origin in lower left
    //corner, this means we have to reflect y
    mouse_y = WINDOWSIZE - mouse_y;
    //printf("mouse pressed at (%d,%d)\n", mouse_x, mouse_y);

  }

  glutPostRedisplay();
}





  float adquirir(float tx)
{
    bool recibio_dato;
static float T_medida ;
    uint8_t  buffer_datos[2]; // Solo contiene dos ya que es parte alta y baja de la temperatura
int get_temp;
      static float tmmm=0;
    float Tm,Vm,alfa;
    bool entro;
    int16_t datov;

  alfa=0.05;//valor recomendado se alfa si utilza media movil

seriewritestr("&");

    recibio_dato = seriereadstr(buffer_datos, 2);

    if(recibio_dato == true)
{
    // obtenemos las partes altas y bajas de la temperatura

    get_temp = (((int)buffer_datos[0])<< 8) + buffer_datos[1];

    // ya que en arduino la enterizamos multiplicandola por 100, ahora la dividimos por 100 para volver a tener los decimales

    T_medida = get_temp / 100.0;

    gotoxy(4,6);
    printf("La temperatura del sensor DS18B20 es %4.2f C : ", T_medida);





if(recibio_dato)
 return(T_medida);//o return(tmmm); si  utiliza media movil
else
  return(-1000);

}
}

void pantalla()
{
char NUM[8];
int8_t xi;
int16_t i;
xi=1;


//ahora dibujar loa cuadricula***
glLineWidth(1);
glColor3f(1.0,1.0,1.0);
glBegin(GL_LINES);
//imprimir(300,100,"Graficas");

for(i=0;i<30;i++)
{


glVertex2i(xi+(i+1)*20,-600);
glVertex2i(xi+(i+1)*20,600);
}


for(i=0;i<60;i++)
{


glVertex2i(xi ,-600+(i+1)*20);
glVertex2i(600,-600+(i+1)*20);

}




glEnd();

//ahora dibujar los  ejes***
glLineWidth(4);
glColor3f(1,0,0);

glBegin(GL_LINES);
glVertex2i(xi,-600);
glVertex2i(xi,600);
glVertex2i(xi,0);
glVertex2i(600,0);



glEnd();
//imprimir numeros del ejex
for(i=0;i<31;i++)
{

glColor3f(0,0,0);
 sprintf(NUM,"%d",i);
imprimirext(20*i,-20,NUM,GLUT_BITMAP_HELVETICA_10);



}
//imprimir numeros del eje y
for(i=-15;i<15;i++)
{

glColor3f(0,0,0);
 sprintf(NUM,"%2d",i*10);
imprimirext(-20,20*i,NUM,GLUT_BITMAP_HELVETICA_10);



}


glColor3f(1,0,0);

imprimirext(300,-50,"Graficas",GLUT_BITMAP_8_BY_13);




}

void ejes()
{
int8_t xi;
xi=1;

glLineWidth(4);
glColor3f(1,0,0);
glBegin(GL_LINES);

glVertex2i(xi,-600);
glVertex2i(xi,600);

glVertex2i(xi,0);
glVertex2i(600,0);





glEnd();


}

void imprimir(int x, int y, char *pal)
{
  int MAXPAL, ct;

  glRasterPos2f(x, y);
  MAXPAL = strlen(pal);
  ct=0;

   while(ct<MAXPAL) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pal[ct]);
    ct++;
    }
}

void imprimirext(int x, int y, char *pal,void *font)
{
  int MAXPAL, ct;

  glRasterPos2f(x, y);
  MAXPAL = strlen(pal);
  ct=0;

   while(ct<MAXPAL) {
    glutBitmapCharacter(font, pal[ct]);
    ct++;
    }
}









