#include "Game_Engine.h"
#include <thread>
#include <chrono>

int main()
{
    Game_Engine gameEngine;
    while (gameEngine.running())
    {
        using namespace std::chrono_literals; // C++14
        //std::this_thread::sleep_for(0.05s); // C++14
        gameEngine.Update();

        gameEngine.Render();
    }

    return 0;
}