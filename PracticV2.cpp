#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

#define SIZE_Board 8 //размер шахматных полей
#define WPeshka -1
#define BPeshka 1
#define WBashenka -2 
#define BBashenka 2
#define WHorse -3
#define BHorse 3
#define WOficer -4
#define BOficer 4
#define WQueen -5
#define BQueen 5
#define WKing -6
#define BKing 6

//структура для записи позиций
struct poz
{
	int x, y;
}oldPoz, wking, bking, Wtransform, Btransform;

int  size = 100, move = 0, x, y;
//Расположение шахмат на доске
int board[8][8] =
{ 2, 3, 4, 5, 6, 4, 3, 2,
  1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, -1, 0, 0,
 -1,-1,-1,-1,-1,-1,-1,-1,
 -2,-3,-4,-5,-6,-4,-3,-2, };

int mutare = 0; // 0 - ход белых, 1 - ход черных
int transformareW = 0, transformareB = 0;

int PeshkaW(int ox, int oy, int nx, int ny)
{
	if (oldPoz.y == 6)
	{
		if ((ny == oy - 1 && nx == ox && board[oy - 1][ox] == 0) || (ny == oy - 2 && nx == ox && board[oy - 1][ox] == 0 && board[oy - 2][ox] == 0)) // можно ли походить вперед с нулевого места (1 вперед или 2 вперед)
		{
			return 1;
		}
	}
	else if (ny == oy - 1 && nx == ox && board[oy - 1][ox] == 0) // обычный ход (на 1) вперед с любой другой позиции кроме стандартной
	{
		return 1;
	}
	if (board[oy - 1][ox - 1] > 0) // бить шахмату чуть ниже и левее от пешки
	{
		if (ny == oy - 1 && nx == ox - 1)
		{
			return 1;
		}
	}
	if (board[oy - 1][ox + 1] > 0) // бить шахмату чуть ниже и правее от пешки
	{
		if (ny == oy - 1 && nx == ox + 1)
		{
			return 1;
		}
	}
	return 0;
}

int PeshkaB(int ox, int oy, int nx, int ny)
{
	if (oldPoz.y == 1)
	{
		if ((ny == oy + 1 && nx == ox && board[oy + 1][ox] == 0) || (ny == oy + 2 && nx == ox && board[oy + 1][ox] == 0 && board[oy + 2][ox] == 0)) // можно ли походить вперед с нулевого места (1 вперед или 2 вперед)
		{
			return 1;
		}
	}
	else if (ny == oy + 1 && nx == ox && board[oy + 1][ox] == 0) // обычный ход (на 1) вперед с любой другой позиции кроме стандартной
	{
		return 1;
	}
	if (board[oy + 1][ox - 1] < 0) // бить шахмату чуть выше и левее от пешки
	{
		if (ny == oy + 1 && nx == ox - 1)
		{
			return 1;
		}
	}
	if (board[oy + 1][ox + 1] < 0) // бить шахмату чуть выше и правее от пешки
	{
		if (ny == oy + 1 && nx == ox + 1)
		{
			return 1;
		}
	}
	return 0;
}

///...
/// [1]
/// ...


