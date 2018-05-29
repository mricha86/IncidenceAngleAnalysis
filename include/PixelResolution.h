/* HEADER FILE: PixelResolution.h */

#ifndef PIXELRESOLUTION_H
#define PIXELRESOLUTION_H
#include <string>
#include <vector>

class PixelResolution
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    double horizontal_resolution;
    double vertical_resolution;
    std::string name;

  /***********************************/
  /* Declaration of class functions */
  /***********************************/
  public:
    PixelResolution(std::string, double, double);
    double GetHorizontal_resolution();
    double GetVertical_resolution();
    std::string GetName();
    void * GetValue(std::string);
};

#endif
