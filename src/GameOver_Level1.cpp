//
// Created by Acer on 18/04/2025.
//

#include "App.hpp"
#include "AnimatedCharacter.hpp"
#include "Character.hpp"
#include "Util/Time.hpp"
#include "Util/Logger.hpp"

void App::Level_1_GameOver(){
    //cheat UI off
    m_CheatOffUI->SetVisible(false);
    m_CheatOnUI->SetVisible(false);

    // exit
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_GameStartSFX->Play();
        m_CurrentState = State::END;
    }

    BirdFallGameOver();

    //game over ui
    if (m_Bird->GetPosition().y <= -238.0f) {
        m_Bird->SetPosition({m_Bird->GetPosition().x, -238.0f});
        m_GameOver->SetVisible(true);

        if (Util::Input::IsKeyPressed(Util::Keycode::R)) {
            m_Restarted = true;
            m_IsGameStarted = false;
            m_GameOver->SetVisible(false);
            m_IsCheating = false;

            ResetClear();
            m_IsCheating = false;
            m_CurrentState = State::LEVEL_1_START;

            return;
        }

        //next level
        if (Util::Input::IsKeyPressed(Util::Keycode::N)) {
            m_Restarted = false;
            m_Canvas_1->SetVisible(false);
            m_CheatOffUI->SetVisible(false);
            m_CheatOnUI->SetVisible(false);
            m_GameOver->SetVisible(false);
            m_IsGameStarted = false;
            m_IsCheating = false;

            ResetClear();
            m_IsCheating = false;
            m_CurrentState = State::LEVEL_2_START;

            return;
        }
    }
    m_Root.Update();
}