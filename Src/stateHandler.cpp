#include "state.h"
#include "statehandler.h"

StateHandler::StateHandler() :
		zustand(new Manual()), zsd(0) {

}

void StateHandler::refresh() {
	int next = zustand->satisfied();

	if (next != zsd) {
		zsd = next;
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

	zustand->display();
}
