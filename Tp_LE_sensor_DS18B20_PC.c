#include <stdio.h>
#include <stdint.h>
#include "utiles.h"
#include "fserie.h"

int main()
{

uint8_t  buffer_datos[2]; // Solo contiene dos ya que es parte alta y baja de la temperatura
int tecla, puerto, get_temp;
bool recibio_dato;
float T_medida;

setcolor(blanco, negro);
    gotoxy(2,2);

    printf("Pulse 0 para salir");

    gotoxy(3,3);
    printf("Ingrese puerto COM");
    scanf("%d", &puerto);

    initserie(puerto, 9600);

    tecla = ' ';
    cursoroff();

    while( tecla != '0')
    {

    if(kbhit() != 0)
        tecla = getch();

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


}
 }

 closeserie();
    cursoron();
}
