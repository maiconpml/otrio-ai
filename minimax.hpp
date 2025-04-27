#pragma once
#include "state.hpp"
#include <limits>
#include <tuple>

class MiniMax {
  public:


      int minimax(State &state, unsigned player, vector<unsigned> & bestMove, int depth ) {

        int best_move_aux = -1;

        int bestVal = player == 1 ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
        unsigned winner = state.get_status();
        if(winner == 1) return -10;
        if(winner == 2) return 10;
        if(depth == 0) return 0;
		vector<vector<unsigned>> possible_moves = state.possibleMoves(player);
        if(possible_moves.size() == 0) return 0;
        vector<State> possible_states(possible_moves.size(),state);
        for(unsigned i = 0; i < possible_moves.size(); i++) {
          possible_states[i].put_piece(player,possible_moves[i][2],possible_moves[i][0],possible_moves[i][1]);
          int valAux = minimax(possible_states[i],player == 1 ? 0:1,bestMove,depth -1);
          if(player == 0){
            if(bestVal > valAux || (valAux == 0 && bestVal < valAux)){
              bestVal = valAux;
              best_move_aux = i;
         	}
        }
        else{
           if(bestVal < valAux || (valAux == 0 && bestVal > valAux)){
              bestVal = valAux;
              best_move_aux = i;
         	}
        }


      }
       bestMove = possible_moves[best_move_aux];
        return bestVal;
}

};