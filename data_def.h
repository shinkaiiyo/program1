
#ifndef WORK_HW_DATA_H
#define WORK_HW_DATA_H

#include <8052.h>


//小车前方 红外避障 / 红外跟随
#define  MODULE_TURN_LEFT     P3_4
#define  MODULE_TURN_RIGH     P3_5


//小车底部红外循迹
#define  MODULE_TRACK_LEFT    P3_3
#define  MODULE_TRACK_RIGH    P3_2


//小车超声波避障
#define  MODULE_ECHO          P2_0         //回声接收端口
#define  MODULE_TRIG          P2_1         //超声触发端口


//小车电机
#define  MODULE_LEFT1_FORWARD P1_4         //左1电机正转
#define  MODULE_LEFT1_RETREAT P1_5         //左1电机反转
#define  MODULE_RIGH1_FORWARD P1_0         //右1电机正转
#define  MODULE_RIGH1_RETREAT P1_1         //右1电机反转
#define  MODULE_RIGH2_RETREAT P1_2         //右2电机反转
#define  MODULE_RIGH2_FORWARD P1_3         //右2电机正转
#define  MODULE_LEFT2_FORWARD P1_7         //左2电机正转
#define  MODULE_LEFT2_RETREAT P1_6         //左2电机反转

//蜂鸣器
#define  MODULE_BEEP          P2_3

//led灯
#define  DU                   P2_6
#define  WE                   P2_7

//i2c
#define  SCL                  P2_1         //I2C  时钟
#define  SDA                  P2_0         //I2C  数据

//PCF8591 地址
#define  ADDR_RW              0x90

//光敏电阻
#define  LIGHT                P2_4


//定义bool类型
typedef  __bit bool;


//定义小车控制参数
enum  __CAR_CMD
{
//    前进     后退     向左   向右  停止
    FORWARD, RETREAT, LEFT, RIGH, STOP
};


//定义蜂鸣器控制参数
enum  __BEEP_CMD
{
//  开启蜂鸣器  关闭蜂鸣器
    BEEP_ON,  BEEP_OFF
};


extern unsigned int   speed;                //小车速度

extern unsigned int   time_count;           //用于存放定时器时间
extern unsigned long  distance;             //用于存放距离的值

extern bool           send_finish;          //发送完毕
extern bool           recv_finish;          //接收完毕
extern unsigned char  recv_count;           //接收的字符数量
extern unsigned char  recv_buf[20];         //接收字符的缓冲区
extern unsigned char  cmd_argv[3][15];      //存放解析出的参数


extern unsigned char  disbuff[4];           //用于分别存放距离的值0.1mm、mm、cm和m的值

extern unsigned int   pwm;

extern unsigned int   timer;
extern unsigned int   TimeOutCounter;

extern bool           ack;                  //应答标志位
extern unsigned int   light_num;            //光感数据

extern const unsigned char sz[10];

#endif //WORK_HW_DATA_H
