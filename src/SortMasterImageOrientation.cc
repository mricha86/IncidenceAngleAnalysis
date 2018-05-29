#include "SortMasterImageOrientation.h"

using namespace std;

SortMasterImageOrientation::SortMasterImageOrientation(vector <MasterImageOrientation> &MASTERIMAGEORIENTATIONS, string FIELD)
{
  field = FIELD;
  masterimageorientations = MASTERIMAGEORIENTATIONS;
}

bool SortMasterImageOrientation::cmp_by_name(MasterImageOrientation &a, MasterImageOrientation &b)
{
  return (a.GetName() < b.GetName());
}

bool SortMasterImageOrientation::cmp_by_upper_left_latitude(MasterImageOrientation &a, MasterImageOrientation &b)
{
  return (a.GetUpper_left_latitude() < b.GetUpper_left_latitude());
}

bool SortMasterImageOrientation::cmp_by_upper_left_longitude(MasterImageOrientation &a, MasterImageOrientation &b)
{
  return (a.GetUpper_left_longitude() < b.GetUpper_left_longitude());
}

int SortMasterImageOrientation::GetFieldValue()
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("name") == 0)
  {
    return 1;
  }
  if(field.compare("upper_left_latitude") == 0)
  {
    return 2;
  }
  if(field.compare("upper_left_longitude") == 0)
  {
    return 3;
  }

  return 0;
}

vector <MasterImageOrientation> SortMasterImageOrientation::GetMasterImageOrientations()
{
  return masterimageorientations;
}

void SortMasterImageOrientation::arrange()
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
      sort(masterimageorientations.begin(), masterimageorientations.end(), cmp_by_name);
      break;
    }
    case 2:
    {
      sort(masterimageorientations.begin(), masterimageorientations.end(), cmp_by_upper_left_latitude);
      break;
    }
    case 3:
    {
      sort(masterimageorientations.begin(), masterimageorientations.end(), cmp_by_upper_left_longitude);
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
