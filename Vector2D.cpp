
#include "Vector2D.h"

Vector2D Vector2D:: operator+(const Vector2D& v2)const
{
    return Vector2D(p_x+v2.p_x,p_y+v2.p_y);
}

Vector2D& Vector2D:: operator+=(const Vector2D& v2)
{
    p_x+=v2.p_x;
    p_y+=v2.p_y;
    return *this;
}

Vector2D Vector2D:: operator-(const Vector2D& v2)const
{
    return Vector2D(p_x-v2.p_x,p_y-v2.p_y);
}

Vector2D& Vector2D:: operator-=(const Vector2D& v2)
{
    p_x-=v2.p_x;
    p_y-=v2.p_y;
    return *this;
}

Vector2D Vector2D:: operator*(float n)
{
    return Vector2D(p_x*n,p_y*n);
}

Vector2D Vector2D:: operator*=(float n)
{
    p_x*=n;
    p_y*=n;
    return *this;
}

Vector2D Vector2D:: operator/(float n)
{
    return Vector2D(p_x/n,p_y/n);
}

Vector2D Vector2D:: operator/=(float n)
{
    p_x/=n;
    p_y/=n;
    return *this;
}

void Vector2D:: normal()
{
    float l=length();
    if(l>1)
    {
        (*this)/=l;
    }
}
