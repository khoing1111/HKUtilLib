#include "Matrix.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>

//==============================================================================
#pragma region // Matrix
//==============================================================================

////////////////////
// STATIC MEMBERS
hkCore::Matrix hkCore::Matrix::Identity(uint x, uint y)
{
    Matrix result(x, y);
    result.SetIdentity();
    return result;
}


////////////////////
// OTHER MEMEBERS
hkCore::Matrix::Matrix()
{
    m_numRow = 0;
    m_numColumn = 0;
    m_cells = nullptr;
}

hkCore::Matrix::Matrix(uint numRow, uint numColumn)
{
    if (numRow > 0 && numColumn > 0)
    {
        this->m_numRow = numRow;
        this->m_numColumn = numColumn;

        this->m_cells = hk_new_pp<float>(numRow, numColumn);

        SetIdentity();
    }
    else
    {
        m_numRow = 0;
        m_numColumn = 0;
        m_cells = nullptr;
    }
}

hkCore::Matrix::Matrix(uint numRow, uint numColumn, float** data)
{
    this->m_numRow = numRow;
    this->m_numColumn = numColumn;
    this->m_cells = data;
}

hkCore::Matrix::Matrix(const Matrix& clone)
{
    m_numRow = clone.m_numRow;
    m_numColumn = clone.m_numColumn;

    m_cells = hk_clone_pp<float>(clone.m_cells, m_numRow, m_numColumn);
}

hkCore::Matrix::~Matrix()
{
    if (m_cells)
    {
        hk_delete_pp(m_cells, m_numRow);
        m_cells = nullptr;
    }

    m_numColumn = 0;
    m_numRow = 0;
}

void hkCore::Matrix::operator=(const Matrix& other)
{
    if (m_cells)
        hk_delete_pp(m_cells, m_numRow);

    m_numRow = other.m_numRow;
    m_numColumn = other.m_numColumn;

    m_cells = hk_clone_pp(other.m_cells, m_numRow, m_numColumn);
}

void hkCore::Matrix::operator*=(const Matrix& other)
{
    if (m_numColumn != other.m_numRow)
        return;

    uint row = m_numRow;
    uint column = other.m_numColumn;

    for (uint i = 0; i < row; i++)
    {
        for (uint j = 0; j < column; j++)
        {
            float newCellValue = 0;

            for (uint inner = 0; inner < column; inner++)
            {
                float v1 = m_cells[i][inner];
                float v2 = other[inner][j];
                newCellValue += m_cells[i][inner] * other[inner][j];
            }

            (*this)[i][j] = newCellValue;
        }
    }
}

bool hkCore::Matrix::operator==(const Matrix& other)
{
    if (m_numColumn != other.m_numColumn || m_numRow != other.m_numRow
        || m_numColumn == 0 || m_numRow == 0)
        return false;

    return hk_is_equal_pp(m_cells, other.m_cells, m_numRow, m_numColumn);
}


void hkCore::Matrix::operator<<(Matrix& other)
{
    if (other.m_cells)
    {
        if (m_cells)
            hk_delete_pp(m_cells, m_numRow);

        m_numRow = other.m_numRow;
        m_numColumn = other.m_numColumn;
        m_cells = other.m_cells;

        other.m_cells = nullptr;
        other.m_numRow = 0;
        other.m_numColumn = 0;
    }
}

void hkCore::Matrix::operator>>(Matrix& other)
{
    if (m_cells)
    {
        if (other.m_cells)
            hk_delete_pp(m_cells, m_numRow);

        other.m_numRow = m_numRow;
        other.m_numColumn = m_numColumn;
        other.m_cells = m_cells;

        m_cells = nullptr;
        m_numRow = 0;
        m_numColumn = 0;
    }
}

float* hkCore::Matrix::operator[](uint x)
{
    return m_cells[x];
}

float* hkCore::Matrix::operator[](uint x) const
{
    return m_cells[x];
}

