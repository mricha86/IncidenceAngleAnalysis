#include "SearchImageSets.h"

using namespace std;

bool SearchImageSets::EqualityComparison(vector <ImageSets> &imagesets, int index, string field, void *value)
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("application_id") == 0)
  {
    return (imagesets[index].GetApplication_id() == *static_cast<int *>(value));
  }
  if(field.compare("created_at") == 0)
  {
    return (imagesets[index].GetCreated_at().compare(*static_cast<string *>(value)) == 0);
  }
  if(field.compare("description") == 0)
  {
    return (imagesets[index].GetDescription().compare(*static_cast<string *>(value)) == 0);
  }
  if(field.compare("details") == 0)
  {
    return (imagesets[index].GetDetails().compare(*static_cast<string *>(value)) == 0);
  }
  if(field.compare("height") == 0)
  {
    return (imagesets[index].GetHeight() == *static_cast<int *>(value));
  }
  if(field.compare("id") == 0)
  {
    return (imagesets[index].GetId() == *static_cast<int *>(value));
  }
  if(field.compare("lower_left_latitude") == 0)
  {
    return (imagesets[index].GetLower_left_latitude() == *static_cast<double *>(value));
  }
  if(field.compare("lower_left_longitude") == 0)
  {
    return (imagesets[index].GetLower_left_longitude() == *static_cast<double *>(value));
  }
  if(field.compare("lower_left_x") == 0)
  {
    return (imagesets[index].GetLower_left_x() == *static_cast<double *>(value));
  }
  if(field.compare("lower_left_y") == 0)
  {
    return (imagesets[index].GetLower_left_y() == *static_cast<double *>(value));
  }
  if(field.compare("lower_right_latitude") == 0)
  {
    return (imagesets[index].GetLower_right_latitude() == *static_cast<double *>(value));
  }
  if(field.compare("lower_right_longitude") == 0)
  {
    return (imagesets[index].GetLower_right_longitude() == *static_cast<double *>(value));
  }
  if(field.compare("lower_right_x") == 0)
  {
    return (imagesets[index].GetLower_right_x() == *static_cast<double *>(value));
  }
  if(field.compare("lower_right_y") == 0)
  {
    return (imagesets[index].GetLower_right_y() == *static_cast<double *>(value));
  }
  if(field.compare("maximum_latitude") == 0)
  {
    return (imagesets[index].GetMaximum_latitude() == *static_cast<double *>(value));
  }
  if(field.compare("maximum_longitude") == 0)
  {
    return (imagesets[index].GetMaximum_longitude() == *static_cast<double *>(value));
  }
  if(field.compare("maximum_x") == 0)
  {
    return (imagesets[index].GetMaximum_x() == *static_cast<double *>(value));
  }
  if(field.compare("maximum_y") == 0)
  {
    return (imagesets[index].GetMaximum_y() == *static_cast<double *>(value));
  }
  if(field.compare("minimum_latitude") == 0)
  {
    return (imagesets[index].GetMinimum_latitude() == *static_cast<double *>(value));
  }
  if(field.compare("minimum_longitude") == 0)
  {
    return (imagesets[index].GetMinimum_longitude() == *static_cast<double *>(value));
  }
  if(field.compare("minimum_x") == 0)
  {
    return (imagesets[index].GetMinimum_x() == *static_cast<double *>(value));
  }
  if(field.compare("minimum_y") == 0)
  {
    return (imagesets[index].GetMinimum_y() == *static_cast<double *>(value));
  }
  if(field.compare("name") == 0)
  {
    return (imagesets[index].GetName().compare(*static_cast<string *>(value)) == 0);
  }
  if(field.compare("pixel_resolution") == 0)
  {
    return (imagesets[index].GetPixel_resolution() == *static_cast<double *>(value));
  }
  if(field.compare("priority") == 0)
  {
    return (imagesets[index].GetPriority() == *static_cast<double *>(value));
  }  
  if(field.compare("sun_angle") == 0)
  {
    return (imagesets[index].GetSun_angle() == *static_cast<double *>(value));
  }
  if(field.compare("updated_at") == 0)
  {
    return (imagesets[index].GetUpdated_at().compare(*static_cast<string *>(value)) == 0);
  }
  if(field.compare("upper_left_corner_x_status") == 0)
  {
    return (imagesets[index].GetUpper_left_corner_x_status().compare(*static_cast<string *>(value)) == 0);
  }
  if(field.compare("upper_left_corner_y_status") == 0)
  {
    return (imagesets[index].GetUpper_left_corner_y_status().compare(*static_cast<string *>(value)) == 0);
  }
  if(field.compare("upper_left_latitude") == 0)
  {
    return (imagesets[index].GetUpper_left_latitude() == *static_cast<double *>(value));
  }
  if(field.compare("upper_left_longitude") == 0)
  {
    return (imagesets[index].GetUpper_left_longitude() == *static_cast<double *>(value));
  }
  if(field.compare("upper_left_x") == 0)
  {
    return (imagesets[index].GetUpper_left_x() == *static_cast<double *>(value));
  }
  if(field.compare("upper_left_y") == 0)
  {
    return (imagesets[index].GetUpper_left_y() == *static_cast<double *>(value));
  }
  if(field.compare("upper_right_latitude") == 0)
  {
    return (imagesets[index].GetUpper_right_latitude() == *static_cast<double *>(value));
  }
  if(field.compare("upper_right_longitude") == 0)
  {
    return (imagesets[index].GetUpper_right_longitude() == *static_cast<double *>(value));
  }
  if(field.compare("upper_right_x") == 0)
  {
    return (imagesets[index].GetUpper_right_x() == *static_cast<double *>(value));
  }
  if(field.compare("upper_right_y") == 0)
  {
    return (imagesets[index].GetUpper_right_y() == *static_cast<double *>(value));
  }
  if(field.compare("width") == 0)
  {
    return (imagesets[index].GetWidth() == *static_cast<int *>(value));
  }

  return false;
}

