#include "App.hpp"
#include "Character.hpp"
#include "AnimatedCharacter.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "Util/SFX.hpp"
#include "Util/Time.hpp"

void App::InitializeUI() {
    m_GameStartSFX = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/GameStart.mp3");
    m_FlappingSFX = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/Flapping.mp3");
    m_PointSFX = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/Point.mp3");
    m_CollideSFX = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/Collide.mp3");
    m_GameWinningSFX = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/Win.mp3");

    std::vector<std::string> birdImages;
    birdImages.reserve(4);
    for (int i = 0; i < 4; ++i) {
        birdImages.emplace_back(RESOURCE_DIR"/Image/Bird_" + std::to_string(i + 1) + ".png");
    }

    m_Bird = std::make_shared<AnimatedCharacter>(birdImages);
    m_Bird->SetZIndex(30);
    m_Bird->SetRotation(0);
    m_Bird->SetPosition({-50.0, 0.0f}); //x - to left + to right // - down + up // before x = -400.0f
    m_Root.AddChild(m_Bird);

    float m_PipeUp_Height[20];
    for (int i = 0; i < 20; ++i) {
        m_PipeUp_Height[i] = -450 + (std::rand() % 301); // value = -450 + [0 to 300]

        // pipe (512) - y position (350 or - 350) = 162 is min height of show pipe
        // center pipeup to center pipedown 700 px
        m_PipeUp.push_back(std::make_shared<Character>(RESOURCE_DIR"/Image/Pipe_Up.png"));
        m_PipeUp[i]->SetZIndex(25);
        m_PipeUp[i]->SetPosition({230.0f + 250.0f * i, m_PipeUp_Height[i]}); // batas paling pendek -450 // batas paling panjang -150
        m_PipeUp[i]->SetVisible(true);
        m_Root.AddChild(m_PipeUp[i]);

        m_PipeDown.push_back(std::make_shared<Character>(RESOURCE_DIR"/Image/Pipe_Down.png"));
        m_PipeDown[i]->SetZIndex(25);
        m_PipeDown[i]->SetPosition({230.0f + 250.0f * i, m_PipeUp_Height[i] + 700.0f}); // batas paling panjang 250 // batas paling pendek 550
        m_PipeDown[i]->SetVisible(true);
        m_Root.AddChild(m_PipeDown[i]);
    }

    //point
    m_Point_0 = std::make_shared<Character>(RESOURCE_DIR"/Points/0.png");
    m_Point_0->SetZIndex(90);
    m_Point_0->SetVisible(true);
    m_Root.AddChild(m_Point_0);

    m_Point_1 = std::make_shared<Character>(RESOURCE_DIR"/Points/1.png");
    m_Point_1->SetZIndex(90);
    m_Point_1->SetVisible(false);
    m_Root.AddChild(m_Point_1);

    m_Point_2 = std::make_shared<Character>(RESOURCE_DIR"/Points/2.png");
    m_Point_2->SetZIndex(90);
    m_Point_2->SetVisible(false);
    m_Root.AddChild(m_Point_2);

    m_Point_3 = std::make_shared<Character>(RESOURCE_DIR"/Points/3.png");
    m_Point_3->SetZIndex(90);
    m_Point_3->SetVisible(false);
    m_Root.AddChild(m_Point_3);

    m_Point_4 = std::make_shared<Character>(RESOURCE_DIR"/Points/4.png");
    m_Point_4->SetZIndex(90);
    m_Point_4->SetVisible(false);
    m_Root.AddChild(m_Point_4);

    m_Point_5 = std::make_shared<Character>(RESOURCE_DIR"/Points/5.png");
    m_Point_5->SetZIndex(90);
    m_Point_5->SetVisible(false);
    m_Root.AddChild(m_Point_5);

    m_Point_6 = std::make_shared<Character>(RESOURCE_DIR"/Points/6.png");
    m_Point_6->SetZIndex(90);
    m_Point_6->SetVisible(false);
    m_Root.AddChild(m_Point_6);

    m_Point_7 = std::make_shared<Character>(RESOURCE_DIR"/Points/7.png");
    m_Point_7->SetZIndex(90);
    m_Point_7->SetVisible(false);
    m_Root.AddChild(m_Point_7);

    m_Point_8 = std::make_shared<Character>(RESOURCE_DIR"/Points/8.png");
    m_Point_8->SetZIndex(90);
    m_Point_8->SetVisible(false);
    m_Root.AddChild(m_Point_8);

    m_Point_9 = std::make_shared<Character>(RESOURCE_DIR"/Points/9.png");
    m_Point_9->SetZIndex(90);
    m_Point_9->SetVisible(false);
    m_Root.AddChild(m_Point_9);

    m_Point_10 = std::make_shared<Character>(RESOURCE_DIR"/Points/10.png");
    m_Point_10->SetZIndex(90);
    m_Point_10->SetVisible(false);
    m_Root.AddChild(m_Point_10);

    m_Point_11 = std::make_shared<Character>(RESOURCE_DIR"/Points/11.png");
    m_Point_11->SetZIndex(90);
    m_Point_11->SetVisible(false);
    m_Root.AddChild(m_Point_11);

    m_Point_12 = std::make_shared<Character>(RESOURCE_DIR"/Points/12.png");
    m_Point_12->SetZIndex(90);
    m_Point_12->SetVisible(false);
    m_Root.AddChild(m_Point_12);

    m_Point_13 = std::make_shared<Character>(RESOURCE_DIR"/Points/13.png");
    m_Point_13->SetZIndex(90);
    m_Point_13->SetVisible(false);
    m_Root.AddChild(m_Point_13);

    m_Point_14 = std::make_shared<Character>(RESOURCE_DIR"/Points/14.png");
    m_Point_14->SetZIndex(90);
    m_Point_14->SetVisible(false);
    m_Root.AddChild(m_Point_14);

    m_Point_15 = std::make_shared<Character>(RESOURCE_DIR"/Points/15.png");
    m_Point_15->SetZIndex(90);
    m_Point_15->SetVisible(false);
    m_Root.AddChild(m_Point_15);

    m_Point_16 = std::make_shared<Character>(RESOURCE_DIR"/Points/16.png");
    m_Point_16->SetZIndex(90);
    m_Point_16->SetVisible(false);
    m_Root.AddChild(m_Point_16);

    m_Point_17 = std::make_shared<Character>(RESOURCE_DIR"/Points/17.png");
    m_Point_17->SetZIndex(90);
    m_Point_17->SetVisible(false);
    m_Root.AddChild(m_Point_17);

    m_Point_18 = std::make_shared<Character>(RESOURCE_DIR"/Points/18.png");
    m_Point_18->SetZIndex(90);
    m_Point_18->SetVisible(false);
    m_Root.AddChild(m_Point_18);

    m_Point_19 = std::make_shared<Character>(RESOURCE_DIR"/Points/19.png");
    m_Point_19->SetZIndex(90);
    m_Point_19->SetVisible(false);
    m_Root.AddChild(m_Point_19);

    m_Point_20 = std::make_shared<Character>(RESOURCE_DIR"/Points/20.png");
    m_Point_20->SetZIndex(90);
    m_Point_20->SetVisible(false);
    m_Root.AddChild(m_Point_20);

    //background
    m_Background = std::make_shared<Character>(RESOURCE_DIR"/Base/Background.jpg");
    m_Background->SetZIndex(-10);
    m_Root.AddChild(m_Background);

    //ground
    m_Ground = std::make_shared<Character>(RESOURCE_DIR"/Base/Ground.jpg");
    m_Ground->SetPosition({0, -308.0f}); //x - to left + to right // - down + up
    m_Ground->SetZIndex(50);
    m_Root.AddChild(m_Ground);

    //Level
    m_Canvas = std::make_shared<Character>(RESOURCE_DIR"/Base/Canvas.png"); // left = 435 / right = 835
    m_Canvas->SetPosition({0, 0}); //x - to left + to right // - down + up // -205.0f & 205.0f
    m_Canvas->SetZIndex(80);
    m_Root.AddChild(m_Canvas);

    m_CheatOnUI = std::make_shared<Character>(RESOURCE_DIR"/Base/CheatOn.png"); // left = 435 / right = 835
    m_CheatOnUI->SetPosition({0, 0}); //x - to left + to right // - down + up // -205.0f & 205.0f
    m_CheatOnUI->SetZIndex(90);
    m_CheatOnUI->SetVisible(false);
    m_Root.AddChild(m_CheatOnUI);

    m_CheatOffUI = std::make_shared<Character>(RESOURCE_DIR"/Base/CheatOff.png"); // left = 435 / right = 835
    m_CheatOffUI->SetPosition({0, 0}); //x - to left + to right // - down + up // -205.0f & 205.0f
    m_CheatOffUI->SetZIndex(90);
    m_Root.AddChild(m_CheatOffUI);

    //display win
    m_YouWin = std::make_shared<Character>(RESOURCE_DIR"/Level/YouWin.png"); // left = 435 / right = 835
    m_YouWin->SetPosition({0, 0}); //x - to left + to right // - down + up // -205.0f & 205.0f
    m_YouWin->SetZIndex(95);
    m_YouWin->SetVisible(false);
    m_Root.AddChild(m_YouWin);

    m_YouWin_2 = std::make_shared<Character>(RESOURCE_DIR"/Level/YouWin_2.png"); // left = 435 / right = 835
    m_YouWin_2->SetPosition({0, 0}); //x - to left + to right // - down + up // -205.0f & 205.0f
    m_YouWin_2->SetZIndex(95);
    m_YouWin_2->SetVisible(false);
    m_Root.AddChild(m_YouWin_2);

    m_YouWin_3 = std::make_shared<Character>(RESOURCE_DIR"/Level/YouWin_3.png"); // left = 435 / right = 835
    m_YouWin_3->SetPosition({0, 0}); //x - to left + to right // - down + up // -205.0f & 205.0f
    m_YouWin_3->SetZIndex(95);
    m_YouWin_3->SetVisible(false);
    m_Root.AddChild(m_YouWin_3);

    //display gameover
    m_GameOver = std::make_shared<Character>(RESOURCE_DIR"/Level/GameOver.png"); // left = 435 / right = 835
    m_GameOver->SetPosition({0, 0}); //x - to left + to right // - down + up // -205.0f & 205.0f
    m_GameOver->SetZIndex(95);
    m_GameOver->SetVisible(false);
    m_Root.AddChild(m_GameOver);

    m_GameOver_2 = std::make_shared<Character>(RESOURCE_DIR"/Level/GameOver_2.png"); // left = 435 / right = 835
    m_GameOver_2->SetPosition({0, 0}); //x - to left + to right // - down + up // -205.0f & 205.0f
    m_GameOver_2->SetZIndex(95);
    m_GameOver_2->SetVisible(false);
    m_Root.AddChild(m_GameOver_2);

    m_GameOver_3 = std::make_shared<Character>(RESOURCE_DIR"/Level/GameOver_3.png"); // left = 435 / right = 835
    m_GameOver_3->SetPosition({0, 0}); //x - to left + to right // - down + up // -205.0f & 205.0f
    m_GameOver_3->SetZIndex(95);
    m_GameOver_3->SetVisible(false);
    m_Root.AddChild(m_GameOver_3);

    //sound
    m_GameStartSFX->Play();
}

