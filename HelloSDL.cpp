#include <SDL2/SDL.h>
#include "Abstractions/Exception.hpp"

int main()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        throw sdl::Exception();
    }

    return 0;
}