#include "state.h"

class StateHandler {
private:
	State *zustand;
	int zsd;

public:
	StateHandler();
	~StateHandler();

	void refresh();
};
