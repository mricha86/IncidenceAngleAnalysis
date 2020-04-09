/* HEADER FILE: SortData.h */

#ifndef SORTDATA_H
#define SORTDATA_H
#include <algorithm>
#include <boost/any.hpp>
#include <stdlib.h>
#include <type_traits>
#include <vector>
#include "Images.h"
#include "ImageSets.h"
#include "IncidenceAngles.h"
#include "Marks.h"
#include "OverlappedImages.h"

template <typename T>
class SortData
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    std::string field;
    std::vector <T> data;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    SortData(std::vector <T> &, std::string);
    static bool cmp_by_application_id(T &, T &);
    static bool cmp_by_confirmed(T &, T &);
    static bool cmp_by_created_at(T &, T &);
    static bool cmp_by_details(T &, T &);
    static bool cmp_by_diameter(T &, T &);
    static bool cmp_by_done(T &, T &);
    static bool cmp_by_file_location(T &, T &);
    static bool cmp_by_height(T &, T &);
    static bool cmp_by_id(T &, T &);
    static bool cmp_by_image_id(T &, T &);
    static bool cmp_by_image_set_id(T &, T &);
    static bool cmp_by_image1_area(T &, T &);
    static bool cmp_by_image1_id(T &, T &);
    static bool cmp_by_image1_incidence_angle(T &, T &);
    static bool cmp_by_image1_lower_left_x(T &, T &);
    static bool cmp_by_image1_lower_left_y(T &, T &);
    static bool cmp_by_image1_lower_right_x(T &, T &);
    static bool cmp_by_image1_lower_right_y(T &, T &);
    static bool cmp_by_image1_name(T &, T &);
    static bool cmp_by_image1_upper_left_x(T &, T &);
    static bool cmp_by_image1_upper_left_y(T &, T &);
    static bool cmp_by_image1_upper_right_x(T &, T &);
    static bool cmp_by_image1_upper_right_y(T &, T &);
    static bool cmp_by_image2_area(T &, T &);
    static bool cmp_by_image2_id(T &, T &);
    static bool cmp_by_image2_incidence_angle(T &, T &);
    static bool cmp_by_image2_lower_left_x(T &, T &);
    static bool cmp_by_image2_lower_left_y(T &, T &);
    static bool cmp_by_image2_lower_right_x(T &, T &);
    static bool cmp_by_image2_lower_right_y(T &, T &);
    static bool cmp_by_image2_name(T &, T &);
    static bool cmp_by_image2_upper_left_x(T &, T &);
    static bool cmp_by_image2_upper_left_y(T &, T &);
    static bool cmp_by_image2_upper_right_x(T &, T &);
    static bool cmp_by_image2_upper_right_y(T &, T &);
    static bool cmp_by_incidence_angle(T &, T &);
    static bool cmp_by_lower_left_latitude(T &, T &);
    static bool cmp_by_lower_left_longitude(T &, T &);
    static bool cmp_by_lower_left_x(T &, T &);
    static bool cmp_by_lower_left_y(T &, T &);
    static bool cmp_by_lower_right_latitude(T &, T &);
    static bool cmp_by_lower_right_longitude(T &, T &);
    static bool cmp_by_lower_right_x(T &, T &);    
    static bool cmp_by_lower_right_y(T &, T &);
    static bool cmp_by_machine_mark_id(T &, T &);
    static bool cmp_by_maximum_latitude(T &, T &);
    static bool cmp_by_maximum_longitude(T &, T &);
    static bool cmp_by_maximum_x(T &, T &);
    static bool cmp_by_maximum_y(T &, T &);
    static bool cmp_by_minimum_latitude(T &, T &);
    static bool cmp_by_minimum_longitude(T &, T &);
    static bool cmp_by_minimum_x(T &, T &);
    static bool cmp_by_minimum_y(T &, T &);
    static bool cmp_by_name(T &, T &);
    static bool cmp_by_overlap_area(T &, T &);
    static bool cmp_by_overlap_lower_left_x(T &, T &);
    static bool cmp_by_overlap_lower_left_y(T &, T &);
    static bool cmp_by_overlap_lower_right_x(T &, T &);
    static bool cmp_by_overlap_lower_right_y(T &, T &);
    static bool cmp_by_overlap_maximum_x(T &, T &);
    static bool cmp_by_overlap_maximum_y(T &, T &);
    static bool cmp_by_overlap_minimum_x(T &, T &);
    static bool cmp_by_overlap_minimum_y(T &, T &);
    static bool cmp_by_overlap_upper_left_x(T &, T &);
    static bool cmp_by_overlap_upper_left_y(T &, T &);
    static bool cmp_by_overlap_upper_right_x(T &, T &);
    static bool cmp_by_overlap_upper_right_y(T &, T &);
    static bool cmp_by_pixel_resolution(T &, T &);
    static bool cmp_by_premarked(T &, T &);
    static bool cmp_by_priority(T &, T &);
    static bool cmp_by_score(T &, T &);
    static bool cmp_by_shared_mark_id(T &, T &);
    static bool cmp_by_sub_type(T &, T &);
    static bool cmp_by_submit_time(T &, T &);
    static bool cmp_by_sun_angle(T &, T &);
    static bool cmp_by_type(T &, T &);
    static bool cmp_by_updated_at(T &, T &);
    static bool cmp_by_upper_left_corner_x_status(T &, T &);
    static bool cmp_by_upper_left_corner_y_status(T &, T &);
    static bool cmp_by_upper_left_latitude(T &, T &);
    static bool cmp_by_upper_left_longitude(T &, T &);
    static bool cmp_by_upper_left_x(T &, T &);
    static bool cmp_by_upper_left_y(T &, T &);
    static bool cmp_by_upper_right_latitude(T &, T &);
    static bool cmp_by_upper_right_longitude(T &, T &);
    static bool cmp_by_upper_right_x(T &, T &);
    static bool cmp_by_upper_right_y(T &, T &);
    static bool cmp_by_user_id(T &, T &);
    static bool cmp_by_width(T &, T &);
    static bool cmp_by_x(T &, T &);
    static bool cmp_by_x_relative(T &, T &);
    static bool cmp_by_y(T &, T &);
    static bool cmp_by_y_relative(T &, T &);
    int GetFieldValue();
    std::vector <T> GetData();
    void arrange();
};

