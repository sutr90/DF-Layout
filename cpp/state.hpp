#ifndef STATE_HPP
#define STATE_HPP

#include <vector>
#include "workshop.hpp"
#include <stdlib.h>
#include <time.h>
#include <ostream>
#include <array>
#include <iostream>

template<std::size_t N> class State {
public:
	std::array<Workshop, N> ws;
	State(std::array<Workshop, N>& wsP) : ws(wsP) {
		srand(time(NULL));
	};

	virtual ~State() {};

	void swapWorkshops(int w1, int w2) {
		std::swap(ws[w1], ws[w2]);
	};

	int getArea() {
		int maxX, maxY, minX, minY;
		maxX = maxY = -10000;
		minX = minY = 10000;
		for(int i = 0; i < N; i++) {
			if(ws[i].x > maxX) maxX = ws[i].x;
			if(ws[i].y > maxY) maxY = ws[i].y;

			if(ws[i].x < minX) minX = ws[i].x;
			if(ws[i].y < minY) minY = ws[i].y;
		}
		return (maxX-minX)*(maxY-minY);
	};

	int getOverlap() {
		int total = 0;
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				if(i == j) continue;
				if(ws[i].x == ws[j].x  && ws[i].y == ws[j].y) {
					total += 1000;
				}
			}
		}

		return total;
	};

	int getDistance() {
		int total = 0;
		for(int i = 0; i < N; i++) {
			for(auto it = ws[i].nbs.begin(); it != ws[i].nbs.end(); ++it) {
				total += abs(ws[i].x - ws[*it-1].x) + abs(ws[i].y - ws[*it-1].y);
			}
		}

		return total;
	};

	int getCost() {
		return getDistance() + getArea() + getOverlap();
	};

	void transition() {
		if(rand() % 4 == 0) {
			swapWorkshops(rand() % N, rand() % N);
		}
		else {
			ws[rand() % N].moveRel();
		}
	};

	void print() {
		for(int i = 0; i < N; i++) {
			std::cout << ws[i];
		}
	};
};

#endif // STATE_HPP
