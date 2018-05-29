#include "OverlappedImages.h"

using namespace std;

OverlappedImages::OverlappedImages(int ID, int IMAGE1ID, string IMAGE1NAME, string IMAGE1XORIGINCONDITION, string IMAGE1YORIGINCONDITION, double IMAGE1HORIZONTALRESOLUTION, double IMAGE1VERTICALRESOLUTION, double IMAGE1XLOW, double IMAGE1XHIGH, double IMAGE1YLOW, double IMAGE1YHIGH, double IMAGE1INCIDENCEANGLE, int IMAGE2ID, string IMAGE2NAME, string IMAGE2XORIGINCONDITION, string IMAGE2YORIGINCONDITION, double IMAGE2HORIZONTALRESOLUTION, double IMAGE2VERTICALRESOLUTION, double IMAGE2XLOW, double IMAGE2XHIGH, double IMAGE2YLOW, double IMAGE2YHIGH, double IMAGE2INCIDENCEANGLE, double OVERLAPXLOW, double OVERLAPXHIGH, double OVERLAPYLOW, double OVERLAPYHIGH)
{
  id = ID;
  image1_area = 0;
  image1_height = 0;
  image1_horizontal_resolution = IMAGE1HORIZONTALRESOLUTION;
  image1_id = IMAGE1ID;
  image1_incidence_angle = IMAGE1INCIDENCEANGLE;
  image1_name = IMAGE1NAME;
  image1_vertical_resolution = IMAGE1VERTICALRESOLUTION;
  image1_width = 0;
  image1_x_high = IMAGE1XHIGH;
  image1_x_low = IMAGE1XLOW;
  image1_x_origin_condition = IMAGE1XORIGINCONDITION;
  image1_y_high = IMAGE1YHIGH;
  image1_y_low = IMAGE1YLOW;
  image1_y_origin_condition = IMAGE1YORIGINCONDITION;
  image2_area = 0;
  image2_height = 0;
  image2_horizontal_resolution = IMAGE2HORIZONTALRESOLUTION;
  image2_id = IMAGE2ID;
  image2_incidence_angle = IMAGE2INCIDENCEANGLE;
  image2_name = IMAGE2NAME;
  image2_vertical_resolution = IMAGE2VERTICALRESOLUTION;
  image2_width = 0;
  image2_x_high = IMAGE2XHIGH;
  image2_x_low = IMAGE2XLOW;
  image2_x_origin_condition = IMAGE2XORIGINCONDITION;
  image2_y_high = IMAGE2YHIGH;
  image2_y_low = IMAGE2YLOW;
  image2_y_origin_condition = IMAGE2YORIGINCONDITION;
  overlap_area = 0;
  overlap_height = 0;
  overlap_width = 0;
  overlap_x_high = OVERLAPXHIGH;
  overlap_x_low = OVERLAPXLOW;
  overlap_y_high = OVERLAPYHIGH;
  overlap_y_low = OVERLAPYLOW;
  
  /************************************************/
  /* Calculate other attributes of overlap region */
  /************************************************/
  AuxilaryFunction();
}

double OverlappedImages::GetImage1_area()
{
  return image1_area;
}

double OverlappedImages::GetImage1_height()
{
  return image1_height;
}

double OverlappedImages::GetImage1_horizontal_resolution()
{
  return image1_horizontal_resolution;
}

double OverlappedImages::GetImage1_incidence_angle()
{
  return image1_incidence_angle;
}

double OverlappedImages::GetImage1_vertical_resolution()
{
  return image1_vertical_resolution;
}

double OverlappedImages::GetImage1_width()
{
  return image1_width;
}

double OverlappedImages::GetImage1_x_high()
{
  return image1_x_high;
}

double OverlappedImages::GetImage1_x_low()
{
  return image1_x_low;
}

double OverlappedImages::GetImage1_y_high()
{
  return image1_y_high;
}

double OverlappedImages::GetImage1_y_low()
{
  return image1_y_low;
}

double OverlappedImages::GetImage2_area()
{
  return image2_area;
}

double OverlappedImages::GetImage2_height()
{
  return image2_height;
}

double OverlappedImages::GetImage2_horizontal_resolution()
{
  return image2_horizontal_resolution;
}

double OverlappedImages::GetImage2_incidence_angle()
{
  return image2_incidence_angle;
}