bool SearchImageSets::GreaterThanComparison(vector <ImageSets> &imagesets, int index, string field, void *value)
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("application_id") == 0)
  {
    return (imagesets[index].GetApplication_id() > *static_cast<int *>(value));
  }
  if(field.compare("created_at") == 0)
  {
    return (imagesets[index].GetCreated_at() > *static_cast<string *>(value));
  }
  if(field.compare("description") == 0)
  {
    return (imagesets[index].GetDescription() > *static_cast<string *>(value));
  }
  if(field.compare("details") == 0)
  {
    return (imagesets[index].GetDetails() > *static_cast<string *>(value));
  }
  if(field.compare("height") == 0)
  {
    return (imagesets[index].GetHeight() > *static_cast<int *>(value));
  }
  if(field.compare("id") == 0)
  {
    return (imagesets[index].GetId() > *static_cast<int *>(value));
  }
  if(field.compare("lower_left_latitude") == 0)
  {
    return (imagesets[index].GetLower_left_latitude() > *static_cast<double *>(value));
  }
  if(field.compare("lower_left_longitude") == 0)
  {
    return (imagesets[index].GetLower_left_longitude() > *static_cast<double *>(value));
  }
  if(field.compare("lower_left_x") == 0)
  {
    return (imagesets[index].GetLower_left_x() > *static_cast<double *>(value));
  }
  if(field.compare("lower_left_y") == 0)
  {
    return (imagesets[index].GetLower_left_y() > *static_cast<double *>(value));
  }
  if(field.compare("lower_right_latitude") == 0)
  {
    return (imagesets[index].GetLower_right_latitude() > *static_cast<double *>(value));
  }
  if(field.compare("lower_right_longitude") == 0)
  {
    return (imagesets[index].GetLower_right_longitude() > *static_cast<double *>(value));
  }
  if(field.compare("lower_right_x") == 0)
  {
    return (imagesets[index].GetLower_right_x() > *static_cast<double *>(value));
  }
  if(field.compare("lower_right_y") == 0)
  {
    return (imagesets[index].GetLower_right_y() > *static_cast<double *>(value));
  }
  if(field.compare("maximum_latitude") == 0)
  {
    return (imagesets[index].GetMaximum_latitude() > *static_cast<double *>(value));
  }
  if(field.compare("maximum_longitude") == 0)
  {
    return (imagesets[index].GetMaximum_longitude() > *static_cast<double *>(value));
  }
  if(field.compare("maximum_x") == 0)
  {
    return (imagesets[index].GetMaximum_x() > *static_cast<double *>(value));
  }
  if(field.compare("maximum_y") == 0)
  {
    return (imagesets[index].GetMaximum_y() > *static_cast<double *>(value));
  }
  if(field.compare("minimum_latitude") == 0)
  {
    return (imagesets[index].GetMinimum_latitude() > *static_cast<double *>(value));
  }
  if(field.compare("minimum_longitude") == 0)
  {
    return (imagesets[index].GetMinimum_longitude() > *static_cast<double *>(value));
  }
  if(field.compare("minimum_x") == 0)
  {
    return (imagesets[index].GetMinimum_x() > *static_cast<double *>(value));
  }
  if(field.compare("minimum_y") == 0)
  {
    return (imagesets[index].GetMinimum_y() > *static_cast<double *>(value));
  }
  if(field.compare("name") == 0)
  {
    return (imagesets[index].GetName() > *static_cast<string *>(value));
  }
  if(field.compare("pixel_resolution") == 0)
  {
    return (imagesets[index].GetPixel_resolution() > *static_cast<double *>(value));
  }
  if(field.compare("priority") == 0)
  {
    return (imagesets[index].GetPriority() > *static_cast<double *>(value));
  }  
  if(field.compare("sun_angle") == 0)
  {
    return (imagesets[index].GetSun_angle() > *static_cast<double *>(value));
  }
  if(field.compare("updated_at") == 0)
  {
    return (imagesets[index].GetUpdated_at() > *static_cast<string *>(value));
  }
  if(field.compare("upper_left_corner_x_status") == 0)
  {
    return (imagesets[index].GetUpper_left_corner_x_status() > *static_cast<string *>(value));
  }
  if(field.compare("upper_left_corner_y_status") == 0)
  {
    return (imagesets[index].GetUpper_left_corner_y_status() > *static_cast<string *>(value));
  }
  if(field.compare("upper_left_latitude") == 0)
  {
    return (imagesets[index].GetUpper_left_latitude() > *static_cast<double *>(value));
  }
  if(field.compare("upper_left_longitude") == 0)
  {
    return (imagesets[index].GetUpper_left_longitude() > *static_cast<double *>(value));
  }
  if(field.compare("upper_left_x") == 0)
  {
    return (imagesets[index].GetUpper_left_x() > *static_cast<double *>(value));
  }
  if(field.compare("upper_left_y") == 0)
  {
    return (imagesets[index].GetUpper_left_y() > *static_cast<double *>(value));
  }
  if(field.compare("upper_right_latitude") == 0)
  {
    return (imagesets[index].GetUpper_right_latitude() > *static_cast<double *>(value));
  }
  if(field.compare("upper_right_longitude") == 0)
  {
    return (imagesets[index].GetUpper_right_longitude() > *static_cast<double *>(value));
  }
  if(field.compare("upper_right_x") == 0)
  {
    return (imagesets[index].GetUpper_right_x() > *static_cast<double *>(value));
  }
  if(field.compare("upper_right_y") == 0)
  {
    return (imagesets[index].GetUpper_right_y() > *static_cast<double *>(value));
  }
  if(field.compare("width") == 0)
  {
    return (imagesets[index].GetWidth() > *static_cast<int *>(value));
  }

  return false;
}

