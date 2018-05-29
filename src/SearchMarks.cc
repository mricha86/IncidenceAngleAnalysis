#include "SearchMarks.h"

using namespace std;

bool SearchMarks::EqualityComparison(vector <Marks> &marks, int index, string field, void *value)
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("id") == 0)
  {
    return (marks[index].GetId() == *static_cast<int *>(value));
  }
  if(field.compare("user_id") == 0)
  {
    return (marks[index].GetUser_id() == *static_cast<int *>(value));
  }
  if(field.compare("image_id") == 0)
  {
    return (marks[index].GetImage_id() == *static_cast<int *>(value));
  }
  if(field.compare("application_id") == 0)
  {
    return (marks[index].GetApplication_id() == *static_cast<int *>(value));
  }
  if(field.compare("image_user_id") == 0)
  {
    return (marks[index].GetImage_user_id() == *static_cast<int *>(value));
  }
  if(field.compare("machine_mark_id") == 0)
  {
    return (marks[index].GetMachine_mark_id() == *static_cast<int *>(value));
  }
  if(field.compare("shared_mark_id") == 0)
  {
    return (marks[index].GetShared_mark_id() == *static_cast<int *>(value));
  }
  if(field.compare("x") == 0)
  {
    return (marks[index].GetX() == *static_cast<double *>(value));
  }
  if(field.compare("y") == 0)
  {
    return (marks[index].GetY() == *static_cast<double *>(value));
  }
  if(field.compare("diameter") == 0)
  {
    return (marks[index].GetDiameter() == *static_cast<double *>(value));
  }
  if(field.compare("submit_time") == 0)
  {
    return (marks[index].GetSubmit_time() == *static_cast<int *>(value));
  }
  if(field.compare("confirmed") == 0)
  {
    return (marks[index].GetConfirmed() == *static_cast<int *>(value));
  }
  if(field.compare("score") == 0)
  {
    return (marks[index].GetScore() == *static_cast<double *>(value));
  }
  if(field.compare("type") == 0)
  {
    return (marks[index].GetType().compare(*static_cast<string *>(value)) == 0);
  }
  if(field.compare("sub_type") == 0)
  {
    return (marks[index].GetSub_type().compare(*static_cast<string *>(value)) == 0);
  }
  if(field.compare("details") == 0)
  {
    return (marks[index].GetDetails().compare(*static_cast<string *>(value)) == 0);
  }
  if(field.compare("created_at") == 0)
  {
    return (marks[index].GetCreated_at().compare(*static_cast<string *>(value)) == 0);
  }
  if(field.compare("updated_at") == 0)
  {
    return (marks[index].GetUpdated_at().compare(*static_cast<string *>(value)) == 0);
  }

  return false;
}

bool SearchMarks::GreaterThanComparison(vector <Marks> &marks, int index, string field, void *value)
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("id") == 0)
  {
    return (marks[index].GetId() > *static_cast<int *>(value));
  }
  if(field.compare("user_id") == 0)
  {
    return (marks[index].GetUser_id() > *static_cast<int *>(value));
  }
  if(field.compare("image_id") == 0)
  {
    return (marks[index].GetImage_id() > *static_cast<int *>(value));
  }
  if(field.compare("application_id") == 0)
  {
    return (marks[index].GetApplication_id() > *static_cast<int *>(value));
  }
  if(field.compare("image_user_id") == 0)
  {
    return (marks[index].GetImage_user_id() > *static_cast<int *>(value));
  }
  if(field.compare("machine_mark_id") == 0)
  {
    return (marks[index].GetMachine_mark_id() > *static_cast<int *>(value));
  }
  if(field.compare("shared_mark_id") == 0)
  {
    return (marks[index].GetShared_mark_id() > *static_cast<int *>(value));
  }
  if(field.compare("x") == 0)
  {
    return (marks[index].GetX() > *static_cast<double *>(value));
  }
  if(field.compare("y") == 0)
  {
    return (marks[index].GetY() > *static_cast<double *>(value));
  }
  if(field.compare("diameter") == 0)
  {
    return (marks[index].GetDiameter() > *static_cast<double *>(value));
  }
  if(field.compare("submit_time") == 0)
  {
    return (marks[index].GetSubmit_time() > *static_cast<int *>(value));
  }
  if(field.compare("confirmed") == 0)
  {
    return (marks[index].GetConfirmed() > *static_cast<int *>(value));
  }
  if(field.compare("score") == 0)
  {
    return (marks[index].GetScore() > *static_cast<double *>(value));
  }
  if(field.compare("type") == 0)
  {
    return (marks[index].GetType() > *static_cast<string *>(value));
  }
  if(field.compare("sub_type") == 0)
  {
    return (marks[index].GetSub_type() > *static_cast<string *>(value));
  }
  if(field.compare("details") == 0)
  {
    return (marks[index].GetDetails() > *static_cast<string *>(value));
  }
  if(field.compare("created_at") == 0)
  {
    return (marks[index].GetCreated_at() > *static_cast<string *>(value));
  }
  if(field.compare("updated_at") == 0)
  {
    return (marks[index].GetUpdated_at() > *static_cast<string *>(value));
  }

  return false;
}

