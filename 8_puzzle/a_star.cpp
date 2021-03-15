#include <algorithm>

#include "boardState.h"
#include "problem.h"

int qmin(std::vector<boardState*> q) {
	double minCost = q[0]->c;
	int minIdx = 0;
	for (int i = 1; i < q.size(); i++) {
		if (q[i]->c < minCost) {
			minCost = q[i]->c;
			minIdx = i;
		}
	}
	return minIdx;
}

boardState* Astar(boardState& start, boardState& goal) {
	start.c = start.hamming(goal);
	std::vector<boardState*> queue;
	queue.push_back(&start);
	std::vector<boardState*> traversed;

	bool goalFound = false;
	boardState *goalState;

	boardState *currentState;

	while (queue.size()) {
		int minIdx = qmin(queue);
		currentState = queue[minIdx];
		queue.erase(queue.begin()+minIdx);
		traversed.push_back(currentState);
		if (*currentState == goal) {
			goalFound = true;
			goalState = currentState;
			break;
		}
		std::vector<boardState*> children = currentState->generateChildren();
		for (auto &i: children) {
			i->c = i->n + i->hamming(goal);
			queue.push_back(i);
		}
	}

	if (goalFound) {
		return goalState;
	} else {
		return &start;
	}
}

int main() {
	boardState startState(start), goalState(goal);
	boardState *answer, *currentState;
	std::vector<boardState*> path;

	answer = Astar(startState, goalState);
	
	if (*answer == startState) {
		std::cout << "Goal could not be found.\n";
		return 0;
	}

	currentState = answer;

	while (currentState != nullptr) {
		path.push_back(currentState);
		currentState = currentState->parent;
	}

	std::reverse(path.begin(), path.end());

	std::cout << "Path to goal (Number of moves = " << path.size() << "):\n";
	for(auto &i: path) {
		i->printState();
	}
	
	return 0;
}