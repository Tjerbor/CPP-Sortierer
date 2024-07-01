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

//Anzahl verarbeiteter Pellets
private:
	inline static int red_counter;
	inline static int white_counter;
	inline static int blue_counter;
	//Undefinierte Farbe
	inline static int error_counter;

// =red_counter++
protected:
	void countRed();
	void countWhite();
	void countBlue();
	void countError();

public:
	//Prueft Uebergangsbedingung und gibt ID fuer naechsten Zustand zureuck
	virtual int satisfied() = 0;
	//Aktion beim Zustandswechsel fuer entsprechendes Ziel
	virtual void transition(int destination) = 0;


	//Displayausgabe
	virtual void display() {
		disp.printf(0, 0, "MODE:Automatic      ");
		disp.printf(2, 0, "clr:%-5d", Signal_Farbe.getRaw());
		disp.printf(2, 10, "drk:%-5d", pressureControl.getPressure());
		disp.printf(3, 0, "R:%-2d ", red_counter);
		disp.printf(3, 5, "W:%-2d ", white_counter);
		disp.printf(3, 10, "B:%-2d ", blue_counter);
		disp.printf(3, 15, "E:%-2d ", error_counter);
	}
};

//ID = 0
class Manual: public State {
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

//ID = 1
class StapelDetect: public State {
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};


//ID = 10
class CLRDetect: public State {
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};


//ID = 20
class Red: public State {
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

//ID = 30
class White: public State {
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

//ID = 40
class Blue: public State {
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

//ID = 41
class BluePass: public State {
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

//ID = -1
class Error: public State {
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};

//ID = 2
class Finish: public State {
public:
	int satisfied();
	void transition(int destination = 0);
	void display();
};
