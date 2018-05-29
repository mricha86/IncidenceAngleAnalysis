/* HEADER FILE: SortPixelResolution.h */

#ifndef SORTPIXELRESOLUTION_H
#define SORTPIXELRESOLUTION_H
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include "PixelResolution.h"

class SortPixelResolutions
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    std::string field;
    std::vector <PixelResolution> pixelresolutions;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    SortPixelResolutions(std::vector <PixelResolution> &, std::string);
    static bool cmp_by_horizontal_resolution(PixelResolution &, PixelResolution &);
    static bool cmp_by_name(PixelResolution &, PixelResolution &);
    static bool cmp_by_vertical_resolution(PixelResolution &, PixelResolution &);
    int GetFieldValue();
    std::vector <PixelResolution> GetPixelResolutions();
    void arrange();
};

#endif