void App::BirdMovement() {
    // const variables
    const float gravity = -9.8f;
    const float jumpStrength = 35.0f;
    const float downAngle = -0.5f;
    const float upAngle = 0.8f;
    Util::ms_t deltaTime = Util::Time::GetDeltaTimeMs() / 100.0f;
    glm::vec2 m_Bird_pos = m_Bird->GetPosition();

    // state variables
    static float velocityY = 0.0f;
    static float angle = 0.0f;
    static bool wasJumping = false;

    //jump algorithm
    bool isJumping = Util::Input::IsKeyPressed(Util::Keycode::SPACE);
    if (isJumping && !wasJumping) {
        m_FlappingSFX->Play();
        velocityY = jumpStrength;
        angle = upAngle; // tilt up when flapping
    }
    wasJumping = isJumping;

    // gravity + position update
    velocityY += gravity * deltaTime;
    m_Bird_pos.y += velocityY * deltaTime;
    m_Bird->SetPosition(m_Bird_pos);

    // rotation update
    float targetAngle = (velocityY < 0.0f) ? downAngle : 0.0f; // Tilt down when falling, neutral otherwise
    float smoothing = 0.5f; // Higher = faster response, try 5–10 for snappy or 2–3 for floaty
    angle = angle + (targetAngle - angle) * smoothing * deltaTime;

    m_Bird->SetRotation(angle);

    m_BirdVelocityY = velocityY;
    m_BirdAngle = angle;
}