template <typename T>
SortData<T>::SortData(std::vector <T> &DATA, std::string FIELD)
{
  field = FIELD;
  data = DATA;
}

template <typename T>
bool SortData<T>::cmp_by_application_id(T &a, T &b)
{
  return (a.GetValue_int("application_id") < b.GetValue_int("application_id"));
}

template <typename T>
bool SortData<T>::cmp_by_confirmed(T &a, T &b)
{
  return (a.GetValue_int("confirmed") < b.GetValue_int("confirmed"));
}

template <typename T>
bool SortData<T>::cmp_by_created_at(T &a, T &b)
{
  return (a.GetValue_string("created_at") < b.GetValue_string("created_at"));
}

template <typename T>
bool SortData<T>::cmp_by_details(T &a, T &b)
{
  return (a.GetValue_string("details") < b.GetValue_string("details"));
}

template <typename T>
bool SortData<T>::cmp_by_diameter(T &a, T &b)
{
  return (a.GetValue_double("diameter") < b.GetValue_double("diameter"));
}

template <typename T>
bool SortData<T>::cmp_by_done(T &a, T &b)
{
  return (a.GetValue_int("done") < b.GetValue_int("done"));
}

template <typename T>
bool SortData<T>::cmp_by_file_location(T &a, T &b)
{
  return (a.GetValue_string("file_location") < b.GetValue_string("file_location"));
}

template <typename T>
bool SortData<T>::cmp_by_height(T &a, T &b)
{
  return (a.GetValue_int("height") < b.GetValue_int("height"));
}

template <typename T>
bool SortData<T>::cmp_by_id(T &a, T &b)
{
  return (a.GetValue_int("id") < b.GetValue_int("id"));
}

template <typename T>
bool SortData<T>::cmp_by_image_id(T &a, T &b)
{
  return (a.GetValue_int("image_id") < b.GetValue_int("image_id"));
}

template <typename T>
bool SortData<T>::cmp_by_image_set_id(T &a, T &b)
{
  return (a.GetValue_int("image_set_id") < b.GetValue_int("image_set_id"));
}

template <typename T>
bool SortData<T>::cmp_by_image1_area(T &a, T &b)
{
  return (a.GetValue_double("image1_area") < b.GetValue_double("image1_area"));
}

template <typename T>
bool SortData<T>::cmp_by_image1_id(T &a, T &b)
{
  return (a.GetValue_int("image1_id") < b.GetValue_int("image1_id"));
}

template <typename T>
bool SortData<T>::cmp_by_image1_incidence_angle(T &a, T &b)
{
  return (a.GetValue_double("image1_incidence_angle") < b.GetValue_double("image1_incidence_angle"));
}

template <typename T>
bool SortData<T>::cmp_by_image1_lower_left_x(T &a, T &b)
{
  return (a.GetValue_double("image1_lower_left_x") < b.GetValue_double("image1_lower_left_x"));
}

template <typename T>
bool SortData<T>::cmp_by_image1_lower_left_y(T &a, T &b)
{
  return (a.GetValue_double("image1_lower_left_y") < b.GetValue_double("image1_lower_left_y"));
}

template <typename T>
bool SortData<T>::cmp_by_image1_lower_right_x(T &a, T &b)
{
  return (a.GetValue_double("image1_lower_right_x") < b.GetValue_double("image1_lower_right_x"));
}

template <typename T>
bool SortData<T>::cmp_by_image1_lower_right_y(T &a, T &b)
{
  return (a.GetValue_double("image1_lower_right_y") < b.GetValue_double("image1_lower_right_y"));
}

template <typename T>
bool SortData<T>::cmp_by_image1_name(T &a, T &b)
{
  return (a.GetValue_string("image1_name") < b.GetValue_string("image1_name"));
}

template <typename T>
bool SortData<T>::cmp_by_image1_upper_left_x(T &a, T &b)
{
  return (a.GetValue_double("image1_upper_left_x") < b.GetValue_double("image1_upper_left_x"));
}

template <typename T>
bool SortData<T>::cmp_by_image1_upper_left_y(T &a, T &b)
{
  return (a.GetValue_double("image1_upper_left_y") < b.GetValue_double("image1_upper_left_y"));
}

template <typename T>
bool SortData<T>::cmp_by_image1_upper_right_x(T &a, T &b)
{
  return (a.GetValue_double("image1_upper_right_x") < b.GetValue_double("image1_upper_right_x"));
}

template <typename T>
bool SortData<T>::cmp_by_image1_upper_right_y(T &a, T &b)
{
  return (a.GetValue_double("image1_upper_right_y") < b.GetValue_double("image1_upper_right_y"));
}

template <typename T>
bool SortData<T>::cmp_by_image2_area(T &a, T &b)
{
  return (a.GetValue_double("image2_area") < b.GetValue_double("image2_area"));
}

