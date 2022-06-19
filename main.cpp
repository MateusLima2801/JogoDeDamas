#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include ".\Board\Board.h"
#include ".\Board\Piece.h"
#include ".\Board\Color.h"
#include ".\Board\Position.h"
#include "Global.h"
#include "Screen.h"
#include ".\Checkers\CheckersMatch.h"
#include ".\Checkers\CheckersPosition.h"

using namespace std;

int main()
{
    CheckersMatch match;
    system("CLS");
    Screen::printHeader();
    match.Set();
    
    while (!match.isMatchFinished())
    {
        try
        {
            system("CLS");
            Screen::printMatch(match);
            cout << endl;
            cout << "Origin: ";
            Position origin = Screen::readCheckersPosition().toPosition();
            match.validateOrigin(origin);
            vector<vector<bool>> possiblePositions = match.board.piece(origin).possibleMoves();

            system("CLS");
            Screen::printBoard(match.board, possiblePositions);

            cout << endl;
            cout << "Destination: ";
            Position destination = Screen::readCheckersPosition().toPosition();
            match.validateDestination(origin, destination);
        }
        catch(runtime_error &e)
        {
            char c;
            cout << e.what() << endl;
            cin >> c;
        }

    }

    cout << "Returning..." << endl;
    
    return 0;
}

