/* HEADER FILE: Rectangle.h */

#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <math.h>
#include <stdio.h>

class Rectangle
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    double area;
    double height;
    double perimeter;
    double width;
    double x_high;
    double x_low;
    double y_high;
    double y_low;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    Rectangle(double, double, double, double);
    double GetArea();
    double GetHeight();
    double GetPerimeter();
    double GetWidth();
    double GetX_high();
    double GetX_low();
    double GetY_high();
    double GetY_low();
    void AuxilaryFunction();
    void CalculateArea();
    void CalculateHeight();
    void CalculatePerimeter();
    void CalculateWidth();
    void Display();
};

#endif
