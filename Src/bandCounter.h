#pragma once
#include "EmbSysLib.h"
#include "Module/Rtos/Rtos.h"

extern Digital Inkremental_Band;

class myBandCounter: public TaskManager::Task {
private:
	int last_band = -1;
	int band_counter = -1;
public:
	//---------------------------------------------------------------
	myBandCounter(TaskManager &taskManager) {
		taskManager.add(this);
	}

	//---------------------------------------------------------------
	virtual void update(void) {
		int new_band = Inkremental_Band.get(); //COUNTS BANDS
		if (new_band != last_band) {
			band_counter++;
			last_band = new_band;
		}
	}

	void setCounter(int count = 0) {
		band_counter = count;
	}

	int getCounter() {
		return band_counter;
	}
};
