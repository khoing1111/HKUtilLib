#pragma once

/////////////
// INCLUDE
#include "Matrix.h"


namespace hkCore
{
    ///////////////
    // PREDEFINE
    struct Matrix3x3;
    struct Matrix4x4;


    /////////////////////
    // STRUCT: Vector2F
    struct Vector2F
    {
    public:
        Vector2F();
        Vector2F(float x, float y);
        Vector2F(const Vector2F&);
        ~Vector2F();

        Vector2F operator+(const Vector2F&);
        Vector2F operator-(const Vector2F&);
        Vector2F operator*(float);
        Vector2F operator/(float);

        Vector2F operator*(float) const;
        Vector2F operator/(float) const;

        void operator=(const Vector2F&);
        void operator+=(const Vector2F&);
        void operator-=(const Vector2F&);
        void operator*=(float);
        void operator/=(float);

        void operator*=(const Matrix3x3&);
        Vector2F operator*(const Matrix3x3&);

        //----------------------------------------------------------------------------
        // Vector length compare (Base on distance)
        bool operator==(const Vector2F&);
        bool operator!=(const Vector2F&);
        bool operator<(const Vector2F&);
        bool operator>(const Vector2F&);
        bool operator<=(const Vector2F&);
        bool operator>=(const Vector2F&);

        bool operator==(const Vector2F&) const;
        bool operator!=(const Vector2F&) const;
        bool operator<(const Vector2F&) const;
        bool operator>(const Vector2F&) const;
        bool operator<=(const Vector2F&) const;
        bool operator>=(const Vector2F&) const;

        //----------------------------------------------------------------------------
        // Vector operation
        double operator*(const Vector2F&);

        double Magnitude() const;
        void SetMagnitude(float d);
        void Normalize();

        //----------------------------------------------------------------------------
    public:
        float x;
        float y;
    };


    /////////////////////
    // STRUCT: Vector3F
    struct Vector3F : Vector2F
    {
    public:
        Vector3F();
        Vector3F(float x, float y, float z);
        Vector3F(const Vector3F&);
        Vector3F(const Vector2F&);
        ~Vector3F();

        Vector3F operator+(const Vector3F&);
        Vector3F operator-(const Vector3F&);
        Vector3F operator*(float);
        Vector3F operator/(float);

        Vector3F operator*(float) const;
        Vector3F operator/(float) const;

        Vector3F Cross(const Vector3F&);

        void operator=(const Vector3F&);
        void operator+=(const Vector3F&);
        void operator-=(const Vector3F&);
        void operator*=(float);
        void operator/=(float);

        Vector3F operator*(const Matrix3x3&);
        void operator*=(const Matrix3x3&);

        Vector3F operator*(const Matrix4x4&);
        void operator*=(const Matrix4x4&);


        //----------------------------------------------------------------------------
        // Vector length compare (Base on distance)
        bool operator==(const Vector3F&);
        bool operator<(const Vector3F&);
        bool operator>(const Vector3F&);
        bool operator<=(const Vector3F&);
        bool operator>=(const Vector3F&);

        //----------------------------------------------------------------------------
        // Vector operation
        double operator*(const Vector3F&);

        double Magnitude() const;
        void SetMagnitude(float d);
        void Normalize();

    public:
        float z;
    };
}

////////////
// DEFINE
#define hkVector2F hkCore::Vector2F
#define hkVector3F hkCore::Vector3F