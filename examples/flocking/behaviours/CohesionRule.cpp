#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  Vector2f centerMass = boid->getPosition();
  int boidCount= 1;
  for(Boid* _boid : neighborhood) {
    centerMass += _boid->getPosition();
    boidCount++;
  }
  centerMass /= boidCount; //Finds center mass of the group
  Vector2f vecToCenter = centerMass - boid->getPosition();
  if(vecToCenter.getMagnitude() <= boid->getDetectionRadius()) {
    cohesionForce = vecToCenter / boid->getDetectionRadius();
  }

  return cohesionForce;
}