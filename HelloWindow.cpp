#include <SDL2/SDL.h>
#include "Abstractions/Window.hpp"

int main()
{
    sdl::Window Win;
    Win.CreateWindow("TestWindow", {800, 600});

    while(Win.IsOpen())
    {
        while(Win.PollEvent()) {}

        Win.Clear({103, 58, 183, 255});
        Win.Display();
    }

    return 0;
}