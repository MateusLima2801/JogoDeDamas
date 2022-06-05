#ifndef PIECE_H
#define PIECE_H
#include "Color.h";
#include "Position.h"
#include "Board.h"

using namespace std;

class Piece
{
protected:
    Color color;
    Position position;
    int amtOfMoves;
    Board board;

    bool canMove(Position pos)
    {
        Piece p = board.piece(pos);
        return p.isEmpty() || p.color != color;
    }

public:
    Piece(Color color, Board board)
    {
        this->color = color;
        amtOfMoves = 0;
        this->board = board;
    }

    Piece(){}

    bool existsPossibleMove()
    {
        vector<vector<bool> > matrix = possibleMoves();
        for(int i = 0; i < board.getLines(); i++)
        {
            for(int j = 0; j< board.getColumns(); j++)
            {
                if(matrix[i][j]) return true;
            }
        }

        return false;
    }

    virtual vector<vector<bool> > possibleMoves();

    void increaseAmtOfMoves()
    {
        amtOfMoves ++;
    }

    void decreaseAmtOfMoves()
    {
        amtOfMoves --;
    }

    bool canMoveTo(Position pos)
    {
        return possibleMoves()[pos.line][pos.column];
    }
    bool isEmpty()
    {
        if (color == emptyColor)
            return true;
        else
            return false;
    }

    void setEmpty()
    {
        color = emptyColor;
    }

    void setPosition(Position pos)
    {
        position.setPosition(pos);
    }
};

#endif