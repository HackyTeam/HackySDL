#pragma once

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>

#include "HackySTL/cpp/Types.hpp"
#include "RenderTarget.hpp"

namespace sdl
{
    struct VideoMode
    {
        hsd::i32 width;
        hsd::i32 height;

        enum class Displays
        {
            Primary,
            Secondary,
            Tertiary,
            Quaternary
        };

        static VideoMode GetDesktopMode(Displays Index = Displays::Primary)
        {
            SDL_Rect _rect;
            SDL_GetDisplayBounds(static_cast<hsd::i32>(Index), &_rect);
            return {_rect.w, _rect.h};
        }
    };

    enum class WindowFlags
    {
        Fullscreen          = SDL_WINDOW_FULLSCREEN,    
        OpenGL              = SDL_WINDOW_OPENGL,
        Shown               = SDL_WINDOW_SHOWN,
        Hidden              = SDL_WINDOW_HIDDEN,
        Borderless          = SDL_WINDOW_BORDERLESS,    
        Resizable           = SDL_WINDOW_RESIZABLE,    
        Minimized           = SDL_WINDOW_MINIMIZED,    
        Maximized           = SDL_WINDOW_MAXIMIZED,    
        InputGrabbed        = SDL_WINDOW_INPUT_GRABBED,        
        InputFocus          = SDL_WINDOW_INPUT_FOCUS,    
        MouseFocus          = SDL_WINDOW_MOUSE_FOCUS,    
        FullscreenDesktop   = SDL_WINDOW_FULLSCREEN_DESKTOP,            
        Foreign             = SDL_WINDOW_FOREIGN,
        HighDPIMode         = SDL_WINDOW_ALLOW_HIGHDPI,        
        MouseCapture        = SDL_WINDOW_MOUSE_CAPTURE,        
        AlwaysOnTop         = SDL_WINDOW_ALWAYS_ON_TOP,        
        SkipTaskbar         = SDL_WINDOW_SKIP_TASKBAR,        
        Utility             = SDL_WINDOW_UTILITY,
        Tooltip             = SDL_WINDOW_TOOLTIP,
        PopupMenu           = SDL_WINDOW_POPUP_MENU,    
        Vulkan              = SDL_WINDOW_VULKAN               
    };

    class Window
        : public RenderTarget
    {
    private:
        SDL_Window* _window = nullptr;
        IRect _default_viewport{};
        SDL_Event _event{};

    public:
        Window() = default;

        Window(const char* Title, VideoMode Mode, 
            WindowFlags Flags = WindowFlags::Shown)
        {
            CreateWindow(Title, Mode, Flags);
        }

        ~Window()
        {
            SDL_DestroyWindow(_window);
            _renderer = nullptr;
        }

        void CreateWindow(const char* Title, VideoMode Mode, 
            WindowFlags Flags = WindowFlags::Shown)
        {
            SDL_DestroyWindow(_window);
            SDL_DestroyRenderer(_renderer);
            
            _window = SDL_CreateWindow(
                Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                Mode.width, Mode.height, static_cast<hsd::u32>(Flags)
            );

            if(_window == nullptr)
            { 
                fputs(SDL_GetError(), stderr);
            }
            else
            {
                _renderer = SDL_CreateRenderer(_window, -1, 0);

                if(_renderer == nullptr)
                {
                    fputs(SDL_GetError(), stderr);
                }
                else
                {
                    SDL_RenderGetViewport(_renderer, reinterpret_cast<SDL_Rect*>(&_default_viewport));
                    SDL_RenderGetViewport(_renderer, reinterpret_cast<SDL_Rect*>(&_new_viewport));
                }
            }
        }

        bool IsOpen()
        {
            return GetEventType() != SDL_QUIT;
        }

        bool PollEvent()
        {
            return SDL_PollEvent(&_event);
        }

        hsd::u32 GetEventType()
        {
            return _event.type;
        }

        void SetViewportCenter(const Vector2I& Pos)
        {
            _new_viewport.left = Pos.x - _new_viewport.width / (_scale * 2.f);
            _new_viewport.top = Pos.y - _new_viewport.height / (_scale * 2.f);
        }

        void SetGlobalScale(hsd::f32 Scale)
        {
            _scale = Scale;
            SDL_RenderSetScale(_renderer, Scale, Scale);
        }

        IRect GetDefaultViewport()
        {
            return _default_viewport;
        }

        virtual void Draw(Drawable& Object) override
        {
            Object.Draw(*this);
        }

        void Clear(const Color& ScreenColor)
        {
            SDL_SetRenderDrawColor(
                _renderer, ScreenColor.red, 
                ScreenColor.green, 
                ScreenColor.blue, 
                ScreenColor.alpha
            );
            SDL_RenderClear(_renderer);
        }

        void Display()
        {
            SDL_RenderPresent(_renderer);
        }
    }; 
} // namespace sdl
