
#include "avr/io.h"
#include <string.h>
#define initserie serialbegin
#define seriereadch serialread
#define seriewritech serialwrite
#define serieavailable serialavailable
#define seriereadch2 serialread2

void serialbegin(uint32_t velo)
{
   
   switch(velo)
   {
    case 1200:
    
    UBRR0H = 0x03;
    UBRR0L = 0x40;
    UCSR0A = 0x0;
    break;
    
    case 2400:
    
    UBRR0H = 0x01;
    UBRR0L = 0xA0;
    UCSR0A = 0x0;
    break;
    
    case 4800:
    
    UBRR0H = 0x00;
    UBRR0L = 207;
    UCSR0A = 0x0;
    break;

   case 9600:
    
    UBRR0H = 0x00;
    UBRR0L = 103;
    UCSR0A = 0x0;
    break;


case 19200:
    
    UBRR0H = 0x00;
    UBRR0L = 51;
    UCSR0A = 0x0;
    break;
  case 38400:
    
    UBRR0H = 0x00;
    UBRR0L = 25;
    UCSR0A = 0x0;
    break;  
    
    case 57600:
    
    UBRR0H = 0x00;
    UBRR0L = 16;
    UCSR0A = 0x0;
    break;
    
    case 115200:
    
    UBRR0H = 0x00;
    UBRR0L = 0x08;
    UCSR0A = 0x0;
    break;

   

   case 200000:
    
    UBRR0H = 0x00;
    UBRR0L = 9;
    UCSR0A = 0x2;
    break;
   
   
   

   
   case 500000:
    
    UBRR0H = 0x00;
    UBRR0L = 3;
    UCSR0A = 0x2;
    break;
   
   
   


   
   case 1000000:
    
    UBRR0H = 0x00;
    UBRR0L = 1;
    UCSR0A = 0x2;
    break;
   
   
   };


    UCSR0B = (1 << RXEN0) |  (1 << TXEN0);  
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
       
}



void serialwrite(uint8_t ch)
{
    uint8_t datoser;
    do{

    datoser= (UCSR0A & (1<< UDRE0));

    }while(datoser == 0);
    
    UDR0 = ch;
}


bool serialavailable()
{
  if((UCSR0A & (1<< RXC0)) != 0 )
    return(true);
  else
     return(false);  

}

uint8_t serialread()
{
    
    
    return(UDR0);
}

int16_t serialread2()
{
   if((UCSR0A & (1<< RXC0)) != 0 )
    return(UDR0);
  else
     return(256);  
 
    
    
}



void seriewritestr(char *pal)
{
    int16_t  ct;
    int16_t ctmax;
    ctmax=strlen(pal);
	ct=0;

    for(ct=0;ct < ctmax;ct++)
    {
        
        seriewritech(pal[ct]);        
        
        
    }
}





