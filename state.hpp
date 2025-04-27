#pragma once

#include <vector>
#include <iostream>
#include <utility>

using namespace std;
class State {
public:
    State() {
        board.resize(3, std::vector<std::pair<unsigned, unsigned>>(3, {0, 0}));
        playersPieces.resize(2, {0, 2, 2, 2});
        status = 0;
    }

	vector<vector<unsigned>> possibleMoves(int player) {
          vector<vector<unsigned>> result;
          for(int i =0;i<3;i++){
            for(int j=0;j<3;j++){
              for(int k=board[i][j].second+1;k<=3;k++){
                if(board[i][j].second==3)  break;
					if(playersPieces[player][k] > 0){
                    	result.push_back({i, j, k});
					}
              }
            }
          }
		return result;
	}
	bool put_piece(unsigned player, const unsigned pieceSize, const unsigned x, const unsigned y) {
        if (x >= 3 || y >= 3) return false;
        if (pieceSize < 1 || pieceSize > 3) return false;
        if (!playersPieces[player][pieceSize] || board[x][y].second >= pieceSize) return false;

    	--playersPieces[player][pieceSize];
        player++;
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
                if (board[i][j].first == 0) {
                    switch (board[i][j].second) {
                        case 1: std::cout << "."; break;
                        case 2: std::cout << "o"; break;
                        case 3: std::cout << "O"; break;
                        default: std::cout << " "; break;
                    }
                } else {
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

    unsigned get_status() const {
        return status;
    }

private:
    std::vector<std::vector<std::pair<unsigned, unsigned>>> board;
    std::vector<std::vector<unsigned>> playersPieces;
    unsigned status; // 0 = jogo em andamento, 1 = player 0 ganhou, 2 = player 1 ganhou
};

