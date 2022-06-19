#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"
#include "Position.h"
#include <vector>
#include <iostream>
#include "..\Checkers\Pieces\Empty.h"


using namespace std;

class Board
{
    vector<vector<Piece*>> pieces;
    int whitePieces;
    int blackPieces;
    vector<Piece*> piecesAtTheBoard;

public:
    Board()
    {
        for (int i = 0; i < Dim; i++)
        {
            vector<Piece *> aux;
            for (int j = 0; j < Dim; j++)
                aux.push_back(new Empty());
            pieces.push_back(aux);
        }

        whitePieces = 0;
        blackPieces = 0;
    }

        Piece *piece(int line, int column)
        {
            return pieces[line][column];
        }

        Piece *piece(Position pos)
        {
            return pieces[pos.line][pos.column];
        }

        bool existsPiece(Position pos)
        {
            validatePosition(pos);
            return !piece(pos)->isEmpty();
        }

        void putPiece(Piece* p, Position pos)
        {
            if(existsPiece(pos))
            {
                throw runtime_error("There is already a piece at this position!");
            }
            pieces[pos.line][pos.column] = p;
            p->setPosition(pos);
            
            if(p->getColor() == white) whitePieces ++;
            else if(p->getColor() == black) blackPieces ++;

            piecesAtTheBoard.push_back(p);

        }

        Piece *removePiece(Position pos)
        {
            if(piece(pos)->isEmpty())
            {
                return piece(pos);
            }
            else
            {
                if (piece(pos)->getColor() == white) whitePieces--;
                else if (piece(pos)->getColor() == black) blackPieces--;

                Piece *aux = piece(pos);
               

                for(int i =0; i<piecesAtTheBoard.size();i++)
                    if(piecesAtTheBoard[i] == piece(pos))
                    {
                        piecesAtTheBoard.erase(piecesAtTheBoard.begin()+i);
                    }

                pieces[pos.line][pos.column] = new Empty();
                return aux;
            }

        }

        bool static validPosition(Position pos)
        {
            if (pos.line < 0 || pos.line >= Dim || pos.column < 0 || pos.column >= Dim)
            {
                return false;
            }
            else
                return true;
        }

        void validatePosition(Position pos)
        {
            if (!validPosition(pos))
            {
                throw runtime_error("Invalid position!");
            }
        }

        bool isFinished()
        {
            return whitePieces * blackPieces == 0;
        }

        friend class CheckersMatch;
        friend class Game;
};

#endif