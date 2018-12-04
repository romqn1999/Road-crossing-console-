#pragma once

#include "CGAMEOBJECT.h"

class CANIMAL : public CGAMEOBJECT
{
public:
	CANIMAL() {}
	CANIMAL(int x, int y, int sizeX, int sizeY) : CGAMEOBJECT(x, y, sizeX, sizeY) {}
	CANIMAL(const CANIMAL& other) : CGAMEOBJECT(other) {}
	CANIMAL& operator=(const CANIMAL& other) { CGAMEOBJECT::operator=(other); return *this; }
	virtual bool isInGame() { return true; }
	virtual ~CANIMAL() {}
	//virtual void Tell();
};

