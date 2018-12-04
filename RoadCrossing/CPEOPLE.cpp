#include "CPEOPLE.h"



CPEOPLE::CPEOPLE() : CGAMEOBJECT(15, 17, 1, 2), mState(true)
{
	/*SetX(15);
	SetY(17);
	SetSizeX(1);
	SetSizeY(2);
	display = new int*[mSizeY];
	for (int i = 0; i < mSizeY; ++i) {
		display[i] = new int[mSizeX];
	}*/
	display[0][0] = 220;
	display[1][0] = 143;
}

CPEOPLE::~CPEOPLE()
{
	clearDraw();
}

void CPEOPLE::draw() {
	GotoXY(mX, mY);
	cout << (char)220;
	GotoXY(mX, mY + 1);
	cout << (char)143;
}

void CPEOPLE::clearDraw() {
	GotoXY(mX, mY);
	if (mY > 1 && mY % CONSTANT::WIDTHLANE == 1)
		cout << (char)196;
	else
		cout << (char)0;
	GotoXY(mX, mY + 1);
	if (mY + 1 > 1 && (mY + 1) % CONSTANT::WIDTHLANE == 1)
		cout << (char)196;
	else
		cout << (char)0;
}

void CPEOPLE::Up(int t) {
	Move(0, -1);
}

void CPEOPLE::Left(int t) {
	Move(-1, 0);
}

void CPEOPLE::Right(int t) {
	Move(1, 0);
}

void CPEOPLE::Down(int t) {
	Move(0, 1);
}

bool CPEOPLE::isImpact(vector<CVEHICLE*> vehicles) {
	for (int i = 0; vehicles[i]->isInGame(); ++i) {
		if (CGAMEOBJECT::isImpact(this, vehicles[i])) {
			mState = false;
			return true;
		}
	}
	return false;
}

bool CPEOPLE::isImpact(vector<CANIMAL*> animals) {
	for (int i = 0; animals[i]->isInGame(); ++i) {
		if (CGAMEOBJECT::isImpact(this, animals[i])) {
			mState = false;
			return true;
		}
	}
	return false;
}

bool CPEOPLE::isFinish() {
	return (mY < 1 + CONSTANT::WIDTHLANE);
}

bool CPEOPLE::isDead() {
	return !mState;
}
