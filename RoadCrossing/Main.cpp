#include "Interface.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include "CGAME.h"

using namespace std;

//bool CGAME::IS_RUNNING = true;

char MOVING;
CGAME cg;
mutex myMutex;

//void exitGame(thread* t) {
//	system("cls");
//	CGAME::IS_RUNNING = false;
//	t->join();
//}

void SubThread() {
	//cg.drawGame();
	auto native_me = ::GetCurrentThread();
	while (CGAME::IS_RUNNING)
	{
		myMutex.lock();
		if (!cg.getPeople()->isDead()) {
			cg.updatePosPeople(MOVING); //Cap nhat vi tri nguoi choi theo thong tin tu main
		}
		MOVING = ' '; //Tam khoa khong cho di chuyen, cho nhan phim tu ham main
		cg.updatePosVehicle(); //Cap nhat vi tri xe
		cg.updatePosAnimal(); //Cap nhat vi tri thu
		cg.drawUpdateGame();
		if (cg.getPeople()->isImpact(cg.getVehicle()) || cg.getPeople()->isImpact(cg.getAnimal())) {
			//Xu ly khi dung xe hay thu
			//CGAME::IS_RUNNING = false;
			//cg.resetGame();
			//auto native_me = std::this_thread::get_id().native_handle();
			//cout << "impact";
			PlaySound(TEXT("Accident.wav"), NULL, SND_FILENAME | SND_ASYNC);
			for (int i = 0; i < 15; ++i) {
				GotoXY(cg.getPeople()->GetX(), cg.getPeople()->GetY() - 1);
				HANDLE chandle = GetStdHandle(STD_OUTPUT_HANDLE);
				cout << setcolour(RED, chandle) << (char)206;
				Sleep(100);
				GotoXY(cg.getPeople()->GetX(), cg.getPeople()->GetY() - 1);
				cout << (char)0;
				Sleep(50);
				cout << setcolour(WHITE, chandle);
			}
			//Sleep(4000);
			GameOverMenu();
			if (CGAME::IS_ONSOUND) {
				BackgroundMusic();
			}
			cg.pauseGame(native_me);
		}
		if (cg.getPeople()->isFinish()) {
			//Xu ly khi ve dich
			//cout << "finish";
			cg.levelUp();
		}
		myMutex.unlock();
		Sleep(100);
	}
	
}

int main() {
	int temp;
	string fileName;
	FixConsoleWindow();
	ShowConsoleCursor(false);
	if (CGAME::IS_ONSOUND) {
		BackgroundMusic();
	}
	CGAME::IS_RUNNING = false;
	while (!CGAME::IS_RUNNING)
	{
		MainMenu();
		int level = cg.getLevel(), offSound = !cg.IS_ONSOUND;
		switch (GetChoiceMainMenu()) {
		case 1: //New game
			DrawLoading(-15, 1);
			cg.drawGame();
			CGAME::IS_RUNNING = true;
			break;
		case 2: //Load game
			SetText("Load game", 15, 3);
			SetText("Enter \"back\" to back to previous screen.", 5, 7);
			GotoXY(5, 5);
			cout << "Enter file name: ";
			//cin >> fileName;
			ShowConsoleCursor(true);
			getline(cin, fileName);
			ShowConsoleCursor(false);
			if (fileName != "back") {
				DrawLoading(-15, 1);
				cg.loadGame(fileName);
				CGAME::IS_RUNNING = true;
			}
			break;
		case 3: //Setting
			SettingMenu();
			if (GetChoiceSettingMenu(level, offSound)) {
				if (offSound) {
					cg.trunOffSound();
				}
				else {
					cg.trunOnSound();
				}
				cg.setLevel(level);
			}
			break;
		case 4: //Exit
			return 0;
			break;
		default:
			break;
		}
	}
	cg.startGame();
	thread t1(SubThread);
	while (true)
	{
		temp = toupper(_getch());
		if (temp == 'L') {
			cg.pauseGame(t1.native_handle());
			system("cls");
			SetText("Save game", 15, 3);
			SetText("Enter \"back\" to back to previous screen.", 5, 7);
			GotoXY(5, 5);
			cout << "Enter file name: ";
			//cin >> fileName;
			ShowConsoleCursor(true);
			getline(cin, fileName);
			ShowConsoleCursor(false);
			if (fileName != "back") {
				cg.saveGame(fileName);
				CGAME::IS_RUNNING = true;
			}
			cg.resumeGame((HANDLE)t1.native_handle());
			myMutex.lock();
			system("cls");
			cg.drawGame();
			myMutex.unlock();
			continue;
		}
		else if (temp == 'T') {
			cg.pauseGame(t1.native_handle());
			system("cls");
			SetText("Load game", 15, 3);
			SetText("Enter \"back\" to back to previous screen.", 5, 7);
			GotoXY(5, 5);
			cout << "Enter file name: ";
			//cin >> fileName;
			ShowConsoleCursor(true);
			getline(cin, fileName);
			ShowConsoleCursor(false);
			if (fileName != "back") {
				cg.loadGame(fileName);
				CGAME::IS_RUNNING = true;
			}
			cg.resumeGame((HANDLE)t1.native_handle());
			myMutex.lock();
			system("cls");
			cg.drawGame();
			myMutex.unlock();
			continue;
		}
		else if (temp == 'C') {
			cg.pauseGame(t1.native_handle());
			system("cls");
			SettingMenu();
			int level = cg.getLevel(), offSound = !cg.IS_ONSOUND;
			if (GetChoiceSettingMenu(level, offSound)) {
				if (offSound) {
					cg.trunOffSound();
				}
				else {
					cg.trunOnSound();
				}
				cg.setLevel(level);
			}
			cg.resumeGame((HANDLE)t1.native_handle());
			myMutex.lock();
			system("cls");
			cg.drawGame();
			myMutex.unlock();
			continue;
		}
		if (!cg.getPeople()->isDead()) {
			if (temp == 27) {
				cg.exitGame(t1.native_handle());
				break;
				/*if (t1.joinable()) {
					t1.join();
				}
				return 0;*/
			}
			else if (temp == 'P') {
				cg.pauseGame(t1.native_handle());
			}
			else {
				cg.resumeGame((HANDLE)t1.native_handle());
				myMutex.lock();
				MOVING = temp;
				//if (!cg.getPeople()->isDead()) {
				//	cg.updatePosPeople(MOVING); //Cap nhat vi tri nguoi choi theo thong tin tu main
				//}
				myMutex.unlock();
			}
		}
		else {
			if (/*temp == 'Y'*/GetChoiceGameOver() == 1) {
				//cg.startGame();
				cg.resetGame();
				CGAME::IS_RUNNING = true;
				cg.resumeGame((HANDLE)t1.native_handle());
			}
			else {
				cg.resumeGame((HANDLE)t1.native_handle());
				cg.exitGame(t1.native_handle());
				/*if (t1.joinable()) {
					t1.join();
				}
				return 0;*/
				break;
			}
		}
	}
	if (t1.joinable()) {
		t1.join();
	}
	
	return 0;
}
