#pragma once

struct Point {
	int x;
	int y;
	double E;

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	bool operator==(const Point& rhs) { return (x == rhs.x) && (y == rhs.y); }
};