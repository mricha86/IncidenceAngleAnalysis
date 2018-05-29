/* HEADER FILE: SearchImages.h */

#ifndef SEARCHIMAGES_H
#define SEARCHIMAGES_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Images.h"

class SearchImages
{
  /************************************/
  /* Declaration of class functions */
  /************************************/
  public:
    static bool EqualityComparison(std::vector <Images> &, int, std::string, void *);
    static bool GreaterThanComparison(std::vector <Images> &, int, std::string, void *);
    static bool LessThanComparison(std::vector <Images> &, int, std::string, void *);
    static double Difference(std::vector <Images> &, int, std::string, void *);
    static int BinarySearch(std::vector <Images> &, int, int, std::string, void *);
    static int FirstNearestValue(std::vector <Images> &, int, int, std::string, void *);
    static int FirstOccurence(std::vector <Images> &, int, int, std::string, void *);
    static int LastNearestValue(std::vector <Images> &, int, int, std::string, void *);
    static int LastOccurence(std::vector <Images> &, int, int, std::string, void *);
};

#endif
