#include "Vector.h"
#include <math.h>


//==============================================================================
#pragma region // Vector 2F
//==============================================================================

//////////////////
// OTHER MEMBER
hkCore::Vector2F::Vector2F()
{
    x = 0;
    y = 0;
}

hkCore::Vector2F::Vector2F(float inX, float inY)
{
    x = inX;
    y = inY;
}

hkCore::Vector2F::Vector2F(const hkCore::Vector2F& clone)
{
    x = clone.x;
    y = clone.y;
}

hkCore::Vector2F::~Vector2F()
{

}

hkCore::Vector2F hkCore::Vector2F::operator*(float num)
{
    return hkCore::Vector2F(x * num, y * num);
}

hkCore::Vector2F hkCore::Vector2F::operator/(float num)
{
    return hkCore::Vector2F(x / num, y / num);
}

hkCore::Vector2F hkCore::Vector2F::operator*(float num) const
{
    return hkCore::Vector2F(x * num, y * num);
}

hkCore::Vector2F hkCore::Vector2F::operator/(float num) const
{
    return hkCore::Vector2F(x / num, y / num);
}

hkCore::Vector2F hkCore::Vector2F::operator+(const hkCore::Vector2F& other)
{
    return hkCore::Vector2F(x + other.x, y + other.y);
}

hkCore::Vector2F hkCore::Vector2F::operator-(const hkCore::Vector2F& other)
{
    return hkCore::Vector2F(x - other.x, y - other.y);
}

void hkCore::Vector2F::operator+=(const hkCore::Vector2F& other)
{
    x += other.x;
    y += other.y;
}

void hkCore::Vector2F::operator-=(const hkCore::Vector2F& other)
{
    x -= other.x;
    y -= other.y;
}

void hkCore::Vector2F::operator*=(float num)
{
    x *= num;
    y *= num;
}

void hkCore::Vector2F::operator/=(float num)
{
    x /= num;
    y /= num;
}

void hkCore::Vector2F::operator=(const hkCore::Vector2F& other)
{
    x = other.x;
    y = other.y;
}

bool hkCore::Vector2F::operator==(const hkCore::Vector2F& other)
{
    return x == other.x && y == other.y;
}

bool hkCore::Vector2F::operator!=(const hkCore::Vector2F& other)
{
    return !operator==(other);
}

bool hkCore::Vector2F::operator<(const Vector2F& other)
{
    return Magnitude() < other.Magnitude();
}

bool hkCore::Vector2F::operator>(const Vector2F& other)
{
    return Magnitude() > other.Magnitude();
}

bool hkCore::Vector2F::operator<=(const Vector2F& other)
{
    return Magnitude() <= other.Magnitude();
}

bool hkCore::Vector2F::operator>=(const Vector2F& other)
{
    return Magnitude() >= other.Magnitude();
}

bool hkCore::Vector2F::operator==(const hkCore::Vector2F& other) const
{
    return x == other.x && y == other.y;
}

bool hkCore::Vector2F::operator!=(const hkCore::Vector2F& other) const
{
    return !operator==(other);
}

bool hkCore::Vector2F::operator<(const Vector2F& other) const
{
    return Magnitude() < other.Magnitude();
}

bool hkCore::Vector2F::operator>(const Vector2F& other) const
{
    return Magnitude() > other.Magnitude();
}

bool hkCore::Vector2F::operator<=(const Vector2F& other) const
{
    return Magnitude() <= other.Magnitude();
}

bool hkCore::Vector2F::operator>=(const Vector2F& other) const
{
    return Magnitude() >= other.Magnitude();
}

double hkCore::Vector2F::Magnitude() const
{
    return sqrt((double)(x * x) + (double)(y * y));
}

hkCore::Vector2F hkCore::Vector2F::operator*(const Matrix3x3& matrix)
{
    return hkCore::Vector2F(
        x * matrix[0][0] + y * matrix[1][0] + matrix[2][0],
        x * matrix[0][1] + y * matrix[1][1] + matrix[2][1]);
}

void hkCore::Vector2F::operator*=(const Matrix3x3& matrix)
{
    x = x * matrix[0][0] + y * matrix[1][0] + matrix[2][0];
    y = x * matrix[0][1] + y * matrix[1][1] + matrix[2][1];
}

double hkCore::Vector2F::operator*(const Vector2F& other)
{
    return (double)(x * other.x) + (double)(y * other.y);
}

void hkCore::Vector2F::SetMagnitude(float d)
{
    Normalize();
    x *= d;
    y *= d;
}

void hkCore::Vector2F::Normalize()
{
    double d = Magnitude();
    x /= d;
    y /= d;
}

//==============================================================================
#pragma endregion // Vector 2F
//==============================================================================


//==============================================================================
#pragma region // Vector 3F
//==============================================================================


//////////////////
// OTHER MEMBER
hkCore::Vector3F::Vector3F()
{
    z = 0;
}

