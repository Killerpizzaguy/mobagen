#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood
  float boidCount = 1;
  averageVelocity += boid->getVelocity(); //adds the velocity of this boid since it isn't included in the neighborhood

  for (Boid* _boid : neighborhood){
    averageVelocity = averageVelocity + _boid->getVelocity(); //adds the velocity of all the boids in the neighborhood
    boidCount++;
  }
  averageVelocity = averageVelocity / boidCount; //divides by total amount of boids to get the average

  return Vector2f::normalized(averageVelocity);
}