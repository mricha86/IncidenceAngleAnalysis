#include "MySQLConnection.h"

using namespace std;
using namespace sql;

MySQLConnection::MySQLConnection(string URL, string USER, string PW, string DATABASE)
{
  /*******************************************************/
  /* Retrieve needed information for database connection */
  /*******************************************************/
  database = DATABASE;
  password = PW;
  url = URL;
  user = USER;

  /**********************************************************************/
  /* Set connection to null, as no connection has been established, yet */
  /**********************************************************************/
  conn = NULL;
}
    
void MySQLConnection::Connect()
{
  /*****************************************************/
  /* Establish connection to CosmoQuest MySQL database */
  /*****************************************************/
  try
  {
    driver = get_driver_instance();
    conn = driver->connect(url.c_str(), user.c_str(), password.c_str());
    conn->setSchema(database.c_str());
  }
  catch(SQLException &e)
  {
    printf("%s\n", e.what());
    exit(EXIT_FAILURE);
  }
}

void MySQLConnection::Disconnect()
{
  /***********************************************/
  /* End connection to CosmoQuest MySQL database */
  /***********************************************/
  if(conn != NULL)
  {
    try
    {
      conn->close();
      conn = NULL;
    }
    catch(SQLException &e)
    {
      printf("Connection could not be broken!");
      printf("%s", e.what());
      exit(EXIT_FAILURE);
    }
  }
}

Connection * MySQLConnection::GetConnection()
{
  return conn;
}

void MySQLConnection::TestConnection()
{
  /************************************************/
  /* Test connection to CosmoQuest MySQL database */
  /************************************************/
  if(conn != NULL)
  {
    /*******************************************/
    /* Declaration/Initialization of variables */
    /*******************************************/
    int columnsNumber;
    ResultSet *rs;
    ResultSetMetaData *rsmd;
    PreparedStatement *ps;
    Statement *st;
    string Database;
    string hostname;
    string query;
	   
    try
    {
      /********************/
      /* Define SQL query */
      /********************/
      query = "SELECT DATABASE()";
      
      /********************/
      /* Create Statement */
      /********************/
      st = conn->createStatement();
      
      /***************************/
      /* Execute selection query */
      /***************************/
      rs = st->executeQuery(query.c_str());
      rsmd = rs->getMetaData();
      columnsNumber = rsmd->getColumnCount();
      
      /*******************/
      /* Return database */
      /*******************/
      while (rs->next())
      {
	for (int i=1; i<=columnsNumber; i++)
	  Database = rs->getString(i);
      }

      /********************/
      /* Define SQL query */
      /********************/
      query = "SHOW VARIABLES WHERE Variable_name = ?";

      /********************/
      /* Create Statement */
      /********************/
      ps = conn->prepareStatement(query);
      ps->setString(1, "hostname");
      
      /*********************/
      /* Execute SQL query */
      /*********************/
      rs = ps->executeQuery();
      rsmd = rs->getMetaData();
      columnsNumber = rsmd->getColumnCount();
      
      /*******************/
      /* Return hostname */
      /*******************/
      while (rs->next())
      {
	for (int i=1; i<=columnsNumber; i++)
	{
	  if (i == 2)
	    hostname = rs->getString(i);
	}
	printf("Connection to %s database on %s is active.\n", Database.c_str(), hostname.c_str());
      }
    }
    catch(SQLException &e)
    {
      printf("%s", e.what());
      exit(EXIT_FAILURE);
    }
  }
  else
  {
    printf("There are no active database connections.");
  }
}