template <typename T>
bool SortData<T>::cmp_by_image2_id(T &a, T &b)
{
  return (a.GetValue_int("image2_id") < b.GetValue_int("image2_id"));
}

template <typename T>
bool SortData<T>::cmp_by_image2_incidence_angle(T &a, T &b)
{
  return (a.GetValue_double("image2_incidence_angle") < b.GetValue_double("image2_incidence_angle"));
}

template <typename T>
bool SortData<T>::cmp_by_image2_lower_left_x(T &a, T &b)
{
  return (a.GetValue_double("image2_lower_left_x") < b.GetValue_double("image2_lower_left_x"));
}

template <typename T>
bool SortData<T>::cmp_by_image2_lower_left_y(T &a, T &b)
{
  return (a.GetValue_double("image2_lower_left_y") < b.GetValue_double("image2_lower_left_y"));
}

template <typename T>
bool SortData<T>::cmp_by_image2_lower_right_x(T &a, T &b)
{
  return (a.GetValue_double("image2_lower_right_x") < b.GetValue_double("image2_lower_right_x"));
}

template <typename T>
bool SortData<T>::cmp_by_image2_lower_right_y(T &a, T &b)
{
  return (a.GetValue_double("image2_lower_right_y") < b.GetValue_double("image2_lower_right_y"));
}

template <typename T>
bool SortData<T>::cmp_by_image2_name(T &a, T &b)
{
  return (a.GetValue_string("image2_name") < b.GetValue_string("image2_name"));
}

template <typename T>
bool SortData<T>::cmp_by_image2_upper_left_x(T &a, T &b)
{
  return (a.GetValue_double("image2_upper_left_x") < b.GetValue_double("image2_upper_left_x"));
}

template <typename T>
bool SortData<T>::cmp_by_image2_upper_left_y(T &a, T &b)
{
  return (a.GetValue_double("image2_upper_left_y") < b.GetValue_double("image2_upper_left_y"));
}

template <typename T>
bool SortData<T>::cmp_by_image2_upper_right_x(T &a, T &b)
{
  return (a.GetValue_double("image2_upper_right_x") < b.GetValue_double("image2_upper_right_x"));
}

template <typename T>
bool SortData<T>::cmp_by_image2_upper_right_y(T &a, T &b)
{
  return (a.GetValue_double("image2_upper_right_y") < b.GetValue_double("image2_upper_right_y"));
}

template <typename T>
bool SortData<T>::cmp_by_incidence_angle(T &a, T &b)
{
  return (a.GetValue_double("incidence_angle") < b.GetValue_double("incidence_angle"));
}

template <typename T>
bool SortData<T>::cmp_by_lower_left_latitude(T &a, T &b)
{
  return (a.GetValue_double("lower_left_latitude") < b.GetValue_double("lower_left_latitude"));
}

template <typename T>
bool SortData<T>::cmp_by_lower_left_longitude(T &a, T &b)
{
  return (a.GetValue_double("lower_left_longitude") < b.GetValue_double("lower_left_longitude"));
}

template <typename T>
bool SortData<T>::cmp_by_lower_left_x(T &a, T &b)
{
  return (a.GetValue_double("lower_left_x") < b.GetValue_double("lower_left_x"));
}

template <typename T>
bool SortData<T>::cmp_by_lower_left_y(T &a, T &b)
{
  return (a.GetValue_double("lower_left_y") < b.GetValue_double("lower_left_y"));
}

template <typename T>
bool SortData<T>::cmp_by_lower_right_latitude(T &a, T &b)
{
  return (a.GetValue_double("lower_right_latitude") < b.GetValue_double("lower_right_latitude"));
}

template <typename T>
bool SortData<T>::cmp_by_lower_right_longitude(T &a, T &b)
{
  return (a.GetValue_double("lower_right_longitude") < b.GetValue_double("lower_right_longitude"));
}

template <typename T>
bool SortData<T>::cmp_by_lower_right_x(T &a, T &b)
{
  return (a.GetValue_double("lower_right_x") < b.GetValue_double("lower_right_x"));
}

template <typename T>
bool SortData<T>::cmp_by_lower_right_y(T &a, T &b)
{
  return (a.GetValue_double("lower_right_y") < b.GetValue_double("lower_right_y"));
}

template <typename T>
bool SortData<T>::cmp_by_machine_mark_id(T &a, T &b)
{
  return (a.GetValue_int("machine_mark_id") < b.GetValue_int("machine_mark_id"));
}

template <typename T>
bool SortData<T>::cmp_by_maximum_latitude(T &a, T &b)
{
  return (a.GetValue_double("maximum_latitude") < b.GetValue_double("maximum_latitude"));
}

template <typename T>
bool SortData<T>::cmp_by_maximum_longitude(T &a, T &b)
{
  return (a.GetValue_double("maximum_longitude") < b.GetValue_double("maximum_longitude"));
}

template <typename T>
bool SortData<T>::cmp_by_maximum_x(T &a, T &b)
{
  return (a.GetValue_double("maximum_x") < b.GetValue_double("maximum_x"));
}

template <typename T>
bool SortData<T>::cmp_by_maximum_y(T &a, T &b)
{
  return (a.GetValue_double("maximum_y") < b.GetValue_double("maximum_y"));
}

template <typename T>
bool SortData<T>::cmp_by_minimum_latitude(T &a, T &b)
{
  return (a.GetValue_double("minimum_latitude") < b.GetValue_double("minimum_latitude"));
}

