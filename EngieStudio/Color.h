#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
    explicit Color(const float& rend_, const float& green_, const float& blue_, const float& alpha_ = 1.0f);
    ~Color();

public:
    float m_fRed;
    float m_fGreen;
    float m_fBlue;
    float m_fAlpha;

protected:

private:

public:

protected:

private:
};

#endif // COLOR_H
