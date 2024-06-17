#include "EmbSysLib.h"
#include "state.h"
#include "Module/Rtos/Rtos.h"
#include "ReportHandler.h"
#include "bandCounter.h"
#include "pressureControl.h"

using namespace EmbSysLib::Hw;
using namespace EmbSysLib::Dev;
using namespace EmbSysLib::Ctrl;
using namespace EmbSysLib::Mod;

State *zustand;
extern myBandCounter bandCounter;
extern myPressureControl pressureControl;
extern myTimerTask timerTask;

extern AnalogInAdc Signal_Farbe;
extern AnalogInAdc Signal_Druck;

extern Digital led0;
extern Digital btnA;
extern Digital PC0;
extern Digital PC1;
extern Digital PC6;
extern Digital PC7;
extern Digital rotA;
extern Digital rotB;
extern Digital rotCtrl;
extern Digital Motor_Band;
extern Digital Ventil_Stapel;
extern Digital Ventil_Ausw;
extern Digital Ventil_Verarb;
extern Digital Motor_Pumpe;
extern Digital Light_Stapel;
extern Digital Light_Verarb;
extern Digital Inkremental_Band;

Manual manual();
StapelDetect stapelDetect();
CLRDetect clrDetect();
Red red();
Blue blue();
BluePass bluePass();
White white();
Error error();
Finish finish();

zustand = manual;

class Manual: public State {
public:
	bool satisfied() {
		return (btnA.getEvent() == Digital::ACTIVATED);
	}

	void transition() {
		Ventil_Verarb.set(0);
		Ventil_Ausw.set(0);
		Ventil_Stapel.set(0);
		Motor_Band.set(0);
		led0.toggle();
		bandCounter.setCounter();
		zustand = stapelDetect;
	}
	void refresh() {
		if (satisfied()) {
			transition();
		} else {
			if (PC0.getEvent() == Digital::ACTIVATED) { //MOTOR_BAND
				Motor_Band.toggle();
			} else if (PC1.getEvent() == Digital::ACTIVATED) { //STEMPEL
				Ventil_Verarb.set(1);
				timerTask.delay(350);
				Ventil_Verarb.set(0);
			} else if (PC6.getEvent() == Digital::ACTIVATED) { //AUSWAHL
				Ventil_Ausw.set(1);
				timerTask.delay(350);
				Ventil_Ausw.set(0);
			} else if (PC7.getEvent() == Digital::ACTIVATED) { //STAPEL
				Ventil_Stapel.set(1);
				timerTask.delay(350);
				Ventil_Stapel.set(0);
			}
		}
	}
};

class StapelDetect: public State {
public:
	bool satisfied() {
		return (Light_Stapel.get() == 1);
	}

	bool altSatisfied() {
		return (btnA.getEvent() == Digital::ACTIVATED);
	}

	void transition() {
		Ventil_Stapel.set(1);
		timerTask.delay(350);
		Ventil_Stapel.set(0);
		timerTask.delay(300);
		zustand = clrDetect;
	}

	void altTransition() {
		Ventil_Verarb.set(0);
		Ventil_Ausw.set(0);
		Ventil_Stapel.set(0);
		Motor_Band.set(0);
		led0.toggle();
		bandCounter.setCounter();
		zustand = manual;

	}

	void refresh() {
		if (satisfied()) {
			transition();
		} else if (altSatisfied()) {
			altTransition();
		}
	}
};

class CLRDetect: public State {
public:
	bool satisfied() {
		return false;
	}

	bool satisfied_red(int clr) {
		return (clr >= 10000 and clr <= 15000);
	}

	bool satisfied_blue(int clr) {
		return;
	}

	bool satisfied_white(int clr) {
		return (clr >= 35000 and clr <= 40000);
	}

	bool satisfied_error(int clr) {
		return (clr >= 62000);
	}

	void transition_red() {
		transition();
		zustand = red;
	}

	void transition_blue() {
		transition();
		zustand = blue;
	}

	void transition_white() {
		transition();
		zustand = white;
	}

	void transition_error() {
		transition();
		zustand = error;
	}

	void transition() {
		bandCounter.setCounter();
		Motor_Band.set(1);
	}

	void refresh() {
		int current_clr = Signal_Farbe.getRaw();
		if (satisfied_red(current_clr)) {
			transition_red();
		} else if (satisfied_white(current_clr)) {
			transition_white();
		} else if (satisfied_blue(current_clr)) {
			transition_blue();
		} else if (satisfied_error(current_clr)) {
			transition_error();
		}
	}
};

class Red: public State {
public:

	bool satisfied() {
		return (bandCounter.getCounter() == 15);
	}

	void transition() {
		Motor_Band.set(0);
		Ventil_Ausw.set(1);
		timerTask.delay(350);
		Ventil_Ausw.set(0);
		zustand = finish;
	}
};

class White: public State {
public:

	bool satisfied() {
		return (bandCounter.getCounter() == 37);
	}

	void transition() {
		zustand = finish;
	}
};

class Blue: public State {
public:

	bool satisfied() {
		return (bandCounter.getCounter() == 30);
	}

	void transition() {
		Motor_Band.set(0);
		Ventil_Verarb.set(1);
		timerTask.delay(350);
		Ventil_Verarb.set(0);
		timerTask.delay(400);
		Motor_Band.set(1);
		zustand = bluePass;
	}
	void refresh() {
		if (satisfied()) {
			transition();
		}
	}
};

class BluePass: public State {
public:

	bool satisfied() {
		return (bandCounter.getCounter() == 37);
	}

	void transition() {

	}
};

class Error: public State {
public:

	bool satisfied() {
		return;
	}

	void transition() {

	}
	void refresh() {
		if (satisfied()) {
			transition();
		}
	}
};

class : public State {
public:

	bool satisfied() {
		return (bandCounter.getCounter() == 45);
	}

	void transition() {

	}

};

class Finish: public State {
public:

	bool satisfied() {
		return true;
	}

	void transition() {
		Ventil_Verarb.set(0);
		Ventil_Ausw.set(0);
		Ventil_Stapel.set(0);
		Motor_Band.set(0);
	}
};
