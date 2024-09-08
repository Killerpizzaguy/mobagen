#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;

  // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  if (!neighborhood.empty()) {
      Vector2f position = boid->transform.position;
      int countCloseFlockmates = 0;
      // todo: find and apply force only on the closest mates
    for(Boid* _boid : neighborhood) {
      Vector2f vecBetween = position - _boid->getPosition(); //Vector from the neighbor to this boid
      float distance = vecBetween.getMagnitude(); //magnitude of vecBetween
      if(distance > 0 && distance <= desiredDistance) { //Checks if the boids are too close to each other
        Vector2f norm = vecBetween / distance; //gets the normal of vecBetween
        separatingForce += norm / distance; //adds the normal to the separating force
      }
    }
  }



  separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
