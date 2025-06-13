#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
<<<<<<< HEAD
#include "Util/Renderer.hpp"
#include "Util/SFX.hpp"

class Character;
class PhaseResourceManager;
class AnimatedCharacter;
=======
>>>>>>> b608f54e3c839843df57c6c582d8eea8d69765aa

class App {
public:
    enum class State {
<<<<<<< HEAD
        LEVEL_1_START,
        LEVEL_1_UPDATE,
        LEVEL_1_GAMEOVER,
        LEVEL_2_START,
        LEVEL_2_UPDATE,
        LEVEL_2_GAMEOVER,
        LEVEL_3_START,
        LEVEL_3_UPDATE,
        LEVEL_3_GAMEOVER,
        LEVEL_4_START,
        LEVEL_4_UPDATE,
        LEVEL_4_GAMEOVER,
        LEVEL_5_START,
        LEVEL_5_UPDATE,
        LEVEL_5_GAMEOVER,
        LEVEL_6_START,
        LEVEL_6_UPDATE,
        LEVEL_6_GAMEOVER,
        LEVEL_7_START,
        LEVEL_7_UPDATE,
        LEVEL_7_GAMEOVER,
        LEVEL_8_START,
        LEVEL_8_UPDATE,
        LEVEL_8_GAMEOVER,
        LEVEL_9_START,
        LEVEL_9_UPDATE,
        LEVEL_9_GAMEOVER,
        LEVEL_10_START,
        LEVEL_10_UPDATE,
        LEVEL_10_GAMEOVER,
=======
        START,
        UPDATE,
>>>>>>> b608f54e3c839843df57c6c582d8eea8d69765aa
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

<<<<<<< HEAD
    //level 1 normal
    void Level_1_Start();

    void Level_1_Update();

    void Level_1_GameOver();

    //level 2 move pipe
    void Level_2_Start();

    void Level_2_Update();

    void Level_2_GameOver();

    //level 3 adjacent pipe
    void Level_3_Start();

    void Level_3_Update();

    void Level_3_GameOver();

    //level 4 blink pipe
    void Level_4_Start();

    void Level_4_Update();

    void Level_4_GameOver();

    //level 5 reverse gravity
    void Level_5_Start();

    void Level_5_Update();

    void Level_5_GameOver();

    //level 6 move pipe + blink pipe
    void Level_6_Start();

    void Level_6_Update();

    void Level_6_GameOver();

    //level 7 adjacent pipe + blink pipe
    void Level_7_Start();

    void Level_7_Update();

    void Level_7_GameOver();

    //level 8 move pipe + reverse gravity
    void Level_8_Start();

    void Level_8_Update();

    void Level_8_GameOver();

    //level 9 adjacent pipe + reverse gravity
    void Level_9_Start();

    void Level_9_Update();

    void Level_9_GameOver();

    //level 10 move pipe + reverse gravity + blink pipe
    void Level_10_Start();

    void Level_10_Update();

    void Level_10_GameOver();

    //other

    void End(); // NOLINT(readability-convert-member-functions-to-static)

    void InitializeUI();

    void ResetClear();

    void DisplayPointUI(int score);

    void ClearPointUI();

    void BirdMovement();

    void BirdMovementReverse();

    void BirdFallGameOver();

private:
    //initialize
    bool m_IsGameStarted = false;
    bool m_IsWinning = false;
    bool m_IsPaused = false;
    bool m_Restarted = false;
    bool m_IsCheating = false;
    State m_CurrentState = State::LEVEL_1_START;

    //bird setup
    float m_BirdVelocityY = 0.0f;
    float m_BirdAngle = 0.0f;

    //handle
    bool m_Jump = false;
    bool m_Enter = false;

    //bird
    std::shared_ptr<AnimatedCharacter> m_Bird;

    //pipe
    std::vector<std::shared_ptr<Character>> m_PipeUp;
    std::vector<std::shared_ptr<Character>> m_PipeDown;

    //point
    int m_Score = 0;
    std::shared_ptr<Character> m_Point_0;
    std::shared_ptr<Character> m_Point_1;
    std::shared_ptr<Character> m_Point_2;
    std::shared_ptr<Character> m_Point_3;
    std::shared_ptr<Character> m_Point_4;
    std::shared_ptr<Character> m_Point_5;
    std::shared_ptr<Character> m_Point_6;
    std::shared_ptr<Character> m_Point_7;
    std::shared_ptr<Character> m_Point_8;
    std::shared_ptr<Character> m_Point_9;
    std::shared_ptr<Character> m_Point_10;
    std::shared_ptr<Character> m_Point_11;
    std::shared_ptr<Character> m_Point_12;
    std::shared_ptr<Character> m_Point_13;
    std::shared_ptr<Character> m_Point_14;
    std::shared_ptr<Character> m_Point_15;
    std::shared_ptr<Character> m_Point_16;
    std::shared_ptr<Character> m_Point_17;
    std::shared_ptr<Character> m_Point_18;
    std::shared_ptr<Character> m_Point_19;
    std::shared_ptr<Character> m_Point_20;

    //base
    std::shared_ptr<Character> m_Background;
    std::shared_ptr<Character> m_Ground;

    //Level
    std::shared_ptr<Character> m_Canvas;
    std::shared_ptr<Character> m_Canvas_1;
    std::shared_ptr<Character> m_Canvas_2;
    std::shared_ptr<Character> m_Canvas_3;
    std::shared_ptr<Character> m_Canvas_4;
    std::shared_ptr<Character> m_Canvas_5;
    std::shared_ptr<Character> m_Canvas_6;
    std::shared_ptr<Character> m_Canvas_7;
    std::shared_ptr<Character> m_Canvas_8;
    std::shared_ptr<Character> m_Canvas_9;
    std::shared_ptr<Character> m_Canvas_10;
    std::shared_ptr<Character> m_CheatOnUI;
    std::shared_ptr<Character> m_CheatOffUI;
    std::shared_ptr<Character> m_YouWin;
    std::shared_ptr<Character> m_YouWin_2;
    std::shared_ptr<Character> m_YouWin_3;
    std::shared_ptr<Character> m_GameOver;
    std::shared_ptr<Character> m_GameOver_2;
    std::shared_ptr<Character> m_GameOver_3;

    //sound
    std::shared_ptr<Util::SFX> m_GameStartSFX;
    std::shared_ptr<Util::SFX> m_FlappingSFX;
    std::shared_ptr<Util::SFX> m_PointSFX;
    std::shared_ptr<Util::SFX> m_CollideSFX;
    std::shared_ptr<Util::SFX> m_GameWinningSFX;

    Util::Renderer m_Root;
=======
    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;
>>>>>>> b608f54e3c839843df57c6c582d8eea8d69765aa
};

#endif
