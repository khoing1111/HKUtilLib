#include "Shape.h"


//////////////////
// CLASS MEMBER
hkCore::Shape::Rectangle2F::Rectangle2F()
{
    top = 0;
    left = 0;
    right = 0;
    bottom = 0;
}

hkCore::Shape::Rectangle2F::Rectangle2F(const Rectangle2F& other)
{
    top = other.top;
    bottom = other.bottom;
    left = other.left;
    right = other.right;
}

hkCore::Shape::Rectangle2F::Rectangle2F(float top, float bottom, float left, float right)
{
    this->top = top;
    this->left = left;
    this->right = right;
    this->bottom = bottom;

    ReAdjust();
}

hkCore::Shape::Rectangle2F::Rectangle2F(hkCore::Vector2F topLeft, hkCore::Vector2F bottomRight)
{
    this->top = topLeft.y;
    this->left = topLeft.x;
    this->bottom = bottomRight.y;
    this->right = bottomRight.x;

    ReAdjust();
}

inline void hkCore::Shape::Rectangle2F::ReAdjust()
{
    if (top < bottom)
    {
        float tmp = top;
        top = bottom;
        bottom = tmp;
    }

    if (left > right)
    {
        float tmp = left;
        left = right;
        right = tmp;
    }
}

hkCore::Shape::Rectangle2F::~Rectangle2F()
{

}

bool hkCore::Shape::Rectangle2F::operator==(const Rectangle2F& other)
{
    return top == other.top && bottom == other.bottom &&
        left == other.left && right == other.right;
}

bool hkCore::Shape::Rectangle2F::operator==(const Rectangle2F& other) const
{
    return top == other.top && bottom == other.bottom &&
        left == other.left && right == other.right;
}

void hkCore::Shape::Rectangle2F::operator=(const Rectangle2F& other)
{
    top = other.top;
    bottom = other.bottom;
    left = other.left;
    right = other.right;
}

void hkCore::Shape::Rectangle2F::operator*=(float value)
{
    top *= value;
    bottom *= value;
    left *= value;
    right *= value;
}

void hkCore::Shape::Rectangle2F::operator/=(float value)
{
    top /= value;
    bottom /= value;
    left /= value;
    right /= value;
}

hkCore::Shape::Rectangle2F hkCore::Shape::Rectangle2F::operator*(float value)
{
    Rectangle2F result = *this;
    result /= value;
    return result;
}

hkCore::Shape::Rectangle2F hkCore::Shape::Rectangle2F::operator/(float value)
{
    Rectangle2F result = *this;
    result /= value;
    return result;
}


hkCore::Vector2F hkCore::Shape::Rectangle2F::GetTopLeft()
{
    return hkCore::Vector2F(left, top);
}

hkCore::Vector2F hkCore::Shape::Rectangle2F::GetBottomRight()
{
    return hkCore::Vector2F(right, bottom);
}

float hkCore::Shape::Rectangle2F::GetWidth() const
{
    return right - left;
}

float hkCore::Shape::Rectangle2F::GetHeight() const
{
    return bottom - top;
}

void hkCore::Shape::Rectangle2F::Move(float x, float y)
{
    left += x;
    right += x;
    
    top += y;
    bottom += y;
}

bool hkCore::Shape::Rectangle2F::IsOverlapedWith(const hkCore::Shape::Rectangle2F& rect)
{
    // If one Rectangle2F is on left side of other
    if (left > rect.right || rect.left > right)
        return false;

    // If one Rectangle2F is above other
    if (top < rect.bottom || rect.top < bottom)
        return false;

    return true;
}