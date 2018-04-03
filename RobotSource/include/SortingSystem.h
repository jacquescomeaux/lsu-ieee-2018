#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H

#include "Color.h"
#include "Token.h"
#include <vector>

#include "Camera.h"
#include "SerialLink.h"

class SortingSystem : private SerialLink {
  private:
    Camera token_cam;
    Token* held_token;
    std::vector<Token*> token_stacks[7];
    void pickUpToken();
    Color checkTokenColor();
    void storeToken(Color) const;
  protected:
    SortingSystem();
  public:
    void sortToken();
    void dropTokenStack(Color);
};

#endif//SORTINGSYSTEM_H
