/* HEADER FILE: OverlappedImages.h */

#ifndef OVERLAPPEDIMAGES_H
#define OVERLAPPEDIMAGES_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

class OverlappedImages
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    double image1_area;
    double image1_height;
    double image1_horizontal_resolution;
    double image1_incidence_angle;
    double image1_vertical_resolution;
    double image1_width;
    double image1_x_high;
    double image1_x_low;
    double image1_y_high;
    double image1_y_low;
    double image2_area;
    double image2_height;
    double image2_horizontal_resolution;
    double image2_incidence_angle;
    double image2_vertical_resolution;
    double image2_width;
    double image2_x_high;
    double image2_x_low;
    double image2_y_high;
    double image2_y_low;
    double overlap_area;
    double overlap_height;
    double overlap_width;
    double overlap_x_high;
    double overlap_x_low;
    double overlap_y_high;
    double overlap_y_low;
    int id;
    int image1_id;
    int image2_id;
    std::string image1_name;
    std::string image1_x_origin_condition;
    std::string image1_y_origin_condition;
    std::string image2_name;
    std::string image2_x_origin_condition;
    std::string image2_y_origin_condition;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    OverlappedImages(int, int, std::string, std::string, std::string, double, double, double, double, double, double, double, int, std::string, std::string, std::string, double, double, double, double, double, double, double, double, double, double, double);
    double GetImage1_area();
    double GetImage1_height();
    double GetImage1_horizontal_resolution();
    double GetImage1_incidence_angle();
    double GetImage1_vertical_resolution();
    double GetImage1_width();
    double GetImage1_x_high();
    double GetImage1_x_low();
    double GetImage1_y_high();
    double GetImage1_y_low();
    double GetImage2_area();
    double GetImage2_height();
    double GetImage2_horizontal_resolution();
    double GetImage2_incidence_angle();
    double GetImage2_vertical_resolution();
    double GetImage2_width();
    double GetImage2_x_high();
    double GetImage2_x_low();
    double GetImage2_y_high();
    double GetImage2_y_low();
    double GetOverlap_area();
    double GetOverlap_height();
    double GetOverlap_width();
    double GetOverlap_x_high();
    double GetOverlap_x_low();
    double GetOverlap_y_high();
    double GetOverlap_y_low();
    int GetId();
    int GetImage1_id();
    int GetImage2_id();
    std::string GetImage1_name();
    std::string GetImage1_x_origin_condition();
    std::string GetImage1_y_origin_condition();
    std::string GetImage2_name();
    std::string GetImage2_x_origin_condition();
    std::string GetImage2_y_origin_condition();
    void AuxilaryFunction();
    void CalculateImage1Area();
    void CalculateImage1Height();
    void CalculateImage1Width();
    void CalculateImage2Area();
    void CalculateImage2Height();
    void CalculateImage2Width();
    void CalculateOverlapArea();
    void CalculateOverlapHeight();
    void CalculateOverlapWidth();
    static void Display(OverlappedImages);
    static void Display(std::vector <OverlappedImages> &);
};

#endif
