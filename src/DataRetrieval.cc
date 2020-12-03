/* Purpose: Functions used to retreive data for incidence angle analysis. 
   Data retrieval is from CosmoQuest's MySQL database and datafile passed
   as an arguement to the main function. */

/* Include header */
#include "DataRetrieval.h"

using namespace boost;
using namespace sql;
using namespace std;

DataRetrieval::DataRetrieval(string dataset_name, vector <ImageSets> &imagesets, vector <Images> &images, vector <Marks> &marks)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  Connection *conn;
  int dataset_id;
  string buffer;
  string field;
  string option;
  string table;

  /*************************/
  /* Initialize checkpoint */
  /*************************/
  Checkpoint myCheckpoint;

  /*****************************************************/
  /* Establish connection to CosmoQuest MySQL database */
  /*****************************************************/
  MySQLConnection myConnection(mysql_url, mysql_user, mysql_password, mysql_database);
  myConnection.Connect();
  conn = myConnection.GetConnection();

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to establish connection to CosmoQuest mysql database:";
  myCheckpoint.ElapsedTime(buffer);

  /************************************************/
  /* Test connection to CosmoQuest MySQL database */
  /************************************************/
  // myConnection.TestConnection();

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to test connection to CosmoQuest mysql database:";
  // myCheckpoint.ElapsedTime(buffer);

  /*********************************/
  /* Establish dataset to retrieve */
  /*********************************/
  dataset_id = DataSetSelector(dataset_name); 

  /****************************************************************/
  /* Retrieve image_sets datatable from CosmoQuest MySQL database */
  /****************************************************************/
  table = "image_sets";
  field = "id, name, application_id, upper_left_latitude, upper_left_longitude, upper_right_latitude, upper_right_longitude, lower_right_latitude, lower_right_longitude, lower_left_latitude, lower_left_longitude, pixel_resolution, details";
  option = "";
  RetrieveData<ImageSets> ImageSetsData(conn, dataset_id, table, field, option);
  ImageSetsData.FetchData();
  imagesets = ImageSetsData.GetData();
  // RetrieveData<ImageSets>::DisplayData(table, imagesets); exit(0);

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to retrieve image_sets table from CosmoQuest mysql database:";
  myCheckpoint.ElapsedTime(buffer);

  /************************************************************/
  /* Retrieve images datatable from CosmoQuest MySQL database */
  /************************************************************/
  table = "images";
  field = "id, image_set_id, application_id, name, details";
  RetrieveData<Images> ImagesData(conn, dataset_id, table, field, option);
  ImagesData.FetchData();
  images = ImagesData.GetData();
  // RetrieveData<Images>::DisplayData(table, images); exit(0);
  
  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to retrieve images table from CosmoQuest mysql database:";
  myCheckpoint.ElapsedTime(buffer);
  
  /***********************************************************/
  /* Retrieve marks datatable from CosmoQuest MySQL database */
  /***********************************************************/
  table = "marks";
  field = "id, image_id, application_id, x, y, diameter";
  RetrieveData<Marks> MarksData(conn, dataset_id, table, field, option);
  MarksData.FetchData();
  marks = MarksData.GetData();
  // RetrieveData<Marks>::DisplayData(table, marks); exit(0);
  
  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to retrieve marks table from CosmoQuest mysql database:";
  myCheckpoint.ElapsedTime(buffer);

  /***********************************************/
  /* End connection to CosmoQuest MySQL database */
  /***********************************************/
  myConnection.Disconnect();

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to end connection to CosmoQuest mysql database:";
  myCheckpoint.ElapsedTime(buffer);

  return;
}

