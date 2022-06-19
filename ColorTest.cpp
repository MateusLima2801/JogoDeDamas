#include <iostream>
#include <windows.h> // WinApi header

using namespace std; // std::cout, std::cin

int main()
{
    HANDLE hConsole;
    int k;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // you can loop k higher to see more color choices
    // for (k = 1; k < 255; k++)
    // for (k = 127; k < 128; k++)
    // {
    //     // pick the color attribute k you want
    //     SetConsoleTextAttribute(hConsole, k);
    //     cout << k << " I want to be nice today!" << endl;
    // }

    cout<< "\u001b[40m A \u001b[41m B \u001b[42m C \u001b[43m D \u001b[0m" <<endl;
    cout<<"\u001b[44m A \u001b[45m B \u001b[46m C \u001b[47m D \u001b[0m" << endl;
    cout << "\u001b[40;1m A \u001b[41;1m B \u001b[42;1m C \u001b[43;1m D \u001b[0m"<< endl;
    cout << "\u001b[44;1m A \u001b[45;1m B \u001b[46;1m C \u001b[47;1m D \u001b[0m"<< endl;
    // SetConsoleTextAttribute(hConsole, 139);
    //cout << "lilsomething" << endl;

    cin.get(); // wait

    //SetConsoleTextAttribute(hConsole, 0);
    return 0;
}