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

	void put_piece(const unsigned player, const unsigned pieceSize, const unsigned x, const unsigned y) {
		if (!playersPieces[player][pieceSize] || board[x][y].second >= pieceSize) return;

		--playersPieces[player][pieceSize];
		board[x][y] = pair<unsigned, unsigned>(player, pieceSize);

		if (board[x][0].first == player && board[x][1].first == player && board[x][2].first == player
			|| board[0][y].first == player && board[1][y].first == player && board[2][y].first == player
			|| board[0][0].first == player && board[1][1].first == player && board[2][2].first == player
			|| board[0][2].first == player && board[1][1].first == player && board[2][0].first == player) {
			status = player;
		}
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