void App::BirdMovementReverse() {
    // const variables
    const float gravity = +9.8f;
    const float jumpStrength = -30.0f;
    const float downAngle = -0.5f;
    const float upAngle = 0.8f;
    Util::ms_t deltaTime = Util::Time::GetDeltaTimeMs() / 100.0f;
    glm::vec2 m_Bird_pos = m_Bird->GetPosition();

    // state variables
    static float velocityY = 0.0f;
    static float angle = 0.0f;
    static bool wasJumping = false;

    //jump algorithm
    bool isJumping = Util::Input::IsKeyPressed(Util::Keycode::SPACE);
    if (isJumping && !wasJumping) {
        m_FlappingSFX->Play();
        velocityY = jumpStrength;
        angle = upAngle; // tilt up when flapping
    }
    wasJumping = isJumping;

    // gravity + position update
    velocityY += gravity * deltaTime;
    m_Bird_pos.y += velocityY * deltaTime;
    m_Bird->SetPosition(m_Bird_pos);

    // rotation update
    float targetAngle = (velocityY < 0.0f) ? downAngle : 0.0f; // Tilt down when falling, neutral otherwise
    float smoothing = 0.5f; // Higher = faster response, try 5–10 for snappy or 2–3 for floaty
    angle = angle + (targetAngle - angle) * smoothing * deltaTime;

    m_Bird->SetRotation(angle);

    m_BirdVelocityY = velocityY;
    m_BirdAngle = angle;
}

