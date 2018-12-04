#include "CGAME.h"
#include "Config.h"


int CGAME::LENGTHX = 35;
bool CGAME::IS_RUNNING = true;
bool CGAME::REDLIGHT = false;
bool CGAME::IS_ONSOUND = true;

void CGAME::setMapObjgame() {
	//Map Truck
	mapTruck[0].clear();
	mapTruck[0].push_back(1); mapTruck[0].push_back(12); mapTruck[0].push_back(23);

	mapTruck[1].clear();
	mapTruck[1].push_back(1); mapTruck[1].push_back(10); mapTruck[1].push_back(18); mapTruck[1].push_back(27);

	mapTruck[2].clear();
	mapTruck[2].push_back(4); mapTruck[2].push_back(11); mapTruck[2].push_back(18); mapTruck[2].push_back(25); mapTruck[2].push_back(32);
	
	//Map Car
	mapCar[0].clear();
	mapCar[0].push_back(5); mapCar[0].push_back(16); mapCar[0].push_back(27);

	mapCar[1].clear();
	mapCar[1].push_back(5); mapCar[1].push_back(16); mapCar[1].push_back(27);

	mapCar[2].clear();
	mapCar[2].push_back(5); mapCar[2].push_back(13); mapCar[2].push_back(21); mapCar[2].push_back(29);

	//Map Bird
	mapBird[0].clear();
	mapBird[0].push_back(1); mapBird[0].push_back(12); mapBird[0].push_back(23);

	mapBird[1].clear();
	mapBird[1].push_back(1); mapBird[1].push_back(10); mapBird[1].push_back(18); mapBird[1].push_back(27);

	mapBird[2].clear();
	mapBird[2].push_back(4); mapBird[2].push_back(11); mapBird[2].push_back(18); mapBird[2].push_back(25); mapBird[2].push_back(32);

	//Map Dinausor
	mapDinausor[0].clear();
	mapDinausor[0].push_back(1); mapDinausor[0].push_back(12); mapDinausor[0].push_back(23);

	mapDinausor[1].clear();
	mapDinausor[1].push_back(1); mapDinausor[1].push_back(10); mapDinausor[1].push_back(18); mapDinausor[1].push_back(27);

	mapDinausor[2].clear();
	mapDinausor[2].push_back(4); mapDinausor[2].push_back(11); mapDinausor[2].push_back(18); mapDinausor[2].push_back(25); mapDinausor[2].push_back(32);
}

void CGAME::setData() {
	setMapObjgame();

	//level = 2;

	//Truck
	//axt = new CTRUCK*[mapTruck[level].size() + 1];
	axt.clear();
	axt.resize(0);
	for (int i = 0; i < mapTruck[level].size(); ++i) {
		//axt[i] = new CTRUCK(mapTruck[level][i], 1 + 4 * CONSTANT::WIDTHLANE + 2);
		axt.push_back(new CTRUCK(mapTruck[level][i], 1 + 4 * CONSTANT::WIDTHLANE + 2));
	}
	//axt[mapTruck[level].size()] = new CTRUCK(-1, -1);
	axt.push_back(new CTRUCK(-1, -1));

	//Car
	axh = new CCAR*[mapCar[level].size() + 1];
	for (int i = 0; i < mapCar[level].size(); ++i) {
		axh[i] = new CCAR(mapCar[level][i], 1 + 3 * CONSTANT::WIDTHLANE + 2);
	}
	axh[mapCar[level].size()] = new CCAR(-1, -1);

	//Dinausor
	akl = new CDINAUSOR*[mapDinausor[level].size() + 1];
	for (int i = 0; i < mapDinausor[level].size(); ++i) {
		akl[i] = new CDINAUSOR(mapDinausor[level][i], 1 + 2 * CONSTANT::WIDTHLANE + 1);
	}
	akl[mapDinausor[level].size()] = new CDINAUSOR(-1, -1);

	//Bird
	ac = new CBIRD*[mapBird[level].size() + 1];
	for (int i = 0; i < mapBird[level].size(); ++i) {
		ac[i] = new CBIRD(mapBird[level][i], 1 + 1 * CONSTANT::WIDTHLANE + 1);
	}
	ac[mapBird[level].size()] = new CBIRD(-1, -1);

	//People
	cn = new CPEOPLE;

	mTruckTrafficLight.setXY(1, 13);
	mCarTrafficLight.setXY(LENGTHX, 10);
}

