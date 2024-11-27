#ifndef VEC2F_H
#define VEC2F_H


class Vec2f
{
    public:
        Vec2f(const float _x = 0.0, const float _y = 0.0);
        virtual ~Vec2f();

        float x, y;

        Vec2f operator+(const Vec2f &a);
        Vec2f operator+=(const Vec2f &a);
        Vec2f operator-();
        Vec2f operator-(const Vec2f& a);
        Vec2f operator-=(const Vec2f& a);
        float squaredMag();
        float mag();
        float arg();

    protected:

    private:
};

#endif // VEC2F_H
