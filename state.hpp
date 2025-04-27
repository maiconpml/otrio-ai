#include <vector>
#include <iostream>

using namespace std;

class State {

public:

	State() {
		board.resize(3, vector<pair<unsigned, unsigned>>(3, pair<unsigned, unsigned>(0, 0)));
		playersPieces.resize(2, { 0, 2, 2, 2 });
		status = 0;
	}
	bool check_victory(unsigned player) {
		// linhas
		for (unsigned i = 0; i < 3; ++i) {
			if (board[i][0].first == player && board[i][1].first == player && board[i][2].first == player) {
				return true;
			}
		}
		//  colunas
		for (unsigned j = 0; j < 3; ++j) {
			if (board[0][j].first == player && board[1][j].first == player && board[2][j].first == player) {
				return true;
			}
		}
		// diagonais
		if (board[0][0].first == player && board[1][1].first == player && board[2][2].first == player) {
			return true;
		}
		if (board[0][2].first == player && board[1][1].first == player && board[2][0].first == player) {
			return true;
		}

		return false;
	}
	bool put_piece(const unsigned player, const unsigned pieceSize, const unsigned x, const unsigned y) {

		if (x >= 3 || y >= 3) return false;
		if (pieceSize < 1 || pieceSize > 3) return false;
		if (playersPieces[player][pieceSize] == 0) return false;
		if (board[x][y].second >= pieceSize) return false;


		--playersPieces[player][pieceSize];
		board[x][y] = pair<unsigned, unsigned>(player, pieceSize);

		if (check_victory(player)) {
			status = player;
		}

		return true;
	}
	void print_board() {

		for (unsigned i = 0; i < 3; ++i) {
			cout << " ";
			for (unsigned j = 0; j < 3; ++j) {
				if (board[i][j].first == 0) {
					switch (board[i][j].second) {
						case 1:
							cout << ".";
							break;
						case 2:
							cout << "o";
							break;
						case 3:
							cout << "O";
							break;
						default:
							cout << " ";
							break;
					}
				}
				else {
					switch (board[i][j].second) {
					case 1:
						cout << "*";
						break;
					case 2:
						cout << "x";
						break;
					case 3:
						cout << "X";
						break;
					default:
						cout << " ";
						break;
					}
				}
				if(j != 2) cout << " | ";
			}
			
			if(i != 2) cout << endl << "-----------" << endl;
		}
		cout << endl;
	}

	unsigned get_status() {
		return status;
	}

private:

	vector<vector<pair<unsigned, unsigned>>> board;
	vector<vector<unsigned>> playersPieces;
	unsigned status;
};