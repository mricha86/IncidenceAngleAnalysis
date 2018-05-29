/* HEADER FILE: RetrieveImageSets.h */

#ifndef RETRIEVEIMAGESETS_H
#define RETRIEVEIMAGESETS_H
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <mysql_connection.h>
#include <string>
#include <vector>
#include "ImageSets.h"

class RetrieveImageSets
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    sql::Connection *conn;
    std::string field;
    std::string option;
    std::string table;
    std::vector <ImageSets> data;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    RetrieveImageSets(sql::Connection *, std::string, std::string, std::string);
    std::vector <ImageSets> GetData();
    static void Display(std::vector <ImageSets> &);
    void Fetch();
};

#endif
