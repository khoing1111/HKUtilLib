#pragma once

#include <string>

#include "Core.h"

namespace hkCore
{
    ///////////////////
    // CLASS: String
    class String
    {
    public:
        String();
        String(const String& clone);
        String(std::string& src);
        String(const char* src);
        String(char* src);
        ~String();

        // Set operator
        void operator=(String& other);
        void operator=(std::string& str);

        // Get source
        std::string GetStdString();

        //----------------------------------------------------------------------------------------
        // OPERATOR
        String operator+(String& other);
        String operator+(std::string& src);
        String operator+(char* str);
        String operator+(const char* str);
        String operator+(int num);
        String operator+(float num);
        String operator+(unsigned int num);
        String operator+(long num);
        String operator+(double num);
        String operator+(bool boolean);
        String operator+(char chr);

        //----------------------------------------------------------------------------------------
        // OPERATOR +=
        void operator+=(String& other);
        void operator+=(std::string& src);
        void operator+=(char* str);
        void operator+=(const char* str);
        void operator+=(int num);
        void operator+=(float num);
        void operator+=(unsigned int num);
        void operator+=(long num);
        void operator+=(double num);
        void operator+=(bool boolean);
        void operator+=(char chr);

        //----------------------------------------------------------------------------------------
        // Compare OPERATION
        bool operator==(String& other);
        bool operator==(std::string& src);
        bool operator==(const String& other) const;
        bool operator==(const std::string& src) const;
        bool operator!=(String& other);
        bool operator!=(std::string& src);
        bool operator!=(const String& other) const;
        bool operator!=(const std::string& src) const;
        int Compare(String& other);
        int Compare(std::string& src);
        int Compare(const String& other) const;
        int Compare(const std::string& src) const;

        std::string ToStdStr();
        std::string ToStdStr() const;

    private:
        std::string m_src;
    };
}

////////////////
// PREDEFINED
#define hkString hkCore::String