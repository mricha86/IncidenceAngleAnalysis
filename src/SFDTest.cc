/**********************************************************************************/
/* Purpose: Testing cumulative and relative size-frequency distribution functions */
/**********************************************************************************/

// Included libraries
#include <random>
#include <TH1.h>
#include <vector>
#include "AuxilaryFunctions.h"
#include "Constants.h"
#include "IncidenceAngleAnalysis_Plot.h"
#include "Plot.h"

using namespace std;

int main() {
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double binwidth;
  double log10_xhigh;
  double log10_xlow;
  double total_area;
  double xhigh;
  double xlow;
  int nbins;
  string xtitle;
  string ytitle;
  TCanvas * can;
  TH1F *frame1;
  TH1F *frame2;
  TH1F *hist1;
  TH1F *hist2;
  TH1F *temphist1;
  TH1F *temphist2;
  TGraphErrors * TG1;
  TGraphErrors * TG2;
  TGraphErrors * TG3;
  TGraphErrors * TG4;
  vector <double> CraterDiameters;
  vector <double> CSFD_Xaxis1;
  vector <double> CSFD_Xaxis2;
  vector <double> Density1;
  vector <double> Density2;
  vector <double> Density_Error1;
  vector <double> Density_Error2;
  vector <double> RSFD_Xaxis1;
  vector <double> RSFD_Xaxis2;
  vector <double> R1;
  vector <double> R2;
  vector <double> R_Error1;
  vector <double> R_Error2;
  vector <int> ncraters_a = {91, 60, 22, 19, 7, 6, 2, 2, 1};
  vector <int> ncraters_b = {85, 49, 57, 25, 15, 11, 10};
  vector < vector <double> > range_a = {{8, 11.3}, {11.3, 16.0}, {16.0, 22.6}, {22.6, 32.0}, {32.0, 45.3}, {45.3, 64.0}, {64.0, 90.5}, {90.5, 128.0}, {128.0, 181.0}};
  vector < vector <double> > range_b = {{0.8, 0.9}, {0.9, 1.0}, {1.0, 1.2}, {1.2, 1.4}, {1.4, 1.8}, {1.8, 2.2}, {2.2, 3.6}};

  /********************************************************************************************/
  /* Simulating mock data set "a" from Crater Analysis Techniques Working Group et al. (1979) */
  /********************************************************************************************/
  nbins = ncraters_a.size();
  for (int i = 0; i < nbins; i++) {
    
    /***************************/
    /* Random number generator */
    /***************************/
    std::default_random_engine generator;
    std::uniform_real_distribution <double> distribution(range_a[i][0], range_a[i][1]);

    /**************************************************/
    /* Generate mock crater diameters for current bin */
    /**************************************************/
    for (int j = 0; j < ncraters_a[i]; j++)
      CraterDiameters.push_back(distribution(generator));
  }
  xlow = 8.0; // Unit: km
  xhigh = 181.0; // Unit: km
  log10_xlow = log10(xlow);
  log10_xhigh = log10(xhigh);
  total_area = 6.67E6;

  /*******************************/
  /* Calculate x-axis bin values */
  /*******************************/
  CSFD_Xaxis1.resize(nbins+1);
  for (int i = 0; i < (int)range_a.size(); i++)
    CSFD_Xaxis1[i] = range_a[i][0];
  CSFD_Xaxis1[nbins] = range_a[nbins-1][1];

  /**************************************************/
  /* Calculate histogram for crater identifications */
  /**************************************************/
  binwidth = 0.1;
  temphist1 = Plot::Histogram(CraterDiameters, (xhigh-xlow+binwidth)/binwidth, xlow, xhigh, "Test A");
  CraterDiameters.clear();

  /****************************************************/
  /* Rebin histogram accounting for variable bin size */
  /****************************************************/
  hist1 = (TH1F *)temphist1->Rebin(nbins, "hist1", CSFD_Xaxis1.data());

  /************************************************************/
  /* Calculate cumulative distributions and associated errors */
  /************************************************************/
  IncidenceAngleAnalysis_Plot::CumulativeCraterDensity(hist1, total_area, CSFD_Xaxis1, Density1, Density_Error1);
  
  /***************************************************/
  /* Calculate R distributions and associated errors */
  /***************************************************/
  IncidenceAngleAnalysis_Plot::RelativeCraterDensity(hist1, total_area, RSFD_Xaxis1, R1, R_Error1);
  
  /********************************************************************************************/
  /* Simulating mock data set "b" from Crater Analysis Techniques Working Group et al. (1979) */
  /********************************************************************************************/
  nbins = ncraters_b.size();
  for (int i = 0; i < nbins; i++) {
    
    /***************************/
    /* Random number generator */
    /***************************/
    std::default_random_engine generator;
    std::uniform_real_distribution <double> distribution(range_b[i][0], range_b[i][1]);

    /**************************************************/
    /* Generate mock crater diameters for current bin */
    /**************************************************/
    for (int j = 0; j < ncraters_b[i]; j++)
      CraterDiameters.push_back(distribution(generator));
  }
  xlow = 0.8; // Unit: km
  xhigh = 3.6; // Unit: km
  log10_xlow = log10(xlow);
  log10_xhigh = log10(xhigh);
  total_area = 4.4109E4;
  
  /*******************************/
  /* Calculate x-axis bin values */
  /*******************************/
  CSFD_Xaxis2.resize(nbins+1);
  for (int i = 0; i < (int)range_b.size(); i++)
    CSFD_Xaxis2[i] = range_b[i][0];
  CSFD_Xaxis2[nbins] = range_b[nbins-1][1];
    
  /**************************************************/
  /* Calculate histogram for crater identifications */
  /**************************************************/
  binwidth = 0.1;
  temphist2 = Plot::Histogram(CraterDiameters, (xhigh-xlow+binwidth)/binwidth, xlow, xhigh, "Test B");

  /****************************************************/
  /* Rebin histogram accounting for variable bin size */
  /****************************************************/
  hist2 = (TH1F *)temphist2->Rebin(nbins, "hist2", CSFD_Xaxis2.data());
  
  /************************************************************/
  /* Calculate cumulative distributions and associated errors */
  /************************************************************/
  IncidenceAngleAnalysis_Plot::CumulativeCraterDensity(hist2, total_area, CSFD_Xaxis2, Density2, Density_Error2);
  
  /***************************************************/
  /* Calculate R distributions and associated errors */
  /***************************************************/
  IncidenceAngleAnalysis_Plot::RelativeCraterDensity(hist2, total_area, RSFD_Xaxis2, R2, R_Error2);
  
  /*********************/
  /* Initialize canvas */
  /*********************/
  can = Plot::CreateCanvas("Test SFD", "Test SFD", 1000, 1000, false, false, false, false);
  can->Divide(1, 2);
  
  /******************/
  /* Generate plots */
  /******************/
  xtitle = "D, KM";
  ytitle = "Cumulative Number / KM^{2}";
  TG1 = Plot::ScatterPlot(CSFD_Xaxis1, Density1, vector <double> (0), Density_Error1, "", xtitle, ytitle, kBlue, 1, kFullDotMedium);
  TG2 = Plot::ScatterPlot(CSFD_Xaxis2, Density2, vector <double> (0), Density_Error2, "", "", "", kBlue, 1, kFullDotMedium);
  xtitle = "D_{bar}, KM";
  ytitle = "R";
  TG3 = Plot::ScatterPlot(RSFD_Xaxis1, R1, vector <double> (0), R_Error1, "", xtitle, ytitle, kBlue, 1, kFullDotMedium);
  TG4 = Plot::ScatterPlot(RSFD_Xaxis2, R2, vector <double> (0), R_Error2, "", "", "", kBlue, 1, kFullDotMedium);

  /**************/
  /* Draw plots */
  /**************/
  can->cd(1);
  gPad->SetLogy();
  gPad->SetLogx();
  gPad->SetRightMargin(0.09);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.2);
  frame1 = Plot::CreateFrame(gPad->cd(),
			     "Cumulative Size-Frequency Distributions",
			     3.16E-1,
			     1.0E-7,
			     3.16E2,
			     1.0E-2,
			     0,
			     0,
			     5,
			     5,
			     TG1->GetXaxis()->GetTitle(),
			     TG1->GetYaxis()->GetTitle());
  TG1->Draw("P");
  TG2->Draw("P");
  can->cd(2);
  gPad->SetLogy();
  gPad->SetLogx();
  gPad->SetRightMargin(0.09);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.2);
  frame2 = Plot::CreateFrame(gPad->cd(),
			     "Relative Size-Frequency Distributions",
			     3.16E-1,
			     1.0E-4,
			     3.16E2,
			     3.16E-2,
			     0,
			     0,
			     5,
			     5,
			     TG3->GetXaxis()->GetTitle(),
			     TG3->GetYaxis()->GetTitle());
  TG3->Draw("P");
  TG4->Draw("P");

  /*********************/
  /* Save plot to file */
  /*********************/
  can->SaveAs("TestSFD.png");
    
  return 0;
}

