#include "../include/Color.h"
#include "../include/Direction.h"
#include "../include/VelocityVector.h"

#include "../include/Board.h"
#include "../include/Robot.h"

#include <iostream>
#include <vector>
#include <list>
#include <tuple>

int main() {
  
  int num_colors = 7;
  int num_holes = 24;
  
  std::vector<Coord> color_squares = {
    Coord(-3.5,  3.5),     //Red
    Coord(-3.5,  0.0),     //Green
    Coord(-3.5, -3.5),     //Blue
    Coord( 3.5,  3.5),     //Cyan
    Coord( 3.5,  0.0),     //Magenta
    Coord( 3.5, -3.5),     //Yellow
    Coord( 0.0,  0.0)      //Gray
  };
  
  std::vector<Coord> token_holes = {
    Coord(-1.0,  1.0), Coord(-1.0,  0.0), Coord(-1.0, -1.0),
    Coord( 1.0, -1.0), Coord( 1.0,  0.0), Coord( 1.0,  1.0),
    Coord(-1.5,  1.5), Coord(-1.5,  0.0), Coord(-1.5, -1.5),
    Coord( 1.5, -1.5), Coord( 1.5,  0.0), Coord( 1.5,  1.5),
    Coord(-2.0,  2.0), Coord(-2.0,  0.0), Coord(-2.0, -2.0),
    Coord( 2.0, -2.0), Coord( 2.0,  0.0), Coord( 2.0,  2.0),
    Coord(-2.5,  2.5), Coord(-2.5,  0.0), Coord(-2.5, -2.5),
    Coord( 2.5, -2.5), Coord( 2.5,  0.0), Coord( 2.5,  2.5)
  };
  
  std::vector<int> collection_path = {20, 14, 8, 2, 1, 7, 13, 19, 18, 12, 6, 0, 5, 11, 17, 23, 22, 16, 10, 4, 3, 9, 15, 21};
  Coord start(0, -3.5);
  Coord end(0, -3.5); 
  
  std::vector<std::list<std::pair<int,double> > > board_map(token_holes.size());
  for(int ring = 0; ring < 4; ring++) for(int line = 0; line < 6; line++) {
    int self = (ring * 6) + line; 
    int neighbor = (ring * 6) + (line + 1) % 6;
    //std::cout << "self = " << self << ", neigh = " << neighbor << std::endl;
    board_map[self].push_back(std::make_pair(neighbor, token_holes[self].dist(token_holes[neighbor])));
    board_map[neighbor].push_back(std::make_pair(self, token_holes[neighbor].dist(token_holes[self])));
    if(ring == 3) continue;
    neighbor = ((ring + 1) * 6) + line;
    board_map[self].push_back(std::make_pair(neighbor, token_holes[self].dist(token_holes[neighbor])));
    board_map[neighbor].push_back(std::make_pair(self, token_holes[neighbor].dist(token_holes[self])));
  }
  
  Board platform(8, 8, color_squares, token_holes, start, end, board_map);
  SortBot robot(&platform);
  
  /*for(int i = 0; i < board_map.size(); i++) {
    std::cout << i << std::endl;
    for(auto& fs : board_map[i]) std::cout << fs.first << ", " << fs.second << std::endl;
  }*/
 
  std::cout << "press enter after the noise" << std::endl; 
  getchar();
  std::cout << "press the green button" << std::endl; 
  robot.setSpeed(50);
  robot.toggleCalibration();
  robot.travel(Direction::FRONT, 40, 12.5, true);
  robot.travel(Direction::CLOCKWISE, 90, 54, true);
  robot.travel(Direction::CLOCKWISE, 90, 54, true);
  robot.toggleCalibration();
  robot.setSpeed(80);
  robot.align(Direction::LEFT, 6);
  std::cout << "hi" << std::endl;
  getchar();
  robot.followLine(Direction::BACK_RIGHT,)
  //robot.followLine(Direction::LEFT);
  //robot.travel(Direction::LEFT, 70, 16, false);
  //while(!robot.followUntilIntersection(Direction::LEFT)) robot.travel(Direction::LEFT, 80, -0.75, false);
  //robot.center();
  //if(!robot.setCurrentIntersection(20)) std::cout << "setCurrentIntersection failed";
  //if(!robot.followPath(collection_path, false)) std::cout << "followPath failed";
  
  return 0;
}