template <typename T>
bool SortData<T>::cmp_by_minimum_longitude(T &a, T &b)
{
  return (a.GetValue_double("minimum_longitude") < b.GetValue_double("minimum_longitude"));
}

template <typename T>
bool SortData<T>::cmp_by_minimum_x(T &a, T &b)
{
  return (a.GetValue_double("minimum_x") < b.GetValue_double("minimum_x"));
}

template <typename T>
bool SortData<T>::cmp_by_minimum_y(T &a, T &b)
{
  return (a.GetValue_double("minimum_y") < b.GetValue_double("minimum_y"));
}

template <typename T>
bool SortData<T>::cmp_by_name(T &a, T &b)
{
  return (a.GetValue_string("name") < b.GetValue_string("name"));
}

template <typename T>
bool SortData<T>::cmp_by_overlap_area(T &a, T &b)
{
  return (a.GetValue_double("overlap_area") < b.GetValue_double("overlap_area"));
}

template <typename T>
bool SortData<T>::cmp_by_overlap_lower_left_x(T &a, T &b)
{
  return (a.GetValue_double("overlap_lower_left_x") < b.GetValue_double("overlap_lower_left_x"));
}

template <typename T>
bool SortData<T>::cmp_by_overlap_lower_left_y(T &a, T &b)
{
  return (a.GetValue_double("overlap_lower_left_y") < b.GetValue_double("overlap_lower_left_y"));
}

template <typename T>
bool SortData<T>::cmp_by_overlap_lower_right_x(T &a, T &b)
{
  return (a.GetValue_double("overlap_lower_right_x") < b.GetValue_double("overlap_lower_right_x"));
}

template <typename T>
bool SortData<T>::cmp_by_overlap_lower_right_y(T &a, T &b)
{
  return (a.GetValue_double("overlap_lower_right_y") < b.GetValue_double("overlap_lower_right_y"));
}

template <typename T>
bool SortData<T>::cmp_by_overlap_maximum_x(T &a, T &b)
{
  return (a.GetValue_double("overlap_maximum_x") < b.GetValue_double("overlap_maximum_x"));
}

template <typename T>
bool SortData<T>::cmp_by_overlap_maximum_y(T &a, T &b)
{
  return (a.GetValue_double("overlap_maximum_y") < b.GetValue_double("overlap_maximum_y"));
}

template <typename T>
bool SortData<T>::cmp_by_overlap_minimum_x(T &a, T &b)
{
  return (a.GetValue_double("overlap_minimum_x") < b.GetValue_double("overlap_minimum_x"));
}

template <typename T>
bool SortData<T>::cmp_by_overlap_minimum_y(T &a, T &b)
{
  return (a.GetValue_double("overlap_minimum_y") < b.GetValue_double("overlap_minimum_y"));
}

template <typename T>
bool SortData<T>::cmp_by_overlap_upper_left_x(T &a, T &b)
{
  return (a.GetValue_double("overlap_upper_left_x") < b.GetValue_double("overlap_upper_left_x"));
}

template <typename T>
bool SortData<T>::cmp_by_overlap_upper_left_y(T &a, T &b)
{
  return (a.GetValue_double("overlap_upper_left_y") < b.GetValue_double("overlap_upper_left_y"));
}

template <typename T>
bool SortData<T>::cmp_by_overlap_upper_right_x(T &a, T &b)
{
  return (a.GetValue_double("overlap_upper_right_x") < b.GetValue_double("overlap_upper_right_x"));
}

template <typename T>
bool SortData<T>::cmp_by_overlap_upper_right_y(T &a, T &b)
{
  return (a.GetValue_double("overlap_upper_right_y") < b.GetValue_double("overlap_upper_right_y"));
}

template <typename T>
bool SortData<T>::cmp_by_pixel_resolution(T &a, T &b)
{
  return (a.GetValue_double("pixel_resolution") < b.GetValue_double("pixel_resolution"));
}

template <typename T>
bool SortData<T>::cmp_by_premarked(T &a, T &b)
{
  return (a.GetValue_int("premarked") < b.GetValue_int("premarked"));
}

template <typename T>
bool SortData<T>::cmp_by_priority(T &a, T &b)
{
  return (a.GetValue_double("priority") < b.GetValue_double("priority"));
}

template <typename T>
bool SortData<T>::cmp_by_score(T &a, T &b)
{
  return (a.GetValue_double("score") < b.GetValue_double("score"));
}

template <typename T>
bool SortData<T>::cmp_by_shared_mark_id(T &a, T &b)
{
  return (a.GetValue_int("shared_mark_id") < b.GetValue_int("shared_mark_id"));
}

template <typename T>
bool SortData<T>::cmp_by_sub_type(T &a, T &b)
{
  return (a.GetValue_string("sub_type") < b.GetValue_string("sub_type"));
}

template <typename T>
bool SortData<T>::cmp_by_submit_time(T &a, T &b)
{
  return (a.GetValue_string("submit_time") < b.GetValue_string("submit_time"));
}

template <typename T>
bool SortData<T>::cmp_by_sun_angle(T &a, T &b)
{
  return (a.GetValue_double("sun_angle") < b.GetValue_double("sun_angle"));
}

template <typename T>
bool SortData<T>::cmp_by_type(T &a, T &b)
{
  return (a.GetValue_string("type") < b.GetValue_string("type"));
}

template <typename T>
bool SortData<T>::cmp_by_updated_at(T &a, T &b)
{
  return (a.GetValue_string("updated_at") < b.GetValue_string("updated_at"));
}

