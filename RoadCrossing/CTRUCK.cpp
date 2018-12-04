#include "CTRUCK.h"



CTRUCK::CTRUCK() : CVEHICLE(-1, -1, 3, 1)
{
	display[0][0] = 220; display[0][1] = 219; display[0][2] = 219;
}

CTRUCK::CTRUCK(int x, int y) : CVEHICLE(x, y, 3, 1)
{
	display[0][0] = 220; display[0][1] = 219; display[0][2] = 219;
}

CTRUCK::~CTRUCK()
{
}

void CTRUCK::draw() {
	GotoXY(mX, mY);
	cout << (char)220 << (char)219 << (char)219;
}

void CTRUCK::clearDraw() {
	GotoXY(mX, mY);
	cout << (char)0 << (char)0 << (char)0;
}
