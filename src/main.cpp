#include "App.hpp"
#include "Util/Keycode.hpp"
#include "Util/Input.hpp"


#include "Core/Context.hpp"

int main(int, char**) {
    auto context = Core::Context::GetInstance();
    App app;

    while (!context->GetExit()) {
        switch (app.GetCurrentState()) {
            //level 1
            case App::State::LEVEL_1_START:
                app.Level_1_Start();
                break;

            case App::State::LEVEL_1_UPDATE:
                app.Level_1_Update();
                break;

            case App::State::LEVEL_1_GAMEOVER:
                app.Level_1_GameOver();
                break;

            //level 2
            case App::State::LEVEL_2_START:
                app.Level_2_Start();
                break;

            case App::State::LEVEL_2_UPDATE:
                app.Level_2_Update();
                break;

            case App::State::LEVEL_2_GAMEOVER:
                app.Level_2_GameOver();
                break;

            //level 3
            case App::State::LEVEL_3_START:
                app.Level_3_Start();
                break;

            case App::State::LEVEL_3_UPDATE:
                app.Level_3_Update();
                break;

            case App::State::LEVEL_3_GAMEOVER:
                app.Level_3_GameOver();
                break;

            //level 4
            case App::State::LEVEL_4_START:
                app.Level_4_Start();
                break;

            case App::State::LEVEL_4_UPDATE:
                app.Level_4_Update();
                break;

            case App::State::LEVEL_4_GAMEOVER:
                app.Level_4_GameOver();
                break;

            //level 5
            case App::State::LEVEL_5_START:
                app.Level_5_Start();
                break;

            case App::State::LEVEL_5_UPDATE:
                app.Level_5_Update();
                break;

            case App::State::LEVEL_5_GAMEOVER:
                app.Level_5_GameOver();
                break;

            //level 6
            case App::State::LEVEL_6_START:
                app.Level_6_Start();
                break;

            case App::State::LEVEL_6_UPDATE:
                app.Level_6_Update();
                break;

            case App::State::LEVEL_6_GAMEOVER:
                app.Level_6_GameOver();
                break;

            //level 7
            case App::State::LEVEL_7_START:
                app.Level_7_Start();
                break;

            case App::State::LEVEL_7_UPDATE:
                app.Level_7_Update();
                break;

            case App::State::LEVEL_7_GAMEOVER:
                app.Level_7_GameOver();
                break;

            //level 8
            case App::State::LEVEL_8_START:
                app.Level_8_Start();
                break;

            case App::State::LEVEL_8_UPDATE:
                app.Level_8_Update();
                break;

            case App::State::LEVEL_8_GAMEOVER:
                app.Level_8_GameOver();
                break;

            //level 9
            case App::State::LEVEL_9_START:
                app.Level_9_Start();
                break;

            case App::State::LEVEL_9_UPDATE:
                app.Level_9_Update();
                break;

            case App::State::LEVEL_9_GAMEOVER:
                app.Level_9_GameOver();
                break;

            //level 10
            case App::State::LEVEL_10_START:
                app.Level_10_Start();
                break;

            case App::State::LEVEL_10_UPDATE:
                app.Level_10_Update();
                break;

            case App::State::LEVEL_10_GAMEOVER:
                app.Level_10_GameOver();
                break;

            //end
            case App::State::END:
                app.End();
                context->SetExit(true);
                break;
        }
        context->Update();
    }
    return 0;
}
