//
// Created by leaf on 17-8-31.
//

#ifndef WORK_IR_AND_INIT_H
#define WORK_IR_AND_INIT_H


void uart_init();
void timer_init();

void timer1() __interrupt 3;

void uart_serial() __interrupt 4;

#endif //WORK_IR_AND_INIT_H
