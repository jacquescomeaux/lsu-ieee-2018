#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H

#include "Color.h"
#include "Token.h"
#include <vector>

#include "Camera.h"
#include "SerialLink.h"

class SortingSystem : private SerialLink {
  private:
    const int COLOR_POSITIONS[8];
    Camera token_cam;
    Token* held_token;
    std::vector<Token*> token_stacks[7];
    int plate_position;
    bool pickUpToken();
    void storeToken(Token*);
  protected:
    SortingSystem();
  public:
    void sortToken1();
    void sortToken2();
    bool dropTokenStack(Color);
};

#endif//SORTINGSYSTEM_H
