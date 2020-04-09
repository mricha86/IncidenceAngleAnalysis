/* HEADER FILE: Plot.h */

#ifndef PLOT_H
#define PLOT_H
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <math.h>
#include <numeric>
#include <sstream>
#include <string>
#include <TASImage.h>
#include <TBox.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TEllipse.h>
#include <TF1.h>
#include <TFrame.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1.h>
#include <THStack.h>
#include <TImage.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TLine.h>
#include <TPolyLine.h>
#include <TROOT.h>
#include <TStyle.h>
#include <vector>

#include "AuxilaryFunctions.h"
#include "Constants.h"
#include "Images.h"
#include "ImageSets.h"
#include "IncidenceAngles.h"
#include "LeastSquares.h"
#include "Marks.h"
#include "OverlappedImages.h"
#include "RetrieveData.h"
#include "SearchImages.h"
#include "SearchImageSets.h"
#include "SearchIncidenceAngles.h"
#include "SearchMarks.h"
#include "SortData.h"
#include "Utilities.h"

class Plot
{
  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    static void CumulativeFrequencySizeDistribution(std::string, std::string);
    static void CumulativeFrequencySizeDistribution(std::string, std::string, TGraphErrors **, TGraphErrors **, TGraph **, TGraph **, TGraphErrors **, TGraphErrors **, TLegend **);
    static void ImageComparison(double, double, double, double, std::string, std::string, std::string, std::vector <ImageSets> &, std::vector <Images> &, std::vector <IncidenceAngles> &, bool = true);
    static void ImageMosaic(std::string, std::vector <ImageSets> &, std::vector <Images> &, std::vector <IncidenceAngles> &, bool = true);
    static void MasterImage(ImageSets, bool = true);
    static void MasterImages(ImageSets, ImageSets, bool = true);
    static void MasterImage_w_SubImages(ImageSets, std::vector <Images> &, bool = true);
    static void MasterImages_w_OverlapData(double, double, std::vector <IncidenceAngles> &, std::vector <ImageSets> &, std::vector <OverlappedImages> &, std::vector <Marks> &);
    static void PaperPlots(std::string);
    static void PlotRealMasterImage(std::string, double, std::vector <IncidenceAngles> &, std::vector <ImageSets> &, std::vector <Images> &, double = 0);
    static void PlotOverlap(OverlappedImages, bool = false);
    static void SubImage(Images, bool = true, bool = false);
    static void SubImages(Images, Images, bool = true, bool = false);
    static void TestOverlap(std::string, std::string, std::vector <ImageSets> &, std::vector <Images> &, bool = true);
};

#endif
