/* HEADER FILE: SearchIncidenceAngles.h */

#ifndef SEARCHINCIDENCEANGLES_H
#define SEARCHINCIDENCEANGLES_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "IncidenceAngles.h"

class SearchIncidenceAngles
{
  /************************************/
  /* Declaration of class functions */
  /************************************/
  public:
    static bool EqualityComparison(std::vector <IncidenceAngles> &, int, std::string, void *);
    static bool GreaterThanComparison(std::vector <IncidenceAngles> &, int, std::string, void *);
    static bool LessThanComparison(std::vector <IncidenceAngles> &, int, std::string, void *);
    static double Difference(std::vector <IncidenceAngles> &, int, std::string, void *);
    static int BinarySearch(std::vector <IncidenceAngles> &, int, int, std::string, void *);
    static int FirstNearestValue(std::vector <IncidenceAngles> &, int, int, std::string, void *);
    static int FirstOccurence(std::vector <IncidenceAngles> &, int, int, std::string, void *);
    static int LastNearestValue(std::vector <IncidenceAngles> &, int, int, std::string, void *);
    static int LastOccurence(std::vector <IncidenceAngles> &, int, int, std::string, void *);
};

#endif
