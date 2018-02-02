#include "Board.h"
#include "Robot.h"
#include "Coord.h"
#include "Token.h"

#include <iostream>
#include <vector>

const Coord START(0, -3.5);
const Coord END1(0, -3.5);
const Coord END2(0, 3.5);

const int DROP_PATH[NUM_COLORS] = {5, 4, 3, 0, 1, 2, 6};
const int COLLECT_PATH[24][2] = {
  {3,2},{1,2},{2,2},{0,2},
  {0,1},{2,1},{1,1},{3,1},
  {3,0},{1,0},{2,0},{0,0},
  {0,3},{2,3},{1,3},{3,3},
  {3,4},{1,4},{2,4},{0,4},
  {0,5},{2,5},{1,5},{3,5}
};
const int COLLECT_PATH_SMALL[18][2] = {
  {1,2},{2,2},{0,2},
  {0,1},{2,1},{1,1},
  {1,0},{2,0},{0,0},
  {0,3},{2,3},{1,3},
  {1,4},{2,4},{0,4},
  {0,5},{2,5},{1,5}
};

void simpleAlg(Board* b, int round, bool record) { 
  Robot simpleBot(START);
  simpleBot.recordMoves(record);
  for(int i = 0; i < 6*(round+1); i++) {
    simpleBot.moveToNearestToken(b);
    simpleBot.pickUpToken(b);
    color_opt c = simpleBot.checkTokenColor();
    simpleBot.moveToLocation(SQUARES[c]);
    simpleBot.dropToken();
  }
  Coord l = simpleBot.getLocation();
  if(l.dist(END1) < l.dist(END2)) simpleBot.moveToLocation(END1);
  else simpleBot.moveToLocation(END2);
  simpleBot.printDists();
}

void storeAlg(Board* b, int round, bool record) { 
  StoreBot storeBot(START);
  storeBot.recordMoves(record);
  int stops = (round == 3) ? 24 : 18;
  for(int i = 0; i < stops; i++) {
    int h = (round == 3) ? COLLECT_PATH[i][0] : COLLECT_PATH_SMALL[i][0];
    int k = (round == 3) ? COLLECT_PATH[i][1] : COLLECT_PATH_SMALL[i][1];
    storeBot.moveToLocation(HOLES[h][k]);
    storeBot.pickUpToken(b);
    storeBot.storeToken();
  }
  for(int i = storeBot.numTokens(); i > 0; i--) {
    storeBot.pickClosest();
    color_opt c = storeBot.checkTokenColor();
    storeBot.moveToLocation(SQUARES[c]);
    storeBot.dropToken();
  }
  Coord l = storeBot.getLocation();
  if(l.dist(END1) < l.dist(END2)) storeBot.moveToLocation(END1);
  else storeBot.moveToLocation(END2);
  storeBot.printDists();
}

void sortAlg(Board* b, int round, bool record) { 
  SortBot sortBot(START);
  sortBot.recordMoves(record);
  int stops = (round == 3) ? 24 : 18;
  for(int i = 0; i < stops; i++) {
    int h = (round == 3) ? COLLECT_PATH[i][0] : COLLECT_PATH_SMALL[i][0];
    int k = (round == 3) ? COLLECT_PATH[i][1] : COLLECT_PATH_SMALL[i][1];
    sortBot.moveToLocation(HOLES[h][k]);
    sortBot.pickUpToken(b);
    sortBot.sortToken();
  }
  for(int i = 0; i < NUM_COLORS; i++) {
    sortBot.moveToLocation(SQUARES[DROP_PATH[i]]);
    sortBot.dropStack(static_cast<color_opt>(DROP_PATH[i]));
  }
  Coord l = sortBot.getLocation();
  if(l.dist(END1) < l.dist(END2)) sortBot.moveToLocation(END1);
  else sortBot.moveToLocation(END2);
  sortBot.printDists();
}

int main() {
  std::cout << "Movement codes:" << std::endl;
  std::cout << "1 – robot movement" << std::endl;
  std::cout << "2 – robot rotation" << std::endl;
  std::cout << "3 – vertical arm movement" << std::endl;
  std::cout << "4 – horizontal arm movement" << std::endl;
  std::cout << "5 – sorting plate rotation" << std::endl;
  
  Board platform(8,8);
  for(int round = 1; round <= 3; round++) {
    std::cout << std::endl << "Testing round " << round << ", simpleBot" << std::endl;
    platform.populate(round);
    //platform.checkTokens();
    std::vector<Token> tokens = platform.tokens;
    simpleAlg(&platform, round, true);
    //platform.checkTokens();
    platform.clear();
    
    std::cout << std::endl << "Testing round " << round << ", storeBot" << std::endl;
    platform.populate(tokens);
    //platform.checkTokens();
    storeAlg(&platform, round, true);
    //platform.checkTokens();
    platform.clear();
    
    std::cout << std::endl << "Testing round " << round << ", sortBot" << std::endl;
    platform.populate(tokens);
    //platform.checkTokens();
    sortAlg(&platform, round, true);
    //platform.checkTokens();
    platform.clear();
  }
}
