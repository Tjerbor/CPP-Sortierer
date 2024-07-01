#include "EmbSysLib.h"
#include "state.h"
#include "Module/Rtos/Rtos.h"
#include "bandCounter.h"
#include "pressureControl.h"
#include "timerTask.h"

using namespace EmbSysLib::Hw;
using namespace EmbSysLib::Dev;
using namespace EmbSysLib::Ctrl;
using namespace EmbSysLib::Mod;

extern myBandCounter bandCounter;
extern myPressureControl pressureControl;
extern myTimerTask timerTask;

extern ScreenChar disp;

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

//*******************************************************************

void State::countRed() {
	red_counter++;
}

void State::countWhite() {
	white_counter++;
}

void State::countBlue() {
	blue_counter++;
}

void State::countError() {
	error_counter++;
}

//*******************************************************************

int Manual::satisfied() {
	if (btnA.getEvent() == Digital::ACTIVATED) {
		return 1; //StapelDetect
	} else {
		//Manuelles ansprechen der Ventile oder des Fliessbandes

		//FLIESSBAND
		if (PC0.getEvent() == Digital::ACTIVATED) {
			Motor_Band.toggle();
		}

		//STEMPEL Ventil
		else if (PC1.getEvent() == Digital::ACTIVATED) {
			Ventil_Verarb.set(1);
			timerTask.delay(350);
			Ventil_Verarb.set(0);
		}

		//AUSWAHL Ventil
		else if (PC6.getEvent() == Digital::ACTIVATED) {
			Ventil_Ausw.set(1);
			timerTask.delay(350);
			Ventil_Ausw.set(0);
		}

		//STAPEL
		else if (PC7.getEvent() == Digital::ACTIVATED) {
			Ventil_Stapel.set(1);
			timerTask.delay(350);
			Ventil_Stapel.set(0);
		}
		return 0; //Bleibt in Manual
	}
}

void Manual::transition(int destination) {
	Ventil_Verarb.set(0);
	Ventil_Ausw.set(0);
	Ventil_Stapel.set(0);
	Motor_Band.set(0);
	led0.toggle();
	bandCounter.setCounter(); //Reset
}

void Manual::display() {
	disp.printf(0, 0, "MODE:Manual         ");
	int clr = Signal_Farbe.getRaw();
	if (clr >= 10000 and clr <= 15000) { //RED
		disp.printf(1, 0, "RED                    ");
	} else if (clr >= 35000 and clr <= 40000) { //WHITE/BROWN
		disp.printf(1, 0, "WHITE/BROWN            ");
	} else if (clr >= 58000 and clr <= 61500) { //BLUE
		disp.printf(1, 0, "BLUE                   ");
	} else {
		disp.printf(1, 0, "                       ");
	}
	disp.printf(2, 0, "clr:%-5d", Signal_Farbe.getRaw());
	disp.printf(2, 10, "drk:%-5d", pressureControl.getPressure());
	disp.printf(3, 0, "bndcnt:%-13d ", bandCounter.getCounter());
	disp.refresh();
}

//*******************************************************************

int StapelDetect::satisfied() {
	if (Light_Stapel.get() == 1) {
		return 10;
	} else if (btnA.getEvent() == Digital::ACTIVATED) {
		return 0;
	} else {
		return 1;
	}
}

void StapelDetect::transition(int destination) {
	//Uebergang zu CLRDetect
	if (destination == 10) {
		Ventil_Stapel.set(1);
		timerTask.delay(350);
		Ventil_Stapel.set(0);
		timerTask.delay(300);
	}

	//Uebergang zu Manual
	else if (destination == 0) {
		Ventil_Verarb.set(0);
		Ventil_Ausw.set(0);
		Ventil_Stapel.set(0);
		Motor_Band.set(0);
		led0.toggle();
		bandCounter.setCounter();
	}
}

void StapelDetect::display() {
	disp.printf(1, 0, "                    ");
	State::display();
	disp.refresh();
}

//*******************************************************************

int CLRDetect::satisfied() {
	int current_clr = Signal_Farbe.getRaw();
	if (current_clr >= 10000 and current_clr <= 15000) {
		return 20; //Red
	} else if (current_clr >= 58000 and current_clr <= 61500) {
		return 40; //Blue
	} else if (current_clr >= 35000 and current_clr <= 40000) {
		return 30; //White
	} else {
		return -1; //Undefinierte Farbe
	}
}

void CLRDetect::transition(int destination) {
	bandCounter.setCounter();
	Motor_Band.set(1);
}

void CLRDetect::display() {
	disp.printf(1, 0, "                    ");
	State::display();
	disp.refresh();
}

//*******************************************************************

int Red::satisfied() {
	if (bandCounter.getCounter() == 15) {
		return 2; //Finish
	} else {
		return 20; //Bleibt in Red
	}
}

void Red::transition(int destination) {
	Motor_Band.set(0);
	Ventil_Ausw.set(1);
	timerTask.delay(350);
	Ventil_Ausw.set(0);
	State::countRed();
}

void Red::display() {
	disp.printf(1, 0, "RED                 ");
	State::display();
	disp.refresh();
}

//*******************************************************************

int White::satisfied() {
	if (bandCounter.getCounter() == 37) {
		return 2; //Finish
	} else {
		return 30; //Beibt in White
	}
}

void White::transition(int destination) {
	State::countWhite();
}

void White::display() {
	disp.printf(1, 0, "WHITE/BROWN         ");
	State::display();
	disp.refresh();
}

//*******************************************************************

int Blue::satisfied() {
	if (bandCounter.getCounter() == 30) {
		return 41; //BluePass
	} else {
		return 40; //Bleibt in Blue
	}
}

void Blue::transition(int destination) {
	Motor_Band.set(0);
	Ventil_Verarb.set(1);
	timerTask.delay(350);
	Ventil_Verarb.set(0);
	timerTask.delay(400);
	Motor_Band.set(1);
}

void Blue::display() {
	disp.printf(1, 0, "BLUE                ");
	State::display();
	disp.refresh();
}

//*******************************************************************

int BluePass::satisfied() {
	if (bandCounter.getCounter() == 37) {
		return 2; //Finish
	} else {
		return 41; //Bleibt in BluePass
	}
}

void BluePass::transition(int destination) {
	State::countBlue();
}

void BluePass::display() {
	disp.printf(1, 0, "BLUE                ");
	State::display();
	disp.refresh();
}

//*******************************************************************

int Error::satisfied() {
	if (bandCounter.getCounter() == 45) {
		return 2; //Finish
	} else {
		return -1; //Bleibt in Error
	}
}

void Error::transition(int destination) {
	State::countError();
}

void Error::display() {
	disp.printf(1, 0, "ERROR               ");
	State::display();
	disp.refresh();
}

//*******************************************************************

int Finish::satisfied() {
	return 1; //StapelDetect
}

void Finish::transition(int destination) {
	Ventil_Verarb.set(0);
	Ventil_Ausw.set(0);
	Ventil_Stapel.set(0);
	Motor_Band.set(0);
}

void Finish::display() {
	disp.printf(1, 0, "                    ");
	State::display();
	disp.refresh();
}
