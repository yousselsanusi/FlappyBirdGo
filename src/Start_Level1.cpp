//
// Created by Acer on 07/03/2025.
//

#include "App.hpp"
#include "Character.hpp"
#include "AnimatedCharacter.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Level_1_Start() {
    InitializeUI();

    m_Canvas_1 = std::make_shared<Character>(RESOURCE_DIR"/Level/Level_1.png"); // left = 435 / right = 835
    m_Canvas_1->SetPosition({0, 0}); //x - to left + to right // - down + up // -205.0f & 205.0f
    m_Canvas_1->SetZIndex(95);
    m_Root.AddChild(m_Canvas_1);

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_GameStartSFX->Play();
        m_CurrentState = State::END;
    }

    m_CurrentState = State::LEVEL_1_UPDATE;
}