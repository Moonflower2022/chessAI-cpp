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