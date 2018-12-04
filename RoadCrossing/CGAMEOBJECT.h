#pragma once

#include "Interface.h"
#include "Config.h"
#include "CTRAFFICLIGHT.h"
#include <vector>

using namespace std;

class CGAMEOBJECT
{
protected:
	int mX;
	int mY;
	int mSizeX;
	int mSizeY;
	//int **display;
	vector<vector<int>> display;
public:
	CGAMEOBJECT();
	CGAMEOBJECT(int x, int y, int sizeX, int sizeY);
	//void copyData(const CGAMEOBJECT& other);
	CGAMEOBJECT(const CGAMEOBJECT& other);
	CGAMEOBJECT(const CGAMEOBJECT*& other);
	CGAMEOBJECT& operator=(const CGAMEOBJECT& other);
	int GetX() { return mX; }
	int GetY() { return mY; }
	void SetX(int x) { mX = x; }
	void SetY(int y) { mY = y; }
	void SetSizeX(int sizeX) { mSizeX = sizeX; }
	void SetSizeY(int sizeY) { mSizeY = sizeY; }
	virtual void clearData();
	virtual ~CGAMEOBJECT() { clearData(); }
	virtual void draw() {}
	virtual void clearDraw() {}
	virtual void Move(int, int);
	//virtual bool isInGame() {}
	static bool isImpact(CGAMEOBJECT *obj, CGAMEOBJECT *other);
	static bool isImpact(CGAMEOBJECT obj, CGAMEOBJECT other);
};

