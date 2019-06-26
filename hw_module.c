
#include <8052.h>
#include <string.h>

#include "data_def.h"
#include "sw_logic.h"
#include "hw_module.h"

extern unsigned int   time_count;           //用于存放定时器时间
extern bool           send_finish;          //发送完毕

void module_car_cmd(CAR_CMD cmd)
{
    switch(cmd)
    {
        case FORWARD:
            MODULE_LEFT1_FORWARD=1;//左电机正转
            MODULE_LEFT1_RETREAT=0;
            MODULE_RIGH1_FORWARD=1;//右电机正转
            MODULE_RIGH1_RETREAT=0;
            MODULE_RIGH2_RETREAT=0；
            MODULE_RIGH2_FORWARD=1；
            MODULE_LEFT2_FORWARD=1；
            MODULE_LEFT2_RETREAT=0；
            break;
        case RETREAT:
            MODULE_LEFT1_FORWARD=0;
            MODULE_LEFT1_RETREAT=1;//左电机反转
            MODULE_RIGH1_FORWARD=0;
            MODULE_RIGH1_RETREAT=1;//右电机反转
            MODULE_RIGH2_RETREAT=1；
            MODULE_RIGH2_FORWARD=0；
            MODULE_LEFT2_FORWARD=0；
            MODULE_LEFT2_RETREAT=1；
            break;
        case LEFT:
            MODULE_LEFT1_FORWARD=0;
            MODULE_LEFT1_RETREAT=0;
            MODULE_RIGH1_FORWARD=1;//右电机正转
            MODULE_RIGH1_RETREAT=0;
            MODULE_RIGH2_RETREAT=0；
            MODULE_RIGH2_FORWARD=1；
            MODULE_LEFT2_FORWARD=1；
            MODULE_LEFT2_RETREAT=0；
            break;
        case RIGH:
            MODULE_LEFT1_FORWARD=1;//左电机正转
            MODULE_LEFT1_RETREAT=0;
            MODULE_RIGH1_FORWARD=0;
            MODULE_RIGH1_RETREAT=0;
            MODULE_RIGH2_RETREAT=0;
            MODULE_RIGH2_FORWARD=1;
            MODULE_LEFT2_FORWARD=1;
            MODULE_LEFT2_RETREAT=0;
            break;
        case STOP:
        default:
            MODULE_LEFT1_FORWARD=0;
            MODULE_LEFT1_RETREAT=0;
            MODULE_RIGH1_FORWARD=0;
            MODULE_RIGH1_RETREAT=0;
            MODULE_RIGH2_RETREAT=0;
            MODULE_RIGH2_FORWARD=0;
            MODULE_LEFT2_FORWARD=0;
            MODULE_LEFT2_RETREAT=0;
    }
}


void module_beep_cmd(BEEP_CMD cmd)
{
    switch(cmd)
    {
        case BEEP_ON:
            MODULE_BEEP=0;
            break;
        case BEEP_OFF:
            MODULE_BEEP=1;
            break;
        default:
            MODULE_BEEP=1;
    }
}


void module_car_follow()
{
    //有信号为0  没有信号为1
    if(MODULE_TURN_LEFT==0 && MODULE_TURN_RIGH==0)
    {
        //前方有障碍 调用小车前进
        module_car_cmd(FORWARD);
    }
    if(MODULE_TURN_LEFT==0 && MODULE_TURN_RIGH==1)
    {
        //障碍在左边 调用小车左转
        module_car_cmd(LEFT);
    }
    if(MODULE_TURN_LEFT==1 && MODULE_TURN_RIGH==0)
    {
        //障碍在右边 调用小车右转
        module_car_cmd(RIGH);
    }
    if(MODULE_TURN_LEFT==1 && MODULE_TURN_RIGH==1)
    {
        //没有检测到障碍 调用小车停止
        module_car_cmd(STOP);
    }
}

void module_car_ir_track()
{
    //有信号为0  没有信号为1
    if(MODULE_TRACK_LEFT==0 && MODULE_TRACK_RIGH==0)
    {
        //两边检测到黑线 调用小车前进
        module_car_cmd(FORWARD);
    }
    if(MODULE_TRACK_LEFT==1 && MODULE_TRACK_RIGH==0)
    {
        //右边检测到黑线 调用小车左转
        module_car_cmd(LEFT);
    }
    if(MODULE_TRACK_LEFT==0 && MODULE_TRACK_RIGH==1)
    {
        //左边检测到黑线 调用小车右转
        module_car_cmd(RIGH);
    }
    if(MODULE_TRACK_RIGH==1 && MODULE_TRACK_LEFT==1)
    {
        //两边都没有黑线 调用小车停止
        module_car_cmd(STOP);
    }
}

void module_car_ir_avoid()
{
    //有信号为0  没有信号为1
    if(MODULE_TURN_LEFT==1 && MODULE_TURN_RIGH==1)
    {
        //前方没有障碍物 调用小车前进
        module_car_cmd(FORWARD);
    }
    if(MODULE_TURN_LEFT==1 && MODULE_TURN_RIGH==0)
    {
        //右边有障碍物 调用小车左转
        module_car_cmd(LEFT);
    }
    if(MODULE_TURN_LEFT==0 && MODULE_TURN_RIGH==1)
    {
        //左边有障碍物 调用小车右转
        module_car_cmd(RIGH);
    }
    if(MODULE_TURN_LEFT==0 && MODULE_TURN_RIGH==0)
    {
        //前方有障碍物 调用小车停止
        module_car_cmd(STOP);
    }
}

void module_car_uw_avoid()
{

    unsigned int S_temp = 0;
    if(timer<400)   //0.1s
    {
        return;
    }
    timer = 0;

    //启动检测
    MODULE_TRIG = 1;			                 //启动一次模块
    logic_delay(1);
    MODULE_TRIG = 0;

    while(!MODULE_ECHO);
        TR0 = 1;								     //开启计数
    while(MODULE_ECHO);		  	                     //当RX为1计数并等待
        TR0 = 0;								     //关闭计数

    time_count = TH0*256+TL0;
    TH0  = 0;
    TL0  = 0;

    distance = time_count*0.17;          //time计算的是从超声波发射到反射接收的双路程，将计算的结果除以2才是实际的路程

    disbuff[3]=distance/1000;
    disbuff[2]=distance/100%10;
    disbuff[1]=distance/10%10;
    disbuff[0]=distance%10;

    S_temp = disbuff[3]*100+disbuff[2]*10+disbuff[1];

    if((S_temp>=40))		          //距离大于，40CM往前走
    {
        module_beep_cmd(BEEP_OFF);
        module_car_cmd(FORWARD);
    }
    else if(S_temp<40)
    {
        module_beep_cmd(BEEP_ON);

        module_car_cmd(STOP);
        logic_delayt(10,50);
        module_beep_cmd(BEEP_OFF);
        module_car_cmd(LEFT);
        logic_delayt(2,20);
    }


}


void module_led_display()
{
    int  i;
    //            8    7     6    5
    int  num[4]={0x7f,0xbf,0xdf,0xef};

    for(i=0;i<4;i++)
    {
        P0=sz[disbuff[3-i]];	//数字8
        DU=1;
        DU=0;
        P0=num[i];
        WE=1;
        WE=0;
        P0=0xff;
        WE=1;
        WE=0;
    }
}


void module_send_info()
{
    const char *info     = "blaise 15110100107";

    while(*info!='\0')
    {
        if(send_finish==0)
        {
            send_finish=1;
            SBUF=*info;
            info++;
        }
    }

}

void module_car_light()
{
    if(LIGHT)
        module_car_cmd(STOP);

}

