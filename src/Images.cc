#include "Images.h"

using namespace std;

Images::Images()
{
}

Images::Images(int ID, int ISID, int AID, string NAME, string FL, double P, int PM, int DONE, double SA, string DET, string CREATE, string UPDATE)
{
  application_id = AID;
  area = 0;
  created_at = CREATE;
  details = DET;
  done = DONE;
  file_location = FL;
  height = 0;
  id = ID;
  image_set_id = ISID;
  lower_left_latitude = 0;
  lower_left_longitude = 0;
  lower_left_x = 0;
  lower_left_y = 0;
  lower_right_latitude = 0;
  lower_right_longitude = 0;
  lower_right_x = 0;
  lower_right_y = 0;
  maximum_latitude = 0;
  maximum_longitude = 0;
  maximum_x = 0;
  maximum_y = 0;
  minimum_latitude = 0;
  minimum_longitude = 0;
  minimum_x = 0;
  minimum_y = 0;
  name = NAME;
  premarked = PM;
  priority = P;
  sun_angle = SA;
  updated_at = UPDATE;
  upper_left_latitude = 0;
  upper_left_longitude = 0;
  upper_left_x = 0;
  upper_left_corner_x_status = "";
  upper_left_y = 0;
  upper_left_corner_y_status = "";
  upper_right_latitude = 0;
  upper_right_longitude = 0;
  upper_right_x = 0;
  upper_right_y = 0;
  width = 0;
  x_relative = 0;
  y_relative = 0;
}

double Images::GetArea()
{
  return area;
}

double Images::GetLower_left_latitude()
{
  return lower_left_latitude;
}

double Images::GetLower_left_longitude()
{
  return lower_left_longitude;
}

double Images::GetLower_left_x()
{
  return lower_left_x;
}

double Images::GetLower_left_y()
{
  return lower_left_y;
}

double Images::GetLower_right_latitude()
{
  return lower_right_latitude;
}

double Images::GetLower_right_longitude()
{
  return lower_right_longitude;
}

double Images::GetLower_right_x()
{
  return lower_right_x;
}

double Images::GetLower_right_y()
{
  return lower_right_y;
}

double Images::GetMaximum_latitude()
{
  return maximum_latitude;
}

double Images::GetMaximum_longitude()
{
  return maximum_longitude;
}

double Images::GetMaximum_x()
{
  return maximum_x;
}

double Images::GetMaximum_y()
{
  return maximum_y;
}

double Images::GetMinimum_latitude()
{
  return minimum_latitude;
}

double Images::GetMinimum_longitude()
{
  return minimum_longitude;
}

double Images::GetMinimum_x()
{
  return minimum_x;
}

double Images::GetMinimum_y()
{
  return minimum_y;
}

double Images::GetPriority()
{
  return priority;
}

double Images::GetSun_angle()
{
  return sun_angle;
}

double Images::GetUpper_left_latitude()
{
  return upper_left_latitude;
}

double Images::GetUpper_left_longitude()
{
  return upper_left_longitude;
}

double Images::GetUpper_left_x()
{
  return upper_left_x;
}

double Images::GetUpper_left_y()
{
  return upper_left_y;
}

double Images::GetUpper_right_latitude()
{
  return upper_right_latitude;
}

double Images::GetUpper_right_longitude()
{
  return upper_right_longitude;
}

double Images::GetUpper_right_x()
{
  return upper_right_x;
}

double Images::GetUpper_right_y()
{
  return upper_right_y;
}

