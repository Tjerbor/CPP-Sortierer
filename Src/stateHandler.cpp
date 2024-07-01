#include "state.h"
#include "statehandler.h"

//Anfangszustand = Manual
StateHandler::StateHandler() :
		zustand(new Manual()), zustandID(0) {
}

void StateHandler::refresh() {
	//Erhalte die neue ZustandsID
	int next = zustand->satisfied();

	//Falls die ID sich geaendert hat,
	//erzeuge entsprechenden neuen zustand
	//und fuehre die Uebergangsaktion aus
	if (next != zustandID) {
		zustandID = next;
		zustand->transition(next);
		delete zustand;
		if (next == 0) {
			zustand = new Manual();
		} else if (next == 1) {
			zustand = new StapelDetect();
		} else if (next == 2) {
			zustand = new Finish();
		} else if (next == -1) {
			zustand = new Error();
		} else if (next == 10) {
			zustand = new CLRDetect();
		} else if (next == 20) {
			zustand = new Red();
		} else if (next == 30) {
			zustand = new White();
		} else if (next == 40) {
			zustand = new Blue();
		} else if (next == 41) {
			zustand = new BluePass();
		}
	}

	//Zustandsspezifische Displayausgabe
	zustand->display();
}
