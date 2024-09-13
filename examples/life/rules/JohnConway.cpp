#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
  int livingNeighbors = 0;
  for (int i=-1; i<=1; i++) {
    for (int j=-1; j<=1; j++) {
      Point2D testPoint(point.x+i, point.y+j);
      if(testPoint != point && world.Get(testPoint)) {
        livingNeighbors++;
      }
    }
  }
  return livingNeighbors;
}
