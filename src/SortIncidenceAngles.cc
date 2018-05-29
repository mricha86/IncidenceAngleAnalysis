#include "SortIncidenceAngles.h"

using namespace std;

SortIncidenceAngles::SortIncidenceAngles(vector <IncidenceAngles> &INCIDENCEANGLES, string FIELD)
{
  field = FIELD;
  incidenceangles = INCIDENCEANGLES;
}

bool SortIncidenceAngles::cmp_by_incidence_angle(IncidenceAngles &a, IncidenceAngles &b)
{
  return (a.GetIncidence_angle() < b.GetIncidence_angle());
}

bool SortIncidenceAngles::cmp_by_name(IncidenceAngles &a, IncidenceAngles &b)
{
  return (a.GetName() < b.GetName());
}

int SortIncidenceAngles::GetFieldValue()
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("name") == 0)
  {
    return 1;
  }
  if(field.compare("incidence_angle") == 0)
  {
    return 2;
  }

  return 0;
}

vector <IncidenceAngles> SortIncidenceAngles::GetIncidenceangles()
{
  return incidenceangles;
}

void SortIncidenceAngles::arrange()
{
  /***************************************************/
  /* Declaration/Initilization of function variables */
  /***************************************************/
  int fieldvalue;

  /***************************/
  /* Get field column number */
  /***************************/
  fieldvalue = GetFieldValue();
  
  /**********************************************/
  /* Determine which field to sort on then sort */
  /**********************************************/
  switch(fieldvalue)
  {
    case 1:
    {
      sort(incidenceangles.begin(), incidenceangles.end(), cmp_by_name);
      break;
    }
    case 2:
    {
      sort(incidenceangles.begin(), incidenceangles.end(), cmp_by_incidence_angle);
      break;
    }
    default:
    {
      printf("Invalid field value %d.\n", fieldvalue);
      printf("Terminating program ...\n");
      exit(EXIT_FAILURE);
    }
  }
  
  return;
}
