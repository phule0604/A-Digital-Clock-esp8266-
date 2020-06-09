
#include <Arduino.h> 	
#include "readbutton.h"
#include <LiquidCrystal_I2C.h>
#include <wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int mode = 0;
int k=0;
//ibutton
int count = 0, count1 = 0, count2 = 0, count3 = 0,tick=0,s = 0,mint = 0;
int ibuttonread1, ibuttonread2;
int ibutton, ibuttonpressed1s, ibuttonpressed3s;
bool iflag1s = 0;
bool iflag3s = 0;
enum { STATE1, STATE2, STATE3, STATE4 } i_FSM;
enum { STATE5, STATE6, STATE7, STATE8 } d_FSM;
enum { NORM, HR, MIN, SEC, SW} FSM_dclock;
int time_s = 0 , time_min = 0 , time_hr = 0;
int ticks=0;
//dbutton
int count5 = 0, count6 = 0, count7 = 0, count8 = 0;
int dbuttonread1, dbuttonread2;
int dbutton, dbuttonpressed1s, dbuttonpressed3s;
bool dflag1s = 0;
bool dflag3s = 0;
//read i_button
void set_lcd(){
	Wire.begin(5,4);
	lcd.begin(16,2);
	lcd.init();
	lcd.backlight();
}

void Read_i_button(const int button) {
  ibuttonread1 = ibuttonread2;
  ibuttonread2 = digitalRead(button);
  //Serial.printf("secondread = %d\n", ibuttonread2);
  if (ibuttonread2 == ibuttonread1) {
    if (!ibuttonread1) {
      ibutton = 1;
      //	Serial.printf("ibutton = %d\n", ibutton);
      count1++;
      //	Serial.printf("count1 = %d\n", count1);
      if (count1 >= 300) {
        ibuttonpressed3s = 1;
        count3++;
        if (count3 >= 10) {
          iflag3s = true;
          count3 = 0;
        }
      }
      else if ((count1 >= 100 ) && (count1 < 300)) {
        ibuttonpressed1s = 1;
        count2++;
        if (count2 >= 50) {
          iflag1s = 1;
          count2 = 0;
        }
      }
    }
    else {
      ibutton = 0;
      ibuttonpressed1s = 0;
      count1 = 0;
      count2 = 0;
      iflag1s = 0;
      iflag3s = 0;
      ibuttonpressed3s = 0;
    }
  }
}
//read d_button
void Read_d_button(const int button) {
  dbuttonread1 = dbuttonread2;
  dbuttonread2 = digitalRead(button);
  //Serial.printf("secondread = %d\n", dbuttonread2);
  if ((dbuttonread2 == dbuttonread1)&&(ibuttonread2==ibuttonread1)&&(ibuttonread2=1)) {
    if (!dbuttonread1) {
      dbutton = 1;
      //  Serial.printf("ibutton = %d\n", ibutton);
      count5++;
      //  Serial.printf("count1 = %d\n", count1);
      if (count5 >= 300) {
        dbuttonpressed3s = 1;
        count7++;
        if (count7 >= 10) {
          dflag3s = true;
          count7 = 0;
        }
      }
      else if ((count5 >= 100 ) && (count5 < 300)) {
        dbuttonpressed1s = 1;
        count6++;
        if (count6 >= 50) {
          dflag1s = 1;
          count6 = 0;
        }
      }
    }
    else {
      dbutton = 0;
      dbuttonpressed1s = 0;
      count5 = 0;
      count6 = 0;
      dflag1s = 0;
      dflag3s = 0;
      dbuttonpressed3s = 0;
    }
  }
}
void time_count() 
	{	
		ticks++;
		if (ticks == 100) 
		{
			time_s++;
			ticks = 0;
		}
		if (time_s == 60 )
		{
			time_min++;
			time_s = 0;
		}
		if (time_min == 60)
		{
			time_hr++;
			time_min = 0;
		}
		if (time_hr == 24)
		{
			time_hr = 0;
		}
	}
void lcd_blink_hr()
	{	
		if (ticks >=50) { 	lcd.setCursor(5, 0);
								lcd.print("  ");
							}
		else { lcd.setCursor(5, 0);
				lcd.print(time_hr);
		}
		lcd.setCursor(8, 0);
		lcd.print(time_min);
		lcd.setCursor(11,0);
		lcd.print(time_s);
	}
