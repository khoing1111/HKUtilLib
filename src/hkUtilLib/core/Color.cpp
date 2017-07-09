#include "Color.h"

//============================================================================================
#pragma region // RGB Color
//============================================================================================

///////////////////
// STATIC MEMBER
/* CONST */
const hkCore::Color::RGBColor hkCore::Color::RGBColor::BLACK(0.0f, 0.0f, 0.0f);
const hkCore::Color::RGBColor hkCore::Color::RGBColor::WHITE(1.0f, 1.0f, 1.0f);
const hkCore::Color::RGBColor hkCore::Color::RGBColor::RED(1.0f, 0.0f, 0.0f);
const hkCore::Color::RGBColor hkCore::Color::RGBColor::GREEN(0.0f, 1.0f, 0.0f);
const hkCore::Color::RGBColor hkCore::Color::RGBColor::BLUE(0.0f, 0.0f, 1.0f);
const hkCore::Color::RGBColor hkCore::Color::RGBColor::YELLOW(1.0f, 1.0f, 0.0f);
const hkCore::Color::RGBColor hkCore::Color::RGBColor::GRAY(0.5f, 0.5f, 0.5f);
const hkCore::Color::RGBColor hkCore::Color::RGBColor::PALE_BLACK(0.75f, 0.75f, 0.75f);


//////////////////
// CLASS MEMBER
hkCore::Color::RGBColor::RGBColor()
{
    r = 0;
    g = 0;
    b = 0;
}

hkCore::Color::RGBColor::RGBColor(const RGBColor& clone)
{
    r = clone.r;
    g = clone.g;
    b = clone.b;
}

hkCore::Color::RGBColor::RGBColor(float inR, float inG, float inB)
{
    r = inR;
    g = inG;
    b = inB;

    RoundUp();
}

hkCore::Color::RGBColor hkCore::Color::RGBColor::operator+(const RGBColor& other)
{
    RGBColor result;

    result.r = r + other.r;
    result.g = g + other.g;
    result.b = b + other.b;

    result.RoundUp();

    return result;
}
//
hkCore::Color::RGBColor hkCore::Color::RGBColor::operator-(const RGBColor& other)
{
    RGBColor result;

    result.r = r - other.r;
    result.g = g - other.g;
    result.b = b - other.b;

    result.RoundUp();

    return result;
}

hkCore::Color::RGBColor hkCore::Color::RGBColor::operator*(float value)
{
    return RGBColor(r * value, g * value, b * value);
}

hkCore::Color::RGBColor hkCore::Color::RGBColor::operator/(float value)
{
    return RGBColor(r / value, g / value, b / value);
}

void hkCore::Color::RGBColor::operator=(const RGBColor& other)
{
    r = other.r;
    g = other.g;
    b = other.b;
}

void hkCore::Color::RGBColor::operator+=(const RGBColor& other)
{
    *this = *this + other;
}

void hkCore::Color::RGBColor::operator-=(const RGBColor& other)
{
    *this = *this + other;
}

void hkCore::Color::RGBColor::operator*=(float value)
{
    *this = *this * value;
}

void hkCore::Color::RGBColor::operator/=(float value)
{
    *this = *this / value;
}

bool hkCore::Color::RGBColor::operator==(const RGBColor& other)
{
    return r == other.r && g == other.g && b == other.b;
}

bool hkCore::Color::RGBColor::operator!=(const RGBColor& other)
{
    return r != other.r || g != other.g || b != other.b;
}

bool hkCore::Color::RGBColor::operator==(const RGBColor& other) const
{
    return r == other.r && g == other.g && b == other.b;
}

bool hkCore::Color::RGBColor::operator!=(const RGBColor& other) const
{
    return r != other.r || g != other.g || b != other.b;
}

uint hkCore::Color::RGBColor::ToNumber() const
{
    return Convert(r) << 24 | Convert(g) << 16 | Convert(b) << 8 | 0xFF;
}

uint hkCore::Color::RGBColor::Convert(const float& value) const
{
    if (value < 0.0f)
        return 0;
    else if (value > 255.0f)
        return 255;
    else
        return (uint)value;
}

bool hkCore::Color::RGBColor::operator>(const RGBColor& color)
{
    return ToNumber() > color.ToNumber();
}

bool hkCore::Color::RGBColor::operator<(const RGBColor& color)
{
    return ToNumber() < color.ToNumber();
}

bool hkCore::Color::RGBColor::operator>=(const RGBColor& color)
{
    return ToNumber() >= color.ToNumber();
}

bool hkCore::Color::RGBColor::operator<=(const RGBColor& color)
{
    return ToNumber() <= color.ToNumber();
}

void hkCore::Color::RGBColor::RoundUp()
{
    RoundUp(r);
    RoundUp(g);
    RoundUp(b);
}

float hkCore::Color::RGBColor::RoundUp(float value)
{
    if (value > 1.0f) return 1.0f;
    else if (value < 0) return 0;

    return value;
}

//============================================================================================
#pragma region // RGB Color
//============================================================================================

