#include <iostream>
#include <iomanip>
#include <conio.h>
#include <thread>
#include <chrono>
#include <ctime>

const int width = 30;
const int height = 20;

int snakeX, snakeY;
int starX, starY;

int score = 0;

char snakeHead = 'O';
char snakeBody = 'o';

char board = '#';
char star = '*';

int tailX[width * height];
int tailY[width * height];
int tailN;

bool gameOverStatus = false;

enum keys { RIGHT, LEFT, DOWN, UP, STOP};

keys prevKeyStatus;
keys keyStatus;

void Start();

void EnterKey();
void Logic();

void Display(bool);
void PrintBoxTop();
void PrintBoxMiddle();
void PrintBoxDown();

int main() {

	std::cout << tailX[0] << std::endl;

	srand(time(NULL));

	Start();

	while (!gameOverStatus) {

		EnterKey();
		Logic();
		Display(gameOverStatus);

		std::this_thread::sleep_for(std::chrono::milliseconds(50 - score / 10));
	}

	return 0;
}

void Start() {

	keyStatus = keys::STOP;

	snakeX = width / 2;
	snakeY = height / 2;

	tailN = 0;

	starX = rand() % width + 1;
	starY = rand() % height;
}

void EnterKey() {

	prevKeyStatus = keyStatus;

	if (_kbhit()) {

		switch (_getch()) {

		case 'a':

			keyStatus = keys::LEFT;
			break;
		case 'd':

			keyStatus = keys::RIGHT;
			break;
		case 's':

			keyStatus = keys::DOWN;
			break;

		case 'w':

			keyStatus = keys::UP;
			break;
		case 'x':

			gameOverStatus = true;
			break;
		}
	}
}

void Display(bool gameOver) {

	if (gameOver) {

		return;
	}

	system("cls");

	std::cout << "//======| Python abuse |======//" << std::endl;
	
	PrintBoxTop();

	PrintBoxMiddle();

	PrintBoxDown();

	std::cout << "Score: " << score << std::endl;
}

void PrintBoxTop() {

	for (int i = 0; i < width + 2; i++) {

		std::cout << board;
	}
	std::cout << std::endl;
}
void PrintBoxMiddle() {

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width + 2; j++) {

			if (j == 0 || j==width+1) {

				std::cout << board;
			}
			else if (i == snakeY && j == snakeX) {

				std::cout << snakeHead;
			}
			else if (i == starY && j == starX) {

				std::cout << star;
			}
			else {

				bool spaceStatus = true;

				for (int k = 0; k < tailN; k++) {

					if (i == tailY[k] && j == tailX[k]) {

						std::cout << snakeBody;
						spaceStatus = false;
					}
				}

				if (spaceStatus) {

					std::cout << ' ';
				}
			}
		}

		std::cout << std::endl;
	}
}
void PrintBoxDown() {

	for (int i = 0; i < width + 2; i++) {
		std::cout << board;
	}
	std::cout << std::endl;
}

void Logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];

	tailX[0] = snakeX;
	tailY[0] = snakeY;

	int prev2X, prev2Y;

	for (int i = 1; i < tailN; i++) {

		prev2X = tailX[i];
		prev2Y = tailY[i];

		tailX[i] = prevX;
		tailY[i] = prevY;

		prevX = prev2X;
		prevY = prev2Y;
	}

	if (prevKeyStatus == keys::DOWN && keyStatus == keys::UP) {

		keyStatus = prevKeyStatus;
	}
	else if (prevKeyStatus == keys::UP && keyStatus == keys::DOWN) {

		keyStatus = prevKeyStatus;
	}
	else if (prevKeyStatus == keys::LEFT && keyStatus == keys::RIGHT) {

		keyStatus = prevKeyStatus;
	}
	else if(prevKeyStatus == keys::RIGHT && keyStatus == keys::LEFT) {

		keyStatus = prevKeyStatus;
	}

	switch (keyStatus)
	{
	case RIGHT:

		snakeX++;
		break;
	case LEFT:

		snakeX--;
		break;
	case DOWN:

		snakeY++;
		break;
	case UP:

		snakeY--;
		break;
	}

	if (snakeX < 1) {

		snakeX = width;
	}
	else if (snakeX > width) {

		snakeX = 1;
	}

	if (snakeY < 0) {

		snakeY = height - 1;
	}
	else if (snakeY >= height) {

		snakeY = 0;
	}

	for (int i = 0; i < tailN; i++) {

		if (tailX[i] == snakeX && tailY[i] == snakeY) {

			gameOverStatus = true;
		}
	}

	if (snakeX == starX && snakeY == starY) {

		score += 10;

		starX = rand() % width + 1;
		starY = rand() % height;

		tailN++;
	}
}