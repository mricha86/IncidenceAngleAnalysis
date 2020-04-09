/* HEADER FILE: IncidenceAngles.h */

#ifndef INCIDENCEANGLES_H
#define INCIDENCEANGLES_H
#include <string>
#include <vector>

#include "AuxilaryFunctions.h"

class IncidenceAngles
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    double incidence_angle;
    std::string name;

  /***********************************/
  /* Declaration of class functions */
  /***********************************/
  public:
    IncidenceAngles(std::string, double);
    double GetIncidence_angle();
    double GetValue_double(std::string);
    int GetValue_int(std::string);
    std::string GetName();
    std::string GetValue_string(std::string);
    void * GetValue(std::string);
};

#endif
