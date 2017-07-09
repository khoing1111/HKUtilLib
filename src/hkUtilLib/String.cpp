#include "String.h"

hkCore::String::String() {}

hkCore::String::String(const hkCore::String& clone)
{
    m_src = clone.m_src;
}

hkCore::String::String(std::string& src)
{
    m_src = src;
}

hkCore::String::String(const char* src)
{
    m_src = src;
}

hkCore::String::String(char* src)
{
    m_src = src;
}

hkCore::String::~String() 
{}

// Set operator
void hkCore::String::operator=(String& other)
{
    m_src = other.m_src;
}

void hkCore::String::operator=(std::string& str)
{
    m_src = str;
}

std::string hkCore::String::GetStdString()
{
    return m_src;
}

//----------------------------------------------------------------------------------------
// OPERATOR
hkCore::String hkCore::String::operator+(hkCore::String& other)
{
    return hkCore::String(m_src + other.m_src);
}

hkCore::String hkCore::String::operator+(std::string& src)
{
    return hkCore::String(m_src + src);
}

hkCore::String hkCore::String::operator+(char* str)
{
    return *this + std::string(str);
}

hkCore::String hkCore::String::operator+(const char* str)
{
    return *this + std::string(str);
}

hkCore::String hkCore::String::operator+(int num)
{
    return *this + std::to_string(num);
}

hkCore::String hkCore::String::operator+(float num)
{
    return *this + std::to_string(num);
}

hkCore::String hkCore::String::operator+(unsigned int num)
{
    return *this + std::to_string(num);
}

hkCore::String hkCore::String::operator+(long num)
{
    return *this + std::to_string(num);
}

hkCore::String hkCore::String::operator+(double num)
{
    return *this + std::to_string(num);
}

hkCore::String hkCore::String::operator+(bool boolean)
{
    return *this + std::to_string(boolean);
}

hkCore::String hkCore::String::operator+(char chr)
{
    return *this + std::to_string(chr);
}

//----------------------------------------------------------------------------------------
// OPERATOR +=
void hkCore::String::operator+=(hkCore::String& other)
{
    m_src += other.m_src;
}

void hkCore::String::operator+=(std::string& src)
{
    m_src += src;
}

void hkCore::String::operator+=(char* str)
{
    *this += std::string(str);
}

void hkCore::String::operator+=(const char* str)
{
    *this += std::string(str);
}

void hkCore::String::operator+=(int num)
{
    *this += (std::to_string(num));
}

void hkCore::String::operator+=(float num)
{
    *this += (std::to_string(num));
}

void hkCore::String::operator+=(unsigned int num)
{
    *this += (std::to_string(num));
}

void hkCore::String::operator+=(long num)
{
    *this += (std::to_string(num));
}

void hkCore::String::operator+=(double num)
{
    *this += (std::to_string(num));
}

void hkCore::String::operator+=(bool boolean)
{
    *this += (std::to_string(boolean));
}

void hkCore::String::operator+=(char chr)
{
    *this += (std::to_string(chr));
}

//----------------------------------------------------------------------------------------
// COMPARE OPERATION
bool hkCore::String::operator==(hkCore::String& other)
{
    return m_src.compare(other.m_src) == 0;
}

bool hkCore::String::operator==(std::string& src)
{
    return m_src.compare(src) == 0;
}

bool hkCore::String::operator==(const hkCore::String& other) const
{
    return m_src.compare(other.m_src) == 0;
}

bool hkCore::String::operator==(const std::string& src) const
{
    return m_src.compare(src) == 0;
}

bool hkCore::String::operator!=(hkCore::String& other)
{
    return m_src.compare(other.m_src) != 0;
}

bool hkCore::String::operator!=(std::string& src)
{
    return m_src.compare(src) != 0;
}

bool hkCore::String::operator!=(const hkCore::String& other) const
{
    return m_src.compare(other.m_src) != 0;
}

bool hkCore::String::operator!=(const std::string& src) const
{
    return m_src.compare(src) != 0;
}

int hkCore::String::Compare(hkCore::String& other)
{
    return m_src.compare(other.m_src);
}

int hkCore::String::Compare(std::string& src)
{
    return m_src.compare(src);
}

int hkCore::String::Compare(const hkCore::String& other) const
{
    return m_src.compare(other.m_src);
}

int hkCore::String::Compare(const std::string& src) const
{
    return m_src.compare(src);
}

std::string hkCore::String::ToStdStr()
{
    return m_src;
}

std::string hkCore::String::ToStdStr() const
{
    return m_src;
}