void App::BirdFallGameOver() {
    // const variables
    const float gravity = -9.8f;
    const float downAngle = -0.5f;
    Util::ms_t deltaTime = Util::Time::GetDeltaTimeMs() / 100.0f;
    glm::vec2 m_Bird_pos = m_Bird->GetPosition();

    float velocityY = std::min(m_BirdVelocityY, 0.0f);
    float angle = m_BirdAngle;

    // gravity + position update
    velocityY += gravity * deltaTime;
    m_Bird_pos.y += velocityY * deltaTime;
    m_Bird->SetPosition(m_Bird_pos);

    //rotation update
    angle = downAngle;
    m_Bird->SetRotation(angle);

    m_BirdVelocityY = velocityY;
}

void App::DisplayPointUI(int score) {
    if (score==1) {
        m_Point_0->SetVisible(false);
        m_Point_1->SetVisible(true);
        //m_IsWinning = true;
    } else if (score==2) {
        m_Point_1->SetVisible(false);
        m_Point_2->SetVisible(true);
    } else if (score==3) {
        m_Point_2->SetVisible(false);
        m_Point_3->SetVisible(true);
    } else if (score==4) {
        m_Point_3->SetVisible(false);
        m_Point_4->SetVisible(true);
    } else if (score==5) {
        m_Point_4->SetVisible(false);
        m_Point_5->SetVisible(true);
    } else if (score==6) {
        m_Point_5->SetVisible(false);
        m_Point_6->SetVisible(true);
    } else if (score==7) {
        m_Point_6->SetVisible(false);
        m_Point_7->SetVisible(true);
    } else if (score==8) {
        m_Point_7->SetVisible(false);
        m_Point_8->SetVisible(true);
    } else if (score==9) {
        m_Point_8->SetVisible(false);
        m_Point_9->SetVisible(true);
    } else if (score==10) {
        m_Point_9->SetVisible(false);
        m_Point_10->SetVisible(true);
    } else if (score==11) {
        m_Point_10->SetVisible(false);
        m_Point_11->SetVisible(true);
    } else if (score==12) {
        m_Point_11->SetVisible(false);
        m_Point_12->SetVisible(true);
    } else if (score==13) {
        m_Point_12->SetVisible(false);
        m_Point_13->SetVisible(true);
    } else if (score==14) {
        m_Point_13->SetVisible(false);
        m_Point_14->SetVisible(true);
    } else if (score==15) {
        m_Point_14->SetVisible(false);
        m_Point_15->SetVisible(true);
    } else if (score==16) {
        m_Point_15->SetVisible(false);
        m_Point_16->SetVisible(true);
    } else if (score==17) {
        m_Point_16->SetVisible(false);
        m_Point_17->SetVisible(true);
    } else if (score==18) {
        m_Point_17->SetVisible(false);
        m_Point_18->SetVisible(true);
    } else if (score==19) {
        m_Point_18->SetVisible(false);
        m_Point_19->SetVisible(true);
    } else if (score==20) {
        m_GameWinningSFX->Play();
        m_Point_19->SetVisible(false);
        m_Point_20->SetVisible(true);
        m_IsWinning = true;
    }
}

