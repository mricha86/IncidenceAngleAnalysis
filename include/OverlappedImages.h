/* HEADER FILE: OverlappedImages.h */

#ifndef OVERLAPPEDIMAGES_H
#define OVERLAPPEDIMAGES_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "AuxilaryFunctions.h"
#include "Images.h"

class OverlappedImages
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    double image1_area;
    double image1_incidence_angle;
    double image1_lower_left_x;
    double image1_lower_left_y;
    double image1_lower_right_x;
    double image1_lower_right_y;
    double image1_upper_left_x;
    double image1_upper_left_y;
    double image1_upper_right_x;
    double image1_upper_right_y;
    double image2_area;
    double image2_incidence_angle;
    double image2_lower_left_x;
    double image2_lower_left_y;
    double image2_lower_right_x;
    double image2_lower_right_y;
    double image2_upper_left_x;
    double image2_upper_left_y;
    double image2_upper_right_x;
    double image2_upper_right_y;
    double overlap_area;
    double overlap_lower_left_x;
    double overlap_lower_left_y;
    double overlap_lower_right_x;
    double overlap_lower_right_y;
    double overlap_maximum_x;
    double overlap_maximum_y;
    double overlap_minimum_x;
    double overlap_minimum_y;
    double overlap_upper_right_x;
    double overlap_upper_right_y;
    double overlap_upper_left_x;
    double overlap_upper_left_y;
    int id;
    int image1_id;
    int image2_id;
    std::string image1_name;
    std::string image2_name;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    OverlappedImages();
    OverlappedImages(int, int, std::string, double, double, double, double, double, double, double, double, double, double, int, std::string, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
    double GetImage1_area();
    double GetImage1_incidence_angle();
    double GetImage1_lower_left_x();
    double GetImage1_lower_left_y();
    double GetImage1_lower_right_x();
    double GetImage1_lower_right_y();
    double GetImage1_upper_left_x();
    double GetImage1_upper_left_y();
    double GetImage1_upper_right_x();
    double GetImage1_upper_right_y();
    double GetImage2_area();
    double GetImage2_incidence_angle();
    double GetImage2_lower_left_x();
    double GetImage2_lower_left_y();
    double GetImage2_lower_right_x();
    double GetImage2_lower_right_y();
    double GetImage2_upper_left_x();
    double GetImage2_upper_left_y();
    double GetImage2_upper_right_x();
    double GetImage2_upper_right_y();
    double GetOverlap_area();
    double GetOverlap_lower_left_x();
    double GetOverlap_lower_left_y();
    double GetOverlap_lower_right_x();
    double GetOverlap_lower_right_y();
    double GetOverlap_maximum_x();
    double GetOverlap_maximum_y();
    double GetOverlap_minimum_x();
    double GetOverlap_minimum_y();
    double GetOverlap_upper_left_x();
    double GetOverlap_upper_left_y();
    double GetOverlap_upper_right_x();
    double GetOverlap_upper_right_y();
    double GetValue_double(std::string);
    int GetId();
    int GetImage1_id();
    int GetImage2_id();
    int GetValue_int(std::string);
    std::string GetImage1_name();
    std::string GetImage2_name();
    std::string GetValue_string(std::string);
    void * GetValue(std::string);
    void OverlapRectangularBoundingRegion();
    static void DisplayData(OverlappedImages);
    static void DisplayData(std::vector <OverlappedImages> &);
};

#endif
