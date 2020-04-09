/* HEADER FILE: SearchData.h */

#ifndef SEARCHDATA_H
#define SEARCHDATA_H
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <vector>

#include "AuxilaryFunctions.h"
#include "Images.h"
#include "ImageSets.h"
#include "IncidenceAngles.h"
#include "Marks.h"

template <typename T>
class SearchData
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  public:
    static bool EqualityComparison(std::vector <T> &, int, std::string, void *);
    static bool GreaterThanComparison(std::vector <T> &, int, std::string, void *);
    static bool LessThanComparison(std::vector <T> &, int, std::string, void *);
    static double Difference(std::vector <T> &, int, std::string, void *);
    static int BinarySearch(std::vector <T> &, int, int, std::string, void *);
    static int FirstNearestValue(std::vector <T> &, int, int, std::string, void *);
    static int FirstOccurence(std::vector <T> &, int, int, std::string, void *);
    static int LastNearestValue(std::vector <T> &, int, int, std::string, void *);
    static int LastOccurence(std::vector <T> &, int, int, std::string, void *);
};

template <typename T>
bool SearchData<T>::EqualityComparison(std::vector <T> &d, int index, std::string f, void *v)
{
  switch (str2int(f.c_str())) {
  case str2int("application_id"):
    return (d[index].GetValue_int("application_id") == *static_cast<int *>(v));
    break;
  case str2int("confirmed"):
    return (d[index].GetValue_int("confirmed") == *static_cast<int *>(v));
    break;
  case str2int("created_at"):
    return (d[index].GetValue_string("created_at").compare(*static_cast<string *>(v)) == 0);
    break;
  case str2int("details"):
    return (d[index].GetValue_string("details").compare(*static_cast<string *>(v)) == 0);
    break;
  case str2int("diameter"):
    return (d[index].GetValue_double("diameter") == *static_cast<double *>(v));
    break;
  case str2int("done"):
    return (d[index].GetValue_int("done") == *static_cast<int *>(v));
    break;
  case str2int("file_location"):
    return (d[index].GetValue_string("file_location").compare(*static_cast<string *>(v)) == 0);
    break;
  case str2int("height"):
    return (d[index].GetValue_int("height") == *static_cast<int *>(v));
    break;
  case str2int("id"):
    return (d[index].GetValue_int("id") == *static_cast<int *>(v));
    break;
  case str2int("image_id"):
    return (d[index].GetValue_int("image_id") == *static_cast<int *>(v));
    break;
  case str2int("image_set_id"):
    return (d[index].GetValue_int("image_set_id") == *static_cast<int *>(v));
    break;
  case str2int("image1_area"):
    return (d[index].GetValue_int("image1_area") == *static_cast<double *>(v));
    break;
  case str2int("image1_id"):
    return (d[index].GetValue_int("image1_id") == *static_cast<int *>(v));
    break;
  case str2int("image1_incidence_angle"):
    return (d[index].GetValue_double("image1_incidence_angle") == *static_cast<double *>(v));
    break;
  case str2int("image1_lower_left_x"):
    return (d[index].GetValue_double("image1_lower_left_x") == *static_cast<double *>(v));
    break;
  case str2int("image1_lower_left_y"):
    return (d[index].GetValue_double("image1_lower_left_y") == *static_cast<double *>(v));
    break;
  case str2int("image1_lower_right_x"):
    return (d[index].GetValue_double("image1_lower_right_x") == *static_cast<double *>(v));
    break;
  case str2int("image1_lower_right_y"):
    return (d[index].GetValue_double("image1_lower_right_y") == *static_cast<double *>(v));
    break;
  case str2int("image1_name"):
    return (d[index].GetValue_string("image1_name").compare(*static_cast<std::string *>(v)) == 0);
    break;
  case str2int("image1_upper_left_x"):
    return (d[index].GetValue_double("image1_upper_left_x") == *static_cast<double *>(v));
    break;
  case str2int("image1_upper_left_y"):
    return (d[index].GetValue_double("image1_upper_left_y") == *static_cast<double *>(v));
    break;
  case str2int("image1_upper_right_x"):
    return (d[index].GetValue_double("image1_upper_right_x") == *static_cast<double *>(v));
    break;
  case str2int("image1_upper_right_y"):
    return (d[index].GetValue_double("image1_upper_right_y") == *static_cast<double *>(v));
    break;
  case str2int("image2_area"):
    return (d[index].GetValue_double("image2_area") == *static_cast<double *>(v));
    break;
  case str2int("image2_id"):
    return (d[index].GetValue_int("image2_id") == *static_cast<int *>(v));
    break;
  case str2int("image2_incidence_angle"):
    return (d[index].GetValue_double("image2_incidence_angle") == *static_cast<double *>(v));
    break;
  case str2int("image2_lower_left_x"):
    return (d[index].GetValue_double("image2_lower_left_x") == *static_cast<double *>(v));
    break;
  case str2int("image2_lower_left_y"):
    return (d[index].GetValue_double("image2_lower_left_y") == *static_cast<double *>(v));
    break;
  case str2int("image2_lower_right_x"):
    return (d[index].GetValue_double("image2_lower_right_x") == *static_cast<double *>(v));
    break;
  case str2int("image2_lower_right_y"):
    return (d[index].GetValue_double("image2_lower_right_y") == *static_cast<double *>(v));
    break;
  case str2int("image2_name"):
    return (d[index].GetValue_string("image2_name").compare(*static_cast<std::string *>(v)) == 0);
    break;
  case str2int("image2_upper_left_x"):
    return (d[index].GetValue_double("image2_upper_left_x") == *static_cast<double *>(v));
    break;
  case str2int("image2_upper_left_y"):
    return (d[index].GetValue_double("image2_upper_left_y") == *static_cast<double *>(v));
    break;
  case str2int("image2_upper_right_x"):
    return (d[index].GetValue_double("image2_upper_right_x") == *static_cast<double *>(v));
    break;
  case str2int("image2_upper_right_y"):
    return (d[index].GetValue_double("image2_upper_right_y") == *static_cast<double *>(v));
    break;
  case str2int("incidence_angle"):
    return (d[index].GetValue_double("incidence_angle") == *static_cast<double *>(v));
    break;
  case str2int("lower_left_latitude"):
    return (d[index].GetValue_double("lower_left_latitude") == *static_cast<double *>(v));
    break;
  case str2int("lower_left_longitude"):
    return (d[index].GetValue_double("lower_left_longitude") == *static_cast<double *>(v));
    break;
  case str2int("lower_left_x"):
    return (d[index].GetValue_double("lower_left_x") == *static_cast<double *>(v));
    break;
  case str2int("lower_left_y"):
    return (d[index].GetValue_double("lower_left_y") == *static_cast<double *>(v));
    break;
  case str2int("lower_right_latitude"):
    return (d[index].GetValue_double("lower_right_latitude") == *static_cast<double *>(v));
    break;
  case str2int("lower_right_longitude"):
    return (d[index].GetValue_double("lower_right_longitude") == *static_cast<double *>(v));
    break;
  case str2int("lower_right_x"):
    return (d[index].GetValue_double("lower_right_x") == *static_cast<double *>(v));
    break;
  case str2int("lower_right_y"):
    return (d[index].GetValue_double("lower_right_y") == *static_cast<double *>(v));
    break;
  case str2int("machine_mark_id"):
    return (d[index].GetValue_double("machine_mark_id") == *static_cast<int *>(v));
    break;
  case str2int("maximum_latitude"):
    return (d[index].GetValue_double("maximum_latitude") == *static_cast<double *>(v));
    break;
  case str2int("maximum_longitude"):
    return (d[index].GetValue_double("maximum_longitude") == *static_cast<double *>(v));
    break;
  case str2int("maximum_x"):
    return (d[index].GetValue_double("maximum_x") == *static_cast<double *>(v));
    break;
  case str2int("maximum_y"):
    return (d[index].GetValue_double("maximum_y") == *static_cast<double *>(v));
    break;
  case str2int("minimum_latitude"):
    return (d[index].GetValue_double("minimum_latitude") == *static_cast<double *>(v));
    break;
  case str2int("minimum_longitude"):
    return (d[index].GetValue_double("minimum_longitude") == *static_cast<double *>(v));
    break;
  case str2int("minimum_x"):
    return (d[index].GetValue_double("minimum_x") == *static_cast<double *>(v));
    break;
  case str2int("minimum_y"):
    return (d[index].GetValue_double("minimum_y") == *static_cast<double *>(v));
    break;
  case str2int("name"):
    return (d[index].GetValue_string("name").compare(*static_cast<string *>(v)) == 0);
    break;
  case str2int("overlap_area"):
    return (d[index].GetValue_double("overlap_area") == *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_left_x"):
    return (d[index].GetValue_double("overlap_lower_left_x") == *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_left_y"):
    return (d[index].GetValue_double("overlap_lower_left_y") == *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_right_x"):
    return (d[index].GetValue_double("overlap_lower_right_x") == *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_right_y"):
    return (d[index].GetValue_double("overlap_lower_right_y") == *static_cast<double *>(v));
    break;
  case str2int("overlap_maximum_x"):
    return (d[index].GetValue_double("overlap_maximum_x") == *static_cast<double *>(v));
    break;
  case str2int("overlap_maximum_y"):
    return (d[index].GetValue_double("overlap_maximum_y") == *static_cast<double *>(v));
    break;
  case str2int("overlap_minimum_x"):
    return (d[index].GetValue_double("overlap_minimum_x") == *static_cast<double *>(v));
    break;
  case str2int("overlap_minimum_y"):
    return (d[index].GetValue_double("overlap_minimum_y") == *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_left_x"):
    return (d[index].GetValue_double("overlap_upper_left_x") == *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_left_y"):
    return (d[index].GetValue_double("overlap_upper_left_y") == *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_right_x"):
    return (d[index].GetValue_double("overlap_upper_right_x") == *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_right_y"):
    return (d[index].GetValue_double("overlap_upper_right_y") == *static_cast<double *>(v));
    break;
  case str2int("pixel_resolution"):
    return (d[index].GetValue_double("pixel_resolution") == *static_cast<double *>(v));
    break;
  case str2int("premarked"):
    return (d[index].GetValue_int("premarked") == *static_cast<int *>(v));
    break;
  case str2int("priority"):
    return (d[index].GetValue_double("priority") == *static_cast<double *>(v));
    break;
  case str2int("score"):
    return (d[index].GetValue_double("score") == *static_cast<double *>(v));
    break;
  case str2int("shared_mark_id"):
    return (d[index].GetValue_double("shared_mark_id") == *static_cast<double *>(v));
    break;
  case str2int("sub_type"):
    return (d[index].GetValue_string("sub_type").compare(*static_cast<string *>(v)) == 0);
    break;
  case str2int("submit_time"):
    return (d[index].GetValue_double("submit_time") == *static_cast<int *>(v));
    break;
  case str2int("sun_angle"):
    return (d[index].GetValue_double("sun_angle") == *static_cast<double *>(v));
    break;
  case str2int("type"):
    return (d[index].GetValue_string("type").compare(*static_cast<string *>(v)) == 0);
    break;
  case str2int("updated_at"):
    return (d[index].GetValue_string("updated_at").compare(*static_cast<string *>(v)) == 0);
    break;
  case str2int("upper_left_corner_x_status"):
    return (d[index].GetValue_string("upper_left_corner_x_status").compare(*static_cast<string *>(v)) == 0);
    break;
  case str2int("upper_left_corner_y_status"):
    return (d[index].GetValue_string("upper_left_corner_y_status").compare(*static_cast<string *>(v)) == 0);
    break;
  case str2int("upper_left_latitude"):
    return (d[index].GetValue_double("upper_left_latitude") == *static_cast<double *>(v));
    break;
  case str2int("upper_left_longitude"):
    return (d[index].GetValue_double("upper_left_longitude") == *static_cast<double *>(v));
    break;
  case str2int("upper_left_x"):
    return (d[index].GetValue_double("upper_left_x") == *static_cast<double *>(v));
    break;
  case str2int("upper_left_y"):
    return (d[index].GetValue_double("upper_left_y") == *static_cast<double *>(v));
    break;
  case str2int("upper_right_latitude"):
    return (d[index].GetValue_double("upper_right_latitude") == *static_cast<double *>(v));
    break;
  case str2int("upper_right_longitude"):
    return (d[index].GetValue_double("upper_right_longitude") == *static_cast<double *>(v));
    break;
  case str2int("upper_right_x"):
    return (d[index].GetValue_double("upper_right_x") == *static_cast<double *>(v));
    break;
  case str2int("upper_right_y"):
    return (d[index].GetValue_double("upper_right_y") == *static_cast<double *>(v));
    break;
  case str2int("width"):
    return (d[index].GetValue_int("width") == *static_cast<int *>(v));
    break;
  case str2int("x"):
    return (d[index].GetValue_double("x") == *static_cast<double *>(v));
    break;
  case str2int("x_relative"):
    return (d[index].GetValue_int("x_relative") == *static_cast<int *>(v));
    break;
  case str2int("y"):
    return (d[index].GetValue_double("y") == *static_cast<double *>(v));
    break;
  case str2int("y_relative"):
    return (d[index].GetValue_int("y_relative") == *static_cast<int *>(v));
    break;
  }
  
  return false;
}

template <typename T>
bool SearchData<T>::GreaterThanComparison(std::vector <T> &d, int index, std::string f, void *v)
{
  switch (str2int(f.c_str())) {
  case str2int("application_id"):
    return (d[index].GetValue_int("application_id") > *static_cast<int *>(v));
    break;
  case str2int("confirmed"):
    return (d[index].GetValue_int("confirmed") > *static_cast<int *>(v));
    break;
  case str2int("created_at"):
    return (d[index].GetValue_string("created_at") > *static_cast<string *>(v));
    break;
  case str2int("details"):
    return (d[index].GetValue_string("details") > *static_cast<string *>(v));
    break;
  case str2int("diameter"):
    return (d[index].GetValue_double("diameter") > *static_cast<double *>(v));
    break;
  case str2int("done"):
    return (d[index].GetValue_int("done") > *static_cast<int *>(v));
    break;
  case str2int("file_location"):
    return (d[index].GetValue_string("file_location") > *static_cast<string *>(v));
    break;
  case str2int("height"):
    return (d[index].GetValue_int("height") > *static_cast<int *>(v));
    break;
  case str2int("id"):
    return (d[index].GetValue_int("id") > *static_cast<int *>(v));
    break;
  case str2int("image_id"):
    return (d[index].GetValue_int("image_id") > *static_cast<int *>(v));
    break;
  case str2int("image_set_id"):
    return (d[index].GetValue_int("image_set_id") > *static_cast<int *>(v));
    break;
  case str2int("image1_area"):
    return (d[index].GetValue_double("image1_area") > *static_cast<double *>(v));
    break;
  case str2int("image1_id"):
    return (d[index].GetValue_int("image1_id") > *static_cast<int *>(v));
    break;
  case str2int("image1_incidence_angle"):
    return (d[index].GetValue_double("image1_incidence_angle") > *static_cast<double *>(v));
    break;
  case str2int("image1_lower_left_x"):
    return (d[index].GetValue_double("image1_lower_left_x") > *static_cast<double *>(v));
    break;
  case str2int("image1_lower_left_y"):
    return (d[index].GetValue_double("image1_lower_left_y") > *static_cast<double *>(v));
    break;
  case str2int("image1_lower_right_x"):
    return (d[index].GetValue_double("image1_lower_right_x") > *static_cast<double *>(v));
    break;
  case str2int("image1_lower_right_y"):
    return (d[index].GetValue_double("image1_lower_right_y") > *static_cast<double *>(v));
    break;
  case str2int("image1_name"):
    return (d[index].GetValue_string("image1_name") > *static_cast<std::string *>(v));
    break;
  case str2int("image1_upper_left_x"):
    return (d[index].GetValue_double("image1_upper_left_x") > *static_cast<double *>(v));
    break;
  case str2int("image1_upper_left_y"):
    return (d[index].GetValue_double("image1_upper_left_y") > *static_cast<double *>(v));
    break;
  case str2int("image1_upper_right_x"):
    return (d[index].GetValue_double("image1_upper_right_x") > *static_cast<double *>(v));
    break;
  case str2int("image1_upper_right_y"):
    return (d[index].GetValue_double("image1_upper_right_y") > *static_cast<double *>(v));
    break;
  case str2int("image2_area"):
    return (d[index].GetValue_double("image2_area") > *static_cast<double *>(v));
    break;
  case str2int("image2_id"):
    return (d[index].GetValue_int("image2_id") > *static_cast<int *>(v));
    break;
  case str2int("image2_incidence_angle"):
    return (d[index].GetValue_double("image2_incidence_angle") > *static_cast<double *>(v));
    break;
  case str2int("image2_lower_left_x"):
    return (d[index].GetValue_double("image2_lower_left_x") > *static_cast<double *>(v));
    break;
  case str2int("image2_lower_left_y"):
    return (d[index].GetValue_double("image2_lower_left_y") > *static_cast<double *>(v));
    break;
  case str2int("image2_lower_right_x"):
    return (d[index].GetValue_double("image2_lower_right_x") > *static_cast<double *>(v));
    break;
  case str2int("image2_lower_right_y"):
    return (d[index].GetValue_double("image2_lower_right_y") > *static_cast<double *>(v));
    break;
  case str2int("image2_name"):
    return (d[index].GetValue_string("image2_name") > *static_cast<std::string *>(v));
    break;
  case str2int("image2_upper_left_x"):
    return (d[index].GetValue_double("image2_upper_left_x") > *static_cast<double *>(v));
    break;
  case str2int("image2_upper_left_y"):
    return (d[index].GetValue_double("image2_upper_left_y") > *static_cast<double *>(v));
    break;
  case str2int("image2_upper_right_x"):
    return (d[index].GetValue_double("image2_upper_right_x") > *static_cast<double *>(v));
    break;
  case str2int("image2_upper_right_y"):
    return (d[index].GetValue_double("image2_upper_right_y") > *static_cast<double *>(v));
    break;
  case str2int("incidence_angle"):
    return (d[index].GetValue_double("incidence_angle") > *static_cast<double *>(v));
    break;
  case str2int("lower_left_latitude"):
    return (d[index].GetValue_double("lower_left_latitude") > *static_cast<double *>(v));
    break;
  case str2int("lower_left_longitude"):
    return (d[index].GetValue_double("lower_left_longitude") > *static_cast<double *>(v));
    break;
  case str2int("lower_left_x"):
    return (d[index].GetValue_double("lower_left_x") > *static_cast<double *>(v));
    break;
  case str2int("lower_left_y"):
    return (d[index].GetValue_double("lower_left_y") > *static_cast<double *>(v));
    break;
  case str2int("lower_right_latitude"):
    return (d[index].GetValue_double("lower_right_latitude") > *static_cast<double *>(v));
    break;
  case str2int("lower_right_longitude"):
    return (d[index].GetValue_double("lower_right_longitude") > *static_cast<double *>(v));
    break;
  case str2int("lower_right_x"):
    return (d[index].GetValue_double("lower_right_x") > *static_cast<double *>(v));
    break;
  case str2int("lower_right_y"):
    return (d[index].GetValue_double("lower_right_y") > *static_cast<double *>(v));
    break;
  case str2int("machine_mark_id"):
    return (d[index].GetValue_double("machine_mark_id") > *static_cast<int *>(v));
    break;
  case str2int("maximum_latitude"):
    return (d[index].GetValue_double("maximum_latitude") > *static_cast<double *>(v));
    break;
  case str2int("maximum_longitude"):
    return (d[index].GetValue_double("maximum_longitude") > *static_cast<double *>(v));
    break;
  case str2int("maximum_x"):
    return (d[index].GetValue_double("maximum_x") > *static_cast<double *>(v));
    break;
  case str2int("maximum_y"):
    return (d[index].GetValue_double("maximum_y") > *static_cast<double *>(v));
    break;
  case str2int("minimum_latitude"):
    return (d[index].GetValue_double("minimum_latitude") > *static_cast<double *>(v));
    break;
  case str2int("minimum_longitude"):
    return (d[index].GetValue_double("minimum_longitude") > *static_cast<double *>(v));
    break;
  case str2int("minimum_x"):
    return (d[index].GetValue_double("minimum_x") > *static_cast<double *>(v));
    break;
  case str2int("minimum_y"):
    return (d[index].GetValue_double("minimum_y") > *static_cast<double *>(v));
    break;
  case str2int("name"):
    return (d[index].GetValue_string("name") > *static_cast<string *>(v));
    break;
  case str2int("overlap_area"):
    return (d[index].GetValue_double("overlap_area") > *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_left_x"):
    return (d[index].GetValue_double("overlap_lower_left_x") > *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_left_y"):
    return (d[index].GetValue_double("overlap_lower_left_y") > *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_right_x"):
    return (d[index].GetValue_double("overlap_lower_right_x") > *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_right_y"):
    return (d[index].GetValue_double("overlap_lower_right_y") > *static_cast<double *>(v));
    break;
  case str2int("overlap_maximum_x"):
    return (d[index].GetValue_double("overlap_maximum_x") > *static_cast<double *>(v));
    break;
  case str2int("overlap_maximum_y"):
    return (d[index].GetValue_double("overlap_maximum_y") > *static_cast<double *>(v));
    break;
  case str2int("overlap_minimum_x"):
    return (d[index].GetValue_double("overlap_minimum_x") > *static_cast<double *>(v));
    break;
  case str2int("overlap_minimum_y"):
    return (d[index].GetValue_double("overlap_minimum_y") > *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_left_x"):
    return (d[index].GetValue_double("overlap_upper_left_x") > *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_left_y"):
    return (d[index].GetValue_double("overlap_upper_left_y") > *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_right_x"):
    return (d[index].GetValue_double("overlap_upper_right_x") > *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_right_y"):
    return (d[index].GetValue_double("overlap_upper_right_y") > *static_cast<double *>(v));
    break;
  case str2int("pixel_resolution"):
    return (d[index].GetValue_double("pixel_resolution") > *static_cast<double *>(v));
    break;
  case str2int("premarked"):
    return (d[index].GetValue_int("premarked") > *static_cast<int *>(v));
    break;
  case str2int("priority"):
    return (d[index].GetValue_double("priority") > *static_cast<double *>(v));
    break;
  case str2int("score"):
    return (d[index].GetValue_double("score") > *static_cast<double *>(v));
    break;
  case str2int("shared_mark_id"):
    return (d[index].GetValue_int("shared_mark_id") > *static_cast<int *>(v));
    break;
  case str2int("sub_type"):
    return (d[index].GetValue_string("sub_type") > *static_cast<string *>(v));
    break;
  case str2int("submit_time"):
    return (d[index].GetValue_int("submit_time") > *static_cast<int *>(v));
    break;
  case str2int("sun_angle"):
    return (d[index].GetValue_double("sun_angle") > *static_cast<double *>(v));
    break;
  case str2int("type"):
    return (d[index].GetValue_string("type") > *static_cast<string *>(v));
    break;
  case str2int("updated_at"):
    return (d[index].GetValue_string("updated_at") > *static_cast<string *>(v));
    break;
  case str2int("upper_left_corner_x_status"):
    return (d[index].GetValue_string("upper_left_corner_x_status") > *static_cast<string *>(v));
    break;
  case str2int("upper_left_corner_y_status"):
    return (d[index].GetValue_string("upper_left_corner_y_status") > *static_cast<string *>(v));
    break;
  case str2int("upper_left_latitude"):
    return (d[index].GetValue_double("upper_left_latitude") > *static_cast<double *>(v));
    break;
  case str2int("upper_left_longitude"):
    return (d[index].GetValue_double("upper_left_longitude") > *static_cast<double *>(v));
    break;
  case str2int("upper_left_x"):
    return (d[index].GetValue_double("upper_left_x") > *static_cast<double *>(v));
    break;
  case str2int("upper_left_y"):
    return (d[index].GetValue_double("upper_left_y") > *static_cast<double *>(v));
    break;
  case str2int("upper_right_latitude"):
    return (d[index].GetValue_double("upper_right_latitude") > *static_cast<double *>(v));
    break;
  case str2int("upper_right_longitude"):
    return (d[index].GetValue_double("upper_right_longitude") > *static_cast<double *>(v));
    break;
  case str2int("upper_right_x"):
    return (d[index].GetValue_double("upper_right_x") > *static_cast<double *>(v));
    break;
  case str2int("upper_right_y"):
    return (d[index].GetValue_double("upper_right_y") > *static_cast<double *>(v));
    break;
  case str2int("width"):
    return (d[index].GetValue_int("width") > *static_cast<int *>(v));
    break;
  case str2int("x"):
    return (d[index].GetValue_double("x") > *static_cast<double *>(v));
    break;
  case str2int("x_relative"):
    return (d[index].GetValue_int("x_relative") > *static_cast<int *>(v));
    break;
  case str2int("y"):
    return (d[index].GetValue_double("y") > *static_cast<double *>(v));
    break;
  case str2int("y_relative"):
    return (d[index].GetValue_int("y_relative") > *static_cast<int *>(v));
    break;
  }

  return false;
}

template <typename T>
bool SearchData<T>::LessThanComparison(std::vector <T> &d, int index, std::string f, void *v)
{
  switch (str2int(f.c_str())) {
  case str2int("application_id"):
    return (d[index].GetValue_int("application_id") < *static_cast<int *>(v));
    break;
  case str2int("confirmed"):
    return (d[index].GetValue_int("confirmed") < *static_cast<int *>(v));
    break;
  case str2int("created_at"):
    return (d[index].GetValue_string("created_at") < *static_cast<string *>(v));
    break;
  case str2int("details"):
    return (d[index].GetValue_string("details") < *static_cast<string *>(v));
    break;
  case str2int("diameter"):
    return (d[index].GetValue_double("diameter") < *static_cast<double *>(v));
    break;
  case str2int("done"):
    return (d[index].GetValue_int("done") < *static_cast<int *>(v));
    break;
  case str2int("file_location"):
    return (d[index].GetValue_string("file_location") < *static_cast<string *>(v));
    break;
  case str2int("height"):
    return (d[index].GetValue_int("height") < *static_cast<int *>(v));
    break;
  case str2int("id"):
    return (d[index].GetValue_int("id") < *static_cast<int *>(v));
    break;
  case str2int("image_id"):
    return (d[index].GetValue_int("image_id") < *static_cast<int *>(v));
    break;
  case str2int("image_set_id"):
    return (d[index].GetValue_int("image_set_id") < *static_cast<int *>(v));
    break;
  case str2int("image1_area"):
    return (d[index].GetValue_double("image1_area") < *static_cast<double *>(v));
    break;
  case str2int("image1_id"):
    return (d[index].GetValue_int("image1_id") < *static_cast<int *>(v));
    break;
  case str2int("image1_incidence_angle"):
    return (d[index].GetValue_double("image1_incidence_angle") < *static_cast<double *>(v));
    break;
  case str2int("image1_lower_left_x"):
    return (d[index].GetValue_double("image1_lower_left_x") < *static_cast<double *>(v));
    break;
  case str2int("image1_lower_left_y"):
    return (d[index].GetValue_double("image1_lower_left_y") < *static_cast<double *>(v));
    break;
  case str2int("image1_lower_right_x"):
    return (d[index].GetValue_double("image1_lower_right_x") < *static_cast<double *>(v));
    break;
  case str2int("image1_lower_right_y"):
    return (d[index].GetValue_double("image1_lower_right_y") < *static_cast<double *>(v));
    break;
  case str2int("image1_name"):
    return (d[index].GetValue_string("image1_name") < *static_cast<std::string *>(v));
    break;
  case str2int("image1_upper_left_x"):
    return (d[index].GetValue_double("image1_upper_left_x") < *static_cast<double *>(v));
    break;
  case str2int("image1_upper_left_y"):
    return (d[index].GetValue_double("image1_upper_left_y") < *static_cast<double *>(v));
    break;
  case str2int("image1_upper_right_x"):
    return (d[index].GetValue_double("image1_upper_right_x") < *static_cast<double *>(v));
    break;
  case str2int("image1_upper_right_y"):
    return (d[index].GetValue_double("image1_upper_right_y") < *static_cast<double *>(v));
    break;
  case str2int("image2_area"):
    return (d[index].GetValue_double("image2_area") < *static_cast<double *>(v));
    break;
  case str2int("image2_id"):
    return (d[index].GetValue_int("image2_id") < *static_cast<int *>(v));
    break;
  case str2int("image2_incidence_angle"):
    return (d[index].GetValue_double("image2_incidence_angle") < *static_cast<double *>(v));
    break;
  case str2int("image2_lower_left_x"):
    return (d[index].GetValue_double("image2_lower_left_x") < *static_cast<double *>(v));
    break;
  case str2int("image2_lower_left_y"):
    return (d[index].GetValue_double("image2_lower_left_y") < *static_cast<double *>(v));
    break;
  case str2int("image2_lower_right_x"):
    return (d[index].GetValue_double("image2_lower_right_x") < *static_cast<double *>(v));
    break;
  case str2int("image2_lower_right_y"):
    return (d[index].GetValue_double("image2_lower_right_y") < *static_cast<double *>(v));
    break;
  case str2int("image2_name"):
    return (d[index].GetValue_string("image2_name") < *static_cast<std::string *>(v));
    break;
  case str2int("image2_upper_left_x"):
    return (d[index].GetValue_double("image2_upper_left_x") < *static_cast<double *>(v));
    break;
  case str2int("image2_upper_left_y"):
    return (d[index].GetValue_double("image2_upper_left_y") < *static_cast<double *>(v));
    break;
  case str2int("image2_upper_right_x"):
    return (d[index].GetValue_double("image2_upper_right_x") < *static_cast<double *>(v));
    break;
  case str2int("image2_upper_right_y"):
    return (d[index].GetValue_double("image2_upper_right_y") < *static_cast<double *>(v));
    break;
  case str2int("incidence_angle"):
    return (d[index].GetValue_double("incidence_angle") < *static_cast<double *>(v));
    break;
  case str2int("lower_left_latitude"):
    return (d[index].GetValue_double("lower_left_latitude") < *static_cast<double *>(v));
    break;
  case str2int("lower_left_longitude"):
    return (d[index].GetValue_double("lower_left_longitude") < *static_cast<double *>(v));
    break;
  case str2int("lower_left_x"):
    return (d[index].GetValue_double("lower_left_x") < *static_cast<double *>(v));
    break;
  case str2int("lower_left_y"):
    return (d[index].GetValue_double("lower_left_y") < *static_cast<double *>(v));
    break;
  case str2int("lower_right_latitude"):
    return (d[index].GetValue_double("lower_right_latitude") < *static_cast<double *>(v));
    break;
  case str2int("lower_right_longitude"):
    return (d[index].GetValue_double("lower_right_longitude") < *static_cast<double *>(v));
    break;
  case str2int("lower_right_x"):
    return (d[index].GetValue_double("lower_right_x") < *static_cast<double *>(v));
    break;
  case str2int("lower_right_y"):
    return (d[index].GetValue_double("lower_right_y") < *static_cast<double *>(v));
    break;
  case str2int("machine_mark_id"):
    return (d[index].GetValue_double("machine_mark_id") < *static_cast<int *>(v));
    break;
  case str2int("maximum_latitude"):
    return (d[index].GetValue_double("maximum_latitude") < *static_cast<double *>(v));
    break;
  case str2int("maximum_longitude"):
    return (d[index].GetValue_double("maximum_longitude") < *static_cast<double *>(v));
    break;
  case str2int("maximum_x"):
    return (d[index].GetValue_double("maximum_x") < *static_cast<double *>(v));
    break;
  case str2int("maximum_y"):
    return (d[index].GetValue_double("maximum_y") < *static_cast<double *>(v));
    break;
  case str2int("minimum_latitude"):
    return (d[index].GetValue_double("minimum_latitude") < *static_cast<double *>(v));
    break;
  case str2int("minimum_longitude"):
    return (d[index].GetValue_double("minimum_longitude") < *static_cast<double *>(v));
    break;
  case str2int("minimum_x"):
    return (d[index].GetValue_double("minimum_x") < *static_cast<double *>(v));
    break;
  case str2int("minimum_y"):
    return (d[index].GetValue_double("minimum_y") < *static_cast<double *>(v));
    break;
  case str2int("name"):
    return (d[index].GetValue_string("name") < *static_cast<string *>(v));
    break;
  case str2int("overlap_area"):
    return (d[index].GetValue_double("overlap_area") < *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_left_x"):
    return (d[index].GetValue_double("overlap_lower_left_x") < *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_left_y"):
    return (d[index].GetValue_double("overlap_lower_left_y") < *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_right_x"):
    return (d[index].GetValue_double("overlap_lower_right_x") < *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_right_y"):
    return (d[index].GetValue_double("overlap_lower_right_y") < *static_cast<double *>(v));
    break;
  case str2int("overlap_maximum_x"):
    return (d[index].GetValue_double("overlap_maximum_x") < *static_cast<double *>(v));
    break;
  case str2int("overlap_maximum_y"):
    return (d[index].GetValue_double("overlap_maximum_y") < *static_cast<double *>(v));
    break;
  case str2int("overlap_minimum_x"):
    return (d[index].GetValue_double("overlap_minimum_x") < *static_cast<double *>(v));
    break;
  case str2int("overlap_minimum_y"):
    return (d[index].GetValue_double("overlap_minimum_y") < *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_left_x"):
    return (d[index].GetValue_double("overlap_upper_left_x") < *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_left_y"):
    return (d[index].GetValue_double("overlap_upper_left_y") < *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_right_x"):
    return (d[index].GetValue_double("overlap_upper_right_x") < *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_right_y"):
    return (d[index].GetValue_double("overlap_upper_right_y") < *static_cast<double *>(v));
    break;
  case str2int("pixel_resolution"):
    return (d[index].GetValue_double("pixel_resolution") < *static_cast<double *>(v));
    break;
  case str2int("premarked"):
    return (d[index].GetValue_int("premarked") < *static_cast<int *>(v));
    break;
  case str2int("priority"):
    return (d[index].GetValue_double("priority") < *static_cast<double *>(v));
    break;
  case str2int("score"):
    return (d[index].GetValue_double("score") < *static_cast<double *>(v));
    break;
  case str2int("shared_mark_id"):
    return (d[index].GetValue_int("shared_mark_id") < *static_cast<int *>(v));
    break;
  case str2int("sub_type"):
    return (d[index].GetValue_string("sub_type") < *static_cast<string *>(v));
    break;
  case str2int("submit_time"):
    return (d[index].GetValue_int("submit_time") < *static_cast<int *>(v));
    break;
  case str2int("sun_angle"):
    return (d[index].GetValue_double("sun_angle") < *static_cast<double *>(v));
    break;
  case str2int("type"):
    return (d[index].GetValue_string("type") < *static_cast<string *>(v));
    break;
  case str2int("updated_at"):
    return (d[index].GetValue_string("updated_at") < *static_cast<string *>(v));
    break;
  case str2int("upper_left_corner_x_status"):
    return (d[index].GetValue_string("upper_left_corner_x_status") < *static_cast<string *>(v));
    break;
  case str2int("upper_left_corner_y_status"):
    return (d[index].GetValue_string("upper_left_corner_y_status") < *static_cast<string *>(v));
    break;
  case str2int("upper_left_latitude"):
    return (d[index].GetValue_double("upper_left_latitude") < *static_cast<double *>(v));
    break;
  case str2int("upper_left_longitude"):
    return (d[index].GetValue_double("upper_left_longitude") < *static_cast<double *>(v));
    break;
  case str2int("upper_left_x"):
    return (d[index].GetValue_double("upper_left_x") < *static_cast<double *>(v));
    break;
  case str2int("upper_left_y"):
    return (d[index].GetValue_double("upper_left_y") < *static_cast<double *>(v));
    break;
  case str2int("upper_right_latitude"):
    return (d[index].GetValue_double("upper_right_latitude") < *static_cast<double *>(v));
    break;
  case str2int("upper_right_longitude"):
    return (d[index].GetValue_double("upper_right_longitude") < *static_cast<double *>(v));
    break;
  case str2int("upper_right_x"):
    return (d[index].GetValue_double("upper_right_x") < *static_cast<double *>(v));
    break;
  case str2int("upper_right_y"):
    return (d[index].GetValue_double("upper_right_y") < *static_cast<double *>(v));
    break;
  case str2int("width"):
    return (d[index].GetValue_int("width") < *static_cast<int *>(v));
    break;
  case str2int("x"):
    return (d[index].GetValue_double("x") < *static_cast<double *>(v));
    break;
  case str2int("x_relative"):
    return (d[index].GetValue_int("x_relative") < *static_cast<int *>(v));
    break;
  case str2int("y"):
    return (d[index].GetValue_double("y") < *static_cast<double *>(v));
    break;
  case str2int("y_relative"):
    return (d[index].GetValue_int("y_relative") < *static_cast<int *>(v));
    break;
  }

  return false;
}

template <typename T>
double SearchData<T>::Difference(std::vector <T> &d, int index, std::string f, void *v)
{
  switch (str2int(f.c_str())) {
  case str2int("application_id"):
    return (d[index].GetValue_int("application_id") - *static_cast<int *>(v));
    break;
  case str2int("confirmed"):
    return (d[index].GetValue_int("confirmed") - *static_cast<int *>(v));
    break;
  case str2int("created_at"):
    return (d[index].GetValue_string("created_at").compare(*static_cast<string *>(v)));
    break;
  case str2int("details"):
    return (d[index].GetValue_string("details").compare(*static_cast<string *>(v)));
    break;
  case str2int("diameter"):
    return (d[index].GetValue_double("diameter") - *static_cast<double *>(v));
    break;
  case str2int("done"):
    return (d[index].GetValue_int("done") - *static_cast<int *>(v));
    break;
  case str2int("file_location"):
    return (d[index].GetValue_string("file_location").compare(*static_cast<string *>(v)));
    break;
  case str2int("height"):
    return (d[index].GetValue_int("height") - *static_cast<int *>(v));
    break;
  case str2int("id"):
    return (d[index].GetValue_int("id") - *static_cast<int *>(v));
    break;
  case str2int("image_id"):
    return (d[index].GetValue_int("image_id") - *static_cast<int *>(v));
    break;
  case str2int("image_set_id"):
    return (d[index].GetValue_int("image_set_id") - *static_cast<int *>(v));
    break;
  case str2int("image1_area"):
    return (d[index].GetValue_double("image1_area") - *static_cast<double *>(v));
    break;
  case str2int("image1_id"):
    return (d[index].GetValue_int("image1_id") - *static_cast<int *>(v));
    break;
  case str2int("image1_incidence_angle"):
    return (d[index].GetValue_double("image1_incidence_angle") - *static_cast<double *>(v));
    break;
  case str2int("image1_lower_left_x"):
    return (d[index].GetValue_double("image1_lower_left_x") - *static_cast<double *>(v));
    break;
  case str2int("image1_lower_left_y"):
    return (d[index].GetValue_double("image1_lower_left_y") - *static_cast<double *>(v));
    break;
  case str2int("image1_lower_right_x"):
    return (d[index].GetValue_double("image1_lower_right_x") - *static_cast<double *>(v));
    break;
  case str2int("image1_lower_right_y"):
    return (d[index].GetValue_double("image1_lower_right_y") - *static_cast<double *>(v));
    break;
  case str2int("image1_name"):
    return (d[index].GetValue_string("image1_name").compare(*static_cast<std::string *>(v)));
    break;
  case str2int("image1_upper_left_x"):
    return (d[index].GetValue_double("image1_upper_left_x") - *static_cast<double *>(v));
    break;
  case str2int("image1_upper_left_y"):
    return (d[index].GetValue_double("image1_upper_left_y") - *static_cast<double *>(v));
    break;
  case str2int("image1_upper_right_x"):
    return (d[index].GetValue_double("image1_upper_right_x") - *static_cast<double *>(v));
    break;
  case str2int("image1_upper_right_y"):
    return (d[index].GetValue_double("image1_upper_right_y") - *static_cast<double *>(v));
    break;
  case str2int("image2_area"):
    return (d[index].GetValue_double("image2_area") - *static_cast<double *>(v));
    break;
  case str2int("image2_id"):
    return (d[index].GetValue_int("image2_id") - *static_cast<int *>(v));
    break;
  case str2int("image2_incidence_angle"):
    return (d[index].GetValue_double("image2_incidence_angle") - *static_cast<double *>(v));
    break;
  case str2int("image2_lower_left_x"):
    return (d[index].GetValue_double("image2_lower_left_x") - *static_cast<double *>(v));
    break;
  case str2int("image2_lower_left_y"):
    return (d[index].GetValue_double("image2_lower_left_y") - *static_cast<double *>(v));
    break;
  case str2int("image2_lower_right_x"):
    return (d[index].GetValue_double("image2_lower_right_x") - *static_cast<double *>(v));
    break;
  case str2int("image2_lower_right_y"):
    return (d[index].GetValue_double("image2_lower_right_y") - *static_cast<double *>(v));
    break;
  case str2int("image2_name"):
    return (d[index].GetValue_string("image2_name").compare(*static_cast<std::string *>(v)));
    break;
  case str2int("image2_upper_left_x"):
    return (d[index].GetValue_double("image2_upper_left_x") - *static_cast<double *>(v));
    break;
  case str2int("image2_upper_left_y"):
    return (d[index].GetValue_double("image2_upper_left_y") - *static_cast<double *>(v));
    break;
  case str2int("image2_upper_right_x"):
    return (d[index].GetValue_double("image2_upper_right_x") - *static_cast<double *>(v));
    break;
  case str2int("image2_upper_right_y"):
    return (d[index].GetValue_double("image2_upper_right_y") - *static_cast<double *>(v));
    break;
  case str2int("incidence_angle"):
    return (d[index].GetValue_double("incidence_angle") - *static_cast<double *>(v));
    break;
  case str2int("lower_left_latitude"):
    return (d[index].GetValue_double("lower_left_latitude") - *static_cast<double *>(v));
    break;
  case str2int("lower_left_longitude"):
    return (d[index].GetValue_double("lower_left_longitude") - *static_cast<double *>(v));
    break;
  case str2int("lower_left_x"):
    return (d[index].GetValue_double("lower_left_x") - *static_cast<double *>(v));
    break;
  case str2int("lower_left_y"):
    return (d[index].GetValue_double("lower_left_y") - *static_cast<double *>(v));
    break;
  case str2int("lower_right_latitude"):
    return (d[index].GetValue_double("lower_right_latitude") - *static_cast<double *>(v));
    break;
  case str2int("lower_right_longitude"):
    return (d[index].GetValue_double("lower_right_longitude") - *static_cast<double *>(v));
    break;
  case str2int("lower_right_x"):
    return (d[index].GetValue_double("lower_right_x") - *static_cast<double *>(v));
    break;
  case str2int("lower_right_y"):
    return (d[index].GetValue_double("lower_right_y") - *static_cast<double *>(v));
    break;
  case str2int("machine_mark_id"):
    return (d[index].GetValue_int("machine_mark_id") - *static_cast<int *>(v));
    break;
  case str2int("maximum_latitude"):
    return (d[index].GetValue_double("maximum_latitude") - *static_cast<double *>(v));
    break;
  case str2int("maximum_longitude"):
    return (d[index].GetValue_double("maximum_longitude") - *static_cast<double *>(v));
    break;
  case str2int("maximum_x"):
    return (d[index].GetValue_double("maximum_x") - *static_cast<double *>(v));
    break;
  case str2int("maximum_y"):
    return (d[index].GetValue_double("maximum_y") - *static_cast<double *>(v));
    break;
  case str2int("minimum_latitude"):
    return (d[index].GetValue_double("minimum_latitude") - *static_cast<double *>(v));
    break;
  case str2int("minimum_longitude"):
    return (d[index].GetValue_double("minimum_longitude") - *static_cast<double *>(v));
    break;
  case str2int("minimum_x"):
    return (d[index].GetValue_double("minimum_x") - *static_cast<double *>(v));
    break;
  case str2int("minimum_y"):
    return (d[index].GetValue_double("minimum_y") - *static_cast<double *>(v));
    break;
  case str2int("name"):
    return (d[index].GetValue_string("name").compare(*static_cast<string *>(v)));
    break;
  case str2int("overlap_area"):
    return (d[index].GetValue_double("overlap_area") - *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_left_x"):
    return (d[index].GetValue_double("overlap_lower_left_x") - *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_left_y"):
    return (d[index].GetValue_double("overlap_lower_left_y") - *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_right_x"):
    return (d[index].GetValue_double("overlap_lower_right_x") - *static_cast<double *>(v));
    break;
  case str2int("overlap_lower_right_y"):
    return (d[index].GetValue_double("overlap_lower_right_y") - *static_cast<double *>(v));
    break;
  case str2int("overlap_maximum_x"):
    return (d[index].GetValue_double("overlap_maximum_x") - *static_cast<double *>(v));
    break;
  case str2int("overlap_maximum_y"):
    return (d[index].GetValue_double("overlap_maximum_y") - *static_cast<double *>(v));
    break;
  case str2int("overlap_minimum_x"):
    return (d[index].GetValue_double("overlap_minimum_x") - *static_cast<double *>(v));
    break;
  case str2int("overlap_minimum_y"):
    return (d[index].GetValue_double("overlap_minimum_y") - *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_left_x"):
    return (d[index].GetValue_double("overlap_upper_left_x") - *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_left_y"):
    return (d[index].GetValue_double("overlap_upper_left_y") - *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_right_x"):
    return (d[index].GetValue_double("overlap_upper_right_x") - *static_cast<double *>(v));
    break;
  case str2int("overlap_upper_right_y"):
    return (d[index].GetValue_double("overlap_upper_right_y") - *static_cast<double *>(v));
    break;
  case str2int("pixel_resolution"):
    return (d[index].GetValue_double("pixel_resolution") - *static_cast<double *>(v));
    break;
  case str2int("premarked"):
    return (d[index].GetValue_int("premarked") - *static_cast<int *>(v));
    break;
  case str2int("priority"):
    return (d[index].GetValue_double("priority") - *static_cast<double *>(v));
    break;
  case str2int("score"):
    return (d[index].GetValue_double("score") - *static_cast<double *>(v));
    break;
  case str2int("shared_mark_id"):
    return (d[index].GetValue_int("shared_mark_id") - *static_cast<int *>(v));
    break;
  case str2int("sub_type"):
    return (d[index].GetValue_string("sub_type").compare(*static_cast<string *>(v)));
    break;
  case str2int("submit_time"):
    return (d[index].GetValue_int("submit_time") - *static_cast<int *>(v));
    break;
  case str2int("sun_angle"):
    return (d[index].GetValue_double("sun_angle") - *static_cast<double *>(v));
    break;
  case str2int("type"):
    return (d[index].GetValue_string("type").compare(*static_cast<string *>(v)));
    break;
  case str2int("updated_at"):
    return (d[index].GetValue_string("updated_at").compare(*static_cast<string *>(v)));
    break;
  case str2int("upper_left_corner_x_status"):
    return (d[index].GetValue_string("upper_left_corner_x_status").compare(*static_cast<string *>(v)));
    break;
  case str2int("upper_left_corner_y_status"):
    return (d[index].GetValue_string("upper_left_corner_y_status").compare(*static_cast<string *>(v)));
    break;
  case str2int("upper_left_latitude"):
    return (d[index].GetValue_double("upper_left_latitude") - *static_cast<double *>(v));
    break;
  case str2int("upper_left_longitude"):
    return (d[index].GetValue_double("upper_left_longitude") - *static_cast<double *>(v));
    break;
  case str2int("upper_left_x"):
    return (d[index].GetValue_double("upper_left_x") - *static_cast<double *>(v));
    break;
  case str2int("upper_left_y"):
    return (d[index].GetValue_double("upper_left_y") - *static_cast<double *>(v));
    break;
  case str2int("upper_right_latitude"):
    return (d[index].GetValue_double("upper_right_latitude") - *static_cast<double *>(v));
    break;
  case str2int("upper_right_longitude"):
    return (d[index].GetValue_double("upper_right_longitude") - *static_cast<double *>(v));
    break;
  case str2int("upper_right_x"):
    return (d[index].GetValue_double("upper_right_x") - *static_cast<double *>(v));
    break;
  case str2int("upper_right_y"):
    return (d[index].GetValue_double("upper_right_y") - *static_cast<double *>(v));
    break;
  case str2int("width"):
    return (d[index].GetValue_int("width") - *static_cast<int *>(v));
    break;
  case str2int("x"):
    return (d[index].GetValue_double("x") - *static_cast<double *>(v));
    break;
  case str2int("x_relative"):
    return (d[index].GetValue_int("x_relative") - *static_cast<int *>(v));
    break;
  case str2int("y"):
    return (d[index].GetValue_double("y") - *static_cast<double *>(v));
    break;
  case str2int("y_relative"):
    return (d[index].GetValue_int("y_relative") - *static_cast<int *>(v));
    break;
  }

  return 0;
}

template <typename T>
int SearchData<T>::BinarySearch(std::vector <T> &d, int m, int n, std::string f, void *v)
{
  if(n >= m)
  {
    /***********************************/
    /* Calculate value of middle index */
    /***********************************/
    int midpoint = m+(n-m)/2;
    
    /****************************************************/
    /* Compare wanted value to value of middle element. */
    /* If equal, return index of middle element.        */
    /****************************************************/
    if(EqualityComparison(d, midpoint, f, v))
    {
      return midpoint;
    }

    /**************************************************/
    /* If value of the middle element is smaller than */
    /* the wanted value, then the wanted value must   */
    /* reside in the right portion of the array.      */
    /**************************************************/
    if(LessThanComparison(d, midpoint, f, v))
    {
      return BinarySearch(d, midpoint+1, n, f, v);
    }

    /*************************************************/
    /* If value of the middle element is larger than */
    /* the wanted value, then the wanted value must  */
    /* reside in the left portion of the array.      */
    /*************************************************/
    if(GreaterThanComparison(d, midpoint, f, v))
    {
      return BinarySearch(d, m, midpoint-1, f, v);
    }
  }

  /***********************************************************/
  /* If value is not present in array, return negative index */
  /***********************************************************/
  return -1;
}

template <typename T>
int SearchData<T>::FirstNearestValue(std::vector <T> &d, int m, int n, std::string f, void *v)
{
  /*************************************************/
  /* Declaration/Initialization of class variables */
  /*************************************************/
  double diff1;
  double diff2;
  
  if((n-m) > 1)
  {
    /******************************************************************/
    /* Calculate index at boundary between first and second quantile. */
    /* Calculate index at boundary between second and third quantile. */
    /******************************************************************/
    int boundary1 = m+(n-m)/3;
    int boundary2 = m+2*(n-m)/3;
    
    /************************************************************************/
    /* Calculate difference between value to value at the index of boundary */
    /* one and repeat for the value at the index of boundary two            */
    /************************************************************************/  
    diff1 = Difference(d, boundary1, f, v);
    diff2 = Difference(d, boundary2, f, v);
    
    /*************************************************/
    /* If either differences equal zero, simply find */
    /* the first occurence of value in data set      */
    /*************************************************/
    if((diff1 == 0) || (diff2 == 0))
    {
      return FirstOccurence(d, m, n, f, v);
    }
  
    /**************************************/
    /* If the first difference is greater */
    /* than zero, examine first quantile  */
    /**************************************/
    if(diff1 > 0)
    {
      return FirstNearestValue(d, 0, boundary1-1, f, v);
    }

    /*************************************/
    /* If the second difference is less  */
    /* than zero, examine third quantile */
    /**************************************/
    if(diff2 < 0)
    {
      return FirstNearestValue(d, boundary2+1, n, f, v);
    }

    /*********************************************/
    /* If zero lies between the two differences, */
    /* then examine second quantile              */
    /*********************************************/
    if((diff1 < 0) && (diff2 > 0))
    {
      return FirstNearestValue(d, boundary1+1, boundary2-1, f, v);
    }
  }

  /************************************************************/
  /* Calculate difference between value to value at the index */
  /* of m one and repeat for the value at the index of n      */
  /************************************************************/
  diff1 = Difference(d, m, f, v);
  diff2 = Difference(d, n, f, v);
  
  return (diff1 < diff2) ? FirstOccurence(d, m, n, f, d[m].GetValue(f)) : FirstOccurence(d, m, n, f, d[n].GetValue(f));
}

template <typename T>
int SearchData<T>::FirstOccurence(std::vector <T> &d, int m, int n, std::string f, void *v)
{
  if((n-m) > 1)
  {
    /***********************************************************/
    /* Find midpoint between upper and lower bounding indicies */
    /***********************************************************/
    int midpoint = m+(n-m)/2;

    /*********************************************************/
    /* Compare value of midpoint element to reference value. */
    /* If less than reference value, move lowerbounding      */
    /* index to midpoint position. If equal to searched      */
    /* value, move upperbounding index to midpoint position  */
    /*********************************************************/
    if(LessThanComparison(d, midpoint, f, v))
    {
      return FirstOccurence(d, midpoint, n, f, v);
    }
    else
    {
      return FirstOccurence(d, m, midpoint, f, v);
    }
  }

  /*********************************************************/
  /* Check to see if quantities at indicies m or n matches */
  /* reference value when indicies are one unit apart      */
  /*********************************************************/
  if(EqualityComparison(d, m, f, v))
  {
    return m;
  }
  if(EqualityComparison(d, n, f, v))
  {
    return n;
  }

  return -1;
}

template <typename T>
int SearchData<T>::LastNearestValue(std::vector <T> &d, int m, int n, std::string f, void *v)
{
  /*************************************************/
  /* Declaration/Initialization of class variables */
  /*************************************************/
  double diff1;
  double diff2;
  
  if((n-m) > 1)
  {
    /******************************************************************/
    /* Calculate index at boundary between first and second quantile. */
    /* Calculate index at boundary between second and third quantile. */
    /******************************************************************/
    int boundary1 = m+(n-m)/3;
    int boundary2 = m+2*(n-m)/3;
    
    /************************************************************************/
    /* Calculate difference between value to value at the index of boundary */
    /* one and repeat for the value at the index of boundary two            */
    /************************************************************************/  
    diff1 = Difference(d, boundary1, f, v);
    diff2 = Difference(d, boundary2, f, v);
    
    /*************************************************/
    /* If either differences equal zero, simply find */
    /* the first occurence of value in data set      */
    /*************************************************/
    if((diff1 == 0) || (diff2 == 0))
    {
      return LastOccurence(d, m, n, f, v);
    }
  
    /**************************************/
    /* If the first difference is greater */
    /* than zero, examine first quantile  */
    /**************************************/
    if(diff1 > 0)
    {
      return LastNearestValue(d, 0, boundary1-1, f, v);
    }

    /*************************************/
    /* If the second difference is less  */
    /* than zero, examine third quantile */
    /**************************************/
    if(diff2 < 0)
    {
      return LastNearestValue(d, boundary2+1, n, f, v);
    }

    /*********************************************/
    /* If zero lies between the two differences, */
    /* then examine second quantile              */
    /*********************************************/
    if((diff1 < 0) && (diff2 > 0))
    {
      return LastNearestValue(d, boundary1+1, boundary2-1, f, v);
    }
  }

  /************************************************************/
  /* Calculate difference between value to value at the index */
  /* of m one and repeat for the value at the index of n      */
  /************************************************************/
  diff1 = Difference(d, m, f, v);
  diff2 = Difference(d, n, f, v);
  
  return (diff1 < diff2) ? LastOccurence(d, m, n, f, d[m].GetValue(f)) : LastOccurence(d, m, n, f, d[n].GetValue(f));
}


template <typename T>
int SearchData<T>::LastOccurence(std::vector <T> &d, int m, int n, std::string f, void *v)
{
  if((n-m) > 1)
  {
    /***********************************************************/
    /* Find midpoint between upper and lower bounding indicies */
    /***********************************************************/
    int midpoint = m+(n-m)/2;
    
    /********************************************************/
    /* Compare value of midpoint element to searched value. */
    /* If less than searched value, move lowerbounding      */
    /* index to midpoint position. If equal to searched     */
    /* value, move upperbounding index to midpoint position */
    /********************************************************/
    if(GreaterThanComparison(d, midpoint, f, v))
    {
      return LastOccurence(d, m, midpoint, f, v);
    }
    else
    {
      return LastOccurence(d, midpoint, n, f, v);
    }
  }

  /*********************************************************/
  /* Check to see if quantities at indicies m or n matches */
  /* reference value when indicies are one unit apart      */
  /*********************************************************/
  if(EqualityComparison(d, n, f, v))
  {
    return n;
  }
  if(EqualityComparison(d, m, f, v))
  {
    return m;
  }

  return -1;  
}

#endif
