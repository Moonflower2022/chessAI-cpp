#include <iostream>
#include "chess.hpp"
#include "bot.cpp"
#include "evaluation.cpp"

using namespace chess;
using namespace std;

Move get_user_move(Board board)
{
    Movelist possible_moves;
    movegen::legalmoves(possible_moves, board);

    while (true)
    {
        string input;
        cout << "Input a move by providing the from square and the to square (for castling just input the king's movement): ";
        cin >> input;
        Move user_move = uci::uciToMove(board, input);

        for (const Move move : possible_moves)
        {
            if (move == user_move)
            {
                return move;
            }
        }
        cout << "\nInvalid move. Try again.\n" << endl;
        cout << board << endl;
    }
}

int main(int argc, char const *argv[])
{
    init_tables();
    Board board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    pair<GameResultReason, GameResult> result_pair = board.isGameOver();
    cout << "\n\n";
    cout << board << endl;
    while (result_pair.second == GameResult::NONE)
    {
        Move user_move = get_user_move(board);
        board.makeMove(user_move);
        cout << board << endl;

        Move computer_move = minimax(4, board, -MAX, MAX, false).second;

        board.makeMove(computer_move);
        cout << board << endl;
        cout << "Black's move: " << uci::moveToUci(computer_move) << endl << endl;
    }

    return 0;
}