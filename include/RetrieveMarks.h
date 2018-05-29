/* HEADER FILE: RetrieveMarks.h */

#ifndef RETRIEVEMARKS_H
#define RETRIEVEMARKS_H
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <mysql_connection.h>
#include <string>
#include <vector>
#include "Marks.h"

class RetrieveMarks
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    sql::Connection *conn;
    std::string field;
    std::string option;
    std::string table;
    std::vector <Marks> data;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    RetrieveMarks(sql::Connection *, std::string, std::string, std::string);
    std::vector <Marks> GetData();
    void Fetch();
    static void Display(std::vector <Marks> &);
};

#endif
