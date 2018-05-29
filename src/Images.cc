#include "Images.h"

using namespace std;

Images::Images(int ID, int ISID, int AID, string NAME, string FL, double P, int PM, int DONE, double SA, string DET, string CREATE, string UPDATE)
{
  application_id = AID;
  created_at = CREATE;
  details = DET;
  done = DONE;
  file_location = FL;
  height = 0;
  horizontal_resolution = 0;
  id = ID;
  image_set_id = ISID;
  name = NAME;
  physical_height = 0;
  physical_width = 0;
  pixel_resolution = 0;
  premarked = PM;
  priority = P;
  sun_angle = SA;
  updated_at = UPDATE;
  upper_left_x = "";
  upper_left_y = "";
  vertical_resolution = 0;
  width = 0;
  x_high = 0;
  x_low = 0;
  x_offset = 0;
  x_origin = 0;
  x_relative = 0;
  y_high = 0;
  y_low = 0;
  y_offset = 0;
  y_origin = 0;
  y_relative = 0;
}

double Images::GetHorizontal_resolution()
{
  return horizontal_resolution;
}

double Images::GetPhysical_height()
{
  return physical_height;
}

double Images::GetPhysical_width()
{
  return physical_width;
}

double Images::GetPixel_resolution()
{
  return pixel_resolution;
}

double Images::GetPriority()
{
  return priority;
}

double Images::GetSun_angle()
{
  return sun_angle;
}

double Images::GetVertical_resolution()
{
  return vertical_resolution;
}

double Images::GetX_high()
{
  return x_high;
}

double Images::GetX_low()
{
  return x_low;
}

double Images::GetX_offset()
{
  return x_offset;
}

double Images::GetX_origin()
{
  return x_origin;
}

double Images::GetY_high()
{
  return y_high;
}

double Images::GetY_low()
{
  return y_low;
}

double Images::GetY_offset()
{
  return y_offset;
}

