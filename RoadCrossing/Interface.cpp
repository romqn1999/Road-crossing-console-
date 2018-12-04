#include "Interface.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(int x, int y) {
	x += 40; y += 5;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GotoConsoleXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowConsoleCursor(const bool &choose) {
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	cursor.bVisible = choose;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

// We could use a template here, making it more generic. Wide streams won't
// work with this version.
basic_ostream<char> &operator<<(basic_ostream<char> &s, const setcolour &ref)
{
	SetConsoleTextAttribute(ref._console_handle, ref._c);
	return s;
}

void BackgroundMusic() {
	PlaySound(TEXT("PatakasWorld.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void SetText(string text, const int &x, const int &y) {
	HANDLE chandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GotoXY(x, y);
	cout << setcolour(WHITE, chandle) << text;
}

void Choose(const int &x, const int &y) {
	GotoXY(x, y);
	cout << (char)175;
}

void DrawGrid(const int &numRow, const int& numCol, const int &widthCell, const int&heightCell, const int &x, const int &y) {
	HANDLE chandle = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << setcolour(WHITE, chandle);

	GotoXY(x, y);
	cout << (char)218;
	GotoXY(x + 1, y);
	for (int i = 1; i < (widthCell + 1) * numCol; ++i) {
		cout << (char)196;
	}
	GotoXY(x + (widthCell + 1) * numCol, y);
	cout << (char)191;

	for (int i = 1; i < (heightCell + 1) * numRow; ++i) {
		GotoXY(x, y + i);
		cout << (char)179;
		GotoXY(x + (widthCell + 1) * numCol, y + i);
		cout << (char)179;
	}

	GotoXY(x, y + (heightCell + 1) * numRow);
	cout << (char)192;
	for (int i = 1; i < (widthCell + 1) * numCol; ++i) {
		GotoXY(x + i, y + (heightCell + 1) * numRow);
		cout << (char)196;
	}
	GotoXY(x + (widthCell + 1) * numCol, y + (heightCell + 1) * numRow);
	cout << (char)217;

	for (int i = 1; i < numCol; ++i) {
		GotoXY(x + (widthCell + 1) * i, y);
		cout << (char)194;
		GotoXY(x + (widthCell + 1) * i, y + (heightCell + 1) * numRow);
		cout << (char)193;
	}

	for (int i = 1; i < numRow; ++i) {
		GotoXY(x, y + (heightCell + 1) * i);
		cout << (char)195;
		GotoXY(x + (widthCell + 1) * numCol, y + (heightCell + 1) * i);
		cout << (char)180;
	}

	for (int i = 1; i < numRow; ++i) {
		for (int j = 1; j < numCol; ++j) {
			GotoXY(x + (widthCell + 1) * j, y + (heightCell + 1) * i);
			cout << (char)197;
		}
	}

	for (int i = 1; i < numRow; ++i) {
		for (int j = 1; j <= numCol; ++j) {
			for (int k = 1; k <= widthCell; ++k) {
				GotoXY(x + (widthCell + 1) * (j - 1) + k, y + (heightCell + 1) * i);
				cout << (char)196;
			}
		}
	}

	for (int i = 1; i <= numRow; ++i) {
		for (int j = 1; j < numCol; ++j) {
			for (int k = 1; k <= heightCell; ++k) {
				GotoXY(x + (widthCell + 1) * j, y + (heightCell + 1) * (i - 1) + k);
				cout << (char)179;
			}
		}
	}
}

void ButtonOnCol(vector<string> text, const int &widthBtn, const int &heightBtn, const int &x, const int &y) {
	DrawGrid(text.size(), 1, widthBtn, heightBtn, x, y);
	for (int i = 0; i < text.size(); ++i) {
		SetText(text[i], x + 2, y + (heightBtn + 1) * i + 1);
	}
}

void ButtonOnRow(vector<string> text, const int &widthBtn, const int &heightBtn, const int &x, const int &y) {
	DrawGrid(1, text.size(), widthBtn, heightBtn, x, y);
	for (int i = 0; i < text.size(); ++i) {
		SetText(text[i], x +(widthBtn + 1) * i + 2, y + 1);
	}
}

int GetChoiceBtnOnCol(const int &x0, const int &y0, const int &numCol) {
	int x = x0 + 1, y = y0 + 1, i = 1;
	GotoXY(x, y);
	Choose(x, y);
	while (_getch() != 13) {
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case 72:
				if (/*x0 < x - 2 && x - 2 < x0 + numCol * 2*/0 < i - 1 && i - 1 <= numCol) {
					GotoXY(x, y); cout << ' ';
					Choose(x, y -= 2);
					--i;
				}
				break;
			case 80:
				if (/*x0 < x + 2 && x + 2 < x0 + numCol * 2*/0 < i + 1 && i + 1 <= numCol) {
					GotoXY(x, y); cout << ' ';
					Choose(x, y += 2);
					++i;
				}
				break;
			}
		}
	}
	system("cls");
	return i;
}

int GetChoiceBtnOnRow(const int &x0, const int &y0, const int &numCol) {
	int x = x0 + 1, y = y0 + 1, i = 1;
	GotoXY(x, y);
	Choose(x, y);
	while (_getch() != 13) {
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case (72 || 80):
				return i;
				break;
			case 75:
				if (/*x0 < x - 2 && x - 2 < x0 + numCol * 2*/0 < i - 1 && i - 1 <= numCol) {
					GotoXY(x, y); cout << ' ';
					Choose(x -= 2, y);
					--i;
				}
				break;
			case 77:
				if (/*x0 < x + 2 && x + 2 < x0 + numCol * 2*/0 < i + 1 && i + 1 <= numCol) {
					GotoXY(x, y); cout << ' ';
					Choose(x += 2, y);
					++i;
				}
				break;
			}
		}
	}
	//system("cls");
	return i;
}