double Images::GetValue_double(string field)
{
  switch (str2int(field.c_str())) {
  case str2int("lower_left_latitude"):
    return lower_left_latitude;
    break;
  case str2int("lower_left_longitude"):
    return lower_left_longitude;
    break;
  case str2int("lower_left_x"):
    return lower_left_x;
    break;
  case str2int("lower_left_y"):
    return lower_left_y;
    break;
  case str2int("lower_right_latitude"):
    return lower_right_latitude;
    break;
  case str2int("lower_right_longitude"):
    return lower_right_longitude;
    break;
  case str2int("lower_right_x"):
    return lower_right_x;
    break;
  case str2int("lower_right_y"):
    return lower_right_y;
    break;
  case str2int("maximum_latitude"):
    return maximum_latitude;
    break;
  case str2int("maximum_longitude"):
    return maximum_longitude;
    break;
  case str2int("maximum_x"):
    return maximum_x;
    break;
  case str2int("maximum_y"):
    return maximum_y;
    break;
  case str2int("minimum_latitude"):
    return minimum_latitude;
    break;
  case str2int("minimum_longitude"):
    return minimum_longitude;
    break;
  case str2int("minimum_x"):
    return minimum_x;
    break;
  case str2int("minimum_y"):
    return minimum_y;
    break;
  case str2int("priority"):
    return priority;
    break;
  case str2int("sun_angle"):
    return sun_angle;
    break;
  case str2int("upper_left_latitude"):
    return upper_left_latitude;
    break;
  case str2int("upper_left_longitude"):
    return upper_left_longitude;
    break;
  case str2int("upper_left_x"):
    return upper_left_x;
    break;
  case str2int("upper_left_y"):
    return upper_left_y;
    break;
  case str2int("upper_right_latitude"):
    return upper_right_latitude;
    break;
  case str2int("upper_right_longitude"):
    return upper_right_longitude;
    break;
  case str2int("upper_right_x"):
    return upper_right_x;
    break;
  case str2int("upper_right_y"):
    return upper_right_y;
    break;
  }
  
  return 0;
}

int Images::GetApplication_id()
{
  return application_id;
}

int Images::GetDone()
{
  return done;
}

int Images::GetHeight()
{
  return height;
}

int Images::GetId()
{
  return id;
}

int Images::GetImage_number()
{
  return image_number;
}

int Images::GetImage_scale()
{
  return image_scale;
}

int Images::GetImage_set_id()
{
  return image_set_id;
}

int Images::GetPremarked()
{
  return premarked;
}

int Images::GetValue_int(string field)
{
  switch (str2int(field.c_str())) {
  case str2int("application_id"):
    return application_id;
    break;
  case str2int("done"):
    return done;
    break;
  case str2int("height"):
    return height;
    break;
  case str2int("id"):
    return id;
    break;
  case str2int("image_number"):
    return image_number;
    break;
  case str2int("image_scale"):
    return image_scale;
    break;
  case str2int("image_set_id"):
    return image_set_id;
    break;
  case str2int("premarked"):
    return premarked;
    break;
  case str2int("width"):
    return width;
    break;
  case str2int("x_relative"):
    return x_relative;
    break;
  case str2int("y_relative"):
    return y_relative;
    break;
  }
  
  return 0;
}

int Images::GetWidth()
{
  return width;
}

int Images::GetX_relative()
{
  return x_relative;
}

int Images::GetY_relative()
{
  return y_relative;
}

ProjectiveTransformation Images::GetProjective_transformation()
{
  return pt;
}

Quadrilateral Images::GetQuadrilateral()
{
  return quad;
}

string Images::GetCreated_at()
{
  return created_at;
}

string Images::GetDetails()
{
  return details;
}

string Images::GetFile_location()
{
  return file_location;
}

string Images::GetMaster_image_name()
{
  return master_image_name;
}

string Images::GetName()
{
  return name;
}

string Images::GetUpdated_at()
{
  return updated_at;
}

string Images::GetUpper_left_corner_x_status()
{
  return upper_left_corner_x_status;
}

string Images::GetUpper_left_corner_y_status()
{
  return upper_left_corner_y_status;
}

