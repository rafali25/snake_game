#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <thread>

using namespace std;

bool isGameOver;
const int gridWidth = 20;
const int gridHeight = 20;
int headX, headY, fruitPosX, fruitPosY, playerScore;
int tailPosX[500], tailPosY[500];
int tailLength;
enum Direction { STOP = 0, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN };
Direction currentDirection;

void initializeGame() {
    system("color 6f");
    isGameOver = false;
    currentDirection = STOP;
    headX = gridWidth / 2;
    headY = gridHeight / 2;
    fruitPosX = rand() % gridWidth;
    fruitPosY = rand() % gridHeight;
    playerScore = 0;
}

void drawGrid() {
    system("cls");
    for (int i = 0; i < gridWidth + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < gridHeight; i++) {
        for (int j = 0; j < gridWidth; j++) {
            if (j == 0)
                cout << "|";
            if (i == headY && j == headX)
                cout << "O";
            else if (i == fruitPosY && j == fruitPosX)
                cout << "#";
            else {
                bool printTail = false;
                for (int k = 0; k < tailLength; k++) {
                    if (tailPosX[k] == j && tailPosY[k] == i) {
                        cout << "o";
                        printTail = true;
                    }
                }
                if (!printTail)
                    cout << " ";
            }
            if (j == gridWidth - 1)
                cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < gridWidth + 2; i++)
        cout << "-";
    cout << endl;
    cout << "Score: " << playerScore << endl;
}

void handleInput() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': currentDirection = MOVE_LEFT; break;
            case 'd': currentDirection = MOVE_RIGHT; break;
            case 'w': currentDirection = MOVE_UP; break;
            case 's': currentDirection = MOVE_DOWN; break;
            case 'x': isGameOver = true; break;
        }
    }
}

void gameLogic() {
    int prevX = tailPosX[0];
    int prevY = tailPosY[0];
    int prev2X, prev2Y;
    tailPosX[0] = headX;
    tailPosY[0] = headY;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailPosX[i];
        prev2Y = tailPosY[i];
        tailPosX[i] = prevX;
        tailPosY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (currentDirection) {
        case MOVE_LEFT: headX--; break;
        case MOVE_RIGHT: headX++; break;
        case MOVE_UP: headY--; break;
        case MOVE_DOWN: headY++; break;
        default: break;
    }

    if (headX >= gridWidth) headX = 0; else if (headX < 0) headX = gridWidth - 1;
    if (headY >= gridHeight) headY = 0; else if (headY < 0) headY = gridHeight - 1;

    for (int i = 0; i < tailLength; i++) {
        if (tailPosX[i] == headX && tailPosY[i] == headY)
            isGameOver = true;
    }

    if (headX == fruitPosX && headY == fruitPosY) {
        playerScore += 10;
        fruitPosX = rand() % gridWidth;
        fruitPosY = rand() % gridHeight;
        tailLength++;
    }
}

void playSound() {
    PlaySound(TEXT("JOLA.wav"), NULL, SND_SYNC);
}

int main() {
    initializeGame();

    while (!isGameOver) {
        drawGrid();
        handleInput();
        gameLogic();
        thread soundThread(playSound);
        soundThread.detach();
        Sleep(80);
    }

    return 0;
}
