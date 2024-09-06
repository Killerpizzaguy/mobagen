#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood
  float boidCount = 1;
  averageVelocity += boid->getVelocity();

  for (Boid* _boid : neighborhood){
    averageVelocity = averageVelocity + _boid->getVelocity();
    boidCount++;
  }
  averageVelocity = averageVelocity / boidCount;

  return Vector2f::normalized(averageVelocity);
}