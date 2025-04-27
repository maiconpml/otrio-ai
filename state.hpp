#pragma once

#include <vector>
#include <iostream>
#include <utility>

using namespace std;
class State {
public:
	State() {
		board.resize(3, std::vector<std::pair<unsigned, unsigned>>(3, { 0, 0 }));
		playersPieces.resize(3, { 0, 2, 2, 2 });
		playersPieces[0] = { 0, 0, 0, 0 };
		status = 0;
		nPieces = 12;
	}

	vector<vector<unsigned>> possibleMoves(int player) {
		vector<vector<unsigned>> result;
		for (unsigned i = 0; i < 3; i++) {
			for (unsigned j = 0; j < 3; j++) {
				for (unsigned k = board[i][j].second + 1; k <= 3; k++) {
					if (playersPieces[player][k] > 0) {
						result.push_back({ i, j, k });
					}
				}
			}
		}
		return result;
	}

	bool put_piece(unsigned player, const unsigned pieceSize, const unsigned x, const unsigned y) {
		if (x > 2 || y > 2 || x < 0 || y < 0) return false;
		if (pieceSize < 1 || pieceSize > 3) return false;
		if (player < 1 || player > 2) return false;
		if (!playersPieces[player][pieceSize] || board[x][y].second >= pieceSize) return false;

		--nPieces;
		--playersPieces[player][pieceSize];
		board[x][y] = pair<unsigned, unsigned>(player, pieceSize);

		if (board[x][0].first == player && board[x][1].first == player && board[x][2].first == player
			|| board[0][y].first == player && board[1][y].first == player && board[2][y].first == player
			|| board[0][0].first == player && board[1][1].first == player && board[2][2].first == player
			|| board[0][2].first == player && board[1][1].first == player && board[2][0].first == player) {
			status = player;
		}
		return true;
	}

	void print_board() {
		for (unsigned i = 0; i < 3; ++i) {
			std::cout << " ";
			for (unsigned j = 0; j < 3; ++j) {
				if (board[i][j].first == 1) {
					switch (board[i][j].second) {
					case 1: std::cout << "."; break;
					case 2: std::cout << "o"; break;
					case 3: std::cout << "O"; break;
					default: std::cout << " "; break;
					}
				}
				else {
					switch (board[i][j].second) {
					case 1: std::cout << "*"; break;
					case 2: std::cout << "x"; break;
					case 3: std::cout << "X"; break;
					default: std::cout << " "; break;
					}
				}
				if (j != 2) std::cout << " | ";
			}
			if (i != 2) std::cout << "\n-----------\n";
		}
		std::cout << "\n";
	}

	void print_remaining_pieces(const unsigned player) const {
		cout << "Remaining pieces: ";
		for (unsigned i = 1; i <= 3; ++i) {
			for (int j = playersPieces[player][i]; j > 0; --j) {
				switch (i) {
					case 1:
						cout << (player == 1 ? " . " : " * ");
						break;
					case 2:
						cout << (player == 1 ? " o " : " x ");
						break;
					case 3:
						cout << (player == 1 ? " O " : " X ");
						break;
				}
			}
		}
		cout << endl;
	}

	unsigned get_status() const {
		return status;
	}

	unsigned get_npieces() {
		return nPieces;
	}

private:
	std::vector<std::vector<std::pair<unsigned, unsigned>>> board;
	std::vector<std::vector<unsigned>> playersPieces;
	unsigned status; // 0 = jogo em andamento, 1 = player 0 ganhou, 2 = player 1 ganhou
	unsigned nPieces;
};

