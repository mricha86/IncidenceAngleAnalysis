#include "EquirectangularProjection.h"

double EquirectangularProjection::CalculateLatitude(double y, double phi_1, double r)
{
  return (y/r)+phi_1*deg2rad;
}

double EquirectangularProjection::CalculateLongitude(double x, double phi_1, double lambda_0, double r)
{
  return (x/(r*cos(phi_1*deg2rad)))+lambda_0*deg2rad;
}

double EquirectangularProjection::CalculateX(double lambda, double lambda_0, double phi_1, double r)
{
  return r*(lambda-lambda_0)*(deg2rad)*cos(phi_1*deg2rad);
}

double EquirectangularProjection::CalculateY(double phi, double phi_1, double r)
{
  return r*(phi-phi_1)*deg2rad;
}
