#if !defined(BOARD_STATE_H)
#define BOARD_STATE_H

#include <iostream>
#include <vector>

class boardState {
	private:
		uint8_t state[3][3];
	public:
		int n;
		boardState* parent;
		double c;

		boardState(uint8_t state[3][3], int n = 0, boardState* parent = nullptr, double c = 0) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					this->state[i][j] = state[i][j];
				}
			}
			this->n = n;
			this->parent = parent;
			this->c = c;
		}

		boardState(const boardState &b1) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					this->state[i][j] = b1.state[i][j];
				}
			}
			this->n = b1.n;
			this->parent = b1.parent;
			this->c = b1.c;
		}

		void printState() {
			std::cout << "Board State with n = " << n << ", c = " << c << ".\n";
			for (int i = 0; i < 3; i++) {
				std::cout << "+---+---+---+\n";
				std::cout << "| ";
				for (int j = 0; j < 3; j++) {
					std::cout << (int)this->state[i][j];
					std::cout << " | ";
				}
				std::cout << "\n";
			}
			std::cout << "+---+---+---+\n";
		}
		
		bool operator==(boardState& other) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					// std::cout << (int)this->state[i][j] << ' ' << (int)other.state[i][j] << ' ' << (this->state[i][j] != other.state[i][j]) << "\n";
					if (this->state[i][j] != other.state[i][j]) {
						return false;
					}
				}
			}
			return true;
		}

		bool operator!=(boardState& other) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					// std::cout << (int)this->state[i][j] << ' ' << (int)other.state[i][j] << ' ' << (this->state[i][j] != other.state[i][j]) << "\n";
					if (this->state[i][j] != other.state[i][j]) {
						return true;
					}
				}
			}
			return false;
		}
		
		int hamming(boardState &goal) {
			int h = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					h += (this->state[i][j] != goal.state[i][j]);
				}
			}
			return h;
		}

		bool parentOccured() {
			boardState* a = this->parent;
			while (a->parent != nullptr) {
				// this->printState();
				// a->parent->printState();
				// std::cout << "Equality: " << (*(a->parent) == *this) <<"\n";
				if (*(a->parent) == *this)
					return true;
				a = a->parent;
			}
			return false;
		}

		int* coords(uint8_t element = 0) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (this->state[i][j] == element) {
						int *crds = new int[2];
						crds[0] = i;
						crds[1] = j;
						return crds;
					}
				}
			}
			static int crds[2] = {-1, -1};
			return crds;
		}

		std::vector<boardState*> generateChildren() {
			int *crds;
			crds = this->coords();
			// std::cout << "\ncoords: " << crds[0] << ", " << crds[1] << "\n";
			std::vector<boardState*> children;

			// Move Up
			if (crds[0] != 0) {
				boardState *child = new boardState(*this);
				child->state[crds[0]-1][crds[1]] = 0;
				child->state[crds[0]][crds[1]] = this->state[crds[0]-1][crds[1]];
				child->n++;
				child->parent = this;
				// std::cout << "Created Up child:\n";
				// child->printState();
				if (!child->parentOccured()) {
					children.push_back(child);
				}
			}

			// Move Left
			if (crds[1] != 0) {
				boardState *child = new boardState(*this);
				child->state[crds[0]][crds[1]-1] = 0;
				child->state[crds[0]][crds[1]] = this->state[crds[0]][crds[1]-1];
				child->n++;
				child->parent = this;
				// std::cout << "Created Left child:\n";
				// child->printState();
				if (!child->parentOccured()) {
					children.push_back(child);
				}
			}

			// Move Down
			if (crds[0] != 2) {
				boardState *child = new boardState(*this);
				child->state[crds[0]+1][crds[1]] = 0;
				child->state[crds[0]][crds[1]] = this->state[crds[0]+1][crds[1]];
				child->n++;
				child->parent = this;
				// std::cout << "Created Down child:\n";
				// child->printState();
				if (!child->parentOccured()) {
					children.push_back(child);
				}
			}

			// Move Right
			if (crds[1] != 2) {
				boardState *child = new boardState(*this);
				child->state[crds[0]][crds[1]+1] = 0;
				child->state[crds[0]][crds[1]] = this->state[crds[0]][crds[1]+1];
				child->n++;
				child->parent = this;
				// std::cout << "Created Right child:\n";
				// child->printState();
				if (!child->parentOccured()) {
					children.push_back(child);
				}
			}
			return children;
		}
};

#endif // BOARD_STATE_H
