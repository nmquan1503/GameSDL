#ifndef _Vector2D_h_
#define _Vector2D_h_

#include<math.h>

class Vector2D
{
private:
    float p_x;
    float p_y;
public:
    Vector2D(float x,float y):p_x(x),p_y(y){}
    float GetX(){return p_x;}
    float GetY(){return p_y;}
    void SetX(float x){p_x=x;}
    void SetY(float y){p_y=y;}

    float length(){return sqrt(p_x*p_x+p_y*p_y);}
    Vector2D operator+(const Vector2D& v2) const;
    Vector2D& operator+=(const Vector2D& v2);
    Vector2D operator-(const Vector2D& v2)const;
    Vector2D& operator-=(const Vector2D& v2);
    Vector2D operator*(float n);
    Vector2D operator*=(float n);
    Vector2D operator/(float n);
    Vector2D operator/=(float n);
    void normal();
};

#endif // _Vector2D_h_
