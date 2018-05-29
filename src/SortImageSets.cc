#include "SortImageSets.h"

using namespace std;

SortImageSets::SortImageSets(vector <ImageSets> &IMAGESETS, string FIELD)
{
  field = FIELD;
  imagesets = IMAGESETS;
}

bool SortImageSets::cmp_by_application_id(ImageSets &a, ImageSets &b)
{
  return (a.GetApplication_id() < b.GetApplication_id());
}

bool SortImageSets::cmp_by_created_at(ImageSets &a, ImageSets &b)
{
  return (a.GetCreated_at() < b.GetCreated_at());
}

bool SortImageSets::cmp_by_description(ImageSets &a, ImageSets &b)
{
  return (a.GetDescription() < b.GetDescription());
}

bool SortImageSets::cmp_by_details(ImageSets &a, ImageSets &b)
{
  return (a.GetDetails() < b.GetDetails());
}

bool SortImageSets::cmp_by_height(ImageSets &a, ImageSets &b)
{
  return (a.GetHeight() < b.GetHeight());
}

bool SortImageSets::cmp_by_horizontal_resolution(ImageSets &a, ImageSets &b)
{
  return (a.GetHorizontal_resolution() < b.GetHorizontal_resolution());
}

bool SortImageSets::cmp_by_id(ImageSets &a, ImageSets &b)
{
  return (a.GetId() < b.GetId());
}

bool SortImageSets::cmp_by_maximum_latitude(ImageSets &a, ImageSets &b)
{
  return (a.GetMaximum_latitude() < b.GetMaximum_latitude());
}

bool SortImageSets::cmp_by_maximum_longitude(ImageSets &a, ImageSets &b)
{
  return (a.GetMaximum_longitude() < b.GetMaximum_longitude());
}

bool SortImageSets::cmp_by_minimum_latitude(ImageSets &a, ImageSets &b)
{
  return (a.GetMinimum_latitude() < b.GetMinimum_latitude());
}

bool SortImageSets::cmp_by_minimum_longitude(ImageSets &a, ImageSets &b)
{
  return (a.GetMinimum_longitude() < b.GetMinimum_longitude());
}

bool SortImageSets::cmp_by_name(ImageSets &a, ImageSets &b)
{
  return (a.GetName() < b.GetName());
}

bool SortImageSets::cmp_by_physical_height(ImageSets &a, ImageSets &b)
{
  return (a.GetPhysical_height() < b.GetPhysical_height());
}

bool SortImageSets::cmp_by_physical_width(ImageSets &a, ImageSets &b)
{
  return (a.GetPhysical_width() < b.GetPhysical_width());
}

bool SortImageSets::cmp_by_pixel_resolution(ImageSets &a, ImageSets &b)
{
  return (a.GetPixel_resolution() < b.GetPixel_resolution());
}

bool SortImageSets::cmp_by_priority(ImageSets &a, ImageSets &b)
{
  return (a.GetPriority() < b.GetPriority());
}

bool SortImageSets::cmp_by_sun_angle(ImageSets &a, ImageSets &b)
{
  return (a.GetSun_angle() < b.GetSun_angle());
}

bool SortImageSets::cmp_by_updated_at(ImageSets &a, ImageSets &b)
{
  return (a.GetUpdated_at() < b.GetUpdated_at());
}

bool SortImageSets::cmp_by_upper_left_latitude(ImageSets &a, ImageSets &b)
{
  return (a.GetUpper_left_latitude() < b.GetUpper_left_latitude());
}

bool SortImageSets::cmp_by_upper_left_longitude(ImageSets &a, ImageSets &b)
{
  return (a.GetUpper_left_longitude() < b.GetUpper_left_longitude());
}

bool SortImageSets::cmp_by_vertical_resolution(ImageSets &a, ImageSets &b)
{
  return (a.GetVertical_resolution() < b.GetVertical_resolution());
}

bool SortImageSets::cmp_by_width(ImageSets &a, ImageSets &b)
{
  return (a.GetWidth() < b.GetWidth());
}

bool SortImageSets::cmp_by_x_high(ImageSets &a, ImageSets &b)
{
  return (a.GetX_high() < b.GetX_high());
}

bool SortImageSets::cmp_by_x_low(ImageSets &a, ImageSets &b)
{
  return (a.GetX_low() < b.GetX_low());
}

