#include "ImageSets.h"

using namespace std;

ImageSets::ImageSets(int ID, string NAME, int AID, double P, double SA, double MINLAT, double MAXLAT, double MINLONG, double MAXLONG, double PR, string DESCRIP, string DET, string CREATE, string UPDATE)
{
  application_id = AID;
  created_at = CREATE;
  description = DESCRIP;
  details = DET;
  height = 0;
  horizontal_resolution = 0;
  id = ID;
  maximum_latitude = MAXLAT;
  maximum_longitude = MAXLONG;
  minimum_latitude = MINLAT;
  minimum_longitude = MINLONG;
  name = NAME;
  physical_height = 0;
  physical_width = 0;
  pixel_resolution = PR;
  priority = P;
  sun_angle = SA;
  updated_at = UPDATE;
  upper_left_latitude = "";
  upper_left_longitude = "";
  vertical_resolution = 0;
  width = 0;
  x_high = 0;
  x_low = 0;
  x_origin = 0;
  y_high = 0;
  y_low = 0;
  y_origin = 0;
}

double ImageSets::GetHorizontal_resolution()
{
  return horizontal_resolution;
}

double ImageSets::GetMaximum_latitude()
{
  return maximum_latitude;
}

double ImageSets::GetMaximum_longitude()
{
  return maximum_longitude;
}

double ImageSets::GetMinimum_latitude()
{
  return minimum_latitude;
}

double ImageSets::GetMinimum_longitude()
{
  return minimum_longitude;
}

double ImageSets::GetPhysical_height()
{
  return physical_height;
}

double ImageSets::GetPhysical_width()
{
  return physical_width;
}

double ImageSets::GetPixel_resolution()
{
  return pixel_resolution;
}

double ImageSets::GetPriority()
{
  return priority;
}

double ImageSets::GetSun_angle()
{
  return sun_angle;
}

double ImageSets::GetVertical_resolution()
{
  return vertical_resolution;
}

double ImageSets::GetX_high()
{
  return x_high;
}
 
double ImageSets::GetX_low()
{
  return x_low;
}

double ImageSets::GetX_origin()
{
  return x_origin;
}

double ImageSets::GetY_high()
{
  return y_high;
}

double ImageSets::GetY_low()
{
  return y_low;
}

double ImageSets::GetY_origin()
{
  return y_origin;
}

int ImageSets::GetApplication_id()
{
  return application_id;
}

int ImageSets::GetHeight()
{
  return height;
}

int ImageSets::GetId()
{
  return id;
}

int ImageSets::GetWidth()
{
  return width;
}

string ImageSets::GetCreated_at()
{
  return created_at;
}

string ImageSets::GetDescription()
{
  return description;
}

string ImageSets::GetDetails()
{
  return details;
}

string ImageSets::GetName()
{
  return name;
}

string ImageSets::GetUpdated_at()
{
  return updated_at;
}

string ImageSets::GetUpper_left_latitude()
{
  return upper_left_latitude;
}

string ImageSets::GetUpper_left_longitude()
{
  return upper_left_longitude;
}

void ImageSets::AuxilaryFunction(string XORIGIN, string YORIGIN)
{
  /*********************************/
  /* Step 1: Set image orientation */
  /*********************************/
  SetUpper_left_longitude(XORIGIN);
  SetUpper_left_latitude(YORIGIN);

  /*******************************************/
  /* Step 2: Retrieve image width and height */
  /*******************************************/
  RetrieveWidth();
  RetrieveHeight();

  /*****************************************************/
  /* Step 3: Calculate (x, y) position of image origin */
  /*****************************************************/
  CalculateX_origin();
  CalculateY_origin();

  /*******************************************************/
  /* Step 4: Calculate bounding region x and y positions */
  /*******************************************************/
  CalculateX_high();
  CalculateX_low();
  CalculateY_high();
  CalculateY_low();

  /*****************************************************/
  /* Step 5: Calculate physical image width and height */
  /*****************************************************/
  CalculatePhysical_width();
  CalculatePhysical_height();

  /***************************************************************/
  /* Step 6: Calculate horizontal and vertical pixel resolutions */
  /***************************************************************/
  CalculateHorizontal_resolution();
  CalculateVertical_resolution();
}

void ImageSets::CalculateHorizontal_resolution()
{
  /*******************************************/
  /* Declaration/Initialization of variables */
  /*******************************************/
  double x_range;
  double n_pixels;

  /*********************/
  /* Calculate x range */
  /*********************/
  x_range = physical_width;

  /*******************************/
  /* Retrieve number of x pixels */
  /*******************************/
  n_pixels = width;

  /****************************************/
  /* Calulate horizontal pixel resolution */
  /****************************************/
  horizontal_resolution = x_range/n_pixels;
}

void ImageSets::CalculatePhysical_height()
{
  physical_height = y_high-y_low;
}

void ImageSets::CalculatePhysical_width()
{
  physical_width = x_high-x_low;
}

