#include "ChessTable.h"

using namespace std;

int main()
{
    ChessTable chess;

    chess.autofill();
    chess.show();

    chess.clear();
    chess.show();

    chess.add_piece('K', 'C', 3);
    chess.add_piece('q', 'D', 5);
    chess.add_piece('M', 'G', 2);
    chess.add_piece('m', 'F', 6);
    chess.show();

    chess.move('C', 3, 'D', 5);
    chess.show();
    chess.move('F', 6, 'E', 6);
    chess.show();


}