//============================================================================================
#pragma region // RGBA Color
//============================================================================================

//////////////
// CONSTANT
const hkCore::Color::RGBAColor hkCore::Color::RGBAColor::BLACK(RGBColor::BLACK);
const hkCore::Color::RGBAColor hkCore::Color::RGBAColor::WHITE(RGBColor::WHITE);
const hkCore::Color::RGBAColor hkCore::Color::RGBAColor::RED(RGBColor::RED);
const hkCore::Color::RGBAColor hkCore::Color::RGBAColor::GREEN(RGBColor::GREEN);
const hkCore::Color::RGBAColor hkCore::Color::RGBAColor::BLUE(RGBColor::BLUE);
const hkCore::Color::RGBAColor hkCore::Color::RGBAColor::YELLOW(RGBColor::YELLOW);
const hkCore::Color::RGBAColor hkCore::Color::RGBAColor::GRAY(RGBColor::GRAY);
const hkCore::Color::RGBAColor hkCore::Color::RGBAColor::PALE_BLACK(RGBColor::PALE_BLACK);


////////////
// MEMBER
hkCore::Color::RGBAColor::RGBAColor()
{
    a = 1;
}

hkCore::Color::RGBAColor::RGBAColor(const RGBAColor& clone)
{
    r = clone.r;
    g = clone.g;
    b = clone.b;
    a = clone.a;
}


hkCore::Color::RGBAColor::RGBAColor(const RGBColor& clone)
{
    this->r = clone.r;
    this->g = clone.g;
    this->b = clone.b;
    this->a = 1;
}

hkCore::Color::RGBAColor::RGBAColor(float inR, float inG, float inB)
{
    r = inR;
    g = inG;
    b = inB;
    a = 1;

    RoundUp();
}

hkCore::Color::RGBAColor::RGBAColor(float inR, float inG, float inB, float inA)
{
    r = inR;
    g = inG;
    b = inB;
    a = inA;

    RoundUp();
}

hkCore::Color::RGBAColor hkCore::Color::RGBAColor::operator+(const RGBAColor other)
{
    RGBAColor result;

    result.r = r + other.r;
    result.g = g + other.a;
    result.b = b + other.b;
    result.a = a + other.a;

    result.RoundUp();

    return result;
}

hkCore::Color::RGBAColor hkCore::Color::RGBAColor::operator-(const RGBAColor other)
{
    RGBAColor result;

    result.r = r - other.r;
    result.g = g - other.a;
    result.b = b - other.b;
    result.a = a - other.a;

    result.RoundUp();

    return result;
}

hkCore::Color::RGBAColor hkCore::Color::RGBAColor::operator*(float value)
{
    return RGBAColor(r * value, g * value, b * value, a * value);
}

hkCore::Color::RGBAColor hkCore::Color::RGBAColor::operator/(float value)
{
    return RGBAColor(r / value, g / value, b / value, a / value);
}

void hkCore::Color::RGBAColor::operator=(const RGBAColor other)
{
    r = other.r;
    g = other.g;
    b = other.b;
    a = other.a;
}

void hkCore::Color::RGBAColor::operator+=(const RGBAColor other)
{
    *this = *this + other;
}

void hkCore::Color::RGBAColor::operator-=(const RGBAColor other)
{
    *this = *this - other;
}

void hkCore::Color::RGBAColor::operator*=(float value)
{
    *this = *this * value;
}

void hkCore::Color::RGBAColor::operator/=(float value)
{
    *this = *this / value;
}

bool hkCore::Color::RGBAColor::operator==(const RGBAColor other)
{
    return r == other.r && g == other.g && b == other.b && a == other.a;
}

bool hkCore::Color::RGBAColor::operator!=(const RGBAColor other)
{
    return r != other.r || g != other.g || b != other.b || a != other.a;
}

bool hkCore::Color::RGBAColor::operator==(const RGBAColor other) const
{
    return r == other.r && g == other.g && b == other.b && a == other.a;
}

bool hkCore::Color::RGBAColor::operator!=(const RGBAColor other) const
{
    return r != other.r || g != other.g || b != other.b || a != other.a;
}

uint hkCore::Color::RGBAColor::ToNumber() const
{
    return Convert(r) << 24 | Convert(g) << 16 | Convert(b) << 8 | Convert(a);
}

bool hkCore::Color::RGBAColor::operator>(const RGBAColor& color)
{
    return ToNumber() > color.ToNumber();
}

bool hkCore::Color::RGBAColor::operator<(const RGBAColor& color)
{
    return ToNumber() < color.ToNumber();
}

bool hkCore::Color::RGBAColor::operator>=(const RGBAColor& color)
{
    return ToNumber() >= color.ToNumber();
}

bool hkCore::Color::RGBAColor::operator<=(const RGBAColor& color)
{
    return ToNumber() <= color.ToNumber();
}

void hkCore::Color::RGBAColor::RoundUp()
{
    RGBColor::RoundUp();	// Round up r, g and b color
    RGBColor::RoundUp(a);
}

//============================================================================================
#pragma endregion // RGBA Color
//============================================================================================