string Images::GetValue_string(string field)
{
  switch (str2int(field.c_str())) {
  case str2int("created_at"):
    return created_at;
    break;
  case str2int("details"):
    return details;
    break;
  case str2int("file_location"):
    return file_location;
    break;
  case str2int("name"):
    return name;
    break;  
  case str2int("updated_at"):
    return updated_at;
    break;
  case str2int("upper_left_corner_x_status"):
    return upper_left_corner_x_status;
    break;
  case str2int("upper_left_corner_y_status"):
    return upper_left_corner_y_status;
    break;
  }
  
  return "";
}

vector <double> Images::GetPhysical_height()
{
  return physical_height;
}

vector <double> Images::GetPhysical_width()
{
  return physical_width;
}

vector <string> Images::GetFields()
{
  vector <string> fields{"id",
      "image_set_id",
      "application_id",
      "name",
      "upper_left_x",
      "upper_left_y",
      "upper_right_x",
      "upper_right_y",
      "lower_right_x",
      "lower_right_y",
      "lower_left_x",
      "lower_left_y",
      "minimum_x",
      "minimum_y",
      "maximum_x",
      "maximum_y"};
  
  return fields;
}

vector < vector <double> > Images::GetShape_vector()
{
  return shape_vector;
}

void Images::AuxilaryFunction(string XORIGIN, string YORIGIN, ProjectiveTransformation PT, bool CalculatePhysical_Height_Width)
{
  /*********************************/
  /* Step 1: Set image orientation */
  /*********************************/
  SetUpper_left_corner_x_status(XORIGIN);
  SetUpper_left_corner_y_status(YORIGIN);
  
  /****************************************/
  /* Step 2: Set transformation matricies */
  /****************************************/
  SetProjective_transformation(PT);
  
  /********************************************/
  /* Step 3: Retrieve relative x and y values */
  /********************************************/
  RetrieveX_relative();
  RetrieveY_relative();

  /*******************************************/
  /* Step 4: Retrieve image width and height */
  /*******************************************/
  RetrieveWidth();
  RetrieveHeight();

  /**************************************************************************************/
  /* Step 5: Calculate bounding region latitude and longitude selenographic coordinates */
  /**************************************************************************************/
  CalculateBoundingRegionSelenographicCoordinates();
    
  /*******************************************************************/
  /* Step 6: Calculate bounding region x and y cartesian coordinates */
  /*******************************************************************/
  CalculateBoundingRegionCartesianCoordinates();

  /********************************************************/
  /* Step 7: Determine minimum/maximum coordinate values */
  /********************************************************/
  DetermineCoordinateExtrema();

  /******************************************************/
  /* Step 8: Establish traits of quadrilateral variable */
  /******************************************************/
  CalculateQuadrilateral();
  
  /*****************************************************/
  /* Step 9: Calculate physical image width and height */
  /*****************************************************/
  if(CalculatePhysical_Height_Width)
  {
    CalculatePhysical_width();
    CalculatePhysical_height();
  }

  /****************************************/
  /* Step 10: Determine master image name */
  /****************************************/
  DetermineMasterImageName();
  
  /**************************************/
  /* Step 11: Determine sub-image scale */
  /**************************************/
  DetermineImageScale();
  
  /***************************************/
  /* Step 12: Determine sub-image number */
  /***************************************/
  DetermineImageNumber();
}

