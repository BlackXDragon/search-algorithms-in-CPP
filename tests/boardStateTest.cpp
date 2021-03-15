#include <iostream>
#include "../8_puzzle/boardState.h"

int main() {
	uint8_t s1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
	uint8_t s2[3][3] = {{1, 2, 3}, {4, 0, 6}, {7, 8, 5}};
	boardState state1(s1);
	boardState state2(s2, 1, &state1);
	boardState state3(s1, 2, &state2);
	
	state1.printState();
	state2.printState();
	state3.printState();

	std::cout << "Equality test 1 (expected false): " << (state1 == state2) << "\n";
	std::cout << "Equality test 2 (expected true): " << (state1 == state3) << "\n";

	std::cout << "\nparentOccured test (expected true): " << state3.parentOccured() << "\n";

	int *c;
	c = state1.coords();
	std::cout << "\ncoords test (expected 2, 2): " << c[0] << ", " << c[1] << "\n";
	c = state2.coords();
	std::cout << "\ncoords test (expected 1, 1): " << c[0] << ", " << c[1] << "\n";

	std::vector<boardState*> children;
	children = state1.generateChildren();
	std::cout << "\nChildren of state1:\n";
	for (auto &i: children) {
		i->printState();
	}

	children = state2.generateChildren();
	std::cout << "\nChildren of state2:\n";
	for (auto &i: children) {
		i->printState();
	}

	return 0;
}