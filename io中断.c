
#include <msp430x14x.h>
#define uchar unsigned char 
#define uint unsigned int
#define keyin (P1IN & 0X0F)
uchar tabel1[]={~0x3f,~0x06,~0x5b,~0x4f,~0x66,~0x6d,~0x7d,~0x07,
                      ~0x7f,~0x6f,~0x77,~0x7c,~0x39,~0x5e,~0x79,~0x71};
uchar keyvalue,keypressed,keyflag;

void delay(void)
{
    uint tmp;
    uchar i;
    
    for(i = 7; i > 0; i--)
    {
        for(tmp = 12000;tmp > 0;tmp--);
    }
}
void keyscan()
{
  uchar temp1,temp2,i,j;
  temp1=0x80;
  for(i=0;i<4;i++)
  {
    P1OUT=0XF0;
    P1OUT-=temp1;
    temp1>>=1;
    if((P1IN & 0X0F)!=0X0F)
    {
      temp2=0x01;
      for(j=3;j>=0;j--)
      {
        if((P1IN & temp2)==0x00)
        {
           keyvalue=4*i+j;
           return;
        }
        temp2<<=1;
      }
    }
  }
}
void keyevent()
{
  uchar temp=P1IN&0x0f;
  P1OUT=0x00;
  if((keypressed==0)&&(temp!=0x0f))
  {
    keypressed=1;
    keyscan();
  }
  else if((keypressed==1)&&(temp==0x0f))
  {
    keypressed=0;
    keyflag=1;
  }
  
}
void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
 
 
  P1DIR=0XF0;
  P1IE=0X0F;
  P1IES=0X0F;
 // P1IFG=0X00;
//  P1OUT = 0xff;
  P3DIR=0XFF;
  _EINT();
  keypressed=0;
  keyvalue=0;
  keyflag=0;
  while(1)
  {
   
   // keyvalue=3;
    P3OUT=tabel1[keyvalue];
    LPM3;
  }
 
}
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
 
  P1IE=0X00;
  /*         四键的
  if(P1IFG & 0x0f)
    {
        if(keyin == 0x0e)   //如果是第一个按键被按下
        {          
            if(keyin == 0x0e)
            {
                while(keyin != 0x0f);       //等待按键放开             
                keyvalue=1;               
            }
        }
        if(keyin == 0x0d)   //如果是第二个按键被按下
        {          
            if(keyin == 0x0d)
            {
                while(keyin != 0x0f);       //等待按键放开                                         
                keyvalue=2;            
            }
        }
        if(keyin == 0x0b)   //如果是第三个按键被按下
        {        
            if(keyin == 0x0b)
            {
                while(keyin != 0x0f);       //等待按键放开                                        
                keyvalue=3;                      
            }
        }
        if(keyin == 0x07)   //如果是第四个按键被按下
        {        
            if(keyin == 0x07)
            {
                while(keyin != 0x0f);       //等待按键放开                       
                keyvalue=4;                                   
            }
        }             
    }
  */
  if(P1IFG & 0X0F)
  {
  keyevent();
  }
  P1IFG = 0x00;
  P1IE=0X0F;
  LPM3_EXIT;
}

