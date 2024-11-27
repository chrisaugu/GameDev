#ifndef SHAPE_H
#define SHAPE_H


class Shape
{
    public:
        Shape();
        virtual ~Shape();

        double calcCircumference();
        double calcArea();

    private:
        double length;
        double width;
        double radius;

    protected:

};

#endif // SHAPE_H
