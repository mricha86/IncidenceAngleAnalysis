/* HEADER FILE: Constants.h */

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <limits>
#include <math.h>
#include <string>

/**********************/
/* Conversion factors */
/**********************/
const double deg2rad = M_PI/180.0; // Unit: degree per radian
const double km2m = 1.0E3; // Unit: m per km
const double m2km = 1.0E-3; // Unit: km per m
const double rad2deg = 180.0/M_PI; // Unit: radian per degree

/**********************/
/* Physical Constants */
/**********************/
const double R_moon = 1737400.0; // Physical mean rsadius of the moon (Unit: meter)

/*********************/
/* Hard Coded Values */
/*********************/
const std::string mysql_url = "tcp://localhost:3306";
const std::string mysql_user = "root";
const std::string mysql_password = "00000000";
const std::string mysql_database = "cosmoquest_matts_version";
// const std::string mysql_database = "cosmoquest_original";

/**************************/
/* Mathematical constants */
/**************************/
// double infinity = std::numeric_limits<double>::infinity();

#endif
