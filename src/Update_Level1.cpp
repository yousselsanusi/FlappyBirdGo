//
// Created by Acer on 07/03/2025.
//

#include "App.hpp"
#include "Character.hpp"
#include "AnimatedCharacter.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"

void App::Level_1_Update() {
    //exit
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_GameStartSFX->Play();
        m_CurrentState = State::END;
    }

    static int lastScore = 0;
    if (m_Restarted) {
        lastScore = 0;
        m_Restarted = false;
    }

    //to start the game
    if (!m_IsGameStarted) {
        if (Util::Input::IsKeyPressed(Util::Keycode::SPACE)) {
            m_IsGameStarted = true;
            m_FlappingSFX->Play();
        }
    }

    if (m_IsWinning) {
        m_YouWin->SetVisible(true);
        m_Canvas_1->SetVisible(false);

        if (Util::Input::IsKeyPressed(Util::Keycode::N)) {
            m_IsWinning = false;
            m_YouWin->SetVisible(false);
            m_CheatOffUI->SetVisible(false);
            m_CheatOnUI->SetVisible(false);

            ResetClear();

            m_Restarted = false;
            m_IsGameStarted = false;
            m_IsCheating = false;
            m_CurrentState = State::LEVEL_2_START;

            return;
        }

        if (Util::Input::IsKeyPressed(Util::Keycode::R)) {
            m_IsWinning = false;
            m_YouWin->SetVisible(false);
            m_CheatOffUI->SetVisible(false);
            m_CheatOnUI->SetVisible(false);

            m_IsWinning = false;
            m_IsCheating = false;
            m_Restarted = true;
            m_IsGameStarted = false;

            ResetClear();
            m_CurrentState = State::LEVEL_1_START;

            return;
        }
        m_Root.Update();
        return;
    }

    //next level
    if (Util::Input::IsKeyPressed(Util::Keycode::N)) {
        m_Restarted = false;
        m_Canvas_1->SetVisible(false);
        m_CheatOffUI->SetVisible(false);
        m_CheatOnUI->SetVisible(false);

        ResetClear();

        m_IsCheating = false;
        m_IsGameStarted = false;
        m_CurrentState = State::LEVEL_2_START;

        return;
    }

    //cheat on
    if (!m_IsCheating) {
        if (Util::Input::IsKeyPressed(Util::Keycode::C)) {
            m_IsCheating = true;
            m_GameStartSFX->Play();

            m_CheatOffUI->SetVisible(false);
            m_CheatOnUI->SetVisible(true);
        }
    }

    //cheat off
    if (m_IsCheating) {
        if (Util::Input::IsKeyPressed(Util::Keycode::O)) {
            m_IsCheating = false;
            m_GameStartSFX->Play();

            m_CheatOnUI->SetVisible(false);
            m_CheatOffUI->SetVisible(true);
        }
        //LOG_DEBUG("cheating is {}", m_IsCheating);
    }

    //pause
    if (!m_IsPaused) {
        if (Util::Input::IsKeyPressed(Util::Keycode::P)) {
            m_IsPaused = true;
            m_GameStartSFX->Play();
        }
    }

    //option in pause
    if (m_IsPaused) {
        if (Util::Input::IsKeyPressed(Util::Keycode::SPACE)) {
            m_IsPaused = false;
            m_GameStartSFX->Play();
        }
        m_Root.Update();
        return;
    }

    //game hasn't started so render UI only
    if (!m_IsGameStarted) {
        m_Root.Update();
        return;
    }

    BirdMovement();

    //pipe movement
    int score = 0;
    for (int i = 0; i < 20; ++i) {
        m_PipeUp[i]->SetPosition({m_PipeUp[i]->GetPosition().x - 1.8, m_PipeUp[i]->GetPosition().y});
        m_PipeDown[i]->SetPosition({m_PipeDown[i]->GetPosition().x - 1.8, m_PipeDown[i]->GetPosition().y});

        if (!m_IsCheating) {
            if (m_Bird->IfCollides(m_PipeUp[i]) || m_Bird->IfCollides(m_PipeDown[i])) {
                m_CollideSFX->Play();
                m_BirdVelocityY = -10.0f;
                m_BirdAngle = -0.5f;
                m_Canvas_1->SetVisible(false);

                ClearPointUI();

                m_CurrentState = State::LEVEL_1_GAMEOVER;

                return;
            }
        }

        if ((m_PipeUp[i]->GetPosition().x + m_PipeUp[i]->GetScaledSize().x / 2 + 60.0f) < (m_Bird->GetPosition().x + m_Bird->GetScaledSize().x / 2)) {
            score++;
        }
    }

    // update point
    if (score > lastScore) {
        m_PointSFX->Play();

        //ui update
        DisplayPointUI(score);
        lastScore = score;
    }

    // lower limit
    if (m_Bird->GetPosition().y <= -238.0f) {
        if (!m_IsCheating){
            m_CollideSFX->Play();
            m_BirdVelocityY = -10.0f;
            m_BirdAngle = -0.5f;
            m_Canvas_1->SetVisible(false);

            ClearPointUI();

            m_CurrentState = State::LEVEL_1_GAMEOVER;

            return;
        }
        m_Bird->SetPosition({m_Bird->GetPosition().x, -238.0f});
    }

    // upper limit
    if (m_Bird->GetPosition().y >= 337.0f) {
        if (!m_IsCheating){
            m_CollideSFX->Play();
            m_BirdVelocityY = -10.0f;
            m_BirdAngle = -0.5f;
            m_Canvas_1->SetVisible(false);

            ClearPointUI();

            m_CurrentState = State::LEVEL_1_GAMEOVER;

            return;
        }
        m_Bird->SetPosition({m_Bird->GetPosition().x, 337.0f});
    }

    //LOG_DEBUG("You score is {}", score);

    m_Root.Update();
}