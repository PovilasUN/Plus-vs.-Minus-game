#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

bool GameOver = false;

char map[25][80] = {
  "                                                                               ",
  "|                                                                             |",
  "|    +++           +++              +++               +++               +++   |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|           +++             +++              +++              +++             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|    +++           +++              +++               +++               +++   |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                                                             |",
  "|                                    ---                                      |",
};

void showConsoleCursor(bool flag)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = flag;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void cls()
{
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Messages
{
private:
	int Score;
	int Lives;
	int EnemyCount;
	char Key;
public:
	void operator ++()
	{
		showConsoleCursor(false);
		cout << "\t\t\t\tPLUS VS. MINUS!" << endl;
		Sleep(2500);
		system("cls");
		cout << "\t\t\t\tPRESS 'S' TO START!" << endl;
		Key = _getch();
		Sleep(250);
	}
	void EndGameMessage(int Score, int Lives, int EnemyCount)
	{
		if (Lives > 0 && EnemyCount == 0)
		{
			cout << "\n\n\n\t\t\tWell Played!\n\n";
			cout << "\n\n\n\t\t\t\t\t\tYour Score is : " << Score << "\n\n\n\n";
		}
		else
		{
			cout << "\n\n\n\n\t\t\tBetter Luck Next Time!\n\n";
			cout << "\n\n\n\n\t\t\t\t\t\tYour Score is : " << Score << "\n\n\n";
		}
	}
};

class Character
{
protected:
	char Symbol;
	char Laser;
public:
	Character() :Symbol(0), Laser(0) {}
	Character(char a, char b) : Symbol(a), Laser(b) {}
	~Character() {}
	char SymbolPlayer()
	{
		return Symbol = '-';
	}
	char SymbolEnemy()
	{
		return Symbol = '+';
	}
	char PlayerLaser()
	{
		return Laser = '^';
	}
	char EnemyLaser()
	{
		return Laser = '*';
	}
};

class Enemy : public Character
{
public:
	char direction = 'l';
	int EnemyReady;
	int EnemyDrop;
	int EnemyCount = 14;
	void EnemyMovement()
	{
		EnemyDrop = 0;
		for (int y = 0; y < 25 - 1; y++)
		{
			if ((map[y][2] == SymbolEnemy() && map[y][3] == SymbolEnemy() && map[y][4] == SymbolEnemy()))
			{
				direction = 'r';
				EnemyDrop = 1;
				break;
			}
			if ((map[y][80 - 3] == SymbolEnemy() && map[y][80 - 4] == SymbolEnemy() && map[y][80 - 5] == SymbolEnemy()))
			{
				direction = 'l';
				EnemyDrop = 1;
				break;
			}
		}
		if (rand() % 13 == 3)
		{
			if (direction == 'l')
			{
				for (int x = 2; x <= 80 - 3; x++)
				{
					for (int y = 0; y < 25; y++)
					{
						if (EnemyDrop && ((map[y - 1][x + 1] == SymbolEnemy() && map[y - 1][x + 2] == SymbolEnemy() && map[y - 1][x + 3] == SymbolEnemy())))
						{
							map[y][x] = map[y - 1][x + 1];
							map[y][x + 1] = map[y - 1][x + 2];
							map[y][x + 2] = map[y - 1][x + 3];
							map[y - 1][x + 1] = ' ';
							map[y - 1][x + 2] = ' ';
							map[y - 1][x + 3] = ' ';
						}
						else if (!EnemyDrop && ((map[y][x + 1] == SymbolEnemy() && map[y][x + 2] == SymbolEnemy() && map[y][x + 3] == SymbolEnemy())))
						{
							map[y][x + 2] = map[y][x + 3];
							map[y][x + 1] = map[y][x + 2];
							map[y][x] = map[y][x + 1];
							map[y][x + 3] = ' ';
						}
					}
				}
			}
			else if (direction == 'r')
			{
				for (int x = 80 - 3; x >= 2; x--)
				{
					for (int y = 0; y < 25; y++)
					{
						if (EnemyDrop && ((map[y - 1][x - 1] == SymbolEnemy() && map[y - 1][x - 2] == SymbolEnemy() && map[y - 1][x - 3] == SymbolEnemy())))
						{
							map[y][x - 2] = map[y - 1][x - 3];
							map[y][x - 1] = map[y - 1][x - 2];
							map[y][x] = map[y - 1][x - 1];
							map[y - 1][x - 1] = ' ';
							map[y - 1][x - 2] = ' ';
							map[y - 1][x - 3] = ' ';
						}
						else if (!EnemyDrop && ((map[y][x - 1] == SymbolEnemy() && map[y][x - 2] == SymbolEnemy() && map[y][x - 3] == SymbolEnemy())))
						{
							map[y][x] = map[y][x - 1];
							map[y][x - 2] = map[y][x - 3];
							map[y][x - 1] = map[y][x - 2];
							map[y][x - 3] = ' ';
						}
					}
				}
			}
		}
		for (int x = 2; x < 80 - 2; x++)
		{
			if (map[25 - 1][x] == SymbolEnemy())
			{
				GameOver = true;
			}
		}
	}
	void Shooting(int &x, int &y)
	{
		for (int H = y + 1; H < 25; H++)
		{
			if (map[H][x] == SymbolEnemy())
			{
				EnemyReady = 0;
				break;
			}
			EnemyReady = 1;
		}
		if (EnemyReady == 1)
		{
			map[y + 1][x + 1] = EnemyLaser();
		}
	}
	void LaserCancelled(int& x, int& y)
	{
		map[y][x] = ' ';
		map[y + 1][x] = ' ';
	}
	void MoveLaser(int& x, int& y)
	{
		map[y + 1][x] = EnemyLaser();
		map[y][x] = ' ';
	}
	void GotHit(int& x, int& y)
	{
		map[y][x] = ' ';
		map[y - 1][x] = ' ';
		map[y - 1][x + 1] = ' ';
		map[y - 1][x + 2] = ' ';
		map[y - 1][x - 1] = ' ';
		map[y - 1][x - 2] = ' ';
		EnemyCount--;
	}
};

class Player :public Character
{
public:
	char KEY = NULL;
	int Score = 0;
	int LReady = 1;
	int Lives = 1;
	int PlayerShapeControl = 0;
	void PlayerMovement()
	{
		LReady++;
		KEY = NULL;
		if (_kbhit() != 0)
		{
			KEY = _getch();
		}
		if (KEY == 'a' || KEY == 'A')
		{
			for (int x = 2; x < 80 - 2; x++)
			{
				if (map[25 - 1][x] == SymbolPlayer() && map[25 - 1][x + 1] == SymbolPlayer() && map[25 - 1][x + 2] == SymbolPlayer())
				{
					map[25 - 1][x - 1] = SymbolPlayer();
					map[25 - 1][x] = SymbolPlayer();
					map[25 - 1][x + 1] = SymbolPlayer();
					map[25 - 1][x + 2] = ' ';
					PlayerShapeControl = PlayerShapeControl - 10;
					break;
				}
			}
		}
		if (KEY == 'd' || KEY == 'D')
		{
			for (int x = 80 - 5; x > 0; x--)
			{
				if (map[25 - 1][x] == SymbolPlayer() && map[25 - 1][x - 1] == SymbolPlayer() && map[25 - 1][x - 2] == SymbolPlayer())
				{
					map[25 - 1][x - 1] = SymbolPlayer();
					map[25 - 1][x] = SymbolPlayer();
					map[25 - 1][x + 1] = SymbolPlayer();
					map[25 - 1][x - 2] = ' ';
					PlayerShapeControl = PlayerShapeControl + 10;
					break;
				}
			}
		}
		if (KEY == ' ' && LReady > 3)
		{
			for (int x = 0; x < 80; x++)
			{
				if (map[25 - 1][x] == SymbolPlayer() && map[25 - 1][x + 1] == SymbolPlayer())
				{
					map[25 - 2][x + 1] = PlayerLaser();
					LReady = 0;
					break;
				}
			}
		}
		if (KEY == 'q' || KEY == 'Q')
		{
			GameOver = true;
		}
	}
	void GotHit(int &x, int &y)
	{
		map[y - 1][x] = ' ';
		GameOver = true;
	}
	void LaserCancelled(int& x, int& y)
	{
		map[y][x] = ' ';
		map[y - 1][x] = ' ';
	}
	void MoveLaser(int& x, int& y)
	{
		map[y][x] = ' ';
		map[y - 1][x] = PlayerLaser();
	}
};

void DisplayWorld(int Score)
{
	for (int y = 1; y < 25; y++)
	{
		gotoxy(20, y);
		cout << map[y] << endl;
	}
	cout << "\t\t\t\tSCORE : " << Score;
}

void LaserControl(Player& P, Enemy& E, int Key)
{
	for (int x = 0; x < 80; x++)
	{
		for (int y = 25 - 1; y > 0; y--)
		{
			if (map[y][x] == E.EnemyLaser() && (map[y + 1][x] == P.PlayerLaser()))
			{
				E.LaserCancelled(x,y);
			}
			else if (map[y][x] == E.EnemyLaser() && (map[y + 1][x] != E.SymbolEnemy()))
			{
				E.MoveLaser(x, y);
			}
			else if (map[y][x] == E.EnemyLaser() && (map[y + 1][x] == E.SymbolEnemy()))
			{
				map[y][x] = ' ';
			}
			else if (map[y][x] == P.SymbolPlayer() && map[y - 1][x] == E.EnemyLaser())
			{
				P.GotHit(x, y);
			}

		}
	}
	for (int x = 0; x < 80; x++)
	{
		for (int y = 0; y < 25; y++)
		{
			if (map[y][x] == P.PlayerLaser() && map[y - 1][x] == E.EnemyLaser())
			{
				P.LaserCancelled(x, y);
			}
			else if (map[y][x] == P.PlayerLaser() && (map[y - 1][x] == E.SymbolEnemy()))
			{
				E.GotHit(x, y);
				P.Score = P.Score + 20;
			}
			else if (GameOver == false)
			{
				if (((map[y][x] == E.SymbolEnemy() && map[y][x + 1] == E.SymbolEnemy() && map[y][x + 2] == E.SymbolEnemy())) && (rand() % 9) == 2 && (rand() % 9) == 5 && map[y + 1][x] != P.PlayerLaser())
				{
					E.Shooting(x, y);
				}
			}
			if (map[y][x] == P.PlayerLaser() && map[y - 1][x] != E.EnemyLaser() && y > 0)
			{
				P.MoveLaser(x, y);
			}
		}
	}
}

int main()
{
	int Key = 0;
	Messages M;
	Enemy E; 
	Player P;
	++M;
	system("cls");
	while (E.EnemyCount > 0 && GameOver == false)
	{
		cls();
		DisplayWorld(P.Score);
		LaserControl(P, E, Key);
		E.EnemyMovement();
		P.PlayerMovement();
		Sleep(50);
	}
	Sleep(500);
	system("cls");
	M.EndGameMessage(P.Score, P.Lives, E.EnemyCount);
	Sleep(3000);
	return 0;
}