/* HEADER FILE: SortImageSets.h */

#ifndef SORTIMAGESETS_H
#define SORTIMAGESETS_H
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include "ImageSets.h"

class SortImageSets
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    std::string field;
    std::vector <ImageSets> imagesets;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    SortImageSets(std::vector <ImageSets> &, std::string);
    static bool cmp_by_application_id(ImageSets &, ImageSets &);
    static bool cmp_by_created_at(ImageSets &, ImageSets &);
    static bool cmp_by_description(ImageSets &, ImageSets &);
    static bool cmp_by_details(ImageSets &, ImageSets &);
    static bool cmp_by_height(ImageSets &, ImageSets &);
    static bool cmp_by_horizontal_resolution(ImageSets &, ImageSets &);
    static bool cmp_by_id(ImageSets &, ImageSets &);
    static bool cmp_by_maximum_latitude(ImageSets &, ImageSets &);
    static bool cmp_by_maximum_longitude(ImageSets &, ImageSets &);
    static bool cmp_by_minimum_latitude(ImageSets &, ImageSets &);
    static bool cmp_by_minimum_longitude(ImageSets &, ImageSets &);
    static bool cmp_by_name(ImageSets &, ImageSets &);
    static bool cmp_by_physical_height(ImageSets &, ImageSets &);
    static bool cmp_by_physical_width(ImageSets &, ImageSets &);
    static bool cmp_by_pixel_resolution(ImageSets &, ImageSets &);
    static bool cmp_by_priority(ImageSets &, ImageSets &);
    static bool cmp_by_sun_angle(ImageSets &, ImageSets &);
    static bool cmp_by_updated_at(ImageSets &, ImageSets &);
    static bool cmp_by_upper_left_latitude(ImageSets &, ImageSets &);
    static bool cmp_by_upper_left_longitude(ImageSets &, ImageSets &);
    static bool cmp_by_vertical_resolution(ImageSets &, ImageSets &);
    static bool cmp_by_width(ImageSets &, ImageSets &);
    static bool cmp_by_x_high(ImageSets &, ImageSets &);
    static bool cmp_by_x_low(ImageSets &, ImageSets &);
    static bool cmp_by_x_origin(ImageSets &, ImageSets &);
    static bool cmp_by_y_high(ImageSets &, ImageSets &);
    static bool cmp_by_y_low(ImageSets &, ImageSets &);
    static bool cmp_by_y_origin(ImageSets &, ImageSets &);
    int GetFieldValue();
    std::vector <ImageSets> GetImageSets();
    void arrange();
};

#endif
