#include "PixelResolution.h"

using namespace std;

PixelResolution::PixelResolution(string NAME, double VERTICAL_RESOLUTION, double HORIZONTAL_RESOLUTION)
{
  horizontal_resolution = HORIZONTAL_RESOLUTION;
  name = NAME;
  vertical_resolution = VERTICAL_RESOLUTION;
}

double PixelResolution::GetHorizontal_resolution()
{
  return horizontal_resolution;
}

double PixelResolution::GetVertical_resolution()
{
  return vertical_resolution;
}

string PixelResolution::GetName()
{
  return name;
}

void * PixelResolution::GetValue(string field)
{
  if(field.compare("name") == 0)
  {
    return &name;
  }
  if(field.compare("horizontal_resolution") == 0)
  {
    return &horizontal_resolution;
  }
  if(field.compare("vertical_resolution") == 0)
  {
    return &vertical_resolution;
  }

  return NULL;
}
