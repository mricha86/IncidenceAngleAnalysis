/* HEADER FILE: Circle.h */

#ifndef CIRCLE_H
#define CIRCLE_H
#include <math.h>
#include <stdio.h>

class Circle
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    double area;
    double circumference;
    long int centerx;
    long int centery;
    long int radius;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    Circle(long int, long int, long int);
    double GetArea();
    double GetCircumference();
    long int GetCenterx();
    long int GetCentery();
    long int GetRadius();
    void Display();
};

#endif
