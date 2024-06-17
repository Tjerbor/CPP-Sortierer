#include "EmbSysLib.h"
#include "pressureControl.h"
#include "bandCounter.h"

using namespace EmbSysLib::Hw;
using namespace EmbSysLib::Dev;
using namespace EmbSysLib::Ctrl;
using namespace EmbSysLib::Mod;

extern myPressureControl pressureControl;
extern myBandCounter bandCounter;
extern AnalogInAdc Signal_Farbe;
extern AnalogInAdc Signal_Druck;

class State {
public:
	State();
	~State();
	virtual bool satisfied() = 0;
	virtual void transition() = 0;
	void refresh() {
		if (satisfied()) {
			transition();
		}
	}
	virtual void display() {
		/*
		disp.printf(0, 0, "MODE:AUTOMATIC      ");
		disp.printf(1, 0, "%-20s", job.c_str());
		disp.printf(2, 0, "clr:%-5d", Signal_Farbe.getRaw());
		disp.printf(2, 10, "drk:%-5d", pressureControl.getPressure());
		disp.printf(3, 0, "bndcnt:%-5d ", bandCounter.getCounter());
		disp.printf(3, 13, "st:%-5d ", -1);
		disp.refresh();
		*/
	}
};
