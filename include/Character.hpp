//
// Created by Acer on 08/03/2025.
//

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include "Util/GameObject.hpp"
#include "Util/Input.hpp"

class Character : public Util::GameObject {
public:
    explicit Character(const std::string& ImagePath);

    Character(const Character&) = delete;

    Character(Character&&) = delete;

    Character& operator=(const Character&) = delete;

    Character& operator=(Character&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    // TODO: Implement the collision detection
    bool IfCollides(const std::shared_ptr<Character>& other) const {
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

    // TODO: Add and implement more methods and properties as needed to finish Giraffe Adventure.


private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
};

#endif //CHARACTER_HPP