void MainMenu() {
	system("cls");
	SetConsoleTitle("Road Crossing");

	GotoConsoleXY(37, 0);  cout << "  ________";
	GotoConsoleXY(37, 1);  cout << " /  ____  \\                               __";
	GotoConsoleXY(37, 2);  cout << "/  /    \\  \\                             |  |";
	GotoConsoleXY(37, 3);  cout << "|  \\____/  /                             |  |";
	GotoConsoleXY(37, 4);  cout << "|   ___   /     _____     ______      ___|  |";
	GotoConsoleXY(37, 5);  cout << "|  |   \\  \\    /  _  \\   /  _   \\    /  _   |";
	GotoConsoleXY(37, 6);  cout << "|  |    \\  \\  |  |_|  | |  |_|   \\  |  |_|  |";
	GotoConsoleXY(37, 7);  cout << "|__|     \\__\\  \\_____/   \\_____/\\_\\  \\_____/";
	GotoConsoleXY(24, 8);  cout << "   ________";
	GotoConsoleXY(24, 9);  cout << "  /  ____  \\";
	GotoConsoleXY(24, 10); cout << " /  /    \\__\\                                    _";
	GotoConsoleXY(24, 11); cout << "|  |                                            |_|";
	GotoConsoleXY(24, 12); cout << "|  |           ______    _____     ____   ____   _    ______    _____";
	GotoConsoleXY(24, 13); cout << "|  |      ___ /   ___\\  /  _  \\   /  __| /  __| / \\  /  __  \\  /  _  \\";
	GotoConsoleXY(24, 14); cout << " \\  \\____/  / |  |     |  |_|  | _\\  \\  _\\  \\   | |  | |  | | |  |_|  |";
	GotoConsoleXY(24, 15); cout << "  \\________/  \\__/      \\_____/ |____/ |____/   \\_/  |_|  |_|  \\___   |";
	GotoConsoleXY(24, 16); cout << "                                                               ___ |  |";
	GotoConsoleXY(24, 17); cout << "                                                               \\  \\/  |";
	GotoConsoleXY(24, 18); cout << "                                                                \\____/";

	vector<string> textBtn;
	textBtn.push_back("NEW GAME");
	textBtn.push_back("LOAD GAME");
	textBtn.push_back("SETTING");
	textBtn.push_back("EXIT");
	ButtonOnCol(textBtn, 12, 1, 14, 14);
}

int GetChoiceMainMenu() {
	int c = GetChoiceBtnOnCol(14, 14, 4);
	return c;
}

void GameOverMenu() {
	system("cls");
	string text = "GAME OVER! Retry?";
	SetText(text, 10, 6);
	vector<string> textBtn;
	textBtn.push_back("Yes");
	textBtn.push_back("No");
	ButtonOnCol(textBtn, 5, 1, 15, 8);
	Choose(16, 9);
}

int GetChoiceGameOver() {
	return GetChoiceBtnOnCol(15, 8, 2);
}

int upCaseSymbol(int c) {
	switch (c)
	{
	case 195:
		return 199;
	case 197:
		return 215;
	case 180:
		return 182;
	default:
		return c;
		break;
	}
}

int lowCaseSymbol(int c) {
	switch (c)
	{
	case 199:
		return 195;
	case 215:
		return 197;
	case 182:
		return 180;
	default:
		return c;
		break;
	}
}