template <typename T>
bool SortData<T>::cmp_by_upper_left_corner_x_status(T &a, T &b)
{
  return (a.GetValue_string("upper_left_corner_x_status") < b.GetValue_string("upper_left_corner_x_status"));
}

template <typename T>
bool SortData<T>::cmp_by_upper_left_corner_y_status(T &a, T &b)
{
  return (a.GetValue_string("upper_left_corner_y_status") < b.GetValue_string("upper_left_corner_y_status"));
}

template <typename T>
bool SortData<T>::cmp_by_upper_left_latitude(T &a, T &b)
{
  return (a.GetValue_double("upper_left_latitude") < b.GetValue_double("upper_left_latitude"));
}

template <typename T>
bool SortData<T>::cmp_by_upper_left_longitude(T &a, T &b)
{
  return (a.GetValue_double("upper_left_longitude") < b.GetValue_double("upper_left_longitude"));
}

template <typename T>
bool SortData<T>::cmp_by_upper_left_x(T &a, T &b)
{
  return (a.GetValue_double("upper_left_x") < b.GetValue_double("upper_left_x"));
}

template <typename T>
bool SortData<T>::cmp_by_upper_left_y(T &a, T &b)
{
  return (a.GetValue_double("upper_left_y") < b.GetValue_double("upper_left_y"));
}

template <typename T>
bool SortData<T>::cmp_by_upper_right_latitude(T &a, T &b)
{
  return (a.GetValue_double("upper_right_latitude") < b.GetValue_double("upper_right_latitude"));
}

template <typename T>
bool SortData<T>::cmp_by_upper_right_longitude(T &a, T &b)
{
  return (a.GetValue_double("upper_right_longitude") < b.GetValue_double("upper_right_longitude"));
}

template <typename T>
bool SortData<T>::cmp_by_upper_right_x(T &a, T &b)
{
  return (a.GetValue_double("upper_right_x") < b.GetValue_double("upper_right_x"));
}

template <typename T>
bool SortData<T>::cmp_by_upper_right_y(T &a, T &b)
{
  return (a.GetValue_double("upper_right_y") < b.GetValue_double("upper_right_y"));
}

template <typename T>
bool SortData<T>::cmp_by_user_id(T &a, T &b)
{
  return (a.GetValue_int("user_id") < b.GetValue_int("user_id"));
}

template <typename T>
bool SortData<T>::cmp_by_width(T &a, T &b)
{
  return (a.GetValue_int("width") < b.GetValue_int("width"));
}

template <typename T>
bool SortData<T>::cmp_by_x(T &a, T &b)
{
  return (a.GetValue_double("x") < b.GetValue_double("x"));
}

template <typename T>
bool SortData<T>::cmp_by_x_relative(T &a, T &b)
{
  return (a.GetValue_int("x_relative") < b.GetValue_int("x_relative"));
}

template <typename T>
bool SortData<T>::cmp_by_y(T &a, T &b)
{
  return (a.GetValue_double("y") < b.GetValue_double("y"));
}

template <typename T>
bool SortData<T>::cmp_by_y_relative(T &a, T &b)
{
  return (a.GetValue_int("y_relative") < b.GetValue_int("y_relative"));
}

