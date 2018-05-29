/* HEADER FILE: RetrieveImages.h */

#ifndef RETRIEVEIMAGES_H
#define RETRIEVEIMAGES_H
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <mysql_connection.h>
#include <string>
#include <vector>
#include "Images.h"

class RetrieveImages
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    sql::Connection *conn;
    std::string field;
    std::string option;
    std::string table;
    std::vector <Images> data;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    RetrieveImages(sql::Connection *, std::string, std::string, std::string);
    std::vector <Images> GetData();
    static void Display(std::vector <Images> &);
    void Fetch();
};

#endif
