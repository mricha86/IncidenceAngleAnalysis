#include "OverlappedImages.h"

using namespace std;

OverlappedImages::OverlappedImages()
{
}

OverlappedImages::OverlappedImages(int ID, int IMAGE1ID, string IMAGE1NAME, double IMAGE1ULX, double IMAGE1ULY, double IMAGE1URX, double IMAGE1URY, double IMAGE1LRX, double IMAGE1LRY, double IMAGE1LLX, double IMAGE1LLY, double IMAGE1AREA, double IMAGE1INCIDENCEANGLE, int IMAGE2ID, string IMAGE2NAME, double IMAGE2ULX, double IMAGE2ULY, double IMAGE2URX, double IMAGE2URY, double IMAGE2LRX, double IMAGE2LRY, double IMAGE2LLX, double IMAGE2LLY, double IMAGE2AREA, double IMAGE2INCIDENCEANGLE, double OVERLAPULX, double OVERLAPULY, double OVERLAPURX, double OVERLAPURY, double OVERLAPLRX, double OVERLAPLRY, double OVERLAPLLX, double OVERLAPLLY, double OVERLAPAREA)
{
  /***********************/
  /* Retrieve parameters */
  /***********************/
  id = ID;
  image1_area = IMAGE1AREA;
  image1_id = IMAGE1ID;
  image1_incidence_angle = IMAGE1INCIDENCEANGLE;
  image1_lower_left_x = IMAGE1LLX;
  image1_lower_left_y = IMAGE1LLY;
  image1_lower_right_x = IMAGE1LRX;
  image1_lower_right_y = IMAGE1LRY;
  image1_name = IMAGE1NAME;
  image1_upper_left_x = IMAGE1ULX;
  image1_upper_left_y = IMAGE1ULY;
  image1_upper_right_x = IMAGE1URX;
  image1_upper_right_y = IMAGE1URY;
  image2_area = IMAGE2AREA;
  image2_id = IMAGE2ID;
  image2_incidence_angle = IMAGE2INCIDENCEANGLE;
  image2_lower_left_x = IMAGE2LLX;
  image2_lower_left_y = IMAGE2LLY;
  image2_lower_right_x = IMAGE2LRX;
  image2_lower_right_y = IMAGE2LRY;
  image2_name = IMAGE2NAME;
  image2_upper_left_x = IMAGE2ULX;
  image2_upper_left_y = IMAGE2ULY;
  image2_upper_right_x = IMAGE2URX;
  image2_upper_right_y = IMAGE2URY;
  overlap_area = OVERLAPAREA;
  overlap_lower_left_x = OVERLAPLLX;
  overlap_lower_left_y = OVERLAPLLY;
  overlap_lower_right_x = OVERLAPLRX;
  overlap_lower_right_y = OVERLAPLRY;
  overlap_upper_left_x = OVERLAPULX;
  overlap_upper_left_y = OVERLAPULY;
  overlap_upper_right_x = OVERLAPURX;
  overlap_upper_right_y = OVERLAPURY;

  /****************************************************/
  /* Determine rectangular bounding region of overlap */
  /****************************************************/
  OverlapRectangularBoundingRegion();
}

double OverlappedImages::GetImage1_area()
{
  return image1_area;
}

double OverlappedImages::GetImage1_incidence_angle()
{
  return image1_incidence_angle;
}

double OverlappedImages::GetImage1_lower_left_x()
{
  return image1_lower_left_x;
}

double OverlappedImages::GetImage1_lower_left_y()
{
  return image1_lower_left_y;
}

double OverlappedImages::GetImage1_lower_right_x()
{
  return image1_lower_right_x;
}

double OverlappedImages::GetImage1_lower_right_y()
{
  return image1_lower_right_y;
}

double OverlappedImages::GetImage1_upper_left_x()
{
  return image1_upper_left_x;
}

double OverlappedImages::GetImage1_upper_left_y()
{
  return image1_upper_left_y;
}

double OverlappedImages::GetImage1_upper_right_x()
{
  return image1_upper_right_x;
}

double OverlappedImages::GetImage1_upper_right_y()
{
  return image1_upper_right_y;
}

double OverlappedImages::GetImage2_area()
{
  return image2_area;
}

double OverlappedImages::GetImage2_incidence_angle()
{
  return image2_incidence_angle;
}

double OverlappedImages::GetImage2_lower_left_x()
{
  return image2_lower_left_x;
}

double OverlappedImages::GetImage2_lower_left_y()
{
  return image2_lower_left_y;
}

double OverlappedImages::GetImage2_lower_right_x()
{
  return image2_lower_right_x;
}

double OverlappedImages::GetImage2_lower_right_y()
{
  return image2_lower_right_y;
}