CGAME::CGAME()
{
	setData();
}

void CGAME::clearData() {
	int i;
	//Truck
	//for (i = 0; axt[i]->isInGame(); ++i) {
	//	axt[i]->SetX(-1);
	//	delete axt[i];
	//}
	//delete axt[i];
	//delete[] axt; axt = nullptr;
	for (i = 0; i < axt.size(); ++i) {
		axt[i]->SetX(-1);
		delete axt[i];
		axt[i] = nullptr;
	}
	axt.clear();
	//axt.resize(0);

	//Car
	for (i = 0; axh[i]->isInGame(); ++i) {
		axh[i]->SetX(-1);
		delete axh[i];
	}
	delete axh[i];
	delete[] axh;
	axh = nullptr;

	//Dinausor
	for (i = 0; akl[i]->isInGame(); ++i) {
		akl[i]->SetX(-1);
		delete akl[i];
	}
	delete akl[i];
	delete[] akl; akl = nullptr;

	//Bird
	for (i = 0; ac[i]->isInGame(); ++i) {
		ac[i]->SetX(-1);
		delete ac[i];
	}
	delete ac[i];
	delete[] ac;
	ac = nullptr;

	//People
	delete cn;
	cn = nullptr;
}

CGAME::~CGAME()
{
	clearData();
}

void CGAME::drawBoard() {
	HANDLE chandle = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << setcolour(WHITE, chandle);

	GotoXY(0, 0);
	cout << (char)218;
	GotoXY(1, 0);
	for (int i = 1; i <= LENGTHX; ++i) {
		cout << (char)196;
	}
	GotoXY(LENGTHX + 1, 0);
	cout << (char)191;

	for (int y = 1; y <= 18; ++y) {
		GotoXY(0, y);
		cout << (char)179;
		GotoXY(36, y);
		cout << (char)179;
	}

	GotoXY(0, 19);
	cout << (char)192;
	for (int x = 1; x <= LENGTHX; ++x) {
		GotoXY(x, 19);
		cout << (char)196;
	}
	GotoXY(LENGTHX + 1, 19);
	cout << (char)217;

	for (int i = 1; i <= 5; ++i) {
		GotoXY(0, CONSTANT::WIDTHLANE * i + 1);
		cout << (char)195;
		for (int x = 1; x <= LENGTHX; ++x) {
			GotoXY(x, CONSTANT::WIDTHLANE * i + 1);
			cout << (char)196;
		}
		GotoXY(LENGTHX + 1, CONSTANT::WIDTHLANE * i + 1);
		cout << (char)180;
	}
}

void CGAME::drawGame() {
	system("cls");
	drawBoard();
	mTruckTrafficLight.draw();
	mCarTrafficLight.draw();

	for (int i = 0; axt[i]->isInGame(); ++i) {
		axt[i]->draw();
	}

	for (int i = 0; axh[i]->isInGame(); ++i) {
		axh[i]->draw();
	}

	for (int i = 0; akl[i]->isInGame(); ++i) {
		akl[i]->draw();
	}

	for (int i = 0; ac[i]->isInGame(); ++i) {
		ac[i]->draw();
	}
	
	cn->draw();

	GotoXY(-28, 2); cout << "Press L to save game.";
	GotoXY(-28, 3); cout << "Press T to load game.";
	GotoXY(-28, 4); cout << "Press C to go to setting.";
	GotoXY(-28, 5); cout << "Press Esc to exit game.";
}

