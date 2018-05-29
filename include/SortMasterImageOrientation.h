/* HEADER FILE: SortMasterImageOrientation.h */

#ifndef SORTMASTERIMAGEORIENTATION_H
#define SORTMASTERIMAGEORIENTATION_H
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include "MasterImageOrientation.h"

class SortMasterImageOrientation
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    std::string field;
    std::vector <MasterImageOrientation> masterimageorientations;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    SortMasterImageOrientation(std::vector <MasterImageOrientation> &, std::string);
    static bool cmp_by_name(MasterImageOrientation &, MasterImageOrientation &);
    static bool cmp_by_upper_left_latitude(MasterImageOrientation &, MasterImageOrientation &);
    static bool cmp_by_upper_left_longitude(MasterImageOrientation &, MasterImageOrientation &);
    int GetFieldValue();
    std::vector <MasterImageOrientation> GetMasterImageOrientations();
    void arrange();
};

#endif
