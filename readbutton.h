// readbutton.h

#ifndef _READBUTTON_h
#define _READBUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
extern int count, count1, count2, count3,k;
extern int ibuttonread1, ibuttonread2;
extern int ibutton, ibuttonpressed1s, ibuttonpressed3s;
extern bool iflag1s ;
extern bool iflag3s ;
extern int time_s , time_min , time_hr ;
extern int ticks;
//extern enum { STATE1, STATE2, STATE3, STATE4 } i_FSM;

extern int count5, count6, count7, count8,mode,tick,s,mint;
extern int dbuttonread1, dbuttonread2;
extern int dbutton, dbuttonpressed1s, dbuttonpressed3s;
extern bool dflag1s;
extern bool dflag3s;
//extern enum { STATE5, STATE6, STATE7, STATE8 } d_FSM;

void Read_i_button(const int button);
void Read_d_button(const int button);
void dclock();
void lcd_norm();
void time_count();
void lcd_blink_hr();
void lcd_blink_min();
void lcd_blink_s();
void set_lcd();
void FSM_increase();
void FSM_inc();
void stop_watch();
void stop_watch_lcd();
#endif
