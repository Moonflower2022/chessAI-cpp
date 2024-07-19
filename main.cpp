#include <iostream>
#include "chess.hpp"
#include "bot.cpp"

using namespace chess;
using namespace std;

int main(int argc, char const *argv[])
{
    init_tables();
    Board board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    pair<GameResultReason, GameResult> resultPair = board.isGameOver();
    cout << board << endl;
    while (resultPair.second == GameResult::NONE)
    {
        string input;
        cout << "Input a move: "; // Type a number and press enter
        cin >> input;
        Move userMove = uci::uciToMove(board, input);

        board.makeMove(userMove);
        cout << board << endl;

        Move computer_move = minimax(4, board, -MAX, MAX, false).second;

        board.makeMove(computer_move);
        cout << board << endl;
    }

    return 0;
}