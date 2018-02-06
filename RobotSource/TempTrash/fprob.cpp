#include "Board.h"
#include "Robot.h"
#include "Coord.h"

#include <iostream>
#include <queue>

const int REPS = 3000;
const int GRAPH_STEPS = 30;
const double GRAPH_SCALE = 0.4;
const double GRAPH_UNIT = 5;

const Coord START(-3.5, 0);
const Coord END(-3.5, 0);

typedef std::priority_queue<double, std::vector<double>, std::greater<double> > prioque;

void display(prioque& d); 
void simpleAlg(Board* b, int round);
void simpleAlg(Board* b, int round, prioque& d); 

void display(prioque& d) { 
  if(d.empty()) return;
  int s = d.size();
  double offset = d.top();
  std::cout << offset << "\t";
  //double stars[GRAPH_STEPS] = {0};
  /*for(int i = 0; i < GRAPH_STEPS; i++) {
    //std::cout << "diddly" ;
    while(d.top() < offset+(i+1)*GRAPH_SCALE) {
    std::cout <<"+";
    stars[i] += (1/GRAPH_UNIT);
    d.pop();
    if(d.empty()) break;
  }}
  for(int i = 0; i < GRAPH_STEPS; i++) {
    for(int j = 0; j < stars[i]; j++) std::cout << "*";
    std::cout << std::endl;
  }*/
  for(int i = 0; i < s; i++) {
    std::cout << "*";
    if(d.top() > offset + GRAPH_SCALE) {
      std::cout << std::endl << d.top() << "\t";
      offset += GRAPH_SCALE;
    }
    d.pop();
  }
  std::cout << std::endl;
}

void simpleAlg(Board* b, int round) {
  prioque d;
  simpleAlg(b, round, d);
}

void simpleAlg(Board* b, int round, prioque& d) { 
  Robot simple(START);
  for(int i = 0; i < 6*(round+1); i++) {
    simple.moveToNearestToken(b);
    simple.pickUpToken(b);
    color_opt c = simple.checkTokenColor();
    simple.moveToLocation(SQUARES[c]);
    simple.dropToken();
  }
  simple.moveToLocation(END);
  //simple.printDists();
  d.push(simple.getDist());
}

int main() {
  Board platform(8,8);
  for(int round = 1; round <= 3; round++) {
    std::cout << "Testing round " << round << std::endl;
    prioque dists;
    for(int i = 0; i < REPS; i++) {
      platform.populate(round);
      simpleAlg(&platform, round, dists);
      platform.clear();
    }
    display(dists);
  }
}
