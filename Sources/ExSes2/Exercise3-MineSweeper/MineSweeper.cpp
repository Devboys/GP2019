#include "MineSweeper.hpp"
#include "sstream"
#include "iostream"
#include "time.h"

int boardSize;
std::vector <std::vector<FieldType>> board;
std::vector <std::vector<bool>> revealedMap;

bool running;

MineSweeper::MineSweeper()
{
	running = true;
}

void MineSweeper::initLevel(int size)
{
	boardSize = size;

	board = std::vector<std::vector<FieldType>>(boardSize, std::vector<FieldType>(boardSize));
	revealedMap = std::vector<std::vector<bool>>(boardSize, std::vector<bool>(boardSize));

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			board[i][j] = Empty;
		}
	}

	srand(time(NULL));
	int numBombs = boardSize + (rand() % 6) - 3; //generate num between -3 and 3
	std::cout << "num bombs: " << numBombs;

	int numBombsPlaced = 0;
	while (numBombsPlaced < numBombs) 
	{
		int randomX = rand() % boardSize;
		int randomY = rand() % boardSize;

		if (board[randomY][randomX] != BombUnexploded)
		{
			board[randomY][randomX] = BombUnexploded;
			numBombsPlaced++;
		}
	}

	for (int y = 0; y < boardSize; y++) {
		for (int x = 0; x < boardSize; x++) {

			int nearBombs = bombsNearby(y, x);
			
			FieldType type = Empty;
			if (board[y][x] != BombUnexploded && nearBombs != 0) {
				switch (nearBombs)
				{
				case 1:
					type = Empty1;
					break;
				case 2:
					type = Empty2;
					break;
				case 3:
					type = Empty3;
					break;
				case 4:
					type = Empty4;
					break;
				case 5:
					type = Empty5;
					break;
				case 6:
					type = Empty6;
					break;
				case 7:
					type = Empty7;
					break;
				case 8:
					type = Empty8;
					break;
				}

				board[y][x] = type;
			}
		}
	}
}

void MineSweeper::print()
{
	std::ostringstream oss;

	oss << "  ";
	for (int x = 0; x < boardSize; x++) {
		oss << x;
	}
	oss << "\n";

	for (int i = 0; i < boardSize; i++)
	{
		oss << i << " ";
		for (int j = 0; j < boardSize; j++)
		{
			FieldType type = Button;
			if (revealedMap[i][j])
				type = board[i][j];

			switch (type)
			{
			case Button: 
			case BombUnexploded:
				oss << "#";
				break;
			case Empty:
				oss << 0;
				break;
			case Empty1:
				oss << 1;
				break;
			case Empty2:
				oss << 2;
				break;
			case Empty3:
				oss << 3;
				break;
			case Empty4:
				oss << 4;
				break;
			case Empty5:
				oss << 5;
				break;
			case Empty6:
				oss << 6;
				break;
			case Empty7:
				oss << 7;
				break;
			case Empty8:
				oss << 8;
				break;
			case BombExploded:
				oss << "B";
				break;
			case Flag:
				oss << "*";
				break;
			default:
				break;
			}
		}
		oss << "\n";
	}

	std::cout << oss.str();
}

FieldType MineSweeper::getField(int row, int column)
{
	// todo implement
	return Button;
}

bool MineSweeper::isRunning()
{
	return running;
}

std::string MineSweeper::take(int row, int column)
{
	if (!checkBounds(row, column))
		return "INVALID VALUE";

	if (board[row][column] == BombUnexploded) 
	{
		running = false;
		return "you lose!";
	}
	else 
	{
		revealedMap[row][column] = true;
		return " aight";
	}
}

int MineSweeper::numberOfBombs()
{
	// todo implement
	return 0;
}

int MineSweeper::numberOfHidden()
{
	// todo implement
	return 0;
}

int MineSweeper::bombsNearby(int row, int column)
{
	int numNearBombs = 0;
	for (int y = -1; y < 2; y++) {
		for (int x = -1; x < 2; x++) {
			if (x == 0 && y == 0) continue;
			
			int neighborRow = row + y;
			int neighborColumn = column + x;

			if (checkBounds(neighborColumn, neighborRow)) {
				if (board[neighborRow][neighborColumn] == BombUnexploded)
					numNearBombs++;
			}
		}
	}
	return numNearBombs;
}

bool MineSweeper::checkBounds(int row, int column) 
{
	if (row >= boardSize || row < 0 || column >= boardSize || column < 0) 
		return false;
	else
		return true;
}
