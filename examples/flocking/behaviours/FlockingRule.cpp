#include "FlockingRule.h"

#include "Utils.h"
#include "Boid.h"
#include "imgui.h"
#include "../ImGuiExtra.h"

using namespace utils;

FlockingRule::FlockingRule(const FlockingRule& toCopy){
    weight = toCopy.weight;
    debugColor = toCopy.debugColor;
    force = toCopy.force;
    isEnabled = toCopy.isEnabled;
}

Vector2 FlockingRule::computeWeightedForce(const std::vector<Boid*>& neighbordhood, Boid* boid) {
    //the computed force is cached in a var
    if (isEnabled) {
        force = getBaseWeightMultiplier() * weight * computeForce(neighbordhood, boid);
    }
    else
    {
        //If the rule is not enabled, return vector zero.
        force = Vector2::zero();
    }

    return force;
}

bool FlockingRule::drawImguiRule() {
    bool valueHasChanged = false;

    ImGui::SetNextItemOpen(isEnabled, ImGuiCond_Once); //Opened by default if rule active
    if (ImGui::TreeNode(getRuleName())) {
        ImguiTooltip(getRuleExplanation());

        if (ImGui::Checkbox("Enabled", &isEnabled)){
            valueHasChanged = true;
        }

        if (isEnabled) {
            if (ImGui::DragFloat("Weight##", &weight, 0.025f)){
                valueHasChanged = true;
            }

            ImGui::SameLine(); HelpMarker("Drag to change the weight's value or CTRL+Click to input a new value.");

            //Additional settings rule-dependant
            if (drawImguiRuleExtra()) {
                valueHasChanged = true;
            }
        }

        ImGui::TreePop();
    }
    else {
        ImguiTooltip(getRuleExplanation());
    }

    return valueHasChanged;
}

void FlockingRule::draw(const Boid& boid, sf::RenderTarget& target, sf::RenderStates states) const {
    //Scaled by 1.5f to see it more easily on screen.
    graphics::drawVector(target, states, boid.getPosition(), force * 1.5f, debugColor);
}



