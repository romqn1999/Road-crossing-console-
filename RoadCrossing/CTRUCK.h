#pragma once
#include "CVEHICLE.h"

class CTRUCK :
	public CVEHICLE
{
private:
	int mMinX;
	int mMaxX;
public:
	CTRUCK();
	CTRUCK(int x, int y);
	CTRUCK(const CTRUCK& other) : CVEHICLE(other) {}
	~CTRUCK();
	void draw();
	void clearDraw();
	bool isInGame() { return mX != -1; }
};

