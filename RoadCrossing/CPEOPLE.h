#pragma once

#include "CVEHICLE.h"
#include "CANIMAL.h"
#include "Interface.h"
#include "CGAMEOBJECT.h"

class CPEOPLE : public CGAMEOBJECT
{
private:
	bool mState;
public:
	CPEOPLE();
	~CPEOPLE();
	void draw();
	void clearDraw();
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	bool isImpact(vector<CVEHICLE*>);
	bool isImpact(vector<CANIMAL*>);
	bool isFinish();
	bool isDead();
};

