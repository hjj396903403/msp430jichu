
//                        _ooOoo_
//                       o8888888o
//                       88" . "88
//                       (| -_- |)
//                       O\  =  /O
//                    ____/`---'\____
//                  .'  \\|     |//  `.
//                 /  \\|||  :  |||//  \
//                /  _||||| -:- |||||-  \
//                |   | \\\  -  /// |   |
//                | \_|  ''\---/''  |   |
//                \  .-\__  `-`  ___/-. /
//              ___`. .'  /--.--\  `. . __
//           ."" '<  `.___\_<|>_/___.'  >'"".
//          | | :  `_ \`.;`\ _ /`;.`/ - `.: | |
//          \  \ `-.   \_ __\ /__ _/   .-` /  /
//        ===`-.____`-.___\_____/___.-`____.-'===
//                        `=---='
//        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^	
//               ·ð×æ±£ÓÓ         ÓÀÎÞBUG					


#include <msp430x14x.h>
#define uchar unsigned char
#define uint unsigned int
#define keyin (P1IN & 0x0f)
uchar tabel1[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                      0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar tabel2[]={0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70};
void delay(uint a)
{
   uchar i;
   for(;a>0;a--)
     for(i=19;i>0;i--);
}
void  main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  uchar key,keyvalue,i;
  P2DIR=0XFF;
  P1DIR=0X00;
  P3DIR=0XFF;
  
  
/* 
  while(1)
  {
     P2OUT=keyin;
  }
*/
  while(1)
  {
    if(keyin != 0x0f)
    {
        delay(10);
        if(keyin != 0x0f)
        {
            key=keyin;
            switch(key)
            {
              case(0x0e):keyvalue=1;break;
              case(0x0d):keyvalue=2;break;
              case(0x0b):keyvalue=3;break;
              case(0x07):keyvalue=4;break;
                 default:keyvalue=0;break;
            }
        }
    }
    for(i=0;i<4;i++)
    {
      P2OUT=tabel1[keyvalue];
      P3OUT=tabel2[i];
      delay(10);
    }
  }
}
