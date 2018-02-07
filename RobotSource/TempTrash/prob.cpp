#include "Board.h"
#include "Robot.h"
#include "Coord.h"
#include "Token.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <cmath>

const int REPS = 100000;
//const int GRAPH_SIZE_X = 260;
//const int GRAPH_SIZE_Y = 70;
const int GRAPH_SIZE_X = 80;
const int GRAPH_SIZE_Y = 20;
//const int GRAPH_SIZE_X = 130;
//const int GRAPH_SIZE_Y = 30;

const Coord START(0, -3.5);
const Coord END1(0, -3.5);
const Coord END2(0, 3.5);

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

void simpleAlg(Board* b, Robot& r, int round) { 
  for(int i = 0; i < 6*(round+1); i++) {
    r.moveToNearestToken(b);
    r.pickUpToken(b);
    r.moveToLocation(SQUARES[r.checkTokenColor()]);
    r.dropToken();
  }
  Coord l = r.getLocation();
  if(l.dist(END1) < l.dist(END2)) r.moveToLocation(END1);
  else r.moveToLocation(END2);
}

void storeAlg(Board* b, StoreBot& r, int round) { 
  int stops = (round == 3) ? 24 : 18;
  for(int i = 0; i < stops; i++) {
    int h = (round == 3) ? COLLECT_PATH[i][0] : COLLECT_PATH_SMALL[i][0];
    int k = (round == 3) ? COLLECT_PATH[i][1] : COLLECT_PATH_SMALL[i][1];
    r.moveToLocation(HOLES[h][k]);
    r.pickUpToken(b);
    r.storeToken();
  }
  for(int i = r.numTokens(); i > 0; i--) {
    r.pickClosest();
    r.moveToLocation(SQUARES[r.checkTokenColor()]);
    r.dropToken();
  }
  Coord l = r.getLocation();
  if(l.dist(END1) < l.dist(END2)) r.moveToLocation(END1);
  else r.moveToLocation(END2);
}

void plot(std::map<double, int, std::less<double> >& dists, std::map<int, int, std::less<int> >& columns, int round, std::string name) {
  double xmin = dists.begin()->first; 
  double xmax = dists.rbegin()->first; 
  double xstep = (xmax - xmin) / (double)GRAPH_SIZE_X;
  int chunk = 1;
  double sum = 0;
  for(auto const& x : dists) sum += x.first * (double)x.second;
  double mean = sum / (double)REPS;
  double var = 0;
  for(auto const& x : dists) var += std::pow((x.first - mean), 2) * x.second/(double)REPS;
  double stddev = std::sqrt(var);
  for(auto const& x : dists) {
    if(x.first <= xmin+((double)chunk*xstep)) columns[chunk] += + x.second;
    else columns[++chunk] += x.second;
  }
  int ymax = columns.begin()->second; 
  for(auto const& x : columns) if(x.second > ymax) ymax = x.second;
  double ystep = (double)ymax / (double)GRAPH_SIZE_Y;
  for(auto& x : columns) x.second = std::round((double)x.second / ystep);
  std::cout << "======";
  for(int i = 0; i < GRAPH_SIZE_X; i++) std::cout << "=";
  std::cout << std::endl << name << " Round " << round << ", " << REPS << " iterations..."<< std::endl << "ft^-1 %" << std::endl;
  for(int y = GRAPH_SIZE_Y; y >= 0; y --) {
    if(!(y%5)) std::cout << std::setw(4) << std::setprecision(2) << 100 * ((double)y/(double)GRAPH_SIZE_Y) * ((double)ymax/(double)REPS) * (1/xstep) << "||";
    else std::cout << "    ||";
    for(int x = 1; x <= GRAPH_SIZE_X; x++) {
      if(columns[x] >= y) std::cout << "*";
      else std::cout << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "======";
  for(int i = 0; i < GRAPH_SIZE_X; i++) std::cout << "=";
  std::cout << std::endl << " ft";
  for(int i = 0; i <= GRAPH_SIZE_X; i++) if(!(i%5)) std::cout << std::setw(5) << (int)xmin + (int)((double)i*xstep);
  std::cout << std::fixed << std::endl;
  std::cout << "Minimum distance: " << xmin << " ft" << std::endl;
  std::cout << "Maximum distance: " << xmax << " ft" << std::endl; 
  std::cout << "Expected value: " << mean << " ft" << std::endl;
  std::cout << "Standard deviation: " << stddev << " ft" << std::endl;
}

int main() {
  Board platform(8,8);
  for(int round = 1; round <= 3; round++) {
    std::map<double, int, std::less<double> > simpledists, storedists;
    std::map<int, int, std::less<int> > simplecolumns, storecolumns;
    for(int j = 0; j < REPS; j++) {
      platform.populate(round);
      std::vector<Token> tokens = platform.tokens;
      Robot simpleBot(START);
      simpleAlg(&platform, simpleBot, round);
      simpledists[simpleBot.getDist()] += 1;
      platform.clear();
      
      platform.populate(tokens);
      StoreBot storeBot(START);
      storeAlg(&platform, storeBot, round);
      storedists[storeBot.getDist()] += 1;
      platform.clear();
    }
    plot(simpledists, simplecolumns, round, "SimpleBot");
    plot(storedists, storecolumns, round, "StoreBot");
  }
}