hkCore::Matrix hkCore::Matrix::operator*(const Matrix& other)
{
    if (m_numColumn != other.m_numRow)
        return Matrix();

    uint row = m_numRow;
    uint column = other.m_numColumn;

    float **data = hk_new_pp<float>(row, column);

    for (uint i = 0; i < row; i++)
    {
        for (uint j = 0; j < column; j++)
        {
            data[i][j] = 0;

            for (uint inner = 0; inner < column; inner++)
            {
                data[i][j] += m_cells[i][inner] * other[inner][j];
            }
        }
    }

    Matrix result(row, column, data);

    return result;
}

hkCore::Matrix hkCore::Matrix::Transpose()
{
    float **data = hk_new_pp<float>(m_numRow, m_numColumn);

    for (uint i = 0; i < m_numRow; i++)
    {
        for (uint j = 0; j < m_numColumn; j++)
        {
            data[j][i] = m_cells[i][j];
        }
    }

    Matrix result(m_numColumn, m_numRow, data);

    return result;
}

void hkCore::Matrix::SetTranspose()
{
    (*this) << Transpose();
}

void hkCore::Matrix::SetIdentity()
{
    for (uint i = 0; i < m_numRow; i++)
    {
        for (uint j = 0; j < m_numColumn; j++)
        {
            if (i == j)
                m_cells[i][j] = 1.0f;
            else
                m_cells[i][j] = 0.0f;
        }
    }
}

void hkCore::Matrix::SetZero()
{
    for (uint i = 0; i < m_numRow; i++)
        for (uint j = 0; j < m_numColumn; j++)
            m_cells[i][j] = 0.0f;
}

uint hkCore::Matrix::GetNumRow() {
    return m_numRow;
}

uint hkCore::Matrix::GetNumColumn() {
    return m_numColumn;
}

//==============================================================================
#pragma endregion // Matrix
//==============================================================================


//==============================================================================
#pragma region // Matrix3x3
//==============================================================================

////////////////////
// STATIC MEMBERS
hkCore::Matrix3x3 hkCore::Matrix3x3::Identity()
{
    Matrix3x3 result;
    result.SetIdentity();

    return result;
}


///////////////////
// OTHER MEMBERS
hkCore::Matrix3x3::Matrix3x3() : Matrix(3, 3)
{
}

hkCore::Matrix3x3::Matrix3x3(const Matrix3x3& clone) : Matrix(clone)
{
}

hkCore::Matrix3x3::~Matrix3x3()
{

}

hkCore::Matrix3x3 hkCore::Matrix3x3::operator*(const Matrix3x3& other)
{
    hkMatrix3x3 result;
    result << Matrix::operator*(other);
    return result;
}

hkCore::Matrix3x3 hkCore::Matrix3x3::Transpose()
{
    hkMatrix3x3 result;
    result << Matrix::Transpose();
    return result;
}

void hkCore::Matrix3x3::SetTranslation(float x, float y)
{
    SetIdentity();

    m_cells[2][0] = x;
    m_cells[2][1] = y;
}

void hkCore::Matrix3x3::SetScaling(float x, float y)
{
    SetIdentity();

    m_cells[0][0] = x;
    m_cells[1][1] = y;
}

void hkCore::Matrix3x3::SetRotation(float r)
{
    SetIdentity();

    float inRadiant = r * (float) M_PI / 180;
    float cosR = cos(inRadiant);
    float sinR = sin(inRadiant);

    m_cells[0][0] = cosR;
    m_cells[0][1] = -sinR;
    m_cells[1][0] = sinR;
    m_cells[1][1] = cosR;
}

void hkCore::Matrix3x3::Move(float x, float y)
{
    m_cells[2][0] += x;
    m_cells[2][1] += y;
}

void hkCore::Matrix3x3::Scale(float x, float y)
{
    Matrix3x3 scaleMatrix;
    scaleMatrix.SetScaling(x, y);

    (*this) *= scaleMatrix;
}

