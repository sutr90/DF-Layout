#include "workshop.hpp"
#include <stdlib.h>

void Workshop::moveRel()
{
	int d = rand() % 8;
	this->x += this->delta[d][0];
	this->y += this->delta[d][1];
}

std::ostream& operator<< (std::ostream& os, const Workshop& obj) {
	os << "WShop: " << obj.x << "," << obj.y << "\n";
	return os;
}
