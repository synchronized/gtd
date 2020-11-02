#ifndef _VECTOR2D_H
#define _VECTOR2D_H

struct Vector2D
{
    double x;
    double y;
    Vector2D():x(0.0),y(0.0){}
    Vector2D(double a, double b):x(a),y(b){}

    //设置x,y为0
    inline void Zero();
    //如果x,y都为0返回TRUE
    inline bool isZero() const;
    //返回矢量的长度
    inline double Length() const;

    //返回矢量的长度的平方
    inline double LengthSq() const;
    inline void Normalize();
    //返回v2的点积
    inline double Dot(const Vector2D &v2) const;
    //如果v2在this矢量顺时针方向返回正值
    //如果在逆时针方向返回负值(假设Y轴箭头向下,X轴像右,类似窗口应用)
    inline int Sign(const Vector2D& v2) const;
    //返回与this矢量正交的矢量
    inline Vector2D Perp() const;
    //调整x,y使矢量长度不会超过最大值
    inline void Truncate(double max);
    //返回this与矢量v2的距离
    inline double Distance(const Vector2D& v2) const;
    //距离的平方
    inline double DistanceSq(const Vector2D& v2) const;
    //返回与this矢量相反的矢量
    inline Vector2D GetReverse() const;
    //操作
    const Vector2D& operator+=(const Vector2D &rhs);
    const Vector2D& operator-=(const Vector2D &rhs);
    const Vector2D& operator*=(const double &rhs);
    const Vector2D& operator/=(const double &rhs);
    bool operator==(const Vector2D &rhs)const;
    bool operator!=(const Vector2D &rhs)const;
};

#endif // _VECTOR2D_H
