#include "Marks.h"

using namespace std;

Marks::Marks(int ID, int UID, int IID, int AID, int IUID, int MMID, int SMID, double X, double Y, double DIA, int SUBTIME, int C, double S, string T, string SUBTYPE, string DET, string CREATE, string UPDATE)
{
  diameter = DIA;
  score = S;
  x = X;
  y = Y;
  application_id = AID;
  confirmed = C;
  id = ID;
  image_id = IID;
  image_user_id = IUID;
  machine_mark_id = MMID;
  shared_mark_id = SMID;
  submit_time = SUBTIME;
  user_id = UID;
  created_at = CREATE;
  details = DET;
  sub_type = SUBTYPE;
  type = T;
  updated_at = UPDATE;
}

double Marks::GetDiameter()
{
  return diameter;
}

double Marks::GetScore()
{
  return score;
}

double Marks::GetX()
{
  return x;
}

double Marks::GetY()
{
  return y;
}

int Marks::GetApplication_id()
{
  return application_id;
}

int Marks::GetConfirmed()
{
  return confirmed;
}

int Marks::GetId()

{
  return id;
}

int Marks::GetImage_id()
{
  return image_id;
}

int Marks::GetImage_user_id()
{
  return image_user_id;
}

int Marks::GetMachine_mark_id()
{
  return machine_mark_id;
}

int Marks::GetShared_mark_id()
{
  return shared_mark_id;
}

int Marks::GetSubmit_time()
{
  return submit_time;
}

int Marks::GetUser_id()
{
  return user_id;
}

string Marks::GetCreated_at()
{
  return created_at;
}

string Marks::GetDetails()
{
  return details;
}

string Marks::GetSub_type()
{
  return sub_type;
}

string Marks::GetType()
{
  return type;
}

string Marks::GetUpdated_at()
{
  return updated_at;
}

void * Marks::GetValue(string field)
{
  if(field.compare("id") == 0)
  {
    return &id;
  }
  if(field.compare("user_id") == 0)
  {
    return &user_id;
  }
  if(field.compare("image_id") == 0)
  {
    return &image_id;
  }
  if(field.compare("application_id") == 0)
  {
    return &application_id;
  }
  if(field.compare("image_user_id") == 0)
  {
    return &image_user_id;
  }
  if(field.compare("machine_mark_id") == 0)
  {
    return &machine_mark_id;
  }
  if(field.compare("shared_mark_id") == 0)
  {
    return &shared_mark_id;
  }
  if(field.compare("x") == 0)
  {
    return &x;
  }
  if(field.compare("y") == 0)
  {
    return &y;
  }
  if(field.compare("diameter") == 0)
  {
    return &diameter;
  }
  if(field.compare("submit_time") == 0)
  {
    return &submit_time;
  }
  if(field.compare("confirmed") == 0)
  {
    return &confirmed;
  }
  if(field.compare("score") == 0)
  {
    return &score;
  }
  if(field.compare("type") == 0)
  {
    return &type;
  }
  if(field.compare("sub_type") == 0)
  {
    return &sub_type;
  }
  if(field.compare("details") == 0)
  {
    return &details;
  }
  if(field.compare("created_at") == 0)
  {
    return &created_at;
  }
  if(field.compare("updated_at") == 0)
  {
    return &updated_at;
  }

  return NULL;
}

void Marks::SetX(double value)
{
  x = value;
}

void Marks::SetY(double value)
{
  y = value;
}
