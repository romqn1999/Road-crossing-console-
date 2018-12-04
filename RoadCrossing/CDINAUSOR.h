#pragma once
#include "CANIMAL.h"

class CDINAUSOR :
	public CANIMAL
{
public:
	CDINAUSOR();
	CDINAUSOR(int x, int y);
	~CDINAUSOR();
	void draw();
	void clearDraw();
	bool isInGame() { return mX != -1; }
};

