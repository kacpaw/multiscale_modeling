#pragma once

struct Point {
	int x;
	int y;

	bool operator==(const Point& rhs) { return (x == rhs.x) && (y == rhs.y); }
};