#ifndef POSITION_H
#define POSITION_H

struct Position{
	int x;
	int y;
	int w;
	int h;
	Position() :x(0), y(0), w(0), h(0){}
	Position(int x, int y, int w, int h){ 
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};

#endif