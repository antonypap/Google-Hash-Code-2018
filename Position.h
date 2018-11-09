#pragma once

struct Position {
	int x, y;
	
	Position() : x(0), y(0) {};
	Position(int x, int y) : x(x), y(y) {};
};

enum Direction { UP = +1, DOWN = -1, RIGHT = +2, LEFT = -2 };
