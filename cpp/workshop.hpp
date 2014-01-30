#ifndef WORKSHOP_HPP
#define WORKSHOP_HPP

#include <vector>
#include <ostream>

class Workshop {
	int delta[8][2] = {{-1, 1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

public:
	Workshop(int xP, int yP, const std::vector<int> &n) : x(xP), y(yP), nbs(n) {};
	virtual ~Workshop() {};
	int x;
	int y;
	std::vector<int> nbs;
	void moveRel();


};

	std::ostream& operator<< (std::ostream&, const Workshop&);
#endif // WORKSHOP_HPP
