#ifndef CHECKERS_MATCH_H
#define CHECKERS_MATCH_H
#include "..\Board\Board.h"
#include "..\Board\Color.h"
#include "..\Board\Piece.h"
#include "..\Board\Position.h"
#include "..\Global.h"
#include ".\Pieces\Checker.h"
#include "CheckersPosition.h"
#include <math.h>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

class CheckersMatch
{
    
    int turn;
    Color currentPlayer;
    Color livePlayer;
    bool finished;
    // Piece pieces[AmtPieces];
    // int piecesSize;
    // Piece capturated[AmtPieces];
    // int capturatedSize;

    

    public:
        Board board;

        CheckersMatch()
        {
            board = Board();
            turn = 1;
            currentPlayer = white;
            // setArrayEmpty(AmtPieces, capturated);
            // setArrayEmpty(AmtPieces,pieces);
            // piecesSize = 0;
            // capturatedSize = 0;
            SetLivePlayer();
            putPieces();
        }

        Piece doMovement(Position origin, Position destination)
        {
            Piece p = board.removePiece(origin);
            p.increaseAmtOfMoves();
            Piece capturatedPiece;
            if (capturatedAPiece(origin, destination))
            {
                capturatedPiece = board.removePiece((origin-destination)/2+origin);
                //capturated[capturatedSize++] = capturatedPiece;
            }
            else capturatedPiece.setEmpty();

            board.putPiece(p, destination);
            return capturatedPiece;
        }

        void makePlay(Position origin, Position destination)
        {
            Piece capturatedPiece = doMovement(origin, destination);
            turn++;
            switchesPlayer();
        }

        void switchesPlayer()
        {
            currentPlayer = (currentPlayer == white) ? black : white;
        }

        void validateOrigin(Position pos)
        {
            if(board.piece(pos).isEmpty())
            {
                throw runtime_error("There is no piece at the chosen position!");
            }
            else if(currentPlayer != board.piece(pos).getColor())
            {
                throw runtime_error("The piece chosen as origin is not yours!");
            }
            else if(!board.piece(pos).existsPossibleMove())
            {
                throw runtime_error("There is no possible movements for the piece chosen as origin!");
            }
        }

        void validateDestination(Position origin, Position destination)
        {
            if(!board.piece(origin).canMoveTo(destination))
            {
                throw runtime_error("Invalid destination position!");
            }
        }

        bool capturatedAPiece(Position origin, Position destination)
        {
            return abs(origin.column-destination.column) == 2;     
        }

        // Piece* capturatedPieces(Color color)
        // {
        //     Piece aux[AmtPieces];
        //     int auxSize = 0;
        //     setArrayEmpty(AmtPieces, aux);
        //     for(int i = 0; i< AmtPieces; i++)
        //     {
        //         if(capturated[i].getColor() == color)
        //         {
        //             aux[auxSize++] = capturated[i];
        //         }
        //     }
            
        //     return aux;
        // }

        // //NOT FINISHED YET
        // Piece *piecesAtTheGame(Color color)
        // {
        //     Piece aux[AmtPieces];
        //      int auxSize = 0;
        //     setArrayEmpty(AmtPieces, aux);
        //     for (int i = 0; i < AmtPieces; i++)
        //     {
        //         if (pieces[i].getColor() == color)
        //         {
        //             aux[auxSize++] = pieces[i];
        //         }
        //     }


        //     return aux;
        // }

        void setArrayEmpty(int size, Piece* v)
        {
            for(int i = 0; i<size; i++)
            {
                v[i].setEmpty();
            }
        }

        void putNewPiece(int line, int column, Piece piece)
        {
            board.putPiece(piece, Position(line, column));
        }

        //NOT FINISHED YET
        void putPieces()
        {
            //SecondPlayer
            for(int i = 0; i<3; i++)
            {
                for(int j = 0; j<Dim; j++)
                {
                    if( (i+j)%2==1) putNewPiece(i,j, Checker(opponent(livePlayer), board, livePlayer));
                }
            }
            
            for(int i=Dim-3; i<Dim; i++)
            {
                for (int j = 0; j < Dim; j++)
                {
                    if ((i + j) % 2 == 1) putNewPiece(i, j, Checker(livePlayer, board, livePlayer));
                }
            }
            //FirstPlayer
            
        }

        bool isMatchFinished()
        {
            if(!finished) return false;
            else{
                string winner = currentPlayer == white ? "White" : "Black";
                cout << "WINNER: " << winner;
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
};

#endif