bool SearchImageSets::LessThanComparison(vector <ImageSets> &imagesets, int index, string field, void *value)
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("application_id") == 0)
  {
    return (imagesets[index].GetApplication_id() < *static_cast<int *>(value));
  }
  if(field.compare("created_at") == 0)
  {
    return (imagesets[index].GetCreated_at() < *static_cast<string *>(value));
  }
  if(field.compare("description") == 0)
  {
    return (imagesets[index].GetDescription() < *static_cast<string *>(value));
  }
  if(field.compare("details") == 0)
  {
    return (imagesets[index].GetDetails() < *static_cast<string *>(value));
  }
  if(field.compare("height") == 0)
  {
    return (imagesets[index].GetHeight() < *static_cast<int *>(value));
  }
  if(field.compare("id") == 0)
  {
    return (imagesets[index].GetId() < *static_cast<int *>(value));
  }
  if(field.compare("lower_left_latitude") == 0)
  {
    return (imagesets[index].GetLower_left_latitude() < *static_cast<double *>(value));
  }
  if(field.compare("lower_left_longitude") == 0)
  {
    return (imagesets[index].GetLower_left_longitude() < *static_cast<double *>(value));
  }
  if(field.compare("lower_left_x") == 0)
  {
    return (imagesets[index].GetLower_left_x() < *static_cast<double *>(value));
  }
  if(field.compare("lower_left_y") == 0)
  {
    return (imagesets[index].GetLower_left_y() < *static_cast<double *>(value));
  }
  if(field.compare("lower_right_latitude") == 0)
  {
    return (imagesets[index].GetLower_right_latitude() < *static_cast<double *>(value));
  }
  if(field.compare("lower_right_longitude") == 0)
  {
    return (imagesets[index].GetLower_right_longitude() < *static_cast<double *>(value));
  }
  if(field.compare("lower_right_x") == 0)
  {
    return (imagesets[index].GetLower_right_x() < *static_cast<double *>(value));
  }
  if(field.compare("lower_right_y") == 0)
  {
    return (imagesets[index].GetLower_right_y() < *static_cast<double *>(value));
  }
  if(field.compare("maximum_latitude") == 0)
  {
    return (imagesets[index].GetMaximum_latitude() < *static_cast<double *>(value));
  }
  if(field.compare("maximum_longitude") == 0)
  {
    return (imagesets[index].GetMaximum_longitude() < *static_cast<double *>(value));
  }
  if(field.compare("maximum_x") == 0)
  {
    return (imagesets[index].GetMaximum_x() < *static_cast<double *>(value));
  }
  if(field.compare("maximum_y") == 0)
  {
    return (imagesets[index].GetMaximum_y() < *static_cast<double *>(value));
  }
  if(field.compare("minimum_latitude") == 0)
  {
    return (imagesets[index].GetMinimum_latitude() < *static_cast<double *>(value));
  }
  if(field.compare("minimum_longitude") == 0)
  {
    return (imagesets[index].GetMinimum_longitude() < *static_cast<double *>(value));
  }
  if(field.compare("minimum_x") == 0)
  {
    return (imagesets[index].GetMinimum_x() < *static_cast<double *>(value));
  }
  if(field.compare("minimum_y") == 0)
  {
    return (imagesets[index].GetMinimum_y() < *static_cast<double *>(value));
  }
  if(field.compare("name") == 0)
  {
    return (imagesets[index].GetName() < *static_cast<string *>(value));
  }
  if(field.compare("pixel_resolution") == 0)
  {
    return (imagesets[index].GetPixel_resolution() < *static_cast<double *>(value));
  }
  if(field.compare("priority") == 0)
  {
    return (imagesets[index].GetPriority() < *static_cast<double *>(value));
  }  
  if(field.compare("sun_angle") == 0)
  {
    return (imagesets[index].GetSun_angle() < *static_cast<double *>(value));
  }
  if(field.compare("updated_at") == 0)
  {
    return (imagesets[index].GetUpdated_at() < *static_cast<string *>(value));
  }
  if(field.compare("upper_left_corner_x_status") == 0)
  {
    return (imagesets[index].GetUpper_left_corner_x_status() < *static_cast<string *>(value));
  }
  if(field.compare("upper_left_corner_y_status") == 0)
  {
    return (imagesets[index].GetUpper_left_corner_y_status() < *static_cast<string *>(value));
  }
  if(field.compare("upper_left_latitude") == 0)
  {
    return (imagesets[index].GetUpper_left_latitude() < *static_cast<double *>(value));
  }
  if(field.compare("upper_left_longitude") == 0)
  {
    return (imagesets[index].GetUpper_left_longitude() < *static_cast<double *>(value));
  }
  if(field.compare("upper_left_x") == 0)
  {
    return (imagesets[index].GetUpper_left_x() < *static_cast<double *>(value));
  }
  if(field.compare("upper_left_y") == 0)
  {
    return (imagesets[index].GetUpper_left_y() < *static_cast<double *>(value));
  }
  if(field.compare("upper_right_latitude") == 0)
  {
    return (imagesets[index].GetUpper_right_latitude() < *static_cast<double *>(value));
  }
  if(field.compare("upper_right_longitude") == 0)
  {
    return (imagesets[index].GetUpper_right_longitude() < *static_cast<double *>(value));
  }
  if(field.compare("upper_right_x") == 0)
  {
    return (imagesets[index].GetUpper_right_x() < *static_cast<double *>(value));
  }
  if(field.compare("upper_right_y") == 0)
  {
    return (imagesets[index].GetUpper_right_y() < *static_cast<double *>(value));
  }
  if(field.compare("width") == 0)
  {
    return (imagesets[index].GetWidth() < *static_cast<int *>(value));
  }

  return false;
}

