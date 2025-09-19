#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "fserieatmega.h"

OneWire ourWire(9); // Se establece el pin 9 (PB1) como bus OneWire

DallasTemperature sensors(&ourWire); // Se declara una variable u objeto para nuestro sensor

volatile int8_t temp_low, temp_high;

int main()
{

  init();
  serialbegin(9600);
  sensors.begin();         // Se inicia el sensor
  UCSR0B |= (1 << RXCIE0); // Habilitamos las interrupciones de recepción del USART

  while (1)
  {
    sensors.requestTemperatures();           // Se envía el comando para leer la temperatura
    float temp = sensors.getTempCByIndex(0); // Se obtiene la temperatura en ºC

    // enterizamos la temperatura multiplicandola por 100 ya que tenemos 2 decimales

    int16_t int_temp = temp * 100;

    // separamos la temperatura en parte alta y baja

    temp_high = (int_temp >> 8) & 0xff;
    temp_low = int_temp & 0xff;
  }
}

ISR(USART_RX_vect)
{
  int16_t dato_caracter;

  dato_caracter = serialread(); // leo el dato recibido en la interrupción

  if (dato_caracter == '&')
  {
    seriewritech(temp_high); // envío la parte alta de la temperatura
    seriewritech(temp_low);  // envío la parte baja de la temperatura
  }
}