#include "state.hpp"
#include "minimax.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using namespace chrono;

int main(int argc, char *argv[]) {
	State s;
	unsigned currentPlayer = 2;
	unsigned pieceSize, x, y;
	int round = 0;
	MiniMax minimax;
	int ct;

	if (argc < 2) {
		ct = 6;
	}
	else {
		ct = stoi(argv[1]);
	}

	while (s.get_status() == 0 && s.get_npieces()) {
		
		system("clear"); 
		s.print_board();

		if (currentPlayer == 1) {
			// Jogador humano
			cout << endl;
			s.print_remaining_pieces(1);
			cout << "Player " << currentPlayer << " (You):\n";
			cout << "Enter piece size (1, 2, or 3), x and y coordinates: ";
			cin >> pieceSize >> x >> y;
			while (!s.put_piece(currentPlayer, pieceSize, x, y)) {
				cout << "Invalid move, try again: ";
				cin >> pieceSize >> x >> y;
			}
		}
		else {
			// Jogador IA (Minimax)
			cout << "\nPlayer " << currentPlayer << " (AI) is choosing its move...\n";

			
			
			vector<unsigned> bestMove;
			if (round == 0) {
				bestMove = { 1, 1, 1 };
			}
			else {
				minimax.minimax(s, currentPlayer, bestMove, ct);
			}
			x = bestMove[0];
			y = bestMove[1];
			pieceSize = bestMove[2];

			cout << "AI plays piece " << pieceSize << " at (" << x << ", " << y << ")\n";
			s.put_piece(currentPlayer, pieceSize, x, y);
			std::this_thread::sleep_for(seconds(3));
		}
		if (s.get_status() != 0) {
			cout << "Player " << s.get_status() << " victory!!" << endl;
		}
		currentPlayer = (currentPlayer == 1) ? 2 : 1;
		round++;
	}

	system("clear");
	s.print_board();
	if (s.get_status()) {
		cout << "\nPlayer " << s.get_status() << " victory!!\n\n";
	}
	else {
		cout << "\nDraw!!\n\n";
	}

	return 0;
}