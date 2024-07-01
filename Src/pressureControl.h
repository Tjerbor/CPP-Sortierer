#pragma once
#include "EmbSysLib.h"
#include "Module/Rtos/Rtos.h"

using namespace EmbSysLib::Hw;
using namespace EmbSysLib::Dev;
using namespace EmbSysLib::Ctrl;
using namespace EmbSysLib::Mod;

extern AnalogInAdc Signal_Druck;
extern Digital Motor_Pumpe;

class myPressureControl: public TaskManager::Task {
private:
	int pressure = -1;
public:
	//---------------------------------------------------------------
	myPressureControl(TaskManager &taskManager) {
		taskManager.add(this);
	}


	//Duck wird ins Intervall reguliert.
	virtual void update(void) {
		pressure = Signal_Druck.getRaw(); //AUTOMATIC PRESSURE CONTROL
		if (pressure < 18000) {
			Motor_Pumpe.set(1);
		} else if (pressure > 20000) {
			Motor_Pumpe.set(0);
		}
	}

	int getPressure() {
		return pressure;
	}
};
