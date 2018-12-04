#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include "Config.h"

using namespace std;

void FixConsoleWindow();

void GotoXY(int x, int y); //Dong y, Cot x

void ShowConsoleCursor(const bool &choose);

enum colour { DARKBLUE = 1, DARKGREEN, DARKTEAL, DARKRED, DARKPINK, DARKYELLOW, GRAY, DARKGRAY, BLUE, GREEN, TEAL, RED, PINK, YELLOW, WHITE };

struct setcolour
{
	colour _c;
	HANDLE _console_handle;


	setcolour(colour c, HANDLE console_handle)
		: _c(c), _console_handle(0)
	{
		_console_handle = console_handle;
	}
};

basic_ostream<char> &operator<<(basic_ostream<char> &s, const setcolour &ref);

void BackgroundMusic();

void SetText(string text, const int &x, const int &y);

void Choose(const int &x, const int &y);

void DrawGrid(const int &numRow, const int& numCol, const int &widthCell, const int&heightCell, const int &x, const int &y);

void ButtonOnCol(vector<string> text, const int &widthBtn, const int &heightBtn, const int &x, const int &y);

int GetChoiceBtnOnCol(const int &x0, const int &y0, const int &numCol);

void MainMenu();

int GetChoiceMainMenu();

void GameOverMenu();

int GetChoiceGameOver();

void SettingMenu();

int GetChoiceSettingMenu(int &level, int &offSound);

void DrawLoading(int x, int y);
