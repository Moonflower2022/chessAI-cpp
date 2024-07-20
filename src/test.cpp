#include <iostream>
#include "lib/chess.hpp"
#include "minimax.cpp"
#include "evaluation.cpp"

using namespace chess;
using namespace std;

int main(int argc, char const *argv[])
{

    init_tables();
    Board board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    pair<GameResultReason, GameResult> result_pair = board.isGameOver();
    cout << board << endl;

    vector<string> input_moves = {"a2a3", "b2b3", "c2c3", "d2d3", "e2e3", "f2f3", "g2g3", "h2h3"};

    for (const string move : input_moves)
    {
        board.makeMove(uci::uciToMove(board, move));
        cout << board << endl;

        Move computer_move = minimax(4, board, -MAX, MAX, false).second;

        board.makeMove(computer_move);
        cout << board << endl;
        cout << "Black's move: " << uci::moveToUci(computer_move) << endl;
    }

    return 0;
}