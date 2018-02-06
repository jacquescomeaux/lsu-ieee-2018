#include <iostream>
#include "Token.h"
#include "Board.h"
#include "Robot.h"
#include "Coord.h"

const Coord START(-3.5, 0);
const Coord END(-3.5, 0);
const int DROP_PATH[NUM_COLORS] = {5, 4, 3, 0, 1, 2, 6};
const int COLLECT_PATH[NUM_RINGS*(NUM_COLORS-1)][2] = {
  {3,2},{1,2},{2,2},{0,2},
  {0,1},{2,1},{1,1},{3,1},
  {3,0},{1,0},{2,0},{0,0},
  {0,3},{2,3},{1,3},{3,3},
  {3,4},{1,4},{2,4},{0,4},
  {0,5},{2,5},{1,5},{3,5}
};

void fixedPath(SortBot* r, Board* b) {
  for(int i = 0; i < NUM_RINGS*(NUM_COLORS-1); i++) {
    int h = COLLECT_PATH[i][0];
    int k = COLLECT_PATH[i][1];
    r->moveToLocation(HOLES[h][k]);
    r->pickUpToken(b);
    r->sortToken();
  }
}

int main(int argc, char *argv[]) {
  int ROUND = std::stoi(argv[1]);
 
  Board platform(8, 8);
  platform.populate(ROUND);
  SortBot sorty;
  sorty.control.algorithm

  std::cout << std::endl << "Round " << ROUND << ", SortBot" << std::endl;
  platform.populate(ROUND);
  std::vector<Token> tokens = platform.tokens;
  platform.checkTokens();
  SortBot sorty(START);
  std::cout << "Collecting tokens..." << std::endl;
  for(int i = 0; i < 6*(ROUND+1); i++) {
    sorty.moveToNearestToken(&platform);
    sorty.pickUpToken(&platform);
    sorty.sortToken();
  }
  std::cout << "Distributing tokens..." << std::endl;
  for(int i = 0; i < NUM_COLORS; i++) {
    sorty.moveToLocation(SQUARES[DROP_PATH[i]]);
    sorty.dropStack(static_cast<color_opt>(DROP_PATH[i]));
  }
  sorty.moveToLocation(END);
  platform.checkTokens();
  sorty.printDists();
  platform.clear(); 
  
  std::cout << std::endl << "Round " << ROUND << ", StoreBot" << std::endl;
  platform.populate(tokens);
  platform.checkTokens();
  StoreBot storey(START);
  std::cout << "Collecting tokens..." << std::endl;
  for(int i = 0; i < 6*(ROUND+1); i++) {
    storey.moveToNearestToken(&platform);
    storey.pickUpToken(&platform);
    storey.storeToken();
  }
  std::cout << "Distributing tokens..." << std::endl;
  for(int i = storey.numTokens(); i > 0; i--) {
    storey.pickClosest();
    storey.moveToLocation(SQUARES[storey.checkTokenColor()]);
    storey.dropToken();
  }
  storey.moveToLocation(END);
  platform.checkTokens();
  storey.printDists();
  platform.clear();
  
  std::cout << std::endl << "Round " << ROUND << ", SimpleBot" << std::endl;
  platform.populate(tokens);
  platform.checkTokens();
  Robot simple(START);
  std::cout << "Collecting and distributing tokens..." << std::endl;
  for(int i = 0; i < 6*(ROUND+1); i++) {
    simple.moveToNearestToken(&platform);
    simple.pickUpToken(&platform);
    simple.moveToLocation(SQUARES[simple.checkTokenColor()]); 
    simple.dropToken();
  }
  simple.moveToLocation(END);
  platform.checkTokens();
  simple.printDists();
  platform.clear();
}