double SearchImageSets::Difference(vector <ImageSets> &imagesets, int index, string field, void *value)
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("application_id") == 0)
  {
    return static_cast<double>(imagesets[index].GetApplication_id() - *static_cast<int *>(value));
  }
  if(field.compare("created_at") == 0)
  {
    return static_cast<double>(imagesets[index].GetCreated_at().compare(*static_cast<string *>(value)));
  }
  if(field.compare("description") == 0)
  {
    return static_cast<double>(imagesets[index].GetDescription().compare(*static_cast<string *>(value)));
  }
  if(field.compare("details") == 0)
  {
    return static_cast<double>(imagesets[index].GetDetails().compare(*static_cast<string *>(value)));
  }
  if(field.compare("height") == 0)
  {
    return static_cast<double>(imagesets[index].GetHeight() - *static_cast<int *>(value));
  }
  if(field.compare("id") == 0)
  {
    return static_cast<double>(imagesets[index].GetId() - *static_cast<int *>(value));
  }
  if(field.compare("lower_left_latitude") == 0)
  {
    return static_cast<double>(imagesets[index].GetLower_left_latitude() - *static_cast<double *>(value));
  }
  if(field.compare("lower_left_longitude") == 0)
  {
    return static_cast<double>(imagesets[index].GetLower_left_longitude() - *static_cast<double *>(value));
  }
  if(field.compare("lower_left_x") == 0)
  {
    return static_cast<double>(imagesets[index].GetLower_left_x() - *static_cast<double *>(value));
  }
  if(field.compare("lower_left_y") == 0)
  {
    return static_cast<double>(imagesets[index].GetLower_left_y() - *static_cast<double *>(value));
  }
  if(field.compare("lower_right_latitude") == 0)
  {
    return static_cast<double>(imagesets[index].GetLower_right_latitude() - *static_cast<double *>(value));
  }
  if(field.compare("lower_right_longitude") == 0)
  {
    return static_cast<double>(imagesets[index].GetLower_right_longitude() - *static_cast<double *>(value));
  }
  if(field.compare("lower_right_x") == 0)
  {
    return static_cast<double>(imagesets[index].GetLower_right_x() - *static_cast<double *>(value));
  }
  if(field.compare("lower_right_y") == 0)
  {
    return static_cast<double>(imagesets[index].GetLower_right_y() - *static_cast<double *>(value));
  }
  if(field.compare("maximum_latitude") == 0)
  {
    return static_cast<double>(imagesets[index].GetMaximum_latitude() - *static_cast<double *>(value));
  }
  if(field.compare("maximum_longitude") == 0)
  {
    return static_cast<double>(imagesets[index].GetMaximum_longitude() - *static_cast<double *>(value));
  }
  if(field.compare("maximum_x") == 0)
  {
    return static_cast<double>(imagesets[index].GetMaximum_x() - *static_cast<double *>(value));
  }
  if(field.compare("maximum_y") == 0)
  {
    return static_cast<double>(imagesets[index].GetMaximum_y() - *static_cast<double *>(value));
  }
  if(field.compare("minimum_latitude") == 0)
  {
    return static_cast<double>(imagesets[index].GetMinimum_latitude() - *static_cast<double *>(value));
  }
  if(field.compare("minimum_longitude") == 0)
  {
    return static_cast<double>(imagesets[index].GetMinimum_longitude() - *static_cast<double *>(value));
  }
  if(field.compare("minimum_x") == 0)
  {
    return static_cast<double>(imagesets[index].GetMinimum_x() - *static_cast<double *>(value));
  }
  if(field.compare("minimum_y") == 0)
  {
    return static_cast<double>(imagesets[index].GetMinimum_y() - *static_cast<double *>(value));
  }
  if(field.compare("name") == 0)
  {
    return static_cast<double>(imagesets[index].GetName().compare(*static_cast<string *>(value)));
  }
  if(field.compare("pixel_resolution") == 0)
  {
    return static_cast<double>(imagesets[index].GetPixel_resolution() - *static_cast<double *>(value));
  }
  if(field.compare("priority") == 0)
  {
    return static_cast<double>(imagesets[index].GetPriority() - *static_cast<double *>(value));
  }  
  if(field.compare("sun_angle") == 0)
  {
    return static_cast<double>(imagesets[index].GetSun_angle() - *static_cast<double *>(value));
  }
  if(field.compare("updated_at") == 0)
  {
    return static_cast<double>(imagesets[index].GetUpdated_at().compare(*static_cast<string *>(value)));
  }
  if(field.compare("upper_left_corner_x_status") == 0)
  {
    return static_cast<double>(imagesets[index].GetUpper_left_corner_x_status().compare(*static_cast<string *>(value)));
  }
  if(field.compare("upper_left_corner_y_status") == 0)
  {
    return static_cast<double>(imagesets[index].GetUpper_left_corner_y_status().compare(*static_cast<string *>(value)));
  }
  if(field.compare("upper_left_latitude") == 0)
  {
    return static_cast<double>(imagesets[index].GetUpper_left_latitude() - *static_cast<double *>(value));
  }
  if(field.compare("upper_left_longitude") == 0)
  {
    return static_cast<double>(imagesets[index].GetUpper_left_longitude() - *static_cast<double *>(value));
  }
  if(field.compare("upper_left_x") == 0)
  {
    return static_cast<double>(imagesets[index].GetUpper_left_x() - *static_cast<double *>(value));
  }
  if(field.compare("upper_left_y") == 0)
  {
    return static_cast<double>(imagesets[index].GetUpper_left_y() - *static_cast<double *>(value));
  }
  if(field.compare("upper_right_latitude") == 0)
  {
    return static_cast<double>(imagesets[index].GetUpper_right_latitude() - *static_cast<double *>(value));
  }
  if(field.compare("upper_right_longitude") == 0)
  {
    return static_cast<double>(imagesets[index].GetUpper_right_longitude() - *static_cast<double *>(value));
  }
  if(field.compare("upper_right_x") == 0)
  {
    return static_cast<double>(imagesets[index].GetUpper_right_x() - *static_cast<double *>(value));
  }
  if(field.compare("upper_right_y") == 0)
  {
    return static_cast<double>(imagesets[index].GetUpper_right_y() - *static_cast<double *>(value));
  }
  if(field.compare("width") == 0)
  {
    return static_cast<double>(imagesets[index].GetWidth() - *static_cast<int *>(value));
  }

  return false;
}

