/* HEADER FILE: DataRetrieval.h */

// Included libraries
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include "Checkpoint.h"
#include "Constants.h"
#include "Images.h"
#include "ImageSets.h"
#include "IncidenceAngles.h"
#include "Marks.h"
#include "MySQLConnection.h"
#include "ReadAuxilaryData.h"
#include "RetrieveData.h"

class DataRetrieval
{
  /******************************************/
  /* Declaration of class members/functions */
  /******************************************/
  public:
    DataRetrieval(std::string, std::vector <ImageSets> &, std::vector <Images> &, std::vector <Marks> &);
    DataRetrieval(std::string, std::string, std::vector <ImageSets> &, std::vector <Images> &, std::vector <Marks> &, std::vector <IncidenceAngles> &);
    static int DataSetSelector(std::string);
};
