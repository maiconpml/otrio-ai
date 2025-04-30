#pragma once
#include "state.hpp"
#include <limits>
#include <tuple>
#include <queue>

class MiniMax {
public:


	pair<int, int> minimax(State& state, unsigned player, vector<unsigned>& bestMove, int depth) {
		int best_move_aux = -1;

		pair<int, int> bestVal = player == 2 ? pair<int, int>(numeric_limits<int>::min(), -1) : pair<int, int>(numeric_limits<int>::max(), -1);
		unsigned winner = state.get_status();
		if (winner == 1) return pair<int, int>(- 10, depth);
		if (winner == 2) return pair<int, int>(10, depth);
		if (depth == 0) return pair<int, int>(0, depth);
		vector<vector<unsigned>> possible_moves = state.possibleMoves(player);
		if (possible_moves.size() == 0) return pair<int, int>(0, depth);
		vector<State> possible_states(possible_moves.size(), state);
		vector<pair<int, int>> results(possible_moves.size());
		for (unsigned i = 0; i < possible_moves.size(); i++) {
			possible_states[i].put_piece(player, possible_moves[i][2], possible_moves[i][0], possible_moves[i][1]);
			results[i] = minimax(possible_states[i], player == 2 ? 1 : 2, bestMove, depth - 1);
			/*if (player == 1) {
				if (bestVal > valAux) {
					bestVal = valAux;
					best_move_aux = i;
					if (bestVal == -10) break;
				}
			}
			else {
				if (bestVal < valAux) {
					bestVal = valAux;
					best_move_aux = i;
					if (bestVal == 10) break;
				}
			}*/


		}

		for (unsigned i = 0; i < results.size(); ++i) {
			if (player == 1) {
				if (bestVal.first > results[i].first) {
					bestVal = results[i];
					best_move_aux = i;
				}
				else if (bestVal.first == results[i].first && bestVal.second < results[i].second) {
					bestVal = results[i];
					best_move_aux = i;
				}
			}
			else {
				if (bestVal.first < results[i].first) {
					bestVal = results[i];
					best_move_aux = i;
				}
				else if (bestVal.first == results[i].first && bestVal.second < results[i].second) {
					bestVal = results[i];
					best_move_aux = i;
				}
			}
		}

		bestMove = possible_moves[best_move_aux];
		return bestVal;
	}

};