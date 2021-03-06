#pragma once

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include "Base.hpp"

namespace sdl
{
    struct Drawable;

    class RenderTarget
    {
    protected:
        SDL_Surface* _surface = nullptr;
        SDL_Renderer* _renderer = nullptr;
        IRect _new_viewport{};
        hsd::f32 _scale = 1.f;
        friend class Drawable;

    public:
        virtual void Draw(Drawable&) = 0;

        const IRect& GetViewport() const
        {
            return _new_viewport;
        }

        const hsd::f32 GetGlobalScale() const
        {
            return _scale;
        }

        virtual ~RenderTarget()
        {
            SDL_FreeSurface(_surface);
            SDL_DestroyRenderer(_renderer);
        }
    };

    class Drawable
    {
    protected:
        friend class RenderTarget;

        static SDL_Renderer* GetRenderer(const RenderTarget& Target)
        {
            return Target._renderer;
        }

    public:
        virtual void Draw(RenderTarget&) = 0;
    };
} // namespace sdl