int SearchImageSets::BinarySearch(vector <ImageSets> &imagesets, int m, int n, string field, void *value)
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
    if(EqualityComparison(imagesets, midpoint, field, value))
    {
      return midpoint;
    }

    /**************************************************/
    /* If value of the middle element is smaller than */
    /* the wanted value, then the wanted value must   */
    /* reside in the right portion of the array.      */
    /**************************************************/
    if(LessThanComparison(imagesets, midpoint, field, value))
    {
      return BinarySearch(imagesets, midpoint+1, n, field, value);
    }

    /*************************************************/
    /* If value of the middle element is larger than */
    /* the wanted value, then the wanted value must  */
    /* reside in the left portion of the array.      */
    /*************************************************/
    if(GreaterThanComparison(imagesets, midpoint, field, value))
    {
      return BinarySearch(imagesets, m, midpoint-1, field, value);
    }
  }

  /***********************************************************/
  /* If value is not present in array, return negative index */
  /***********************************************************/
  return -1;
}

int SearchImageSets::FirstNearestValue(vector <ImageSets> &imagesets, int m, int n, string field, void *value)
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
    diff1 = Difference(imagesets, boundary1, field, value);
    diff2 = Difference(imagesets, boundary2, field, value);
    
    /*************************************************/
    /* If either differences equal zero, simply find */
    /* the first occurence of value in data set      */
    /*************************************************/
    if((diff1 == 0) || (diff2 == 0))
    {
      return FirstOccurence(imagesets, m, n, field, value);
    }
  
    /**************************************/
    /* If the first difference is greater */
    /* than zero, examine first quantile  */
    /**************************************/
    if(diff1 > 0)
    {
      return FirstNearestValue(imagesets, 0, boundary1-1, field, value);
    }

    /*************************************/
    /* If the second difference is less  */
    /* than zero, examine third quantile */
    /**************************************/
    if(diff2 < 0)
    {
      return FirstNearestValue(imagesets, boundary2+1, n, field, value);
    }

    /*********************************************/
    /* If zero lies between the two differences, */
    /* then examine second quantile              */
    /*********************************************/
    if((diff1 < 0) && (diff2 > 0))
    {
      return FirstNearestValue(imagesets, boundary1+1, boundary2-1, field, value);
    }
  }

  /************************************************************/
  /* Calculate difference between value to value at the index */
  /* of m one and repeat for the value at the index of n      */
  /************************************************************/
  diff1 = Difference(imagesets, m, field, value);
  diff2 = Difference(imagesets, n, field, value);
    
  return (diff1 < diff2) ? FirstOccurence(imagesets, m, n, field, imagesets[m].GetValue(field)) : FirstOccurence(imagesets, m, n, field, imagesets[n].GetValue(field));
}

