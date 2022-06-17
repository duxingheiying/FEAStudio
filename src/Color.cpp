#include "Color.h"

Color::Color(const float& rend_, const float& green_, const float& blue_, const float& alpha_ )
{
    m_fRed = rend_;
    m_fGreen = green_;
    m_fBlue = blue_;
    m_fAlpha = alpha_;
}

Color::~Color()
{
}
