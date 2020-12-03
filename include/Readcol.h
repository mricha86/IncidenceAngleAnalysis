/* Header File: Readcol.h */

#ifndef READCOL_H
#define READCOL_H
#include <cstdarg>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdarg.h>
#include <string>
#include <vector>

#include "AuxilaryFunctions.h"

class Readcol
{
  public:
  static int Read(std::string, std::string, ...);
  static int Read(std::string, std::string, std::string, ...);
  static std::vector <std::string> FormatParser(std::string);
};


#endif
