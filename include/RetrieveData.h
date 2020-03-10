/* HEADER FILE: RetrieveData.h */

#ifndef RETRIEVEDATA_H
#define RETRIEVEDATA_H
#include <boost/algorithm/string.hpp>
#include <boost/any.hpp>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iomanip>
#include <mysql_connection.h>
#include <string>
#include <vector>
#include "Images.h"
#include "ImageSets.h"
#include "Marks.h"

template <typename T>
class RetrieveData
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    int dataset;
    sql::Connection *conn;
    std::string field;
    std::string option;
    std::string table;
    std::vector <T> data;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    RetrieveData(sql::Connection *, int, std::string, std::string, std::string);
    std::vector <T> GetData();
    static std::vector <std::string> DisplayData_column_names(std::string);
    static std::vector <std::vector <int> > DisplayData_formatting(std::string);
    static std::vector <boost::any> DisplayData_row_values(T, std::vector <std::vector <int> >);
    static void DisplayData(std::string, std::vector <T> &);
    T FetchData_datum(sql::ResultSet *);
    void FetchData();
};

/******************************/
/* Class function definitions */
/******************************/
template <typename T>
RetrieveData<T>::RetrieveData(sql::Connection *CONN, int DATASET, std::string TABLE, std::string FIELD, std::string OPTION)
{
  /*******************************************************************/
  /* Retrieve needed information for database information extraction */
  /*******************************************************************/
  conn = CONN;
  dataset = DATASET;
  table = TABLE;
  field = FIELD;
  option = OPTION;
}

template <typename T>
std::vector <T> RetrieveData<T>::GetData()
{
  return data;
}

template <typename T>
std::vector <std::string> RetrieveData<T>::DisplayData_column_names(std::string tab)
{
  /***************************************/
  /* Declaration of function variable(s) */
  /***************************************/
  std::vector <std::string> columns;
  
  /***************************/
  /* Capitalize tab variable */
  /***************************/
  boost::to_upper(tab);
  
  /*************************************************/
  /* Determine which column names to use for table */
  /*************************************************/
  if(tab.compare("IMAGES") == 0) {
    columns.push_back("ID");
    columns.push_back("ISID");
    columns.push_back("AID");
    columns.push_back("NAME");
    columns.push_back("ULX");
    columns.push_back("ULY");
    columns.push_back("URX");
    columns.push_back("URY");
    columns.push_back("LRX");
    columns.push_back("LRY");
    columns.push_back("LLX");
    columns.push_back("LLY");
  } else if(tab.compare("IMAGE_SETS") == 0) {
    columns.push_back("ID");
    columns.push_back("NAME");
    columns.push_back("AID");
    columns.push_back("ULLAT");
    columns.push_back("ULLONG");
    columns.push_back("URLAT");
    columns.push_back("URLONG");
    columns.push_back("LRLAT");
    columns.push_back("LRLONG");
    columns.push_back("LLLAT");
    columns.push_back("LLLONG");
    columns.push_back("ULXSTATUS");
    columns.push_back("ULYSTATUS");
  } else if(tab.compare("MARKS") == 0) {
    columns.push_back("ID");
    columns.push_back("IID");
    columns.push_back("AID");
    columns.push_back("X");
    columns.push_back("Y");
    columns.push_back("D");
  } else {
    std::cout << "Table " << tab.c_str() << " not found." << std::endl;
    exit(EXIT_FAILURE);
  }
  
  return columns;
}

template <typename T>
std::vector < std::vector <int> > RetrieveData<T>::DisplayData_formatting(std::string tab)
{
  /***************************************/
  /* Declaration of function variable(s) */
  /***************************************/
  std::vector < std::vector <int> > format;

  /***************************/
  /* Capitalize tab variable */
  /***************************/
  boost::to_upper(tab);
  
  /*******************************************/
  /* Determine which format to use for table */
  /*******************************************/
  if(tab.compare("IMAGES") == 0) {
    format.push_back(std::vector <int>{0, 5, 2});
    format.push_back(std::vector <int>{0, 4, 2});
    format.push_back(std::vector <int>{0, 3, 2});
    format.push_back(std::vector <int>{0, 19, 1});
    format.push_back(std::vector <int>{2, 11, 3});
    format.push_back(std::vector <int>{2, 11, 3});
    format.push_back(std::vector <int>{2, 11, 3});
    format.push_back(std::vector <int>{2, 11, 3});
    format.push_back(std::vector <int>{2, 11, 3});
    format.push_back(std::vector <int>{2, 11, 3});
    format.push_back(std::vector <int>{2, 11, 3});
    format.push_back(std::vector <int>{2, 11, 3});
  } else if(tab.compare("IMAGE_SETS") == 0) {
    format.push_back(std::vector <int>{0, 2, 2});
    format.push_back(std::vector <int>{0, 12, 1});
    format.push_back(std::vector <int>{0, 3, 2});
    format.push_back(std::vector <int>{4, 8, 3});
    format.push_back(std::vector <int>{4, 8, 3});
    format.push_back(std::vector <int>{4, 8, 3});
    format.push_back(std::vector <int>{4, 8, 3});
    format.push_back(std::vector <int>{4, 8, 3});
    format.push_back(std::vector <int>{4, 8, 3});
    format.push_back(std::vector <int>{4, 8, 3});
    format.push_back(std::vector <int>{4, 8, 3});
    format.push_back(std::vector <int>{0, 9, 1});
    format.push_back(std::vector <int>{0, 9, 1});
  } else if(tab.compare("MARKS") == 0) {
    format.push_back(std::vector <int>{0, 10, 2});
    format.push_back(std::vector <int>{0, 10, 2});
    format.push_back(std::vector <int>{0, 3, 2});
    format.push_back(std::vector <int>{2, 8, 3});
    format.push_back(std::vector <int>{2, 8, 3});
    format.push_back(std::vector <int>{2, 8, 3});
  } else {
    std::cout << "Table " << tab.c_str() << " not found." << std::endl;
    exit(EXIT_FAILURE);
  }
  
  return format;
}