void Images::CalculateBoundingRegionCartesianCoordinates()
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double phi_1 = 0; // Flat square projection (Unit: degree)
  double lambda_0 = 0; // Central meridian (Unit: degree)
  
  /*******************************************************************************/
  /* Calculate x and y position of sub-image upper left corner as viewed by user */
  /*******************************************************************************/
  upper_left_x = EquirectangularProjection::CalculateX(upper_left_longitude, lambda_0, phi_1, R_moon); // Unit: meter
  upper_left_y = EquirectangularProjection::CalculateY(upper_left_latitude, phi_1, R_moon); // Unit: meter

  /********************************************************************************/
  /* Calculate x and y position of sub-image lower right corner as viewed by user */
  /********************************************************************************/
  upper_right_x = EquirectangularProjection::CalculateX(upper_right_longitude, lambda_0, phi_1, R_moon); // Unit: meter
  upper_right_y = EquirectangularProjection::CalculateY(upper_right_latitude, phi_1, R_moon); // Unit: meter

  /********************************************************************************/
  /* Calculate x and y position of sub-image lower right corner as viewed by user */
  /********************************************************************************/
  lower_right_x = EquirectangularProjection::CalculateX(lower_right_longitude, lambda_0, phi_1, R_moon); // Unit: meter
  lower_right_y = EquirectangularProjection::CalculateY(lower_right_latitude, phi_1, R_moon); // Unit: meter

  /*******************************************************************************/
  /* Calculate x and y position of sub-image lower left corner as viewed by user */
  /*******************************************************************************/
  lower_left_x = EquirectangularProjection::CalculateX(lower_left_longitude, lambda_0, phi_1, R_moon); // Unit: meter
  lower_left_y = EquirectangularProjection::CalculateY(lower_left_latitude, phi_1, R_moon); // Unit: meter
}

void Images::CalculateBoundingRegionSelenographicCoordinates()
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  vector <double> coordinates;

  /*************************************************************************************/
  /* Calculate longitude and latitude of sub-image upper left corner as viewed by user */
  /*************************************************************************************/
  coordinates = pt.ComputeTarget2SourceCoordinates(x_relative, y_relative);
  upper_left_longitude = coordinates[0];
  upper_left_latitude = coordinates[1];

  /**************************************************************************************/
  /* Calculate longitude and latitude of sub-image upper right corner as viewed by user */
  /**************************************************************************************/
  coordinates = pt.ComputeTarget2SourceCoordinates(x_relative+width, y_relative);
  upper_right_longitude = coordinates[0];
  upper_right_latitude = coordinates[1];

  /**************************************************************************************/
  /* Calculate longitude and latitude of sub-image lower right corner as viewed by user */
  /**************************************************************************************/
  coordinates = pt.ComputeTarget2SourceCoordinates(x_relative+width, y_relative+height);
  lower_right_longitude = coordinates[0];
  lower_right_latitude = coordinates[1];
  
  /*************************************************************************************/
  /* Calculate longitude and latitude of sub-image lower left corner as viewed by user */
  /*************************************************************************************/
  coordinates = pt.ComputeTarget2SourceCoordinates(x_relative, y_relative+height);
  lower_left_longitude = coordinates[0];
  lower_left_latitude = coordinates[1];
}

void Images::CalculatePhysical_height()
{
  /*******************************************************************************/
  /* Iterate through columns of image and calculate physical height along column */
  /*******************************************************************************/
  double constant = y_relative+height;
  for(int i=0; i<width; i++)
  {
    double h_0 = pt.ComputeTarget2SourceCoordinate_y(x_relative+i, y_relative); // Unit: degree
    double h_1 = pt.ComputeTarget2SourceCoordinate_y(x_relative+i, constant); // Unit: degree
    double diff = fabs(h_1-h_0); // Unit: degree
    double ph = EquirectangularProjection::CalculateY(diff, 0.0, R_moon); // Unit: meter
    physical_height.push_back(ph); // Unit: meter
  }
}

void Images::CalculatePhysical_width()
{
  /************************************************************************/
  /* Iterate through rows of image and calculate physical width along row */
  /************************************************************************/
  double constant = x_relative+width;
  for(int i=0; i<height; i++)
  {
    double w_0 = pt.ComputeTarget2SourceCoordinate_x(x_relative, y_relative+i); // Unit: degree
    double w_1 = pt.ComputeTarget2SourceCoordinate_x(constant, y_relative+i); // Unit: degree
    double diff = fabs(w_1-w_0); // Unit: degree
    double wh = EquirectangularProjection::CalculateX(diff, 0.0, 0.0, R_moon); // Unit: meter
    physical_height.push_back(wh); // Unit: meter
  }
}

