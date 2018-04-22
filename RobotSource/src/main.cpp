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
  
  //shortest path to collect all tokens
  std::vector<int> collection_path = {20, 14, 8, 2, 1, 7, 13, 19, 18, 12, 6, 0, 5, 11, 17, 23, 22, 16, 10, 4, 3, 9, 15, 21};
  Coord start(0, -3.5);
  Coord end(0, -3.5); 
  
  //create adjacency list of board lines
  std::vector<std::list<std::pair<int,double> > > board_map(token_holes.size());
  for(int ring = 0; ring < 4; ring++) for(int line = 0; line < 6; line++) {
    int self = (ring * 6) + line; 
    int neighbor = (ring * 6) + (line + 1) % 6;
    board_map[self].push_back(std::make_pair(neighbor, token_holes[self].dist(token_holes[neighbor])));
    board_map[neighbor].push_back(std::make_pair(self, token_holes[neighbor].dist(token_holes[self])));
    if(ring == 3) continue;
    neighbor = ((ring + 1) * 6) + line;
    board_map[self].push_back(std::make_pair(neighbor, token_holes[self].dist(token_holes[neighbor])));
    board_map[neighbor].push_back(std::make_pair(self, token_holes[neighbor].dist(token_holes[self])));
  }
  
  //construct board and sortbot objects
  Board platform(8, 8, color_squares, token_holes, start, end, board_map);
  SortBot robot(&platform);
 
  //begin algorithm
  std::cout << "press enter after the noise" << std::endl; 
  getchar();
  std::cout << "press the green button" << std::endl; 
  
  //calibrate line sensors
  robot.setSpeed(50);
  robot.toggleCalibration();
  robot.travel(Direction::FRONT, 40, 12.5, true);
  robot.travel(Direction::CLOCKWISE, 90, 54, true);
  robot.travel(Direction::CLOCKWISE, 90, 54, true);
  robot.toggleCalibration();
  
  //get to first intersection
  robot.setSpeed(80);
  robot.align(Direction::LEFT, 6);
  while(!robot.followUntilIntersection(Direction::LEFT)) robot.travel(Direction::LEFT, 80, -0.75, false);
  robot.center();
  if(!robot.setCurrentIntersection(20)) std::cout << "setCurrentIntersection failed";
  
  //collect tokens
  int visited = robot.followPath(collection_path, true);
  std::cout << "followPath finished, visited " << visited << " tokens" << std::endl;
  if(visited != collection_path.size()) return 0;
  
  //drop off tokens
  Direction drop_sequence[6] = {
    Direction::BACK_RIGHT, Direction::RIGHT, Direction::FRONT_RIGHT,
    Direction::FRONT_LEFT, Direction::LEFT, Direction::BACK_LEFT
  };
  Direction box_sequence[6] = {
    Direction::FRONT, Direction::FRONT, Direction::LEFT,
    Direction::BACK, Direction::BACK, Direction::LEFT
  };
  double dist_sequence[6] = {16.97, 12, 16.97, 16.97, 12, 16.97};
  Color color_sequence[7] = {Color::YELLOW, Color::MAGENTA, Color::CYAN, Color::RED, Color::GREEN, Color::BLUE, Color::GRAY}
  for(int i = 0; i < 6; i++) {
    robot.travel(drop_sequence[i], 70, dist_sequence[i], true);
    robot.dropTokenStack(color_sequence[i]);
    robot.setSpeed(70);
    robot.travel(box_sequence[i], 70, 10, true);
    robot.moveUntilLine(drop_sequence[(i+3)%6], 80);
    robot.align(box_sequence[i], 5);
    robot.followLine(box_sequence[i]);
    robot.travel(box_sequence[i], 70, 8, false);
    if(!robot.followUntilIntersection(box_sequence[i])) while(!findIntersection(box_sequence[i]));
    robot.center();
  }

  //get to center square
  if(!robot.setCurrentIntersection(20)) std::cout << "setCurrentIntersection failed";
  robot.goToIntersection(2);
  robot.travel(Direction::FRONT_RIGHT, 65, 6, true);

  //return to start
  robot.travel(Direction::FRONT, 65, 40, true);

  return 0;
}
