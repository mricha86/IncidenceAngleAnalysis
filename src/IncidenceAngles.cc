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

double IncidenceAngles::GetValue_double(string field)
{
  switch(str2int(field.c_str())) {
  case str2int("incidence_angle"):
    return incidence_angle;
    break;
  }

  return 0;
}

int IncidenceAngles::GetValue_int(string field)
{
  return 0;
}

string IncidenceAngles::GetName()
{
  return name;
}

string IncidenceAngles::GetValue_string(string field)
{
  switch(str2int(field.c_str())) {
  case str2int("name"):
    return name;
    break;
  }

  return "";
}

void * IncidenceAngles::GetValue(string field)
{
  switch(str2int(field.c_str())) {
  case str2int("incidence_angle"):
    return &incidence_angle;
    break;
  case str2int("name"):
    return &name;
    break;
  }

  return NULL;
}
