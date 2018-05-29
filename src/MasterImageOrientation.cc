#include "MasterImageOrientation.h"

using namespace std;

MasterImageOrientation::MasterImageOrientation(string NAME, string UPPERLEFTLATITUDE, string UPPERLEFTLONGITUDE)
{
  name = NAME;
  upper_left_latitude = UPPERLEFTLATITUDE;
  upper_left_longitude = UPPERLEFTLONGITUDE;
}

string MasterImageOrientation::GetName()
{
  return name;
}

string MasterImageOrientation::GetUpper_left_latitude()
{
  return upper_left_latitude;
}

string MasterImageOrientation::GetUpper_left_longitude()
{
  return upper_left_longitude;
}

void * MasterImageOrientation::GetValue(string field)
{
  if(field.compare("name") == 0)
  {
    return &name;
  }
  if(field.compare("upper_left_angle") == 0)
  {
    return &upper_left_latitude;
  }
  if(field.compare("upper_left_longitude") == 0)
  {
    return &upper_left_longitude;
  }

  return NULL;
}