void lcd_blink_min()
	{	
		if (ticks >=50) { 	lcd.setCursor(8, 0);
								lcd.print("  ");
							}
		else { lcd.setCursor(8, 0);
				lcd.print(time_min);
		}
		lcd.setCursor(5, 0);
		lcd.print(time_hr);
		lcd.setCursor(11,0);
		lcd.print(time_s);
	}
void lcd_blink_s()
	{	
		if (ticks >=50) { 	lcd.setCursor(11, 0);
								lcd.print("  ");
							}
		else { lcd.setCursor(11, 0);
				lcd.print(time_s);
		}
		lcd.setCursor(5, 0);
		lcd.print(time_hr);
		lcd.setCursor(8,0);
		lcd.print(time_min);
	}
void lcd_norm(){
	lcd.setCursor(5, 0);
	lcd.print(time_hr);
	lcd.setCursor(8, 0);
	lcd.print(time_min);
	lcd.setCursor(11,0);
	lcd.print(time_s);
}
void FSM_increase() {
  switch (i_FSM) {
    case STATE1:
      if (ibutton == 1) {
        mode++;
        //Serial.printf("count = %d\n", count);
        i_FSM = STATE2;
      }
      break;
    case STATE2:
      if (ibutton == 0) i_FSM = STATE1;
      else if (ibuttonpressed1s) i_FSM = STATE3;
      break;
    case STATE3:
      if (iflag1s) {
        mode++;
        iflag1s = 0;
      //  Serial.printf("count = %d\n", count);
      }
      if (ibuttonpressed3s) i_FSM = STATE4;
      if (ibutton == 0) {
        i_FSM = STATE1;
      }
      break;
    case STATE4:
      if (iflag3s) {
        mode++;
        iflag3s = 0;
      //  Serial.printf("count = %d\n", count);
      }
      if (ibutton == 0) {
        i_FSM = STATE1;
      }
      break;
    default:
      break;
  }
}
void stop_watch(){
	if ((k==4)&&(dbutton==1)) {
	tick++;
	if (tick==100) {s++;tick=0;};
	if (s==60) { mint++; s=0;};
	}
	else {tick = 00; s=00; mint=00;}; 
	
}
void stop_watch_lcd(){
	lcd.setCursor(5, 1);
	lcd.print(mint);
	lcd.setCursor(8, 1);
	if (s > 0) lcd.print(s);
		else lcd.print("0 ");
	lcd.setCursor(11,1);
	if (tick > 0 ) 
			lcd.print(tick);
		else 
			lcd.print("0 ");
	
}
void FSM_inc() {
  switch (d_FSM) {
    case STATE5:
      if (dbutton == 1) {
        if (k==1) time_hr++;
			else if (k==2) time_min++;
				else if (k==3) time_s++;
					else break;
				}
        d_FSM = STATE6;
      break;
    case STATE6:
      if (dbutton == 0) d_FSM = STATE5;
      else if (dbuttonpressed1s) d_FSM = STATE7;
      break;
    case STATE7:
      if (dflag1s) {
        if (k==1) time_hr++;
			else if (k==2) time_min++;
				else if (k==3) time_s++;
					else break;
        dflag1s = 0;
      }
      if (dbuttonpressed3s) d_FSM = STATE8;
      if (dbutton == 0) {
        d_FSM = STATE5;
      }
      break;
    case STATE8:
      if (dflag3s) {
        if (k==1) time_hr++;
			else if (k==2) time_min++;
				else if (k==3) time_s++;
					else break;
        dflag3s = 0;
      }
      if (dbutton == 0) {
        d_FSM = STATE5;
      }
		break;
    default:
      break;
   }
  }

void dclock(){
	//Serial.printf("mode = %d\n", mode);
	k = mode %5;
	switch(FSM_dclock){
		case NORM :
		if (k == 0) lcd_norm();
		else  FSM_dclock = HR;
		break;
		
		case HR :
		if (k ==1 ) lcd_blink_hr(); 
					
		else FSM_dclock=MIN;
		break;
		
		case MIN :
		if (k ==2  ) lcd_blink_min(); 
						
		else FSM_dclock=SEC;
		break;
		
		case SEC :
		if (k == 3 ) lcd_blink_s(); 
		else FSM_dclock=SW;
		break;
		
		case SW :
		if(k == 4 ) { 	lcd_norm();
						lcd.setCursor(0,1);
						lcd.print("SW");
		}
		else { lcd.setCursor(0,1);
				lcd.print("  ");
				FSM_dclock=NORM;
		}
		break;
		default : break;
	}
}

