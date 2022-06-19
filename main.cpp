#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <chrono>
#include <thread>
#include <cstdlib>
#include <iostream>
#include ".\Board\Board.h"
#include ".\Board\Piece.h"
#include ".\Board\Color.h"
#include ".\Board\Position.h"
#include "Global.h"
#include "Screen.h"
#include ".\Checkers\CheckersMatch.h"
#include ".\Checkers\CheckersPosition.h"
#include ".\Game.h"


using namespace std;

int main()
{
    system("CLS");
    Screen::printHeader();
    CheckersMatch match;
    Game game(&match);

    Color winner = game.playTheWholeGame();

    
    system("CLS");
    Screen::printMatch(match);
    Screen::printWinner(winner);

    return 0;
}