bool SearchMarks::LessThanComparison(vector <Marks> &marks, int index, string field, void *value)
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("id") == 0)
  {
    return (marks[index].GetId() < *static_cast<int *>(value));
  }
  if(field.compare("user_id") == 0)
  {
    return (marks[index].GetUser_id() < *static_cast<int *>(value));
  }
  if(field.compare("image_id") == 0)
  {
    return (marks[index].GetImage_id() < *static_cast<int *>(value));
  }
  if(field.compare("application_id") == 0)
  {
    return (marks[index].GetApplication_id() < *static_cast<int *>(value));
  }
  if(field.compare("image_user_id") == 0)
  {
    return (marks[index].GetImage_user_id() < *static_cast<int *>(value));
  }
  if(field.compare("machine_mark_id") == 0)
  {
    return (marks[index].GetMachine_mark_id() < *static_cast<int *>(value));
  }
  if(field.compare("shared_mark_id") == 0)
  {
    return (marks[index].GetShared_mark_id() < *static_cast<int *>(value));
  }
  if(field.compare("x") == 0)
  {
    return (marks[index].GetX() < *static_cast<double *>(value));
  }
  if(field.compare("y") == 0)
  {
    return (marks[index].GetY() < *static_cast<double *>(value));
  }
  if(field.compare("diameter") == 0)
  {
    return (marks[index].GetDiameter() < *static_cast<double *>(value));
  }
  if(field.compare("submit_time") == 0)
  {
    return (marks[index].GetSubmit_time() < *static_cast<int *>(value));
  }
  if(field.compare("confirmed") == 0)
  {
    return (marks[index].GetConfirmed() < *static_cast<int *>(value));
  }
  if(field.compare("score") == 0)
  {
    return (marks[index].GetScore() < *static_cast<double *>(value));
  }
  if(field.compare("type") == 0)
  {
    return (marks[index].GetType() < *static_cast<string *>(value));
  }
  if(field.compare("sub_type") == 0)
  {
    return (marks[index].GetSub_type() < *static_cast<string *>(value));
  }
  if(field.compare("details") == 0)
  {
    return (marks[index].GetDetails() < *static_cast<string *>(value));
  }
  if(field.compare("created_at") == 0)
  {
    return (marks[index].GetCreated_at() < *static_cast<string *>(value));
  }
  if(field.compare("updated_at") == 0)
  {
    return (marks[index].GetUpdated_at() < *static_cast<string *>(value));
  }

  return false;
}

double SearchMarks::Difference(vector <Marks> &marks, int index, string field, void *value)
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("id") == 0)
  {
    return static_cast<double>(marks[index].GetId() - *static_cast<int *>(value));
  }
  if(field.compare("user_id") == 0)
  {
    return static_cast<double>(marks[index].GetUser_id() - *static_cast<int *>(value));
  }
  if(field.compare("image_id") == 0)
  {
    return static_cast<double>(marks[index].GetImage_id() - *static_cast<int *>(value));
  }
  if(field.compare("application_id") == 0)
  {
    return static_cast<double>(marks[index].GetApplication_id() - *static_cast<int *>(value));
  }
  if(field.compare("image_user_id") == 0)
  {
    return static_cast<double>(marks[index].GetImage_user_id() - *static_cast<int *>(value));
  }
  if(field.compare("machine_mark_id") == 0)
  {
    return static_cast<double>(marks[index].GetMachine_mark_id() - *static_cast<int *>(value));
  }
  if(field.compare("shared_mark_id") == 0)
  {
    return static_cast<double>(marks[index].GetShared_mark_id() - *static_cast<int *>(value));
  }
  if(field.compare("x") == 0)
  {
    return static_cast<double>(marks[index].GetX() - *static_cast<double *>(value));
  }
  if(field.compare("y") == 0)
  {
    return static_cast<double>(marks[index].GetY() - *static_cast<double *>(value));
  }
  if(field.compare("diameter") == 0)
  {
    return static_cast<double>(marks[index].GetDiameter() - *static_cast<double *>(value));
  }
  if(field.compare("submit_time") == 0)
  {
    return static_cast<double>(marks[index].GetSubmit_time() - *static_cast<int *>(value));
  }
  if(field.compare("confirmed") == 0)
  {
    return static_cast<double>(marks[index].GetConfirmed() - *static_cast<int *>(value));
  }
  if(field.compare("score") == 0)
  {
    return static_cast<double>(marks[index].GetScore() - *static_cast<double *>(value));
  }
  if(field.compare("type") == 0)
  {
    return static_cast<double>(marks[index].GetType().compare(*static_cast<string *>(value)));
  }
  if(field.compare("sub_type") == 0)
  {
    return static_cast<double>(marks[index].GetSub_type().compare(*static_cast<string *>(value)));
  }
  if(field.compare("details") == 0)
  {
    return static_cast<double>(marks[index].GetDetails().compare(*static_cast<string *>(value)));
  }
  if(field.compare("created_at") == 0)
  {
    return static_cast<double>(marks[index].GetCreated_at().compare(*static_cast<string *>(value)));
  }
  if(field.compare("updated_at") == 0)
  {
    return static_cast<double>(marks[index].GetUpdated_at().compare(*static_cast<string *>(value)));
  }

  return false;
}

