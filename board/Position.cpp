#include <iostream>
#include <string>

namespace board{
    class Position{
        public:
            int Line;
            int Column;

            Position(int line, int column)
            {
                Line = line;
                Column = column;
            }

            void setPosition(int line, int column)
            {
                Line = line;
                Column = column;
            }

            std::string print()
            {
                return  Line + ", " + Column;
            }
    };
}
