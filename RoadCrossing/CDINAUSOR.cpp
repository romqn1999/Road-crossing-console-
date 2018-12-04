#include "CDINAUSOR.h"



CDINAUSOR::CDINAUSOR() : CANIMAL(-1, -1, 3, 2)
{
	/*SetX(-1);
	SetY(-1);
	SetSizeX(3);
	SetSizeY(2);
	display = new int*[mSizeY];
	for (int i = 0; i < mSizeY; ++i) {
		display[i] = new int[mSizeX];
	}*/
	display[0][0] = 0; display[0][1] = 0; display[0][2] = 220;
	display[1][0] = 220; display[1][1] = 219; display[1][2] = 223;
}

CDINAUSOR::CDINAUSOR(int x, int y) : CANIMAL(x, y, 3, 2)
{
	/*SetX(x);
	SetY(y);
	SetSizeX(3);
	SetSizeY(2);
	display = new int*[mSizeY];
	for (int i = 0; i < mSizeY; ++i) {
		display[i] = new int[mSizeX];
	}*/
	display[0][0] = 0; display[0][1] = 0; display[0][2] = 220;
	display[1][0] = 220; display[1][1] = 219; display[1][2] = 223;
}

CDINAUSOR::~CDINAUSOR()
{
}

void CDINAUSOR::draw() {
	GotoXY(mX, mY + 1);
	cout << (char)220 << (char)219 << (char)223;
	GotoXY(mX + 2, mY);
	cout << (char)220;
}

void CDINAUSOR::clearDraw() {
	GotoXY(mX, mY + 1);
	cout << (char)0 << (char)0 << (char)0;
	GotoXY(mX + 2, mY);
	cout << (char)0;
}
