/* HEADER FILE: SortIncidenceAngles.h */

#ifndef SORTINCIDENCEANGLES_H
#define SORTINCIDENCEANGLES_H
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include "IncidenceAngles.h"

class SortIncidenceAngles
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    std::string field;
    std::vector <IncidenceAngles> incidenceangles;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    SortIncidenceAngles(std::vector <IncidenceAngles> &, std::string);
    static bool cmp_by_incidence_angle(IncidenceAngles &, IncidenceAngles &);
    static bool cmp_by_name(IncidenceAngles &, IncidenceAngles &);
    int GetFieldValue();
    std::vector <IncidenceAngles> GetIncidenceangles();
    void arrange();
};

#endif
