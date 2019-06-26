

#include "data_def.h"

unsigned int   speed;                    //小车速度

unsigned int   timer;


unsigned long  distance  = 0;            //用于存放距离的值
unsigned int   time_count= 0;            //用于存放定时器时间


bool           send_finish=0;            //发送完毕
bool           recv_finish=0;            //接收完毕
unsigned char  recv_count=0;             //接收的字符数量
unsigned char  recv_buf[20];             //接收字符的缓冲区
unsigned char  cmd_argv[3][15];          //存放解析出的参数


unsigned int   pwm=25;

unsigned int   TimeOutCounter=0;

unsigned char  disbuff[4]={0,0,0,0};     //用于分别存放距离的值0.1mm、mm、cm和m的值

bool           ack=0;                    //应答标志位
unsigned int   light_num=0;                //光感数据

const unsigned char sz[10]=
        {
                //   0    1    2    3   4    5    6    7    8    9
                0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
        };