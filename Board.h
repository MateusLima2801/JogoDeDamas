#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"
#include "Position.h"
#include <vector>

using namespace std;

class Board
{
    int lines;
    int columns;

    vector<vector<Piece>> pieces;

public:
    Board(int lines, int columns)
    {
        this->lines = lines;
        this->columns = columns;
        for (int i = 0; i < lines; i++)
        {
            vector<Piece> aux(columns);
            pieces.push_back(aux);
        }
    }

    Piece piece(int line, int column)
    {
        return pieces[line][column];
    }

    Piece piece(Position pos)
    {
        return pieces[pos.line][pos.column];
    }

    bool existsPiece(Position pos)
    {
        validatePosition(pos);
        return !piece(pos).isEmpty();
    }

    void putPiece(Piece p, Position pos)
    {
        if(existsPiece(pos))
        {
            throw runtime_error("There is already a piece at this position!");
        }
        pieces[pos.line][pos.column] = p;
        p.setPosition(pos);
    }

    Piece removePiece(Position pos)
    {
        if(piece(pos).isEmpty())
        {
            return piece(pos);
        }
        else
        {
            Piece aux = piece(pos);
            aux.setEmpty();
            pieces[pos.line][pos.column].setEmpty();
            return aux;
        }
    }

    bool validPosition(Position pos)
    {
        if (pos.line < 0 || pos.line >= lines || pos.column < 0 || pos.column >= columns)
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
};

#endif