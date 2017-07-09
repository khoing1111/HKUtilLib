#pragma once

/////////////
// INCLUDE
#include "../Core.h"
#include "Vector.h"


namespace hkCore
{
    ///////////////
    // PREDEFINE
    struct Vector2F;
    struct Vector3F;


    ////////////////////
    // STRUCT: Matrix
    struct Matrix
    {
    public:
        ////////////
        // STATIC
        static Matrix Identity(uint x, uint y);


        ////////////
        // MEMBER
    public:
        Matrix();
        Matrix(uint numRow, uint numColumn);
        Matrix(uint numRow, uint numColumn, float** data);
        Matrix(const Matrix& clone);
        ~Matrix();

        void operator=(const Matrix&);
        void operator*=(const Matrix&);
        bool operator==(const Matrix&);
        Matrix operator*(const Matrix&);

        void operator<<(Matrix&);
        void operator>>(Matrix&);

        float* operator[](uint x);
        float* operator[](uint x) const;

        Matrix Transpose();
        void SetTranspose();
        void SetIdentity();
        void SetZero();

        uint GetNumRow();
        uint GetNumColumn();

        //////////////
        // VARIABLE
    protected:
        float** m_cells;
        uint m_numRow, m_numColumn;
    };


    ///////////////////////
    // STRUCT: Matrix3x3
    struct Matrix3x3 : public Matrix
    {
    public:
        ////////////
        // STATIC
        static Matrix3x3 Identity();

    public:
        ////////////
        // MEMBER
        Matrix3x3();
        Matrix3x3(const Matrix3x3&);
        ~Matrix3x3();

        Matrix3x3 operator*(const Matrix3x3&);
        Matrix3x3 Transpose();

        void SetTranslation(float x, float y);
        void SetScaling(float x, float y);
        void SetRotation(float r);

        void Move(float x, float y);
        void Scale(float x, float y);
        void Rotate(float r);

        hkCore::Vector2F GetTranslation();
        hkCore::Vector2F GetScaling();
        float GetRotation();
    };
    
    
    ///////////////////////
    // STRUCT: Matrix4x4
    struct Matrix4x4 : public Matrix
    {
    public:
        ////////////
        // STATIC
        static Matrix4x4 Identity();

    public:
        ////////////
        // MEMBER
        Matrix4x4();
        Matrix4x4(const Matrix4x4&);
        ~Matrix4x4();

        Matrix4x4 operator*(const Matrix4x4&);
        Matrix4x4 Transpose();

        void SetTranslation(float x, float y, float z);
        void SetScaling(float x, float y, float z);
        void SetRotation(float rX, float rY, float rZ);

        void Move(float x, float y, float z);
        void Scale(float x, float y, float z);
        void Rotate(float rX, float rY, float rZ);

        void SetTranslation(const hkCore::Vector3F&);
        void SetScaling(const hkCore::Vector3F&);
        void SetRotation(const hkCore::Vector3F&);

        void Move(const hkCore::Vector3F&);
        void Scale(const hkCore::Vector3F&);
        void Rotate(const hkCore::Vector3F&);

        hkCore::Vector3F GetTranslation();
        hkCore::Vector3F GetScaling();
        hkCore::Vector3F GetRollPitchYaw();
    };
}


////////////
// DEFINE
#define hkMatrix hkCore::Matrix
#define hkMatrix3x3 hkCore::Matrix3x3
#define hkMatrix4x4 hkCore::Matrix4x4