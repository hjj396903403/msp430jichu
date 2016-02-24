
#include <msp430x14x.h>
#define uint unsigned int
#define uchar unsigned char

#define DI P1OUT   //DI


//dac0832 pin define  0832�����ڵ�����ģʽ������Ĵ����ܿأ�DAC�Ĵ���ֱͨ
#define CS_SET P2OUT |= BIT6
#define CS_CLR P2OUT &= ~BIT6       //P26 CS
#define WR_SET P2OUT |= BIT7
#define WR_CLR P2OUT &= ~BIT7     //P27 WR
//1��ʱ
//#define CPU_F ((double)16000000)//cpu frequency16000000
#define CPU_F ((double)1000000)//cpu frequency1000000
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

void IO_init()
{
    P1DIR = 0xff;
    P2DIR |= BIT6+BIT7;    //��P26��P27����Ϊ��ͨIO ��Ϊ�����  Ĭ��Ϊ�����������������
    P2SEL &= ~(BIT6+BIT7);
    P2SEL &= ~(BIT6+BIT7);
 
}
void write_dac(uint data)    //dacд���ݺ���
{
 
    CS_CLR;
    DI = data;
    WR_CLR;
    delay_us(1);
    WR_SET;   //latch data
    CS_SET;
}

void main()
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  IO_init();
  
  write_dac(0xff);
  for(;;)
  {
    write_dac(0xff);
    delay_ms(1);
    write_dac(0xc0);
    delay_ms(1);
    write_dac(0x7f);
    delay_ms(1);
    write_dac(0x3f);
    delay_ms(1);
    write_dac(0x00);
    delay_ms(1);
  }
}
