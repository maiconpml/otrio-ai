#include <vector>

class State {

public:

	State() {
		board.resize(3, vector<pair<unsigned, unsigned>(3, pair<unsigned, unsigned>(0, 0)));
		playerPieces.resize(2, { 0, 2, 2, 2 });
		status = 0;
	}

	void put_piece(const unsigned player, const unsigned pieceSize, const unsigned x, const unsigned y) {
		if (!playerPieces[player][pieceSize].first || board[x][y].second >= pieceSize) return;

		--playerPieces[player][pieceSize];
		board[x][y] = pair<unsigned, unsigned>(player, pieceSize);

		if (board[x][0].first == player && board[x][1].first == player && board[x][2].first == player
			|| board[0][y].first == player && board[1][y].first == player && board[2][y].first == player
			|| board[0][0].first == player && board[1][1].first == player && board[2][2].first == player
			|| board[0][2].first == player && board[1][1].first == player && board[2][0].first == player) {
			status = player;
		}
	}

private:

	vector<vector<pair<unsigned, unsigned>>> board;
	vector<vector<unsigned>> playersPieces;
	unsigned status;
};