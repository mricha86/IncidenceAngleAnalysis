/* HEADER FILE: EquirectangularProjection.h */

#ifndef EQUIRECTANGULARPROJECTION_H
#define EQUIRECTANGULARPROJECTION_H
#include <math.h>

class EquirectangularProjection
{
  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    static double CalculateLatitude(double, double, double);
    static double CalculateLongitude(double, double, double, double);
    static double CalculateX(double, double, double, double);
    static double CalculateY(double, double, double);
};

#endif