DataRetrieval::DataRetrieval(string dataset_name, string auxilarydatafile, vector <ImageSets> &imagesets, vector <Images> &images, vector <Marks> &marks, vector <IncidenceAngles> &incidenceangles)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  Connection *conn;
  int dataset_id;
  string buffer;
  string field;
  string option;
  string table;

  /*************************/
  /* Initialize checkpoint */
  /*************************/
  Checkpoint myCheckpoint;

  /*****************************************************/
  /* Establish connection to CosmoQuest MySQL database */
  /*****************************************************/
  MySQLConnection myConnection(mysql_url, mysql_user, mysql_password, mysql_database);
  myConnection.Connect();
  conn = myConnection.GetConnection();

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to establish connection to CosmoQuest mysql database:";
  myCheckpoint.ElapsedTime(buffer);

  /************************************************/
  /* Test connection to CosmoQuest MySQL database */
  /************************************************/
  // myConnection.TestConnection();

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to test connection to CosmoQuest mysql database:";
  // myCheckpoint.ElapsedTime(buffer);

  /*********************************/
  /* Establish dataset to retrieve */
  /*********************************/
  dataset_id = DataSetSelector(dataset_name); 

  /****************************************************************/
  /* Retrieve image_sets datatable from CosmoQuest MySQL database */
  /****************************************************************/
  table = "image_sets";
  field = "id, name, application_id, upper_left_latitude, upper_left_longitude, upper_right_latitude, upper_right_longitude, lower_right_latitude, lower_right_longitude, lower_left_latitude, lower_left_longitude, pixel_resolution, details";
  option = "";
  RetrieveData<ImageSets> ImageSetsData(conn, dataset_id, table, field, option);
  ImageSetsData.FetchData();
  imagesets = ImageSetsData.GetData();
  // RetrieveData<ImageSets>::DisplayData(table, imagesets); exit(0);

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to retrieve image_sets table from CosmoQuest mysql database:";
  myCheckpoint.ElapsedTime(buffer);

  /************************************************************/
  /* Retrieve images datatable from CosmoQuest MySQL database */
  /************************************************************/
  table = "images";
  field = "id, image_set_id, application_id, name, details";
  RetrieveData<Images> ImagesData(conn, dataset_id, table, field, option);
  ImagesData.FetchData();
  images = ImagesData.GetData();
  // RetrieveData<Images>::DisplayData(table, images); exit(0);
  
  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to retrieve images table from CosmoQuest mysql database:";
  myCheckpoint.ElapsedTime(buffer);
  
  /***********************************************************/
  /* Retrieve marks datatable from CosmoQuest MySQL database */
  /***********************************************************/
  table = "marks";
  field = "id, image_id, application_id, x, y, diameter";
  RetrieveData<Marks> MarksData(conn, dataset_id, table, field, option);
  MarksData.FetchData();
  marks = MarksData.GetData();
  // RetrieveData<Marks>::DisplayData(table, marks); exit(0);
  
  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to retrieve marks table from CosmoQuest mysql database:";
  myCheckpoint.ElapsedTime(buffer);

  /***********************************************/
  /* End connection to CosmoQuest MySQL database */
  /***********************************************/
  myConnection.Disconnect();

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to end connection to CosmoQuest mysql database:";
  myCheckpoint.ElapsedTime(buffer);

  /******************************************************/
  /* Retrieve auxilary data from user supplied datafile */
  /******************************************************/
  ReadAuxilaryData AuxilaryData(auxilarydatafile);
  AuxilaryData.Read();
  incidenceangles = AuxilaryData.GetIncidenceAngleData();
  // ReadAuxilaryData::DisplayData(incidenceangles); exit(0);

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to retrieve auxilary data:";
  myCheckpoint.ElapsedTime(buffer);

  return;
}

int DataRetrieval::DataSetSelector(string datasetname)
{
  to_upper(datasetname);
  if(datasetname.compare("MARS") == 0) return 18;
  else if(datasetname.compare("MERCURY") == 0) return 5;
  else if(datasetname.compare("MOON") == 0) return 1;
  else if(datasetname.compare("VESTA") == 0) return 4;
  else
  {
    printf("Invalid data set (%s) request. Terminating program ...\n", datasetname.c_str());
    exit(EXIT_FAILURE);
  }

  return 0;
}
