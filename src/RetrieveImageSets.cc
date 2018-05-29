#include "RetrieveImageSets.h"

using namespace std;
using namespace sql;

RetrieveImageSets::RetrieveImageSets(Connection *CONN, string TABLE, string FIELD, string OPTION)
{
  /*******************************************************************/
  /* Retrieve needed information for database information extraction */
  /*******************************************************************/
  conn = CONN;
  table = TABLE;
  field = FIELD;
  option = OPTION;
}
    
vector <ImageSets> RetrieveImageSets::GetData()
{
  return data;
}

void RetrieveImageSets::Display(vector <ImageSets> &list)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  int nelements;

  /********************/
  /* Print header row */
  /********************/
  printf("%-2s %-12s %-3s %6s %6s %7s %7s %-7s %4s %4s %4s %11s %11s\n", 
	 "ID",
	 "NAME",
	 "AID",
	 "MINLAT",
	 "MAXLAT",
	 "MINLONG", 
	 "MAXLONG",  
	 "DETAILS", 
	 "PR",
	 "HR",
	 "VR",
	 "XORIGIN", 
	 "YORIGIN");
  
  /********************/
  /* Print data rows */
  /********************/
  nelements = (int)list.size();
  for(int i=0; i<nelements; i++)
    printf("%-2d %-12s %-3d %6.2lf %6.2lf %7.2lf %7.2lf %-7.7s %4.2lf %4.2lf %4.2lf %11.2lf %11.2lf\n", 
	   list[i].GetId(), 
	   list[i].GetName().c_str(), 
	   list[i].GetApplication_id(), 
	   list[i].GetMinimum_latitude(), 
	   list[i].GetMaximum_latitude(), 
	   list[i].GetMinimum_longitude(), 
	   list[i].GetMaximum_longitude(), 
	   list[i].GetDetails().c_str(),
	   list[i].GetPixel_resolution(), 
	   list[i].GetHorizontal_resolution(),
	   list[i].GetVertical_resolution(),
	   list[i].GetX_origin(), 
	   list[i].GetY_origin());

  return;
}

void RetrieveImageSets::Fetch()
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  int columnsNumber;
  PreparedStatement *pst;
  ResultSet *rs;
  ResultSetMetaData *rsmd;
  string query;

  try
  {
    /************************/
    /* Define SQL selection */
    /************************/
    query = "SELECT " + field + " FROM " + table + option;

    /********************/
    /* Create Statement */
    /********************/
    pst = conn->prepareStatement(query.c_str());
      
    /***************************/
    /* Execute selection query */
    /***************************/
    rs = pst->executeQuery();
    
    /*****************/
    /* Retrieve data */
    /*****************/
    rsmd = rs->getMetaData();
    columnsNumber = rsmd->getColumnCount();
    while(rs->next())
    {
      int application_id = rs->getInt("application_id");
      if(application_id == 1)
      {
	ImageSets myImageSet(rs->getInt("id"), rs->getString("name"), application_id, 0, 0, rs->getDouble("minimum_latitude"), rs->getDouble("maximum_latitude"), rs->getDouble("minimum_longitude"), rs->getDouble("maximum_longitude"), rs->getDouble("pixel_resolution"), "", rs->getString("details"), "", "");
	data.push_back(myImageSet);
      }
    }
  }
  catch(SQLException &e)
  {
    printf("%s\n", e.what());
    exit(EXIT_FAILURE);
  }

  /*********************/
  /* Deallocate memory */
  /*********************/
  if(rs != NULL)
  {
    try
    {
      rs->close();
      rs = NULL;
    }
    catch(SQLException &e)
    {
      printf("%s\n", e.what());
      exit(EXIT_FAILURE);
    }
  }
  if(pst != NULL)
  {
    try
    {
      pst->close();
      pst = NULL;
    }
    catch(SQLException &e)
    {
      printf("%s\n", e.what());
      exit(EXIT_FAILURE);
    }
  }

  return;
}
