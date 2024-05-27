//*******************************************************************
#include "EmbSysLib.h"
#include "Module/Rtos/Rtos.h"
#include "ReportHandler.h"
#include "config.h"
#include ".\Bargraf.h"
#include <stdio.h>
#include<chrono>
#include<thread>

//*******************************************************************
class myTimerTask: public TaskManager::Task {
public:
	//---------------------------------------------------------------
	myTimerTask(TaskManager &taskManager) {
		cnt = 0;
		taskManager.add(this);
	}

	//---------------------------------------------------------------
	virtual void update(void) {
		cnt++;
	}
	void delay(uint32_t millis) {
		uint32_t cntinitial = cnt;
		uint32_t diff = (uint32_t) millis / 10;
		while (cnt - cntinitial < diff) {
		}
	}
	//---------------------------------------------------------------
	DWORD cnt;
};

//*******************************************************************
class myRtosTask: public Rtos::Task {
public:
	//---------------------------------------------------------------
	myRtosTask(Rtos &rtos) :
			Rtos::Task(rtos, 500/* stack size*/) {
		cnt = 0;
	}

private:
	//---------------------------------------------------------------
	virtual void update(void) {
		while (1) {
			cnt++;
			pause();  // pause the task until next time slot
		}
	}

public:
	//---------------------------------------------------------------
	DWORD cnt;

};
//class myTask

//*******************************************************************
Rtos rtos(2,   // max num of tasks
		1000); // time slice in us

//*******************************************************************
int main(void) {
	disp.printf(0, 0, __DATE__ " " __TIME__);
	terminal.printf( __DATE__ " " __TIME__ "\r\n");

	int num = 0;

	myTimerTask timerTask(taskManager);

	myRtosTask rtosTask(rtos);

	rtosTask.start();

	int state = 0;
	bool enough_pressure = false;

	int last_band = -1;
	int band_counter = -1;

	std::string top = "NO JOB";

	while (1) {
		/*
		 if( char *str = terminal.getString() )
		 {
		 terminal.printf( "\r\n=>%s\r\n", str );
		 }
		 */

		switch (enc.getEvent()) {
		case DigitalEncoder::LEFT:
			num -= 1;
			break;
		case DigitalEncoder::RIGHT:
			num += 1;
			break;
		case DigitalEncoder::CTRL_DWN:
			num = 0;
			break;
		default:
			break;
		}

		int new_band = Inkremental_Band.get();
		if (new_band != last_band) {
			band_counter++;
			last_band = new_band;
		}

		int pressure = Signal_Druck.getRaw();
		if (pressure < 18000) {
			enough_pressure = false;
			Motor_Pumpe.set(1);
		} else if (pressure > 20000) {
			enough_pressure = true;
			Motor_Pumpe.set(0);
		}

		int clr = Signal_Farbe.getRaw();

		if (state == 0 and enough_pressure and Light_Stapel.get() == 1) { // NO JOB
			state = 10;
			Ventil_Stapel.set(1);
			timerTask.delay(350);
			Ventil_Stapel.set(0);
			timerTask.delay(300);
		} else if (state == 1) { //FINISH JOB
			Ventil_Verarb.set(0);
			Ventil_Ausw.set(0);
			Ventil_Stapel.set(0);
			Motor_Band.set(0);
			top = "NO JOB";
			state = 0;
		} else if (state == 2 and band_counter == 45) { //FALSE
			state = 1;
		} else if (state == 10) { //CHECK COLOUR
			if (clr >= 10000 and clr <= 15000) { //RED
				top = "RED";
				state = 11;
			} else if (clr >= 35000 and clr <= 40000) { //WHITE/BROWN
				top = "WHITE/BROWN";
				state = 21;
			} else if (clr >= 58000 and clr <= 61500) { //BLUE
				top = "BLUE";
				state = 31;
			} else if (clr >= 62000) { //FALSE
				top = "ERROR";
				state = 2;
			}
			band_counter = 0;
			Motor_Band.set(1);

		} else if (state == 11 and band_counter == 15) {
			Motor_Band.set(0);
			Ventil_Ausw.set(1);
			timerTask.delay(350);
			Ventil_Ausw.set(0);
			state = 1;
		} else if (state == 21 and band_counter == 37) {
			state = 1;
		} else if (state == 31 and band_counter == 30) {
			Motor_Band.set(0);
			Ventil_Verarb.set(1);
			timerTask.delay(350);
			Ventil_Verarb.set(0);
			timerTask.delay(400);
			Motor_Band.set(1);

			state = 32;
		} else if (state == 32 and band_counter == 37) {
			Motor_Band.set(0);
			state = 1;
		}

		if (state == 0 and btnA.getEvent() == Digital::ACTIVATED) {
			led0.toggle();
			Motor_Pumpe.toggle();
		}
		/*
		 if (state == 0 and PC0.getEvent() == Digital::ACTIVATED) {
		 Motor_Pumpe.set(1);
		 timerTask.delay(10000);
		 Motor_Pumpe.set(0);
		 }
		 if (state == 0 and PC1.getEvent() == Digital::ACTIVATED) {
		 Ventil_Verarb.set(1);
		 timerTask.delay(350);
		 Ventil_Verarb.set(0);
		 }
		 if (state == 0 and PC6.getEvent() == Digital::ACTIVATED) {
		 Ventil_Ausw.set(1);
		 timerTask.delay(350);
		 Ventil_Ausw.set(0);
		 }
		 if (state == 0 and PC7.getEvent() == Digital::ACTIVATED) {
		 Ventil_Stapel.set(1);
		 timerTask.delay(350);
		 Ventil_Stapel.set(0);
		 }
		 */

		//System::delayMilliSec(1000);
		//b.draw(num);
		disp.printf(0,0,"%-20s", top.c_str());
		disp.printf(1, 0, "clr:%-5d", Signal_Farbe.getRaw());
		disp.printf(1, 10, "drk:%-5d", Signal_Druck.getRaw());
		disp.printf(2, 0, "bndcnt:%-5d ", band_counter);
		disp.printf(2, 11, "vligh:%-5d ", Light_Verarb.get());
		disp.printf(3, 0, "timer:%-5d 	", timerTask.cnt);
		disp.printf(3, 13, "st:%-5d ", state);
		disp.refresh();
		//disp.printf(1,0,"Bargrafs:%-5d",b.getAmount());
		//disp.refresh();
		/*
		 disp.printf( 1, 0, "timer:%-5d ", timerTask.cnt );
		 disp.printf( 2, 0, "rtos: %-5d ", rtosTask.cnt  );
		 disp.printf( 3, 0, "num:  %-5d ", num           );
		 disp.refresh();
		 */
	}
}
//EOF
