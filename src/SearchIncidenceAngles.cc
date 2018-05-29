#include "SearchIncidenceAngles.h"

using namespace std;

bool SearchIncidenceAngles::EqualityComparison(vector <IncidenceAngles> &incidenceangles, int index, string field, void *value)
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("name") == 0)
  {
    return (incidenceangles[index].GetName().compare(*static_cast<string *>(value)) == 0);
  }
  if(field.compare("incidence_angle") == 0)
  {
    return (incidenceangles[index].GetIncidence_angle() == *static_cast<double *>(value));
  }

  return false;
}

bool SearchIncidenceAngles::GreaterThanComparison(vector <IncidenceAngles> &incidenceangles, int index, string field, void *value)
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("name") == 0)
  {
    return (incidenceangles[index].GetName() > *static_cast<string *>(value));
  }
  if(field.compare("incidence_angle") == 0)
  {
    return (incidenceangles[index].GetIncidence_angle() > *static_cast<double *>(value));
  }

  return false;
}

bool SearchIncidenceAngles::LessThanComparison(vector <IncidenceAngles> &incidenceangles, int index, string field, void *value)
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("name") == 0)
  {
    return (incidenceangles[index].GetName() < *static_cast<string *>(value));
  }
  if(field.compare("incidence_angle") == 0)
  {
    return (incidenceangles[index].GetIncidence_angle() < *static_cast<double *>(value));
  }

  return false;
}

double SearchIncidenceAngles::Difference(vector <IncidenceAngles> &incidenceangles, int index, string field, void *value)
{
  /********************************/
  /* Retrieve field column number */
  /********************************/
  if(field.compare("name") == 0)
  {
    return static_cast<double>(incidenceangles[index].GetName().compare(*static_cast<string *>(value)));
  }
  if(field.compare("incidence_angle") == 0)
  {
    return (incidenceangles[index].GetIncidence_angle() - *static_cast<double *>(value));
  }

  return false;
}

int SearchIncidenceAngles::BinarySearch(vector <IncidenceAngles> &incidenceangles, int m, int n, string field, void *value)
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
    if(EqualityComparison(incidenceangles, midpoint, field, value))
    {
      return midpoint;
    }

    /**************************************************/
    /* If value of the middle element is smaller than */
    /* the wanted value, then the wanted value must   */
    /* reside in the right portion of the array.      */
    /**************************************************/
    if(LessThanComparison(incidenceangles, midpoint, field, value))
    {
      return BinarySearch(incidenceangles, midpoint+1, n, field, value);
    }

    /*************************************************/
    /* If value of the middle element is larger than */
    /* the wanted value, then the wanted value must  */
    /* reside in the left portion of the array.      */
    /*************************************************/
    if(GreaterThanComparison(incidenceangles, midpoint, field, value))
    {
      return BinarySearch(incidenceangles, m, midpoint-1, field, value);
    }
  }

  /***********************************************************/
  /* If value is not present in array, return negative index */
  /***********************************************************/
  return -1;
}

int SearchIncidenceAngles::FirstNearestValue(vector <IncidenceAngles> &incidenceangles, int m, int n, string field, void *value)
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
    diff1 = Difference(incidenceangles, boundary1, field, value);
    diff2 = Difference(incidenceangles, boundary2, field, value);
    
    /*************************************************/
    /* If either differences equal zero, simply find */
    /* the first occurence of value in data set      */
    /*************************************************/
    if((diff1 == 0) || (diff2 == 0))
    {
      return FirstOccurence(incidenceangles, m, n, field, value);
    }
  
    /**************************************/
    /* If the first difference is greater */
    /* than zero, examine first quantile  */
    /**************************************/
    if(diff1 > 0)
    {
      return FirstNearestValue(incidenceangles, 0, boundary1-1, field, value);
    }

    /*************************************/
    /* If the second difference is less  */
    /* than zero, examine third quantile */
    /**************************************/
    if(diff2 < 0)
    {
      return FirstNearestValue(incidenceangles, boundary2+1, n, field, value);
    }

    /*********************************************/
    /* If zero lies between the two differences, */
    /* then examine second quantile              */
    /*********************************************/
    if((diff1 < 0) && (diff2 > 0))
    {
      return FirstNearestValue(incidenceangles, boundary1+1, boundary2-1, field, value);
    }
  }

  /************************************************************/
  /* Calculate difference between value to value at the index */
  /* of m one and repeat for the value at the index of n      */
  /************************************************************/
  diff1 = Difference(incidenceangles, m, field, value);
  diff2 = Difference(incidenceangles, n, field, value);
    
  return (diff1 < diff2) ? FirstOccurence(incidenceangles, m, n, field, incidenceangles[m].GetValue(field)) : FirstOccurence(incidenceangles, m, n, field, incidenceangles[n].GetValue(field));
}

