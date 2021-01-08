/* HEADER FILE: Plot.h */

#ifndef PLOT_H
#define PLOT_H
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

class Plot
{
  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    static TCanvas * CreateCanvas(std::string, std::string = "", int = 800, int = 1000, bool = false, bool = false, bool = false, bool = false);
    static TH1F * CreateFrame(TCanvas *, std::string, double, double, double, double, double = 0, double = 0, int = 5, int = 5, std::string = "", std::string = "");
    static TH1F * CreateFrame(TVirtualPad *, std::string, double, double, double, double, double = 0, double = 0, int = 5, int = 5, std::string = "", std::string = "");
    static TH1F * Histogram(std::vector <double> const &, int, double, double, std::string, std::string = "", std::string = "", std::string = "");
    static TGraph * ScatterPlot(std::vector <double> const &, std::vector <double> const &, std::string = "", std::string = "", std::string = "", Color_t = kBlack, Size_t = 1, Style_t = 1);
    static TGraphErrors * ScatterPlot(std::vector <double> const &, std::vector <double> const &, std::vector <double> const &, std::vector <double> const &, std::string = "", std::string = "", std::string = "", Color_t = kBlack, Size_t = 1, Style_t = 1);
};

#endif
