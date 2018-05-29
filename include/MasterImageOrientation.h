/* HEADER FILE: MasterImageOrientation.h */

#ifndef MASTERIMAGEORIENTATION_H
#define MASTERIMAGEORIENTATION_H
#include <string>
#include <vector>

class MasterImageOrientation
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    std::string name;
    std::string upper_left_latitude;
    std::string upper_left_longitude;

  /***********************************/
  /* Declaration of class functions */
  /***********************************/
  public:
    MasterImageOrientation(std::string, std::string ,std::string);
    std::string GetName();
    std::string GetUpper_left_latitude();
    std::string GetUpper_left_longitude();
    void * GetValue(std::string);
};

#endif
