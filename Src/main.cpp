//*******************************************************************
#include "EmbSysLib.h"
#include "Module/Rtos/Rtos.h"
#include "ReportHandler.h"
#include "config.h"
#include "state.h"
#include "bandCounter.h"
#include "pressureControl.h"
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

//*******************************************************************


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

myBandCounter bandCounter(taskManager);
myPressureControl pressureControl(taskManager);
myTimerTask timerTask(taskManager);

extern State *zustand;

int main(void) {
	disp.printf(0, 0, __DATE__ " " __TIME__);
	terminal.printf( __DATE__ " " __TIME__ "\r\n");

	int num = 0;

	myRtosTask rtosTask(rtos);

	rtosTask.start();

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

		zustand->refresh();

		/*if (mode) {
		 disp.printf(0, 0, "MODE:AUTOMATIC      ");
		 disp.printf(1, 0, "%-20s", job.c_str());
		 }
		 */

	}
}
//EOF