int SearchIncidenceAngles::FirstOccurence(vector <IncidenceAngles> &incidenceangles, int m, int n, string field, void *value)
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
    if(LessThanComparison(incidenceangles, midpoint, field, value))
    {
      return FirstOccurence(incidenceangles, midpoint, n, field, value);
    }
    else
    {
      return FirstOccurence(incidenceangles, m, midpoint, field, value);
    }
  }

  /*********************************************************/
  /* Check to see if quantities at indicies m or n matches */
  /* reference value when indicies are one unit apart      */
  /*********************************************************/
  if(EqualityComparison(incidenceangles, m, field, value))
  {
    return m;
  }
  if(EqualityComparison(incidenceangles, n, field, value))
  {
    return n;
  }

  return -1;
}

int SearchIncidenceAngles::LastNearestValue(vector <IncidenceAngles> &incidenceangles, int m, int n, string field, void *value)
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
    diff1 = Difference(incidenceangles, boundary1, field, value);
    diff2 = Difference(incidenceangles, boundary2, field, value);
    
    /*************************************************/
    /* If either differences equal zero, simply find */
    /* the first occurence of value in data set      */
    /*************************************************/
    if((diff1 == 0) || (diff2 == 0))
    {
      return LastOccurence(incidenceangles, m, n, field, value);
    }
  
    /**************************************/
    /* If the first difference is greater */
    /* than zero, examine first quantile  */
    /**************************************/
    if(diff1 > 0)
    {
      return LastNearestValue(incidenceangles, 0, boundary1-1, field, value);
    }

    /*************************************/
    /* If the second difference is less  */
    /* than zero, examine third quantile */
    /**************************************/
    if(diff2 < 0)
    {
      return LastNearestValue(incidenceangles, boundary2+1, n, field, value);
    }

    /*********************************************/
    /* If zero lies between the two differences, */
    /* then examine second quantile              */
    /*********************************************/
    if((diff1 < 0) && (diff2 > 0))
    {
      return LastNearestValue(incidenceangles, boundary1+1, boundary2-1, field, value);
    }
  }

  /************************************************************/
  /* Calculate difference between value to value at the index */
  /* of m one and repeat for the value at the index of n      */
  /************************************************************/
  diff1 = Difference(incidenceangles, m, field, value);
  diff2 = Difference(incidenceangles, n, field, value);
    
  return (diff1 < diff2) ? LastOccurence(incidenceangles, m, n, field, incidenceangles[m].GetValue(field)) : LastOccurence(incidenceangles, m, n, field, incidenceangles[n].GetValue(field));
}


int SearchIncidenceAngles::LastOccurence(vector <IncidenceAngles> &incidenceangles, int m, int n, string field, void *value)
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
    if(GreaterThanComparison(incidenceangles, midpoint, field, value))
    {
      return LastOccurence(incidenceangles, m, midpoint, field, value);
    }
    else
    {
      return LastOccurence(incidenceangles, midpoint, n, field, value);
    }
  }

  /*********************************************************/
  /* Check to see if quantities at indicies m or n matches */
  /* reference value when indicies are one unit apart      */
  /*********************************************************/
  if(EqualityComparison(incidenceangles, n, field, value))
  {
    return n;
  }
  if(EqualityComparison(incidenceangles, m, field, value))
  {
    return m;
  }

  return -1;  
}
