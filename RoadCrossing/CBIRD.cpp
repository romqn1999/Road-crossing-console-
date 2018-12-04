#include "CBIRD.h"

CBIRD::CBIRD() : CANIMAL(-1, -1, 3, 1)
{
	/*SetX(-1);
	SetY(-1);
	SetSizeX(3);
	SetSizeY(1);
	display = new int*[mSizeY];
	for (int i = 0; i < mSizeY; ++i) {
		display[i] = new int[mSizeX];
	}*/
	display[0][0] = 223; display[0][1] = 254; display[0][2] = 223;
}

CBIRD::CBIRD(int x, int y) : CANIMAL(x, y, 3, 1)
{
	/*SetX(x);
	SetY(y);
	SetSizeX(3);
	SetSizeY(1);
	display = new int*[mSizeY];
	for (int i = 0; i < mSizeY; ++i) {
		display[i] = new int[mSizeX];
	}*/
	display[0][0] = 223; display[0][1] = 254; display[0][2] = 223;
}

CBIRD::~CBIRD()
{
}

void CBIRD::draw() {
	GotoXY(mX, mY);
	cout << (char)223 << (char)254 << (char)223;
}

void CBIRD::clearDraw() {
	GotoXY(mX, mY);
	cout << (char)0 << (char)0 << (char)0;
}

