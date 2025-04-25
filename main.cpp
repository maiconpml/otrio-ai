#include <iostream>
#include "state.hpp"
#include <cstdlib>

int main() {

	State s;
	unsigned currentPlayer = 0;
	unsigned pieceSize, x, y;
	while (s.get_status() == 0) {
		system("clear");
		s.print_board();
		cout << endl << "Player " << currentPlayer << ":" << endl;
		cin >> pieceSize >> x >> y;
		s.put_piece(currentPlayer, pieceSize, x, y);
		currentPlayer = currentPlayer == 0 ? 1 : 0;
	}

	s.print_board();
	cout << "Player " << currentPlayer + 1 << "victory!!" << endl;
}