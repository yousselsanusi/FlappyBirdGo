#include "App.hpp"
#include "Character.hpp"
#include "AnimatedCharacter.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"

void App::Level_3_Start() {
    InitializeUI();

    float m_PipeUp_Height[20];
    m_PipeUp_Height[0] = -300;

    for (int i = 0; i < 20; ++i) {
        if (i > 0) {
            int delta = (std::rand() % 101) - 50;
            m_PipeUp_Height[i] = m_PipeUp_Height[i - 1] + delta;

            // Optional clamp to avoid extreme pipe positions (if needed)
            if (m_PipeUp_Height[i] < -450) m_PipeUp_Height[i] = -450;
            if (m_PipeUp_Height[i] > -150) m_PipeUp_Height[i] = -150;
        }

        m_PipeUp.push_back(std::make_shared<Character>(RESOURCE_DIR"/Image/Pipe_Up.png"));
        m_PipeUp[i]->SetZIndex(25);
        m_PipeUp[i]->SetPosition({230.0f + 62.0f * i, m_PipeUp_Height[i]});
        m_Root.AddChild(m_PipeUp[i]);

        m_PipeDown.push_back(std::make_shared<Character>(RESOURCE_DIR"/Image/Pipe_Down.png"));
        m_PipeDown[i]->SetZIndex(25);
        m_PipeDown[i]->SetPosition({230.0f + 62.0f * i, m_PipeUp_Height[i] + 720.0f});
        m_Root.AddChild(m_PipeDown[i]);
    }

    m_Canvas_3 = std::make_shared<Character>(RESOURCE_DIR"/Level/Level_3.png"); // left = 435 / right = 835
    m_Canvas_3->SetPosition({0, 0}); //x - to left + to right // - down + up // -205.0f & 205.0f
    m_Canvas_3->SetZIndex(95);
    m_Root.AddChild(m_Canvas_3);

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_GameStartSFX->Play();
        m_CurrentState = State::END;
    }

    m_CurrentState = State::LEVEL_3_UPDATE;
}

void App::Level_3_Update() {
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
        m_YouWin_2->SetVisible(true);
        m_Canvas_3->SetVisible(false);

        if (Util::Input::IsKeyPressed(Util::Keycode::N)) {
            m_IsWinning = false;
            m_YouWin_2->SetVisible(false);
            m_CheatOffUI->SetVisible(false);
            m_CheatOnUI->SetVisible(false);

            ResetClear();

            m_IsCheating = false;
            m_Restarted = false;
            m_IsGameStarted = false;
            m_CurrentState = State::LEVEL_4_START;

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
            m_CurrentState = State::LEVEL_3_START;

            return;
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
            m_IsWinning = false;
            m_Canvas_3->SetVisible(false);
            m_YouWin_2->SetVisible(false);
            m_CheatOffUI->SetVisible(false);
            m_CheatOnUI->SetVisible(false);
            m_IsCheating = false;

            ResetClear();

            m_IsCheating = false;
            m_Restarted = false;
            m_IsGameStarted = false;
            m_CurrentState = State::LEVEL_2_START;

            return;
        }
        m_Root.Update();
        return;
    }

    //next level
    if (Util::Input::IsKeyPressed(Util::Keycode::N)) {
        m_Restarted = false;
        m_Canvas_3->SetVisible(false);
        m_CheatOffUI->SetVisible(false);
        m_CheatOnUI->SetVisible(false);
        m_IsCheating = false;

        ResetClear();

        m_IsCheating = false;
        m_IsGameStarted = false;
        m_CurrentState = State::LEVEL_4_START;

        return;
    }

    //previous level
    if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
        m_Restarted = false;
        m_Canvas_3->SetVisible(false);
        m_CheatOffUI->SetVisible(false);
        m_CheatOnUI->SetVisible(false);
        m_IsCheating = false;

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
                m_Canvas_3->SetVisible(false);

                ClearPointUI();

                m_CurrentState = State::LEVEL_3_GAMEOVER;

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
            m_Canvas_3->SetVisible(false);

            ClearPointUI();

            m_CurrentState = State::LEVEL_3_GAMEOVER;

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
            m_Canvas_3->SetVisible(false);

            ClearPointUI();

            m_CurrentState = State::LEVEL_3_GAMEOVER;

            return;
        }
        m_Bird->SetPosition({m_Bird->GetPosition().x, 337.0f});
    }

    //LOG_DEBUG("You score is {}", score);

    m_Root.Update();
}

void App::Level_3_GameOver(){
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
            m_CurrentState = State::LEVEL_3_START;

            return;
        }

        //next level
        if (Util::Input::IsKeyPressed(Util::Keycode::N)) {
            m_Restarted = false;
            m_Canvas_3->SetVisible(false);
            m_CheatOffUI->SetVisible(false);
            m_CheatOnUI->SetVisible(false);
            m_GameOver_2->SetVisible(false);
            m_IsGameStarted = false;
            m_IsCheating = false;

            ResetClear();

            m_IsCheating = false;
            m_CurrentState = State::LEVEL_4_START;

            return;
        }

        if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
            m_Restarted = false;
            m_Canvas_3->SetVisible(false);
            m_CheatOffUI->SetVisible(false);
            m_CheatOnUI->SetVisible(false);
            m_GameOver_2->SetVisible(false);
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