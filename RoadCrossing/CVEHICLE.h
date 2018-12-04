#pragma once

#include "CGAMEOBJECT.h"

class CVEHICLE : public CGAMEOBJECT
{
public:
	CVEHICLE() {}
	CVEHICLE(int x, int y, int sizeX, int sizeY) : CGAMEOBJECT(x, y, sizeX, sizeY) {}
	CVEHICLE(const CVEHICLE& other) : CGAMEOBJECT(other) {}
	CVEHICLE& operator=(const CVEHICLE& other) { CGAMEOBJECT::operator=(other); return *this; }
	virtual bool isInGame() { return true; }
	virtual ~CVEHICLE() {}
};

