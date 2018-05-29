#include "SortMarks.h"

using namespace std;

SortMarks::SortMarks(vector <Marks> &MARKS, string FIELD)
{
  field = FIELD;
  marks = MARKS;
}

bool SortMarks::cmp_by_application_id(Marks &a, Marks &b)
{
  return (a.GetApplication_id() < b.GetApplication_id());
}

bool SortMarks::cmp_by_confirmed(Marks &a, Marks &b)
{
  return (a.GetConfirmed() < b.GetConfirmed());
}

bool SortMarks::cmp_by_created_at(Marks &a, Marks &b)
{
  return (a.GetCreated_at() < b.GetCreated_at());
}

bool SortMarks::cmp_by_details(Marks &a, Marks &b)
{
  return (a.GetDetails() < b.GetDetails());
}

bool SortMarks::cmp_by_diameter(Marks &a, Marks &b)
{
  return (a.GetDiameter() < b.GetDiameter());
}

bool SortMarks::cmp_by_id(Marks &a, Marks &b)
{
  return (a.GetId() < b.GetId());
}

bool SortMarks::cmp_by_image_id(Marks &a, Marks &b)
{
  return (a.GetImage_id() < b.GetImage_id());
}

bool SortMarks::cmp_by_image_user_id(Marks &a, Marks &b)
{
  return (a.GetImage_user_id() < b.GetImage_user_id());
}

bool SortMarks::cmp_by_machine_mark_id(Marks &a, Marks &b)
{
  return (a.GetMachine_mark_id() < b.GetMachine_mark_id());
}

bool SortMarks::cmp_by_score(Marks &a, Marks &b)
{
  return (a.GetScore() < b.GetScore());
}

bool SortMarks::cmp_by_shared_mark_id(Marks &a, Marks &b)
{
  return (a.GetShared_mark_id() < b.GetShared_mark_id());
}

bool SortMarks::cmp_by_sub_type(Marks &a, Marks &b)
{
  return (a.GetSub_type() < b.GetSub_type());
}

bool SortMarks::cmp_by_submit_time(Marks &a, Marks &b)
{
  return (a.GetSubmit_time() < b.GetSubmit_time());
}

bool SortMarks::cmp_by_type(Marks &a, Marks &b)
{
  return (a.GetType() < b.GetType());
}

bool SortMarks::cmp_by_updated_at(Marks &a, Marks &b)
{
  return (a.GetUpdated_at() < b.GetUpdated_at());
}

bool SortMarks::cmp_by_user_id(Marks &a, Marks &b)
{
  return (a.GetUser_id() < b.GetUser_id());
}

bool SortMarks::cmp_by_x(Marks &a, Marks &b)
{
  return (a.GetX() < b.GetX());
}

bool SortMarks::cmp_by_y(Marks &a, Marks &b)
{
  return (a.GetY() < b.GetY());
}

int SortMarks::GetFieldValue()
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("id") == 0)
  {
    return 1;
  }
  if(field.compare("user_id") == 0)
  {
    return 2;
  }
  if(field.compare("image_id") == 0)
  {
    return 3;
  }
  if(field.compare("application_id") == 0)
  {
    return 4;
  }
  if(field.compare("image_user_id") == 0)
  {
    return 5;
  }
  if(field.compare("machine_mark_id") == 0)
  {
    return 6;
  }
  if(field.compare("shared_mark_id") == 0)
  {
    return 7;
  }
  if(field.compare("x") == 0)
  {
    return 8;
  }
  if(field.compare("y") == 0)
  {
    return 9;
  }
  if(field.compare("diameter") == 0)
  {
    return 10;
  }
  if(field.compare("submit_time") == 0)
  {
    return 11;
  }
  if(field.compare("confirmed") == 0)
  {
    return 12;
  }
  if(field.compare("score") == 0)
  {
    return 13;
  }
  if(field.compare("type") == 0)
  {
    return 14;
  }
  if(field.compare("sub_type") == 0)
  {
    return 15;
  }
  if(field.compare("details") == 0)
  {
    return 16;
  }
  if(field.compare("created_at") == 0)
  {
    return 17;
  }
  if(field.compare("updated_at") == 0)
  {
    return 18;
  }

  return 0;
}

vector <Marks> SortMarks::GetMarks()
{
  return marks;
}

void SortMarks::arrange()
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
      sort(marks.begin(), marks.end(), cmp_by_id);
      break;
    }
    case 2:
    {
      sort(marks.begin(), marks.end(), cmp_by_user_id);
      break;
    }
    case 3:
    {
      sort(marks.begin(), marks.end(), cmp_by_image_id);
      break;
    }
    case 4:
    {
      sort(marks.begin(), marks.end(), cmp_by_application_id);
      break;
    }
    case 5:
    {
      sort(marks.begin(), marks.end(), cmp_by_image_user_id);
      break;
    }
    case 6:
    {
      sort(marks.begin(), marks.end(), cmp_by_machine_mark_id);
      break;
    }
    case 7:
    {
      sort(marks.begin(), marks.end(), cmp_by_shared_mark_id);
      break;
    }
    case 8:
    {
      sort(marks.begin(), marks.end(), cmp_by_x);
      break;
    }
    case 9:
    {
      sort(marks.begin(), marks.end(), cmp_by_y);
      break;
    }
    case 10:
    {
      sort(marks.begin(), marks.end(), cmp_by_diameter);
      break;
    }
    case 11:
    {
      sort(marks.begin(), marks.end(), cmp_by_submit_time);
      break;
    }
    case 12:
    {
      sort(marks.begin(), marks.end(), cmp_by_confirmed);
      break;
    }
    case 13:
    {
      sort(marks.begin(), marks.end(), cmp_by_score);
      break;
    }
    case 14:
    {
      sort(marks.begin(), marks.end(), cmp_by_type);
      break;
    }
    case 15:
    {
      sort(marks.begin(), marks.end(), cmp_by_sub_type);
      break;
    }
    case 16:
    {
      sort(marks.begin(), marks.end(), cmp_by_details);
      break;
    }
    case 17:
    {
      sort(marks.begin(), marks.end(), cmp_by_created_at);
      break;
    }
    case 18:
    {
      sort(marks.begin(), marks.end(), cmp_by_updated_at);
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