void hkCore::Matrix3x3::Rotate(float r)
{
    Matrix3x3 rotateMatrix;
    rotateMatrix.SetRotation(r);

    (*this) *= rotateMatrix;
}

hkCore::Vector2F hkCore::Matrix3x3::GetTranslation()
{
    return hkCore::Vector2F(m_cells[2][0], m_cells[2][1]);
}

hkCore::Vector2F hkCore::Matrix3x3::GetScaling()
{
    float scaleX = (m_cells[0][0] < 0 ? -1 : 1) *
        sqrt(m_cells[0][0] * m_cells[0][0] + m_cells[0][1] * m_cells[0][1]);

    float scaleY = (m_cells[1][1] < 0 ? -1 : 1) *
        sqrt(m_cells[1][0] * m_cells[1][0] + m_cells[1][1] * m_cells[1][1]);

    return hkCore::Vector2F(scaleX, scaleY);
}

float hkCore::Matrix3x3::GetRotation()
{
    return atan2(m_cells[1][0], m_cells[1][1]);
}

//==============================================================================
#pragma endregion // Matrix3x3
//==============================================================================


//==============================================================================
#pragma region // Matrix4x4
//==============================================================================

////////////////////
// STATIC MEMBERS
hkCore::Matrix4x4 hkCore::Matrix4x4::Identity()
{
    Matrix4x4 result;
    result.SetIdentity();

    return result;
}


///////////////////
// OTHER MEMBERS
hkCore::Matrix4x4::Matrix4x4() : Matrix(4, 4)
{
}

hkCore::Matrix4x4::Matrix4x4(const Matrix4x4& clone) : Matrix(clone)
{
}

hkCore::Matrix4x4::~Matrix4x4()
{

}

hkMatrix4x4 hkCore::Matrix4x4::operator*(const Matrix4x4& other)
{
    hkMatrix4x4 result;
    result << Matrix::operator*(other);
    return result;
}

hkMatrix4x4 hkCore::Matrix4x4::Transpose()
{
    hkMatrix4x4 result;
    result << Matrix::Transpose();
    return result;
}

void hkCore::Matrix4x4::SetTranslation(float x, float y, float z)
{
    SetIdentity();

    m_cells[3][0] = x;
    m_cells[3][1] = y;
    m_cells[3][2] = z;
}

void hkCore::Matrix4x4::SetScaling(float x, float y, float z)
{
    SetIdentity();

    m_cells[0][0] = x;
    m_cells[1][1] = y;
    m_cells[2][2] = z;
}

void hkCore::Matrix4x4::SetRotation(float rX, float rY, float rZ)
{
    SetIdentity();

    float alpha = rX * (float)M_PI / 180;
    float beta = rY * (float)M_PI / 180;
    float gamma = rZ * (float)M_PI / 180;

    float cosAlpha = cos(alpha);
    float sinAlpha = sin(alpha);

    float cosBeta = cos(beta);
    float sinBeta = sin(beta);

    float cosGamma = cos(gamma);
    float sinGamma = sin(gamma);

    m_cells[0][0] = cosBeta * cosGamma;
    m_cells[0][1] = - cosBeta * sinGamma;
    m_cells[0][2] = sinBeta;
    m_cells[1][0] = cosAlpha * sinGamma + sinAlpha * sinBeta * cosGamma;
    m_cells[1][1] = cosAlpha * cosGamma - sinAlpha * sinBeta * sinGamma;
    m_cells[1][2] = - sinAlpha * cosBeta;
    m_cells[2][0] = sinAlpha * sinGamma - cosAlpha * sinBeta * cosGamma;
    m_cells[2][1] = sinAlpha * cosGamma + cosAlpha * sinBeta * sinGamma;
    m_cells[2][2] = cosAlpha * cosBeta;
}