bool SortImageSets::cmp_by_x_origin(ImageSets &a, ImageSets &b)
{
  return (a.GetX_origin() < b.GetX_origin());
}

bool SortImageSets::cmp_by_y_high(ImageSets &a, ImageSets &b)
{
  return (a.GetY_high() < b.GetY_high());
}

bool SortImageSets::cmp_by_y_low(ImageSets &a, ImageSets &b)
{
  return (a.GetY_low() < b.GetY_low());
}

bool SortImageSets::cmp_by_y_origin(ImageSets &a, ImageSets &b)
{
  return (a.GetY_origin() < b.GetY_origin());
}

int SortImageSets::GetFieldValue()
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("application_id") == 0)
  {
    return 1;
  }
  if(field.compare("created_at") == 0)
  {
    return 2;
  }
  if(field.compare("description") == 0)
  {
    return 3;
  }
  if(field.compare("details") == 0)
  {
    return 4;
  }
  if(field.compare("height") == 0)
  {
    return 5;
  }
  if(field.compare("horizontal_resolution") == 0)
  {
    return 6;
  }
  if(field.compare("id") == 0)
  {
    return 7;
  }
  if(field.compare("maxium_latitude") == 0)
  {
    return 8;
  }
  if(field.compare("maxium_longitude") == 0)
  {
    return 9;
  }
  if(field.compare("minium_latitude") == 0)
  {
    return 10;
  }
  if(field.compare("minium_longitude") == 0)
  {
    return 11;
  }
  if(field.compare("name") == 0)
  {
    return 12;
  }
  if(field.compare("physical_height") == 0)
  {
    return 13;
  }
  if(field.compare("physical_width") == 0)
  {
    return 14;
  }
  if(field.compare("pixel_resolution") == 0)
  {
    return 15;
  }
  if(field.compare("priority") == 0)
  {
    return 16;
  }
  if(field.compare("sun_angle") == 0)
  {
    return 17;
  }
  if(field.compare("updated_at") == 0)
  {
    return 18;
  }
  if(field.compare("upper_left_latitude") == 0)
  {
    return 19;
  }
  if(field.compare("upper_left_longitude") == 0)
  {
    return 20;
  }
  if(field.compare("vertical_resolution") == 0)
  {
    return 21;
  }
  if(field.compare("width") == 0)
  {
    return 22;
  }
  if(field.compare("x_high") == 0)
  {
    return 23;
  }
  if(field.compare("x_low") == 0)
  {
    return 24;
  }
  if(field.compare("x_origin") == 0)
  {
    return 25;
  }
  if(field.compare("y_high") == 0)
  {
    return 26;
  }
  if(field.compare("y_low") == 0)
  {
    return 27;
  }
  if(field.compare("y_origin") == 0)
  {
    return 28;
  }


  return 0;
}

vector <ImageSets> SortImageSets::GetImageSets()
{
  return imagesets;
}

void SortImageSets::arrange()
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
      sort(imagesets.begin(), imagesets.end(), cmp_by_application_id);
      break;
    }
    case 2:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_created_at);
      break;
    }
    case 3:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_description);
      break;
    }
    case 4:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_details);
      break;
    }
    case 5:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_height);
      break;
    }
    case 6:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_horizontal_resolution);
      break;
    }
    case 7:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_id);
      break;
    }
    case 8:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_maximum_latitude);
      break;
    }
    case 9:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_maximum_longitude);
      break;
    }
    case 10:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_minimum_latitude);
      break;
    }
    case 11:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_minimum_longitude);
      break;
    }
    case 12:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_name);
      break;
    }
    case 13:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_physical_height);
      break;
    }
    case 14:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_physical_width);
      break;
    }
    case 15:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_pixel_resolution);
      break;
    }
    case 16:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_priority);
      break;
    }
    case 17:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_sun_angle);
      break;
    }
    case 18:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_updated_at);
      break;
    }
    case 19:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_upper_left_latitude);
      break;
    }
    case 20:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_upper_left_longitude);
      break;
    }
    case 21:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_vertical_resolution);
      break;
    }
    case 22:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_width);
      break;
    }
    case 23:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_x_high);
      break;
    }
    case 24:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_x_low);
      break;
    }
    case 25:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_x_origin);
      break;
    }
    case 26:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_y_high);
      break;
    }
    case 27:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_y_low);
      break;
    }
    case 28:
    {
      sort(imagesets.begin(), imagesets.end(), cmp_by_y_origin);
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
