#include "CCAR.h"

CCAR::CCAR() : CVEHICLE(-1, -1, 4, 1)
{
	display[0][0] = 220; display[0][1] = 219; display[0][2] = 219; display[0][3] = 220;
}

CCAR::CCAR(int x, int y) : CVEHICLE(x, y, 4, 1)
{
	display[0][0] = 220; display[0][1] = 219; display[0][2] = 219; display[0][3] = 220;
}

CCAR::~CCAR()
{
}

void CCAR::draw() {
	GotoXY(mX, mY);
	cout << (char)220 << (char)219 << (char)219 << (char)220;
}

void CCAR::clearDraw() {
	GotoXY(mX, mY);
	cout << (char)0 << (char)0 << (char)0 << (char)0;
}

