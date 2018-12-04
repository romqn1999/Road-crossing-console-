#include "CGAMEOBJECT.h"

CGAMEOBJECT::CGAMEOBJECT() {
	//display = nullptr;
	clearData();
}

CGAMEOBJECT::CGAMEOBJECT(int x, int y, int sizeX, int sizeY) : mX(x), mY(y), mSizeX(sizeX), mSizeY(sizeY) {
	/*display = new int*[mSizeY];
	for (int i = 0; i < mSizeY; ++i) {
		display[i] = new int[mSizeX];
	}*/
	display.resize(mSizeY);
	for (int i = 0; i < mSizeY; ++i) {
		display[i].resize(mSizeX);
	}
}

//void CGAMEOBJECT::copyData(const CGAMEOBJECT& other) {
//	if (display != nullptr) {
//		delete[] display;
//	}
//	this->mX = other.mX;
//	this->mY = other.mY;
//	this->mSizeX = other.mSizeX;
//	this->mSizeY = other.mSizeY;
//	display = nullptr;
//	display = new int*[mSizeY];
//	for (int i = 0; i < mSizeY; ++i) {
//		display[i] = new int[mSizeX];
//		for (int j = 0; j < mSizeX; ++j) {
//			display[i][j] = other.display[i][j];
//		}
//	}
//}

CGAMEOBJECT::CGAMEOBJECT(const CGAMEOBJECT& other) {
	if (this != &other) {
		*this = other;
	}
}

CGAMEOBJECT::CGAMEOBJECT(const CGAMEOBJECT*& other) {
	if (this != other) {
		*this = *other;
	}
}

CGAMEOBJECT& CGAMEOBJECT::operator=(const CGAMEOBJECT& other) {
	clearData();
	mX = other.mX;
	mY = other.mY;
	mSizeX = other.mSizeX;
	mSizeY = other.mSizeY;
	/*display = nullptr;
	display = new int*[mSizeY];
	for (int i = 0; i < mSizeY; ++i) {
		display[i] = new int[mSizeX];
		for (int j = 0; j < mSizeX; ++j) {
			display[i][j] = other.display[i][j];
		}
	}*/
	display = other.display;
	return *this;
}

void CGAMEOBJECT::clearData()
{
	/*if (display == nullptr) return;
	for (int i = 0; i < mSizeY; ++i) {
		if (display[i] != nullptr)
			delete[] display[i];
		display[i] = nullptr;
	}
	delete[] display;
	display = nullptr;*/
	display.clear();
}

void CGAMEOBJECT::Move(int dx, int dy) {
	clearDraw();
	int l = CONSTANT::LENGTHX - mSizeX + 1;
	mX = ((mX - 1 + dx) % l + l) % l + 1;
	//mY = ((mY - 1 + dy) % l + l) % l + 1;
	if (0 < mY + dy && mY + dy < 6 * CONSTANT::WIDTHLANE) {
		mY += dy;
	}
	draw();
}

bool CGAMEOBJECT::isImpact(CGAMEOBJECT*obj, CGAMEOBJECT* other) {
	for (int i = 0; i < obj->mSizeY; ++i) {
		for (int j = 0; j < obj->mSizeX; ++j) {
			if (obj->display[i][j] == 0) continue;
			int y = obj->mY + i - other->mY, x = obj->mX + j - other->mX;
			if (x < 0 || other->mSizeX <= x || y < 0 || other->mSizeY <= y) {
				continue;
			}
			if (other->display[y][x] != 0) {
				return true;
			}
		}
	}
	return false;
}

bool CGAMEOBJECT::isImpact(CGAMEOBJECT obj, CGAMEOBJECT other) {
	for (int i = 0; i < obj.mSizeX; ++i) {
		for (int j = 0; j < obj.mSizeY; ++j) {
			if (obj.display[obj.mX + i][obj.mY + j] == 0) continue;
			int u = obj.mX + i - other.mX, v = obj.mY + j - other.mY;
			if (u < 0 || other.mX + other.mSizeX <= u || v < 0 || other.mY + other.mSizeY <= v) {
				continue;
			}
			if (other.display[other.mX + u][other.mY + v] != 0) {
				return true;
			}
		}
	}
	return false;
}
