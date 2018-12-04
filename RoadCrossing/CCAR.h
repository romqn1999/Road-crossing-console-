#pragma once
#include "CVEHICLE.h"

class CCAR :
	public CVEHICLE
{
public:
	CCAR();
	CCAR(int x, int y);
	CCAR(const CCAR& other) : CVEHICLE(other) {}
	~CCAR();
	void draw();
	void clearDraw();
	bool isInGame() { return mX != -1; }
};

