#pragma once

#include "Interface.h"
#include "CTRUCK.h"
#include "CCAR.h"
#include "CDINAUSOR.h"
#include "CBIRD.h"
#include "CPEOPLE.h"
#include "CTRAFFICLIGHT.h"
#include <iostream>
#include <thread>
#include <conio.h>

using namespace std;

class CGAME
{
private:
	int numTruck;
	//CTRUCK **axt;
	vector<CTRUCK*> axt;
	int numCar;
	CCAR **axh;
	int numDinausor;
	CDINAUSOR **akl;
	int numBird;
	CBIRD **ac;
	CPEOPLE *cn;
	CTRAFFICLIGHT mTruckTrafficLight;
	CTRAFFICLIGHT mCarTrafficLight;
	int level = 0;
	const static int MAXLEVEL = 3;
	vector<int> mapTruck[MAXLEVEL];
	vector<int> mapCar[MAXLEVEL];
	vector<int> mapBird[MAXLEVEL];
	vector<int> mapDinausor[MAXLEVEL];
	void setMapObjgame();
public:
	static bool IS_RUNNING;
	static int LENGTHX;
	static bool REDLIGHT;
	static bool IS_ONSOUND;
	void setData();
	CGAME();
	void drawBoard();
	void drawGame();
	void clearData();
	~CGAME();
	CPEOPLE*& getPeople(); //Lay thong tin nguoi
	vector<CVEHICLE*> getVehicle(); //Lay danh sach cac xe
	vector<CANIMAL*> getAnimal(); //Lay danh sach cac thu
	void resetGame();
	void exitGame(HANDLE); //Thuc hien thoat Thread
	void startGame();
	void drawUpdateGame();
	int getLevel() { return level; }
	bool levelUp();
	void setLevel(int l);
	void loadGame(string fileName);
	void saveGame(string fileName);
	void pauseGame(HANDLE); //Tam dung Thread
	void resumeGame(HANDLE); //Quay lai Thread
	void updatePosPeople(char); //Thuc hien dieu khien di chuyen cua CPEOPLE
	void updatePosVehicle(); //Thuc hien cho CTRUCK & CCAR di chuyen
	void updatePosAnimal(); //Thuc hien cho CDINAUSOUR & CBIRD di chuyen
	void trunOnSound() { IS_ONSOUND = true; BackgroundMusic(); }
	void trunOffSound() { IS_ONSOUND = false; PlaySound(NULL, NULL, NULL); }
};

