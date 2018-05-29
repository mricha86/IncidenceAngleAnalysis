#include "Circle.h"

Circle::Circle(long int CENTERX, long int CENTERY, long int RADIUS)
{
  /*********************/
  /* Record parameters */
  /*********************/
  centerx = CENTERX;
  centery = CENTERY;
  radius = RADIUS;

  /*******************************************/
  /* Determine other attributes of rectangle */
  /*******************************************/
  area = M_PI*radius*radius;
  circumference = 2*M_PI*radius;
}

double Circle::GetArea()
{
  return area;
}

double Circle::GetCircumference()
{
  return circumference;
}

long int Circle::GetCenterx()
{
  return centerx;
}

long int Circle::GetCentery()
{
  return centery;
}

long int Circle::GetRadius()
{
  return radius;
}

void Circle::Display()
{
  /*********************************************/
  /* Print parameters and attributes to screen */
  /*********************************************/
  printf("Parameters:\n");
  printf("Center_X = %ld\n", centerx);
  printf("Center_Y = %ld\n", centery);
  printf("Radius = %ld\n", radius);
  printf("Attributes:\n");
  printf("Area = %lf\n", area);
  printf("Circumference = %lf\n", circumference);
}
