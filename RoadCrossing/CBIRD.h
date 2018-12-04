#pragma once
#include "CANIMAL.h"

class CBIRD :
	public CANIMAL
{
public:
	CBIRD();
	CBIRD(int x, int y);
	~CBIRD();
	void draw();
	void clearDraw();
	bool isInGame() { return mX != -1; }
};

