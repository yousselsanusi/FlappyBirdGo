#include "App.hpp"
#include "Character.hpp"
#include "AnimatedCharacter.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"

void App::Level_8_Start() {
    InitializeUI();

    for (int i = 0; i < 20; ++i) {
        m_PipeUp[i]->SetVisible(true);
        m_Root.AddChild(m_PipeUp[i]);

        m_PipeUp[i]->SetVisible(true);
        m_Root.AddChild(m_PipeUp[i]);
    }

    m_Canvas_8 = std::make_shared<Character>(RESOURCE_DIR"/Level/Level_8.png"); // left = 435 / right = 835
    m_Canvas_8->SetPosition({0, 0}); //x - to left + to right // - down + up // -205.0f & 205.0f
    m_Canvas_8->SetZIndex(95);
    m_Root.AddChild(m_Canvas_8);

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_GameStartSFX->Play();
        m_CurrentState = State::END;
    }

    m_IsCheating = false;

    m_CurrentState = State::LEVEL_8_UPDATE;
}

void App::Level_8_Update() {
    //exit
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_GameStartSFX->Play();
        m_CurrentState = State::END;
    }

    static int lastScore = 0;
    static float pipeYOffset = 0.0f;
    static float pipeYSpeed = 0.02f;
    static bool goingUp = true;
    if (m_Restarted) {
        lastScore = 0;
        pipeYOffset = 0.0f;
        pipeYSpeed = 0.02f;
        goingUp = true;
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
        m_YouWin_2->SetVisible(true);
        m_Canvas_8->SetVisible(false);

        if (Util::Input::IsKeyPressed(Util::Keycode::N)) {
            m_IsWinning = false;
            m_YouWin_2->SetVisible(false);
            m_CheatOffUI->SetVisible(false);
            m_CheatOnUI->SetVisible(false);
            m_IsCheating = false;

            ResetClear();

            m_IsCheating = false;
            m_Restarted = false;
            m_IsGameStarted = false;
            m_CurrentState = State::LEVEL_9_START;

            return;
        }

        if (Util::Input::IsKeyPressed(Util::Keycode::R)) {
            m_YouWin_2->SetVisible(false);
            m_CheatOffUI->SetVisible(false);
            m_CheatOnUI->SetVisible(false);

            m_IsWinning = false;
            m_IsCheating =  false;
            m_Restarted = true;
            m_IsGameStarted = false;

            ResetClear();

            m_IsCheating = false;
            m_CurrentState = State::LEVEL_8_START;

            return;
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
            m_IsWinning = false;
            m_YouWin_2->SetVisible(false);
            m_CheatOffUI->SetVisible(false);
            m_CheatOnUI->SetVisible(false);
            m_Canvas_8->SetVisible(false);
            m_IsCheating = false;

            ResetClear();

            m_IsCheating = false;
            m_Canvas_8->SetVisible(false);
            m_Restarted = false;
            m_IsGameStarted = false;
            m_CurrentState = State::LEVEL_7_START;

            return;
        }
        m_Root.Update();
        return;
    }

    //next level
    if (Util::Input::IsKeyPressed(Util::Keycode::N)) {
        m_Restarted = false;
        m_Canvas_8->SetVisible(false);
        m_CheatOffUI->SetVisible(false);
        m_CheatOnUI->SetVisible(false);
        m_IsCheating = false;

        ResetClear();

        m_IsCheating = false;
        m_IsGameStarted = false;
        m_CurrentState = State::LEVEL_9_START;

        return;
    }

    //previous level
    if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
        m_Restarted = false;
        m_Canvas_8->SetVisible(false);
        m_CheatOffUI->SetVisible(false);
        m_CheatOnUI->SetVisible(false);
        m_IsCheating = false;

        ResetClear();

        m_IsCheating = false;
        m_Canvas_8->SetVisible(false);
        m_IsGameStarted = false;
        m_CurrentState = State::LEVEL_7_START;

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

    BirdMovementReverse();

    //pipe movement
    float maxOffset = 1.0f;

    // Update offset each frame
    if (goingUp)
        pipeYOffset += pipeYSpeed;
    else
        pipeYOffset -= pipeYSpeed;

    if (pipeYOffset > maxOffset)
        goingUp = false;
    else if (pipeYOffset < -maxOffset)
        goingUp = true;

    int score = 0;
    for (int i = 0; i < 20; ++i) {
        float currentX = m_PipeUp[i]->GetPosition().x - 1.8f;
        float originalYUp = m_PipeUp[i]->GetPosition().y;     // Assume you store initial Y
        float originalYDown = m_PipeDown[i]->GetPosition().y; // Same for down pipe

        m_PipeUp[i]->SetPosition({currentX, originalYUp + pipeYOffset});
        m_PipeDown[i]->SetPosition({currentX, originalYDown + pipeYOffset});

        if (!m_IsCheating) {
            if (m_Bird->IfCollides(m_PipeUp[i]) || m_Bird->IfCollides(m_PipeDown[i])) {
                m_CollideSFX->Play();
                m_BirdVelocityY = -10.0f;
                m_BirdAngle = -0.5f;
                m_Canvas_8->SetVisible(false);

                ClearPointUI();

                m_CurrentState = State::LEVEL_8_GAMEOVER;

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
            m_Canvas_8->SetVisible(false);

            ClearPointUI();

            m_CurrentState = State::LEVEL_8_GAMEOVER;

            return;
        } else {
            m_Bird->SetPosition({m_Bird->GetPosition().x, -238.0f});
        }
    }

    // upper limit
    if (m_Bird->GetPosition().y >= 337.0f) {
        if (!m_IsCheating){
            m_CollideSFX->Play();
            m_BirdVelocityY = -10.0f;
            m_BirdAngle = -0.5f;
            m_Canvas_8->SetVisible(false);

            ClearPointUI();

            m_CurrentState = State::LEVEL_8_GAMEOVER;

            return;
        } else {
            m_Bird->SetPosition({m_Bird->GetPosition().x, 337.0f});
        }
    }

    //LOG_DEBUG("You score is {}", score);

    m_Root.Update();
}

void App::Level_8_GameOver(){
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
        m_GameOver_2->SetVisible(true);

        if (Util::Input::IsKeyPressed(Util::Keycode::R)) {
            m_Restarted = true;
            m_IsGameStarted = false;
            m_GameOver_2->SetVisible(false);
            m_IsCheating = false;

            ResetClear();

            m_IsCheating = false;
            m_CurrentState = State::LEVEL_8_START;

            return;
        }

        //next level
        if (Util::Input::IsKeyPressed(Util::Keycode::N)) {
            m_Restarted = false;
            m_Canvas_8->SetVisible(false);
            m_CheatOffUI->SetVisible(false);
            m_CheatOnUI->SetVisible(false);
            m_GameOver_2->SetVisible(false);
            m_IsGameStarted = false;
            m_IsCheating = false;

            ResetClear();

            m_IsCheating = false;
            m_CurrentState = State::LEVEL_9_START;

            return;
        }

        if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
            m_Restarted = false;
            m_Canvas_8->SetVisible(false);
            m_CheatOffUI->SetVisible(false);
            m_CheatOnUI->SetVisible(false);
            m_GameOver_2->SetVisible(false);
            m_IsGameStarted = false;
            m_IsCheating = false;

            ResetClear();

            m_IsCheating = false;
            m_Canvas_8->SetVisible(false);
            m_CurrentState = State::LEVEL_7_START;

            return;
        }
    }
    m_Root.Update();
}