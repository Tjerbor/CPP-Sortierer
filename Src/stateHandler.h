#include "state.h"

class StateHandler {
private:
	//Zurzeitiger Zustand
	State *zustand;
	//ID des zurzeitigen zustands
	int zustandID;

public:
	StateHandler();
	~StateHandler();

	//Prueft auf Zustandsaenderung
	void refresh();
};
