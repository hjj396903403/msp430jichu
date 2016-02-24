
#include <msp430x14x.h>

void delay(int a)
{
  char i;
  for(;a>0;a--)
    for(i=200;i>0;i--);
}
void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P2SEL|=BIT3;//+BIT4;
  P2DIR=0XFF;
  P2OUT=0XFF;
  CCR0=32768;
  CCR1=32768;
 
  CCR2=1024;
 // CCTL2|=OUTMOD_7;
  TACTL=TASSEL_1+ID_0+MC_1;
 // LPM3;
  char i;
  while(1)
  {
    
    
      CCR1=CCR1-10;
      delay(50);
      if(CCR1<=0)
      {
        CCR1=32768;
      }
       CCTL1|=OUTMOD_7;
    
  }
 
}
