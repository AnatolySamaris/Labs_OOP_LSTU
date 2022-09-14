#include "ChessTable.h"
#include <string>
#include <vector>

using namespace std;

vector<string> split(string &s)
{
    vector<string> ans;
    string word;
    for (auto i: s + " ")
    {
        if (i == ' ')
        {
            ans.push_back(word);
            word = "";
        }
        else word.push_back(i);
    }
    return ans;
}

int to_int(char num)
{
    return (int)num - '0';
}

int main()
{
    ChessTable chess;
    bool game = true;
    string act;
    while (game)
    {
        cout << "Enter your command: ";
        cin >> act;
        vector<string> to_do = split(act);

        if (to_do[0] == "MOVE")
        {
            chess.move(to_do[1][0], to_int(to_do[2][0]), to_do[3][0], to_int(to_do[4][0]));
        }
        else if (to_do[0] == "ADD")
        {
            chess.add_figure(to_do[1][0], to_do[2][0], to_int(to_do[3][0]));
        }
        else if (to_do[0] == "AUTO")
        {
            chess.autofill();
        }
        else if (to_do[0] == "CLEAR")
        {
            chess.clear();
        }
        else if (to_do[0] == "SHOW")
        {
            chess.show();
        }
        else if (to_do[0] == "HELP")
        {
            chess.help();
        }
        else if (to_do[0] == "END")
        {
            game = false;
        }
    }

    cout << "Game over!" << endl;
}
