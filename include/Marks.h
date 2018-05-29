/* HEADER FILE: Marks.h */

#ifndef MARKS_H
#define MARKS_H
#include <string>

class Marks
{
  /***********************************/
  /* Declaration of class variables */
  /***********************************/
  private:
    double diameter;
    double score;
    double x;
    double y;
    int application_id;
    int confirmed;
    int id;
    int image_id;
    int image_user_id;
    int machine_mark_id;
    int shared_mark_id;
    int submit_time;
    int user_id;
    std::string created_at;
    std::string details;
    std::string sub_type;
    std::string type;
    std::string updated_at;

  /************************************/
  /* Declaration of class functions */
  /************************************/
  public:
    Marks(int, int, int, int, int, int, int, double, double, double, int, int, double, std::string, std::string, std::string, std::string, std::string);
    double GetDiameter();
    double GetScore();
    double GetX();
    double GetY();
    int GetApplication_id();
    int GetConfirmed();
    int GetId();
    int GetImage_id();
    int GetImage_user_id();
    int GetMachine_mark_id();
    int GetShared_mark_id();
    int GetSubmit_time();
    int GetUser_id();
    std::string GetCreated_at();
    std::string GetDetails();
    std::string GetSub_type();
    std::string GetType();
    std::string GetUpdated_at();
    void * GetValue(std::string);
    void SetX(double);
    void SetY(double);
};

#endif
