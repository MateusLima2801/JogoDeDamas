#ifndef GAME_H
#define GAME_H
#include ".\Board\Board.h"
#include ".\Board\Piece.h"
#include ".\Board\Color.h"
#include ".\Board\Position.h"
#include "Global.h"
#include ".\Checkers\CheckersMatch.h"
#include ".\Checkers\CheckersPosition.h"
#include ".\Checkers\Pieces\Checker.h"
#include ".\Screen.h"
#include ".\Util.h"
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>

using namespace std;

class Game
{
    CheckersMatch* match;
    Color livePlayer;
    Color machinePlayer;
public :
    Game(CheckersMatch* match)
    {
        this->match = match;
        this->match->SetLivePlayer();
        this->match->putPieces();
        livePlayer = match->livePlayer;
        machinePlayer =match->opponent(livePlayer);
    }

    Color playTheWholeGame()
    {
        Color winner;

        while (!match->isMatchFinished(winner))
        {
            try
            {
                system("CLS");
                Screen::printMatch(*match);
                cout << endl;
                vector<Position> movement;

                movement = (match->currentPlayer == match->livePlayer) ? playLive() : playMachine();

                match->makePlay(movement[0], movement[1]);
                match->checkForLadies();
            }
            catch (runtime_error &e)
            {
                cout << e.what() << endl;
                Util::ReadKey();
            }
        }

        return winner;
    }

    

    vector<Position> playLive()
    {
        cout << "Origin: ";
        CheckersPosition origin_ch = Screen::readCheckersPosition();
        Position origin = origin_ch.toPosition();
        match->validateOrigin(origin);
        vector<vector<bool>> possiblePositions = match->board.piece(origin)->possibleMoves();

        system("CLS");
        Screen::printMatch(*match, possiblePositions);

        cout << endl;
        cout << "Origin: " << origin_ch << endl;
        cout << "Destination: ";
        Position destination = Screen::readCheckersPosition().toPosition();
        match->validateDestination(origin, destination);

        vector<Position> movement = {origin, destination};
        return movement;
    }

    vector<Position> playMachine()
    {
        vector< pair<int, vector<Position> > > catalogueOfMoves;
        vector< pair<int, vector<Position>>>::iterator it;
        vector<Piece *> machinePieces;

        for(int i = 0; i<match->board.piecesAtTheBoard.size(); i++)
        {
            if (match->board.piecesAtTheBoard[i]->getColor() == machinePlayer)
            {
                machinePieces.push_back(match->board.piecesAtTheBoard[i]);
            }
        }

        for(int i=0; i< machinePieces.size(); i++)
        {
            vector<vector<bool>> matrix = machinePieces[i]->possibleMoves();
            for(int j = 0; j < Dim; j++)
            {
                for(int k = 0; k < Dim; k++)
                {
                    if(matrix[j][k])
                    {
                        vector<Position> movement = {machinePieces[i]->getPosition(), Position(j, k)};
                        int captured = 0;
                        captured += match->pieceWasCapturated(movement[0], movement[1]) ? 1 : 0;
                        catalogueOfMoves.push_back( make_pair(captured,movement) );
                    }
                }
            }
        }

        random_shuffle(catalogueOfMoves.begin(),catalogueOfMoves.end());
        vector<pair<int, vector<Position>>>::iterator bigger_catch = catalogueOfMoves.begin();
        for (it = catalogueOfMoves.begin()+1; it != catalogueOfMoves.end(); it++)
        {
            if(bigger_catch->first < it-> first) bigger_catch = it;
        }

        if(bigger_catch->first == 0)
        {
            // bigger_catch == catalogueOfMoves.begin()
            for (it = catalogueOfMoves.begin() +1; it != catalogueOfMoves.end(); it++)
            {
                if ((bigger_catch->second)[0].line > (it->second)[0].line)
                    bigger_catch = it;
            }
        }

        vector<Position> movement = bigger_catch->second;

        cout << "Origin: " << Util::toCheckersPosition(movement[0]) << endl;
        cout << "Destination: " << Util::toCheckersPosition( movement[1]) << endl << endl;

        Util::ReadKey();
    
        return movement;
    }
};

#endif