void Images::CalculateQuadrilateral()
{
  quad = Quadrilateral(upper_left_x, upper_left_y, upper_right_x, upper_right_y, lower_right_x, lower_right_y, lower_left_x, lower_left_y);
  area = quad.GetArea();
  shape_vector = quad.GetVector();
}

void Images::DetermineCoordinateExtrema()
{
  /***************************************************************************/
  /* Determine maximum/minimum selenographic and cartesian coordinate values */
  /***************************************************************************/
  if(upper_left_corner_x_status.compare("MAX") == 0)
  {
    maximum_longitude = (upper_left_longitude > lower_left_longitude) ? upper_left_longitude : lower_left_longitude;
    maximum_x = (upper_left_x > lower_left_x) ? upper_left_x : lower_left_x;
    minimum_longitude = (upper_right_longitude < lower_right_longitude) ? upper_right_longitude : lower_right_longitude;
    minimum_x = (upper_right_x < lower_right_x) ? upper_right_x : lower_right_x;
  }
  else
  {
    maximum_longitude = (upper_right_longitude > lower_right_longitude) ? upper_right_longitude : lower_right_longitude;
    maximum_x = (upper_right_x > lower_right_x) ? upper_right_x : lower_right_x;
    minimum_longitude = (upper_left_longitude < lower_left_longitude) ? upper_left_longitude : lower_left_longitude;
    minimum_x = (upper_left_x < lower_left_x) ? upper_left_x : lower_left_x;
  }
  if(upper_left_corner_y_status.compare("MAX") == 0)
  {
    maximum_latitude = (upper_left_latitude > upper_right_latitude) ? upper_left_latitude : upper_right_latitude;
    maximum_y = (upper_left_y > upper_right_y) ? upper_left_y : upper_right_y;
    minimum_latitude = (lower_left_latitude < lower_right_latitude) ? lower_left_latitude : lower_right_latitude;
    minimum_y = (lower_left_y < lower_right_y) ? lower_left_y : lower_right_y;
  }
  else
  {
    maximum_latitude = (lower_left_latitude > lower_right_latitude) ? lower_left_latitude : lower_right_latitude;
    maximum_y = (lower_left_y > lower_right_y) ? lower_left_y : lower_right_y;
    minimum_latitude = (upper_left_latitude < upper_right_latitude) ? upper_left_latitude : upper_right_latitude;
    minimum_y = (upper_left_y < upper_right_y) ? upper_left_y : upper_right_y;
  }
}

void Images::DetermineImageNumber()
{
  int pos1 = name.rfind("_")+1;
  image_number = stoi(name.substr(pos1));
}

void Images::DetermineImageScale()
{
  int pos1 = name.find("_")+1;
  int pos2 = name.rfind("_");
  int len = pos2-pos1;
  image_scale = stoi(name.substr(pos1, len));
}

void Images::DetermineMasterImageName()
{
  int pos1 = 0;
  int pos2 = name.find("_");
  int len = pos2-pos1;
  master_image_name = name.substr(pos1, len);
}

void Images::RetrieveHeight()
{
  /******************************************************/
  /* Parse "details" string to retrieve value of height */
  /******************************************************/
  int p1 = details.find("<height>")+8;
  int p2 = details.find("</height>");
  int length = p2-p1;
  string str = details.substr(p1, length);
  height = stoi(str, nullptr);
}

void Images::RetrieveWidth()
{
  /*****************************************************/
  /* Parse "details" string to retrieve value of width */
  /*****************************************************/
  int p1 = details.find("<width>")+7;
  int p2 = details.find("</width>");
  int length = p2-p1;
  string str = details.substr(p1, length);
  width = stoi(str, nullptr);
}

void Images::RetrieveX_relative()
{
  /***********************************************************/
  /* Retrieve x position relative to associated master image */
  /***********************************************************/
  int p1 = details.find("<x>")+3;
  int p2 = details.find("</x>");
  int length = p2-p1;
  string str = details.substr(p1, length);
  x_relative = stoi(str, nullptr);
}

