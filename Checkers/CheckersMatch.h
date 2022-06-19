#ifndef CHECKERS_MATCH_H
#define CHECKERS_MATCH_H
#include "..\Board\Board.h"
#include "..\Board\Color.h"
#include "..\Board\Piece.h"
#include "..\Board\Position.h"
#include "..\Global.h"
#include ".\Pieces\Checker.h"
#include ".\Pieces\Lady.h"
#include "CheckersPosition.h"
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

using namespace std;

class CheckersMatch
{
    
    int turn;
    Color currentPlayer;
    Color livePlayer;
    vector<Position> capturedAtTheTurn;

    public:
        Board board;

        CheckersMatch()
        {
            board = Board();
            turn = 1;
            currentPlayer = white;
        }


        void doMovement(Position origin, Position destination)
        {
            Piece *p = board.removePiece(origin);
            p->increaseAmtOfMoves();

            if (getCapturatedPiece(origin, destination))
            {
                for(int i = 0; i<capturedAtTheTurn.size(); i++)
                {
                    board.removePiece(capturedAtTheTurn[i]);
                }
            }

            board.putPiece(p, destination);
        }

        void makePlay(Position origin, Position destination)
        {
            doMovement(origin, destination);
            turn++;
            switchesPlayer();
            capturedAtTheTurn.clear();
        }

        void checkForLadies()
        {
            for (int i = 0; i < Dim; i++)
            {
                checkForLadyAt(livePlayer, 0, i);
                checkForLadyAt(opponent(livePlayer), Dim - 1, i);
            }
        }

        void checkForLadyAt(Color color, int line, int column)
        {
            if (board.piece(line, column)->getColor() == color)
            {
                Position pos(line, column);
                Piece *p = board.removePiece(pos);
                board.putPiece(new Lady(color, &board, p->getAmtOfMoves()), pos);
            }
        }

        void switchesPlayer()
        {
            currentPlayer = (currentPlayer == white) ? black : white;
        }

        void validateOrigin(Position pos)
        {
            Piece *p = board.piece(pos);
            if (p->isEmpty())
            {  
                throw runtime_error("There is no piece at the chosen position!");
            }
            if(currentPlayer != p->getColor())
            {
                throw runtime_error("The piece chosen as origin is not yours!");
            }
            if(!p->existsPossibleMove())
            {

                throw runtime_error("There is no possible movements for the piece chosen as origin!");
            }
        }

        void validateDestination(Position origin, Position destination)
        {
            if(!board.piece(origin)->canMoveTo(destination))
            {
                throw runtime_error("Invalid destination position!");
            }
        }

        bool getCapturatedPiece(Position origin, Position destination)
        {
            int n_steps = std::abs(destination.line - origin.line);
            Position step =(destination - origin)/n_steps;
            Position current = origin;
            while(current != destination)
            {
                if(board.piece(current)->getColor() == opponent(currentPlayer))
                {
                    capturedAtTheTurn.push_back(current);
                    return true;
                }
                current = current +step;
            }
            return false;
        }

        bool pieceWasCapturated(Position origin, Position destination)
        {
            int n_steps = std::abs(destination.line - origin.line);
            Position step = (destination - origin) / n_steps;
            Position current = origin;
            while (current != destination)
            {
                if (board.piece(current)->getColor() == opponent(currentPlayer))
                {
                    return true;
                }
                current = current + step;
            }
            return false;
        }

        void setArrayEmpty(int size, Piece* v)
        {
            for(int i = 0; i<size; i++)
            {
                v[i].setEmpty();
            }
        }

        void putNewPiece(int line, int column, Piece* piece)
        {
            board.putPiece(piece, Position(line, column));
        }

        
        void putPieces()
        {
            //STANDARD GAME
             //SecondPlayer
            for(int i = 0; i<3; i++)
            {
                for(int j = 0; j<Dim; j++)
                {
                    if( (i+j)%2==1) putNewPiece(i,j, new Checker(opponent(livePlayer), &board, livePlayer));
                }
            }

            // FirstPlayer
            for(int i=Dim-3; i<Dim; i++)
            {
                for (int j = 0; j < Dim; j++)
                {
                    if ((i + j) % 2 == 1) putNewPiece(i, j, new Checker(livePlayer, &board, livePlayer));
                }
            }

            //LADIES' GAME
            //Use to test the transformation from checker into lady
            // //SecondPlayer
            // int i = 1;
            // for (int j = 0; j < Dim; j++)
            // {
            //     if ((i + j) % 2 == 1)
            //         putNewPiece(i, j, new Checker(livePlayer, &board, livePlayer));
            // }

            // // FirstPlayer
            // i = Dim - 2;
            // for (int j = 0; j < Dim; j++)
            // {
            //     if ((i + j) % 2 == 1)
            //         putNewPiece(i, j, new Checker(opponent(livePlayer), &board, livePlayer));
            // }

            // FINISH GAME
            //Use to test the victory of one side
            // putNewPiece(4, 5, new Checker(livePlayer, &board, livePlayer));
            // putNewPiece(3, 4, new Checker(opponent(livePlayer), &board, livePlayer));

            // KILL GAME
            // Use to test randomic machine 
            //  putNewPiece(4, 5, new Checker(livePlayer, &board, livePlayer));
            //  putNewPiece(2, 5, new Checker(opponent(livePlayer), &board, livePlayer));
        }

        bool isMatchFinished(Color &winner )
        {
            if (!board.isFinished()) return false;
            else{
                winner = opponent(currentPlayer);
                turn --;
                return true;
            }
        }

        void SetLivePlayer()
        {
            cout << "Let's begin:"<<endl;
            cout << " (B) Black" << endl;
            cout << " (W) White" << endl;
            bool playerChoosen = false;
            do
            {
                char playerChoice;
                cout << "Choose your color: " << endl;
                cin >> playerChoice;
                switch(playerChoice)
                {
                    case 'b':
                    case 'B':
                        livePlayer = black;
                        playerChoosen = true;
                        break;
                    case 'w':
                    case 'W':
                        livePlayer = white;
                        playerChoosen = true;
                        break;
                    default:
                        cout << "Invalid choice for player!" << endl;
                }
            } while (!playerChoosen);
 
        }

        Color opponent(Color color)
        {
            switch (color)
            {
            case white:
                return black;
            case black:
                return white;
            default:
                throw invalid_argument("Invalid argument for opponent function");
                return emptyColor;
            }
        }

        
        friend class Screen;
        friend class Game;
};

#endif