#include <limits>
#include <math.h>
#include <stdlib.h>
#include <TBox.h>
#include <TCanvas.h>
#include <TEllipse.h>
#include <TF1.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1.h>
#include <THStack.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TLine.h>
#include <TPolyLine.h>
#include <vector>

using namespace std;

int main()
{
  /*******************************************/
  /* Declaration/Initialization of variables */
  /*******************************************/
  int canheight;
  int canwidth;
  int index;
  int nbins;
  string buffer;
  string format;
  string filename;
  TCanvas *can;
  TCanvas *can3;
  TGraphErrors *TG1;
  TGraphErrors *TG3;
  vector <double> XAXISBIN(17);
  vector <int> N_K(17);
  
  /**************/
  /* Data set 1 */
  /**************/
  int n_data_points_1 = 9;

  /************************/
  /* X axis bin left edge */
  /************************/
  vector <double> XAXISBIN1(n_data_points_1);
  XAXISBIN1[0] = 8.0;
  XAXISBIN1[1] = 11.3;
  XAXISBIN1[2] = 16.0;
  XAXISBIN1[3] = 22.6;
  XAXISBIN1[4] = 32.0;
  XAXISBIN1[5] = 45.3;
  XAXISBIN1[6] = 64.0;
  XAXISBIN1[7] = 90.5;
  XAXISBIN1[8] = 128.0;

  /*****************************/
  /* Number of craters per bin */
  /*****************************/
  vector <int> N_K1(n_data_points_1);
  N_K1[0] = 91;
  N_K1[1] = 60;
  N_K1[2] = 22;
  N_K1[3] = 19;
  N_K1[4] = 7;
  N_K1[5] = 6;
  N_K1[6] = 2;
  N_K1[7] = 2;
  N_K1[8] = 1;

  /**************/
  /* Total area */
  /**************/
  double total_area_1 = 6.67E6;

  /**************/
  /* Data set 2 */
  /**************/
  int n_data_points_2 = 8;

  /************************/
  /* X axis bin left edge */
  /************************/
  vector <double> XAXISBIN2(n_data_points_2);
  XAXISBIN2[0] = 0.8;
  XAXISBIN2[1] = 0.9;
  XAXISBIN2[2] = 1.0;
  XAXISBIN2[3] = 1.2;
  XAXISBIN2[4] = 1.4;
  XAXISBIN2[5] = 1.8;
  XAXISBIN2[6] = 2.2;
  XAXISBIN2[7] = 3.6;
  
  /*****************************/
  /* Number of craters per bin */
  /*****************************/
  vector <int> N_K2(n_data_points_2);
  N_K2[0] = 85;
  N_K2[1] = 49;
  N_K2[2] = 57;
  N_K2[3] = 25;
  N_K2[4] = 15;
  N_K2[5] = 11;
  N_K2[6] = 10;
  N_K2[7] = 1;

  /**************/
  /* Total area */
  /**************/
  double total_area_2 = 4.4109E4;

  /*********************/
  /* Combine data sets */
  /*********************/
  index = 0;
  for(int i=0; i<(int)XAXISBIN2.size(); i++)
  {
    XAXISBIN[i] = XAXISBIN2[i];
    N_K[i] = N_K2[i];
    index++;
  }
  for(int i=index; i<index+(int)XAXISBIN1.size(); i++)
  {
    XAXISBIN[i] = XAXISBIN1[i-index];
    N_K[i] = N_K1[i-index];
  }
  nbins = (int)XAXISBIN.size();

  /***********************/
  /* Density calculation */
  /***********************/
  vector <double> Density(nbins, 0.0);
  vector <double> Density_Error(nbins, 0.0);
  for(int i=nbins-1; i>=0; i--)
  {
    for(int j=i; j<nbins; j++)
    {
      Density[i] += (j >= index ) ? N_K1[j-index]/total_area_1 : N_K2[j]/total_area_2;
    }
  }
  
  /*****************************/
  /* Density error calculation */
  /*****************************/
  for(int i=nbins-1; i>=0; i--)
  {
    double N = 0;
    for(int j=i; j<nbins; j++)
    {
      N += N_K[j];
    }
    
    Density_Error[i] = Density[i]/sqrt(N);
  }

  /***************************/
  /* Calculation of R values */
  /***************************/
  vector <double> R(nbins);
  vector <double> R_Error(nbins);
  for(int i=0; i<nbins; i++)
  {
    double b1 = XAXISBIN[i];
    double b2 = (i+1 < nbins) ? XAXISBIN[i+1] : 181.0;
    double D = sqrt(b1*b2);
    double numerator = pow(D, 3.0)*N_K[i];
    double denominator = (i < index ) ? total_area_2*(b2-b1) : total_area_1*(b2-b1);
    R[i] = numerator/denominator;
    R_Error[i] = R[i]/sqrt(N_K[i]);
  }

  /*********************/
  /* Initialize canvas */
  /*********************/
  canwidth = 1000;
  canheight = 800;
  can = new TCanvas("Canvas", "", canwidth, canheight);
  can->SetLogy();
  can->SetLogx();
  can->SetGridx();
  can->SetGridy();
  
  /**********************/
  /* Initialize graph 1 */
  /**********************/
  TG1 = new TGraphErrors(nbins, XAXISBIN.data(), Density.data(), 0, Density_Error.data());
  
  /*****************/
  /* Plot settings */
  /*****************/
  TG1->SetTitle("");
  TG1->GetXaxis()->SetTitle("Diameter [km]");
  TG1->GetYaxis()->SetTitle("Cumulative Number of Craters [km^{-2}]");
  TG1->GetXaxis()->CenterTitle();
  TG1->GetYaxis()->CenterTitle();
  TG1->SetMarkerStyle(kFullDotLarge);
  TG1->SetMarkerColor(kBlue);
  TG1->Draw("AP");
  
  /*********************/
  /* Save plot to file */
  /*********************/
  filename = "CumulativeFrequency_vs_SizeDistribution_Test.ps";
  can->SaveAs(filename.c_str());

  /***********************/
  /* Initialize canvas 3 */
  /***********************/
  canwidth = 1000;
  canheight = 800;
  can3 = new TCanvas("Canvas 3", "", canwidth, canheight);
  can3->SetLogy();
  can3->SetLogx();
  can3->SetGridx();
  can3->SetGridy();
  
  /**********************/
  /* Initialize graph 1 */
  /**********************/
  TG3 = new TGraphErrors(nbins, XAXISBIN.data(), R.data(), 0, R_Error.data());
  
  /*****************/
  /* Plot settings */
  /*****************/
  TG3->SetTitle("");
  TG3->GetXaxis()->SetTitle("Diameter [km]");
  TG3->GetYaxis()->SetTitle("R");
  TG3->GetXaxis()->CenterTitle();
  TG3->GetYaxis()->CenterTitle();
  TG3->SetMarkerStyle(kFullDotLarge);
  TG3->SetMarkerColor(kBlue);
  TG3->Draw("AP");
  
  /*********************/
  /* Save plot to file */
  /*********************/
  filename = "RValue_vs_SizeDistribution_Test.ps";
  can3->SaveAs(filename.c_str());

 return 0;
}
