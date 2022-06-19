#ifndef LADY_H
#define LADY_H
#include "..\..\Board\Piece.h"
#include "..\..\Board\Board.h"
#include "..\..\Board\Color.h"
#include "..\..\Board\Position.h"
#include <vector>
#include <fstream>
using namespace std;

class Lady : public Piece
{
    Board* board;
public:
    Lady(Color color, Board* board, int amtOfMoves)
        : Piece(color)
    {
        symbol = "L";
        this->amtOfMoves = amtOfMoves;
        this->board = board;
    }

    virtual vector<vector<bool>> possibleMoves()
    {
        vector<vector<bool>> matrix;
        for (int i = 0; i < Dim; i++)
        {
            vector<bool> aux(Dim, false);
            matrix.push_back(aux);
        }

        Position pos(0, 0);

        // ne
        pos.setPosition(position.line - 1, position.column + 1);
        while(Board::validPosition(pos))
        {
            Piece *p = board->piece(pos);
            if (p->color == color) break;
            else if(p->isEmpty())
                matrix[pos.line][pos.column] = true;
            pos.line--;
            pos.column++;
        }

        // nw
        pos.setPosition(position.line - 1, position.column - 1);
        while (Board::validPosition(pos))
        {
            Piece *p = board->piece(pos);
            if (p->color == color)
                break;
            else if (p->isEmpty())
                matrix[pos.line][pos.column] = true;
            pos.line--;
            pos.column--;
        }

        // se
        pos.setPosition(position.line + 1, position.column + 1);
        while (Board::validPosition(pos))
        {
            Piece *p = board->piece(pos);
            if (p->color == color)
                break;
            else if (p->isEmpty())
                matrix[pos.line][pos.column] = true;
            pos.line++;
            pos.column++;
        }

        // sw
        pos.setPosition(position.line + 1, position.column - 1);
        while (Board::validPosition(pos))
        {
            Piece *p = board->piece(pos);
            if (p->color == color)
                break;
            else if (p->isEmpty())
                matrix[pos.line][pos.column] = true;
            pos.line++;
            pos.column--;
        }

        return matrix;
    }

    bool canMove(Position pos)
    {
        Piece *p = board->piece(pos);
        return p->isEmpty();
    }
};

#endif