void Images::RetrieveY_relative()
{
  /***********************************************************/
  /* Retrieve y position relative to associated master image */
  /***********************************************************/
  int p1 = details.find("<y>")+3;
  int p2 = details.find("</y>");
  int length = p2-p1;
  string str = details.substr(p1, length);
  y_relative = stoi(str, nullptr);
}

void Images::SetProjective_transformation(ProjectiveTransformation PT)
{
  pt = PT;
}

void Images::SetUpper_left_corner_x_status(string str)
{
  upper_left_corner_x_status = str;
}

void Images::SetUpper_left_corner_y_status(string str)
{
  upper_left_corner_y_status = str;
}

void * Images::GetValue(string field)
{
  switch (str2int(field.c_str())) {
  case str2int("application_id"):
    return &application_id;
    break;
  case str2int("created_at"):
    return &created_at;
    break;
  case str2int("details"):
    return &details;
    break;
  case str2int("done"):
    return &done;
    break;
  case str2int("file_location"):
    return &file_location;
    break;
  case str2int("height"):
    return &height;
    break;
  case str2int("id"):
    return &id;
    break;
  case str2int("image_number"):
    return &image_number;
    break;
  case str2int("image_scale"):
    return &image_scale;
    break;
  case str2int("image_set_id"):
    return &image_set_id;
    break;
  case str2int("lower_left_latitude"):
    return &lower_left_latitude;
    break;
  case str2int("lower_left_longitude"):
    return &lower_left_longitude;
    break;
  case str2int("lower_left_x"):
    return &lower_left_x;
    break;
  case str2int("lower_left_y"):
    return &lower_left_y;
    break;
  case str2int("lower_right_latitude"):
    return &lower_right_latitude;
    break;
  case str2int("lower_right_longitude"):
    return &lower_right_longitude;
    break;
  case str2int("lower_right_x"):
    return &lower_right_x;
    break;
  case str2int("lower_right_y"):
    return &lower_right_y;
    break;
  case str2int("maximum_latitude"):
    return &maximum_latitude;
    break;
  case str2int("maximum_longitude"):
    return &maximum_longitude;
    break;
  case str2int("maximum_x"):
    return &maximum_x;
    break;
  case str2int("maximum_y"):
    return &maximum_y;
    break;
  case str2int("minimum_latitude"):
    return &minimum_latitude;
    break;
  case str2int("minimum_longitude"):
    return &minimum_longitude;
    break;
  case str2int("minimum_x"):
    return &minimum_x;
    break;
  case str2int("minimum_y"):
    return &minimum_y;
    break;
  case str2int("name"):
    return &name;
    break;
  case str2int("premarked"):
    return &premarked;
    break;
  case str2int("priority"):
    return &priority;
    break;
  case str2int("sun_angle"):
    return &sun_angle;
    break;  
  case str2int("updated_at"):
    return &updated_at;
    break;
  case str2int("upper_left_corner_x_status"):
    return &upper_left_corner_x_status;
    break;
  case str2int("upper_left_corner_y_status"):
    return &upper_left_corner_y_status;
    break;
  case str2int("upper_left_latitude"):
    return &upper_left_latitude;
    break;
  case str2int("upper_left_longitude"):
    return &upper_left_longitude;
    break;
  case str2int("upper_left_x"):
    return &upper_left_x;
    break;
  case str2int("upper_left_y"):
    return &upper_left_y;
    break;
  case str2int("upper_right_latitude"):
    return &upper_right_x;
    break;
  case str2int("upper_right_longitude"):
    return &upper_right_y;
    break;
  case str2int("upper_right_x"):
    return &upper_right_x;
    break;
  case str2int("upper_right_y"):
    return &upper_right_y;
    break;
  case str2int("width"):
    return &width;
    break;
  case str2int("x_relative"):
    return &x_relative;
    break;
  case str2int("y_relative"):
    return &y_relative;
    break;
  }
  
  return NULL;
}