double OverlappedImages::GetImage2_upper_left_x()
{
  return image2_upper_left_x;
}

double OverlappedImages::GetImage2_upper_left_y()
{
  return image2_upper_left_y;
}

double OverlappedImages::GetImage2_upper_right_x()
{
  return image2_upper_right_x;
}

double OverlappedImages::GetImage2_upper_right_y()
{
  return image2_upper_right_y;
}

double OverlappedImages::GetOverlap_area()
{
  return overlap_area;
}

double OverlappedImages::GetOverlap_lower_left_x()
{
  return overlap_lower_left_x;
}

double OverlappedImages::GetOverlap_lower_left_y()
{
  return overlap_lower_left_y;
}

double OverlappedImages::GetOverlap_lower_right_x()
{
  return overlap_lower_right_x;
}

double OverlappedImages::GetOverlap_lower_right_y()
{
  return overlap_lower_right_y;
}

double OverlappedImages::GetOverlap_maximum_x()
{ 
  return overlap_maximum_x;
}

double OverlappedImages::GetOverlap_maximum_y()
{ 
  return overlap_maximum_y;
}

double OverlappedImages::GetOverlap_minimum_x()
{ 
  return overlap_minimum_x;
}

double OverlappedImages::GetOverlap_minimum_y()
{ 
  return overlap_minimum_y;
}

double OverlappedImages::GetOverlap_upper_left_x()
{
  return overlap_upper_left_x;
}

double OverlappedImages::GetOverlap_upper_left_y()
{
  return overlap_upper_left_y;
}

double OverlappedImages::GetOverlap_upper_right_x()
{
  return overlap_upper_right_x;
}

double OverlappedImages::GetOverlap_upper_right_y()
{
  return overlap_upper_right_y;
}

int OverlappedImages::GetId()
{
  return id;
}

int OverlappedImages::GetImage1_id()
{
  return image1_id;
}

int OverlappedImages::GetImage2_id()
{
  return image2_id;
}

string OverlappedImages::GetImage1_name()
{
  return image1_name;
}

string OverlappedImages::GetImage2_name()
{
  return image2_name;
}

void OverlappedImages::OverlapRectangularBoundingRegion()
{
  /****************************************************************/
  /* Determine minimum and maximum x values of the overlap region */
  /****************************************************************/
  if(overlap_upper_left_x < overlap_upper_right_x)
  {
    overlap_minimum_x = (overlap_upper_left_x < overlap_lower_left_x) ?
                        overlap_upper_left_x : overlap_lower_left_x;
    overlap_maximum_x = (overlap_upper_right_x > overlap_lower_right_x) ?
                        overlap_upper_right_x : overlap_lower_right_x;
  }
  else
  {
    overlap_minimum_x = (overlap_upper_right_x < overlap_lower_right_x) ?
                        overlap_upper_right_x : overlap_lower_right_x;
    overlap_maximum_x = (overlap_upper_left_x > overlap_lower_left_x) ?
                        overlap_upper_left_x : overlap_lower_left_x;
  }

  /****************************************************************/
  /* Determine minimum and maximum y values of the overlap region */
  /****************************************************************/
  if(overlap_upper_left_y < overlap_lower_left_y)
  {
    overlap_minimum_y = (overlap_upper_left_y < overlap_upper_right_y) ?
                        overlap_upper_left_y : overlap_upper_right_y;
    overlap_maximum_y = (overlap_lower_left_y > overlap_lower_right_y) ?
                        overlap_lower_left_y : overlap_lower_right_y;
  }
  else
  {
    overlap_minimum_y = (overlap_lower_left_y < overlap_lower_right_y) ?
                        overlap_lower_right_y : overlap_lower_right_y;
    overlap_maximum_x = (overlap_upper_left_y > overlap_upper_right_y) ?
                        overlap_upper_left_y : overlap_upper_right_y;
  }

  return;
}

