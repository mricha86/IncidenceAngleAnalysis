/* HEADER FILE: Images.h */

#ifndef IMAGES_H
#define IMAGES_H
#include <iostream>
#include <stdlib.h>
#include <string>

class Images
{
  /***********************************/
  /* Declaration of class variables */
  /***********************************/
  private:
    double horizontal_resolution;
    double physical_height;
    double physical_width;
    double pixel_resolution;
    double priority;
    double sun_angle;
    double vertical_resolution;
    double x_high;
    double x_low;
    double x_offset;
    double x_origin;
    double y_high;
    double y_low;
    double y_offset;
    double y_origin;
    int application_id;
    int done;
    int height;
    int id;
    int image_set_id;
    int premarked;
    int width;
    int x_relative;
    int y_relative;
    std::string created_at;
    std::string details;
    std::string file_location;
    std::string name;
    std::string updated_at;
    std::string upper_left_x;
    std::string upper_left_y;

  /************************************/
  /* Declaration of class functions */
  /************************************/
  public:
    Images(int, int, int, std::string, std::string, double, int, int, double, std::string, std::string, std::string);
    double GetHorizontal_resolution();
    double GetPhysical_height();
    double GetPhysical_width();
    double GetPixel_resolution();
    double GetPriority();
    double GetSun_angle();
    double GetVertical_resolution();
    double GetX_high();
    double GetX_low();
    double GetX_offset();
    double GetX_origin();
    double GetY_high();
    double GetY_low();
    double GetY_offset();
    double GetY_origin();
    int GetApplication_id();
    int GetDone();
    int GetHeight();
    int GetId();
    int GetImage_set_id();
    int GetPremarked();
    int GetWidth();
    int GetX_relative();
    int GetY_relative();
    std::string GetCreated_at();
    std::string GetDetails();
    std::string GetFile_location();
    std::string GetName();
    std::string GetUpdated_at();
    std::string GetUpper_left_x();
    std::string GetUpper_left_y();
    void AuxilaryFunction(std::string, std::string, double, double, double, double, double);
    void CalculatePhysical_height();
    void CalculatePhysical_width();
    void CalculateX_high();
    void CalculateX_low();
    void CalculateX_origin();
    void CalculateY_high();
    void CalculateY_low();
    void CalculateY_origin();
    void RetrieveHeight();
    void RetrieveWidth();
    void RetrieveX_relative();
    void RetrieveY_relative();
    void SetHorizontal_resolution(double);
    void SetPixel_resolution(double);
    void SetVertical_resolution(double);
    void SetUpper_left_x(std::string);
    void SetUpper_left_y(std::string);
    void SetX_offset(double);
    void SetY_offset(double);
    void * GetValue(std::string);
};

#endif
