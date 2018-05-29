#include "SortPixelResolutions.h"

using namespace std;

SortPixelResolutions::SortPixelResolutions(vector <PixelResolution> &PIXELRESOLUTIONS, string FIELD)
{
  field = FIELD;
  pixelresolutions = PIXELRESOLUTIONS;
}

bool SortPixelResolutions::cmp_by_horizontal_resolution(PixelResolution &a, PixelResolution &b)
{
  return (a.GetHorizontal_resolution() < b.GetHorizontal_resolution());
}

bool SortPixelResolutions::cmp_by_name(PixelResolution &a, PixelResolution &b)
{
  return (a.GetName() < b.GetName());
}

bool SortPixelResolutions::cmp_by_vertical_resolution(PixelResolution &a, PixelResolution &b)
{
  return (a.GetVertical_resolution() < b.GetVertical_resolution());
}

int SortPixelResolutions::GetFieldValue()
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("name") == 0)
  {
    return 1;
  }
  if(field.compare("vertical_resolution") == 0)
  {
    return 2;
  }
  if(field.compare("horizontal_resolution") == 0)
  {
    return 3;
  }

  return 0;
}

vector <PixelResolution> SortPixelResolutions::GetPixelResolutions()
{
  return pixelresolutions;
}

void SortPixelResolutions::arrange()
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
      sort(pixelresolutions.begin(), pixelresolutions.end(), cmp_by_name);
      break;
    }
    case 2:
    {
      sort(pixelresolutions.begin(), pixelresolutions.end(), cmp_by_vertical_resolution);
      break;
    }
    case 3:
    {
      sort(pixelresolutions.begin(), pixelresolutions.end(), cmp_by_horizontal_resolution);
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