hkCore::Vector3F::Vector3F(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

hkCore::Vector3F::Vector3F(const Vector3F& clone)
{
    this->x = clone.x;
    this->y = clone.y;
    this->z = clone.z;
}

hkCore::Vector3F::Vector3F(const Vector2F& clone)
{
    this->x = clone.x;
    this->y = clone.y;
    this->z = 0;
}

hkCore::Vector3F::~Vector3F()
{

}

hkCore::Vector3F hkCore::Vector3F::operator+(const Vector3F& other)
{
    return hkCore::Vector3F(x + other.x, y + other.y, z + other.z);
}

hkCore::Vector3F hkCore::Vector3F::operator-(const Vector3F& other)
{
    return hkCore::Vector3F(x - other.x, y - other.y, z - other.z);
}

hkCore::Vector3F hkCore::Vector3F::operator*(float num)
{
    return hkCore::Vector3F(x * num, y * num, z * num);
}

hkCore::Vector3F hkCore::Vector3F::operator/(float num)
{
    return hkCore::Vector3F(x / num, y / num, z / num);
}

hkCore::Vector3F hkCore::Vector3F::operator*(float num) const
{
    return hkCore::Vector3F(x * num, y * num, z * num);
}

hkCore::Vector3F hkCore::Vector3F::operator/(float num) const
{
    return hkCore::Vector3F(x / num, y / num, z / num);
}

void hkCore::Vector3F::operator=(const Vector3F& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

void hkCore::Vector3F::operator+=(const Vector3F& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
}

void hkCore::Vector3F::operator-=(const Vector3F& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

void hkCore::Vector3F::operator*=(float num)
{
    x *= num;
    y *= num;
    z *= num;
}

void hkCore::Vector3F::operator/=(float num)
{
    x /= num;
    y /= num;
    z /= num;
}

hkCore::Vector3F hkCore::Vector3F::operator*(const Matrix3x3& matrix)
{
    return hkCore::Vector3F(x * matrix[0][0] + y * matrix[1][0] + z * matrix[2][0],
        x * matrix[0][1] + y * matrix[1][1] + z * matrix[2][1],
        x * matrix[0][2] + y * matrix[1][2] + z * matrix[2][2]);
}

void hkCore::Vector3F::operator*=(const Matrix3x3& matrix)
{
    x = x * matrix[0][0] + y * matrix[1][0] + z * matrix[2][0];
    y = x * matrix[0][1] + y * matrix[1][1] + z * matrix[2][1];
    z = x * matrix[0][2] + y * matrix[1][2] + z * matrix[2][2];
}

hkCore::Vector3F hkCore::Vector3F::operator*(const Matrix4x4& matrix)
{
    return hkCore::Vector3F(x * matrix[0][0] + y * matrix[1][0] + z * matrix[2][0] + matrix[3][0],
        x * matrix[0][1] + y * matrix[1][1] + z * matrix[2][1] + matrix[3][1],
        x * matrix[0][2] + y * matrix[1][2] + z * matrix[2][2] + matrix[3][2]);
}

void hkCore::Vector3F::operator*=(const Matrix4x4& matrix)
{
    x = x * matrix[0][0] + y * matrix[1][0] + z * matrix[2][0] + matrix[3][0];
    y = x * matrix[0][1] + y * matrix[1][1] + z * matrix[2][1] + matrix[3][1];
    z = x * matrix[0][2] + y * matrix[1][2] + z * matrix[2][2] + matrix[3][2];
}

bool hkCore::Vector3F::operator==(const Vector3F& other)
{
    return x == other.x && y == other.y && z == other.z;
}

bool hkCore::Vector3F::operator<(const Vector3F& other)
{
    return Magnitude() < other.Magnitude();
}

bool hkCore::Vector3F::operator>(const Vector3F& other)
{
    return Magnitude() > other.Magnitude();
}

bool hkCore::Vector3F::operator<=(const Vector3F& other)
{
    return Magnitude() <= other.Magnitude();
}

bool hkCore::Vector3F::operator>=(const Vector3F& other)
{
    return Magnitude() >= other.Magnitude();
}

double hkCore::Vector3F::operator*(const Vector3F& other)
{
    return (double)(x * other.x) + (double)(y * other.y) + (double)(z * other.z);
}

double hkCore::Vector3F::Magnitude() const
{
    return sqrt((double)(x * x) + (double)(y * y) + (double)(z * z));
}

void hkCore::Vector3F::SetMagnitude(float d)
{
    Normalize();
    x *= d;
    y *= d;
    z *= d;
}

void hkCore::Vector3F::Normalize()
{
    double d = Magnitude();
    x /= d;
    y /= d;
    z /= d;
}

hkCore::Vector3F hkCore::Vector3F::Cross(const hkCore::Vector3F& other)
{
    return hkCore::Vector3F(y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x);
}

//==============================================================================
#pragma endregion // Vector 3F
//==============================================================================