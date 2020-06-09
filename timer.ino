#include "readbutton.h"
//#include "LiquidCrystal_I2C.h"
//#include "wire.h"
//LiquidCrystal_I2C lcd(0x27, 16, 2);
const uint8_t  i = 14;
const uint8_t  d = 12;



void ICACHE_RAM_ATTR onTimerISR() {
	Read_i_button(i);
	Read_d_button(d);
	time_count();
	stop_watch();
	timer1_write(50000);//12us
	
}
//=======================================================================
//                               Setup
//=======================================================================
void setup()
{	set_lcd();
	//lcd.setCursor(5, 0);
	//lcd.print("hello");
	Serial.begin(115200);
	Serial.println("");
	pinMode(i, INPUT);
	pinMode(d, INPUT);
	//Initialize Ticker every 0.1s
	timer1_attachInterrupt(onTimerISR);
	timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
	timer1_write(50000);
}

void loop() {
	dclock();
	FSM_increase();
	FSM_inc();
	stop_watch_lcd();
	//Read_i_button(i);
	//lcd_blink();
}