void CGAME::drawUpdateGame() {
	mTruckTrafficLight.updateTime();
	mTruckTrafficLight.draw();
	mCarTrafficLight.updateTime();
	mCarTrafficLight.draw();
	cn->draw();
	if (level < MAXLEVEL && !getPeople()->isFinish()) {
		GotoXY(45, 2); cout << "Level: " << level;
	}
	else {
		GotoXY(45, 2); cout << "Congratulations! You win!";
		//HANDLE chandle = GetStdHandle(STD_OUTPUT_HANDLE);
		//GotoXY(45, 4); cout << setcolour(colour::RED, chandle);
	}
	GotoXY(LENGTHX / 2, 1);
}

bool CGAME::levelUp() {
	if (level == MAXLEVEL - 1) {
		//cout << "Max level";
		return false;
	}
	else {
		clearData();
		++level;
		setData();
		resetGame();
		return true;
	}
}

void CGAME::setLevel(int l) {
	if (level == l) return;
	if (0 <= l && l < MAXLEVEL) {
		clearData();
		level = l;
		setData();
	}
}

CPEOPLE*& CGAME::getPeople() {
	return (cn);
}

vector<CVEHICLE*> CGAME::getVehicle() {
	//CVEHICLE **vehicles = new CVEHICLE*[numCar + numTruck + 1];
	vector<CVEHICLE*> vehicles;
	for (int i = 0; axh[i]->isInGame(); ++i) {
		//vehicles[i] = new CCAR(*axh[i]);
		vehicles.push_back(new CCAR(*axh[i]));
	}
	for (int i = 0; axt[i]->isInGame(); ++i) {
		//vehicles[numCar + i] = new CTRUCK(*axt[i]);
		vehicles.push_back(new CTRUCK(*axt[i]));
	}
	//vehicles[numCar + numTruck] = new CTRUCK(-1, -1);
	vehicles.push_back(new CTRUCK(-1, -1));
	return vehicles;
}

vector<CANIMAL*> CGAME::getAnimal() {
	//CANIMAL **animals = new CANIMAL*[numBird + numDinausor + 1];
	vector<CANIMAL*> animals;
	for (int i = 0; ac[i]->isInGame(); ++i) {
		//animals[i] = new CANIMAL(*ac[i]);
		animals.push_back(new CBIRD(*ac[i]));
	}
	for (int i = 0; akl[i]->isInGame(); ++i) {
		//animals[numBird + i] = new CANIMAL(*akl[i]);
		animals.push_back(new CDINAUSOR(*akl[i]));
	}
	//animals[numBird + numDinausor] = new CANIMAL(*akl[numDinausor]);
	animals.push_back(new CDINAUSOR(-1, -1));
	return animals;
}

void CGAME::resetGame() {
	delete cn;
	cn = new CPEOPLE;
	system("cls");
	drawGame();
	IS_RUNNING = true;
}

void CGAME::exitGame(HANDLE h) {
	system("cls");
	IS_RUNNING = false;
	/*LPDWORD lpExitCode = NULL;
	if (GetExitCodeThread(h, lpExitCode)) {
		ExitThread(*lpExitCode);
	}*/
}

void CGAME::startGame() {

}

void CGAME::loadGame(string fileName) {
	int x;
	fstream file;
	file.open(fileName, ios::in | ios::binary);
	file.read(reinterpret_cast<char*>(&level), sizeof(level));
	setData();
	file.read(reinterpret_cast<char*>(&x), sizeof(x));
	cn->SetX(x);
	file.read(reinterpret_cast<char*>(&x), sizeof(x));
	cn->SetY(x);
	for (int i = 0; i < mapTruck[level].size(); ++i) {
		file.read(reinterpret_cast<char*>(&x), sizeof(x));
		axt[i]->SetX(x);
	}
	for (int i = 0; i < mapCar[level].size(); ++i) {
		file.read(reinterpret_cast<char*>(&x), sizeof(x));
		axh[i]->SetX(x);
	}
	for (int i = 0; i < mapDinausor[level].size(); ++i) {
		file.read(reinterpret_cast<char*>(&x), sizeof(x));
		akl[i]->SetX(x);
	}
	for (int i = 0; i < mapBird[level].size(); ++i) {
		file.read(reinterpret_cast<char*>(&x), sizeof(x));
		ac[i]->SetX(x);
	}
	file.read(reinterpret_cast<char*>(&x), sizeof(x));
	if (x > 0) {
		mTruckTrafficLight.SetRedLight();
	}
	file.read(reinterpret_cast<char*>(&x), sizeof(x));
	mTruckTrafficLight.SetTime(x);
	file.read(reinterpret_cast<char*>(&x), sizeof(x));
	if (x > 0) {
		mCarTrafficLight.SetRedLight();
	}
	file.read(reinterpret_cast<char*>(&x), sizeof(x));
	mCarTrafficLight.SetTime(x);
	file.close();
	drawGame();
}

