#include <SDL2/SDL.h>
#include "Abstractions/Window.hpp"
#include "Abstractions/Sprite.hpp"

void run_app()
{
    sdl::Window Win;
    Win.CreateWindow("TestWindow", {1200, 1000});
    sdl::Sprite Sprite1{{-300, -300}};
    sdl::Sprite Sprite2{{0, 0}, "World.png"};
    Win.SetGlobalScale(3.f);
    //Win.SetViewport({200, 150, 400, 300});

    while(Win.IsOpen())
    {
        while(Win.PollEvent())
        {
            if(Win.GetEventType() == SDL_EventType::SDL_MOUSEBUTTONDOWN)
            {
                Sprite1.LoadFromFile("BasicEnemy.png", {24, 32, 24, 32});
            }
            else if(Win.GetEventType() == SDL_EventType::SDL_KEYDOWN)
            {
                Sprite1.LoadFromFile("Player.png", {0, 32, 24, 32});
            }
        }

        Sprite1.Move({0.1f, 0.1f});
        Win.SetViewportCenter({
            static_cast<hsd::i32>(Sprite1.GetPosition().x), 
            static_cast<hsd::i32>(Sprite1.GetPosition().y)
        });
        Win.Clear({255, 255, 255});
        Win.Draw(Sprite2);
        Win.Draw(Sprite1);
        Win.Display();
    }
}

int main()
{
    run_app();
    return 0;
}