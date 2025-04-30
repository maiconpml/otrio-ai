#pragma once
#include "state.hpp"
#include <limits>
#include <tuple>
#include <queue>

class MiniMax {
public:


	pair<int, pair<int, int>> minimax(State& state, unsigned player, vector<unsigned>& bestMove, int depth) {
		int best_move_aux = -1;

		pair<int, pair<int, int>> bestVal = player == 2 ? pair<int, pair<int, int>>(numeric_limits<int>::min(), pair<int, int>(-1, 0)) : pair<int, pair<int, int>>(numeric_limits<int>::max(), pair<int, int>(-1, 0));
		unsigned winner = state.get_status();
		if (winner == 1) return pair<int, pair<int, int>>(-10, pair<int, int>(depth, 0));
		if (winner == 2) return pair<int, pair<int, int>>(10, pair<int, int>(depth, 1));
		if (depth == 0) return pair<int, pair<int, int>>(0, pair<int, int>(depth, 0));
		vector<vector<unsigned>> possible_moves = state.possibleMoves(player);
		if (possible_moves.size() == 0) return pair<int, pair<int, int>>(0, pair<int, int>(depth, 0));
		vector<State> possible_states(possible_moves.size(), state);
		vector<pair<int, int>> results(possible_moves.size());
		int nVictorys = 0;
		pair<int, pair<int, int>> valAux;
		for (unsigned i = 0; i < possible_moves.size(); i++) {
			possible_states[i].put_piece(player, possible_moves[i][2], possible_moves[i][0], possible_moves[i][1]);
			valAux = minimax(possible_states[i], player == 2 ? 1 : 2, bestMove, depth - 1);
			nVictorys += valAux.second.second;
			if (player == 1) {
				if (bestVal.first > valAux.first) {
					bestVal = valAux;
					best_move_aux = i;
				}
				else if (bestVal.first == valAux.first) {
					if (bestVal.second.first < valAux.second.first) {
						bestVal = valAux;
						best_move_aux = i;
					}
					else if (bestVal.second.first == valAux.second.first && bestVal.second.second < valAux.second.second) {
						bestVal = valAux;
						best_move_aux = i;
					}
				}
			}
			else {
				if (bestVal.first < valAux.first) {
					bestVal = valAux;
					best_move_aux = i;
				}
				else if (bestVal.first == valAux.first) {
					if (bestVal.second.first < valAux.second.first) {
						bestVal = valAux;
						best_move_aux = i;
					}
					else if (bestVal.second.first == valAux.second.first && bestVal.second.second < valAux.second.second) {
						bestVal = valAux;
						best_move_aux = i;
					}
				}
			}
		}

		bestMove = possible_moves[best_move_aux];
		bestVal.second.second = nVictorys;
		return bestVal;
	}

};