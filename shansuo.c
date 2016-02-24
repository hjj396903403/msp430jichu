/***************************************************
程序功能：控制8个LED闪烁，用于测试下载功能是否正常
---------------------------------------------------
测试说明：观察LED闪烁
***************************************************/
#include  <msp430x14x.h>

/****************主函数****************/
void main(void)
{  
    /*下面六行程序关闭所有的IO口*/
//    P1DIR = 0XFF;P1OUT = 0XFF;
 //   P2DIR = 0XFF;P2OUT = 0XFF;
//    P3DIR = 0XFF;P3OUT = 0XFF;
 //   P4DIR = 0XFF;P4OUT = 0XFF;
 //   P5DIR = 0XFF;P5OUT = 0XFF;
  //  P6DIR = 0XFF;P6OUT = 0XFF;
  
    WDTCTL = WDTPW + WDTHOLD;       //关闭看门狗
    
  //  P6DIR |= BIT2;P6OUT |= BIT2;    //关闭电平转换
    CCTL0 = CCIE;                   //使能CCR0中断
    CCR0 = 2047;                    //设定周期0.5S                
    TACTL = TASSEL_1 + ID_3 + MC_1; //定时器A的时钟源选择ACLK，增计数模式
   P2DIR = 0xff;                   //设置P2口方向为输出
   P2OUT = 0xff;
 
    _EINT();                        //使能全局中断
    LPM3;                           //CPU进入LPM3模式
}

/*******************************************
函数名称：Timer_A 
功    能：定时器A的中断服务函数
参    数：无
返回值  ：无
********************************************/
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A (void)
{  
    P2OUT ^= 0xff;                  //P2口输出取反
}