void ImageSets::CalculateVertical_resolution()
{
  /*******************************************/
  /* Declaration/Initialization of variables */
  /*******************************************/
  double y_range;
  double n_pixels;

  /*********************/
  /* Calculate y range */
  /*********************/
  y_range = physical_height;

  /*******************************/
  /* Retrieve number of y pixels */
  /*******************************/
  n_pixels = height;

  /***************************************/
  /* Calculate vertical pixel resolution */
  /***************************************/
  vertical_resolution = y_range/n_pixels;
}

void ImageSets::CalculateX_high()
{
  /*****************************************/
  /* Calculate maximum x position of image */
  /*****************************************/
  double lambda = maximum_longitude*(M_PI/180); // Unit: radians
  double lambda_0 = 0; // Central meridian (Unit: radians)
  double phi_1 = 0; // Flat square projection - Can also be interpreted as the equator (Unit: radians)
  //double R_moon = 1.0; // Unit sphere
  double R_moon = 1737400; // Physical radius of the moon in meters 
  x_high = EquirectangularProjection::CalculateX(lambda, lambda_0, phi_1, R_moon); // Unit: meter
}

void ImageSets::CalculateX_low()
{
  /*****************************************/
  /* Calculate minimum x position of image */
  /*****************************************/
  double lambda = minimum_longitude*(M_PI/180); // Unit: radians
  double lambda_0 = 0; // Central meridian (Unit: radians)
  double phi_1 = 0; // Flat square projection - Can also be interpreted as the equator (Unit: radians)
  //double R_moon = 1.0; // Unit sphere
  double R_moon = 1737400; // Physical radius of the moon in meters 
  x_low = EquirectangularProjection::CalculateX(lambda, lambda_0, phi_1, R_moon); // Unit: meter
}

void ImageSets::CalculateX_origin()
{
  /*********************************************************************************************/
  /* Calculate x position of image's upper left corner as viewed by user (Defined as x origin) */
  /*********************************************************************************************/
  double lambda = (upper_left_longitude.compare("MAX") == 0) ? maximum_longitude*(M_PI/180) : minimum_longitude*(M_PI/180); // Longitude of image's left edge as viewed by user (Unit: radians)
  double lambda_0 = 0; // Central meridian (Unit: radians)
  double phi_1 = 0; // Flat square projection - Can also be interpreted as the equator (Unit: radians)
  //double R_moon = 1.0; // Unit sphere
  double R_moon = 1737400; // Physical radius of the moon in meters 
  x_origin = EquirectangularProjection::CalculateX(lambda, lambda_0, phi_1, R_moon); // Unit: meter
}

void ImageSets::CalculateY_high()
{
  /*****************************************/
  /* Calculate maximum y position of image */
  /*****************************************/
  double phi = maximum_latitude*(M_PI/180); // Unit: radians
  double phi_1 = 0; // Flat square projection - Can also be interpreted as the equator (Unit: radians)
  //double R_moon = 1.0; // Unit sphere
  double R_moon = 1737400; // Physical radius of the moon (Unit: meter)
  y_high = EquirectangularProjection::CalculateY(phi, phi_1, R_moon); // Unit: meter
}

void ImageSets::CalculateY_low()
{
  /*****************************************/
  /* Calculate maximum y position of image */
  /*****************************************/
  double phi = minimum_latitude*(M_PI/180); // Unit: radians
  double phi_1 = 0; // Flat square projection - Can also be interpreted as the equator (Unit: radians)
  //double R_moon = 1.0; // Unit sphere
  double R_moon = 1737400; // Physical radius of the moon (Unit: meter)
  y_low = EquirectangularProjection::CalculateY(phi, phi_1, R_moon); // Unit: meter
}

void ImageSets::CalculateY_origin()
{
  /*********************************************************************************************/
  /* Calculate y position of image's upper left corner as viewed by user (Defined as y origin) */
  /*********************************************************************************************/
  double phi = (upper_left_latitude.compare("MAX") == 0) ? maximum_latitude*(M_PI/180) : minimum_latitude*(M_PI/180); // Latitude of image's top edge as viewed by user (Unit: radians)
  double phi_1 = 0; // Flat square projection - Can also be interpreted as the equator (Unit: radians)
  //double R_moon = 1.0; // Unit sphere
  double R_moon = 1737400; // Physical radius of the moon (Unit: meter)
  y_origin = EquirectangularProjection::CalculateY(phi, phi_1, R_moon); // Unit: meter
}

void ImageSets::RetrieveHeight()
{
  /*************************/
  /* Retrieve image height */
  /*************************/
  int p1 = details.find("<height>")+8;
  int p2 = details.find("</height>");
  int length = p2-p1;
  string str = details.substr(p1, length);
  height = stoi(str, nullptr);
}

void ImageSets::RetrieveWidth()
{
  /************************/
  /* Retrieve image width */
  /************************/
  int p1 = details.find("<width>")+7;
  int p2 = details.find("</width>");
  int length = p2-p1;
  string str = details.substr(p1, length);
  width = stoi(str, nullptr);
}

void ImageSets::SetHorizontal_resolution(double d)
{
  horizontal_resolution = d;
}

void ImageSets::SetUpper_left_latitude(string str)
{
  upper_left_latitude = str;
}

void ImageSets::SetUpper_left_longitude(string str)
{
  upper_left_longitude = str;
}

void ImageSets::SetVertical_resolution(double d)
{
  vertical_resolution = d;
}