template <typename T>
std::vector <boost::any> RetrieveData<T>::DisplayData_row_values(T datum, std::vector <std::vector <int> > formatting)
{
  /***************************************/
  /* Declaration of function variable(s) */
  /***************************************/
  boost::any value;
  std::vector <boost::any> row_values;
  std::vector <std::string> fields;

  /**************************************************/
  /* Retrieve column names and corresponding values */
  /**************************************************/
  fields = datum.GetFields();
  for (int i = 0; i < (int)fields.size(); i++) {
    void * v = datum.GetValue(fields[i]);
    switch (formatting[i][2]) {
      case 1: {
	std::string * str = static_cast<std::string *>(v);
	value = *str;
	break;
      }
      case 2: {
	int * dig = static_cast<int *>(v);
	value = *dig;
	break;
      }
      case 3: {
	double * doub = static_cast<double *>(v);
	value = *doub;
	break;
      }
    }
    row_values.push_back(value);
  }
  
  return row_values;
}

template <typename T>
void RetrieveData<T>::DisplayData(std::string tab, std::vector <T> &list)
{  
  /***********************/
  /* Retrieve formatting */
  /***********************/
  std::vector <std::vector <int> > formatting = DisplayData_formatting(tab);
  
  /*******************************/
  /* Retrieve header information */
  /*******************************/
  std::vector <std::string> columns = DisplayData_column_names(tab);
  
  /********************/
  /* Print header row */
  /********************/
  for (int i = 0; i < (int)formatting.size(); i++)
    std::cout << std::setprecision(0) << std::setw(formatting[i][1]) << std::left << columns[i] << " ";
  std::cout << std::endl;
  
  /**************/
  /* Print data */
  /**************/
  for(int i = 0; i < (int)list.size(); i++) {
    /*******************************/
    /* Retrieve current data point */
    /*******************************/
    T datum = list[i]; 
    std::vector <boost::any> row = DisplayData_row_values(datum, formatting);

    /*********************/
    /* Print current row */
    /*********************/
    for (int j = 0; j < (int)row.size(); j++) {
      switch (formatting[j][2]) {
        case 1: {
	  std::cout << std::setprecision(formatting[j][0]) << std::setw(formatting[j][1]) << std::left << boost::any_cast<std::string>(row[j]) << " ";
	  break;
	}
        case 2: {
	  std::cout << std::setprecision(formatting[j][0]) << std::setw(formatting[j][1]) << std::left << boost::any_cast<int>(row[j]) << " ";
	break;
	}
        case 3: {
	  std::cout << std::setprecision(formatting[j][0]) << std::setw(formatting[j][1]) << std::left << boost::any_cast<double>(row[j]) << " ";
	  break;
	}
      }
    }
    std::cout << std::endl;
  }
  
  return;
}

template <typename T>
T RetrieveData<T>::FetchData_datum(sql::ResultSet *rs)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  T datum;
  boost::any datum_selector;

  /******************************/
  /* Copy and modify table name */
  /******************************/
  std::string tab = table;
  boost::to_upper(tab);

  /********************************************/
  /* Retrieve data from the appropriate table */
  /********************************************/
  if(tab.compare("IMAGES") == 0) {
    Images d(rs->getInt("id"),
	     rs->getInt("image_set_id"),
	     rs->getInt("application_id"),
	     rs->getString("name"),
	     "",
	     0,
	     0,
	     0,
	     0,
	     rs->getString("details"),
	     "",
	     "");
    datum_selector = d;
  } else if(tab.compare("IMAGE_SETS") == 0) {
    ImageSets d(rs->getInt("id"),
		rs->getString("name"),
		rs->getInt("application_id"),
		0,
		0,
		rs->getDouble("upper_left_latitude"),
		rs->getDouble("upper_left_longitude"),
		rs->getDouble("upper_right_latitude"),
		rs->getDouble("upper_right_longitude"),
		rs->getDouble("lower_right_latitude"),
		rs->getDouble("lower_right_longitude"),
		rs->getDouble("lower_left_latitude"),
		rs->getDouble("lower_left_longitude"),
		0,
		"",
		rs->getString("details"),
		"",
		"");
    datum_selector = d;
  } else if(tab.compare("MARKS") == 0) {
    Marks d(rs->getInt("id"),
	    0,
	    rs->getInt("image_id"),
	    rs->getInt("application_id"),
	    0,
	    0,
	    0,
	    rs->getDouble("x"),
	    rs->getDouble("y"),
	    rs->getDouble("diameter"),
	    0,
	    0,
	    0,
	    "",
	    "",
	    "",
	    "",
	    "");
    datum_selector = d;
  } else {
    std::cout << "Table " << tab.c_str() << " not found." << std::endl;
    exit(EXIT_FAILURE);
  }
  datum = boost::any_cast<T>(datum_selector);
  
  return datum;
}

template <typename T>
void RetrieveData<T>::FetchData()
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  int columnsNumber;
  sql::PreparedStatement *pst;
  sql::ResultSet *rs;
  sql::ResultSetMetaData *rsmd;
  std::string query;

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
      if(application_id == dataset)
      {
	T datum = FetchData_datum(rs);
	data.push_back(datum);
      }
    }
  }
  catch(sql::SQLException &e)
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
    catch(sql::SQLException &e)
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
    catch(sql::SQLException &e)
    {
      printf("%s\n", e.what());
      exit(EXIT_FAILURE);
    }
  }

  return;
}

#endif
