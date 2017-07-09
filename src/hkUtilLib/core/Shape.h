#pragma once


/////////////
// INCLUDE
#include "Matrix.h"


namespace hkCore
{
    namespace Shape
    {
        /////////////////////////
        // STRUCT: Rectangle2F
        struct Rectangle2F
        {
        public:
            Rectangle2F();
            Rectangle2F(const Rectangle2F&);
            Rectangle2F(float top, float bottom, float left, float right);
            Rectangle2F(hkCore::Vector2F topLeft, hkCore::Vector2F bottomRight);
            ~Rectangle2F();

            bool operator==(const Rectangle2F&);
            bool operator==(const Rectangle2F&) const;
            
            void operator=(const Rectangle2F&);
            void operator*=(float);
            void operator/=(float);

            Rectangle2F operator*(float);
            Rectangle2F operator/(float);

            hkCore::Vector2F GetTopLeft();
            hkCore::Vector2F GetBottomRight();
            float GetWidth() const;
            float GetHeight() const;
            
            void Move(float x, float y);

            bool IsOverlapedWith(const hkCore::Shape::Rectangle2F &rect);

        private:
            inline void ReAdjust();

        public:
            float left;
            float top;
            float right;
            float bottom;
        };
    }
}


////////////
// DEFINE
#define hkRect2F hkCore::Shape::Rectangle2F