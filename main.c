/******************************************************************************
Hardware: atmega8

    This code was written today to do the things.
     By me.


portB goes to the array cathodes
portD goes to the array anodes.
    
                       +---\/---+
        (/RESET)  PC6  |1     28|  PC5  (ADC5 / SCL)
           (RXD)  PD0  |2     27|  PC4  (ADC4 / SDA)
           (TXD)  PD1  |3     26|  PC3  (ADC3)
          (INT0)  PD2  |4     25|  PC2  (ADC2)
          (INT1)  PD3  |5     24|  PC1  (ADC1)
      (XCK / T0)  PD4  |6     23|  PC0  (ADC0)
                  VCC  |7     22|  GND
                  GND  |8     21|  AREF
 (XTAL1 / TOSC1)  PB6  |9     20|  AVCC
 (XTAL2 / TOSC2)  PB7  |10    19|  PB5  (SCK)          
            (T1)  PD5  |11    18|  PB4  (MISO)         
          (AIN0)  PD6  |12    17|  PB3  (MOSI / OC2)  
          (AIN1)  PD7  |13    16|  PB2  (SS / OC1B)    
          (ICP1)  PB0  |14    15|  PB1  (OC1A)         
                       +--------+

    
*******************************************************************************/
 
/****************************| INCLUDGEABLES |********************************/
 
#include <avr/io.h>
#include <stdint.h>
#include "avrcommon.h"
#include "usart.h"


/*****************************| DEFINIATIONS |********************************/
  
 
/*****************************| VARIDIABLIES |********************************/
 
/************************| FUNKSHION DECLARATIONS |*************************/
void    Delay  ( unsigned int delay) ;
void    Delay2 ( unsigned int delay) ;
void    setLED(uint8_t i) ;
void    dumpMap(void);
uint8_t waitKey();

/****************************| MANE CODY... |***********************************/
 /*

0x01, 0x38, 0x39, 0x30, 0x28, 0x20, 0x10, 0x08, 0x09, 0x00, 0x19, 0x18, 0x11, 0x29, 0x1A, 0x02, 0x1B, 0x31, 0x0B, 0x0A, 0x0C, 0x13, 0x05, 0x03, 0x0D, 0x23, 0x25, 0x04,
 0x2A, 0x14, 0x3A, 0x2B, 0x21, 0x32, 0x12, 0x22, 0x2C, 0x33, 0x2E, 0x35, 0x2D, 0x1D, 0x3B, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

0x01, 0x38, 0x39, 0x30, 0x28, 0x20, 0x10, 0x08, 0x09, 0x00, 0x19, 0x18, 0x11, 0x29, 0x1A, 0x02, 0x1B, 0x31, 0x0B, 0x0A, 0x0C, 0x13, 0x05, 0x03, 0x0D, 0x23, 0x25, 0x04,
 0x2A, 0x14, 0x3A, 0x2B, 0x21, 0x32, 0x12, 0x22, 0x2C, 0x33, 0x2E, 0x35, 0x2D, 0x1D, 0x3B, 0x34, 0x3D, 0x3F, 0x36, 0x37, 0x15, 0x3E, 0x2F, 0x3C, 0x1F, 0x16, 0x24, 0x1C
, 0x1E, 0x26, 0x0F, 0x17, 0x27, 0x0E, 0x06, 0x07


 */
 
 
 uint8_t remap[64] = { 0x01, 0x38, 0x39, 0x30, 0x28, 0x20, 0x10, 0x08, 
                       0x09, 0x00, 0x19, 0x18, 0x11, 0x29, 0x1A, 0x02, 
		       0x1B, 0x31, 0x0B, 0x0A, 0x0C, 0x13, 0x05, 0x03, 
		       0x0D, 0x23, 0x25, 0x04, 0x2A, 0x14, 0x3A, 0x2B, 
		       0x21, 0x32, 0x12, 0x22, 0x2C, 0x33, 0x2E, 0x35, 
		       0x2D, 0x1D, 0x3B, 0x34, 0x3D, 0x3F, 0x36, 0x37, 
		       0x15, 0x3E, 0x2F, 0x3C, 0x1F, 0x16, 0x24, 0x1C, 
		       0x1E, 0x26, 0x0F, 0x17, 0x27, 0x0E, 0x06, 0x07 }; 
		                  
 