double Images::GetY_origin()
{
  return y_origin;
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

int Images::GetImage_set_id()
{
  return image_set_id;
}

int Images::GetPremarked()
{
  return premarked;
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

string Images::GetName()
{
  return name;
}

string Images::GetUpdated_at()
{
  return updated_at;
}

string Images::GetUpper_left_x()
{
  return upper_left_x;
}

string Images::GetUpper_left_y()
{
  return upper_left_y;
}

void Images::AuxilaryFunction(string XORIGIN, string YORIGIN, double PR, double HR, double VR, double XOFFSET, double YOFFSET)
{
  /*********************************/
  /* Step 1: Set image orientation */
  /*********************************/
  SetUpper_left_x(XORIGIN);
  SetUpper_left_y(YORIGIN);

  /********************************/
  /* Step 2: Set pixel resolution */
  /********************************/
  SetPixel_resolution(PR);
  SetHorizontal_resolution(HR);
  SetVertical_resolution(VR);

  /*******************************/
  /* Step 3: Set x and y offsets */
  /*******************************/
  SetX_offset(XOFFSET);
  SetY_offset(YOFFSET);

  /********************************************/
  /* Step 4: Retrieve relative x and y values */
  /********************************************/
  RetrieveX_relative();
  RetrieveY_relative();

  /*******************************************/
  /* Step 4: Retrieve image width and height */
  /*******************************************/
  RetrieveWidth();
  RetrieveHeight();

  /*****************************************************/
  /* Step 5: Calculate physical image width and height */
  /*****************************************************/
  CalculatePhysical_width();
  CalculatePhysical_height();

  /*****************************************************/
  /* Step 6: Calculate (x, y) position of image origin */
  /*****************************************************/
  CalculateX_origin();
  CalculateY_origin();

  /*******************************************************/
  /* Step 7: Calculate bounding region x and y positions */
  /*******************************************************/
  CalculateX_high();
  CalculateX_low();
  CalculateY_high();
  CalculateY_low();
}

void Images::CalculatePhysical_height()
{
  physical_height = height*vertical_resolution;
}

void Images::CalculatePhysical_width()
{
  physical_width = width*horizontal_resolution;
}

void Images::CalculateX_high()
{
  /*****************************************/
  /* Calculate maximum x position of image */
  /*****************************************/
  x_high = (upper_left_x.compare("MAX") == 0) ? x_origin : x_origin+physical_width; // Unit: meter
}

void Images::CalculateX_low()
{
  /*****************************************/
  /* Calculate minimum x position of image */
  /*****************************************/
  x_low = (upper_left_x.compare("MIN") == 0) ? x_origin : x_origin-physical_width; // Unit: meter
}

void Images::CalculateX_origin()
{
  /************************************************************************************************/
  /* Calculate x position of subimage's upper left corner as viewed by user (Defined as x origin) */
  /************************************************************************************************/
  x_origin = (upper_left_x.compare("MIN") == 0) ? x_offset+x_relative*horizontal_resolution : x_offset-x_relative*horizontal_resolution; // Unit: meter
}

void Images::CalculateY_high()
{

  /*****************************************/
  /* Calculate maximum y position of image */
  /*****************************************/
  y_high = (upper_left_y.compare("MAX") == 0) ? y_origin : y_origin+physical_height; // Unit: meter
}

void Images::CalculateY_low()
{

  /*****************************************/
  /* Calculate minimum y position of image */
  /*****************************************/
  y_low = (upper_left_y.compare("MIN") == 0) ? y_origin : y_origin-physical_height; // Unit: meter
}

void Images::CalculateY_origin()
{

  /****************************************/
  /* Calculate global y position of image */
  /****************************************/
  y_origin = (upper_left_y.compare("MIN") == 0) ? y_offset+y_relative*vertical_resolution : y_offset-y_relative*vertical_resolution; // Unit: meter
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

void Images::SetHorizontal_resolution(double val)
{
  horizontal_resolution = val;
}

void Images::SetPixel_resolution(double val)
{
  pixel_resolution = val;
}

void Images::SetVertical_resolution(double val)
{
  vertical_resolution = val;
}

void Images::SetUpper_left_x(string str)
{
  upper_left_x = str;
}

void Images::SetUpper_left_y(string str)
{
  upper_left_y = str;
}

void Images::SetX_offset(double val)
{
  x_offset = val;
}

void Images::SetY_offset(double val)
{
  y_offset = val;
}

void * Images::GetValue(string field)
{
  if(field.compare("application_id") == 0)
  {
    return &application_id;
  }
  if(field.compare("created_at") == 0)
  {
    return &created_at;
  }
  if(field.compare("details") == 0)
  {
    return &details;
  }
  if(field.compare("done") == 0)
  {
    return &done;
  }
  if(field.compare("file_location") == 0)
  {
    return &file_location;
  }
  if(field.compare("height") == 0)
  {
    return &height;
  }
  if(field.compare("horizontal_resolution") == 0)
  {
    return &horizontal_resolution;
  }
  if(field.compare("id") == 0)
  {
    return &id;
  }
  if(field.compare("image_set_id") == 0)
  {
    return &image_set_id;
  }
  if(field.compare("name") == 0)
  {
    return &name;
  }
  if(field.compare("physical_height") == 0)
  {
    return &physical_height;
  }
  if(field.compare("physical_width") == 0)
  {
    return &physical_width;
  }
  if(field.compare("pixel_resolution") == 0)
  {
    return &pixel_resolution;
  }
  if(field.compare("premarked") == 0)
  {
    return &premarked;
  }
  if(field.compare("priority") == 0)
  {
    return &priority;
  }
  if(field.compare("sun_angle") == 0)
  {
    return &sun_angle;
  }  
  if(field.compare("updated_at") == 0)
  {
    return &updated_at;
  }
  if(field.compare("upper_left_x") == 0)
  {
    return &upper_left_x;
  }
  if(field.compare("upper_left_y") == 0)
  {
    return &upper_left_y;
  }
  if(field.compare("vertical_resolution") == 0)
  {
    return &vertical_resolution;
  }
  if(field.compare("width") == 0)
  {
    return &width;
  }
  if(field.compare("x_high") == 0)
  {
    return &x_high;
  }
  if(field.compare("x_low") == 0)
  {
    return &x_low;
  }
  if(field.compare("x_offset") == 0)
  {
    return &x_offset;
  }
  if(field.compare("x_origin") == 0)
  {
    return &x_origin;
  }
  if(field.compare("x_relative") == 0)
  {
    return &x_relative;
  }
  if(field.compare("y_high") == 0)
  {
    return &y_high;
  }
  if(field.compare("y_low") == 0)
  {
    return &y_low;
  }
  if(field.compare("y_offset") == 0)
  {
    return &y_offset;
  }
  if(field.compare("y_origin") == 0)
  {
    return &y_origin;
  }
  if(field.compare("y_relative") == 0)
  {
    return &y_relative;
  }
  return NULL;
}
