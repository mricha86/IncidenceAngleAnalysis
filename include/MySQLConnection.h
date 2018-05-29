/* HEADER FILE: MySQLConnection.h */

#ifndef MYSQLCONNECTION_H
#define MYSQLCONNECTION_H
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <string>

class MySQLConnection
{
  /***********************************/
  /* Declaration of class variables */
  /***********************************/
  private:
    sql::Connection *conn;
    sql::Driver *driver;
    std::string database;
    std::string password;
    std::string url;
    std::string user;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    MySQLConnection(std::string, std::string, std::string, std::string);
    sql::Connection * GetConnection();
    void Connect();
    void Disconnect();
    void TestConnection();
};

#endif
