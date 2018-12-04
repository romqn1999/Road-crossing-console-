#include "CTRAFFICLIGHT.h"



CTRAFFICLIGHT::CTRAFFICLIGHT()
{
}


CTRAFFICLIGHT::~CTRAFFICLIGHT()
{
}

void CTRAFFICLIGHT::updateTime() {
	if (mTime == MAXTIME) {
		mTime = 0;
		if (mLightColour == RED) {
			mLightColour = GREEN;
		}
		else {
			mLightColour = RED;
		}
	}
	else {
		++mTime;
	}
}

void CTRAFFICLIGHT::draw() {
	HANDLE chandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (mLightColour == LIGHTCOLOUR::GREEN) {
		GotoXY(mX, mY);
		cout << setcolour(colour::GREEN, chandle) << (char)220;
		GotoXY(mX, mY + 1);
		cout << (char)0;
	}
	else {
		GotoXY(mX, mY);
		cout << setcolour(colour::WHITE, chandle) << (char)196;
		GotoXY(mX, mY + 1);
		cout << setcolour(colour::RED, chandle) << (char)223;
	}

	cout << setcolour(WHITE, chandle);
}
