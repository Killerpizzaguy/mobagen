#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  auto sideOver2 = w->GetSize() / 2; //copied from the functions below, I think it gets the row/column count?
  //If it just started, add the top left cell to the main stack
  if (!started) {
    started = true;
    stack.push_back(Point2D(-sideOver2, -sideOver2));
  }

  //if main stack isn't empty
  if (!stack.empty()) {
    Point2D mainPoint = stack.back();
    std::vector<Point2D> neighbours = getVisitables(w, mainPoint);
    Point2D chosenNeighbour;

    //mark the point as visited
    visited[mainPoint.y][mainPoint.x] = true;
    w->SetNodeColor(mainPoint, Color::Blue);

    //if there are visitable neighbors
    if (neighbours.size() > 0) {
      //get all visitable neighbors


      if (neighbours.size() == 1) {
        chosenNeighbour = neighbours.back();
      }

      //rng a neighbor
      else {
        chosenNeighbour = neighbours[getFakeRandomNumber() % neighbours.size()];
      }

      //remove the wall between current cell and the neighbor
      if (chosenNeighbour.y < mainPoint.y)
        w->SetNorth(mainPoint, false);
      if (chosenNeighbour.x > mainPoint.x)
        w->SetEast(mainPoint, false);
      if (chosenNeighbour.y > mainPoint.y)
        w->SetSouth(mainPoint, false);
      if (chosenNeighbour.x < mainPoint.x)
        w->SetWest(mainPoint, false);

      //add neighbor to the stack
      stack.push_back(chosenNeighbour);
      return true;
    }

    //if there aren't visitable neighbors
    else {
      w->SetNodeColor(mainPoint, Color::Green);
      stack.erase(stack.end());
      return true;
    }
  }




  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  started = false;
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: implement this
  //top
  Point2D top (p.x, p.y - 1);
  if (checkVisitable(top, sideOver2)) {
    visitables.push_back(top);
  }
  //right
  Point2D right(p.x + 1, p.y);
  if (checkVisitable(right, sideOver2)) {
    visitables.push_back(right);
  }
  //bottom
  Point2D bottom (p.x, p.y + 1);
  if (checkVisitable(bottom, sideOver2)) {
    visitables.push_back(bottom);
  }
  //left
  Point2D left(p.x - 1, p.y);
  if (checkVisitable(left, sideOver2)) {
    visitables.push_back(left);
  }
  std::cout<<"visitables size: "<<visitables.size()<<std::endl;

  return visitables;
}

bool RecursiveBacktrackerExample::checkVisitable(Point2D p, int sideOver2) {
  if (p.y >= -sideOver2 && p.y <= sideOver2 && p.x >= -sideOver2 && p.x <= sideOver2) {
    return !visited[p.y][p.x];
  }
  return false;
}


int RecursiveBacktrackerExample::getFakeRandomNumber() { //function to get from the fixed set of random values that the assignment said to use
  int rand = FAKE_RANDOM_ARRAY[fakeRandomIndex];
  fakeRandomIndex++;
  if (fakeRandomIndex > FAKE_RANDOM_SIZE-1) {
    fakeRandomIndex = 0;
  }
  return rand;
}

