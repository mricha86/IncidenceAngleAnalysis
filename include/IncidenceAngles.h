/* HEADER FILE: IncidenceAngles.h */

#ifndef INCIDENCEANGLES_H
#define INCIDENCEANGLES_H
#include <string>
#include <vector>

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
    std::string GetName();
    void * GetValue(std::string);
};

#endif
