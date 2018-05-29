/* HEADER FILE: SortOverlappedImages.h */

#ifndef SORTOVERLAPPEDIMAGES_H
#define SORTOVERLAPPEDIMAGES_H
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include "OverlappedImages.h"

class SortOverlappedImages
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    std::string field;
    std::vector <OverlappedImages> overlappedimages;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    SortOverlappedImages(std::vector <OverlappedImages> &, std::string);
    static bool cmp_by_id(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image1_area(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image1_height(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image1_horizontal_resolution(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image1_id(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image1_incidence_angle(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image1_name(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image1_vertical_resolution(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image1_width(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image1_x_high(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image1_x_low(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image1_y_high(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image1_y_low(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image2_area(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image2_height(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image2_horizontal_resolution(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image2_id(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image2_incidence_angle(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image2_name(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image2_vertical_resolution(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image2_width(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image2_x_high(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image2_x_low(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image2_y_high(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_image2_y_low(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_overlap_area(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_overlap_x_high(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_overlap_x_low(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_overlap_y_high(OverlappedImages &, OverlappedImages &);
    static bool cmp_by_overlap_y_low(OverlappedImages &, OverlappedImages &);
    int GetFieldValue();
    std::vector <OverlappedImages> GetOverlappedimages();
    void arrange();
};

#endif
