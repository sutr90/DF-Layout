#include <stdio.h>
#include <vector>
#include "workshop.hpp"
#include "state.hpp"
#include <array>
#include <iostream>
#include <cmath>

int main(int argc, char **argv) {
	std::array<Workshop,28> ws = {
		Workshop(0,0, {}),
		Workshop(0,0, {2,3}),
		Workshop(0,0, {3,2,5,6,7}),
		Workshop(0,0, {4,14,15}),
		Workshop(0,0, {5,3,11,6}),
		Workshop(0,0, {6,5,7,3,9}),
		Workshop(0,0, {7,3,9,6}),
		Workshop(0,0, {}),
		Workshop(0,0, {9,6,7}),
		Workshop(0,0, {10,11,16,19,27}),
		Workshop(0,0, {11,5,10}),
		Workshop(0,0, {}),
		Workshop(0,0, {13,27}),
		Workshop(0,0, {14,4,20}),
		Workshop(0,0, {15,16,22,4}),
		Workshop(0,0, {16,20,10,17,15}),
		Workshop(0,0, {17,22,16}),
		Workshop(0,0, {18,21,26}),
		Workshop(0,0, {19,21,10}),
		Workshop(0,0, {20,16,25,14}),
		Workshop(0,0, {21,25,27,23,24,19,18}),
		Workshop(0,0, {22,17,15}),
		Workshop(0,0, {23,21}),
		Workshop(0,0, {24,21,28}),
		Workshop(0,0, {25,20,21}),
		Workshop(0,0, {26,18}),
		Workshop(0,0, {27,13,21,28,10}),
		Workshop(0,0, {28,24,27})
	};


	State<28> start(ws);
	State<28> best_state(ws), newState(ws);
	double t = 1000;
	int step_count = 0;
	int cost, newCost;
	for (int i = 0; i < 10000; i++) {
		cost = start.getCost();
		for (int j = 0; j < 500; j++) {
			step_count += 1;
			newState = start;
			newState.transition();
			newCost = newState.getCost();

			//std::cout << cost << " >< "  << newCost << "\n";
			if (newCost <= cost) {
				start = newState;
				best_state = start;
				cost = newCost;
			}
			else if(exp(-(newCost - cost)/t) > static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) {
				cost = newCost;
				best_state = start;
			}
			t *= 0.95;
		}
		if(step_count % 5000 == 0) {
			std::cout << step_count << "," << t << "\n";
		}
	}

	best_state.print();


	return 0;
}