int SearchMarks::BinarySearch(vector <Marks> &marks, int m, int n, string field, void *value)
{
  if(n >= m)
  {
    /***********************************/
    /* Calculate value of middle index */
    /***********************************/
    int midpoint = m+(n-m)/2;
    
    /****************************************************/
    /* Compare wanted value to value of middle element. */
    /* If equal, return index of middle element.        */
    /****************************************************/
    if(EqualityComparison(marks, midpoint, field, value))
    {
      return midpoint;
    }

    /**************************************************/
    /* If value of the middle element is smaller than */
    /* the wanted value, then the wanted value must   */
    /* reside in the right portion of the array.      */
    /**************************************************/
    if(LessThanComparison(marks, midpoint, field, value))
    {
      return BinarySearch(marks, midpoint+1, n, field, value);
    }

    /*************************************************/
    /* If value of the middle element is larger than */
    /* the wanted value, then the wanted value must  */
    /* reside in the left portion of the array.      */
    /*************************************************/
    if(GreaterThanComparison(marks, midpoint, field, value))
    {
      return BinarySearch(marks, m, midpoint-1, field, value);
    }
  }

  /***********************************************************/
  /* If value is not present in array, return negative index */
  /***********************************************************/
  return -1;
}

int SearchMarks::FirstNearestValue(vector <Marks> &marks, int m, int n, string field, void *value)
{
  /*************************************************/
  /* Declaration/Initialization of class variables */
  /*************************************************/
  double diff1;
  double diff2;
  
  if((n-m) > 1)
  {
    /******************************************************************/
    /* Calculate index at boundary between first and second quantile. */
    /* Calculate index at boundary between second and third quantile. */
    /******************************************************************/
    int boundary1 = m+(n-m)/3;
    int boundary2 = m+2*(n-m)/3;
    
    /************************************************************************/
    /* Calculate difference between value to value at the index of boundary */
    /* one and repeat for the value at the index of boundary two            */
    /************************************************************************/  
    diff1 = Difference(marks, boundary1, field, value);
    diff2 = Difference(marks, boundary2, field, value);
    
    /*************************************************/
    /* If either differences equal zero, simply find */
    /* the first occurence of value in data set      */
    /*************************************************/
    if((diff1 == 0) || (diff2 == 0))
    {
      return FirstOccurence(marks, m, n, field, value);
    }
  
    /**************************************/
    /* If the first difference is greater */
    /* than zero, examine first quantile  */
    /**************************************/
    if(diff1 > 0)
    {
      return FirstNearestValue(marks, 0, boundary1-1, field, value);
    }

    /*************************************/
    /* If the second difference is less  */
    /* than zero, examine third quantile */
    /**************************************/
    if(diff2 < 0)
    {
      return FirstNearestValue(marks, boundary2+1, n, field, value);
    }

    /*********************************************/
    /* If zero lies between the two differences, */
    /* then examine second quantile              */
    /*********************************************/
    if((diff1 < 0) && (diff2 > 0))
    {
      return FirstNearestValue(marks, boundary1+1, boundary2-1, field, value);
    }
  }

  /************************************************************/
  /* Calculate difference between value to value at the index */
  /* of m one and repeat for the value at the index of n      */
  /************************************************************/
  diff1 = Difference(marks, m, field, value);
  diff2 = Difference(marks, n, field, value);
    
  return (diff1 < diff2) ? FirstOccurence(marks, m, n, field, marks[m].GetValue(field)) : FirstOccurence(marks, m, n, field, marks[n].GetValue(field));
}

