#include "RetrieveMarks.h"

using namespace std;
using namespace sql;

RetrieveMarks::RetrieveMarks(Connection *CONN, string TABLE, string FIELD, string OPTION)
{
  /*******************************************************************/
  /* Retrieve needed information for database information extraction */
  /*******************************************************************/
  conn = CONN;
  table = TABLE;
  field = FIELD;
  option = OPTION;
}
    
vector <Marks> RetrieveMarks::GetData()
{
  return data;
}

void RetrieveMarks::Display(vector <Marks> &list)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  int nelements;

  /********************/
  /* Print header row */
  /********************/
  printf("%10s %10s %10s %3s %10s %10s %10s %8s %8s %8s %10s %4s %8s %6s %7s %7s %6s %6s\n", "ID", "UID", "IID", "AID", "IUID", "MMID", "SMID", "X", "Y", "DIAMETER", "SUBTIME", "CONF", "SCORE", "TYPE", "SUBTYPE", "DETAILS", "CREATE", "UPDATE");
  
  /********************/
  /* Print data rows */
  /********************/
  nelements = (int)list.size();
  for(int i=0; i<nelements; i++)
    printf("%10d %10d %10d %3d %10d %10d %10d %8.2lf %8.2lf %8.2lf %10d %4d %8.2lf %6s %7s %7s %6s %6s\n", list[i].GetId(), list[i].GetUser_id(), list[i].GetImage_id(), list[i].GetApplication_id(), list[i].GetImage_user_id(), list[i].GetMachine_mark_id(), list[i].GetShared_mark_id(), list[i].GetX(), list[i].GetY(), list[i].GetDiameter(), list[i].GetSubmit_time(), list[i].GetConfirmed(), list[i].GetScore(), list[i].GetType().c_str(), list[i].GetSub_type().c_str(), list[i].GetDetails().c_str(), list[i].GetCreated_at().c_str(), list[i].GetUpdated_at().c_str());

  return;
}

void RetrieveMarks::Fetch()
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

    /**********************/
    /* Prepared Statement */
    /**********************/
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
      	Marks myMark(rs->getInt("id"), 0, rs->getInt("image_id"), rs->getInt("application_id"), 0, 0, 0, rs->getDouble("x"), rs->getDouble("y"), rs->getDouble("diameter"), 0, 0, 0, "", "", "", "", "");
      	data.push_back(myMark);
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