double OverlappedImages::GetImage2_vertical_resolution()
{
  return image2_vertical_resolution;
}

double OverlappedImages::GetImage2_width()
{
  return image2_width;
}

double OverlappedImages::GetImage2_x_high()
{
  return image2_x_high;
}

double OverlappedImages::GetImage2_x_low()
{
  return image2_x_low;
}

double OverlappedImages::GetImage2_y_high()
{
  return image2_y_high;
}

double OverlappedImages::GetImage2_y_low()
{
  return image2_y_low;
}

double OverlappedImages::GetOverlap_area()
{
  return overlap_area;
}

double OverlappedImages::GetOverlap_height()
{
  return overlap_height;
}

double OverlappedImages::GetOverlap_width()
{
  return overlap_width;
}

double OverlappedImages::GetOverlap_x_high()
{
  return overlap_x_high;
}

double OverlappedImages::GetOverlap_x_low()
{
  return overlap_x_low;
}

double OverlappedImages::GetOverlap_y_high()
{
  return overlap_y_high;
}

double OverlappedImages::GetOverlap_y_low()
{
  return overlap_y_low;
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

string OverlappedImages::GetImage1_x_origin_condition()
{
  return image1_x_origin_condition;
}

string OverlappedImages::GetImage1_y_origin_condition()
{
  return image1_y_origin_condition;
}

string OverlappedImages::GetImage2_name()
{
  return image2_name;
}

string OverlappedImages::GetImage2_x_origin_condition()
{
  return image2_x_origin_condition;
}

string OverlappedImages::GetImage2_y_origin_condition()
{
  return image2_y_origin_condition;
}

void OverlappedImages::AuxilaryFunction()
{
  /****************************************************/
  /* Step 1: Calculate both images widths and heights */
  /****************************************************/
  CalculateImage1Height();
  CalculateImage1Width();
  CalculateImage2Height();
  CalculateImage2Width();

  /***************************************/
  /* Step 2: Calculate both images areas */
  /***************************************/
  CalculateImage1Area();
  CalculateImage2Area();

  /**********************************************/
  /* Step 3: Calculate overlap width and height */
  /**********************************************/
  CalculateOverlapHeight();
  CalculateOverlapWidth();

  /**********************************/
  /* Step 4: Calculate overlap area */
  /**********************************/
  CalculateOverlapArea();
}

void OverlappedImages::CalculateImage1Area()
{
  image1_area = image1_width*image1_height;
}

void OverlappedImages::CalculateImage1Height()
{
  image1_height = (image1_y_high-image1_y_low);
}

void OverlappedImages::CalculateImage1Width()
{
  image1_width = (image1_x_high-image1_x_low);
}

void OverlappedImages::CalculateImage2Area()
{
  image2_area = image2_width*image2_height;
}

void OverlappedImages::CalculateImage2Height()
{
  image2_height = (image2_y_high-image2_y_low);
}

void OverlappedImages::CalculateImage2Width()
{
  image2_width = (image2_x_high-image2_x_low);
}

void OverlappedImages::CalculateOverlapArea()
{
  overlap_area = overlap_width*overlap_height;
}

void OverlappedImages::CalculateOverlapHeight()
{
  overlap_height = (overlap_y_high-overlap_y_low);
}

void OverlappedImages::CalculateOverlapWidth()
{
  overlap_width = (overlap_x_high-overlap_x_low);
}

void OverlappedImages::Display(OverlappedImages a)
{
  /********************/
  /* Print header row */
  /********************/
  printf("%-5s %-19s %4s %4s %11s %11s %11s %11s %8s %8s %5s %-19s %4s %4s %11s %11s %11s %11s %8s %8s %5s %11s %11s %11s %11s\n", 
	 "ID", 
	 "I1NAME",
	 "I1HR", 
	 "I1VR",
	 "I1XLOW",
	 "I1XHIGH",
	 "I1YLOW",
	 "I1YHIGH",
	 "I1HEIGHT", 
	 "I1WIDTH", 
	 "I1IA", 
	 "I2NAME", 
	 "I2HR", 
	 "I2VR",
	 "I2XLOW",
	 "I2XHIGH",
	 "I2YLOW",
	 "I2YHIGH", 
	 "I2HEIGHT", 
	 "I2WIDTH", 
	 "I2IA", 
	 "OXLOW", 
	 "OXHIGH", 
	 "OYLOW", 
	 "OYHIGH");
  
  /******************/
  /* Print data row */
  /******************/
  printf("%-5d %-19s %4.2lf %4.2lf %11.2lf %11.2lf %11.2lf %11.2lf %8.2lf %8.2lf %5.2lf %-19s %4.2lf %4.2lf %11.2lf %11.2lf %11.2lf %11.2lf %8.2lf %8.2lf %5.2lf %11.2lf %11.2lf %11.2lf %11.2lf\n", 
	 a.GetId(), 
	 a.GetImage1_name().c_str(), 
	 a.GetImage1_horizontal_resolution(), 
	 a.GetImage1_vertical_resolution(),
	 a.GetImage1_x_low(),
	 a.GetImage1_x_high(),
	 a.GetImage1_y_low(),
	 a.GetImage1_y_high(),
	 a.GetImage1_height(), 
	 a.GetImage1_width(), 
	 a.GetImage1_incidence_angle(),
	 a.GetImage2_name().c_str(),
	 a.GetImage2_horizontal_resolution(), 
	 a.GetImage2_vertical_resolution(),
	 a.GetImage2_x_low(),
	 a.GetImage2_x_high(),
	 a.GetImage2_y_low(),
	 a.GetImage2_y_high(), 
	 a.GetImage2_height(), 
	 a.GetImage2_width(), 
	 a.GetImage2_incidence_angle(), 
	 a.GetOverlap_x_low(), 
	 a.GetOverlap_x_high(), 
	 a.GetOverlap_y_low(), 
	 a.GetOverlap_y_high());

  return;
}

void OverlappedImages::Display(vector <OverlappedImages> &list)
{
  /********************/
  /* Print header row */
  /********************/
  printf("%-5s %-19s %4s %4s %11s %11s %11s %11s %8s %8s %5s %-19s %4s %4s %11s %11s %11s %11s %8s %8s %5s %11s %11s %11s %11s\n", 
	 "ID", 
	 "I1NAME",
	 "I1HR", 
	 "I1VR",
	 "I1XLOW",
	 "I1XHIGH",
	 "I1YLOW",
	 "I1YHIGH",
	 "I1HEIGHT", 
	 "I1WIDTH", 
	 "I1IA", 
	 "I2NAME", 
	 "I2HR", 
	 "I2VR",
	 "I2XLOW",
	 "I2XHIGH",
	 "I2YLOW",
	 "I2YHIGH", 
	 "I2HEIGHT", 
	 "I2WIDTH", 
	 "I2IA", 
	 "OXLOW", 
	 "OXHIGH", 
	 "OYLOW", 
	 "OYHIGH");
  
  /*******************/
  /* Print data rows */
  /*******************/
  for(int i=0; i<(int)list.size(); i++)
    printf("%-5d %-19s %4.2lf %4.2lf %11.2lf %11.2lf %11.2lf %11.2lf %8.2lf %8.2lf %5.2lf %-19s %4.2lf %4.2lf %11.2lf %11.2lf %11.2lf %11.2lf %8.2lf %8.2lf %5.2lf %11.2lf %11.2lf %11.2lf %11.2lf\n", 
	 list[i].GetId(), 
	 list[i].GetImage1_name().c_str(), 
	 list[i].GetImage1_horizontal_resolution(), 
	 list[i].GetImage1_vertical_resolution(),
	 list[i].GetImage1_x_low(),
	 list[i].GetImage1_x_high(),
	 list[i].GetImage1_y_low(),
	 list[i].GetImage1_y_high(),
	 list[i].GetImage1_height(), 
	 list[i].GetImage1_width(), 
	 list[i].GetImage1_incidence_angle(),
	 list[i].GetImage2_name().c_str(),
	 list[i].GetImage2_horizontal_resolution(), 
	 list[i].GetImage2_vertical_resolution(),
	 list[i].GetImage2_x_low(),
	 list[i].GetImage2_x_high(),
	 list[i].GetImage2_y_low(),
	 list[i].GetImage2_y_high(), 
	 list[i].GetImage2_height(), 
	 list[i].GetImage2_width(), 
	 list[i].GetImage2_incidence_angle(), 
	 list[i].GetOverlap_x_low(), 
	 list[i].GetOverlap_x_high(), 
	 list[i].GetOverlap_y_low(), 
	 list[i].GetOverlap_y_high());

  return;
}
