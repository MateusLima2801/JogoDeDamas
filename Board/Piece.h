#ifndef PIECE_H
#define PIECE_H
#include "Color.h"
#include "Position.h"
#include "..\Global.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iostream>
#include <windows.h>

using namespace std;

class Piece
{
    protected:
        Color color;
        Position position;
        int amtOfMoves;

    public:
        Piece(Color color)
        {
            this->color = color;
            amtOfMoves = 0;
        }

        Piece(){}

        Color getColor(){ return color; }

        bool existsPossibleMove()
        {
            vector<vector<bool> > matrix = possibleMoves();
            for(int i = 0; i < Dim; i++)
            {
                for(int j = 0; j< Dim; j++)
                {
                    if(matrix[i][j]) return true;
                }
            }

            return false;
        }

        virtual vector<vector<bool> > possibleMoves()
        {
            return vector<vector<bool>>();
        }

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

        virtual string symbol(){
            return " ";
        }

        friend ostream &operator<<(ostream &os, Piece &piece);
        friend class Checker;
        friend class Lady;
};

ostream &operator<<(ostream &os, Piece &piece)
{
    os << piece.symbol();
    return os;
}

#endif