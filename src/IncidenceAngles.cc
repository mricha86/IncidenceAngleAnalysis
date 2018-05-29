#include "IncidenceAngles.h"

using namespace std;

IncidenceAngles::IncidenceAngles(string NAME, double INCIDENCE_ANGLE)
{
  incidence_angle = INCIDENCE_ANGLE;
  name = NAME;
}

double IncidenceAngles::GetIncidence_angle()
{
  return incidence_angle;
}

string IncidenceAngles::GetName()
{
  return name;
}

void * IncidenceAngles::GetValue(string field)
{
  if(field.compare("name") == 0)
  {
    return &name;
  }
  if(field.compare("incidence_angle") == 0)
  {
    return &incidence_angle;
  }

  return NULL;
}
