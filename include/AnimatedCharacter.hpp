//
// Created by Acer on 21/03/2025.
//

#ifndef ANIMATEDCHARACTER_HPP
#define ANIMATEDCHARACTER_HPP

#include <vector>
#include <string>

#include "Character.hpp"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class AnimatedCharacter : public Util::GameObject {

public:
    explicit AnimatedCharacter(const std::vector<std::string>& AnimationPaths){
        m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, true, 100, true, 0);
    }

    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }

    bool IfCollides (const std::shared_ptr<Character>& other) const {
        //character position
        float characterLeft   = GetPosition().x - GetScaledSize().x / 2;
        float characterRight  = GetPosition().x + GetScaledSize().x / 2;
        float characterTop    = GetPosition().y + GetScaledSize().y / 2;
        float characterBottom = GetPosition().y - GetScaledSize().y / 2;

        //other character position
        float otherLeft   = other->GetPosition().x - other->GetScaledSize().x / 2;
        float otherRight  = other->GetPosition().x + other->GetScaledSize().x / 2;
        float otherTop    = other->GetPosition().y + other->GetScaledSize().y / 2;
        float otherBottom = other->GetPosition().y - other->GetScaledSize().y / 2;

        // AABB Collision Check
        bool isColliding = (characterRight > otherLeft && characterLeft < otherRight &&
                            characterTop > otherBottom && characterBottom < otherTop);

        return isColliding;
    }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    void SetRotation(const float Rotation) { m_Transform.rotation = Rotation; }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
};

#endif //ANIMATEDCHARACTER_HPP
