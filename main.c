//
// Created by leaf on 17-8-31.
//

#include <8052.h>
#include <string.h>

#include "data_def.h"
#include "sw_logic.h"
#include "hw_module.h"
#include "ir_and_init.h"


extern unsigned int speed;

extern unsigned int  timer;

extern unsigned char recv_buf[20];
extern unsigned char cmd_argv[3][15];


void main()
{
	uart_init();
	timer_init();
	EN1=1;
	EN2=1;
	while(1)
	{
		if(recv_finish==1)
		{
			recv_finish=0;
            logic_analysis_cmd(recv_buf);
		}
		if(strcmp(cmd_argv[1],"control")==0)
		{
            switch(cmd_argv[2][0])
            {
                case '4':
                    logic_delay(1);module_car_cmd(RIGH);break;
                case '3':
                    logic_delay(1);module_car_cmd(LEFT);break;
                case '2':
                    module_car_cmd(RETREAT);break;
                case '1':
                    module_car_cmd(FORWARD);break;
                case '0':
                default:
                    module_car_cmd(STOP);
            }
		}
		else if(strcmp(cmd_argv[1],"speed")==0)
		{
  			speed=(cmd_argv[2][0]-48)*10+(cmd_argv[2][1]-48)*10;
  			pwm=speed;
		}
        else if(strcmp(cmd_argv[1],"info") == 0)
        {
            module_send_info();
            cmd_argv[1][0]='!';
        }
		else
        {
            if(cmd_argv[2][0]=='0')
            {
                module_car_cmd(STOP);
            }
            else if(cmd_argv[2][0]=='1')
            {
                if(strcmp(cmd_argv[1],"track")==0)
                {
                    module_car_ir_track();
                }
                else if(strcmp(cmd_argv[1],"infrared")==0)
                {
                    module_car_ir_avoid();
                }
                else if(strcmp(cmd_argv[1],"follow")==0)
                {
                    module_car_follow();
                }
                else if(strcmp(cmd_argv[1],"ultrasonic") == 0)
                {
                    module_car_uw_avoid();
                }else if(strcmp(cmd_argv[1],"light") == 0)
                {
                    module_car_light();
                    module_car_ir_avoid();
                }
            }
        }
	}
}
