#include "EmbSysLib.h"
#include "pressureControl.h"
#include "bandCounter.h"
#pragma once

using namespace EmbSysLib::Hw;
using namespace EmbSysLib::Dev;
using namespace EmbSysLib::Ctrl;
using namespace EmbSysLib::Mod;

extern myPressureControl pressureControl;
extern myBandCounter bandCounter;
extern AnalogInAdc Signal_Farbe;
extern AnalogInAdc Signal_Druck;

extern ScreenChar disp;

class State {
public:
	virtual int satisfied() = 0;
	virtual void transition(int destination = 0) = 0;
	virtual void display() {
		disp.printf(2, 0, "clr:%-5d", Signal_Farbe.getRaw());
		disp.printf(2, 10, "drk:%-5d", pressureControl.getPressure());
		disp.printf(3, 0, "bndcnt:%-5d ", bandCounter.getCounter());
	}
};

class Manual: public State { //0
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

class StapelDetect: public State { //1
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

class CLRDetect: public State { //10
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

class Red: public State { //20
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

class White: public State { //30
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

class Blue: public State { //40
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

class BluePass: public State { //41
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

class Error: public State { //-1
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

class Finish: public State { //2
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};