void CGAME::saveGame(string fileName) {
	fstream file;
	file.open(fileName, ios::out | ios::binary);
	file.write(reinterpret_cast<char*>(&level), sizeof(level));
	int x = cn->GetX(), y = cn->GetY();
	file.write(reinterpret_cast<char*>(&x), sizeof(x));
	file.write(reinterpret_cast<char*>(&y), sizeof(y));
	for (int i = 0; /*axt[i]->isInGame()*/ i < mapTruck[level].size(); ++i) {
		int x = axt[i]->GetX();
		file.write(reinterpret_cast<char*>(&x), sizeof(x));
	}
	for (int i = 0; /*axh[i]->isInGame()*/ i < mapCar[level].size(); ++i) {
		int x = axh[i]->GetX();
		file.write(reinterpret_cast<char*>(&x), sizeof(x));
	}
	for (int i = 0; akl[i]->isInGame(); ++i) {
		int x = akl[i]->GetX();
		file.write(reinterpret_cast<char*>(&x), sizeof(x));
	}
	for (int i = 0; ac[i]->isInGame(); ++i) {
		int x = ac[i]->GetX();
		file.write(reinterpret_cast<char*>(&x), sizeof(x));
	}
	x = mTruckTrafficLight.isRedLight();
	file.write(reinterpret_cast<char*>(&x), sizeof(x));
	x = mTruckTrafficLight.GetTime();
	file.write(reinterpret_cast<char*>(&x), sizeof(x));
	x = mCarTrafficLight.isRedLight();
	file.write(reinterpret_cast<char*>(&x), sizeof(x));
	x = mCarTrafficLight.GetTime();
	file.write(reinterpret_cast<char*>(&x), sizeof(x));
	//file.open(fileName, ios::out);
	//file << level << "\n";
	//for (int i = 0; axt[i]->isInGame() /*i < mapTruck[level].size()*/; ++i) {
	//	file << axt[i]->GetX() << " ";
	//}
	//file << "\n";
	//for (int i = 0; axh[i]->isInGame() /*i < mapTruck[level].size()*/; ++i) {
	//	file << axh[i]->GetX() << " ";
	//}
	file.close();
}

void CGAME::pauseGame(HANDLE h) {
	SuspendThread(h);
}

void CGAME::resumeGame(HANDLE h) {
	ResumeThread(h);
}

void CGAME::updatePosPeople(char move) {
	switch (move)
	{
	case 'W':
		cn->Up(1);
		break;
	case 'S':
		cn->Down(1);
		break;
	case 'A':
		cn->Left(1);
		break;
	case 'D':
		cn->Right(1);
		break;
	default:
		break;
	}
}

void CGAME::updatePosVehicle() {
	if (!mTruckTrafficLight.isRedLight()) {
		for (int i = 0; axt[i]->isInGame(); ++i) {
			axt[i]->Move(-1, 0);
		}
	}
	
	if (!mCarTrafficLight.isRedLight()) {
		for (int i = 0; axh[i]->isInGame(); ++i) {
			axh[i]->Move(1, 0);
		}
	}
}

void CGAME::updatePosAnimal() {
	for (int i = 0; akl[i]->isInGame(); ++i) {
		akl[i]->Move(1, 0);
	}
	for (int i = 0; ac[i]->isInGame(); ++i) {
		ac[i]->Move(-1, 0);
	}
}