void SettingMenu() {
	system("cls");
	string text = "Setting";
	SetText(text, 15, 6);

	text = "Level ";
	text += (char)195;
	text += (char)196; text += (char)196; text += (char)196; text += (char)196; text += (char)196;
	text += (char)197;
	text += (char)196; text += (char)196; text += (char)196; text += (char)196; text += (char)196;
	text += (char)180;
	SetText(text, 10, 8);

	text = "Sound ";
	SetText(text, 10, 10);
	vector<string> textBtn;
	textBtn.push_back("On");
	textBtn.push_back("Off");
	ButtonOnRow(textBtn, 5, 1, 16, 9);

	textBtn.clear();
	textBtn.push_back("Save");
	textBtn.push_back("Cancel");
	ButtonOnRow(textBtn, 7, 1, 10, 12);
}

void print(vector<int> strlevel, int x, int y) {
	GotoXY(x, y);
	for (int i = 0; i < strlevel.size(); ++i) {
		if (strlevel[i] == 199 || strlevel[i] == 215 || strlevel[i] == 182) cout << (char)219; else
		cout << (char)strlevel[i];
	}
}

int GetChoiceSettingMenu(int &mlevel, int &moffSound) {
	Choose(9, 8);
	//return GetChoiceBtnOnCol(15, 8, 2);
	int x = 9, y = 8, i = 1, level = mlevel, offSound = moffSound, j = 1;
	vector<int> strlevel;
	strlevel.push_back(195);
	strlevel.push_back(196); strlevel.push_back(196); strlevel.push_back(196); strlevel.push_back(196); strlevel.push_back(196);
	strlevel.push_back(197);
	strlevel.push_back(196); strlevel.push_back(196); strlevel.push_back(196); strlevel.push_back(196); strlevel.push_back(196);
	strlevel.push_back(180);
	strlevel[6 * level] = upCaseSymbol(strlevel[6 * level]);
	print(strlevel, 16, 8);
	if (!offSound) Choose(17, 10); else Choose(23, 10);
	while (true) {
		//if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case 13:
				if (i == 3) {
					if (j == 1) {
						mlevel = level;
						moffSound = offSound;
						return 1;
					}
					else if (j == 2) {
						return 0;
					}
				}
			case 27:
				return 0;
			case 75:
				if (i == 1) {
					if (0 <= level - 1 && level - 1 < CONSTANT::MAXLEVEL) {
						strlevel[6 * level] = lowCaseSymbol(strlevel[6 * level]);
						--level;
						strlevel[6 * level] = upCaseSymbol(strlevel[6 * level]);
						//GotoXY(16, 8); cout << strlevel;
						print(strlevel, 16, 8);
					}
				}
				else if (i == 2) {
					if (offSound) {
						GotoXY(23, 10); cout << ' ';
						Choose(17, 10);
						offSound = 0;
					}
				}
				else if (i == 3) {
					if (0 < j - 1 && j - 1 <= 2) {
						GotoXY(x, y); cout << ' ';
						Choose(x = 11, y = 13);
						--j;
					}
				}
				break;
			case 77:
				if (i == 1) {
					if (0 <= level + 1 && level + 1 < CONSTANT::MAXLEVEL) {
						strlevel[6 * level] = lowCaseSymbol(strlevel[6 * level]);
						++level;
						strlevel[6 * level] = upCaseSymbol(strlevel[6 * level]);
						//GotoXY(16, 8); cout << strlevel;
						print(strlevel, 16, 8);
					}
				}
				else if (i == 2) {
					if (!offSound) {
						GotoXY(17, 10); cout << ' ';
						Choose(23, 10);
						offSound = 1;
					}
				}
				else if (i == 3) {
					if (0 < j + 1 && j + 1 <= 2) {
						GotoXY(x, y); cout << ' ';
						Choose(x = 19, y = 13);
						++j;
					}
				}
				break;
			case 72:
				if (0 < i - 1 && i - 1 <= 3) {
					GotoXY(x, y); cout << ' ';
					--i;
					if (i == 1) {
						Choose(x = 9, y = 8);
					}
					else if (i == 2) {
						Choose(x = 9, y = 10);
					}
				}
				break;
			case 80:
				if (0 < i + 1 && i + 1 <= 3) {
					GotoXY(x, y); cout << ' ';
					++i;
					if (i == 1) {
						Choose(x = 9, y = 8);
					}
					else if (i == 2) {
						Choose(x = 9, y = 10);
					}
					else if (i == 3) {
						Choose(x = 11, y = 13);
					}
				}
				break;
			}
		//}
	}
	return 1;
}

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress(double percentage, int x, int y)
{
	GotoXY(x, y);
	int val = (int)(percentage * 100);
	int lpad = (int)(percentage * PBWIDTH);
	int rpad = PBWIDTH - lpad;
	printf("%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
	fflush(stdout);
}

void DrawLoading(int x, int y) {
	system("cls");
	//GotoXY(x + 30, y);
	SetText("Loading", x + 30, y);
	for (int i = 0; i <= 100; ++i) {
		printProgress(i / 100.0, x, y + 2);
		Sleep(10);
	}
	system("cls");
}