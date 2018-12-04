#pragma once

#include "Interface.h"

class CTRAFFICLIGHT
{
private:
	enum LIGHTCOLOUR
	{
		RED,
		GREEN
	};
	int mX = 0;
	int mY = 0;
	int mTime = 0;
	int MAXTIME = 20;
	LIGHTCOLOUR mLightColour = GREEN;
public:
	CTRAFFICLIGHT();
	~CTRAFFICLIGHT();
	bool isRedLight() { return mLightColour == RED; }
	void updateTime();
	void draw();
	void setXY(int x, int y) { mX = x; mY = y; }
	int GetTime() { return mTime; }
	void SetTime(int time) { mTime = time; }
	void SetRedLight() { mLightColour = RED; }
};

