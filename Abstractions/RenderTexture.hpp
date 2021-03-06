#pragma once

#include "RenderTarget.hpp"

namespace sdl
{
    class RenderTexture
        : public RenderTarget, public Drawable
    {
    private:
        Rect<hsd::i32> _rect{};

    public:
        RenderTexture() = default;

        RenderTexture(const Rect<hsd::i32>& rect)
            : _rect{rect}
        {
            CreateRenderer(rect.width, rect.height);
        }

        void CreateRenderer(hsd::i32 width, hsd::i32 height)
        {
            SDL_FreeSurface(_surface);
            SDL_DestroyRenderer(_renderer);
            _surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

            if(_surface == nullptr)
            {
                fputs(SDL_GetError(), stderr);
            }
            else
            {
                _renderer = SDL_CreateSoftwareRenderer(_surface);
            }
        }

        Drawable& AsDrawable()
        {
            return *this;
        }

        RenderTexture& AsRender()
        {
            return *this;
        }

        void Clear(const Color& color)
        {
            SDL_SetRenderDrawColor(
                _renderer, color.red, color.green, 
                color.blue, color.alpha
            );

            SDL_RenderClear(_renderer);
        }

        virtual void Draw(Drawable& object) override
        {
            object.Draw(*this);
            SDL_RenderPresent(_renderer);
        }

        virtual void Draw(RenderTarget& Target) override
        {
            SDL_Texture* _tex = SDL_CreateTextureFromSurface(
                GetRenderer(Target), _surface
            );

            SDL_RenderCopy(
                GetRenderer(Target), _tex, 
                &_surface->clip_rect, 
                reinterpret_cast<SDL_Rect*>(&_rect)
            );

            SDL_DestroyTexture(_tex);
        }
    };
} // namespace sdl
