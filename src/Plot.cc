/* Purpose: Useful general purpose plotting routines using Cern's root library. */

/***********************/
/* Include header file */
/***********************/
#include "Plot.h"

using namespace std;

TCanvas * Plot::CreateCanvas(string name, string title, int height, int width, bool xgrid, bool ygrid, bool logx, bool logy)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  TCanvas *can;
  
  /*****************/
  /* Create canvas */
  /*****************/
  can = new TCanvas(name.c_str(), title.c_str(), width, height);

  /********************/
  /* Enable plot grid */
  /********************/
  if (xgrid) can->SetGridx();
  if (ygrid) can->SetGridy();

  /*******************************/
  /* Enable logaritmic axis/axes */
  /*******************************/
  if (logx) can->SetLogx();
  if (logy) can->SetLogy();

  return can;
}

TH1F * Plot::CreateFrame(TCanvas *can, string name, double xlow, double ylow, double xhigh, double yhigh, double xmargin, double ymargin, int nxdiv, int nydiv, string xtitle, string ytitle)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  TH1F *frame;

  /****************/
  /* Create frame */
  /****************/
  frame = can->DrawFrame(xlow-xmargin, ylow-ymargin, xhigh+xmargin, yhigh+ymargin, name.c_str());

  /******************/
  /* Frame settings */
  /******************/
  frame->GetYaxis()->CenterTitle();
  frame->GetYaxis()->SetNdivisions(nydiv);
  frame->SetYTitle(ytitle.c_str());
  frame->GetXaxis()->CenterTitle();
  frame->GetXaxis()->SetNdivisions(nxdiv);
  frame->SetXTitle(xtitle.c_str());

  return frame;
}

TH1F * Plot::CreateFrame(TVirtualPad *pad, string name, double xlow, double ylow, double xhigh, double yhigh, double xmargin, double ymargin, int nxdiv, int nydiv, string xtitle, string ytitle)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  TH1F *frame;

  /****************/
  /* Create frame */
  /****************/
  frame = pad->DrawFrame(xlow-xmargin, ylow-ymargin, xhigh+xmargin, yhigh+ymargin, name.c_str());

  /******************/
  /* Frame settings */
  /******************/
  frame->GetYaxis()->CenterTitle();
  frame->GetYaxis()->SetNdivisions(nydiv);
  frame->SetYTitle(ytitle.c_str());
  frame->GetXaxis()->CenterTitle();
  frame->GetXaxis()->SetNdivisions(nxdiv);
  frame->SetXTitle(xtitle.c_str());

  return frame;
}

TH1F * Plot::Histogram(vector <double> const &x, int nbins, double xlow, double xhigh, string name, string title, string xtitle, string ytitle)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  int n;
  TH1F *hist;

  /************************/
  /* Initialize histogram */
  /************************/
  hist = new TH1F(name.c_str(), title.c_str(), nbins, xlow, xhigh);

  /******************/
  /* Fill histogram */
  /******************/
  n = (int)x.size();
  for(int i=0; i<n; i++)
    hist->Fill(x[i]);

  /**********************/
  /* Histogram settings */
  /**********************/
  hist->SetTitle(title.c_str());
  hist->GetXaxis()->SetTitle(xtitle.c_str());
  hist->GetYaxis()->SetTitle(ytitle.c_str());
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  
  return hist;
}

TGraph * Plot::ScatterPlot(vector <double> const &x, vector <double> const &y, string title, string xtitle, string ytitle, Color_t markercolor, Size_t markersize, Style_t markerstyle)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  int n;
  int nx;
  int ny;
  TGraph *graph;

  /***********************************/
  /* Determine number of data points */
  /***********************************/
  nx = (int)x.size();
  ny = (int)y.size();
  if (nx == ny)
    n = nx;
  else {
    cout << "Error in Plot::ScatterPlot: X array size doesn't match Y array size." << endl;
    exit(EXIT_FAILURE);
  }
  
  
  /***********************/
  /* Create scatter plot */
  /***********************/
  graph = new TGraph(n, x.data(), y.data());
  
  /*****************/
  /* Plot settings */
  /*****************/
  graph->SetTitle(title.c_str());
  graph->GetXaxis()->SetTitle(xtitle.c_str());
  graph->GetYaxis()->SetTitle(ytitle.c_str());
  graph->GetXaxis()->CenterTitle();
  graph->GetYaxis()->CenterTitle();
  graph->SetMarkerColor(markercolor);
  graph->SetMarkerSize(markersize);
  graph->SetMarkerStyle(markerstyle);

  return graph;
}

TGraphErrors * Plot::ScatterPlot(vector <double> const &x, vector <double> const &y, vector <double> const &x_err, vector <double> const &y_err, string title, string xtitle, string ytitle, Color_t markercolor, Size_t markersize, Style_t markerstyle)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  int n;
  int nx;
  int ny;
  TGraphErrors *graph;

  /***********************************/
  /* Determine number of data points */
  /***********************************/
  nx = (int)x.size();
  ny = (int)y.size();
  if (nx == ny)
    n = nx;
  else {
    cout << "Error in Plot::ScatterPlot: X array size doesn't match Y array size." << endl;
    exit(EXIT_FAILURE);
  }
  
  
  /***********************/
  /* Create scatter plot */
  /***********************/
  graph = new TGraphErrors(n, x.data(), y.data(), x_err.data(), y_err.data());
  
  /*****************/
  /* Plot settings */
  /*****************/
  graph->SetTitle(title.c_str());
  graph->GetXaxis()->SetTitle(xtitle.c_str());
  graph->GetYaxis()->SetTitle(ytitle.c_str());
  graph->GetXaxis()->CenterTitle();
  graph->GetYaxis()->CenterTitle();
  graph->SetMarkerColor(markercolor);
  graph->SetMarkerSize(markersize);
  graph->SetMarkerStyle(markerstyle);

  return graph;
}
