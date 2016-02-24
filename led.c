
#include <msp430x14x.h>


void delay(unsigned int a)
{
    unsigned char i;
    for(;a>0;a--)
      for(i=19;i>0;i--);
}
void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P2DIR=0XFF;
  P2OUT=0XFF;
  while(1)
  {
      P2OUT^=0XFF;
      delay(1000);
      
  }
 
}
