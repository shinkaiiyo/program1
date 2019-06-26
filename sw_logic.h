
#ifndef WORK_SW_LOGIC_H
#define WORK_SW_LOGIC_H

// 延时指定毫秒
void logic_delay(unsigned int ms);

// 自定义延时时长
// time --延时时长  n --时长循环次数
void logic_delayt(int n,int time);

void logic_analysis_cmd(unsigned char *bcomm);

#endif //WORK_SW_LOGIC_H
