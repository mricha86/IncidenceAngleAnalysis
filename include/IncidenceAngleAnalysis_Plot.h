/* HEADER FILE: IncidenceAngleAnalysis_Plot.h */

#ifndef INCIDENCEANGLEANALYSIS_PLOT_H
#define INCIDENCEANGLEANALYSIS_PLOT_H
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "AuxilaryFunctions.h"
#include "Constants.h"
#include "Images.h"
#include "ImageSets.h"
#include "IncidenceAngles.h"
#include "LeastSquares.h"
#include "Marks.h"
#include "OverlappedImages.h"
#include "Plot.h"
#include "Readcol.h"
#include "RetrieveData.h"
#include "SearchData.h"
#include "SortData.h"
#include "Utilities.h"

class IncidenceAngleAnalysis_Plot
{
  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    static double ExtractIncidenceAngle(std::string);
    static std::string ExtractImageName(std::string);
    static void CSFDFittingRoutine(std::vector <double> &diameter, std::vector <double> &density, double &slope, double &slope_err, double &intercept, double &intercept_err);
    static void CumulativeCraterDensity(TH1F *, double, std::vector <double> &, std::vector <double> &, std::vector <double> &);
    static void CumulativeFrequencySizeDistribution(std::string, std::string, TGraphErrors **, TGraphErrors **, TGraph **, TGraph **, TGraphErrors **, TGraphErrors **, TLegend **);
    static void ImageComparison(double, double, double, double, std::string, std::string, std::string, std::vector <ImageSets> &, std::vector <Images> &, std::vector <IncidenceAngles> &, bool = true);
    static void ImageMosaic(std::string, std::vector <ImageSets> &, std::vector <Images> &, std::vector <IncidenceAngles> &, bool = true);
    static void MasterImage(ImageSets, bool = true);
    static void MasterImages(ImageSets, ImageSets, bool = true);
    static void MasterImage_w_SubImages(ImageSets, std::vector <Images> &, bool);
    static void MasterImages_w_OverlapData(double, double, std::vector <IncidenceAngles> &, std::vector <ImageSets> &, std::vector <OverlappedImages> &, std::vector <Marks> &);
    static void PaperPlots(std::string);
    static void PlotRealMasterImage(std::string, double, std::vector <IncidenceAngles> &, std::vector <ImageSets> &, std::vector <Images> &, double = 0);
    static void PlotOverlap(OverlappedImages, bool = false);
    static void RelativeCraterDensity(TH1F *, double, std::vector <double> &, std::vector <double> &, std::vector <double> &);
    static void SubImage(Images, bool = true, bool = false);
    static void SubImages(Images, Images, bool = true, bool = false);
    static void TestOverlap(std::string, std::string, std::vector <ImageSets> &, std::vector <Images> &, bool = true);
    static void Visualization1(std::vector <double> &, std::vector <ImageSets> &, std::vector <Images> &, std::vector <IncidenceAngles> &);
};

#endif
