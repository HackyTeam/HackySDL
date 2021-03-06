#pragma once

#include "RenderTarget.hpp"
#include <SDL2/SDL_image.h>

namespace sdl
{
    class Sprite
        : public Drawable
    {
    private:
        IRect _rect{0, 0, 32, 32};
        Vector2F _velocity{};
        SDL_Surface* _surface = nullptr;
        bool _textured = false;

    public:
        Sprite() = default;

        Sprite(const Vector2I& Position, const char* FileName = "")
            : _rect{Position, {32, 32}}
        {
            _surface = IMG_Load(FileName);
            _textured = _surface != nullptr;

            if(_textured == false)
            {
                _surface = SDL_CreateRGBSurface(0, _rect.width, _rect.height, 32, 0, 0, 0, 0);

                if(_surface == nullptr)
                {
                    fputs(SDL_GetError(), stderr);
                }
                else
                {
                    SDL_FillRect(_surface, nullptr, 0xffffffff);
                }  
            }
            else
            {
                _rect.width = _surface->clip_rect.w;
                _rect.height = _surface->clip_rect.h;
            }
        }

        Sprite(const IRect& rect)
            : _rect{rect}, _textured{false}
        {
            _surface = SDL_CreateRGBSurface(0, rect.width, rect.height, 32, 0, 0, 0, 0);

            if(_surface == nullptr)
            {
                fputs(SDL_GetError(), stderr);
            }
            else
            {
                SDL_FillRect(_surface, nullptr, 0xffffffff);
            }
        }

        ~Sprite()
        {
            SDL_FreeSurface(_surface);
        }

        void SetColor(const Color& color)
        {
            if(_textured == false)
                SDL_FillRect(_surface, nullptr, color.PackColors());
        }

        void SetPosition(const Vector2F& Position)
        {
            _rect.left = static_cast<hsd::i32>(Position.x);
            _rect.top = static_cast<hsd::i32>(Position.y);
            _velocity = {0.f, 0.f};
        }

        Vector2F GetPosition()
        {
            return {
                static_cast<hsd::f32>(_rect.left),
                static_cast<hsd::f32>(_rect.top)
            };
        }

        void Move(const Vector2F& Velocity)
        {
            _velocity += Velocity;

            if(_velocity.x >= 1.f)
            {
                _rect.left += static_cast<hsd::i32>(_velocity.x);
                _velocity.x = 0.f;
            }
            if(_velocity.y >= 1.f)
            {
                _rect.top += static_cast<hsd::i32>(_velocity.y);
                _velocity.y = 0.f;
            }
        }

        void SetTextureRect(const IRect& rect)
        {
            _surface->clip_rect = static_cast<SDL_Rect>(rect);
            _rect.width = rect.width;
            _rect.height = rect.height;
        }

        bool LoadFromFile(const char* FileName)
        {
            SDL_FreeSurface(_surface);
            _surface = IMG_Load(FileName);
            _textured = _surface != nullptr;

            if(_textured == false)
            {
                _surface = SDL_CreateRGBSurface(0, _rect.width, _rect.height, 32, 0, 0, 0, 0);

                if(_surface == nullptr)
                {
                    fputs(SDL_GetError(), stderr);
                }
                else
                {
                    SDL_FillRect(_surface, nullptr, 0xffffffff);
                }                 
            }
            else
            {
                _rect.width = _surface->clip_rect.w;
                _rect.height = _surface->clip_rect.h;
            }

            return _textured;
        }

        bool LoadFromFile(const char* FileName, const IRect& rect)
        {
            bool _ret = LoadFromFile(FileName);
            
            if(_ret == true)
                SetTextureRect(rect);

            return _ret;
        }

        virtual void Draw(RenderTarget& Target) override
        {
            SDL_Rect _result = {
                .x = _rect.left - Target.GetViewport().left - _rect.width / 2,
                .y = _rect.top - Target.GetViewport().top - _rect.height / 2,
                .w = _rect.width, .h = _rect.height
            };

            SDL_Texture* _tex = SDL_CreateTextureFromSurface(
                GetRenderer(Target), _surface
            );
            
            SDL_RenderCopy(
                GetRenderer(Target), _tex,
                &_surface->clip_rect, &_result
            );

            SDL_DestroyTexture(_tex);
        }
    };
} // namespace sdl
