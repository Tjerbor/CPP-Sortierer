#include "EmbSysLib.h"
#include "Module/Rtos/Rtos.h"

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

	//Code Verzoegerung aber cnt bleibt intakt
	void delay(uint32_t millis) {
		uint32_t cntinitial = cnt;
		uint32_t diff = (uint32_t) millis / 10;
		while (cnt - cntinitial < diff) {
		}
	}
	//---------------------------------------------------------------
	DWORD cnt;
};
