/* HEADER FILE: SearchImageSets.h */

#ifndef SEARCHIMAGESETS_H
#define SEARCHIMAGESETS_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "ImageSets.h"

class SearchImageSets
{
  /************************************/
  /* Declaration of class functions */
  /************************************/
  public:
    static bool EqualityComparison(std::vector <ImageSets> &, int, std::string, void *);
    static bool GreaterThanComparison(std::vector <ImageSets> &, int, std::string, void *);
    static bool LessThanComparison(std::vector <ImageSets> &, int, std::string, void *);
    static double Difference(std::vector <ImageSets> &, int, std::string, void *);
    static int BinarySearch(std::vector <ImageSets> &, int, int, std::string, void *);
    static int FirstNearestValue(std::vector <ImageSets> &, int, int, std::string, void *);
    static int FirstOccurence(std::vector <ImageSets> &, int, int, std::string, void *);
    static int LastNearestValue(std::vector <ImageSets> &, int, int, std::string, void *);
    static int LastOccurence(std::vector <ImageSets> &, int, int, std::string, void *);
};

#endif
