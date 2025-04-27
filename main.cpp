#include "state.hpp"
#include "minimax.hpp"
#include <iostream>



int main() {
    State s;
    unsigned currentPlayer = 1;
    unsigned pieceSize, x, y;

    // Inicializando o Minimax com o estado atual
    MiniMax minimax;

    while (s.get_status() == 0) {
        system("clear"); // ou "cls" no Windows
        s.print_board();

        if (currentPlayer == 0) {
            // Jogador humano
            cout << "\nPlayer " << currentPlayer << " (You):\n";
            cout << "Enter piece size (1, 2, or 3), x and y coordinates: ";
            cin >> pieceSize >> x >> y;
            while (!s.put_piece(currentPlayer, pieceSize, x, y)) {
                cout << "Invalid move, try again: ";
                cin >> pieceSize >> x >> y;
            }
        } else {
            // Jogador IA (Minimax)
            cout << "\nPlayer " << currentPlayer << " (AI) is thinking...\n";

            // Encontra o melhor movimento da   IA
            int ct = 4;
            vector<unsigned> bestMove;
            minimax.minimax(s, currentPlayer, bestMove,ct);
            x = bestMove[0];
            y = bestMove[1];
            pieceSize = bestMove[2];

            cout << "AI plays piece " << pieceSize << " at (" << x << ", " << y << ")\n";
            s.put_piece(currentPlayer, pieceSize, x, y);
        }
        if(s.get_status() != 0) {
            cout << "Player " << s.get_status() << " victory!!" << endl;
        }
        currentPlayer = (currentPlayer == 0) ? 1 : 0;
    }

    system("clear"); // Limpar tela final
    s.print_board();
    cout << "Player " << s.get_status() << " victory!!" << endl;

    return 0;
}