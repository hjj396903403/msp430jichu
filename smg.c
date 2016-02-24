
#include<msp430x14x.h>
#define uchar unsigned char
#define uint unsigned int

uchar tabel1[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f};
uchar tabel2[]={0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70};

void delay(uint a)
{
  uchar i;
  for(;a>0;a--)
    for(i=19;i>0;i--);
}
void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  uchar i;
  P1DIR=0XFF;
  P3DIR=0XFF;
  while(1)
  {
    for(i=0;i<8;i++)
    {
       P1OUT=tabel1[i];
       P3OUT=tabel2[i];
       delay(10);
    }
  }
  
}