template <typename T>
int SortData<T>::GetFieldValue()
{
  /************************/
  /* Retrieve field value */
  /************************/
  if(field.compare("application_id") == 0)
  {
    return 1;
  }
  if(field.compare("confirmed") == 0)
  {
    return 2;
  }
  if(field.compare("created_at") == 0)
  {
    return 3;
  }
  if(field.compare("details") == 0)
  {
    return 4;
  }
  if(field.compare("diameter") == 0)
  {
    return 5;
  }
  if(field.compare("done") == 0)
  {
    return 6;
  }
  if(field.compare("file_location") == 0)
  {
    return 7;
  }
  if(field.compare("height") == 0)
  {
    return 8;
  }
  if(field.compare("id") == 0)
  {
    return 9;
  }
  if(field.compare("image_id") == 0)
  {
    return 10;
  }
  if(field.compare("image_set_id") == 0)
  {
    return 11;
  }
  if(field.compare("image1_area") == 0)
  {
    return 12;
  }
  if(field.compare("image1_id") == 0)
  {
    return 13;
  }
  if(field.compare("image1_incidence_angle") == 0)
  {
    return 14;
  }
  if(field.compare("image1_lower_left_x") == 0)
  {
    return 15;
  }
  if(field.compare("image1_lower_left_y") == 0)
  {
    return 16;
  }
  if(field.compare("image1_lower_right_x") == 0)
  {
    return 17;
  }
  if(field.compare("image1_lower_right_y") == 0)
  {
    return 18;
  }
  if(field.compare("image1_name") == 0)
  {
    return 19;
  }
  if(field.compare("image1_upper_left_x") == 0)
  {
    return 20;
  }
  if(field.compare("image1_upper_left_y") == 0)
  {
    return 21;
  }
  if(field.compare("image1_upper_right_x") == 0)
  {
    return 22;
  }
  if(field.compare("image1_upper_right_y") == 0)
  {
    return 23;
  }
  if(field.compare("image2_area") == 0)
  {
    return 24;
  }
  if(field.compare("image2_id") == 0)
  {
    return 25;
  }
  if(field.compare("image2_incidence_angle") == 0)
  {
    return 26;
  }
  if(field.compare("image2_lower_left_x") == 0)
  {
    return 27;
  }
  if(field.compare("image2_lower_left_y") == 0)
  {
    return 28;
  }
  if(field.compare("image2_lower_right_x") == 0)
  {
    return 29;
  }
  if(field.compare("image2_lower_right_y") == 0)
  {
    return 30;
  }
  if(field.compare("image2_name") == 0)
  {
    return 31;
  }
  if(field.compare("image2_upper_left_x") == 0)
  {
    return 32;
  }
  if(field.compare("image2_upper_left_y") == 0)
  {
    return 33;
  }
  if(field.compare("image2_upper_right_x") == 0)
  {
    return 34;
  }
  if(field.compare("image2_upper_right_y") == 0)
  {
    return 35;
  }
  if(field.compare("incidence_angle") == 0)
  {
    return 36;
  }
  if(field.compare("lower_left_latitude") == 0)
  {
    return 37;
  }
  if(field.compare("lower_left_longitude") == 0)
  {
    return 38;
  }
  if(field.compare("lower_left_x") == 0)
  {
    return 39;
  }
  if(field.compare("lower_left_y") == 0)
  {
    return 40;
  }
  if(field.compare("lower_right_latitude") == 0)
  {
    return 41;
  }
  if(field.compare("lower_right_longitude") == 0)
  {
    return 42;
  }
  if(field.compare("lower_right_x") == 0)
  {
    return 43;
  }
  if(field.compare("lower_right_y") == 0)
  {
    return 44;
  }
  if(field.compare("machine_mark_id") == 0)
  {
    return 45;
  }
  if(field.compare("maximum_latitude") == 0)
  {
    return 46;
  }
  if(field.compare("maximum_longitude") == 0)
  {
    return 47;
  }
  if(field.compare("maximum_x") == 0)
  {
    return 48;
  }
  if(field.compare("maximum_y") == 0)
  {
    return 49;
  }
  if(field.compare("minimum_latitude") == 0)
  {
    return 50;
  }
  if(field.compare("minimum_longitude") == 0)
  {
    return 51;
  }
  if(field.compare("minimum_x") == 0)
  {
    return 52;
  }
  if(field.compare("minimum_y") == 0)
  {
    return 53;
  }
  if(field.compare("name") == 0)
  {
    return 54;
  }
  if(field.compare("overlap_area") == 0)
  {
    return 55;
  }
  if(field.compare("overlap_lower_left_x") == 0)
  {
    return 56;
  }
  if(field.compare("overlap_lower_left_y") == 0)
  {
    return 57;
  }
  if(field.compare("overlap_lower_right_x") == 0)
  {
    return 58;
  }
  if(field.compare("overlap_lower_right_y") == 0)
  {
    return 59;
  }
  if(field.compare("overlap_maximum_x") == 0)
  {
    return 60;
  }
  if(field.compare("overlap_maximum_y") == 0)
  {
    return 61;
  }
  if(field.compare("overlap_minimum_x") == 0)
  {
    return 62;
  }
  if(field.compare("overlap_minimum_y") == 0)
  {
    return 63;
  }
  if(field.compare("overlap_upper_left_x") == 0)
  {
    return 64;
  }
  if(field.compare("overlap_upper_left_y") == 0)
  {
    return 65;
  }
  if(field.compare("overlap_upper_right_x") == 0)
  {
    return 66;
  }
  if(field.compare("overlap_upper_right_y") == 0)
  {
    return 67;
  }
  if(field.compare("pixel_resolution") == 0)
  {
    return 68;
  }
  if(field.compare("premarked") == 0)
  {
    return 69;
  }
  if(field.compare("priority") == 0)
  {
    return 70;
  }
  if(field.compare("score") == 0)
  {
    return 71;
  }
  if(field.compare("shared_mark_id") == 0)
  {
    return 72;
  }
  if(field.compare("sub_type") == 0)
  {
    return 73;
  }
  if(field.compare("submit_time") == 0)
  {
    return 74;
  }
  if(field.compare("sun_angle") == 0)
  {
    return 75;
  }
  if(field.compare("type") == 0)
  {
    return 76;
  }
  if(field.compare("updated_at") == 0)
  {
    return 77;
  }
  if(field.compare("upper_left_corner_x_status") == 0)
  {
    return 78;
  }
  if(field.compare("upper_left_corner_y_status") == 0)
  {
    return 79;
  }
  if(field.compare("upper_left_latitude") == 0)
  {
    return 80;
  }
  if(field.compare("upper_left_longitude") == 0)
  {
    return 81;
  }
  if(field.compare("upper_left_x") == 0)
  {
    return 82;
  }
  if(field.compare("upper_left_y") == 0)
  {
    return 83;
  }
  if(field.compare("upper_right_latitude") == 0)
  {
    return 84;
  }
  if(field.compare("upper_right_longitude") == 0)
  {
    return 85;
  }
  if(field.compare("upper_right_x") == 0)
  {
    return 86;
  }
  if(field.compare("upper_right_y") == 0)
  {
    return 87;
  }
  if(field.compare("user_id") == 0)
  {
    return 88;
  }
  if(field.compare("width") == 0)
  {
    return 89;
  }
  if(field.compare("x") == 0)
  {
    return 90;
  }
  if(field.compare("x_relative") == 0)
  {
    return 91;
  }
  if(field.compare("y") == 0)
  {
    return 92;
  }
  if(field.compare("y_relative") == 0)
  {
    return 93;
  }
  
  return 0;
}

template <typename T>
std::vector <T> SortData<T>::GetData()
{
  return data;
}