int main (void)  {
  uint8_t i, k;

  DDRB = (INPUT << PB0)|(INPUT << PB1)|(INPUT << PB2)|(INPUT << PB3)|(INPUT << PB4)|(INPUT << PB5)|(INPUT << PB6)|(INPUT << PB7);
  DDRC = (INPUT << PC0)|(INPUT << PC1)|(INPUT << PC2)|(INPUT << PC3)|(INPUT << PC4)|(INPUT << PC5)|(INPUT << PC6);
  DDRD = (INPUT << PD0)|(INPUT << PD1)|(INPUT << PD2)|(INPUT << PD3)|(INPUT << PD4)|(INPUT << PD5)|(INPUT << PD6)|(INPUT << PD7);        

  USART_Init( 54 ); //9600 fuseintfast

  PORTB = 0x00;  // cathodes
  PORTD = 0xFF;  // anodes
  
  i = 0;

  while(1) {
  
 //  setLED(i);
 //  k = waitKey();
   /*
   USART_printhex(k); i++;
   USART_Transmit( '\r' );
   USART_ransmit( '\n' );
   */
   /*
   #define KEY_UP      0x03
   #define KEY_DOWN    0x07
   #define KEY_RESET   0x02
   #define KEY_NEXT    0x08
   #define KEY_PREV    0x0A
   #define KEY_DUMP    0x0C
   
   if (k == KEY_UP) { if (remap[i] < 64 ) remap[i]++; }
   if (k == KEY_DOWN) { if (remap[i] != 0) remap[i]--; }
   if (k == KEY_RESET) i = 0;
   if (k == KEY_NEXT) if (i < 64) i++;
   if (k == KEY_PREV) if (i != 0) i--;
   if (k == KEY_DUMP) dumpMap();
  */
    
  
    for (i = 0; i < 64; i++) {
     setLED(i);
     Delay (32768);    
    }
    
    
  }
 

 
  return 0;
}


//-------------------------------------------------------------------

#define KBMASK 0x3C
uint8_t waitKey(){  
  while( (PINC & KBMASK) != 0);  // wait for any key-ups.
  Delay(5000); // debounce?
  while( (PINC & KBMASK) == 0); // wait for a key
  Delay(5000); // debounce?
  return ((PINC & KBMASK)>>2);
}

void setLED(uint8_t i) {
  uint8_t mi;
  uint8_t r,c;
  
  mi = remap[i];
  r = 1 << (mi & 0x07);
  c = 1 << ((mi>>3) & 0x07);
  DDRB = r;
  //ugh
  DDRD = (c & 0xFC) | 0x03; PORTD = c & 0xFC; // we have to adjust the PORT setting to avoid pullups
  if (c & 0x01){ SetBit(0, DDRC); SetBit(0, PORTC); }else{ ClearBit(0, DDRC); ClearBit(0, PORTC);}
  if (c & 0x02){ SetBit(1, DDRC); SetBit(1, PORTC); }else{ ClearBit(1, DDRC); ClearBit(1, PORTC);};    

}


void dumpMap() {
  uint8_t i;
  for ( i = 0; i < 64; i++) {
  
    USART_Transmit( '0' );
    USART_Transmit( 'x' );
    USART_printhex(remap[i]);
    USART_Transmit( ',' );
    USART_Transmit( ' ' );
  }
  USART_Transmit( '\r' );
  USART_Transmit( '\n' );
  
}
    
//------------------------| FUNCTIONS |------------------------

void Delay(uint16_t d) {
  for (; d != 0; d--) {
    asm volatile ("nop"::); 
  }
}

void Delay2(uint16_t d) {
  for ( ; d != 0; d--) {
    Delay(65000);
  }
}


