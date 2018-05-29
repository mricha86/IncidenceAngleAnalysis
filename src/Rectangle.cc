#include "Rectangle.h"

Rectangle::Rectangle(double XLOW, double XHIGH, double YLOW, double YHIGH)
{
  /***********************/
  /* Retrieve parameters */
  /***********************/
  x_high = XHIGH;
  x_low = XLOW;
  y_high = YHIGH;
  y_low = YLOW;

  /*****************************/
  /* Execute auxilary function */
  /*****************************/
  AuxilaryFunction();
}

double Rectangle::GetArea()
{
  return area;
}

double Rectangle::GetHeight()
{
  return height;
}

double Rectangle::GetPerimeter()
{
  return perimeter;
}

double Rectangle::GetWidth()
{
  return width;
}

double Rectangle::GetX_high()
{
  return x_high;
}

double Rectangle::GetX_low()
{
  return x_low;
}

double Rectangle::GetY_high()
{
  return y_high;
}

double Rectangle::GetY_low()
{
  return y_low;
}

void Rectangle::AuxilaryFunction()
{
  /**************************************************/
  /* Step 1: Calculate rectangle's width and height */
  /**************************************************/
  CalculateWidth();
  CalculateHeight();

  /****************************************************/
  /* Step 2: Calculate rectangle's perimeter and area */
  /****************************************************/
  CalculatePerimeter();
  CalculateArea();
}

void Rectangle::CalculateArea()
{
  area = width*height;
}

void Rectangle::CalculateHeight()
{
  height = y_high-y_low;
}

void Rectangle::CalculatePerimeter()
{
  perimeter = 2.0*(width+height);
}

void Rectangle::CalculateWidth()
{
  width = x_high-x_low;
}

void Rectangle::Display()
{
  /*********************************************/
  /* Print parameters and attributes to screen */
  /*********************************************/
  printf("Parameters:\n");
  printf("XLow = %lf\n", x_low);
  printf("XHigh = %lf\n", x_high);
  printf("YLow = %lf\n", y_low);
  printf("YHigh = %lf\n", y_high);
  printf("Attributes:\n");
  printf("Area = %lf\n", area);
  printf("Height => (Y = %lf)\n", height);
  printf("Perimeter => (X = %lf)\n", perimeter);
  printf("Width = %lf\n", width);
}
