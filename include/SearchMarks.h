/* HEADER FILE: SearchMarks.h */

#ifndef SEARCHMARKS_H
#define SEARCHMARKS_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Marks.h"

class SearchMarks
{
  /************************************/
  /* Declaration of class functions */
  /************************************/
  public:
    static bool EqualityComparison(std::vector <Marks> &, int, std::string, void *);
    static bool GreaterThanComparison(std::vector <Marks> &, int, std::string, void *);
    static bool LessThanComparison(std::vector <Marks> &, int, std::string, void *);
    static double Difference(std::vector <Marks> &, int, std::string, void *);
    static int BinarySearch(std::vector <Marks> &, int, int, std::string, void *);
    static int FirstNearestValue(std::vector <Marks> &, int, int, std::string, void *);
    static int FirstOccurence(std::vector <Marks> &, int, int, std::string, void *);
    static int LastNearestValue(std::vector <Marks> &, int, int, std::string, void *);
    static int LastOccurence(std::vector <Marks> &, int, int, std::string, void *);
};

#endif