int SearchImageSets::FirstOccurence(vector <ImageSets> &imagesets, int m, int n, string field, void *value)
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
    if(LessThanComparison(imagesets, midpoint, field, value))
    {
      return FirstOccurence(imagesets, midpoint, n, field, value);
    }
    else
    {
      return FirstOccurence(imagesets, m, midpoint, field, value);
    }
  }

  /*********************************************************/
  /* Check to see if quantities at indicies m or n matches */
  /* reference value when indicies are one unit apart      */
  /*********************************************************/
  if(EqualityComparison(imagesets, m, field, value))
  {
    return m;
  }
  if(EqualityComparison(imagesets, n, field, value))
  {
    return n;
  }

  return -1;
}

int SearchImageSets::LastNearestValue(vector <ImageSets> &imagesets, int m, int n, string field, void *value)
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
    diff1 = Difference(imagesets, boundary1, field, value);
    diff2 = Difference(imagesets, boundary2, field, value);
    
    /*************************************************/
    /* If either differences equal zero, simply find */
    /* the first occurence of value in data set      */
    /*************************************************/
    if((diff1 == 0) || (diff2 == 0))
    {
      return LastOccurence(imagesets, m, n, field, value);
    }
  
    /**************************************/
    /* If the first difference is greater */
    /* than zero, examine first quantile  */
    /**************************************/
    if(diff1 > 0)
    {
      return LastNearestValue(imagesets, 0, boundary1-1, field, value);
    }

    /*************************************/
    /* If the second difference is less  */
    /* than zero, examine third quantile */
    /**************************************/
    if(diff2 < 0)
    {
      return LastNearestValue(imagesets, boundary2+1, n, field, value);
    }

    /*********************************************/
    /* If zero lies between the two differences, */
    /* then examine second quantile              */
    /*********************************************/
    if((diff1 < 0) && (diff2 > 0))
    {
      return LastNearestValue(imagesets, boundary1+1, boundary2-1, field, value);
    }
  }

  /************************************************************/
  /* Calculate difference between value to value at the index */
  /* of m one and repeat for the value at the index of n      */
  /************************************************************/
  diff1 = Difference(imagesets, m, field, value);
  diff2 = Difference(imagesets, n, field, value);
    
  return (diff1 < diff2) ? LastOccurence(imagesets, m, n, field, imagesets[m].GetValue(field)) : LastOccurence(imagesets, m, n, field, imagesets[n].GetValue(field));
}


int SearchImageSets::LastOccurence(vector <ImageSets> &imagesets, int m, int n, string field, void *value)
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
    if(GreaterThanComparison(imagesets, midpoint, field, value))
    {
      return LastOccurence(imagesets, m, midpoint, field, value);
    }
    else
    {
      return LastOccurence(imagesets, midpoint, n, field, value);
    }
  }

  /*********************************************************/
  /* Check to see if quantities at indicies m or n matches */
  /* reference value when indicies are one unit apart      */
  /*********************************************************/
  if(EqualityComparison(imagesets, n, field, value))
  {
    return n;
  }
  if(EqualityComparison(imagesets, m, field, value))
  {
    return m;
  }

  return -1;  
}