int main()
{
	RenderWindow window(VideoMode(800, 800), L"Шахматы", sf::Style::Close | sf::Style::Titlebar);//Размер,название,запрет возможности изменять размер окна
	//Иконка окна
	Image icon;
	if (!icon.loadFromFile("images/icon.png"))
	{
		return 1;
	}
	window.setIcon(300, 300, icon.getPixelsPtr());

	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13;
	t1.loadFromFile("images/board.png");
	t2.loadFromFile("images/WPeshka.png");
	t3.loadFromFile("images/BPeshka.png");
	t4.loadFromFile("images/WBashenka.png");
	t5.loadFromFile("images/BBashenka.png");
	t6.loadFromFile("images/WHorse.png");
	t7.loadFromFile("images/BHorse.png");
	t8.loadFromFile("images/WOficer.png");
	t9.loadFromFile("images/BOficer.png");
	t10.loadFromFile("images/WQueen.png");
	t11.loadFromFile("images/BQueen.png");
	t12.loadFromFile("images/WKing.png");
	t13.loadFromFile("images/BKing.png");
	
	Sprite tabla(t1);
	Sprite wPeshka(t2);
	Sprite bPeshka(t3);
	Sprite wBashenka(t4);
	Sprite bBashenka(t5);
	Sprite wHorse(t6);
	Sprite bHorse(t7);
	Sprite wOficer(t8);
	Sprite bOficer(t9);
	Sprite wQueen(t10);
	Sprite bQueen(t11);
	Sprite wKing(t12);
	Sprite bKing(t13);
	Sprite Mutare;

	float dx = 0, dy = 0;
	int MovingPartNumber = 0;

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
		x = pos.x / size;
		y = pos.y / size;
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			window.clear();
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{					
					if (board[y][x] != 0)
					{
						dx = pos.x - x * 100;
						dy = pos.y - y * 100;
						if (board[y][x] == BPeshka && mutare == 1)
						{
							MovingPartNumber = BPeshka;
							Mutare = bPeshka;
							board[y][x] = 0;
						}
						if (board[y][x] == WPeshka && mutare == 0)
						{
							MovingPartNumber = WPeshka;
							Mutare = wPeshka;
							board[y][x] = 0;
						}
						if (board[y][x] == BBashenka && mutare == 1)
						{
							MovingPartNumber = BBashenka;
							Mutare = bBashenka;
							board[y][x] = 0;

						}
						if (board[y][x] == WBashenka && mutare == 0)
						{
							MovingPartNumber = WBashenka;
							Mutare = wBashenka;
							board[y][x] = 0;

						}
						if (board[y][x] == WHorse && mutare == 0)
						{
							MovingPartNumber = WHorse;
							Mutare = wHorse;
							board[y][x] = 0;
						}
						if (board[y][x] == BHorse && mutare == 1)
						{
							MovingPartNumber = BHorse;
							Mutare = bHorse;
							board[y][x] = 0;
						}
						if (board[y][x] == BOficer && mutare == 1)
						{
							MovingPartNumber = BOficer;
							Mutare = bOficer;
							board[y][x] = 0;
						}
						if (board[y][x] == WOficer && mutare == 0)
						{
							MovingPartNumber = WOficer;
							Mutare = wOficer;
							board[y][x] = 0;
						}
						if (board[y][x] == WQueen && mutare == 0)
						{
							MovingPartNumber = WQueen;
							Mutare = wQueen;
							board[y][x] = 0;
						}
						if (board[y][x] == BQueen && mutare == 1)
						{
							MovingPartNumber = BQueen;
							Mutare = bQueen;
							board[y][x] = 0;
						}
						if (board[y][x] == BKing && mutare == 1)
						{
							MovingPartNumber = BKing;
							Mutare = bKing;
							board[y][x] = 0;
						}
						if (board[y][x] == WKing && mutare == 0)
						{
							MovingPartNumber = WKing;
							Mutare = wKing;
							board[y][x] = 0;
						}
						if (board[y][x] == 0)
						{
							move = 1;
							oldPoz.x = x;
							oldPoz.y = y;
						}
					}
				}
			}
			if (e.type == Event::MouseButtonReleased)
			{
				if (e.key.code == Mouse::Left)
				{
					int ok = 2;
					if (MovingPartNumber == WPeshka && move == 1)
					{
						ok = PeshkaW(oldPoz.x, oldPoz.y, x, y);
					}
					if (MovingPartNumber == BPeshka && move == 1)
					{
						ok = PeshkaB(oldPoz.x, oldPoz.y, x, y);
					}
					
					if (ok == 1)
					{
						int nr = board[y][x];
						board[y][x] = MovingPartNumber;
						if (y == 0 && MovingPartNumber == WPeshka)
						{
							transformareW = 1;
							Wtransform.x = x;
							Wtransform.y = y;
							board[y][x] = 0;
						}
						if (y == 7 && MovingPartNumber == BPeshka)
						{
							transformareB = 1;
							Btransform.x = x;
							Btransform.y = y;
							board[y][x] = 0;
						}

						/// ...
						/// [2]
						/// ... 
						
					}
					else if (ok == 0)
					{
						board[oldPoz.y][oldPoz.x] = MovingPartNumber;
					}
					move = 0;
				}
			}
		}
		// Отображение
		window.clear();
		window.draw(tabla);
		
		if (move == 1)
		{
			Mutare.setPosition(pos.x - dx, pos.y - dy);
			window.draw(Mutare);
		}
		for (int i = 0; i < SIZE_Board; i++)
		{
			for (int j = 0; j < SIZE_Board; j++)
			{

				if (board[i][j] != 0)
				{
					if (board[i][j] == BPeshka)
					{
						bPeshka.setPosition(j * size, i * size);
						window.draw(bPeshka);
					}
					if (board[i][j] == WPeshka)
					{
						wPeshka.setPosition(j * size, i * size);
						window.draw(wPeshka);
					}
					if (board[i][j] == BBashenka)
					{
						bBashenka.setPosition(j * size, i * size);
						window.draw(bBashenka);

					}
					if (board[i][j] == WBashenka)
					{
						wBashenka.setPosition(j * size, i * size);
						window.draw(wBashenka);

					}
					if (board[i][j] == WHorse)
					{
						wHorse.setPosition(j * size, i * size);
						window.draw(wHorse);
					}
					if (board[i][j] == BHorse)
					{
						bHorse.setPosition(j * size, i * size);
						window.draw(bHorse);
					}
					if (board[i][j] == BOficer)
					{
						bOficer.setPosition(j * size, i * size);
						window.draw(bOficer);
					}
					if (board[i][j] == WOficer)
					{
						wOficer.setPosition(j * size, i * size);
						window.draw(wOficer);
					}
					if (board[i][j] == WQueen)
					{
						wQueen.setPosition(j * size, i * size);
						window.draw(wQueen);
					}
					if (board[i][j] == BQueen)
					{
						bQueen.setPosition(j * size, i * size);
						window.draw(bQueen);
					}
					if (board[i][j] == BKing)
					{
						bKing.setPosition(j * size, i * size);
						window.draw(bKing);
					}
					if (board[i][j] == WKing)
					{
						wKing.setPosition(j * size, i * size);
						window.draw(wKing);
					}
				}
			}
		}
		window.display();
	}
	return 0;
}