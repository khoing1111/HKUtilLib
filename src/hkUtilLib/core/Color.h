#pragma once


#include "../Core.h"
#include "../dataManage/LinkedList.h"


namespace hkCore
{
    namespace Color
    {
        /////////////////////
        // CLASS: RGBColor
        struct RGBColor
        {
            ///////////////////
            // STATIC MEMBER
        public:
            static const RGBColor BLACK;
            static const RGBColor WHITE;
            static const RGBColor RED;
            static const RGBColor GREEN;
            static const RGBColor BLUE;
            static const RGBColor YELLOW;
            static const RGBColor GRAY;
            static const RGBColor PALE_BLACK;

        public:
            RGBColor();
            RGBColor(const RGBColor&);
            RGBColor(float, float, float);

            RGBColor operator+(const RGBColor&);
            RGBColor operator-(const RGBColor&);
            RGBColor operator*(float);
            RGBColor operator/(float);

            void operator=(const RGBColor&);
            void operator+=(const RGBColor&);
            void operator-=(const RGBColor&);
            void operator*=(float);
            void operator/=(float);

            bool operator==(const RGBColor&);
            bool operator!=(const RGBColor&);
            bool operator==(const RGBColor&) const;
            bool operator!=(const RGBColor&) const;

            bool operator>(const RGBColor&);
            bool operator<(const RGBColor&);
            bool operator>=(const RGBColor&);
            bool operator<=(const RGBColor&);

            uint ToNumber() const;

        protected:
            inline void RoundUp();
            inline float RoundUp(float);
            uint Convert(const float& value) const;

        public:
            float r;
            float g;
            float b;
        };


        //////////////////////----------------------------------------------------------------------
        // CLASS: RGBAColor
        struct RGBAColor : public RGBColor
        {
            ///////////////////
            // STATIC MEMBER
        public:
            static const RGBAColor BLACK;
            static const RGBAColor WHITE;
            static const RGBAColor RED;
            static const RGBAColor GREEN;
            static const RGBAColor BLUE;
            static const RGBAColor YELLOW;
            static const RGBAColor GRAY;
            static const RGBAColor PALE_BLACK;

        public:
            RGBAColor();
            RGBAColor(const RGBAColor&);
            RGBAColor(const RGBColor&);
            RGBAColor(float, float, float);
            RGBAColor(float, float, float, float);

            RGBAColor operator+(const RGBAColor);
            RGBAColor operator-(const RGBAColor);
            RGBAColor operator*(float);
            RGBAColor operator/(float);

            void operator=(const RGBAColor);
            void operator+=(const RGBAColor);
            void operator-=(const RGBAColor);
            void operator*=(float);
            void operator/=(float);

            bool operator==(const RGBAColor);
            bool operator!=(const RGBAColor);
            bool operator==(const RGBAColor) const;
            bool operator!=(const RGBAColor) const;

            bool operator>(const RGBAColor&);
            bool operator<(const RGBAColor&);
            bool operator>=(const RGBAColor&);
            bool operator<=(const RGBAColor&);

            uint ToNumber() const;

        protected:
            inline void RoundUp();

        public:
            float a;
        };
    }
}


////////////
// DEFINE
#define hkRGBColor hkCore::Color::RGBColor
#define hkRGBAColor hkCore::Color::RGBAColor