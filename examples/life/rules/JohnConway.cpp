#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  int worldSize = world.SideSize();

  for (int y = 0; y < worldSize; y++) {
    for (int x = 0; x < worldSize; x++) {
      Point2D testPoint(x,y);
      int livingNeighbors = CountNeighbors(world, testPoint);

      world.SetNext(testPoint, world.Get(testPoint)); //assumes the cell won't change by default

      if(world.Get(testPoint)) { //checks if cell is alive
        if(livingNeighbors < 2 || livingNeighbors > 3) { //checks if cell should die
          world.SetNext(testPoint, false);
        }
      }

      else if(livingNeighbors == 3) { //if the cell is dead, checks if it should be alive
           world.SetNext(testPoint, true);
      }
    }
  }
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
