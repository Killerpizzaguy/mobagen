#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points
  bool borderFound = false;

  while (!frontier.empty()) {
    // get the current from frontier
    Point2D current = frontier.front();
    //might need to do frontier.pop();
    // remove the current from frontierset
    frontierSet.erase(current);
    // mark current as visited
    visited[current] = false;
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> neighbors;

    for (auto neighbor : w->neighbors(current)) {
      if (!w->getContent(neighbor) && !visited[neighbor]) { //Checks if the neighbor is empty and hasn't been visited yet
        bool valid = true;
        for (auto point : frontier) { //makes sure the neighbor isn't already in the frontier
            if(point == neighbor) {
              valid = false;
              break;
            }
          }
        if(valid) {
          neighbors.push_back(neighbor);
        }
      }
    }

    // iterate over the neighs:
    for (auto neighbor : neighbors) {
      // for every neighbor set the cameFrom
      cameFrom[neighbor] = current;
      // enqueue the neighbors to frontier and frontierset
      frontier.push(neighbor);
      frontierSet.insert(neighbor);
      // do this up to find a visitable border and break the loop
      if(!w->isValidPosition(neighbor)) {
        borderFound = true;
        borderExit = neighbor; //should this be current or neighbor?
        break;
      }
    }

  if(borderFound) {
    break;
  }

  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}