int SearchMarks::FirstOccurence(vector <Marks> &marks, int m, int n, string field, void *value)
{
  if((n-m) > 1)
  {
    /***********************************************************/
    /* Find midpoint between upper and lower bounding indicies */
    /***********************************************************/
    int midpoint = m+(n-m)/2;

    /*********************************************************/
    /* Compare value of midpoint element to reference value. */
    /* If less than reference value, move lowerbounding      */
    /* index to midpoint position. If equal to searched      */
    /* value, move upperbounding index to midpoint position  */
    /*********************************************************/
    if(LessThanComparison(marks, midpoint, field, value))
    {
      return FirstOccurence(marks, midpoint, n, field, value);
    }
    else
    {
      return FirstOccurence(marks, m, midpoint, field, value);
    }
  }

  /*********************************************************/
  /* Check to see if quantities at indicies m or n matches */
  /* reference value when indicies are one unit apart      */
  /*********************************************************/
  if(EqualityComparison(marks, m, field, value))
  {
    return m;
  }
  if(EqualityComparison(marks, n, field, value))
  {
    return n;
  }

  return -1;
}

int SearchMarks::LastNearestValue(vector <Marks> &marks, int m, int n, string field, void *value)
{
  /*************************************************/
  /* Declaration/Initialization of class variables */
  /*************************************************/
  double diff1;
  double diff2;
  
  if((n-m) > 1)
  {
    /******************************************************************/
    /* Calculate index at boundary between first and second quantile. */
    /* Calculate index at boundary between second and third quantile. */
    /******************************************************************/
    int boundary1 = m+(n-m)/3;
    int boundary2 = m+2*(n-m)/3;
    
    /************************************************************************/
    /* Calculate difference between value to value at the index of boundary */
    /* one and repeat for the value at the index of boundary two            */
    /************************************************************************/  
    diff1 = Difference(marks, boundary1, field, value);
    diff2 = Difference(marks, boundary2, field, value);
    
    /*************************************************/
    /* If either differences equal zero, simply find */
    /* the first occurence of value in data set      */
    /*************************************************/
    if((diff1 == 0) || (diff2 == 0))
    {
      return LastOccurence(marks, m, n, field, value);
    }
  
    /**************************************/
    /* If the first difference is greater */
    /* than zero, examine first quantile  */
    /**************************************/
    if(diff1 > 0)
    {
      return LastNearestValue(marks, 0, boundary1-1, field, value);
    }

    /*************************************/
    /* If the second difference is less  */
    /* than zero, examine third quantile */
    /**************************************/
    if(diff2 < 0)
    {
      return LastNearestValue(marks, boundary2+1, n, field, value);
    }

    /*********************************************/
    /* If zero lies between the two differences, */
    /* then examine second quantile              */
    /*********************************************/
    if((diff1 < 0) && (diff2 > 0))
    {
      return LastNearestValue(marks, boundary1+1, boundary2-1, field, value);
    }
  }

  /************************************************************/
  /* Calculate difference between value to value at the index */
  /* of m one and repeat for the value at the index of n      */
  /************************************************************/
  diff1 = Difference(marks, m, field, value);
  diff2 = Difference(marks, n, field, value);
    
  return (diff1 < diff2) ? LastOccurence(marks, m, n, field, marks[m].GetValue(field)) : LastOccurence(marks, m, n, field, marks[n].GetValue(field));
}


int SearchMarks::LastOccurence(vector <Marks> &marks, int m, int n, string field, void *value)
{
  if((n-m) > 1)
  {
    /***********************************************************/
    /* Find midpoint between upper and lower bounding indicies */
    /***********************************************************/
    int midpoint = m+(n-m)/2;
    
    /********************************************************/
    /* Compare value of midpoint element to searched value. */
    /* If less than searched value, move lowerbounding      */
    /* index to midpoint position. If equal to searched     */
    /* value, move upperbounding index to midpoint position */
    /********************************************************/
    if(GreaterThanComparison(marks, midpoint, field, value))
    {
      return LastOccurence(marks, m, midpoint, field, value);
    }
    else
    {
      return LastOccurence(marks, midpoint, n, field, value);
    }
  }

  /*********************************************************/
  /* Check to see if quantities at indicies m or n matches */
  /* reference value when indicies are one unit apart      */
  /*********************************************************/
  if(EqualityComparison(marks, n, field, value))
  {
    return n;
  }
  if(EqualityComparison(marks, m, field, value))
  {
    return m;
  }

  return -1;  
}
