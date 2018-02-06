#ifndef ROBOT_H
#define ROBOT_H

#include "Coord.h"
#include "Token.h"
#include "Board.h"

#include "rs232.h"

#include <vector>

static const double GRAB_DIST = 0.02; //Max error distance for successfully picking up token
static const double VERT_DIST = 0.20; //Arm vertical displacement
static const double SIDE_DIST = 0.10; //StoreBot arm horizontal displacement
static const int STACK_POS[NUM_COLORS] = {4, 3, 2, 5, 6, 7, 1}; //Order of token colors on sorting plate

static const int PORTNUM = 24;

class Robot {
  private:
    Coord location;
    float heading;
    //float totaldist; //Total distance covered
    //float totalrot; //Total robot rotation
    //float totalvert; //Total vertical arm movement
    
    union multinum {
      float floating;
      int integer;
      unsigned char data[4];
    };
    
//    Drivetrain wheels;
//    ProximitySensor ultra;
//    SensorRing line_sensors;
//    Camera logitech;
//    Camera noir;
//    
//    MotorController arduino;
//    RGBSensor token sensor;
//    SortingSystem sorter;
    
    int receiveNumber() const;
    float receiveNumber() const;
    void transmitNumber(int t) const{
    void transmitNumber(float t) const{

  protected:
    Token* held; //Token arm currently held token
    bool record; //Prints movements to stdout if true
  public:
    Robot();
    Robot(Coord l);
    Controller control;
    
    void determineLocation();

    Coord getLocation() const;
    float getHeading() const;
    
    void rotateToAngle(float);
    void followLine(); //Follows line until intersection
    
    
    void pickUpToken();  
    color_opt checkTokenColor() const; //Returns color of currently held token
    void dropToken(); //Drops currently held token
    void printDists() const; //Prints distance totals to stdout
    //void moveToLocation(Coord);
    //void moveToNearestToken(Board*); //Moves robot to nearest incorrect token on board
    
    
    //void recordMoves(bool);
    //float getDist() const;
    //float getRot() const;
    //float getVert() const;
};

class SortBot : public Robot {
  private:
    float totalplate;
    int topplate; //Sorting plate position
    int botplate; //Selector plate positon
    std::vector<Token*> stacks[NUM_COLORS]; //Sorting stacks on robot, one for each color
    void placeTokenInStack(color_opt);
    void rotatePlates(int);
    void rotateTop(int);
  public:
    SortBot();
    SortBot(Coord);
    void sortToken(); //Places currently held token in appropriate color stack
    void dropStack(color_opt); //Drops entire colored stack of tokens
    void printDists() const;
    float getPlate() const;
};

#endif
