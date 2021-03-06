#include <SDL2/SDL.h>
#include "Abstractions/Window.hpp"
#include "Abstractions/RenderTexture.hpp"

int main()
{
    sdl::Window Win;
    Win.CreateWindow("TestWindow", {800, 600});
    sdl::RenderTexture Tex{{350, 200, 200, 150}};
    sdl::RenderTexture Tex2{{50, 50, 60, 45}};

    while(Win.IsOpen())
    {
        while(Win.PollEvent()) {}

        Win.Clear({103, 58, 183});
        Tex.Clear({0, 153, 183});
        Tex2.Clear({255, 255, 255});
        Tex.Draw(Tex2.AsDrawable());
        Win.Draw(Tex);
        Win.Display();
    }

    return 0;
}