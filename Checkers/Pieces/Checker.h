#ifndef CHECKER_H
#define CHECKER_H
#include "..\..\Board\Piece.h"
#include "..\..\Board\Board.h"
#include "..\..\Board\Color.h"
#include "..\..\Board\Position.h"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

class Checker : public Piece
{   
        int forthDirection;
        Color livePlayer;
        Board *board;

    public:
        Checker(Color color, Board* board, Color livePlayer)
            : Piece(color)
        {
            wsymbol = L"\u25CF";
            symbol = "C";
            this->board = board;
            this->livePlayer = livePlayer;
            setDirection();
        }

        void setDirection()
        {
            if(livePlayer == white)
            {
                switch (color)
                {
                    case black:
                        forthDirection = 1;
                        break;
                    case white:
                        forthDirection = -1;
                        break;
                    default:
                        forthDirection = -1;
                        break;
                }
            }
            else
            {
                switch (color)
                {
                    case black:
                        forthDirection = -1;
                        break;
                    case white:
                        forthDirection = 1;
                        break;
                    default:
                        forthDirection = 1;
                        break;
                }
            }
        }

        vector<vector<bool>> possibleMoves() override
        {
            vector<vector<bool> > matrix;
            for(int i = 0; i< Dim; i++)
            {
                vector<bool> aux(Dim, false);
                matrix.push_back(aux); 
            } 

            Position pos(0,0);

            //ne
            pos.setPosition(position.line+forthDirection, position.column+1);
            if(Board::validPosition(pos) && canMove(pos))
                matrix[pos.line][pos.column] = true;

            //nw
            pos.setPosition(position.line + forthDirection, position.column - 1);
            if (Board::validPosition(pos) && canMove(pos))
                matrix[pos.line][pos.column] = true;
            //ne++
            pos.setPosition(position.line + 2*forthDirection, position.column +2);
            if (Board::validPosition(pos) && canMove(pos))
                matrix[pos.line][pos.column] = true;

            //nw++
            pos.setPosition(position.line + 2*forthDirection, position.column - 2);
            if (Board::validPosition(pos) && canMove(pos))
                matrix[pos.line][pos.column] = true;

            return matrix;
        }

        bool canMove(Position pos)
        {
            Piece* p = board->piece(pos);
            if (std::abs(pos.line - position.line) == 2)
            {
                Position Middle(position.line + (pos.line - position.line) / 2, position.column + (pos.column - position.column) / 2);
                if (board->piece(Middle)->color == opponent(color) && p->isEmpty())
                {
                    return true;
                }
                else return false;
            }
            else return p->isEmpty();
        }
        
};

#endif