#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  Vector2f centerMass = boid->getPosition(); //adds the position of this boid since it isn't included in the neighborhood
  int boidCount= 1;
  for(Boid* _boid : neighborhood) {
    centerMass += _boid->getPosition(); //adds the positions of all the boids in the neighborhood
    boidCount++;
  }
  centerMass /= boidCount; //Finds center mass of the group
  Vector2f vecToCenter = centerMass - boid->getPosition(); //gets the vector from the boid to the center of the group
  if(vecToCenter.getMagnitude() <= boid->getDetectionRadius()) {
    cohesionForce = vecToCenter / boid->getDetectionRadius(); //if the center is within the detection radius of the boid add force in that direction
  }

  return cohesionForce;
}