template <typename T>
void SortData<T>::arrange()
{
  /***************************************************/
  /* Declaration/Initilization of function variables */
  /***************************************************/
  int fieldvalue;

  /***************************/
  /* Get field column number */
  /***************************/
  fieldvalue = GetFieldValue();
  
  /**********************************************/
  /* Determine which field to sort on then sort */
  /**********************************************/
  switch(fieldvalue)
  {
    case 1:
    {
      sort(data.begin(), data.end(), cmp_by_application_id);
      break;
    }
    case 2:
    {
      sort(data.begin(), data.end(), cmp_by_confirmed);
      break;
    }
    case 3:
    {
      sort(data.begin(), data.end(), cmp_by_created_at);
      break;
    }
    case 4:
    {
      sort(data.begin(), data.end(), cmp_by_details);
      break;
    }
    case 5:
    {
      sort(data.begin(), data.end(), cmp_by_diameter);
      break;
    }
    case 6:
    {
      sort(data.begin(), data.end(), cmp_by_done);
      break;
    }
    case 7:
    {
      sort(data.begin(), data.end(), cmp_by_file_location);
      break;
    }
    case 8:
    {
      sort(data.begin(), data.end(), cmp_by_height);
      break;
    }
    case 9:
    {
      sort(data.begin(), data.end(), cmp_by_id);
      break;
    }
    case 10:
    {
      sort(data.begin(), data.end(), cmp_by_image_id);
      break;
    }
    case 11:
    {
      sort(data.begin(), data.end(), cmp_by_image_set_id);
      break;
    }
    case 12:
    {
      sort(data.begin(), data.end(), cmp_by_image1_area);
      break;
    }
    case 13:
    {
      sort(data.begin(), data.end(), cmp_by_image1_id);
      break;
    }
    case 14:
    {
      sort(data.begin(), data.end(), cmp_by_image1_incidence_angle);
      break;
    }
    case 15:
    {
      sort(data.begin(), data.end(), cmp_by_image1_lower_left_x);
      break;
    }
    case 16:
    {
      sort(data.begin(), data.end(), cmp_by_image1_lower_left_y);
      break;
    }
    case 17:
    {
      sort(data.begin(), data.end(), cmp_by_image1_lower_right_x);
      break;
    }
    case 18:
    {
      sort(data.begin(), data.end(), cmp_by_image1_lower_right_y);
      break;
    }
    case 19:
    {
      sort(data.begin(), data.end(), cmp_by_image1_name);
      break;
    }
    case 20:
    {
      sort(data.begin(), data.end(), cmp_by_image1_upper_left_x);
      break;
    }
    case 21:
    {
      sort(data.begin(), data.end(), cmp_by_image1_upper_left_y);
      break;
    }
    case 22:
    {
      sort(data.begin(), data.end(), cmp_by_image1_upper_right_x);
      break;
    }
    case 23:
    {
      sort(data.begin(), data.end(), cmp_by_image1_upper_right_y);
      break;
    }
    case 24:
    {
      sort(data.begin(), data.end(), cmp_by_image2_area);
      break;
    }
    case 25:
    {
      sort(data.begin(), data.end(), cmp_by_image2_id);
      break;
    }
    case 26:
    {
      sort(data.begin(), data.end(), cmp_by_image2_incidence_angle);
      break;
    }
    case 27:
    {
      sort(data.begin(), data.end(), cmp_by_image2_lower_left_x);
      break;
    }
    case 28:
    {
      sort(data.begin(), data.end(), cmp_by_image2_lower_left_y);
      break;
    }
    case 29:
    {
      sort(data.begin(), data.end(), cmp_by_image2_lower_right_x);
      break;
    }
    case 30:
    {
      sort(data.begin(), data.end(), cmp_by_image2_lower_right_y);
      break;
    }
    case 31:
    {
      sort(data.begin(), data.end(), cmp_by_image2_name);
      break;
    }
    case 32:
    {
      sort(data.begin(), data.end(), cmp_by_image2_upper_left_x);
      break;
    }
    case 33:
    {
      sort(data.begin(), data.end(), cmp_by_image2_upper_left_y);
      break;
    }
    case 34:
    {
      sort(data.begin(), data.end(), cmp_by_image2_upper_right_x);
      break;
    }
    case 35:
    {
      sort(data.begin(), data.end(), cmp_by_image2_upper_right_y);
      break;
    }
    case 36:
    {
      sort(data.begin(), data.end(), cmp_by_incidence_angle);
      break;
    }
    case 37:
    {
      sort(data.begin(), data.end(), cmp_by_lower_left_latitude);
      break;
    }
    case 38:
    {
      sort(data.begin(), data.end(), cmp_by_lower_left_longitude);
      break;
    }
    case 39:
    {
      sort(data.begin(), data.end(), cmp_by_lower_left_x);
      break;
    }
    case 40:
    {
      sort(data.begin(), data.end(), cmp_by_lower_left_y);
      break;
    }
    case 41:
    {
      sort(data.begin(), data.end(), cmp_by_lower_right_latitude);
      break;
    }
    case 42:
    {
      sort(data.begin(), data.end(), cmp_by_lower_right_longitude);
      break;
    }
    case 43:
    {
      sort(data.begin(), data.end(), cmp_by_lower_right_x);
      break;
    }
    case 44:
    {
      sort(data.begin(), data.end(), cmp_by_lower_right_y);
      break;
    }
    case 45:
    {
      sort(data.begin(), data.end(), cmp_by_machine_mark_id);
      break;
    }
    case 46:
    {
      sort(data.begin(), data.end(), cmp_by_maximum_latitude);
      break;
    }
    case 47:
    {
      sort(data.begin(), data.end(), cmp_by_maximum_longitude);
      break;
    }
    case 48:
    {
      sort(data.begin(), data.end(), cmp_by_maximum_x);
      break;
    }
    case 49:
    {
      sort(data.begin(), data.end(), cmp_by_maximum_y);
      break;
    }
    case 50:
    {
      sort(data.begin(), data.end(), cmp_by_minimum_latitude);
      break;
    }
    case 51:
    {
      sort(data.begin(), data.end(), cmp_by_minimum_longitude);
      break;
    }
    case 52:
    {
      sort(data.begin(), data.end(), cmp_by_minimum_x);
      break;
    }
    case 53:
    {
      sort(data.begin(), data.end(), cmp_by_minimum_y);
      break;
    }
    case 54:
    {
      sort(data.begin(), data.end(), cmp_by_name);
      break;
    }
    case 55:
    {
      sort(data.begin(), data.end(), cmp_by_overlap_area);
      break;
    }
    case 56:
    {
      sort(data.begin(), data.end(), cmp_by_overlap_lower_left_x);
      break;
    }
    case 57:
    {
      sort(data.begin(), data.end(), cmp_by_overlap_lower_left_y);
      break;
    }
    case 58:
    {
      sort(data.begin(), data.end(), cmp_by_overlap_lower_right_x);
      break;
    }
    case 59:
    {
      sort(data.begin(), data.end(), cmp_by_overlap_lower_right_y);
      break;
    }
    case 60:
    {
      sort(data.begin(), data.end(), cmp_by_overlap_maximum_x);
      break;
    }
    case 61:
    {
      sort(data.begin(), data.end(), cmp_by_overlap_maximum_y);
      break;
    }
    case 62:
    {
      sort(data.begin(), data.end(), cmp_by_overlap_minimum_x);
      break;
    }
    case 63:
    {
      sort(data.begin(), data.end(), cmp_by_overlap_minimum_y);
      break;
    }
    case 64:
    {
      sort(data.begin(), data.end(), cmp_by_overlap_upper_left_x);
      break;
    }
    case 65:
    {
      sort(data.begin(), data.end(), cmp_by_overlap_upper_left_y);
      break;
    }
    case 66:
    {
      sort(data.begin(), data.end(), cmp_by_overlap_upper_right_x);
      break;
    }
    case 67:
    {
      sort(data.begin(), data.end(), cmp_by_overlap_upper_right_y);
      break;
    }
    case 68:
    {
      sort(data.begin(), data.end(), cmp_by_pixel_resolution);
      break;
    }
    case 69:
    {
      sort(data.begin(), data.end(), cmp_by_premarked);
      break;
    }
    case 70:
    {
      sort(data.begin(), data.end(), cmp_by_priority);
      break;
    }
    case 71:
    {
      sort(data.begin(), data.end(), cmp_by_score);
      break;
    }
    case 72:
    {
      sort(data.begin(), data.end(), cmp_by_shared_mark_id);
      break;
    }
    case 73:
    {
      sort(data.begin(), data.end(), cmp_by_sub_type);
      break;
    }
    case 74:
    {
      sort(data.begin(), data.end(), cmp_by_submit_time);
      break;
    }
    case 75:
    {
      sort(data.begin(), data.end(), cmp_by_sun_angle);
      break;
    }
    case 76:
    {
      sort(data.begin(), data.end(), cmp_by_type);
      break;
    }
    case 77:
    {
      sort(data.begin(), data.end(), cmp_by_updated_at);
      break;
    }
    case 78:
    {
      sort(data.begin(), data.end(), cmp_by_upper_left_corner_x_status);
      break;
    }
    case 79:
    {
      sort(data.begin(), data.end(), cmp_by_upper_left_corner_y_status);
      break;
    }
    case 80:
    {
      sort(data.begin(), data.end(), cmp_by_upper_left_latitude);
      break;
    }
    case 81:
    {
      sort(data.begin(), data.end(), cmp_by_upper_left_longitude);
      break;
    }
    case 82:
    {
      sort(data.begin(), data.end(), cmp_by_upper_left_x);
      break;
    }
    case 83:
    {
      sort(data.begin(), data.end(), cmp_by_upper_left_y);
      break;
    }
    case 84:
    {
      sort(data.begin(), data.end(), cmp_by_upper_right_latitude);
      break;
    }
    case 85:
    {
      sort(data.begin(), data.end(), cmp_by_upper_right_longitude);
      break;
    }
    case 86:
    {
      sort(data.begin(), data.end(), cmp_by_upper_right_x);
      break;
    }
    case 87:
    {
      sort(data.begin(), data.end(), cmp_by_upper_right_y);
      break;
    }
    case 88:
    {
      sort(data.begin(), data.end(), cmp_by_user_id);
      break;
    }
    case 89:
    {
      sort(data.begin(), data.end(), cmp_by_width);
      break;
    }
    case 90:
    {
      sort(data.begin(), data.end(), cmp_by_x);
      break;
    }
    case 91:
    {
      sort(data.begin(), data.end(), cmp_by_x_relative);
      break;
    }
    case 92:
    {
      sort(data.begin(), data.end(), cmp_by_y);
      break;
    }
    case 93:
    {
      sort(data.begin(), data.end(), cmp_by_y_relative);
      break;
    }
    default:
    {
      printf("Invalid field value %d.\n", fieldvalue);
      printf("Terminating program ...\n");
      exit(EXIT_FAILURE);
    }
  }
  
  return;
}

#endif
