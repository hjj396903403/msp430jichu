
#include <msp430x14x.h>

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  CCTL0|=CCIE;
  CCR0=2048;
  TACTL=TASSEL_1+ID_3+MC_1;
  P2DIR=0XFF;
  P2OUT=0XFF;
  _EINT();
  
}
#pragma vector =TIMERA0_VECTOR
__interrupt void TIMER_A(void)
{
  P2OUT=P2OUT>>1;
  while(P2OUT==0X00) P2OUT=0XFF;
}
