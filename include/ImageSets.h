/* HEADER FILE: ImageSets.h */

#ifndef IMAGESETS_H
#define IMAGESETS_H
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include "EquirectangularProjection.h"

class ImageSets
{
  /***********************************/
  /* Declaration of class variables */
  /***********************************/
  private:
    double horizontal_resolution;
    double maximum_latitude;
    double maximum_longitude;
    double minimum_latitude;
    double minimum_longitude;
    double physical_height;
    double physical_width;
    double pixel_resolution;
    double priority;
    double sun_angle;
    double vertical_resolution;
    double x_high;
    double x_low;
    double x_origin;
    double y_high;
    double y_low;
    double y_origin;
    int application_id;
    int height;
    int id;
    int width;
    std::string created_at;
    std::string description;
    std::string details;
    std::string name;
    std::string updated_at;
    std::string upper_left_latitude;
    std::string upper_left_longitude;

  /************************************/
  /* Declaration of class functions */
  /************************************/
  public:
    ImageSets(int, std::string, int, double, double, double, double, double, double, double, std::string, std::string, std::string, std::string);
    double GetHorizontal_resolution();
    double GetMaximum_latitude();
    double GetMaximum_longitude();
    double GetMinimum_latitude();
    double GetMinimum_longitude();
    double GetPhysical_height();
    double GetPhysical_width();
    double GetPixel_resolution();
    double GetPriority();
    double GetSun_angle();
    double GetVertical_resolution();
    double GetX_high();
    double GetX_low();
    double GetX_origin();
    double GetY_high();
    double GetY_low();
    double GetY_origin();
    int GetApplication_id();
    int GetHeight();
    int GetId();
    int GetWidth();
    std::string GetCreated_at();
    std::string GetDescription();
    std::string GetDetails();
    std::string GetName();
    std::string GetUpdated_at();
    std::string GetUpper_left_latitude();
    std::string GetUpper_left_longitude();
    void AuxilaryFunction(std::string, std::string);
    void CalculateHorizontal_resolution();
    void CalculatePhysical_height();
    void CalculatePhysical_width();
    void CalculateVertical_resolution();
    void CalculateX_high();
    void CalculateX_low();
    void CalculateX_origin();
    void CalculateY_high();
    void CalculateY_low();
    void CalculateY_origin();
    void RetrieveHeight();
    void RetrieveWidth();
    void SetHorizontal_resolution(double);
    void SetUpper_left_latitude(std::string);
    void SetUpper_left_longitude(std::string);
    void SetVertical_resolution(double);
};

#endif
