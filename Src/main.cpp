//*******************************************************************
#include "EmbSysLib.h"
#include "Module/Rtos/Rtos.h"
#include "ReportHandler.h"
#include "config.h"
#include "stateHandler.h"
#include "bandCounter.h"
#include "pressureControl.h"
#include "timerTask.h"
#include <stdio.h>
#include<chrono>
#include<thread>

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

//----Selstdefinierte Hintergrundtasks----
//1. Task: Zaehlt die Aenderungen des Bandes -> Banddistanz
myBandCounter bandCounter(taskManager);
//2. Task: Reguliert den Pneumatikdruck automatisch im gewuenschten Intervall
myPressureControl pressureControl(taskManager);
//3: Task: Extrem genaue Verzögerung.
myTimerTask timerTask(taskManager);
//-----------------------------------------

int main(void) {
	disp.printf(0, 0, __DATE__ " " __TIME__);
	terminal.printf( __DATE__ " " __TIME__ "\r\n");

	int num = 0;
	StateHandler derEpicHandler;

	myRtosTask rtosTask(rtos);

	rtosTask.start();

	while (1) {

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

		//Startet im Manualzustand
		//Checkt nach Zustandsaenderung
		derEpicHandler.refresh();

	}
}
//EOF
