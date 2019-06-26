
#include <8052.h>

#include "data_def.h"
#include "ir_and_init.h"

extern bool           send_finish;          //发送完毕
extern unsigned char  recv_count;
extern unsigned char  recv_buf[20];
extern unsigned char  cmd_argv[3][15];



void uart_serial() __interrupt 4
{
    unsigned char temp;

    if(TI == 1)
    {
        send_finish=0;
        TI=0;
        return;
    }

    RI=0;
    temp=SBUF;
    if(recv_count==0)
    {
        if(temp=='*')
        {
            recv_buf[recv_count++]=temp;
            //SBUF=temp;
        }
    }
    else
    {
        recv_buf[recv_count++]=temp;
        //SBUF=temp;
        if(temp=='!')
        {
            recv_count=0;
            recv_finish=1;
        }
    }
}


void timer1() __interrupt 3
{
    TH1=0xFF;
    TL1=0x1A;
    TimeOutCounter++;
    timer++;
    if(TimeOutCounter <=pwm)
    {
        EN1=1;
        EN2=1;
    }
    else if(TimeOutCounter >pwm)
    {
        EN1=0;
        EN2=0;
    }
    if(TimeOutCounter>80)
    {
        TimeOutCounter=0;
    }
}

void timer_init()
{
    TMOD = TMOD|0x11;
    TH0  = 0;
    TL0  = 0;
    ET0  = 0;
    TH1  = 0xfc;
    TL1  = 0x66;
    ET1  = 1;
    TR1  = 1;
    EA   = 1;
}


void uart_init()
{
    SCON   = 0x50;
    RCAP2H = (65536-36)/256;//36:9600 3:115200
    RCAP2L = (65536-36)%256;
    TH2    = RCAP2H;
    TL2    = RCAP2L;
    T2CON  = 0X34;
    PS     = 1;
    EA     = 1;
    ES     = 1;
}