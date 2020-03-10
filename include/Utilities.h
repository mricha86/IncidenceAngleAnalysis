/* HEADER FILE: Utilities.h */

#ifndef UTILITIES_H
#define UTILITIES_H
// #include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/geometry/geometry.hpp>
// #include <boost/geometry/geometries/geometries.hpp>
// #include <boost/geometry/geometries/adapted/boost_tuple.hpp>
// #include <boost/geometry/multi/geometries/multi_polygon.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <set>
#include <stdlib.h>
#include <string>
#include <vector>
#include "AuxilaryFunctions.h"
#include "CheckOverlap.h"
#include "Checkpoint.h"
#include "Constants.h"
#include "EquirectangularProjection.h"
#include "Images.h"
#include "ImageSets.h"
#include "IncidenceAngles.h"
#include "Marks.h"
#include "MySQLConnection.h"
#include "OverlappedImages.h"
#include "ProjectiveTransformation.h"
#include "Quadrilateral.h"
#include "ReadAuxilaryData.h"
#include "RetrieveData.h"
#include "SearchImages.h"
#include "SearchIncidenceAngles.h"
#include "SearchMarks.h"
#include "SortImages.h"
#include "SortImageSets.h"
#include "SortIncidenceAngles.h"
#include "SortMarks.h"
#include "SortOverlappedImages.h"
// #include "SphericalLawofCosines.h"

class Utilities
{
  /******************************************/
  /* Declaration of class members/functions */
  /******************************************/
  private:
    typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > polygon;

  public:
    static bool do_LinesIntersect(double, double, double, double, double, double);
    static bool FileExists(std::string);
    static bool is_PointContained(double, double, std::vector < std::vector <double> > &);
    static double ImageTotalArea(std::vector <double> &, std::vector <IncidenceAngles> &, std::vector <ImageSets> &);
    static int DataSetSelector(std::string);
    static std::vector <OverlappedImages> FindDifferentIncidenceAngleOverlappingImages(std::vector <OverlappedImages> &);
    static std::vector <OverlappedImages> FindOverlappingImages(std::vector <Images> &, std::vector <IncidenceAngles> &);
    static std::vector <OverlappedImages> FindSameScaleOverlappingImages(std::vector <OverlappedImages> &, int = 3);
    static std::vector <OverlappedImages> FindTotalOverlappingImages(std::vector <OverlappedImages> &);
    static std::vector <double> RetrieveUniqueIncidenceAngles(std::vector <IncidenceAngles> &);
    static void RetrieveCraterCatalog(double, double, std::vector <OverlappedImages> &, std::vector <Marks> &, std::vector < std::vector <std::string> > &, std::vector <Marks> &, std::vector <Marks> &, std::vector <double> &, std::vector <double> &, std::vector <int> &, std::vector <int> &);
    static void ExecuteAuxilaryFunctions(std::vector <ImageSets> &, std::vector <Images> &, std::vector <Marks> &);
    static void ExecuteImagesAuxilaryFunction(std::vector <Images> &, std::vector <ImageSets> &);
    static void ExecuteImageSetsAuxilaryFunction(std::vector <ImageSets> &);
    static void ExecuteMarksAuxilaryFunction(std::vector <Marks> &, std::vector <Images> &);
    static void ObtainData(std::string, std::vector <ImageSets> &, std::vector <Images> &, std::vector <Marks> &, std::string, std::vector <IncidenceAngles> &);
    static void PrintCraterCatalog(double, double, std::vector <IncidenceAngles> &, std::vector <OverlappedImages> &, std::vector <Marks> &, int, bool = false);
    static void union_polys(std::vector <polygon>, std::vector <polygon> &);
};

#endif