void hkCore::Matrix4x4::Move(float x, float y, float z)
{
    m_cells[3][0] += x;
    m_cells[3][1] += y;
    m_cells[3][2] += z;
}

void hkCore::Matrix4x4::Scale(float x, float y, float z)
{
    Matrix4x4 scaleMatrix = Matrix4x4::Identity();
    scaleMatrix.SetScaling(x, y, z);

    (*this) *= scaleMatrix;
}

void hkCore::Matrix4x4::Rotate(float rX, float rY, float rZ)
{
    Matrix4x4 rotateMatrix;
    rotateMatrix.SetRotation(rX, rY, rZ);

    (*this) *= rotateMatrix;
}

hkCore::Vector3F hkCore::Matrix4x4::GetTranslation()
{
    return hkCore::Vector3F(m_cells[3][0], m_cells[3][1], m_cells[3][2]);
}

hkCore::Vector3F hkCore::Matrix4x4::GetScaling()
{
    float scaleX = (m_cells[0][0] < 0 ? -1 : 1) *
        sqrt(m_cells[0][0] * m_cells[0][0] + 
        m_cells[0][1] * m_cells[0][1] + 
        m_cells[0][2] * m_cells[0][2]);

    float scaleY = (m_cells[1][1] < 0 ? -1 : 1) *
        sqrt(m_cells[1][0] * m_cells[1][0] + 
        m_cells[1][1] * m_cells[1][1] +
        m_cells[1][2] * m_cells[1][2]);

    float scaleZ = (m_cells[2][2] < 0 ? -1 : 1) *
        sqrt(m_cells[2][0] * m_cells[2][0] +
        m_cells[2][1] * m_cells[2][1] +
        m_cells[2][2] * m_cells[2][2]);

    return hkCore::Vector3F(scaleX, scaleY, scaleZ);
}

hkCore::Vector3F hkCore::Matrix4x4::GetRollPitchYaw()
{
    double sinPitch, cosPitch, sinRoll, cosRoll, sinYaw, cosYaw;

    sinPitch = -m_cells[2][0];
    cosPitch = sqrt(1 - sinPitch*sinPitch);

    if (abs(cosPitch) > DBL_EPSILON)
    {
        sinRoll = m_cells[2][1] / cosPitch;
        cosRoll = m_cells[2][2] / cosPitch;
        sinYaw = m_cells[1][0] / cosPitch;
        cosYaw = m_cells[0][0] / cosPitch;
    }
    else
    {
        sinRoll = -m_cells[1][2];
        cosRoll = m_cells[1][1];
        sinYaw = 0;
        cosYaw = 1;
    }

    double yaw = atan2(sinYaw, cosYaw);
    double pitch = atan2(sinPitch, cosPitch);
    double roll = atan2(sinRoll, cosRoll);

    return hkCore::Vector3F((float)yaw, (float)pitch, (float)roll);
}

void hkCore::Matrix4x4::SetTranslation(const hkCore::Vector3F& vec)
{
    SetTranslation(vec.x, vec.y, vec.z);
}

void hkCore::Matrix4x4::SetScaling(const hkCore::Vector3F& vec)
{
    SetScaling(vec.x, vec.y, vec.z);
}

void hkCore::Matrix4x4::SetRotation(const hkCore::Vector3F& vec)
{
    SetRotation(vec.x, vec.y, vec.z);
}

void hkCore::Matrix4x4::Move(const hkCore::Vector3F& vec)
{
    Move(vec.x, vec.y, vec.z);
}

void hkCore::Matrix4x4::Scale(const hkCore::Vector3F& vec)
{
    Scale(vec.x, vec.y, vec.z);
}

void hkCore::Matrix4x4::Rotate(const hkCore::Vector3F& vec)
{
    Rotate(vec.x, vec.y, vec.z);
}

//==============================================================================
#pragma endregion // Matrix4x4
//==============================================================================