void App::ResetClear() {
    m_Root.RemoveChild(m_Bird);
    m_Bird->SetVisible(false);
    m_Bird.reset();

    m_Root.RemoveChild(m_Point_0);
    m_Point_0->SetVisible(false);
    m_Point_0.reset();

    m_Root.RemoveChild(m_Point_1);
    m_Point_1->SetVisible(false);
    m_Point_1.reset();

    m_Root.RemoveChild(m_Point_2);
    m_Point_2->SetVisible(false);
    m_Point_2.reset();

    m_Root.RemoveChild(m_Point_3);
    m_Point_3->SetVisible(false);
    m_Point_3.reset();

    m_Root.RemoveChild(m_Point_4);
    m_Point_4->SetVisible(false);
    m_Point_4.reset();

    m_Root.RemoveChild(m_Point_5);
    m_Point_5->SetVisible(false);
    m_Point_5.reset();

    m_Root.RemoveChild(m_Point_6);
    m_Point_6->SetVisible(false);
    m_Point_6.reset();

    m_Root.RemoveChild(m_Point_7);
    m_Point_7->SetVisible(false);
    m_Point_7.reset();

    m_Root.RemoveChild(m_Point_8);
    m_Point_8->SetVisible(false);
    m_Point_8.reset();

    m_Root.RemoveChild(m_Point_9);
    m_Point_9->SetVisible(false);
    m_Point_9.reset();

    m_Root.RemoveChild(m_Point_10);
    m_Point_10->SetVisible(false);
    m_Point_10.reset();

    m_Root.RemoveChild(m_Point_11);
    m_Point_11->SetVisible(false);
    m_Point_11.reset();

    m_Root.RemoveChild(m_Point_12);
    m_Point_12->SetVisible(false);
    m_Point_12.reset();

    m_Root.RemoveChild(m_Point_13);
    m_Point_13->SetVisible(false);
    m_Point_13.reset();

    m_Root.RemoveChild(m_Point_14);
    m_Point_14->SetVisible(false);
    m_Point_14.reset();

    m_Root.RemoveChild(m_Point_15);
    m_Point_15->SetVisible(false);
    m_Point_15.reset();

    m_Root.RemoveChild(m_Point_16);
    m_Point_16->SetVisible(false);
    m_Point_16.reset();

    m_Root.RemoveChild(m_Point_17);
    m_Point_17->SetVisible(false);
    m_Point_17.reset();

    m_Root.RemoveChild(m_Point_18);
    m_Point_18->SetVisible(false);
    m_Point_18.reset();

    m_Root.RemoveChild(m_Point_19);
    m_Point_19->SetVisible(false);
    m_Point_19.reset();

    m_Root.RemoveChild(m_Point_20);
    m_Point_20->SetVisible(false);
    m_Point_20.reset();

    m_Root.RemoveChild(m_CheatOffUI);
    m_CheatOffUI->SetVisible(false);
    m_CheatOffUI.reset();

    m_Root.RemoveChild(m_CheatOnUI);
    m_CheatOnUI->SetVisible(false);
    m_CheatOnUI.reset();

    m_BirdVelocityY = 0.0f;
    m_BirdAngle = 0.0f;
}

void App::ClearPointUI() {
    m_Point_0->SetVisible(false);
    m_Point_1->SetVisible(false);
    m_Point_2->SetVisible(false);
    m_Point_3->SetVisible(false);
    m_Point_4->SetVisible(false);
    m_Point_5->SetVisible(false);
    m_Point_6->SetVisible(false);
    m_Point_7->SetVisible(false);
    m_Point_8->SetVisible(false);
    m_Point_9->SetVisible(false);
    m_Point_10->SetVisible(false);
    m_Point_11->SetVisible(false);
    m_Point_12->SetVisible(false);
    m_Point_13->SetVisible(false);
    m_Point_14->SetVisible(false);
    m_Point_15->SetVisible(false);
    m_Point_16->SetVisible(false);
    m_Point_17->SetVisible(false);
    m_Point_18->SetVisible(false);
    m_Point_19->SetVisible(false);
    m_Point_20->SetVisible(false);
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}