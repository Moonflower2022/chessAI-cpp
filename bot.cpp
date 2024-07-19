#include <iostream>
#include "chess.hpp"
#include "evaluation.cpp"
#include <string>
#include <vector>

using namespace chess;
using namespace std;

pair<int, Move> minimax(int depth, Board board, int alpha, int beta, bool is_maximizing_player)
{
    if (depth == 0)
    {
        return {evaluate_fen(board.getFen()), Move()};
    }

    Move best_move;
    int best_move_value = is_maximizing_player ? -MAX : MAX;

    Movelist possible_moves;
    movegen::legalmoves(possible_moves, board);

    // randomize the array

    for (const Move move : possible_moves)
    {
        int value = 0;
        board.makeMove(move);

        pair<GameResultReason, GameResult> resultPair = board.isGameOver();

        if (resultPair.second == GameResult::NONE)
        {
            value = minimax(depth - 1, board, alpha, beta, !is_maximizing_player).first;
        }
        else
        {
            value = (resultPair.second == GameResult::WIN && is_maximizing_player) * MAX - (resultPair.second == GameResult::WIN && !is_maximizing_player) * MAX;
        }

        if (is_maximizing_player)
        {
            // Look for moves that maximize position
            if (value > best_move_value)
            {
                best_move = move;
                best_move_value = value;
            }
            alpha = max(alpha, value);
        }
        else
        {
            // Look for moves that minimize position
            if (value < best_move_value)
            {
                best_move = move;
                best_move_value = value;
            }
            beta = min(beta, value);
        }

        board.unmakeMove(move);
        if (beta <= alpha)
            break;
    }

    return {best_move_value, best_move};
}

int main(int argc, char const *argv[])
{
    init_tables();
    Board board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    // Board board = Board("Q2qkbnr/p2bpppp/2n5/8/8/8/PPPP1PPP/RNBQKBNR b KQk - 0 5");
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