void OverlappedImages::Display(OverlappedImages a)
{
  /********************/
  /* Print header row */
  /********************/
  printf("%-5s %-19s %10s %10s %10s %10s %10s %10s %10s %10s %5s %-19s %10s %10s %10s %10s %10s %10s %10s %10s %5s %10s %10s %10s %10s %10s %10s %10s %10s\n", 
	 "ID",
	 "I1NAME",
	 "I1ULX",
	 "I1ULY",
	 "I1URX",
	 "I1URY",
	 "I1LRX",
	 "I1LRY",
	 "I1LLX",
	 "I1LLY",
	 "I1IA", 
	 "I2NAME",
	 "I2ULX",
	 "I2ULY",
	 "I2URX",
	 "I2URY",
	 "I2LRX",
	 "I2LRY",
	 "I2LLX",
	 "I2LLY", 
	 "I2IA", 
	 "OULX",
	 "OULY",
	 "OURX",
	 "OURY",
	 "OLRX",
	 "OLRY",
	 "OLLX",
	 "OLLY");
  
  /******************/
  /* Print data row */
  /******************/
  printf("%-5d %-19s %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %5.2lf %-19s %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %5.2lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf\n", 
	 a.GetId(), 
	 a.GetImage1_name().c_str(),
	 a.GetImage1_upper_left_x(),
	 a.GetImage1_upper_left_y(),
	 a.GetImage1_upper_right_x(),
	 a.GetImage1_upper_right_y(),
	 a.GetImage1_lower_right_x(),
	 a.GetImage1_lower_right_y(),
	 a.GetImage1_lower_left_x(),
	 a.GetImage1_lower_left_y(),
	 a.GetImage1_incidence_angle(),
	 a.GetImage2_name().c_str(),
	 a.GetImage2_upper_left_x(),
	 a.GetImage2_upper_left_y(),
	 a.GetImage2_upper_right_x(),
	 a.GetImage2_upper_right_y(),
	 a.GetImage2_lower_right_x(),
	 a.GetImage2_lower_right_y(),
	 a.GetImage2_lower_left_x(),
	 a.GetImage2_lower_left_y(), 
	 a.GetImage2_incidence_angle(), 
	 a.GetOverlap_upper_left_x(),
	 a.GetOverlap_upper_left_y(),
	 a.GetOverlap_upper_right_x(),
	 a.GetOverlap_upper_right_y(),
	 a.GetOverlap_lower_right_x(),
	 a.GetOverlap_lower_right_y(),
	 a.GetOverlap_lower_left_x(),
	 a.GetOverlap_lower_left_y());

  return;
}

void OverlappedImages::Display(vector <OverlappedImages> &list)
{
  /********************/
  /* Print header row */
  /********************/
  printf("%-5s %-19s %10s %10s %10s %10s %10s %10s %10s %10s %5s %-19s %10s %10s %10s %10s %10s %10s %10s %10s %5s %10s %10s %10s %10s %10s %10s %10s %10s\n", 
	 "ID",
	 "I1NAME",
	 "I1ULX",
	 "I1ULY",
	 "I1URX",
	 "I1URY",
	 "I1LRX",
	 "I1LRY",
	 "I1LLX",
	 "I1LLY",
	 "I1IA", 
	 "I2NAME",
	 "I2ULX",
	 "I2ULY",
	 "I2URX",
	 "I2URY",
	 "I2LRX",
	 "I2LRY",
	 "I2LLX",
	 "I2LLY", 
	 "I2IA", 
	 "OULX",
	 "OULY",
	 "OURX",
	 "OURY",
	 "OLRX",
	 "OLRY",
	 "OLLX",
	 "OLLY");
  
  /*******************/
  /* Print data rows */
  /*******************/
  for(int i=0; i<(int)list.size(); i++)
    printf("%-5d %-19s %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %5.2lf %-19s %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %5.2lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf %10.4lf\n",
	 list[i].GetId(), 
	 list[i].GetImage1_name().c_str(), 
	 list[i].GetImage1_upper_left_x(),
	 list[i].GetImage1_upper_left_y(),
	 list[i].GetImage1_upper_right_x(),
	 list[i].GetImage1_upper_right_y(),
	 list[i].GetImage1_lower_right_x(),
	 list[i].GetImage1_lower_right_y(),
	 list[i].GetImage1_lower_left_x(),
	 list[i].GetImage1_lower_left_y(),
	 list[i].GetImage1_incidence_angle(),
	 list[i].GetImage2_name().c_str(),
	 list[i].GetImage2_upper_left_x(),
	 list[i].GetImage2_upper_left_y(),
	 list[i].GetImage2_upper_right_x(),
	 list[i].GetImage2_upper_right_y(),
	 list[i].GetImage2_lower_right_x(),
	 list[i].GetImage2_lower_right_y(),
	 list[i].GetImage2_lower_left_x(),
	 list[i].GetImage2_lower_left_y(), 
	 list[i].GetImage2_incidence_angle(), 
	 list[i].GetOverlap_upper_left_x(),
	 list[i].GetOverlap_upper_left_y(),
	 list[i].GetOverlap_upper_right_x(),
	 list[i].GetOverlap_upper_right_y(),
	 list[i].GetOverlap_lower_right_x(),
	 list[i].GetOverlap_lower_right_y(),
	 list[i].GetOverlap_lower_left_x(),
	 list[i].GetOverlap_lower_left_y());

  return;
}
