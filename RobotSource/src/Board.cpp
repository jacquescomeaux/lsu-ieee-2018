#include "../include/Board.h"

#include <cmath>
#include <iostream>
#include <set>

Board::Board(double l, double w, const std::vector<Coord>& S, const std::vector<Coord>& H, Coord start, Coord end, const std::vector<std::list<std::pair<int,double> > >& L) :
  LENGTH(l),
  WIDTH(w),
  NUM_COLORS(S.size()),
  NUM_HOLES(H.size()),
  SQUARES(S),
  HOLES(H),
  START(start),
  END(end),
  LINES(L) {};

double Board::getLength() const {
  return LENGTH;
}

double Board::getWidth() const {
  return WIDTH;
}
Coord Board::getStart() const {
  return START;
}

Coord Board::getEnd() const {
  return END;
}

Coord Board::getIntersectionLocation(int n) const {
  return HOLES[n];
}

bool Board::getShortestPath(std::vector<int>* path, int src, int dest) {
  //Dijkstra's shortest path algorithm
  std::set<int> Q;
  for(int i = 0; i < HOLES.size(); i++) Q.insert(i);
  std::vector<double> dist(HOLES.size(), LENGTH + WIDTH);
  std::vector<int> prev(HOLES.size(), -1);
  dist[dest] = 0;
  while(!Q.empty()) {
    double min = LENGTH + WIDTH;
    int u = *Q.begin();
    for(int v : Q) if(dist[v] < min) {
      min = dist[v];
      u = v;
    }
    Q.erase(Q.find(u));
    if(u == src) break;
    for(auto& fs : LINES[u]) if(Q.count(fs.first) != 0) {
      double alt = dist[u] + fs.second;
      if(alt < dist[fs.first]) {
        dist[fs.first] = alt;
        prev[fs.first] = u; 
      }
    }
  }
  for(int u = prev[src]; u != -1; u = prev[u]) path->push_back(u);
  return true;
}

void Board::checkTokens() const {
  for(int i = 0; i < tokens.size(); i++) {
    double x = tokens[i].getLocation().x;
    double y = tokens[i].getLocation().y;
    Color c = tokens[i].getColor();
    std::string s;
    switch(c) {
      case Color::RED : s = "Red"; break;
      case Color::GREEN : s = "Green"; break;
      case Color::BLUE : s = "Blue"; break;
      case Color::CYAN : s = "Cyan"; break;
      case Color::MAGENTA : s = "Magenta"; break;
      case Color::YELLOW : s = "Yellow"; break;
      case Color::GRAY : s = "Gray"; break;
      default : s = "Error";
    }
    if((std::abs(x-SQUARES[static_cast<int>(c)].x) < 0.5) && (std::abs(y-SQUARES[static_cast<int>(c)].y) < 0.5)) std::cout << "Correct:   ";
    else std::cout << "Incorrect: ";
    std::cout << s << " token at location (" << x << ", " << y << ")" << std::endl;
  }
}

void Board::clear() {
  tokens.clear();
}
