#pragma once

#include "HackySTL/cpp/Math.hpp"

namespace sdl
{
    struct Color
    {
        hsd::u8 red   = 0;    
        hsd::u8 green = 0;
        hsd::u8 blue  = 0;   
        hsd::u8 alpha = 0;

        constexpr hsd::u32 PackColors() const
        {
            return static_cast<hsd::u32>(red) + (static_cast<hsd::u32>(green) << 8) + 
                (static_cast<hsd::u32>(blue) << 16) + (static_cast<hsd::u32>(alpha) << 24);
        }
    };

    template <hsd::math::IsNumber T>
    struct Vector2
    {
        T x = 0;
        T y = 0;

        Vector2 operator+(const Vector2& rhs) const
        {
            return {x + rhs.x, y + rhs.y};
        }

        Vector2& operator+=(const Vector2& rhs)
        {
            x += rhs.x; 
            y += rhs.y;

            return *this;
        }

        Vector2 operator-(const Vector2& rhs) const
        {
            return {x - rhs.x, y - rhs.y};
        }

        Vector2& operator-=(const Vector2& rhs)
        {
            x -= rhs.x; 
            y -= rhs.y;

            return *this;
        }

        friend Vector2 operator*(const T& lhs, const Vector2& rhs)
        {
            return {lhs * rhs.x, lhs * rhs.y};
        }

        friend Vector2 operator*(const Vector2& lhs, const T& rhs)
        {
            return {lhs.x * rhs, lhs.y * rhs};
        }

        Vector2& operator*=(const T& rhs)
        {
            x *= rhs; 
            y *= rhs;

            return *this;
        }

        Vector2 operator/(const T& rhs) const
        {
            return {x / rhs, y / rhs};
        }

        Vector2& operator/=(const T& rhs)
        {
            x /= rhs; 
            y /= rhs;

            return *this;
        }

        bool operator==(const Vector2& rhs) const
        {
            return x == rhs.x && y == rhs.y;
        }

        bool operator!=(const Vector2& rhs) const
        {
            return x != rhs.x || y != rhs.y;
        }
    };

    template <hsd::math::IsNumber T>
    struct Rect
    {
        T left   = 0;
        T top    = 0;
        T width  = 0;
        T height = 0;

        Rect() = default;
        Rect(const Rect&) = default;
        Rect& operator=(const Rect&) = default;

        Rect(T Left, T Top, T Width, T Height)
            : left{Left}, top{Top}, width{Width}, height{Height}
        {}

        Rect(const SDL_Rect& other)
        {
            left = static_cast<T>(other.x);
            top = static_cast<T>(other.y);
            width = static_cast<T>(other.w);
            height = static_cast<T>(other.h);
        }

        Rect(const SDL_FRect& other)
        {
            left = static_cast<T>(other.x);
            top = static_cast<T>(other.y);
            width = static_cast<T>(other.w);
            height = static_cast<T>(other.h);
        }

        Rect(const Vector2<T>& First, const Vector2<T>& Second)
            : left{First.x}, top{First.y}, width{Second.x}, height{Second.y}
        {}

        Rect& operator=(const SDL_Rect& rhs)
        {
            left = static_cast<T>(rhs.x);
            top = static_cast<T>(rhs.y);
            width = static_cast<T>(rhs.w);
            height = static_cast<T>(rhs.h);

            return *this;
        }

        Rect& operator=(const SDL_FRect& rhs)
        {
            left = static_cast<T>(rhs.x);
            top = static_cast<T>(rhs.y);
            width = static_cast<T>(rhs.w);
            height = static_cast<T>(rhs.h);

            return *this;
        }

        operator SDL_Rect() const
        {
            return {
                static_cast<hsd::i32>(left), 
                static_cast<hsd::i32>(top), 
                static_cast<hsd::i32>(width), 
                static_cast<hsd::i32>(height)
            };
        }

        operator SDL_FRect() const
        {
            return {
                static_cast<hsd::f32>(left), 
                static_cast<hsd::f32>(top), 
                static_cast<hsd::f32>(width), 
                static_cast<hsd::f32>(height)
            };
        }

        bool operator==(const Rect& rhs) const
        {
            return left == rhs.left && top == rhs.top &&
                width == rhs.width && height == rhs.height;
        }

        bool operator!=(const Rect& rhs) const
        {
            return left != rhs.left || top != rhs.top ||
                width != rhs.width || height != rhs.height;
        }

        Rect operator-(const Rect& rhs) const
        {
            return {
                left - rhs.left,
                top - rhs.top,
                width - rhs.width,
                height - rhs.height
            };
        }

        Rect ScaleRect(hsd::f32 Scale)
        {
            Rect _ret;

            _ret.left = static_cast<T>(static_cast<hsd::f32>(left) * Scale);
            _ret.top = static_cast<T>(static_cast<hsd::f32>(top) * Scale);
            _ret.width = static_cast<T>(static_cast<hsd::f32>(width) * Scale);
            _ret.height = static_cast<T>(static_cast<hsd::f32>(height) * Scale);

            return _ret;
        }
    };

    using Vector2I = Vector2<hsd::i32>; // Signed 32-bit integral 2D point
    using Vector2L = Vector2<hsd::i64>; // Signed 64-bit integral 2D point
    using Vector2U = Vector2<hsd::u32>; // Unsigned 32-bit integral 2D point
    using Vector2S = Vector2<hsd::u64>; // Unsigned 64-bit integral 2D point
    using Vector2F = Vector2<hsd::f32>; // Floating-point single precision 2D point
    using Vector2D = Vector2<hsd::f64>; // Floating-point double precision 2D point

    using IRect = Rect<hsd::i32>; // Signed 32-bit integral rectangle
    using LRect = Rect<hsd::i64>; // Signed 64-bit integral rectangle
    using URect = Rect<hsd::u32>; // Unsigned 32-bit integral rectangle
    using SRect = Rect<hsd::u64>; // Unsigned 64-bit integral rectangle
    using FRect = Rect<hsd::f32>; // Floating-point single precision rectangle
    using DRect = Rect<hsd::f64>; // Floating-point double precision rectangle
} // namespace sdl
