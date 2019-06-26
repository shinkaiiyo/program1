//
// Created by leaf on 17-8-31.
//

#include "data_def.h"
#include "sw_logic.h"

extern unsigned char  cmd_argv[3][15];      //存放解析出的参数

void logic_delay(unsigned int ms)
{
    char i;
    while(ms--)
    {
        for(i=112;i>0;i--);
    }
}

void logic_delayt(int n,int time)
{
    int i;
    while(n--)
    {
        for(i=time;i>0;i--);
    }
}

void logic_analysis_cmd(unsigned char *bcomm)
{
    unsigned char i=0,row=0,column=0;
    for(i=0;bcomm[i]!='\0';i++)
    {
        if(bcomm[i]!='-')
            cmd_argv[row][column++]=bcomm[i];
        else
        {
            cmd_argv[row][column++]='\0';
            column=0;
            cmd_argv[++row][column++]=bcomm[++i];
        }
    }
    bcomm[i]='\0';
}