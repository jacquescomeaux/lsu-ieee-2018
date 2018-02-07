#ifndef SORTINGPLATE_H
#define SORTINGPLATE_H

class SortingPlate {
  private:
    float position;
  protected:
    SortingPlate();
  public:
    void reset();
    void setPosition();
    float getPosition();
};

#endif
