

#ifndef WORK_HW_MODULE_H
#define WORK_HW_MODULE_H

enum __CAR_CMD;
enum __BEEP_CMD;

typedef enum __CAR_CMD  CAR_CMD;
typedef enum __BEEP_CMD BEEP_CMD;


// 控制小车行动
void module_car_cmd(CAR_CMD cmd);

// 控制蜂鸣器
void module_beep_cmd(BEEP_CMD cmd);

// 小车跟随
void module_car_follow();

// 小车循迹 --红外
void module_car_ir_track();

// 小车避障 --红外
void module_car_ir_avoid();

// 小车避障 --超声波
void module_car_uw_avoid();

// 数码管显示
void module_led_display();

//用户信息发送
void module_send_info();

// 小车光感
void module_car_light();




#endif //WORK_HW_MODULE_H
