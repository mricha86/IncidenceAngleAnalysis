/* Purpose: Useful general purpose plotting routines using Cern's root library. */

/***********************/
/* Include header file */
/***********************/
#include "IncidenceAngleAnalysis_Plot.h"

using namespace std;

double IncidenceAngleAnalysis_Plot::ExtractIncidenceAngle(string str)
{
  int p1 = str.find("E_")+2;
  int p2 = str.rfind(".");
  int len = p2-p1;
  return stod(str.substr(p1, len));
}

string IncidenceAngleAnalysis_Plot::ExtractImageName(string str)
{
  int p1 = str.find("_M")+1;
  int p2 = str.find("E_")+1;
  int len = p2-p1;
  return str.substr(p1, len);
}

void IncidenceAngleAnalysis_Plot::CSFDFittingRoutine(vector <double> &diameter, vector <double> &density, double &slope, double &slope_err, double &intercept, double &intercept_err)
{ 
  double prev_slope = 0;
  unsigned nbins = diameter.size();
  unsigned index = nbins-2;
  bool condition = true;
  while(condition) {
    /**********************************/
    /* Retrieve sample of data points */
    /**********************************/
    vector <double> x;
    vector <double> y;
    for(unsigned i = nbins-1; i >= index; i--) {
      /*************************************************/
      /* Removes data points where density equals zero */
      /*************************************************/
      if(density[i] == 0) continue;
    
      /*************************************************/
      /* Record x and y data point for fit calculation */
      /*************************************************/
      x.push_back(diameter[i]);
      y.push_back(density[i]);
    }
    if(index == 0)
      condition = false;
    else
      index--;
  
    /***************************************/
    /* Ensures that a minimum of two data  */
    /* points are used for fit calculation */
    /***************************************/
    if(y.size() > 1) {
      /**************************/
      /* Fit initial conditions */
      /**************************/
      int methodchoice = 2; // Least squares grid search method
      int modelchoice = 8; // Power-law fitting function (y = ax^-k)
      double sd = 0.5;
      vector <double> params = {3, 1}; // {k, a}
      vector <double> stepsizes = {0.001, 0.001};
      
      /****************************/
      /* Determine fit parameters */
      /****************************/
      LeastSquares Regression(x, y);
      Regression.Fit(methodchoice, modelchoice, sd, stepsizes, params);
      vector < vector <double> > covMatrix = Regression.GetCovariance_matrix();

      /********************/
      /* Slope comparison */
      /********************/
      if(prev_slope == 0) {
	prev_slope = params[0];
	slope = params[0];
	intercept = params[1];
	slope_err = sqrt(covMatrix[0][0]);
	intercept_err = sqrt(covMatrix[1][1]);
      }
      else if(fabs(prev_slope-params[0])/prev_slope > 0.01)
	condition = false;
      else {
	/***************************/
	/* Record current solution */
	/***************************/
	slope = params[0];
	intercept = params[1];
	slope_err = covMatrix[0][0];
	intercept_err = covMatrix[1][1];
      }
    }
  }
}

void IncidenceAngleAnalysis_Plot::CumulativeCraterDensity(TH1F *h, double area, vector <double> &density, vector <double> &density_err)
{
  int nbins = h->GetNbinsX();
  density.resize(nbins);
  density_err.resize(nbins);
  
  /******************************************/
  /* Calculate cumulative density and error */
  /******************************************/
  for(int i = nbins; i >= 1; i--) {
    int N = 0;
    for(int j = i; j <= nbins; j++) {
      N += h->GetBinContent(j);
      density[i-1] += h->GetBinContent(j)/area;
    }
    density_err[i-1] = (N != 0) ? density[i-1]/sqrt(N) : 0;
  }
}

void IncidenceAngleAnalysis_Plot::CumulativeFrequencySizeDistribution(string CraterCatalogue1, string CraterCatalogue2)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  double binwidth;
  double incidence_angle_1;
  double incidence_angle_2;
  double log10_xlow;
  double log10_xup;
  double total_area;
  double xlow;
  double xup;
  double ylow_1;
  double ylow_2;
  double yup_1;
  double yup_2;
  ifstream InFile;
  int canheight;
  int canwidth;
  int index1;
  int index2;
  int length;
  int max_elements;
  int n;
  int nbins;
  int nlines;
  ofstream OutFile1;
  ofstream OutFile2;
  string buffer;
  string format;
  string filename;
  string imagename1;
  string imagename2;
  TCanvas *can;
  TCanvas *can2;
  TCanvas *can3;
  TGraph *F1;
  TGraph *F2;
  TGraphErrors *TG1;
  TGraphErrors *TG2;
  TGraphErrors *TG3;
  TGraphErrors *TG4;
  TH1F *hist1;
  TH1F *hist2;
  THStack *bar;
  TLegend *leg;
  TLegend *leg2;
  TLegend *leg3;
  vector <double> A1;
  vector <double> A2;
  vector <double> D1;
  vector <double> D2;
  vector <double> XAXISBIN;
  vector <double> XAXISBINLOG;

  /***********************************/
  /* Request memory for data vectors */
  /***********************************/
  n = 10;
  max_elements = 100000;
  vector < vector <double> > CC1(n, vector <double> (max_elements));
  vector < vector <double> > CC2(n, vector <double> (max_elements));
  
  /**********************/
  /* Read-in Filename 1 */
  /**********************/
  format = "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf";
  nlines = Readcol::Read(CraterCatalogue1, format, CC1[0].data(), CC1[1].data(),
		CC1[2].data(), CC1[3].data(), CC1[4].data(), CC1[5].data(),
		CC1[6].data(), CC1[7].data(), CC1[8].data(), CC1[9].data());
  for(int i = 0; i < (int)CC1.size(); i++)
    CC1[i].resize(nlines);
  
  /**********************/
  /* Read-in Filename 2 */
  /**********************/
  nlines = Readcol::Read(CraterCatalogue2, format, CC2[0].data(), CC2[1].data(),
		CC2[2].data(), CC2[3].data(), CC2[4].data(), CC2[5].data(),
		CC2[6].data(), CC2[7].data(), CC2[8].data(), CC2[9].data());
  for(int i = 0; i < (int)CC2.size(); i++)
    CC2[i].resize(nlines);

  /******************************************************/
  /* Parse filename 1 to retrieve pertinent information */
  /******************************************************/
  index1 = CraterCatalogue1.find("_M")+1;
  index2 = CraterCatalogue1.find("E_")+1;
  length = index2-index1;
  imagename1 = CraterCatalogue1.substr(index1, length);
  index1 = index2+1;
  index2 = CraterCatalogue1.rfind(".");
  length = index2-index1;
  incidence_angle_1 = stod(CraterCatalogue1.substr(index1, length));

  /******************************************************/
  /* Parse filename 1 to retrieve pertinent information */
  /******************************************************/
  index1 = CraterCatalogue2.find("_M")+1;
  index2 = CraterCatalogue2.find("E_")+1;
  length = index2-index1;
  imagename2 = CraterCatalogue2.substr(index1, length);
  index1 = index2+1;
  index2 = CraterCatalogue2.rfind(".");
  length = index2-index1;
  incidence_angle_2 = stod(CraterCatalogue2.substr(index1, length));
  
  /***************/
  /* Select data */
  /***************/
  for(int i=0; i<(int)CC1.size(); i++)
  {
    D1.push_back(CC1[i][5]*m2km);
    A1.push_back(CC1[i][8]*m2km*m2km);
  }
  for(int i=0; i<(int)CC2.size(); i++)
  {
    D2.push_back(CC2[i][5]*m2km);
    A2.push_back(CC2[i][8]*m2km*m2km);
  }

  /***************/
  /* Data switch */
  /***************/
  if(incidence_angle_2 > incidence_angle_1)
  {
    D1.swap(D2);
    A1.swap(A2);
    imagename1.swap(imagename2);
    double temp = incidence_angle_1;
    incidence_angle_1 = incidence_angle_2;
    incidence_angle_2 = temp;
  }
  
  /*****************************************/
  /* Determine plot spacing and number of  */
  /* bins (Using even logarithmic spacing) */
  /*****************************************/
  binwidth = log10(sqrt(2)); 
  xlow = 8.0*m2km;
  xup = 110.0*m2km;
  log10_xlow = log10(xlow);
  log10_xup = log10(xup);
  nbins = MaxNearestMultiple(log10_xup-log10_xlow, binwidth)/binwidth;
  log10_xup = log10_xlow+nbins*binwidth;
  xup = pow(10, log10_xup);

  /***********************************/
  /* Calculate left edge of each bin */
  /***********************************/
  for(int i=0; i<nbins; i++)
  {
    XAXISBINLOG.push_back(log10_xlow+binwidth*i);
    XAXISBIN.push_back(pow(10, XAXISBINLOG.back()));
  }

  /*************************/
  /* Initialize histograms */
  /*************************/
  hist1 = new TH1F("", "", nbins, log10_xlow, log10_xup);
  hist2 = new TH1F("", "", nbins, log10_xlow, log10_xup);
  
  /**************************************/
  /* Calculate cumulative distributions */
  /**************************************/
  vector <double> Density1(nbins, 0.0);
  vector <double> Density2(nbins, 0.0);
  vector <double> Density1_Error(nbins, 0.0);
  vector <double> Density2_Error(nbins, 0.0);
  vector <double> n_K1(nbins, 0.0);
  vector <double> n_K2(nbins, 0.0);
  double bin_number = 1.0/binwidth;
  for(int i=0; i<(int)D1.size(); i++)
  {    
    /******************************************/
    /* Calculate common log value of diameter */
    /******************************************/
    double logD = log10(D1[i]);

    /******************/
    /* Fill histogram */
    /******************/
    hist1->Fill(logD);
    
    /************************/
    /* Determine bin number */
    /************************/
    int index = floor((logD-log10_xlow)*bin_number);
    
    /*******************************************/
    /* Only include data above threshold value */
    /*******************************************/
    if((index < 0) || (index > nbins-1))
      continue;

    /**************************************/
    /* Increment all bins associated with */
    /* diameters less than or equal logD  */
    /**************************************/
    n_K1[index]++;
  }
  
  for(int i=0; i<(int)D2.size(); i++)
  {
    /******************************************/
    /* Calculate common log value of diameter */
    /******************************************/
    double logD = log10(D2[i]);

    /********************/
    /* Fill histogram 2 */
    /********************/
    hist2->Fill(logD);
    
    /************************/
    /* Determine bin number */
    /************************/
    int index = floor((logD-log10_xlow)*bin_number);

    /*******************************************/
    /* Only include data above threshold value */
    /*******************************************/
    if((index < 0) || (index > nbins-1))
      continue;

    /***************************************/
    /* Increment bin associated with index */
    /***************************************/
    n_K2[index]++;
  }

  /************************/
  /* Calculate total area */
  /************************/
  total_area = A1[0];

  /*************************/
  /* Determined total area */
  /*************************/
  //cout << "Calculated total area for cumulative plot is: " << to_string(total_area) << " km^2" << endl;
  
  /***********************/
  /* Density calculation */
  /***********************/
  for(int i=nbins-1; i>=0; i--)
  {
    for(int j=i; j<nbins; j++)
    {
      Density1[i] += n_K1[j]/total_area;
      Density2[i] += n_K2[j]/total_area;
    }
  }
  
  /*****************************/
  /* Density error calculation */
  /*****************************/
  ylow_1 = std::numeric_limits<double>::infinity();
  yup_1 = -std::numeric_limits<double>::infinity();
  for(int i=nbins-1; i>=0; i--)
  {
    double N1 = 0;
    double N2 = 0;
    for(int j=i; j<nbins; j++)
    {
      N1 += n_K1[j];
      N2 += n_K2[j];
    }
    
    Density1_Error[i] = (N1 != 0) ? Density1[i]/sqrt(N1) : 0;
    Density2_Error[i] = (N2 != 0) ? Density2[i]/sqrt(N2) : 0;
    
    /***************************************************/
    /* Determine absolute max and min densities values */
    /***************************************************/
    double low_arg1 = Density1[i]-Density1_Error[i];
    double low_arg2 = Density2[i]-Density2_Error[i];
    double up_arg1 = Density1[i]+Density1_Error[i];
    double up_arg2 = Density2[i]+Density2_Error[i];
    if(low_arg1 < low_arg2)
      ylow_1 = (low_arg1 < ylow_1) ? low_arg1 : ylow_1;
    else
      ylow_1 = (low_arg2 < ylow_1) ? low_arg2 : ylow_1;
    if(up_arg1 > up_arg2)
      yup_1 = (up_arg1 > yup_1) ? up_arg1 : yup_1;
    else
      yup_1 = (up_arg2 > yup_1) ? up_arg2 : yup_1;
  }

  /***************************/
  /* Calculation of R values */
  /***************************/
  vector <double> R1(nbins);
  vector <double> R1_Error(nbins);
  vector <double> R2(nbins);
  vector <double> R2_Error(nbins);
  ylow_2 = std::numeric_limits<double>::infinity();
  yup_2 = -std::numeric_limits<double>::infinity();
  for(int i=0; i<nbins; i++)
  {
    double b1 = XAXISBIN[i];
    double b2 = b1+pow(10,binwidth);
    double D = sqrt(b1*b2);

    /**********************/
    /* First distribution */
    /**********************/
    double numerator = pow(D, 3.0)*n_K1[i];
    double denominator = total_area*(b2-b1);
    R1[i] = numerator/denominator;
    R1_Error[i] = (n_K1[i] != 0) ? R1[i]/sqrt(n_K1[i]) : 0;

    /***********************/
    /* Second distribution */
    /***********************/
    numerator = pow(D, 3.0)*n_K2[i];
    R2[i] = numerator/denominator;
    R2_Error[i] = (n_K2[i] != 0) ? R2[i]/sqrt(n_K2[i]) : 0;

    /*******************************************/
    /* Determine absolute max and min r values */
    /*******************************************/
    double low_arg1 = R1[i]-R1_Error[i];
    double low_arg2 = R2[i]-R2_Error[i];
    double up_arg1 = R1[i]+R1_Error[i];
    double up_arg2 = R2[i]+R2_Error[i];
    if(low_arg1 < low_arg2)
      ylow_2 = (low_arg1 < ylow_2) ? low_arg1 : ylow_2;
    else
      ylow_2 = (low_arg2 < ylow_2) ? low_arg2 : ylow_2;
    if(up_arg1 > up_arg2)
      yup_2 = (up_arg1 > yup_2) ? up_arg1 : yup_2;
    else
      yup_2 = (up_arg2 > yup_2) ? up_arg2 : yup_2;
  }

  /*******************************/
  /* Establish slope restriction */
  /*******************************/
  double slope_restriction = 2.0;
  
  /****************************************************/
  /* Calculate log-log slope and y-intercept of first */
  /* cumulative distribution assuming power law       */
  /****************************************************/
  double chiSquare1 = 0;
  double power1 = 0;
  double power1_error = 0;
  double coefficient1 = 0;
  double coefficient1_error = 0;
  int index = nbins-1;
  vector < vector <double> > cov1;
  while(index > 2)
  {
    /********************************/
    /* Retrieve x and y data points */
    /********************************/
    vector <double> x;
    vector <double> y;
    for(int i=nbins-1; i>=index-1; i--)
    {
      /*************************************************/
      /* Removes data points where density equals zero */
      /*************************************************/
      if(Density1[i] == 0)
	continue;
      
      /*************************************************/
      /* Record x and y data point for fit calculation */
      /*************************************************/
      x.push_back(XAXISBIN[i]);
      y.push_back(Density1[i]);
    }
    
    /***************************************/
    /* Ensures that a minimum of two data  */
    /* points are used for fit calculation */
    /***************************************/
    if((int)y.size() < 2)
    {
      /****************/
      /* Update index */
      /****************/
      index--;
      
      continue;
    }

    /**************************/
    /* Fit initial conditions */
    /**************************/
    int methodchoice = 2; // Least squares grid search method
    int modelchoice = 8; // Power-law fitting function (y = ax^-k)
    double sd = 0.5;
    vector <double> params = {3, 1}; // {k, a}
    vector <double> stepsizes = {0.001, 0.001};

    /****************************/
    /* Determine fit parameters */
    /****************************/
    LeastSquares Regression(x, y);
    Regression.Fit(methodchoice, modelchoice, sd, stepsizes, params);

    /***********************************************************/
    /* Apply slope condition as stated in Wilcox et al. (2006) */
    /***********************************************************/
    if(params[0] >= slope_restriction)
    {
      power1 = params[0];
      coefficient1 = params[1];
      chiSquare1 = Regression.GetChiSquare();
      cov1 = Regression.GetCovariance_matrix();
      power1_error = sqrt(cov1[0][0]);
      coefficient1_error = sqrt(cov1[1][1]);
    }
    
    /**********************************************/
    /* If we have not satisfied slope condition   */
    /* increase the number of points used for the */
    /* fit starting at the highest diameter bin   */
    /**********************************************/
    index--;
  }

  /*****************************************************/
  /* Calculate log-log slope and y-intercept of second */
  /* cumulative distribution assuming power law        */
  /*****************************************************/
  double chiSquare2;
  double power2 = 0;
  double power2_error = 0;
  double coefficient2 = 0;
  double coefficient2_error = 0;
  index = nbins-1;
  vector < vector <double> > cov2;
  while(index > 2)
  {
    /********************************/
    /* Retrieve x and y data points */
    /********************************/
    vector <double> x;
    vector <double> y;
    for(int i=nbins-1; i>=index-1; i--)
    {
      /*************************************************/
      /* Removes data points where density equals zero */
      /*************************************************/
      if(Density2[i] == 0)
	continue;
      
      /*************************************************/
      /* Record x and y data point for fit calculation */
      /*************************************************/
      x.push_back(XAXISBIN[i]);
      y.push_back(Density2[i]);
    }

    /***************************************/
    /* Ensures that a minimum of two data  */
    /* points are used for fit calculation */
    /***************************************/
    if((int)y.size() < 2)
    {
      /****************/
      /* Update index */
      /****************/
      index--;
      
      continue;
    }
    
    /**************************/
    /* Fit initial conditions */
    /**************************/
    int methodchoice = 2; // Least squares grid search method
    int modelchoice = 8; // Power-law fitting function (y = ax^-k)
    double sd = 0.5;
    vector <double> params = {3, 1}; // {k, a}
    vector <double> stepsizes = {0.001, 0.001};

    /****************************/
    /* Determine fit parameters */
    /****************************/
    LeastSquares Regression(x, y);
    Regression.Fit(methodchoice, modelchoice, sd, stepsizes, params);
    
    /***********************************************************/
    /* Apply slope condition as stated in Wilcox et al. (2006) */
    /***********************************************************/
    if(params[0] >= slope_restriction)
    {
      power2 = params[0];
      coefficient2 = params[1];
      chiSquare2 = Regression.GetChiSquare();
      cov2 = Regression.GetCovariance_matrix();
      power2_error = sqrt(cov2[0][0]);
      coefficient2_error = sqrt(cov2[1][1]);
    }
    
    /**********************************************/
    /* If we have not satisfied slope condition   */
    /* increase the number of points used for the */
    /* fit starting at the highest diameter bin   */
    /**********************************************/
    index--;
  }
  
  printf("Distribution 1: slope = %lf +/- %lf, amplitude = %lf +/- %lf\n", -power1, power1_error, coefficient1, coefficient1_error);
  printf("Distribution 2: slope = %lf +/- %lf, amplitude = %lf +/- %lf\n", -power2, power2_error, coefficient2, coefficient2_error);

  /*****************/
  /* Retrieve fits */
  /*****************/
  vector <double> Fit1(nbins);
  vector <double> Fit2(nbins);
  for(int i=0; i<nbins; i++)
  {
    Fit1[i] = coefficient1*pow(XAXISBIN[i], -power1);
    Fit2[i] = coefficient2*pow(XAXISBIN[i], -power2);
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
  TG1 = new TGraphErrors(nbins, XAXISBIN.data(), Density1.data(), 0, Density1_Error.data());
  
  /**********************/
  /* Initialize graph 2 */
  /**********************/
  TG2 = new TGraphErrors(nbins, XAXISBIN.data(), Density2.data(), 0, Density2_Error.data());
  
  /********************/
  /* Initialize fit 1 */
  /********************/
  F1 = new TGraph(nbins, XAXISBIN.data(), Fit1.data());
    
  /********************/
  /* Initialize fit 2 */
  /********************/
  F2 = new TGraph(nbins, XAXISBIN.data(), Fit2.data());

  /*****************/
  /* Plot settings */
  /*****************/
  TG1->SetTitle("");
  TG1->GetXaxis()->SetTitle("Diameter [km]");
  TG1->GetYaxis()->SetTitle("Cumulative Number of Craters [km^{-2}]");
  TG1->GetXaxis()->CenterTitle();
  TG1->GetYaxis()->CenterTitle();
  TG1->SetMarkerStyle(kOpenTriangleUp);
  TG1->SetMarkerColor(kBlue);
  TG1->GetXaxis()->SetRangeUser(xlow, xup);
  TG1->GetYaxis()->SetRangeUser(ylow_1, yup_1);
  TG1->Draw("AP");
  TG2->SetMarkerStyle(kFullTriangleUp);
  TG2->SetMarkerColor(kRed);
  TG2->Draw("P");
  F1->SetMarkerStyle(kDot);
  F1->SetMarkerColor(kBlue);
  F1->SetLineColor(kBlue);
  F1->Draw("L");
  F2->SetMarkerStyle(kDot);
  F2->SetMarkerColor(kRed);
  F2->SetLineColor(kRed);
  F2->Draw("L");

  /**********/
  /* Legend */
  /**********/
  //leg = new TLegend(0.7,0.7,0.9,0.9);
  leg = new TLegend(0.2,0.2,0.4,0.4);
  buffer = imagename1+", "+to_string(incidence_angle_1);
  leg->AddEntry(TG1, buffer.c_str(), "p");
  buffer = imagename2+", "+to_string(incidence_angle_2);
  leg->AddEntry(TG2, buffer.c_str(), "p");
  leg->Draw();
  
  /*********************/
  /* Save plot to file */
  /*********************/
  filename = "CumulativeFrequency_vs_SizeDistribution.ps";
  can->SaveAs(filename.c_str());

  /***********************/
  /* Initialize canvas 2 */
  /***********************/
  canwidth = 1000;
  canheight = 800;
  can2 = new TCanvas("Canvas 2", "", canwidth, canheight);

  /**************************/
  /* Make stacked bar graph */
  /**************************/
  buffer = "Frequency-Size Distribution; Crater Size [log_{10}(km)]; Frequency";
  bar = new THStack("Bar", buffer.c_str());
  hist1->SetFillColor(kBlue);
  bar->Add(hist1);
  hist2->SetFillColor(kRed);
  bar->Add(hist2);
  bar->Draw("nostackb");
  bar->GetXaxis()->SetLimits(log10_xlow, log10_xup);

  /************/
  /* Legend 2 */
  /************/
  leg2 = new TLegend(0.7,0.7,0.9,0.9);
  buffer = imagename1+", "+to_string(incidence_angle_1);
  leg2->AddEntry(hist1, buffer.c_str(), "f");
  buffer = imagename2+", "+to_string(incidence_angle_2);
  leg2->AddEntry(hist2, buffer.c_str(), "f");
  leg2->Draw();
  
  /*********************/
  /* Save plot to file */
  /*********************/
  filename = "Frequency_vs_SizeDistribution.ps";
  can2->SaveAs(filename.c_str());
  
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
  TG3 = new TGraphErrors(nbins, XAXISBIN.data(), R1.data(), 0, R1_Error.data());
  
  /**********************/
  /* Initialize graph 2 */
  /**********************/
  TG4 = new TGraphErrors(nbins, XAXISBIN.data(), R2.data(), 0, R2_Error.data());
  
  /*****************/
  /* Plot settings */
  /*****************/
  TG3->SetTitle("");
  TG3->GetXaxis()->SetTitle("Diameter [km]");
  TG3->GetYaxis()->SetTitle("R Value");
  TG3->GetXaxis()->CenterTitle();
  TG3->GetYaxis()->CenterTitle();
  TG3->SetMarkerStyle(kOpenTriangleUp);
  TG3->SetMarkerColor(kBlue);
  TG3->GetXaxis()->SetRangeUser(xlow, xup);
  TG3->GetYaxis()->SetRangeUser(ylow_2, yup_2);
  TG3->Draw("AP");
  TG4->SetMarkerStyle(kFullTriangleUp);
  TG4->SetMarkerColor(kRed);
  TG4->Draw("P");

  /**********/
  /* Legend */
  /**********/
  //leg = new TLegend(0.7,0.7,0.9,0.9);
  leg3 = new TLegend(0.2,0.2,0.4,0.4);
  buffer = imagename1+", "+to_string(incidence_angle_1);
  leg3->AddEntry(TG3, buffer.c_str(), "p");
  buffer = imagename2+", "+to_string(incidence_angle_2);
  leg3->AddEntry(TG4, buffer.c_str(), "p");
  leg3->Draw();
  
  /*********************/
  /* Save plot to file */
  /*********************/
  filename = "RValue_vs_SizeDistribution.ps";
  can3->SaveAs(filename.c_str());

  /***********************/
  /* Initialize canvas 3 */
  /***********************/
  canwidth = 1000;
  canheight = 800;
  TCanvas *can4 = new TCanvas("Canvas 4", "", canwidth, canheight);
  can4->Divide(1,2,0,0);

  gROOT->SetStyle("Plain");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  can4->cd(1);
  gPad->SetLogy();
  gPad->SetLogx();
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetBottomMargin(0.001);
  gPad->SetTopMargin(0.01);
  gPad->SetRightMargin(0.01);
  TG1->Draw("AP");
  TG2->Draw("P");

  can4->cd(2);
  gPad->SetLogy();
  gPad->SetLogx();
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetTopMargin(0.001);
  gPad->SetRightMargin(0.01);
  TG3->Draw("AP");
  TG4->Draw("P");
  //can4->Update();

  /**********/
  /* Legend */
  /**********/
  leg->Draw();
  
  /*********************/
  /* Save plot to file */
  /*********************/
  filename = "FullDistribution.ps";
  can4->SaveAs(filename.c_str());
  
  /********************************/
  /* Output plotting data to file */
  /********************************/
  OutFile1.open("CumulativeSizeFrequencyDistribution_"+to_string(incidence_angle_1)+"_vs_"+to_string(incidence_angle_2)+".dat");
  OutFile2.open("R_Distribution_"+to_string(incidence_angle_1)+"_vs_"+to_string(incidence_angle_2)+".dat");
  OutFile1 << setw(10) << "x1" << " \t | \t " << setw(10) << "y1" << " \t | \t " << setw(10) << "y1_err" << " \t | \t " << setw(10) << "x2" << " \t | \t " << setw(10) << "y2" << " \t | \t " << setw(10) << "y2_err" << endl;
  OutFile2 << setw(10) << "x1" << " \t | \t " << setw(10) << "y1" << " \t | \t " << setw(10) << "y1_err" << " \t | \t " << setw(10) << "x2" << " \t | \t " << setw(10) << "y2" << " \t | \t " << setw(10) << "y2_err" << endl;
  for(int i=0; i<nbins; i++)
  {
    OutFile1 << setw(10) << XAXISBIN[i] << " \t | \t " << setw(10) << Density1[i] << " \t | \t " << setw(10) << Density1_Error[i] << " \t | \t " << setw(10) << XAXISBIN[i] << " \t | \t " << setw(10) << Density2[i] << " \t | \t " << setw(10) << Density2_Error[i] << endl;
    OutFile2 << setw(10) << XAXISBIN[i] << " \t | \t " << setw(10) << R1[i] << " \t | \t " << setw(10) << R1_Error[i] << " \t | \t " << setw(10) << XAXISBIN[i] << " \t | \t " << setw(10) << R2[i] << " \t | \t " << setw(10) << R2_Error[i] << endl;
  }
  OutFile1.close();
  OutFile2.close();

  /***********************************/
  /* Free memory reserved for canvas */
  /***********************************/
  delete can;
  delete can2;
  delete can3;
  delete TG1;
  delete TG2;
  delete TG3;
  delete TG4;
  delete hist1;
  delete hist2;
  delete bar;
  delete leg;
  delete leg2;
  delete leg3;

  return;
}

void IncidenceAngleAnalysis_Plot::CumulativeFrequencySizeDistribution(string CraterCatalogue1, string CraterCatalogue2, TGraphErrors **CSFD1, TGraphErrors **CSFD2, TGraph **FIT1, TGraph **FIT2, TGraphErrors **RD1, TGraphErrors **RD2, TLegend **L)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  double binwidth;
  double incidence_angle_1;
  double incidence_angle_2;
  double intercept1;
  double intercept1_error;
  double intercept2;
  double intercept2_error;
  double log10_xlow;
  double log10_xhigh;
  double slope1;
  double slope1_error;
  double slope2;
  double slope2_error;
  double total_area;
  double xlow;
  double xhigh;
  // double ylow_1;
  // double ylow_2;
  // double yhigh_1;
  // double yhigh_2;
  int max_elements;
  int n;
  int nlines;
  string buffer;
  string filename;
  string format;
  string imagename1;
  string imagename2;
  stringstream stream;
  TGraph *F1 = nullptr;
  TGraph *F2 = nullptr;
  TGraphErrors *TG1 = nullptr;
  TGraphErrors *TG2 = nullptr;
  TGraphErrors *TG3 = nullptr;
  TGraphErrors *TG4 = nullptr;
  TLegend *leg = nullptr;
  unsigned nbins;
  vector <double> Density1;
  vector <double> Density2;
  vector <double> Density1_Error;
  vector <double> Density2_Error;
  vector <double> R1;
  vector <double> R2;
  vector <double> R1_Error;
  vector <double> R2_Error;
  vector <double> XAXISBIN;
  vector <double> XAXISBINLOG;
  
  /***********************************/
  /* Request memory for data vectors */
  /***********************************/
  n = 10;
  max_elements = 100000;
  vector < vector <double> > CC1(n, vector <double> (max_elements));
  vector < vector <double> > CC2(n, vector <double> (max_elements));
  
  /**********************/
  /* Read-in Filename 1 */
  /**********************/
  format = "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf";
  nlines = Readcol::Read(CraterCatalogue1, format, CC1[0].data(), CC1[1].data(),
		CC1[2].data(), CC1[3].data(), CC1[4].data(), CC1[5].data(),
		CC1[6].data(), CC1[7].data(), CC1[8].data(), CC1[9].data());
  for(int i = 0; i < (int)CC1.size(); i++)
    CC1[i].resize(nlines);
  
  /**********************/
  /* Read-in Filename 2 */
  /**********************/
  nlines = Readcol::Read(CraterCatalogue2, format, CC2[0].data(), CC2[1].data(),
		CC2[2].data(), CC2[3].data(), CC2[4].data(), CC2[5].data(),
		CC2[6].data(), CC2[7].data(), CC2[8].data(), CC2[9].data());
  for(int i = 0; i < (int)CC2.size(); i++)
    CC2[i].resize(nlines);
  
  /******************************************************/
  /* Parse filename 1 to retrieve pertinent information */
  /******************************************************/
  imagename1 = ExtractImageName(CraterCatalogue1);
  incidence_angle_1 = ExtractIncidenceAngle(CraterCatalogue1);

  /******************************************************/
  /* Parse filename 2 to retrieve pertinent information */
  /******************************************************/
  imagename2 = ExtractImageName(CraterCatalogue2);
  incidence_angle_2 = ExtractIncidenceAngle(CraterCatalogue2);
  
  /***************/
  /* Select data */
  /***************/
  vector <double> A1 = vectorMultiplication(CC1[8], m2km*m2km);
  vector <double> A2 = vectorMultiplication(CC2[8], m2km*m2km);
  vector <double> D1 = vectorMultiplication(CC1[5], m2km);
  vector <double> D2 = vectorMultiplication(CC2[5], m2km);
  
  /*************/
  /* Data swap */
  /*************/
  if(incidence_angle_2 > incidence_angle_1)
  {
    D1.swap(D2);
    A1.swap(A2);
    imagename1.swap(imagename2);
    vswap(incidence_angle_1, incidence_angle_2);
  }

  /***************************************************/
  /* Calculate the common logarithm of the diameters */
  /***************************************************/
  vector <double> logD1 = vectorLogarithm(D1);
  vector <double> logD2 = vectorLogarithm(D2);
  
  /*************************************/
  /* Determine x-axis characteristics  */
  /*************************************/
  binwidth = log10(sqrt(2)); 
  xlow = 10.0*m2km;
  xhigh = 110.0*m2km;
  log10_xlow = log10(xlow);
  log10_xhigh = log10(xhigh);
  nbins = MaxNearestMultiple(log10_xhigh-log10_xlow, binwidth)/binwidth;
  log10_xhigh = log10_xlow+nbins*binwidth;
  xhigh = pow(10, log10_xhigh);

  /**************************************************/
  /* Calculate histogram for crater identifications */
  /**************************************************/
  TH1F *hist1 = Plot::Histogram(logD1, nbins, log10_xlow, log10_xhigh, CraterCatalogue1);
  TH1F *hist2 = Plot::Histogram(logD2, nbins, log10_xlow, log10_xhigh, CraterCatalogue2);

  /*******************/
  /* Retrieve x-axis */
  /*******************/
  for(unsigned i = 0; i < nbins; i++) {
    XAXISBIN.push_back(pow(10, hist1->GetXaxis()->GetBinLowEdge(i+1)));
    XAXISBINLOG.push_back(hist1->GetXaxis()->GetBinLowEdge(i+1));
  }
  
  /***********************/
  /* Retrieve total area */
  /***********************/
  total_area = A1[0];
  
  /************************************************************/
  /* Calculate cumulative distributions and associated errors */
  /************************************************************/
  CumulativeCraterDensity(hist1, total_area, Density1, Density1_Error);
  CumulativeCraterDensity(hist2, total_area, Density2, Density2_Error);

  /***************************************************/
  /* Calculate R distributions and associated errors */
  /***************************************************/
  RelativeCraterDensity(hist1, total_area, R1, R1_Error);
  RelativeCraterDensity(hist2, total_area, R2, R2_Error);
  
  /***************************************************/
  /* Determine absolute max and min densities values */
  /***************************************************/
  // double low_arg1 = 0; //Density1[i]-Density1_Error[i];
  // double low_arg2 = 0; //Density2[i]-Density2_Error[i];
  // double up_arg1 = 0; //Density1[i]+Density1_Error[i];
  // double up_arg2 = 0; //Density2[i]+Density2_Error[i];
  // if(low_arg1 < low_arg2)
  //   ylow_1 = (low_arg1 < ylow_1) ? low_arg1 : ylow_1;
  // else
  //   ylow_1 = (low_arg2 < ylow_1) ? low_arg2 : ylow_1;
  // if(up_arg1 > up_arg2)
  //   yhigh_1 = (up_arg1 > yhigh_1) ? up_arg1 : yhigh_1;
  // else
  //   yhigh_1 = (up_arg2 > yhigh_1) ? up_arg2 : yhigh_1;

  /*******************************************/
  /* Determine absolute max and min r values */
  /*******************************************/
  // double low_arg1 = 0; // R1[i]-R1_Error[i];
  // double low_arg2 = 0; // R2[i]-R2_Error[i];
  // double up_arg1 = 0; // R1[i]+R1_Error[i];
  // double up_arg2 = 0; // R2[i]+R2_Error[i];
  // if(low_arg1 < low_arg2)
  //   ylow_2 = (low_arg1 < ylow_2) ? low_arg1 : ylow_2;
  // else
  //   ylow_2 = (low_arg2 < ylow_2) ? low_arg2 : ylow_2;
  // if(up_arg1 > up_arg2)
  //   yhigh_2 = (up_arg1 > yhigh_2) ? up_arg1 : yhigh_2;
  // else
  //   yhigh_2 = (up_arg2 > yhigh_2) ? up_arg2 : yhigh_2;

  /***************************************************************/
  /* Send crater population data to file for 1st incidence angle */
  /***************************************************************/
  Utilities::PrintCraterPopulationData(CraterCatalogue1, imagename1, incidence_angle_1, total_area, hist1, Density1, Density1_Error, R1, R1_Error);
  
  /***************************************************************/
  /* Send crater population data to file for 2nd incidence angle */
  /***************************************************************/
  Utilities::PrintCraterPopulationData(CraterCatalogue2, imagename2, incidence_angle_2, total_area, hist2, Density2, Density2_Error, R2, R2_Error);
  
  /****************************************/
  /* Least Squares Fitting Algorithm Test */
  /****************************************/
  // LeastSquares::Test(); exit(0);
  
  /****************************************************/
  /* Calculate log-log slope and y-intercept of first */
  /* cumulative distribution assuming power law       */
  /****************************************************/
  // CSFDFittingRoutine(XAXISBIN, Density1, slope1, slope1_error, intercept1, intercept1_error);
  
  /*****************************************************/
  /* Calculate log-log slope and y-intercept of second */
  /* cumulative distribution assuming power law        */
  /*****************************************************/
  // CSFDFittingRoutine(XAXISBIN, Density2, slope2, slope2_error, intercept2, intercept2_error);

  /*****************/
  /* Retrieve fits */
  /*****************/
  // vector <double> Fit1(nbins);
  // vector <double> Fit2(nbins);
  // for(unsigned i = 0; i < nbins; i++)
  // {
  //   Fit1[i] = intercept1*pow(XAXISBIN[i], -slope1);
  //   Fit2[i] = intercept2*pow(XAXISBIN[i], -slope2);
  // }
  
  // cout << "Data below are best fit parameters for comparison between incidence angles " << incidence_angle_1 << " and " << incidence_angle_2 << endl; 
  // cout << "Image " << imagename1 << " slope: " << slope1 << " +/- " << slope1_error << endl;
  // cout << "Image " << imagename1 << " amplitude: " << intercept1 << " +/- " << intercept1_error << endl;
  // cout << "Image " << imagename2 << " slope: " << slope2 << " +/- " << slope2_error << endl;
  // cout << "Image " << imagename2 << " amplitude: " << intercept2 << " +/- " << intercept2_error << endl << endl;

  /*****************/
  /* Plot settings */
  /*****************/
  string xtitle = "Diameter [km]";
  string ytitle = "Cumulative Number of Craters [km^{-2}]";
  
  /**********************/
  /* Initialize graph 1 */
  /**********************/
  TG1 = Plot::ScatterPlot(XAXISBIN, Density1, vector <double> (0), Density1_Error, "", xtitle, ytitle, kBlue, 1, kOpenTriangleUp);
    
  /**********************/
  /* Initialize graph 2 */
  /**********************/
  TG2 = Plot::ScatterPlot(XAXISBIN, Density2, vector <double> (0), Density2_Error, "", xtitle, ytitle, kRed, 1, kOpenTriangleUp);

  /********************/
  /* Initialize fit 1 */
  /********************/
  // F1 = Plot::ScatterPlot(XAXISBIN, Fit1, "", "", "", kBlue, 1, kDot);
    
  /********************/
  /* Initialize fit 2 */
  /********************/
  // F2 = Plot::ScatterPlot(XAXISBIN, Fit2, "", "", "", kRed, 1, kDot);
  
  /*****************/
  /* Plot settings */
  /*****************/
  // TG1->GetXaxis()->SetRangeUser(xlow, xhigh);
  // TG1->GetYaxis()->SetRangeUser(ylow_1, yhigh_1);
  //TG2->SetMarkerStyle(kFullDotMedium);
  // F1->SetLineColor(kBlue);
  // F2->SetLineColor(kRed);
  
  /**********/
  /* Legend */
  /**********/
  leg = new TLegend(0.1 ,0.1, 0.75, 0.3);
  stream << fixed << setprecision(2) << incidence_angle_1;
  buffer = imagename1+", "+stream.str();
  stream.str(std::string());
  leg->AddEntry(TG1, buffer.c_str(), "lep");
  stream << fixed << setprecision(2) << incidence_angle_2;
  buffer = imagename2+", "+stream.str();
  stream.str(std::string());
  leg->AddEntry(TG2, buffer.c_str(), "lep");

  /*****************/
  /* Plot settings */
  /*****************/
  ytitle = "R Value";
  
  /***********************/
  /* Initialize R-plot 1 */
  /***********************/
  TG3 = Plot::ScatterPlot(XAXISBIN, R1, vector <double> (0), R1_Error, "", xtitle, ytitle, kBlue, 1, kOpenTriangleUp);
  
  /***********************/
  /* Initialize R-plot 2 */
  /***********************/
  TG4 = Plot::ScatterPlot(XAXISBIN, R2, vector <double> (0), R2_Error, "", xtitle, ytitle, kRed, 1, kOpenTriangleUp);
  
  /*****************/
  /* Plot settings */
  /*****************/
  // TG3->GetXaxis()->SetRangeUser(xlow, xhigh);
  // TG3->GetYaxis()->SetRangeUser(ylow_2, yhigh_2);
  
  /***************/
  /* Record data */
  /***************/
  *CSFD1 = (TGraphErrors *)TG1->Clone();  
  *CSFD2 = (TGraphErrors *)TG2->Clone();
  // *FIT1 = (TGraph *)F1->Clone();
  // *FIT2 = (TGraph *)F2->Clone();
  *RD1 = (TGraphErrors *)TG3->Clone();
  *RD2 = (TGraphErrors *)TG4->Clone();
  *L = (TLegend *)leg->Clone();
  
  /***********************************/
  /* Free memory reserved for canvas */
  /***********************************/
  // delete F1;
  // delete F2;
  delete TG1;
  delete TG2;
  delete TG3;
  delete TG4;
  delete leg;

  return;
}

void IncidenceAngleAnalysis_Plot::ImageComparison(double x1, double x2, double y1, double y2, string cratercatalog1, string cratercatalog2, string imagedirlist, vector <ImageSets> &imagesets, vector <Images> &images, vector <IncidenceAngles> &incidenceangles, bool selenographic)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double incidence_angle_1;
  double incidence_angle_2;
  double spacing;
  double x_high;
  double x_low;
  double x_max;
  double x_min;
  double y_high;
  double y_low;
  double y_min;
  double y_max;
  ifstream InFile;
  int canheight;
  int canwidth;
  int max_elements;
  int n;
  int nlines;
  string buffer;
  string field;
  string filename;
  string format;
  string skipline;
  TCanvas *can;
  TH1F *h1;
  TH1F *h2;
  vector <double> A1;
  vector <double> A2;
  vector <double> D1;
  vector <double> D2;
  vector <double> incidence_angles;
  vector <double> XAXISBIN;
  vector <double> XAXISBINLOG;
  vector <double> xrange;
  vector <double> yrange;
  vector <int> master_image_id;
  vector <string> image_directories;
  vector <string> master_image_names;
  vector < vector <TASImage *> > tasimages;
  vector < vector <TPad *> > pads;

  /***********************************/
  /* Request memory for data vectors */
  /***********************************/
  n = 10;
  max_elements = 100000;
  vector < vector <double> > CC1(n, vector <double> (max_elements));
  vector < vector <double> > CC2(n, vector <double> (max_elements));
  
  /**********************/
  /* Read-in Filename 1 */
  /**********************/
  format = "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf";
  nlines = Readcol::Read(cratercatalog1, format, CC1[0].data(), CC1[1].data(),
		CC1[2].data(), CC1[3].data(), CC1[4].data(), CC1[5].data(),
		CC1[6].data(), CC1[7].data(), CC1[8].data(), CC1[9].data());
  for(int i = 0; i < (int)CC1.size(); i++)
    CC1[i].resize(nlines);
  
  /**********************/
  /* Read-in Filename 2 */
  /**********************/
  nlines = Readcol::Read(cratercatalog2, format, CC2[0].data(), CC2[1].data(),
		CC2[2].data(), CC2[3].data(), CC2[4].data(), CC2[5].data(),
		CC2[6].data(), CC2[7].data(), CC2[8].data(), CC2[9].data());
  for(int i = 0; i < (int)CC2.size(); i++)
    CC2[i].resize(nlines);

  /***********************************/
  /* Request memory for data vectors */
  /***********************************/
  n = 1000;
  vector <string> image_files(n);
  
  /**********************/
  /* Read-in image data */
  /**********************/
  format = "%s";
  skipline = "/";
  nlines = Readcol::Read(imagedirlist, skipline, format, image_files.data());
  image_files.resize(nlines);
  
  /***************************************/
  /* Sort incidenceangles vector by name */
  /***************************************/
  field = "name";
  SortData <IncidenceAngles> sortincidenceangles(incidenceangles, field);
  sortincidenceangles.arrange();
  incidenceangles = sortincidenceangles.GetData();

  /*********************************/
  /* Sort imagesets vector by name */
  /*********************************/
  field = "name";
  SortData <ImageSets> sortimagesets(imagesets, field);
  sortimagesets.arrange();
  imagesets = sortimagesets.GetData();

  /*****************************************************************/
  /* Retrieve master image names and corresponding incidence angle */
  /*****************************************************************/
  incidence_angle_1 = 0;
  incidence_angle_2 = 0;
  n = (int)incidenceangles.size();
  for(int i=0; i<(int)image_directories.size(); i++)
  {
    /*****************/
    /* Retrieve name */
    /*****************/
    int p1 = image_directories[i].rfind("_")+1;
    string imagename = image_directories[i].substr(p1, 12);
    master_image_names.push_back(imagename);

    /******************/
    /* Retrieve angle */
    /******************/
    int index = SearchData<IncidenceAngles>::BinarySearch(incidenceangles, 0, n-1, field, &imagename);
    incidence_angles.push_back(incidenceangles[index].GetIncidence_angle());

    /*******************************/
    /* Set incidence angle 1 and 2 */
    /*******************************/
    if(incidence_angle_1 == 0)
      incidence_angle_1 = incidence_angles.back();
    else
      if((incidence_angles.back() != incidence_angle_1) && (incidence_angle_2 == 0))
	incidence_angle_2 = incidence_angles.back();
  }

  /**************************/
  /* Retrieve master images */
  /**************************/
  n = (int)imagesets.size();
  for(int i=0; i<(int)master_image_names.size(); i++)
  {
    /******************************/
    /* Identify master image name */
    /******************************/
    string master_image_name = master_image_names[i];
    
    /*********************************************/
    /* Find master image within imagesets vector */
    /*********************************************/
    int index = SearchData<ImageSets>::BinarySearch(imagesets, 0, n-1, field, &master_image_name);

    /******************************/
    /* Retrieve image information */
    /******************************/
    master_image_id.push_back(imagesets[index].GetId());
  }

  /*****************/
  /* Axes settings */
  /*****************/
  if(selenographic)
  {
    buffer = "; X [Degree]; Y [Degree]";
    spacing = 1.0E-2;
  }
  else
  {
    buffer = "; X [m]; Y [m]";
    spacing = 1.0E3;
  }
  x_high = (x1 > x2) ? x1 : x2;
  x_low = (x1 < x2) ? x1 : x2;
  y_high = (y1 > y2) ? y1 : y2;
  y_low = (y1 < y2) ? y1 : y2;
  
  /**********************/
  /* Sort images vector */
  /**********************/
  field = "image_set_id";
  SortData <Images> sortimages(images, field);
  sortimages.arrange();
  images = sortimages.GetData();

  /*********************/
  /* Initialize Canvas */
  /*********************/
  canheight = 1200;
  canwidth = 800;
  // can = new TCanvas("Canvas", "", canheight, canwidth);
  can = new TCanvas("Canvas");
  can->Divide(2, 1);
  can->SetGridx();
  can->SetGridy();

  /***********************/
  /* Draw frame in pad 1 */
  /***********************/
  can->cd(1);
  h1 = can->DrawFrame(x_low-spacing, y_low-spacing, x_high+spacing, y_high+spacing, buffer.c_str());
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetNdivisions(5);
  h1->GetXaxis()->CenterTitle();
  h1->GetXaxis()->SetNdivisions(5);
  gPad->GetRange(x_min, y_min, x_max, y_max);
  xrange.push_back(x_max-x_min);
  yrange.push_back(y_max-y_min);  

  /***********************/
  /* Draw frame in pad 2 */
  /***********************/
  can->cd(2);
  h2 = can->DrawFrame(x_low-spacing, y_low-spacing, x_high+spacing, y_high+spacing, buffer.c_str());
  h2->GetYaxis()->CenterTitle();
  h2->GetYaxis()->SetNdivisions(5);
  h2->GetXaxis()->CenterTitle();
  h2->GetXaxis()->SetNdivisions(5);
  gPad->GetRange(x_min, y_min, x_max, y_max);
  xrange.push_back(x_max-x_min);
  yrange.push_back(y_max-y_min);

  /*********************************/
  /* Iterate through master images */
  /*********************************/
  for(int i=0; i<(int)master_image_id.size(); i++)
  {
    /*******************************************************************/
    /* Find first and last occurrence of image_set_id in images vector */
    /*******************************************************************/
    n = (int)images.size();
    int value = master_image_id[i];
    int first_index = SearchData<Images>::FirstOccurence(images, 0, n-1, field, &value);
    int last_index = SearchData<Images>::LastOccurence(images, 0, n-1, field, &value);

    /*****************************************************/
    /* Iterate through images vector and plot sub-images */
    /*****************************************************/
    for(int j=first_index; j<=last_index; j++)
    {
      /*****************************/
      /* Determine sub-image scale */
      /*****************************/
      string sub_image_name = images[j].GetName();
      int p1 = sub_image_name.find("_")+1;
      int scl = stoi(sub_image_name.substr(p1, 1), nullptr);
      if(scl == 0)
      {
	/************************************/
	/* Determine sub-image slice number */
	/************************************/
	int p2 = sub_image_name.rfind("_")+1;
	int p3 = sub_image_name.length();
	int length = p3-p2;
	int image_slice_number = stoi(sub_image_name.substr(p2, length), nullptr);
	
	/***********************/
	/* Find image filename */
	/***********************/
	int index = -1;
	for(int k=0; k<(int)image_files.size(); k++)
	{
	  string name = image_files[k].substr(0, 12);
	  p2 = image_files[k].rfind("_")+1;
	  p3 = image_files[k].find(".")+1;
	  length = p3-p2;
	  int isn = stoi(image_files[k].substr(p2, length), nullptr);
	  if((master_image_names[i].compare(name) == 0) && (image_slice_number == isn))
	  {
	    index = k;
	    break;
	  }
	}

	/*********************************/
	/* Construct image full filename */
	/*********************************/
	filename = (index != -1) ? image_directories[i]+"/"+image_files[index] : nullptr;

	/*************************************************/
	/* Retrieve positional information for sub-image */
	/*************************************************/
	double sub_image_lower_left_latitude = images[j].GetLower_left_latitude();
	double sub_image_lower_left_y = images[j].GetLower_left_y();
	double sub_image_maximum_latitude = images[j].GetMaximum_latitude();
	double sub_image_maximum_longitude = images[j].GetMaximum_longitude();
	double sub_image_maximum_x = images[j].GetMaximum_x();
	double sub_image_maximum_y = images[j].GetMaximum_y();
	double sub_image_minimum_latitude = images[j].GetMinimum_latitude();
	double sub_image_minimum_longitude = images[j].GetMinimum_longitude();
	double sub_image_minimum_x = images[j].GetMinimum_x();
	double sub_image_minimum_y = images[j].GetMinimum_y();
	double sub_image_upper_left_latitude = images[j].GetUpper_left_latitude();
	double sub_image_upper_left_longitude = images[j].GetUpper_left_longitude();
	double sub_image_upper_left_x = images[j].GetUpper_left_x();
	double sub_image_upper_left_y = images[j].GetUpper_left_y();
	double sub_image_upper_right_longitude = images[j].GetUpper_right_longitude();
	double sub_image_upper_right_x = images[j].GetUpper_right_x();

	/****************************************************************/
	/* Skip image if any part of it lies outside of wanted boundary */
	/****************************************************************/
	if(selenographic)
	{
	  if((x1 > sub_image_minimum_longitude) || (sub_image_maximum_longitude > x2))
	    continue;
	  if((y1 > sub_image_minimum_latitude) || (sub_image_maximum_latitude > y2))
	    continue;
	}
	else
	{
	  if((x1 > sub_image_minimum_x) || (sub_image_maximum_x > x2))
	    continue;
	  if((y1 > sub_image_minimum_y) || (sub_image_maximum_y > y2))
	    continue;
	}

	/******************/
	/* Initialize pad */
	/******************/
	double x_1 = 0;
	double x_2 = 0;
	double y_1 = 0;
	double y_2 = 0;
	if(selenographic)
	{
	  x_2 = (sub_image_maximum_longitude-x_min)/xrange[i];
	  x_1 = (sub_image_minimum_longitude-x_min)/xrange[i];
	  y_2 = (sub_image_maximum_latitude-y_min)/yrange[i];
	  y_1 = (sub_image_minimum_latitude-y_min)/yrange[i];
	}
	else
	{
	  x_2 = (sub_image_maximum_x-x_min)/xrange[i];
	  x_1 = (sub_image_minimum_x-x_min)/xrange[i];
	  y_2 = (sub_image_maximum_y-y_min)/yrange[i];
	  y_1 = (sub_image_minimum_y-y_min)/yrange[i];
	}
	TPad *pad = new TPad(image_files[index].c_str(), image_files[index].c_str(), x_1, y_1, x_2, y_2);
	
	/************************/
	/* Make pad transparent */
	/************************/
	pad->SetFillColorAlpha(kWhite, 0.);

	/********************************/
	/* Record current sub-image pad */
	/********************************/	
	pads[i].push_back(pad);

	/**************************/
	/* Open current sub-image */
	/**************************/
	TASImage *img = new TASImage(filename.c_str());
	if (!img)
	{
	  printf("Could not open image %s.\nTerminating program...\n", filename.c_str());
	  exit(1);
	}
	img->SetConstRatio(kFALSE);
	img->SetImageQuality(TAttImage::kImgBest);

	/*****************************/
	/* Correct image orientation */
	/*****************************/
	if(selenographic)
	{
	  if(sub_image_upper_left_longitude > sub_image_upper_right_longitude)
	  {
	    if(sub_image_upper_left_latitude < sub_image_lower_left_latitude)
	      img->Flip(180);
	    else	    
	      img->Mirror(true);
	  }
	}
	else
	{
	  if(sub_image_upper_left_x > sub_image_upper_right_x)
	  {
	    if(sub_image_upper_left_y < sub_image_lower_left_y)
	      img->Flip(180);
	    else
	      img->Mirror(true);
	  }
	}
	img->SetEditable(kTRUE);

	/****************************/
	/* Record current sub-image */
	/****************************/	
	tasimages[i].push_back(img);
      }
    }
  }

  /********************/
  /* Speed up drawing */
  /********************/
  gStyle->SetCanvasPreferGL(kTRUE);

  /****************/
  /* Draw image 1 */
  /****************/
  can->cd(1);
  for(int j=0; j<(int)pads[0].size(); j++)
  {     
    pads[0][j]->Draw();
    pads[0][j]->cd();
    tasimages[0][j]->Draw("X");
    can->cd(1);
  }

  /****************/
  /* Draw image 2 */
  /****************/
  can->cd(2);
  for(int j=0; j<(int)pads[1].size(); j++)
  {     
    pads[1][j]->Draw();
    pads[1][j]->cd();
    tasimages[1][j]->Draw("X");
    can->cd(2);
  }

  /*********************/
  /* Save plot to file */
  /*********************/
  filename = "ImageComparison.ps";
  can->Print(filename.c_str());

  return;
}

void IncidenceAngleAnalysis_Plot::ImageMosaic(string imagedirlist, vector <ImageSets> &imagesets, vector <Images> &images, vector <IncidenceAngles> &incidenceangles, bool selenographic)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double incidence_angle_1;
  double incidence_angle_2;
  double incidence_angle_1_area;
  double incidence_angle_2_area;
  double incidence_angle_w_max_area;
  double spacing;
  double x_high;
  double x_low;
  double x_max;
  double x_min;
  double xrange;
  double y_high;
  double y_low;
  double y_min;
  double y_max;
  double yrange;
  ifstream InFile;
  int canheight;
  int canwidth;
  int first_index;
  int last_index;
  int n;
  int nlines;
  int value;
  string buffer;
  string delay;
  string field;
  string filename;
  string format;
  TCanvas *can;
  TH1F *h1;
  vector <double> incidence_angles;
  vector <double> master_image_areas;
  vector <double> maximum_latitude;
  vector <double> maximum_longitude;
  vector <double> maximum_x;
  vector <double> maximum_y;
  vector <double> minimum_latitude;
  vector <double> minimum_longitude;
  vector <double> minimum_x;
  vector <double> minimum_y;
  vector <int> master_image_id;
  vector <string> image_directories;
  vector <string> master_image_names;
  vector < vector <TASImage *> > tasimages(6, vector <TASImage *> ());
  vector < vector <TPad *> > pads(2, vector <TPad *> ());

  /***********************************/
  /* Request memory for data vectors */
  /***********************************/
  n = 10;
  vector <string> image_files(n);
  
  /**********************/
  /* Read-in Filename 1 */
  /**********************/
  format = "%[^:]";
  nlines = Readcol::Read(imagedirlist, format, image_files.data());
  image_files.resize(nlines);
  
  /**********************/
  /* Read-in image data */
  /**********************/
  // if(FileExists(imagedirlist))
  //   InFile.open(imagedirlist.c_str());
  // else
  // {
  //   printf("Error: File %s does not exist!\n", imagedirlist.c_str());
  //   exit(EXIT_FAILURE);
  // }
  // while(getline(InFile, buffer))
  // {
  //   char str[250];
  //   format = "%[^:]";
  //   sscanf(buffer.c_str(), format.c_str(), str);
  //   buffer = str;
  //   int p1 = buffer.rfind("/")+1;
  //   if(buffer.substr(p1, 6).compare("images") == 0)
  //     image_directories.push_back(str);
  //   p1 = buffer.rfind(".")+1;
  //   if(buffer.substr(p1, 3).compare("png") == 0)
  //     image_files.push_back(str);
  // }
  // InFile.close();

  /***************************************/
  /* Sort incidenceangles vector by name */
  /***************************************/
  field = "name";
  SortData <IncidenceAngles> sortincidenceangles(incidenceangles, field);
  sortincidenceangles.arrange();
  incidenceangles = sortincidenceangles.GetData();

  /*********************************/
  /* Sort imagesets vector by name */
  /*********************************/
  field = "name";
  SortData <ImageSets> sortimagesets(imagesets, field);
  sortimagesets.arrange();
  imagesets = sortimagesets.GetData();

  /*****************************************************************/
  /* Retrieve master image names and corresponding incidence angle */
  /*****************************************************************/
  incidence_angle_1 = 0;
  incidence_angle_2 = 0;
  n = (int)incidenceangles.size();
  for(int i=0; i<(int)image_directories.size(); i++)
  {
    /*****************/
    /* Retrieve name */
    /*****************/
    int p1 = image_directories[i].rfind("_")+1;
    string imagename = image_directories[i].substr(p1, 12);
    master_image_names.push_back(imagename);

    /******************/
    /* Retrieve angle */
    /******************/
    int index = SearchData<IncidenceAngles>::BinarySearch(incidenceangles, 0, n-1, field, &imagename);
    incidence_angles.push_back(incidenceangles[index].GetIncidence_angle());

    /*******************************/
    /* Set incidence angle 1 and 2 */
    /*******************************/
    if(incidence_angle_1 == 0)
      incidence_angle_1 = incidence_angles.back();
    else
      if((incidence_angles.back() != incidence_angle_1) && (incidence_angle_2 == 0))
	incidence_angle_2 = incidence_angles.back();
  }

  /**************************/
  /* Retrieve master images */
  /**************************/
  n = (int)imagesets.size();
  for(int i=0; i<(int)master_image_names.size(); i++)
  {
    /******************************/
    /* Identify master image name */
    /******************************/
    string master_image_name = master_image_names[i];
    
    /*********************************************/
    /* Find master image within imagesets vector */
    /*********************************************/
    int index = SearchData<ImageSets>::BinarySearch(imagesets, 0, n-1, field, &master_image_name);

    /******************************/
    /* Retrieve image information */
    /******************************/
    master_image_areas.push_back(imagesets[index].GetArea());
    master_image_id.push_back(imagesets[index].GetId());
    maximum_latitude.push_back(imagesets[index].GetMaximum_latitude());
    maximum_longitude.push_back(imagesets[index].GetMaximum_longitude());
    maximum_x.push_back(imagesets[index].GetMaximum_x());
    maximum_y.push_back(imagesets[index].GetMaximum_y());
    minimum_latitude.push_back(imagesets[index].GetMinimum_latitude());
    minimum_longitude.push_back(imagesets[index].GetMinimum_longitude());
    minimum_x.push_back(imagesets[index].GetMinimum_x());
    minimum_y.push_back(imagesets[index].GetMinimum_y());
  }

  /***********************************/
  /* Determine which incidence angle */
  /* covers the most surface area    */
  /***********************************/
  incidence_angle_1_area = 0;
  incidence_angle_2_area = 0;
  for(int i=0; i<(int)master_image_areas.size(); i++)
  {
    incidence_angle_1_area += (incidence_angles[i] == incidence_angle_1) ? 
                              master_image_areas[i] : incidence_angle_1_area;
    incidence_angle_2_area += (incidence_angles[i] == incidence_angle_2) ? 
                              master_image_areas[i] : incidence_angle_2_area;
  }
  incidence_angle_w_max_area = (incidence_angle_1_area > incidence_angle_2_area) ? 
                               incidence_angle_1 : incidence_angle_2;

  /*****************/
  /* Axes settings */
  /*****************/
  if(selenographic)
  {
    buffer = "; X [Degree]; Y [Degree]";
    x_high = -std::numeric_limits<double>::infinity();
    x_low = std::numeric_limits<double>::infinity();
    y_high = -std::numeric_limits<double>::infinity();
    y_low = std::numeric_limits<double>::infinity();
    for(int i=0; i<(int)master_image_id.size(); i++)
    {
      x_high = (maximum_longitude[i] > x_high) ? maximum_longitude[i] : x_high;
      x_low = (minimum_longitude[i] < x_low) ? minimum_longitude[i] : x_low;
      y_high = (maximum_latitude[i] > y_high) ? maximum_latitude[i] : y_high;
      y_low = (minimum_latitude[i] < y_low) ? minimum_latitude[i] : y_low;
    }
    spacing = 1.0E-2;
  }
  else
  {
    buffer = "; X [m]; Y [m]";
    x_high = -std::numeric_limits<double>::infinity();
    x_low = std::numeric_limits<double>::infinity();
    y_high = -std::numeric_limits<double>::infinity();
    y_low = std::numeric_limits<double>::infinity();
    for(int i=0; i<(int)master_image_id.size(); i++)
    {
      x_high = (maximum_x[i] > x_high) ? maximum_x[i] : x_high;
      x_low = (minimum_x[i] < x_low) ? minimum_x[i] : x_low;
      y_high = (maximum_y[i] > y_high) ? maximum_y[i] : y_high;
      y_low = (minimum_y[i] < y_low) ? minimum_y[i] : y_low;
    }
    spacing = 1.0E3;
  }

  /**********************/
  /* Sort images vector */
  /**********************/
  field = "image_set_id";
  SortData <Images> sortimages(images, field);
  sortimages.arrange();
  images = sortimages.GetData();

  /*********************/
  /* Initialize Canvas */
  /*********************/
  canheight = 1200;
  canwidth = 800;
  can = new TCanvas("Canvas", "", canheight, canwidth);
  can->SetGridx();
  can->SetGridy();

  /**************/
  /* Draw frame */
  /**************/
  h1 = can->DrawFrame(x_low-spacing, y_low-spacing, x_high+spacing, y_high+spacing, buffer.c_str());
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetNdivisions(5);
  h1->GetXaxis()->CenterTitle();
  h1->GetXaxis()->SetNdivisions(5);
  gPad->GetRange(x_min, y_min, x_max, y_max);
  xrange = x_max-x_min;
  yrange = y_max-y_min;  

  /*********************************/
  /* Iterate through master images */
  /*********************************/
  for(int i=0; i<(int)master_image_id.size(); i++)
  {
    /*******************************************************************/
    /* Find first and last occurrence of image_set_id in images vector */
    /*******************************************************************/
    n = (int)images.size();
    value = master_image_id[i];
    first_index = SearchData<Images>::FirstOccurence(images, 0, n-1, field, &value);
    last_index = SearchData<Images>::LastOccurence(images, 0, n-1, field, &value);

    /*****************************************************/
    /* Iterate through images vector and plot sub-images */
    /*****************************************************/
    for(int j=first_index; j<=last_index; j++)
    {
      /*****************************/
      /* Determine sub-image scale */
      /*****************************/
      string sub_image_name = images[j].GetName();
      int p1 = sub_image_name.find("_")+1;
      int scl = stoi(sub_image_name.substr(p1, 1), nullptr);
      if(scl == 0)
      {
	/************************************/
	/* Determine sub-image slice number */
	/************************************/
	int p2 = sub_image_name.rfind("_")+1;
	int p3 = sub_image_name.length();
	int length = p3-p2;
	int image_slice_number = stoi(sub_image_name.substr(p2, length), nullptr);
	
	/***********************/
	/* Find image filename */
	/***********************/
	int index = -1;
	for(int k=0; k<(int)image_files.size(); k++)
	{
	  string name = image_files[k].substr(0, 12);
	  p2 = image_files[k].rfind("_")+1;
	  p3 = image_files[k].find(".")+1;
	  length = p3-p2;
	  int isn = stoi(image_files[k].substr(p2, length), nullptr);
	  if((master_image_names[i].compare(name) == 0) && (image_slice_number == isn))
	  {
	    index = k;
	    break;
	  }
	}

	/*********************************/
	/* Construct image full filename */
	/*********************************/
	filename = (index != -1) ? image_directories[i]+"/"+image_files[index] : nullptr;

	/*************************************************/
	/* Retrieve positional information for sub-image */
	/*************************************************/
	double sub_image_lower_left_latitude = images[j].GetLower_left_latitude();
	double sub_image_lower_left_y = images[j].GetLower_left_y();
	double sub_image_maximum_latitude = images[j].GetMaximum_latitude();
	double sub_image_maximum_longitude = images[j].GetMaximum_longitude();
	double sub_image_maximum_x = images[j].GetMaximum_x();
	double sub_image_maximum_y = images[j].GetMaximum_y();
	double sub_image_minimum_latitude = images[j].GetMinimum_latitude();
	double sub_image_minimum_longitude = images[j].GetMinimum_longitude();
	double sub_image_minimum_x = images[j].GetMinimum_x();
	double sub_image_minimum_y = images[j].GetMinimum_y();
	double sub_image_upper_left_latitude = images[j].GetUpper_left_latitude();
	double sub_image_upper_left_longitude = images[j].GetUpper_left_longitude();
	double sub_image_upper_left_x = images[j].GetUpper_left_x();
	double sub_image_upper_left_y = images[j].GetUpper_left_y();
	double sub_image_upper_right_longitude = images[j].GetUpper_right_longitude();
	double sub_image_upper_right_x = images[j].GetUpper_right_x();

	/******************/
	/* Initialize pad */
	/******************/
	double x1 = 0;
	double x2 = 0;
	double y1 = 0;
	double y2 = 0;
	if(selenographic)
	{
	  x2 = (sub_image_maximum_longitude-x_min)/xrange;
	  x1 = (sub_image_minimum_longitude-x_min)/xrange;
	  y2 = (sub_image_maximum_latitude-y_min)/yrange;
	  y1 = (sub_image_minimum_latitude-y_min)/yrange;
	}
	else
	{
	  x2 = (sub_image_maximum_x-x_min)/xrange;
	  x1 = (sub_image_minimum_x-x_min)/xrange;
	  y2 = (sub_image_maximum_y-y_min)/yrange;
	  y1 = (sub_image_minimum_y-y_min)/yrange;
	}
	TPad *pad = new TPad(image_files[index].c_str(), image_files[index].c_str(), x1, y1, x2, y2);
	
	/************************/
	/* Make pad transparent */
	/************************/
	pad->SetFillColorAlpha(kWhite, 0.);

	/********************************/
	/* Record current sub-image pad */
	/********************************/	
	if(incidence_angle_w_max_area == incidence_angles[i])
	  pads[0].push_back(pad);
	else
	  pads[1].push_back(pad);

	/**************************/
	/* Open current sub-image */
	/**************************/
	TASImage *img = new TASImage(filename.c_str());
	if (!img)
	{
	  printf("Could not open image %s.\nTerminating program...\n", filename.c_str());
	  exit(1);
	}
	img->SetConstRatio(kFALSE);
	img->SetImageQuality(TAttImage::kImgBest);

	/*****************************/
	/* Correct image orientation */
	/*****************************/
	if(selenographic)
	{
	  if(sub_image_upper_left_longitude > sub_image_upper_right_longitude)
	  {
	    if(sub_image_upper_left_latitude < sub_image_lower_left_latitude)
	      img->Flip(180);
	    else	    
	      img->Mirror(true);
	  }
	}
	else
	{
	  if(sub_image_upper_left_x > sub_image_upper_right_x)
	  {
	    if(sub_image_upper_left_y < sub_image_lower_left_y)
	      img->Flip(180);
	    else
	      img->Mirror(true);
	  }
	}
	img->SetEditable(kTRUE);

	/***************************************/
	/* Make overlapping images transparent */
	/***************************************/
	if(incidence_angle_w_max_area == incidence_angles[i])
	{
	  tasimages[0].push_back(img);
	}
	else
	{
	  /*******************/
	  /* Clone sub-image */
	  /*******************/
	  vector <TASImage *> cloned_images(5);
	  for(int k=0; k<5; k++)
	  {
	    buffer = "img_clone_"+to_string(k);
	    cloned_images[k] = (TASImage *)img->Clone(buffer.c_str());
	  }

	  int image_transparency_level = 0;
	  while(image_transparency_level < 5)
	  {
	    /***********************/
	    /* Retrieve ARGB array */
	    /***********************/
	    unsigned int *argb = (unsigned int *)cloned_images[image_transparency_level]->GetArgbArray();
	    int w = cloned_images[image_transparency_level]->GetWidth();
	    int h = cloned_images[image_transparency_level]->GetHeight();
	    
	    /************************************/
	    /* Scan all pixels in current image */
	    /* and make all colors transparent. */
	    /************************************/
	    for(int k=0; k<h; k++)
	    {
	      for(int l=0; l<w; l++)
	      {
		int idx = k*w + l;
		
		/**************************/
		/* RGB part of ARGB color */
		/**************************/
		unsigned int col = argb[idx] & 0xffffff;
		
		/******************************/
		/* Alpha channel modification */
		/******************************/
		switch(image_transparency_level)
		{
		  case 0: argb[idx] = 0x00000000 + col; // 100 percent transparency
		    break;
		  case 1: argb[idx] = 0x3F000000 + col; // 75 percent transparency
		    break;
		  case 2: argb[idx] = 0x7F000000 + col; // 50 percent transparency
		    break;
		  case 3: argb[idx] = 0xBF000000 + col; // 25 percent transparency
		    break;
		  case 4: argb[idx] = 0xFF000000 + col; // 0 percent transparency
		    break;
		}
	      }
	    }
	    
	    /********************/
	    /* Record sub-image */
	    /********************/
	    tasimages[image_transparency_level+1].push_back(cloned_images[image_transparency_level]);

	    /**********************************/
	    /* Update image tranparency level */
	    /**********************************/
	    image_transparency_level++;
	  }
	}
      }
    }
  }

  /********************/
  /* Speed up drawing */
  /********************/
  gStyle->SetCanvasPreferGL(kTRUE);

  /*************************************/
  /* Remove past instance of animation */
  /*************************************/
  filename = "Graphic.gif";
  remove(filename.c_str());

  /*************************/
  /* Draw background image */
  /*************************/
  for(int j=0; j<(int)pads[0].size(); j++)
  {     
    pads[0][j]->Draw();
    pads[0][j]->cd();
    tasimages[0][j]->Draw("X");
    can->cd();
  }

  /*****************/
  /* Overplot pads */
  /*****************/
  for(int j=0; j<(int)pads[1].size(); j++)
  {
    pads[1][j]->Draw();
    can->cd();
  }

  /*********************/
  /* Save plot to file */
  /*********************/
  delay = "100";
  filename = "Graphic.gif+"+delay;
  can->Print(filename.c_str());

  /******************************/
  /* Overplot foreground images */
  /******************************/
  int imagenumber = 1;
  while(imagenumber < (int)tasimages.size())
  {
    for(int j=0; j<(int)pads[1].size(); j++)
    {
      pads[1][j]->cd();
      tasimages[imagenumber][j]->Draw("X");
      can->cd();
    }

    /*********************/
    /* Save plot to file */
    /*********************/
    can->Print(filename.c_str());

    /**********************/
    /* Update imagenumber */
    /**********************/
    imagenumber++;
  }

  /*********************/
  /* Save plot to file */
  /*********************/
  filename = "Graphic.gif++";
  can->Print(filename.c_str());

  return;
}

void IncidenceAngleAnalysis_Plot::MasterImage(ImageSets a, bool selenographic)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double dot;
  double lower_left_latitude;
  double lower_left_longitude;
  double lower_left_x;
  double lower_left_y;
  double lower_right_latitude;
  double lower_right_longitude;
  double lower_right_x;
  double lower_right_y;
  double spacing;
  double upper_left_latitude;
  double upper_left_longitude;
  double upper_left_x;
  double upper_left_y;
  double upper_right_latitude;
  double upper_right_longitude;
  double upper_right_x;
  double upper_right_y;
  double x_high;
  double x_low;
  double x_reference_point;
  double y_high;
  double y_low;
  double y_reference_point;
  int canheight;
  int canwidth;
  int n;
  string buffer;
  string filename;
  string image_name;
  TCanvas *can;
  TPolyLine *plot;
  TEllipse *el;
  TH1F *h1;
  TLegend *leg;
  vector <double> X_Coords;
  vector <double> Y_Coords;
    
  /******************************/
  /* Retrieve image information */
  /******************************/
  image_name = a.GetName();
  lower_left_latitude = a.GetLower_left_latitude();
  lower_left_longitude = a.GetLower_left_longitude();
  lower_left_x = a.GetLower_left_x();
  lower_left_y = a.GetLower_left_y();
  lower_right_latitude = a.GetLower_right_latitude();
  lower_right_longitude = a.GetLower_right_longitude();
  lower_right_x = a.GetLower_right_x();
  lower_right_y = a.GetLower_right_y();
  upper_left_latitude = a.GetUpper_left_latitude();
  upper_left_longitude = a.GetUpper_left_longitude();
  upper_left_x = a.GetUpper_left_x();
  upper_left_y = a.GetUpper_left_y();
  upper_right_latitude = a.GetUpper_right_latitude();
  upper_right_longitude = a.GetUpper_right_longitude();
  upper_right_x = a.GetUpper_right_x();
  upper_right_y = a.GetUpper_right_y();
  
  /*********************/
  /* Initialize Canvas */
  /*********************/
  canheight = 1200;
  canwidth = 800;
  can = new TCanvas("Canvas", "", canheight, canwidth);
  can->SetGridx();
  can->SetGridy();

  /*************/
  /* Draw axes */
  /*************/
  if(selenographic)
  {
    buffer = image_name+"; X [Degree]; Y [Degree]";
    x_high = a.GetMaximum_longitude();
    x_low = a.GetMinimum_longitude();
    x_reference_point = upper_left_longitude;
    y_high = a.GetMaximum_latitude();
    y_low = a.GetMinimum_latitude();
    y_reference_point = upper_left_latitude;
    spacing = 1E-2;
  }
  else
  {
    buffer = image_name+"; X [m]; Y [m]";
    x_high = a.GetMaximum_x();
    x_low = a.GetMinimum_x();
    x_reference_point = upper_left_x;
    y_high = a.GetMaximum_y();
    y_low = a.GetMinimum_y();
    y_reference_point = upper_left_y;
    spacing = 1E3;
  }
  h1 = can->DrawFrame(x_low-spacing, y_low-spacing, x_high+spacing, y_high+spacing, buffer.c_str());
  h1->GetYaxis()->SetNdivisions(5);
  h1->GetXaxis()->SetNdivisions(5);
    
  /**************/
  /* Plot image */
  /**************/
  if(selenographic)
  {
    X_Coords.push_back(upper_left_longitude);
    Y_Coords.push_back(upper_left_latitude);
    X_Coords.push_back(upper_right_longitude);
    Y_Coords.push_back(upper_right_latitude);    
    X_Coords.push_back(lower_right_longitude);
    Y_Coords.push_back(lower_right_latitude);
    X_Coords.push_back(lower_left_longitude);
    Y_Coords.push_back(lower_left_latitude);
    X_Coords.push_back(upper_left_longitude);
    Y_Coords.push_back(upper_left_latitude);
    dot = 0.01*abs(upper_left_longitude-upper_right_longitude);
  }
  else
  {
    X_Coords.push_back(upper_left_x);
    Y_Coords.push_back(upper_left_y);
    X_Coords.push_back(upper_right_x);
    Y_Coords.push_back(upper_right_y);
    X_Coords.push_back(lower_right_x);
    Y_Coords.push_back(lower_right_y);
    X_Coords.push_back(lower_left_x);
    Y_Coords.push_back(lower_left_y);
    X_Coords.push_back(upper_left_x);
    Y_Coords.push_back(upper_left_y);
    dot = 0.01*abs(upper_left_x-upper_right_x);
  }
  n = (int)X_Coords.size();
  plot = new TPolyLine(n, X_Coords.data(), Y_Coords.data());
  plot->SetLineColor(kGreen);
  plot->SetLineWidth(2);
  plot->Draw();
  gPad->RedrawAxis();

  /***********************/
  /* Plot defined origin */
  /***********************/
  el = new TEllipse(x_reference_point, y_reference_point, dot);
  el->SetFillColorAlpha(kRed, 0.50);
  el->SetFillStyle(4050);
  el->SetLineColor(kRed);
  el->Draw();

  /**********/
  /* Legend */
  /**********/
  leg = new TLegend(0.7,0.7,0.9,0.9);
  //leg->SetHeader("","C"); // option "C" allows to center the header
  buffer = "Image: "+image_name;
  leg->AddEntry(plot, buffer.c_str(), "f");
  leg->AddEntry(el, "Image Origin", "f");
  leg->Draw();

  /*********************/
  /* Save plot to file */
  /*********************/
  filename = image_name+"_Graphic.ps";
  can->SaveAs(filename.c_str());

  /***********************************/
  /* Free memory reserved for canvas */
  /***********************************/
  delete can;
  delete plot;
  delete el;
  delete h1;
  delete leg;
}

void IncidenceAngleAnalysis_Plot::MasterImages(ImageSets a, ImageSets b, bool selenographic)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double dot;
  double lower_left_latitude;
  double lower_left_longitude;
  double lower_left_x;
  double lower_left_y;
  double lower_right_latitude;
  double lower_right_longitude;
  double lower_right_x;
  double lower_right_y;
  double spacing;
  double upper_left_latitude;
  double upper_left_longitude;
  double upper_left_x;
  double upper_left_y;
  double upper_right_latitude;
  double upper_right_longitude;
  double upper_right_x;
  double upper_right_y;
  double x_high;
  double x_low;
  double x_reference_point;
  double y_high;
  double y_low;
  double y_reference_point;
  int canheight;
  int canwidth;
  int n;
  string buffer;
  string filename;
  string image_name;
  TCanvas *can;
  TEllipse *el;
  TH1F *h1;
  TLegend *leg;
  TPolyLine *plot;
  vector <ImageSets> imagesets;

  /**********************/
  /* Record image names */
  /**********************/
  imagesets.push_back(a);
  imagesets.push_back(b);

  /*********************/
  /* Initialize Canvas */
  /*********************/
  canheight = 1200;
  canwidth = 800;
  can = new TCanvas("Canvas", "", canheight, canwidth);
  can->SetGridx();
  can->SetGridy();

  /*************/
  /* Draw axes */
  /*************/
  if(selenographic)
  {
    buffer = image_name+"; X [Degree]; Y [Degree]";
    x_high = Max(a.GetMaximum_longitude(), b.GetMaximum_longitude());
    x_low = Min(a.GetMinimum_longitude(), b.GetMinimum_longitude());
    y_high = Max(a.GetMaximum_latitude(), b.GetMaximum_latitude());
    y_low = Min(a.GetMinimum_latitude(), b.GetMinimum_latitude());
    spacing = 1E-2;
  }
  else
  {
    buffer = image_name+"; X [m]; Y [m]";
    x_high = Max(a.GetMaximum_x(), b.GetMaximum_x());
    x_low = Min(a.GetMinimum_x(), b.GetMinimum_x());
    y_high = Max(a.GetMaximum_y(), b.GetMaximum_y());
    y_low = Min(a.GetMinimum_y(), b.GetMinimum_y());
    spacing = 1E3;
  }
  h1 = can->DrawFrame(x_low-spacing, y_low-spacing, x_high+spacing, y_high+spacing, buffer.c_str());
  h1->GetYaxis()->SetNdivisions(5);
  h1->GetXaxis()->SetNdivisions(5);

  /**********/
  /* Legend */
  /**********/
  leg = new TLegend(0.7,0.7,0.9,0.9);

  for(int i=0; i<(int)imagesets.size(); i++)
  {
    /******************************/
    /* Retrieve image information */
    /******************************/
    image_name = imagesets[i].GetName();
    lower_left_latitude = imagesets[i].GetLower_left_latitude();
    lower_left_longitude = imagesets[i].GetLower_left_longitude();
    lower_left_x = imagesets[i].GetLower_left_x();
    lower_left_y = imagesets[i].GetLower_left_y();
    lower_right_latitude = imagesets[i].GetLower_right_latitude();
    lower_right_longitude = imagesets[i].GetLower_right_longitude();
    lower_right_x = imagesets[i].GetLower_right_x();
    lower_right_y = imagesets[i].GetLower_right_y();
    upper_left_latitude = imagesets[i].GetUpper_left_latitude();
    upper_left_longitude = imagesets[i].GetUpper_left_longitude();
    upper_left_x = imagesets[i].GetUpper_left_x();
    upper_left_y = imagesets[i].GetUpper_left_y();
    upper_right_latitude = imagesets[i].GetUpper_right_latitude();
    upper_right_longitude = imagesets[i].GetUpper_right_longitude();
    upper_right_x = imagesets[i].GetUpper_right_x();
    upper_right_y = imagesets[i].GetUpper_right_y();

    /**************/
    /* Plot image */
    /**************/
    vector <double> X_Coords;
    vector <double> Y_Coords;
    if(selenographic)
    {
      X_Coords.push_back(upper_left_longitude);
      Y_Coords.push_back(upper_left_latitude);
      X_Coords.push_back(upper_right_longitude);
      Y_Coords.push_back(upper_right_latitude);    
      X_Coords.push_back(lower_right_longitude);
      Y_Coords.push_back(lower_right_latitude);
      X_Coords.push_back(lower_left_longitude);
      Y_Coords.push_back(lower_left_latitude);
      X_Coords.push_back(upper_left_longitude);
      Y_Coords.push_back(upper_left_latitude);
      x_reference_point = upper_left_longitude;
      y_reference_point = upper_left_latitude;
      dot = 0.01*abs(upper_left_longitude-upper_right_longitude);
    }
    else
    {
      X_Coords.push_back(upper_left_x);
      Y_Coords.push_back(upper_left_y);
      X_Coords.push_back(upper_right_x);
      Y_Coords.push_back(upper_right_y);
      X_Coords.push_back(lower_right_x);
      Y_Coords.push_back(lower_right_y);
      X_Coords.push_back(lower_left_x);
      Y_Coords.push_back(lower_left_y);
      X_Coords.push_back(upper_left_x);
      Y_Coords.push_back(upper_left_y);
      x_reference_point = upper_left_x;
      y_reference_point = upper_left_y;
      dot = 0.01*abs(upper_left_x-upper_right_x);
    }
    n = (int)X_Coords.size();
    plot = new TPolyLine(n, X_Coords.data(), Y_Coords.data());
    if(i == 0)
    {
      plot->SetLineColor(kGreen);
    }
    else
    {  
      plot->SetLineColor(kBlue);
    }
    plot->SetLineWidth(2);
    plot->Draw();

    /***********************/
    /* Plot defined origin */
    /***********************/
    el = new TEllipse(x_reference_point, y_reference_point, dot);
    if(i == 0)
    {
      el->SetFillColorAlpha(kGreen, 0.50);
      el->SetLineColor(kGreen);
    }
    else
    {
      el->SetFillColorAlpha(kBlue, 0.50);
      el->SetLineColor(kBlue);
    }
    el->SetFillStyle(4050);
    el->Draw();

    /**********************/
    /* Add legend entries */
    /**********************/
    buffer = "Image: "+image_name;
    leg->AddEntry(plot, buffer.c_str(), "f");
    leg->AddEntry(el, "Image Origin", "f");
    leg->Draw();
  }

  /*********************/
  /* Save plot to file */
  /*********************/
  filename = a.GetName()+"_vs_"+b.GetName()+"_Graphic.ps";
  can->SaveAs(filename.c_str());
    
  /************************/
  /* Free reserved memory */
  /************************/
  delete can;
  delete el;
  delete h1;
  delete leg;
  delete plot;
}

void IncidenceAngleAnalysis_Plot::MasterImage_w_SubImages(ImageSets a, vector <Images> &b, bool selenographic)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double dot;
  double lower_left_latitude;
  double lower_left_longitude;
  double lower_left_x;
  double lower_left_y;
  double lower_right_latitude;
  double lower_right_longitude;
  double lower_right_x;
  double lower_right_y;
  double spacing;
  double upper_left_latitude;
  double upper_left_longitude;
  double upper_left_x;
  double upper_left_y;
  double upper_right_latitude;
  double upper_right_longitude;
  double upper_right_x;
  double upper_right_y;
  double x_high;
  double x_low;
  double x_reference_point;
  double y_high;
  double y_low;
  double y_reference_point;
  int canheight;
  int canwidth;
  int first_index;
  int last_index;
  int master_image_id;
  int n;
  int scale;
  int value;
  string buffer;
  string field;
  string filename;
  string master_image_name;
  TCanvas *can;
  TPolyLine *plot;
  TEllipse *el;
  TH1F *h1;
  TLegend *leg;
  vector <double> X_Coords;
  vector <double> Y_Coords;
  
  /******************************/
  /* Retrieve image information */
  /******************************/
  master_image_name = a.GetName();
  master_image_id = a.GetId();
  lower_left_latitude = a.GetLower_left_latitude();
  lower_left_longitude = a.GetLower_left_longitude();
  lower_left_x = a.GetLower_left_x();
  lower_left_y = a.GetLower_left_y();
  lower_right_latitude = a.GetLower_right_latitude();
  lower_right_longitude = a.GetLower_right_longitude();
  lower_right_x = a.GetLower_right_x();
  lower_right_y = a.GetLower_right_y();
  upper_left_latitude = a.GetUpper_left_latitude();
  upper_left_longitude = a.GetUpper_left_longitude();
  upper_left_x = a.GetUpper_left_x();
  upper_left_y = a.GetUpper_left_y();
  upper_right_latitude = a.GetUpper_right_latitude();
  upper_right_longitude = a.GetUpper_right_longitude();
  upper_right_x = a.GetUpper_right_x();
  upper_right_y = a.GetUpper_right_y();

  /**************************/
  /* Sort images (b) vector */
  /**************************/
  field = "image_set_id";
  SortData <Images> sortimages(b, field);
  sortimages.arrange();
  b = sortimages.GetData();

  /***********************************************************************/
  /* Find first and last occurrence of image_set_id in images (b) vector */
  /***********************************************************************/
  n = (int)b.size();
  value = master_image_id;
  first_index = SearchData<Images>::FirstOccurence(b, 0, n-1, field, &value);
  last_index = SearchData<Images>::LastOccurence(b, 0, n-1, field, &value);

  /*****************************/
  /* Boundary for master image */
  /*****************************/
  if(selenographic)
  {
    X_Coords.push_back(upper_left_longitude);
    Y_Coords.push_back(upper_left_latitude);
    X_Coords.push_back(upper_right_longitude);
    Y_Coords.push_back(upper_right_latitude);    
    X_Coords.push_back(lower_right_longitude);
    Y_Coords.push_back(lower_right_latitude);
    X_Coords.push_back(lower_left_longitude);
    Y_Coords.push_back(lower_left_latitude);
    X_Coords.push_back(upper_left_longitude);
    Y_Coords.push_back(upper_left_latitude);
    dot = 0.01*abs(upper_left_longitude-upper_right_longitude);
  }
  else
  {
    X_Coords.push_back(upper_left_x);
    Y_Coords.push_back(upper_left_y);
    X_Coords.push_back(upper_right_x);
    Y_Coords.push_back(upper_right_y);
    X_Coords.push_back(lower_right_x);
    Y_Coords.push_back(lower_right_y);
    X_Coords.push_back(lower_left_x);
    Y_Coords.push_back(lower_left_y);
    X_Coords.push_back(upper_left_x);
    Y_Coords.push_back(upper_left_y);
    dot = 0.01*abs(upper_left_x-upper_right_x);
  }
  n = (int)X_Coords.size();
  plot = new TPolyLine(n, X_Coords.data(), Y_Coords.data());
  plot->SetLineColor(kGreen);
  plot->SetLineWidth(2);
  
  /*****************/
  /* Axes settings */
  /*****************/
  if(selenographic)
  {
    buffer = master_image_name+"; X [Degree]; Y [Degree]";
    x_high = a.GetMaximum_longitude();
    x_low = a.GetMinimum_longitude();
    x_reference_point = upper_left_longitude;
    y_high = a.GetMaximum_latitude();
    y_low = a.GetMinimum_latitude();
    y_reference_point = upper_left_latitude;
    spacing = 1E-2;
  }
  else
  {
    buffer = master_image_name+"; X [m]; Y [m]";
    x_high = a.GetMaximum_x();
    x_low = a.GetMinimum_x();
    x_reference_point = upper_left_x;
    y_high = a.GetMaximum_y();
    y_low = a.GetMinimum_y();
    y_reference_point = upper_left_y;
    spacing = 1E3;
  }
  
  scale = 0;
  while(scale < 3)
  {
    /*********************/
    /* Initialize Canvas */
    /*********************/
    canheight = 1200;
    canwidth = 800;
    can = new TCanvas("Canvas", "", canheight, canwidth);
    can->SetGridx();
    can->SetGridy();

    /**************/
    /* Draw frame */
    /**************/
    h1 = can->DrawFrame(x_low-spacing, y_low-spacing, x_high+spacing, y_high+spacing, buffer.c_str());
    h1->GetYaxis()->SetNdivisions(5);
    h1->GetXaxis()->SetNdivisions(5);

    /*********************/
    /* Plot master image */
    /*********************/
    plot->Draw();
    //gPad->RedrawAxis();

    /***************************************************************************/
    /* Iterate through images (b) vector and plot sub-images for current scale */
    /***************************************************************************/
    TPolyLine *sub_image_plot;
    int counter = 0;
    for(int i=first_index; i<=last_index; i++)
    {
      /*****************************/
      /* Determine sub-image scale */
      /*****************************/
      string sub_image_name = b[i].GetName();
      int p1 = sub_image_name.find("_")+1;
      int scl = stoi(sub_image_name.substr(p1, 1), nullptr);
      if(scl == scale)
      {
	/******************************************/
	/* Retrieve bounding region for sub-image */
	/******************************************/
	double sub_image_lower_left_latitude = b[i].GetLower_left_latitude();
	double sub_image_lower_left_longitude = b[i].GetLower_left_longitude();
	double sub_image_lower_left_x = b[i].GetLower_left_x();
	double sub_image_lower_left_y = b[i].GetLower_left_y();
	double sub_image_lower_right_latitude = b[i].GetLower_right_latitude();
	double sub_image_lower_right_longitude = b[i].GetLower_right_longitude();
	double sub_image_lower_right_x = b[i].GetLower_right_x();
	double sub_image_lower_right_y = b[i].GetLower_right_y();
	double sub_image_upper_left_latitude = b[i].GetUpper_left_latitude();
	double sub_image_upper_left_longitude = b[i].GetUpper_left_longitude();
	double sub_image_upper_left_x = b[i].GetUpper_left_x();
	double sub_image_upper_left_y = b[i].GetUpper_left_y();
	double sub_image_upper_right_latitude = b[i].GetUpper_right_latitude();
	double sub_image_upper_right_longitude = b[i].GetUpper_right_longitude();
	double sub_image_upper_right_x = b[i].GetUpper_right_x();
	double sub_image_upper_right_y = b[i].GetUpper_right_y();

	/*****************************************************/
	/* Store wanted bounding region points for sub-image */
	/*****************************************************/
	vector <double> sub_image_x_coords;
	vector <double> sub_image_y_coords;
	if(selenographic)
	{
	  sub_image_x_coords.push_back(sub_image_upper_left_longitude);
	  sub_image_y_coords.push_back(sub_image_upper_left_latitude);
	  sub_image_x_coords.push_back(sub_image_upper_right_longitude);
	  sub_image_y_coords.push_back(sub_image_upper_right_latitude);    
	  sub_image_x_coords.push_back(sub_image_lower_right_longitude);
	  sub_image_y_coords.push_back(sub_image_lower_right_latitude);
	  sub_image_x_coords.push_back(sub_image_lower_left_longitude);
	  sub_image_y_coords.push_back(sub_image_lower_left_latitude);
	  sub_image_x_coords.push_back(sub_image_upper_left_longitude);
	  sub_image_y_coords.push_back(sub_image_upper_left_latitude);
	}
	else
	{
	  sub_image_x_coords.push_back(sub_image_upper_left_x);
	  sub_image_y_coords.push_back(sub_image_upper_left_y);
	  sub_image_x_coords.push_back(sub_image_upper_right_x);
	  sub_image_y_coords.push_back(sub_image_upper_right_y);
	  sub_image_x_coords.push_back(sub_image_lower_right_x);
	  sub_image_y_coords.push_back(sub_image_lower_right_y);
	  sub_image_x_coords.push_back(sub_image_lower_left_x);
	  sub_image_y_coords.push_back(sub_image_lower_left_y);
	  sub_image_x_coords.push_back(sub_image_upper_left_x);
	  sub_image_y_coords.push_back(sub_image_upper_left_y);
	}

	/**************************/
	/* Sub-image slice number */
	/**************************/
	int p2 = sub_image_name.rfind("_")+1;
	int p3 = sub_image_name.find(".")+1;
	int length = p3-p2;
	int image_slice_number = stoi(sub_image_name.substr(p2, length), nullptr);
	double x = (sub_image_x_coords[0]+sub_image_x_coords[1])/2.;
	double y = (sub_image_y_coords[1]+sub_image_y_coords[3])/2.0001;
	TLatex *l = new TLatex(x, y, Form("%d", image_slice_number));
	l->SetTextSize(0.025);
	l->SetTextFont(42);
	l->SetTextAlign(21);
	l->Draw();

	/******************/
	/* Plot sub-image */
	/******************/
	n = (int)sub_image_x_coords.size();
	sub_image_plot = new TPolyLine(n, sub_image_x_coords.data(), sub_image_y_coords.data());
	sub_image_plot->SetLineColor(kCyan);
	sub_image_plot->SetLineWidth(2);
	sub_image_plot->Draw();
	counter++;
      }
    }
    //cout << "Scale level " << scale << " has " << counter << " number of images." << endl;

    /*****************************************************************/
    /* If no images exists for current scale, continue to next scale */
    /*****************************************************************/
    if(counter == 0)
    {
      /***********************************/
      /* Free memory reserved for canvas */
      /***********************************/
      delete can;
      
      /************************/
      /* Increase scale level */
      /************************/
      scale++;

      continue;
    }

    /***********************/
    /* Plot defined origin */
    /***********************/
    el = new TEllipse(x_reference_point, y_reference_point, dot);
    el->SetFillColorAlpha(kRed, 0.50);
    el->SetFillStyle(4050);
    el->SetLineColor(kRed);
    el->Draw();

    /**********/
    /* Legend */
    /**********/
    leg = new TLegend(0.7,0.7,0.9,0.9);
    //leg->SetHeader("","C"); // option "C" allows to center the header
    buffer = "Image: "+master_image_name;
    leg->AddEntry(plot, buffer.c_str(), "f");
    leg->AddEntry(sub_image_plot, "Sub-images", "f");
    leg->AddEntry(el, "Image Origin", "f");
    leg->Draw();

    /*********************/
    /* Save plot to file */
    /*********************/
    filename = master_image_name+"_"+to_string(scale)+"_Graphic.ps";
    can->SaveAs(filename.c_str());

    /***********************************/
    /* Free memory reserved for canvas */
    /***********************************/
    delete el;
    delete leg;
    delete can;
    delete sub_image_plot;

    /************************/
    /* Increase scale level */
    /************************/
    scale++;
  }

  /*********************************/
  /* Free memory reserved for plot */
  /*********************************/
  delete can;
  delete plot;
  delete el;
  delete h1;
  delete leg;

  return;
}

void IncidenceAngleAnalysis_Plot::MasterImages_w_OverlapData(double incidence_angle_1, double incidence_angle_2, vector <IncidenceAngles> &IA, vector <ImageSets> &imagesets, vector <OverlappedImages> &OI, vector <Marks> &marks)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double incidence_angle_sum;
  double spacing;
  double x_high;
  double x_low;
  double y_high;
  double y_low;
  int canheight;
  int canwidth;
  int n;
  set < pair <double, double> > point;
  string buffer;
  string field;
  string filename;
  TCanvas *can;
  TH1F *h1;
  TLegend *leg;
  vector <double> incidence_angles(2, 0.0);
  vector <double> master_image_area(3, 0.0);
  vector <enum EColor> colors;
  vector <string> master_image_names;
  vector <TPolyLine *> plot;
  vector <TEllipse *> el;
  vector < vector <double> > Polygon_Overlap(4, vector <double> (2));

  /*************************************/
  /* Calculate sum of incidence angles */
  /*************************************/
  incidence_angle_sum = incidence_angle_1+incidence_angle_2;
  
  /**************************************/
  /* Store incidence angles in a vector */
  /**************************************/
  incidence_angles[0] = incidence_angle_1;
  incidence_angles[1] = incidence_angle_2;
  
  /****************************************************************/
  /* Retrieve all master images that match incidence angle values */
  /****************************************************************/
  for(int i=0; i<2; i++)
    for(int j=0; j<(int)IA.size(); j++)
      if(incidence_angles[i] == IA[j].GetIncidence_angle())
	master_image_names.push_back(IA[j].GetName());

  /***************/
  /* Plot colors */
  /***************/
  colors.push_back(kRed);
  colors.push_back(kBlue);
  colors.push_back(kCyan);

  /*********************/
  /* Initialize Canvas */
  /*********************/
  canheight = 1200;
  canwidth = 800;
  can = new TCanvas("Canvas", "", canheight, canwidth);
  can->SetGridx();
  can->SetGridy();

  int counter = 0;
  x_high = 0;
  x_low = std::numeric_limits<double>::infinity();
  y_high = 0;
  y_low = std::numeric_limits<double>::infinity();
  while(counter < (int)master_image_names.size())
  {
    /*************************/
    /* Retrieve master image */
    /*************************/
    field = "name";
    int index = SearchData<ImageSets>::BinarySearch(imagesets, 0, (int)imagesets.size()-1, field, &master_image_names[counter]);
    ImageSets a = imagesets[index];

    /*************************************/
    /* Retrieve master image information */
    /*************************************/
    double lower_left_x = a.GetLower_left_x();
    double lower_left_y = a.GetLower_left_y();
    double lower_right_x = a.GetLower_right_x();
    double lower_right_y = a.GetLower_right_y();
    double upper_left_x = a.GetUpper_left_x();
    double upper_left_y = a.GetUpper_left_y();
    double upper_right_x = a.GetUpper_right_x();
    double upper_right_y = a.GetUpper_right_y(); 
    master_image_area[counter] = a.GetArea();

    /*******************************************/
    /* Determine maximum values for plot frame */
    /*******************************************/
    double xmax;
    double xmin;
    double ymax;
    double ymin;
    if(upper_left_x < upper_right_x)
    {
      xmax = (upper_right_x > lower_right_x) ? upper_right_x : lower_right_x;
      xmin = (upper_left_x < lower_left_x) ? upper_left_x : lower_left_x;
    }
    else
    {
      xmax = (upper_left_x > lower_left_x) ? upper_left_x : lower_left_x;
      xmin = (upper_right_x < lower_right_x) ? upper_right_x : lower_right_x;
    }
    if(upper_left_y < lower_left_y)
    {
      ymax = (lower_left_y > lower_right_y) ? lower_left_y : lower_right_y;
      ymin = (upper_left_y < upper_right_y) ? upper_left_y : upper_right_y;
    }
    else
    {
      ymax = (upper_left_y < upper_right_y) ? upper_left_y : upper_right_y;
      ymin = (lower_left_y > lower_right_y) ? lower_left_y : lower_right_y;
    }
    x_high = (x_high > xmax) ? x_high : xmax;
    x_low = (x_low < xmin) ? x_low : xmin;
    y_high = (y_high > ymax) ? y_high : ymax;
    y_low = (y_low < ymin) ? y_low : ymin;

    /*****************************/
    /* Boundary for master image */
    /*****************************/
    vector <double> X_Coords;
    vector <double> Y_Coords;
    X_Coords.push_back(upper_left_x);
    Y_Coords.push_back(upper_left_y);
    X_Coords.push_back(upper_right_x);
    Y_Coords.push_back(upper_right_y);
    X_Coords.push_back(lower_right_x);
    Y_Coords.push_back(lower_right_y);
    X_Coords.push_back(lower_left_x);
    Y_Coords.push_back(lower_left_y);
    X_Coords.push_back(upper_left_x);
    Y_Coords.push_back(upper_left_y);
    double dot = 0.01*abs(upper_left_x-upper_right_x);

    /*******************/
    /* Initialize plot */
    /*******************/
    n = (int)X_Coords.size();
    plot.push_back(new TPolyLine(n, X_Coords.data(), Y_Coords.data()));

    /*********************/
    /* Initialize origin */
    /*********************/
    el.push_back(new TEllipse(upper_left_x, upper_left_y, dot));

    /******************/
    /* Update counter */
    /******************/
    counter++;
  }

  /**************/
  /* Draw frame */
  /**************/
  spacing = 1.0E3;
  h1 = can->DrawFrame(x_low-spacing, y_low-spacing, x_high+spacing, y_high+spacing);
  h1->GetYaxis()->SetTitle("Y [m]");
  h1->GetXaxis()->SetTitle("X [m]");
  h1->GetYaxis()->CenterTitle();
  h1->GetXaxis()->CenterTitle();
  h1->GetYaxis()->SetNdivisions(10);
  h1->GetXaxis()->SetNdivisions(10);

  /*********************/
  /* Initialize legend */
  /*********************/
  leg = new TLegend(0.7,0.7,0.9,0.9);
  
  /**********************/
  /* Plot master images */
  /**********************/
  for(int i=0; i<(int)plot.size(); i++)
  {
    plot[i]->SetLineColor(colors[i]);
    plot[i]->SetLineWidth(2);
    plot[i]->Draw("L");
  }

  /**************************************/
  /* Plot master image reference points */
  /**************************************/
  for(int i=0; i<(int)el.size(); i++)
  {
    el[i]->SetFillColorAlpha(colors[i], 0.50);
    el[i]->SetFillStyle(4050);
    el[i]->SetLineColor(colors[i]);
    el[i]->Draw();
  }

  for(int i=0; i<(int)master_image_names.size(); i++)
  {
    buffer = "Image: "+master_image_names[i];
    leg->AddEntry(plot[i], buffer.c_str(), "f");
    buffer = "Image "+master_image_names[i]+" origin";
    leg->AddEntry(el[i], buffer.c_str(), "f");
  }
  
  /*********************/
  /* Sort marks vector */
  /*********************/
  field = "image_id";
  SortData <Marks> sortmarks(marks, field);
  sortmarks.arrange();
  marks = sortmarks.GetData();
  
  /****************************/
  /* Draw overlapping regions */
  /****************************/
  double total_area1 = 0;
  int leg_counter = 0;
  for(int i=0; i<(int)OI.size(); i++)
  {
    /*********************************************/
    /* Reject overlapping images whose incidence */
    /* angle sum doesn't match the sum above     */
    /*********************************************/
    if(incidence_angle_sum != OI[i].GetImage1_incidence_angle()+OI[i].GetImage2_incidence_angle())
      continue;

    /*********************/
    /* Image information */
    /*********************/
    int image1_id = OI[i].GetImage1_id();
    int image2_id = OI[i].GetImage2_id();
    
    /****************************************/
    /* Reject moon_mappers_tutorial_4 image */
    /****************************************/
    if((image1_id == 60639) || (image2_id == 60639))
      continue;
    
    /******************/
    /* Overlap region */
    /******************/
    Polygon_Overlap[0][0] = OI[i].GetOverlap_upper_left_x();
    Polygon_Overlap[0][1] = OI[i].GetOverlap_upper_left_y();
    Polygon_Overlap[1][0] = OI[i].GetOverlap_upper_right_x();
    Polygon_Overlap[1][1] = OI[i].GetOverlap_upper_right_y();
    Polygon_Overlap[2][0] = OI[i].GetOverlap_lower_right_x();
    Polygon_Overlap[2][1] = OI[i].GetOverlap_lower_right_y();
    Polygon_Overlap[3][0] = OI[i].GetOverlap_lower_left_x();
    Polygon_Overlap[3][1] = OI[i].GetOverlap_lower_left_y();
    
    /************************/
    /* Plotting information */
    /************************/
    vector <double> Polygon_Overlap_X_Coords;
    vector <double> Polygon_Overlap_Y_Coords;
    Polygon_Overlap_X_Coords.push_back(OI[i].GetOverlap_upper_left_x());
    Polygon_Overlap_Y_Coords.push_back(OI[i].GetOverlap_upper_left_y());
    Polygon_Overlap_X_Coords.push_back(OI[i].GetOverlap_upper_right_x());
    Polygon_Overlap_Y_Coords.push_back(OI[i].GetOverlap_upper_right_y());
    Polygon_Overlap_X_Coords.push_back(OI[i].GetOverlap_lower_right_x());
    Polygon_Overlap_Y_Coords.push_back(OI[i].GetOverlap_lower_right_y());
    Polygon_Overlap_X_Coords.push_back(OI[i].GetOverlap_lower_left_x());
    Polygon_Overlap_Y_Coords.push_back(OI[i].GetOverlap_lower_left_y());
    Polygon_Overlap_X_Coords.push_back(OI[i].GetOverlap_upper_left_x());
    Polygon_Overlap_Y_Coords.push_back(OI[i].GetOverlap_upper_left_y());
    
    /*********************************************************************/
    /* Isolate marks that are associated with current overlapping images */
    /*********************************************************************/
    n = (int)marks.size();
    int index1 = SearchData<Marks>::FirstOccurence(marks, 0, n-1, field, &image1_id);
    int index2 = SearchData<Marks>::LastOccurence(marks, 0, n-1, field, &image1_id);

    /*************************************************************************/
    /* Determine allowed marks are in overlap region and plot overlap region */
    /*************************************************************************/
    TPolyLine *plot_overlap;
    bool skip = false;
    bool enter = false;
    for(int j=index1; j<index2; j++)
    {
      double x = marks[j].GetPhysical_x();
      double y = marks[j].GetPhysical_y();
      pair <double, double> entry(x, y);
      if(point.find(entry) == point.end())
      {
	if(Utilities::is_PointContained(x, y, Polygon_Overlap))
	{
	  point.insert(entry);
	  n = (int)Polygon_Overlap_X_Coords.size();
	  plot_overlap = new TPolyLine(n, Polygon_Overlap_X_Coords.data(), Polygon_Overlap_Y_Coords.data());
	  skip = true;
	  enter = true;
	  break;
	}
      }
    }

    if(!skip)
    {
      /*********************************************************************/
      /* Isolate marks that are associated with current overlapping images */
      /*********************************************************************/
      n = (int)marks.size();
      index1 = SearchData<Marks>::FirstOccurence(marks, 0, n-1, field, &image2_id);
      index2 = SearchData<Marks>::LastOccurence(marks, 0, n-1, field, &image2_id);

      /*************************************************************************/
      /* Determine allowed marks are in overlap region and plot overlap region */
      /*************************************************************************/
      for(int j=index1; j<index2; j++)
      {
	double x = marks[j].GetPhysical_x();
	double y = marks[j].GetPhysical_y();
	pair <double, double> entry(x, y);
	if(point.find(entry) == point.end())
	{
	  if(Utilities::is_PointContained(x, y, Polygon_Overlap))
	  {
	    point.insert(entry);
	    n = (int)Polygon_Overlap_X_Coords.size();
	    plot_overlap = new TPolyLine(n, Polygon_Overlap_X_Coords.data(), Polygon_Overlap_Y_Coords.data());
	    enter = true;
	    break;
	  }
	}
      }
    }
    
    /****************************************************************/
    /* Plot overlap region if mark data is being used within region */
    /****************************************************************/
    if(enter)
    {
      total_area1 += OI[i].GetOverlap_area();
      plot_overlap->SetLineColor(kGreen);
      plot_overlap->SetLineWidth(2);
      plot_overlap->SetFillColorAlpha(kGreen, 0.5);
      plot_overlap->Draw("FL");
      if(leg_counter == 0)
	leg->AddEntry(plot_overlap, "Overlap region w/ data", "f");
      leg_counter++;
    }
  }

  /***************************/
  /* Draw all legend entries */
  /***************************/
  leg->Draw();
  
  /*********************/
  /* Save plot to file */
  /*********************/
  filename = "Graphic.ps"; //master_image_name+"_"+to_string(scale)+"_Graphic.ps";
  can->SaveAs(filename.c_str());

  /******************************/
  /* Print total area to screen */
  /******************************/
  total_area1 *= (m2km*m2km);
  for(int i=0; i<(int)master_image_names.size(); i++)
    cout << "Total area of image " << master_image_names[i] << " is: " << to_string(master_image_area[i]*(m2km*m2km)) << " km^2" << endl;
  cout << "Estimated total area by summing the areas of overlap regions: " << to_string(total_area1) << " km^2" << endl;
  cout << "Number of overlap regions: " << leg_counter << endl;

  /***********************************/
  /* Free memory reserved for canvas */
  /***********************************/
  //delete can;
  //delete h1;
  //delete leg;

  return;
}

void IncidenceAngleAnalysis_Plot::PaperPlots(string list)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double canheight;
  double canwidth;
  ifstream InFile;
  int max_elements;
  int n;
  int nelements;
  int nlines;
  int pagenumber;
  int pages;
  int plotnumber;
  int plotsperpage;
  string buffer;
  string canname;
  string filename;
  string format;
  TCanvas *can;
  vector <TGraph *> FIT1;
  vector <TGraph *> FIT2;
  vector <TGraphErrors *> TG1;
  vector <TGraphErrors *> TG2;
  vector <TGraphErrors *> TG3;
  vector <TGraphErrors *> TG4;
  vector <TLegend *> leg;

  /***********************************/
  /* Request memory for data vectors */
  /***********************************/
  n = 2;
  max_elements = 100000;
  vector < vector <string> > datafiles(n, vector <string> (max_elements));
  
  /**************************/
  /* Extract data filenames */
  /**************************/
  format = "%s %s";
  nlines = Readcol::Read(list, format, datafiles[0].data(), datafiles[1].data());
  for(int i = 0; i < (int)datafiles.size(); i++)
    datafiles[i].resize(nlines);
  TransposeVector2D(datafiles);
  
  /*************************************************/
  /* Loop through reduced crater catalog list file */
  /*************************************************/
  for(int i=0; i<(int)datafiles.size(); i++)
  {
    /**********************/
    /* Retrieve datafiles */
    /**********************/
    string datafile1 = datafiles[i][0];
    string datafile2 = datafiles[i][1];
    
    /**************************************************************/
    /* Cumulative Frequency versus Size Distributions and R-Plots */
    /**************************************************************/
    TGraph *F1 = nullptr;
    TGraph *F2 = nullptr;
    TGraphErrors *T1 = nullptr;
    TGraphErrors *T2 = nullptr;
    TGraphErrors *T3 = nullptr;
    TGraphErrors *T4 = nullptr;
    TLegend *L = nullptr;
    CumulativeFrequencySizeDistribution(datafile1, datafile2, &T1, &T2, &F1, &F2, &T3, &T4, &L);

    /********************/
    /* Record plot data */
    /********************/
    TG1.push_back(T1);
    TG2.push_back(T2);
    TG3.push_back(T3);
    TG4.push_back(T4);
    FIT1.push_back(F1);
    FIT2.push_back(F2);
    leg.push_back(L);
  }
  nelements = (int)TG1.size();

  /************************************************/
  /* Determine number of pages and plots per page */
  /************************************************/
  plotsperpage = 0;
  if(nelements%4 == 0)
  {
    pages = nelements/4;
    plotsperpage = 4;
  }
  else if(nelements%3 == 0)
  {
    pages = nelements/3;
    plotsperpage = 3;
  }
  else if(nelements%2 == 0)
  {
    pages = nelements/2;
    plotsperpage = 2;
  }
  else
  {
    pages = nelements;
    plotsperpage = 1;
  }
  pages = nelements;
  plotsperpage = 1;

  pagenumber = 1;
  plotnumber = 0;
  while(pagenumber <= pages)
  {
    /*********************/
    /* Initialize Canvas */
    /*********************/
    canname = "Canvas_"+to_string(pagenumber);    
    can = Plot::CreateCanvas(canname, "");
    can->SetFixedAspectRatio();
    
    /**********************************/
    /* Pad Declaration/Initialization */
    /**********************************/
    vector <TPad *> Pads(plotsperpage);
    for(int i=0; i<plotsperpage; i++)
    {
      int shift_l_l_x = 0;
      int shift_l_l_y = 0;
      int shift_u_r_x = 0;
      int shift_u_r_y = 0;
      int correction_x = 0;
      if(plotsperpage>2)
      {
	shift_l_l_x = i%2;
	shift_u_r_x = (shift_l_l_x == 0) ? 1 : 0;
	if(plotsperpage == 3)
	  correction_x = (i == 2) ? 1 : 0;
      }
      if(plotsperpage>1)
      {
	if(plotsperpage == 2)
	{
	  shift_l_l_y = (i%2 == 0) ? 1 : 0;
	  shift_u_r_y = (shift_l_l_y == 1) ? 0 : 1;
	}
	else
	{
	  shift_l_l_y = (i<2) ? 1 : 0;
	  shift_u_r_y = (shift_l_l_y == 1) ? 0 : 1;
	}
      } 
      string padname = "pad_"+to_string(i+1);
      double px_1 = 0.02+shift_l_l_x*0.50+correction_x*0.25;
      double py_1 = 0.02+shift_l_l_y*0.50;
      double px_2 = 0.98-shift_u_r_x*0.50+correction_x*0.25;
      double py_2 = 0.98-shift_u_r_y*0.50;      
      Pads[i] = new TPad(padname.c_str(), "", px_1, py_1, px_2, py_2, kWhite);
    }
    
    /*************/
    /* Draw Pads */
    /*************/
    for(int i=0; i<(int)Pads.size(); i++)
      Pads[i]->Draw();
    
    /*************/
    /* Plot data */
    /*************/
    for(int i=0; i<(int)Pads.size(); i++)
    { 
      /**********************/
      /* Initialize sub-pad */
      /**********************/
      TVirtualPad *subpad = Pads[i]->cd();
      subpad->Divide(1, 2);

      /********************/
      /* Axes information */
      /********************/
      double axislabelfontsize = 0.05;
      double legendfontsize = 0.05;
      double titlefontsize = 0.05;
      double YAxisMaximum1 = 1.1E3;//1.1*TG1[plotnumber]->GetHistogram()->GetMaximum();
      double YAxisMinimum1 = 8.0E-2;//0.9*TG1[plotnumber]->GetHistogram()->GetMinimum();
      double YAxisMaximum2 = 1.0E0;//1.1*TG3[plotnumber]->GetHistogram()->GetMaximum();
      double YAxisMinimum2 = 1E-3;//0.9*TG3[plotnumber]->GetHistogram()->GetMinimum();
      int textfontstyle = 62;
      string XAxisTitle = TG1[plotnumber]->GetXaxis()->GetTitle();
      string YAxisTitle1 = TG1[plotnumber]->GetYaxis()->GetTitle();
      string YAxisTitle2 = TG3[plotnumber]->GetYaxis()->GetTitle();
      
      subpad->cd(1);
      gPad->SetLogy();
      gPad->SetLogx();
      //gPad->SetGridx();
      //gPad->SetGridy();
      gPad->SetBottomMargin(0.001);
      //gPad->SetLeftMargin(0.01);
      //gPad->SetRightMargin(0.01);
      TG1[plotnumber]->GetYaxis()->SetTitle(YAxisTitle1.c_str());
      TG1[plotnumber]->GetYaxis()->SetTitleSize(titlefontsize);
      TG1[plotnumber]->GetYaxis()->SetTitleFont(textfontstyle);
      TG1[plotnumber]->GetYaxis()->SetTitleOffset(1.0);
      TG1[plotnumber]->GetYaxis()->CenterTitle();
      TG1[plotnumber]->GetYaxis()->SetLabelSize(axislabelfontsize);
      TG1[plotnumber]->GetYaxis()->SetLabelFont(textfontstyle);
      TG1[plotnumber]->GetXaxis()->SetLabelSize(axislabelfontsize);
      TG1[plotnumber]->GetXaxis()->SetLabelFont(textfontstyle);
      TG1[plotnumber]->SetMaximum(YAxisMaximum1);
      TG1[plotnumber]->SetMinimum(YAxisMinimum1);
      TG1[plotnumber]->Draw("AP");
      TG2[plotnumber]->Draw("P");
      // FIT1[plotnumber]->Draw("LP");
      // FIT2[plotnumber]->Draw("LP");
      
      subpad->cd(2);
      gPad->SetLogy();
      gPad->SetLogx();
      //gPad->SetGridx();
      //gPad->SetGridy();
      gPad->SetTopMargin(0.001);
      //gPad->SetLeftMargin(0.01);
      //gPad->SetRightMargin(0.01);
      TG3[plotnumber]->GetYaxis()->SetTitle(YAxisTitle2.c_str());
      TG3[plotnumber]->GetYaxis()->SetTitleSize(titlefontsize);
      TG3[plotnumber]->GetYaxis()->SetTitleFont(textfontstyle);
      TG3[plotnumber]->GetYaxis()->SetTitleOffset(1.0);
      TG3[plotnumber]->GetXaxis()->SetTitle(XAxisTitle.c_str());
      TG3[plotnumber]->GetXaxis()->SetTitleSize(titlefontsize);
      TG3[plotnumber]->GetXaxis()->SetTitleFont(textfontstyle);
      TG3[plotnumber]->GetYaxis()->CenterTitle();
      TG3[plotnumber]->GetXaxis()->CenterTitle();
      TG3[plotnumber]->GetYaxis()->SetLabelSize(axislabelfontsize);
      TG3[plotnumber]->GetYaxis()->SetLabelFont(textfontstyle);
      TG3[plotnumber]->GetXaxis()->SetLabelSize(axislabelfontsize);
      TG3[plotnumber]->GetXaxis()->SetLabelFont(textfontstyle);
      TG3[plotnumber]->SetMaximum(YAxisMaximum2);
      TG3[plotnumber]->SetMinimum(YAxisMinimum2);
      TG3[plotnumber]->Draw("AP");
      TG4[plotnumber]->Draw("P");
      
      /**********/
      /* Legend */
      /**********/
      leg[plotnumber]->SetTextSize(legendfontsize);
      leg[plotnumber]->SetTextFont(textfontstyle);
      leg[plotnumber]->Draw();

      /**********************/
      /* Update plot number */
      /**********************/
      plotnumber++;
    }
    
    /*********************/
    /* Save plot to file */
    /*********************/
    can->Update();
    filename = "AllDistributions_"+to_string(pagenumber)+".ps";
    can->SaveAs(filename.c_str());
    
    /**********************/
    /* Update page number */
    /**********************/
    pagenumber++;
  }
  
  /***********************************/
  /* Free memory reserved for canvas */
  /***********************************/
  delete can;
}

void IncidenceAngleAnalysis_Plot::PlotRealMasterImage(string imdir, double incidence_angle, vector <IncidenceAngles> &incidenceangles, vector <ImageSets> &imagesets, vector <Images> &images, double comparison_incidence_angle)
{
  /***************************************/
  /* Declaration of function variable(s) */
  /***************************************/
  double aspectRatio;
  double dvalue;
  double min_x;
  double min_y;
  double x_degree_high;
  double x_degree_low;
  double x_length_high;
  double x_length_low;
  double x_max;
  double x_min;
  double xrange;
  double y_degree_high;
  double y_degree_low;
  double y_length_high;
  double y_length_low;
  double y_max;
  double y_min;
  double yrange;
  EColor selected_color;
  int canheight;
  int canwidth;
  int ivalue;
  int m;
  int n;
  map <double, EColor> comparison_color;
  string axes1;
  string axes2;
  string buffer;
  string field;
  string filename;
  string svalue;
  TCanvas *can;
  TH1F *h1;
  vector <int> comparison_imagesets_ids;
  vector <int> comparison_nimages;
  vector <int> imagesets_ids;
  vector <int> indicies;
  vector <int> nimages;
  vector < vector <bool> > comparison_skip;
  vector < vector <bool> > skip;
  vector < vector <double> > comparison_lower_left_latitude;
  vector < vector <double> > comparison_lower_left_y;
  vector < vector <double> > comparison_maximum_latitude;
  vector < vector <double> > comparison_maximum_longitude;
  vector < vector <double> > comparison_maximum_x;
  vector < vector <double> > comparison_maximum_y;
  vector < vector <double> > comparison_minimum_latitude;
  vector < vector <double> > comparison_minimum_longitude;
  vector < vector <double> > comparison_minimum_x;
  vector < vector <double> > comparison_minimum_y;
  vector < vector <double> > comparison_upper_left_latitude;
  vector < vector <double> > comparison_upper_left_longitude;
  vector < vector <double> > comparison_upper_left_x;
  vector < vector <double> > comparison_upper_left_y;
  vector < vector <double> > comparison_upper_right_longitude;
  vector < vector <double> > comparison_upper_right_x;
  vector < vector <double> > lower_left_latitude;
  vector < vector <double> > lower_left_y;
  vector < vector <double> > maximum_latitude;
  vector < vector <double> > maximum_longitude;
  vector < vector <double> > maximum_x;
  vector < vector <double> > maximum_y;
  vector < vector <double> > minimum_latitude;
  vector < vector <double> > minimum_longitude;
  vector < vector <double> > minimum_x;
  vector < vector <double> > minimum_y;
  vector < vector <double> > upper_left_latitude;
  vector < vector <double> > upper_left_longitude;
  vector < vector <double> > upper_left_x;
  vector < vector <double> > upper_left_y;
  vector < vector <double> > upper_right_longitude;
  vector < vector <double> > upper_right_x;
  vector < vector <int> > comparison_sub_image_ids;
  vector < vector <int> > sub_image_ids;
  vector < vector <TASImage *> > imgs;
  vector < vector <TPad *> > comparison_pads;
  vector < vector <TPad *> > pads;
  vector < vector <string> > comparison_imagenames;
  vector < vector <string> > imagefiles;
  vector < vector <string> > imagenames;
  vector <string> comparison_masterimages;
  vector <string> masterimages;

  /****************************************/
  /* Hardcoded reference incidence angles */
  /****************************************/
  vector <double> selected_angles = {27.50, 38.00, 58.00, 77.50, 83.00};
  
  /*********************/
  /* Comparison colors */
  /*********************/
  comparison_color.insert(pair<double, EColor>(selected_angles[0], kBlue));
  comparison_color.insert(pair<double, EColor>(selected_angles[1], kYellow));
  comparison_color.insert(pair<double, EColor>(selected_angles[2], kRed));
  comparison_color.insert(pair<double, EColor>(selected_angles[3], kGreen));
  comparison_color.insert(pair<double, EColor>(selected_angles[4], kViolet));
  if(comparison_incidence_angle != 0)
    selected_color = comparison_color[comparison_incidence_angle];
  
  /*******************************/
  /* Sort Incidence Angle vector */
  /*******************************/
  field = "incidence_angle";
  SortData <IncidenceAngles> iasort(incidenceangles, field);
  iasort.arrange();
  incidenceangles = iasort.GetData();
  
  /**********************************/
  /* Determine master image name(s) */
  /**********************************/
  n = (int)incidenceangles.size();
  dvalue = incidence_angle;
  indicies.push_back(SearchData<IncidenceAngles>::FirstOccurence(incidenceangles, 0, n-1, field, &dvalue));
  indicies.push_back(SearchData<IncidenceAngles>::LastOccurence(incidenceangles, 0, n-1, field, &dvalue));
  if (indicies.front() == indicies.back())
    masterimages.push_back(incidenceangles[indicies[0]].GetName());
  else
    for (int i = 0; i < (int)indicies.size(); i++)
      masterimages.push_back(incidenceangles[indicies[i]].GetName());
  indicies.clear();

  /*******************************************************/
  /* Determine master image name(s) for comparison image */
  /*******************************************************/
  if(comparison_incidence_angle != 0) {
    dvalue = comparison_incidence_angle;
    indicies.push_back(SearchData<IncidenceAngles>::FirstOccurence(incidenceangles, 0, n-1, field, &dvalue));
    indicies.push_back(SearchData<IncidenceAngles>::LastOccurence(incidenceangles, 0, n-1, field, &dvalue));
    if (indicies.front() == indicies.back())
      comparison_masterimages.push_back(incidenceangles[indicies[0]].GetName());
    else
      for (int i = 0; i < (int)indicies.size(); i++)
	comparison_masterimages.push_back(incidenceangles[indicies[i]].GetName());
    indicies.clear();
  }
  
  /*************************/
  /* Sort imagesets vector */
  /*************************/
  field = "name";
  SortData <ImageSets> imssort(imagesets, field);
  imssort.arrange();
  imagesets = imssort.GetData();
  
  /***********************************************************************/
  /* Determine ids for each master image and estimate image aspect ratio */
  /***********************************************************************/
  n = (int)masterimages.size();
  for (int i = 0; i < n; i++) {
    svalue = masterimages[i];
    indicies.push_back(SearchData<ImageSets>::LastOccurence(imagesets, 0, (int)imagesets.size()-1, field, &svalue));
  }
  double height = 0.;
  double width = 0.;
  for (int i = 0; i < (int)indicies.size(); i++) {
    imagesets_ids.push_back(imagesets[indicies[i]].GetId());
    height = (imagesets[indicies[i]].GetHeight() > height) ? imagesets[indicies[i]].GetHeight() : height;
    width += imagesets[indicies[i]].GetWidth();
  }
  aspectRatio = width/height;
  indicies.clear();  

  /**************************************************/
  /* Determine ids for each comparison master image */
  /**************************************************/
  if(comparison_incidence_angle != 0) {
    for (int i = 0; i < n; i++) {
      svalue = comparison_masterimages[i];
      indicies.push_back(SearchData<ImageSets>::LastOccurence(imagesets, 0, (int)imagesets.size()-1, field, &svalue));
    }
    for (int i = 0; i < (int)indicies.size(); i++)
      comparison_imagesets_ids.push_back(imagesets[indicies[i]].GetId());
    indicies.clear();
  }
  
  /**********************/
  /* Sort images vector */
  /**********************/
  field = "image_set_id";
  SortData <Images> imsort(images, field);
  imsort.arrange();
  images = imsort.GetData();
  
  /*******************************************************************************************/
  /* Determine number of sub-images for each master image (Only using zero scale sub-images) */
  /*******************************************************************************************/
  n = (int)imagesets_ids.size();
  for (int i = 0; i < n; i++) {
    field = "image_set_id";
    ivalue = imagesets_ids[i];
    indicies.push_back(SearchData<Images>::FirstOccurence(images, 0, (int)images.size()-1, field, &ivalue));
    indicies.push_back(SearchData<Images>::LastOccurence(images, 0, (int)images.size()-1, field, &ivalue));

    /*******************/
    /* Copy sub-vector */
    /*******************/
    vector <Images> temp_images(images.begin()+indicies.front(), images.begin()+indicies.back());
    
    /**********************/
    /* Sort images vector */
    /**********************/
    field = "id";
    SortData <Images> temp_imsort(temp_images, field);
    temp_imsort.arrange();
    temp_images = temp_imsort.GetData();

    for (int j = (int)temp_images.size()-1; j >= 0; j--) {
      string imname = temp_images[j].GetName();
      int p1 = imname.find("_")+1;
      int p2 = imname.rfind("_");
      int len = p2-p1;
      int scale = stoi(imname.substr(p1, len));
      if (scale == 0) {
	nimages.push_back(stoi(imname.substr(p2+1))+1);
	break;
      }
    }
    indicies.clear();
    temp_images.clear();
  }

  /******************************************************************************************************/
  /* Determine number of sub-images for each comparison master image (Only using zero scale sub-images) */
  /******************************************************************************************************/
  if(comparison_incidence_angle != 0)
    for (int i = 0; i < n; i++) {
      field = "image_set_id";
      ivalue = comparison_imagesets_ids[i];
      indicies.push_back(SearchData<Images>::FirstOccurence(images, 0, (int)images.size()-1, field, &ivalue));
      indicies.push_back(SearchData<Images>::LastOccurence(images, 0, (int)images.size()-1, field, &ivalue));

      /*******************/
      /* Copy sub-vector */
      /*******************/
      vector <Images> temp_images(images.begin()+indicies.front(), images.begin()+indicies.back());
      
      /**********************/
      /* Sort images vector */
      /**********************/
      field = "id";
      SortData <Images> temp_imsort(temp_images, field);
      temp_imsort.arrange();
      temp_images = temp_imsort.GetData();
      
      for (int j = (int)temp_images.size()-1; j >= 0; j--) {
	string imname = temp_images[j].GetName();
	int p1 = imname.find("_")+1;
	int p2 = imname.rfind("_");
	int len = p2-p1;
	int scale = stoi(imname.substr(p1, len));
	if (scale == 0) {
	  comparison_nimages.push_back(stoi(imname.substr(p2+1))+1);
	  break;
	}
      }
      indicies.clear();
      temp_images.clear();
    }
  
  /*****************************/
  /* Construct sub-image names */
  /*****************************/
  for (int i = 0; i < (int)nimages.size(); i++) {
    vector <string> imfiles;
    vector <string> imnames;
    for (int j = 0; j < nimages[i]; j++) {
      string original_string_number = to_string(j);
      string new_string_number = string(5-original_string_number.length(), '0')+original_string_number;
      string intermediate_dir = "images_"+masterimages[i]+"/";
      imfiles.push_back(imdir+intermediate_dir+masterimages[i]+"_0_"+new_string_number+".png");
      imnames.push_back(masterimages[i]+"_0_"+original_string_number);
    }
    imagefiles.push_back(imfiles);
    imagenames.push_back(imnames);
  }   

  /****************************************/
  /* Construct comparison sub-image names */
  /****************************************/
  if(comparison_incidence_angle != 0)
    for (int i = 0; i < (int)comparison_nimages.size(); i++) {
      vector <string> imnames;
      for (int j = 0; j < comparison_nimages[i]; j++) {
	string original_string_number = to_string(j);
	imnames.push_back(comparison_masterimages[i]+"_0_"+original_string_number);
      }
      comparison_imagenames.push_back(imnames);
    }
  
  /**********************/
  /* Sort images vector */
  /**********************/
  field = "name";
  SortData <Images> sortimages(images, field);
  sortimages.arrange();
  images = sortimages.GetData();
  
  /******************/
  /* Sub-image data */
  /******************/
  m = (int)images.size();
  for (int i = 0; i < (int)imagenames.size(); i++) {
    vector <bool> sk;
    vector <double> llla;
    vector <double> lly;
    vector <double> maxla;
    vector <double> maxlo;
    vector <double> maxx;
    vector <double> maxy;
    vector <double> minla;
    vector <double> minlo;
    vector <double> minx;
    vector <double> miny;    
    vector <double> ulla;
    vector <double> ullo;
    vector <double> ulx;
    vector <double> uly;
    vector <double> urlo;
    vector <double> urx;
    vector <int> sii;
    for (int j = 0; j < (int)imagenames[i].size(); j++) {
      string sub_image_name = imagenames[i][j];
      int sub_image_index = SearchData<Images>::BinarySearch(images, 0, m-1, field, &sub_image_name);
      if (sub_image_index == -1) {
	sk.push_back(true);
	sii.push_back(std::nan("1"));
	llla.push_back(std::nan("1")); // Unit: degree
	lly.push_back(std::nan("1")); // Unit: meter
	ulla.push_back(std::nan("1")); // Unit: degree
	uly.push_back(std::nan("1")); // Unit: meter
	ullo.push_back(std::nan("1")); // Unit: degree
	ulx.push_back(std::nan("1")); // Unit: meter
	urlo.push_back(std::nan("1")); // Unit: degree
	urx.push_back(std::nan("1")); // Unit: meter
	maxla.push_back(std::nan("1")); // Unit: degree
	maxlo.push_back(std::nan("1")); // Unit: degree
	maxx.push_back(std::nan("1")); // Unit: meter
	maxy.push_back(std::nan("1")); // Unit: meter
	minla.push_back(std::nan("1")); // Unit: degree
	minlo.push_back(std::nan("1")); // Unit: degree
	minx.push_back(std::nan("1")); // Unit: meter
	miny.push_back(std::nan("1")); // Unit: meter
	continue;
      }
      sk.push_back(false);
      sii.push_back(images[sub_image_index].GetId());
      llla.push_back(images[sub_image_index].GetLower_left_latitude()); // Unit: degree
      lly.push_back(images[sub_image_index].GetLower_left_y()); // Unit: meter
      ulla.push_back(images[sub_image_index].GetUpper_left_latitude()); // Unit: degree
      uly.push_back(images[sub_image_index].GetUpper_left_y()); // Unit: meter
      ullo.push_back(images[sub_image_index].GetUpper_left_longitude()); // Unit: degree
      ulx.push_back(images[sub_image_index].GetUpper_left_x()); // Unit: meter
      urlo.push_back(images[sub_image_index].GetUpper_right_longitude()); // Unit: degree
      urx.push_back(images[sub_image_index].GetUpper_right_x()); // Unit: meter
      maxla.push_back(images[sub_image_index].GetMaximum_latitude()); // Unit: degree
      maxlo.push_back(images[sub_image_index].GetMaximum_longitude()); // Unit: degree
      maxx.push_back(images[sub_image_index].GetMaximum_x()); // Unit: meter
      maxy.push_back(images[sub_image_index].GetMaximum_y()); // Unit: meter
      minla.push_back(images[sub_image_index].GetMinimum_latitude()); // Unit: degree
      minlo.push_back(images[sub_image_index].GetMinimum_longitude()); // Unit: degree
      minx.push_back(images[sub_image_index].GetMinimum_x()); // Unit: meter
      miny.push_back(images[sub_image_index].GetMinimum_y()); // Unit: meter
    }
    skip.push_back(sk);
    sub_image_ids.push_back(sii);
    lower_left_latitude.push_back(llla); // Unit: degree
    lower_left_y.push_back(lly); // Unit: meter
    upper_left_latitude.push_back(ulla); // Unit: degree
    upper_left_y.push_back(uly); // Unit: meter
    upper_left_longitude.push_back(ullo); // Unit: degree
    upper_left_x.push_back(ulx); // Unit: meter
    upper_right_longitude.push_back(urlo); // Unit: degree
    upper_right_x.push_back(urx); // Unit: meter
    maximum_latitude.push_back(maxla); // Unit: degree
    maximum_longitude.push_back(maxlo); // Unit: degree
    maximum_x.push_back(maxx); // Unit: meter
    maximum_y.push_back(maxy); // Unit: meter
    minimum_latitude.push_back(minla); // Unit: degree
    minimum_longitude.push_back(minlo); // Unit: degree
    minimum_x.push_back(minx); // Unit: meter
    minimum_y.push_back(miny); // Unit: meter
  }

  /*****************************/
  /* Comparison sub-image data */
  /*****************************/
  if(comparison_incidence_angle != 0)
    for (int i = 0; i < (int)comparison_imagenames.size(); i++) {
      vector <bool> sk;
      vector <double> llla;
      vector <double> lly;
      vector <double> maxla;
      vector <double> maxlo;
      vector <double> maxx;
      vector <double> maxy;
      vector <double> minla;
      vector <double> minlo;
      vector <double> minx;
      vector <double> miny;    
      vector <double> ulla;
      vector <double> ullo;
      vector <double> ulx;
      vector <double> uly;
      vector <double> urlo;
      vector <double> urx;
      vector <int> sii;
      for (int j = 0; j < (int)comparison_imagenames[i].size(); j++) {
	string sub_image_name = comparison_imagenames[i][j];
	int sub_image_index = SearchData<Images>::BinarySearch(images, 0, m-1, field, &sub_image_name);
	if (sub_image_index == -1) {
	  sk.push_back(true);
	  sii.push_back(std::nan("1"));
	  llla.push_back(std::nan("1")); // Unit: degree
	  lly.push_back(std::nan("1")); // Unit: meter
	  ulla.push_back(std::nan("1")); // Unit: degree
	  uly.push_back(std::nan("1")); // Unit: meter
	  ullo.push_back(std::nan("1")); // Unit: degree
	  ulx.push_back(std::nan("1")); // Unit: meter
	  urlo.push_back(std::nan("1")); // Unit: degree
	  urx.push_back(std::nan("1")); // Unit: meter
	  maxla.push_back(std::nan("1")); // Unit: degree
	  maxlo.push_back(std::nan("1")); // Unit: degree
	  maxx.push_back(std::nan("1")); // Unit: meter
	  maxy.push_back(std::nan("1")); // Unit: meter
	  minla.push_back(std::nan("1")); // Unit: degree
	  minlo.push_back(std::nan("1")); // Unit: degree
	  minx.push_back(std::nan("1")); // Unit: meter
	  miny.push_back(std::nan("1")); // Unit: meter
	  continue;
	}
	sk.push_back(false);
	sii.push_back(images[sub_image_index].GetId());
	llla.push_back(images[sub_image_index].GetLower_left_latitude()); // Unit: degree
	lly.push_back(images[sub_image_index].GetLower_left_y()); // Unit: meter
	ulla.push_back(images[sub_image_index].GetUpper_left_latitude()); // Unit: degree
	uly.push_back(images[sub_image_index].GetUpper_left_y()); // Unit: meter
	ullo.push_back(images[sub_image_index].GetUpper_left_longitude()); // Unit: degree
	ulx.push_back(images[sub_image_index].GetUpper_left_x()); // Unit: meter
	urlo.push_back(images[sub_image_index].GetUpper_right_longitude()); // Unit: degree
	urx.push_back(images[sub_image_index].GetUpper_right_x()); // Unit: meter
	maxla.push_back(images[sub_image_index].GetMaximum_latitude()); // Unit: degree
	maxlo.push_back(images[sub_image_index].GetMaximum_longitude()); // Unit: degree
	maxx.push_back(images[sub_image_index].GetMaximum_x()); // Unit: meter
	maxy.push_back(images[sub_image_index].GetMaximum_y()); // Unit: meter
	minla.push_back(images[sub_image_index].GetMinimum_latitude()); // Unit: degree
	minlo.push_back(images[sub_image_index].GetMinimum_longitude()); // Unit: degree
	minx.push_back(images[sub_image_index].GetMinimum_x()); // Unit: meter
	miny.push_back(images[sub_image_index].GetMinimum_y()); // Unit: meter
      }
      comparison_skip.push_back(sk);
      comparison_sub_image_ids.push_back(sii);
      comparison_lower_left_latitude.push_back(llla); // Unit: degree
      comparison_lower_left_y.push_back(lly); // Unit: meter
      comparison_upper_left_latitude.push_back(ulla); // Unit: degree
      comparison_upper_left_y.push_back(uly); // Unit: meter
      comparison_upper_left_longitude.push_back(ullo); // Unit: degree
      comparison_upper_left_x.push_back(ulx); // Unit: meter
      comparison_upper_right_longitude.push_back(urlo); // Unit: degree
      comparison_upper_right_x.push_back(urx); // Unit: meter
      comparison_maximum_latitude.push_back(maxla); // Unit: degree
      comparison_maximum_longitude.push_back(maxlo); // Unit: degree
      comparison_maximum_x.push_back(maxx); // Unit: meter
      comparison_maximum_y.push_back(maxy); // Unit: meter
      comparison_minimum_latitude.push_back(minla); // Unit: degree
      comparison_minimum_longitude.push_back(minlo); // Unit: degree
      comparison_minimum_x.push_back(minx); // Unit: meter
      comparison_minimum_y.push_back(miny); // Unit: meter
    }
  
  /************************************/
  /* Determine minimum x and y values */
  /************************************/
  double constant = 1.0E-3;
  min_x = std::numeric_limits<double>::infinity();
  min_y = std::numeric_limits<double>::infinity();  
  for (unsigned i = 0; i < minimum_x.size(); i++) {
    double mx = ArrayMinimum(minimum_x[i].size(), minimum_x[i].data())*constant; // Unit: kilometer
    min_x = (min_x < mx) ? min_x : mx;
    double my = ArrayMinimum(minimum_y[i].size(), minimum_y[i].data())*constant; // Unit: kilometer
    min_y = (min_y < my) ? min_y : my;
  }
  if(comparison_incidence_angle != 0)
   for (unsigned i = 0; i < comparison_minimum_x.size(); i++) {
     double mx = ArrayMinimum(comparison_minimum_x[i].size(), comparison_minimum_x[i].data())*constant; // Unit: kilometer
     min_x = (min_x < mx) ? min_x : mx;
     double my = ArrayMinimum(comparison_minimum_y[i].size(), comparison_minimum_y[i].data())*constant; // Unit: kilometer
     min_y = (min_y < my) ? min_y : my;
   } 
  
  /************************************************/
  /* Make corrections to data with physical units */
  /************************************************/
  for (unsigned i = 0; i < minimum_x.size(); i++) {
    for (unsigned j = 0; j < minimum_x[i].size(); j++) {
      lower_left_y[i][j] *= constant; // Unit: kilometer
      maximum_x[i][j] *= constant; // Unit: kilometer
      minimum_x[i][j] *= constant; // Unit: kilometer
      maximum_y[i][j] *= constant; // Unit: kilometer
      minimum_y[i][j] *= constant; // Unit: kilometer
      upper_left_y[i][j] *= constant; // Unit: kilometer
      upper_left_x[i][j] *= constant; // Unit: kilometer
      upper_right_x[i][j] *= constant; // Unit: kilometer
      lower_left_y[i][j] -= min_y; // Applying y-offset
      maximum_x[i][j] -= min_x; // Applying x-offset
      minimum_x[i][j] -= min_x; // Applying x-offset
      maximum_y[i][j] -= min_y; // Applying y-offset
      minimum_y[i][j] -= min_y; // Applying y-offset
      upper_left_y[i][j] -= min_y; // Applying y-offset
      upper_left_x[i][j] -= min_x; // Applying x-offset
      upper_right_x[i][j] -= min_x; // Applying x-offset
    }
  }

  /***********************************************************/
  /* Make corrections to comparison data with physical units */
  /***********************************************************/
  if(comparison_incidence_angle != 0)
    for (int i = 0; i < (int) comparison_minimum_x.size(); i++) {
      for (int j = 0; j < (int) comparison_minimum_x[i].size(); j++) {
	comparison_lower_left_y[i][j] *= constant; // Unit: kilometer
	comparison_maximum_x[i][j] *= constant; // Unit: kilometer
	comparison_minimum_x[i][j] *= constant; // Unit: kilometer
	comparison_maximum_y[i][j] *= constant; // Unit: kilometer
	comparison_minimum_y[i][j] *= constant; // Unit: kilometer
	comparison_upper_left_y[i][j] *= constant; // Unit: kilometer
	comparison_upper_left_x[i][j] *= constant; // Unit: kilometer
	comparison_upper_right_x[i][j] *= constant; // Unit: kilometer
	comparison_lower_left_y[i][j] -= min_y; // Applying y-offset
	comparison_maximum_x[i][j] -= min_x; // Applying x-offset
	comparison_minimum_x[i][j] -= min_x; // Applying x-offset
	comparison_maximum_y[i][j] -= min_y; // Applying y-offset
	comparison_minimum_y[i][j] -= min_y; // Applying y-offset
	comparison_upper_left_y[i][j] -= min_y; // Applying y-offset
	comparison_upper_left_x[i][j] -= min_x; // Applying x-offset
	comparison_upper_right_x[i][j] -= min_x; // Applying x-offset
      }
    }
  
  /*******************/
  /* Axes boundaries */
  /*******************/
  axes1 = "; X [Degree]; Y [Degree]";
  axes2 = "; X [km]; Y [km]";
  x_degree_high = -std::numeric_limits<double>::infinity();
  x_degree_low = std::numeric_limits<double>::infinity();
  y_degree_high = -std::numeric_limits<double>::infinity();
  y_degree_low = std::numeric_limits<double>::infinity();
  x_length_high = -std::numeric_limits<double>::infinity();
  x_length_low = std::numeric_limits<double>::infinity();
  y_length_high = -std::numeric_limits<double>::infinity();
  y_length_low = std::numeric_limits<double>::infinity();
  for (unsigned i = 0; i < maximum_longitude.size(); i++) {
    double max = ArrayMaximum(maximum_longitude[i].size(), maximum_longitude[i].data());
    x_degree_high = (x_degree_high > max) ? x_degree_high : max;
    double min = ArrayMinimum(minimum_longitude[i].size(), minimum_longitude[i].data());
    x_degree_low = (x_degree_low < min) ? x_degree_low : min;
    max = ArrayMaximum(maximum_latitude[i].size(), maximum_latitude[i].data());
    y_degree_high = (y_degree_high > max) ? y_degree_high : max;
    min = ArrayMinimum(minimum_latitude[i].size(), minimum_latitude[i].data());
    y_degree_low = (y_degree_low < min) ? y_degree_low : min;
    max = ArrayMaximum(maximum_x[i].size(), maximum_x[i].data());
    x_length_high = (x_length_high > max) ? x_length_high : max;
    min = ArrayMinimum(minimum_x[i].size(), minimum_x[i].data());
    x_length_low = (x_length_low < min) ? x_length_low : min;
    max = ArrayMaximum(maximum_y[i].size(), maximum_y[i].data());
    y_length_high = (y_length_high > max) ? y_length_high : max;
    min = ArrayMinimum(minimum_y[i].size(), minimum_y[i].data());
    y_length_low = (y_length_low < min) ? y_length_low : min;
  }
  if(comparison_incidence_angle != 0)
    for (unsigned i = 0; i < comparison_maximum_longitude.size(); i++) {
      double max = ArrayMaximum(comparison_maximum_longitude[i].size(), comparison_maximum_longitude[i].data());
      x_degree_high = (x_degree_high > max) ? x_degree_high : max;
      double min = ArrayMinimum(comparison_minimum_longitude[i].size(), comparison_minimum_longitude[i].data());
      x_degree_low = (x_degree_low < min) ? x_degree_low : min;
      max = ArrayMaximum(comparison_maximum_latitude[i].size(), comparison_maximum_latitude[i].data());
      y_degree_high = (y_degree_high > max) ? y_degree_high : max;
      min = ArrayMinimum(comparison_minimum_latitude[i].size(), comparison_minimum_latitude[i].data());
      y_degree_low = (y_degree_low < min) ? y_degree_low : min;
      max = ArrayMaximum(comparison_maximum_x[i].size(), comparison_maximum_x[i].data());
      x_length_high = (x_length_high > max) ? x_length_high : max;
      min = ArrayMinimum(comparison_minimum_x[i].size(), comparison_minimum_x[i].data());
      x_length_low = (x_length_low < min) ? x_length_low : min;
      max = ArrayMaximum(comparison_maximum_y[i].size(), comparison_maximum_y[i].data());
      y_length_high = (y_length_high > max) ? y_length_high : max;
      min = ArrayMinimum(comparison_minimum_y[i].size(), comparison_minimum_y[i].data());
      y_length_low = (y_length_low < min) ? y_length_low : min;
    }
  
  /****************************/
  /* Generate output filename */
  /****************************/
  string fileType = ".png";
  if(comparison_incidence_angle == 0) {
    n = (int) masterimages.size();
    if(n == 1)
      filename = masterimages[0]+"_image"+fileType;
    else {
      int len = masterimages[0].length()-2;
      filename = masterimages[0].substr(0, len)+"LERE_image"+fileType;
    }
  } else {
    m = (int) masterimages.size();
    n = (int) comparison_masterimages.size();
    if(m == 1)
      if(n ==1)
	filename = masterimages[0]+"_v_"+comparison_masterimages[0]+"_image"+fileType;
	else {
	  int len = comparison_masterimages[0].length()-2;
	  filename = masterimages[0]+"_v_"+comparison_masterimages[0].substr(0, len)+"LERE_image"+fileType;
	}
    else
      if(n ==1) {	
	int len = masterimages[0].length()-2;
	filename = masterimages[0].substr(0, len)+"LERE_v_"+comparison_masterimages[0]+"_image"+fileType;
      }
      else {
	int len1 = masterimages[0].length()-2;
	int len2 = comparison_masterimages[0].length()-2;
	filename = masterimages[0].substr(0, len1)+"LERE_v_"+comparison_masterimages[0].substr(0, len2)+"LERE_image"+fileType;
      }
  }
  
  /***************/
  /* Draw canvas */
  /***************/
  canheight = 1000;
  canwidth = int(aspectRatio*canheight);
  can = new TCanvas(filename.c_str(), "", canwidth, canheight);
  can->SetGridx();
  can->SetGridy();
  can->SetRightMargin(0.09);
  can->SetLeftMargin(0.15);
  can->SetBottomMargin(0.15);
  
  /**************/
  /* Draw frame */
  /**************/
  double spacing = 0.;
  h1 = can->DrawFrame(x_degree_low-spacing, y_degree_low-spacing, x_degree_high+spacing, y_degree_high+spacing, axes1.c_str());
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetNdivisions(5);
  h1->GetXaxis()->CenterTitle();
  h1->GetXaxis()->SetNdivisions(5);
  gPad->GetRange(x_min, y_min, x_max, y_max);
  xrange = x_max-x_min;
  yrange = y_max-y_min;
  
  /**************************************/
  /* Create images to insert into frame */
  /**************************************/
  for (int i = 0; i < (int)nimages.size(); i++) {
    vector <TPad *> p;
    vector <TASImage *> im;
    for (int j = 0; j < nimages[i]; j++) {
      /****************************************/
      /* Skip frames that have no useful data */
      /****************************************/
      if(skip[i][j]) continue;
      
      /****************************/
      /* Initialize and store pad */
      /****************************/
      double x1 = (minimum_longitude[i][j]-x_min)/xrange;
      double x2 = (maximum_longitude[i][j]-x_min)/xrange;
      double y1 = (minimum_latitude[i][j]-y_min)/yrange;
      double y2 = (maximum_latitude[i][j]-y_min)/yrange;      
      TPad *pad = new TPad(imagenames[i][j].c_str(), "", x1, y1, x2, y2);
      pad->SetFillColorAlpha(kWhite, 0.); // Make pad transparent
      p.push_back(pad);
      
      /*****************/
      /* Read in image */
      /*****************/
      TASImage *img = new TASImage(imagefiles[i][j].c_str());
      if (!img) {
  	cout << "Could not open image " << imagefiles[i][j] << ".\nTerminating program ...\n" << endl;
  	exit(EXIT_FAILURE);
      }
      img->SetConstRatio(kTRUE);
      img->SetImageQuality(TAttImage::kImgBest);

      /*****************************/
      /* Correct image orientation */
      /*****************************/
      if(upper_left_longitude[i][j] > upper_right_longitude[i][j]) {
  	if(upper_left_latitude[i][j] < lower_left_latitude[i][j])
  	  img->Flip(180);
  	else	    
  	  img->Mirror(true);
      }
      img->SetEditable(kTRUE);
      im.push_back(img);
    }
    pads.push_back(p);
    imgs.push_back(im);
  }

  /***********************************************************************/
  /* Create transparent pads to insert into frame if comparison is given */
  /***********************************************************************/
  if(comparison_incidence_angle != 0)
    for (int i = 0; i < (int)comparison_nimages.size(); i++) {
      vector <TPad *> p;
      for (int j = 0; j < comparison_nimages[i]; j++) {
  	/****************************************/
  	/* Skip frames that have no useful data */
  	/****************************************/
  	if(comparison_skip[i][j]) continue;
      
  	/****************************/
  	/* Initialize and store pad */
  	/****************************/
  	double x1 = (comparison_minimum_longitude[i][j]-x_min)/xrange;
  	double x2 = (comparison_maximum_longitude[i][j]-x_min)/xrange;
  	double y1 = (comparison_minimum_latitude[i][j]-y_min)/yrange;
  	double y2 = (comparison_maximum_latitude[i][j]-y_min)/yrange;      
  	TPad *pad = new TPad(comparison_imagenames[i][j].c_str(), "", x1, y1, x2, y2);
  	pad->SetFillColorAlpha(selected_color, 0.5); // Make pad transparent
  	p.push_back(pad);
      }
      comparison_pads.push_back(p);
    }
  
  /********************/
  /* Speed up drawing */
  /********************/
  // gStyle->SetCanvasPreferGL(kTRUE);

  /**************/
  /* Draw image */
  /**************/
  for (int i = 0; i < (int)pads.size(); i++) {
    for (int j = 0; j < (int)pads[i].size(); j++) {
      can->cd();
      pads[i][j]->Draw();
      pads[i][j]->cd();
      imgs[i][j]->Draw("X");
    }
  }

  /********************************************/
  /* Draw comparison transparent shaded image */
  /********************************************/
  if(comparison_incidence_angle != 0)
    for (int i = 0; i < (int)comparison_pads.size(); i++) {
      for (int j = 0; j < (int)comparison_pads[i].size(); j++) {
  	can->cd();
  	comparison_pads[i][j]->Draw();
      }
    }
  
  /**********************/
  /* Save image to file */
  /**********************/
  can->Print(filename.c_str());

  /**************************/
  /* Delete reserved memory */
  /**************************/
  for (int i = 0; i < (int)pads.size(); i++) {
    for (int j = 0; j < (int)pads[i].size(); j++) {
      delete pads[i][j];
      delete imgs[i][j];
      pads[i][j] = NULL;
      imgs[i][j] = NULL;
    }

  }
  if(comparison_incidence_angle != 0) {
    for (int i = 0; i < (int)comparison_pads.size(); i++) {
      for (int j = 0; j < (int)comparison_pads[i].size(); j++) {
	delete comparison_pads[i][j];
	comparison_pads[i][j] = NULL;
      }
    }
  }
  delete h1;
  delete can;
  h1 = NULL;
  can = NULL;
  
  return;
}

void IncidenceAngleAnalysis_Plot::PlotOverlap(OverlappedImages a, bool print_coordinates)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double dot;
  double image1_x_high;
  double image1_x_low;
  double image1_y_high;
  double image1_y_low;
  double image2_x_high;
  double image2_x_low;
  double image2_y_high;
  double image2_y_low;
  double spacing;
  double x_high;
  double x_low;
  double x_reference_point;
  double y_high;
  double y_low;
  double y_reference_point;
  int canheight;
  int canwidth;
  int n;
  string buffer;
  string filename;
  string image1_name;
  string image2_name;
  TCanvas *can;
  TPolyLine *plot1;
  TPolyLine *plot2;
  TPolyLine *plot3;
  TEllipse *el1;
  TEllipse *el2;
  TH1F *h1;
  TLegend *leg;
  vector <double> Image1_X_Coords;
  vector <double> Image1_Y_Coords;
  vector <double> Image2_X_Coords;
  vector <double> Image2_Y_Coords;
  vector <double> Overplot_X_Coords;
  vector <double> Overplot_Y_Coords;

  /***********************/
  /* Image 1 Information */
  /***********************/
  image1_name = a.GetImage1_name();
  Image1_X_Coords.push_back(a.GetImage1_upper_left_x());
  Image1_Y_Coords.push_back(a.GetImage1_upper_left_y());
  Image1_X_Coords.push_back(a.GetImage1_upper_right_x());
  Image1_Y_Coords.push_back(a.GetImage1_upper_right_y());    
  Image1_X_Coords.push_back(a.GetImage1_lower_right_x());
  Image1_Y_Coords.push_back(a.GetImage1_lower_right_y());
  Image1_X_Coords.push_back(a.GetImage1_lower_left_x());
  Image1_Y_Coords.push_back(a.GetImage1_lower_left_y());
  Image1_X_Coords.push_back(a.GetImage1_upper_left_x());
  Image1_Y_Coords.push_back(a.GetImage1_upper_left_y());

  /***********************/
  /* Image 2 Information */
  /***********************/
  image2_name = a.GetImage2_name();
  Image2_X_Coords.push_back(a.GetImage2_upper_left_x());
  Image2_Y_Coords.push_back(a.GetImage2_upper_left_y());
  Image2_X_Coords.push_back(a.GetImage2_upper_right_x());
  Image2_Y_Coords.push_back(a.GetImage2_upper_right_y());    
  Image2_X_Coords.push_back(a.GetImage2_lower_right_x());
  Image2_Y_Coords.push_back(a.GetImage2_lower_right_y());
  Image2_X_Coords.push_back(a.GetImage2_lower_left_x());
  Image2_Y_Coords.push_back(a.GetImage2_lower_left_y());
  Image2_X_Coords.push_back(a.GetImage2_upper_left_x());
  Image2_Y_Coords.push_back(a.GetImage2_upper_left_y());

  /*********************************/
  /* Overplot Plotting Coordinates */
  /*********************************/
  Overplot_X_Coords.push_back(a.GetOverlap_upper_left_x());
  Overplot_Y_Coords.push_back(a.GetOverlap_upper_left_y());
  Overplot_X_Coords.push_back(a.GetOverlap_upper_right_x());
  Overplot_Y_Coords.push_back(a.GetOverlap_upper_right_y());    
  Overplot_X_Coords.push_back(a.GetOverlap_lower_right_x());
  Overplot_Y_Coords.push_back(a.GetOverlap_lower_right_y());
  Overplot_X_Coords.push_back(a.GetOverlap_lower_left_x());
  Overplot_Y_Coords.push_back(a.GetOverlap_lower_left_y());
  Overplot_X_Coords.push_back(a.GetOverlap_upper_left_x());
  Overplot_Y_Coords.push_back(a.GetOverlap_upper_left_y());
  
  /*********************/
  /* Initialize Canvas */
  /*********************/
  canheight = 1200;
  canwidth = 500;
  can = new TCanvas("Canvas", "", canheight, canwidth);
  can->SetGridx();
  can->SetGridy();

  /***************************/
  /* Determine plotting area */
  /***************************/
  if(Image1_X_Coords[0] < Image1_X_Coords[1])
  {
    image1_x_high = (Image1_X_Coords[1] > Image1_X_Coords[2]) ? Image1_X_Coords[1] : Image1_X_Coords[2];
    image1_x_low  = (Image1_X_Coords[0] < Image1_X_Coords[3]) ? Image1_X_Coords[0] : Image1_X_Coords[3];
  }
  else
  {
    image1_x_high = (Image1_X_Coords[0] > Image1_X_Coords[3]) ? Image1_X_Coords[0] : Image1_X_Coords[3];
    image1_x_low  = (Image1_X_Coords[1] < Image1_X_Coords[2]) ? Image1_X_Coords[1] : Image1_X_Coords[2];
  }
  if(Image1_Y_Coords[0] < Image1_Y_Coords[3])
  {
    image1_y_high = (Image1_Y_Coords[2] > Image1_Y_Coords[3]) ? Image1_Y_Coords[2] : Image1_Y_Coords[3];
    image1_y_low  = (Image1_Y_Coords[0] < Image1_Y_Coords[1]) ? Image1_Y_Coords[0] : Image1_Y_Coords[1];
  }
  else
  {
    image1_y_high = (Image1_Y_Coords[0] > Image1_Y_Coords[1]) ? Image1_Y_Coords[0] : Image1_Y_Coords[1];
    image1_y_low  = (Image1_Y_Coords[2] < Image1_Y_Coords[3]) ? Image1_Y_Coords[2] : Image1_Y_Coords[3];
  }
  if(Image2_X_Coords[0] < Image2_X_Coords[1])
  {
    image2_x_high = (Image2_X_Coords[1] > Image2_X_Coords[2]) ? Image2_X_Coords[1] : Image2_X_Coords[2];
    image2_x_low  = (Image2_X_Coords[0] < Image2_X_Coords[3]) ? Image2_X_Coords[0] : Image2_X_Coords[3];
  }
  else
  {
    image2_x_high = (Image2_X_Coords[0] > Image2_X_Coords[3]) ? Image2_X_Coords[0] : Image2_X_Coords[3];
    image2_x_low  = (Image2_X_Coords[1] < Image2_X_Coords[2]) ? Image2_X_Coords[1] : Image2_X_Coords[2];
  }
  if(Image2_Y_Coords[0] < Image2_Y_Coords[3])
  {
    image2_y_high = (Image2_Y_Coords[2] > Image2_Y_Coords[3]) ? Image2_Y_Coords[2] : Image2_Y_Coords[3];
    image2_y_low  = (Image2_Y_Coords[0] < Image2_Y_Coords[1]) ? Image2_Y_Coords[0] : Image2_Y_Coords[1];
  }
  else
  {
    image2_y_high = (Image2_Y_Coords[0] > Image2_Y_Coords[1]) ? Image2_Y_Coords[0] : Image2_Y_Coords[1];
    image2_y_low  = (Image2_Y_Coords[2] < Image2_Y_Coords[3]) ? Image2_Y_Coords[2] : Image2_Y_Coords[3];
  }
  x_high = (image1_x_high > image2_x_high) ? image1_x_high : image2_x_high;
  x_low = (image1_x_low < image2_x_low) ? image1_x_low : image2_x_low;
  y_high = (image1_y_high > image2_y_high) ? image1_y_high : image2_y_high;
  y_low = (image1_y_low < image2_y_low) ? image1_y_low : image2_y_low;
  
  /*************/
  /* Draw axes */
  /*************/
  buffer = image1_name+" vs "+image2_name+"; X [m]; Y [m]";
  spacing = 1E-4;
  h1 = can->DrawFrame(x_low-spacing, y_low-spacing, x_high+spacing, y_high+spacing, buffer.c_str());
  h1->GetYaxis()->SetNdivisions(10);
  h1->GetXaxis()->SetNdivisions(10);
  
  /****************/
  /* Plot image 1 */
  /****************/
  n = (int)Image1_X_Coords.size();
  plot1 = new TPolyLine(n, Image1_X_Coords.data(), Image1_Y_Coords.data());
  plot1->SetLineColor(kBlue);
  plot1->SetLineWidth(2);
  plot1->Draw();

  /****************/
  /* Plot image 2 */
  /****************/
  n = (int)Image2_X_Coords.size();
  plot2 = new TPolyLine(n, Image2_X_Coords.data(), Image2_Y_Coords.data());
  plot2->SetLineColor(kYellow);
  plot2->SetLineWidth(2);
  plot2->Draw();

  /****************/
  /* Plot Overlap */
  /****************/
  n = (int)Overplot_X_Coords.size();
  plot3 = new TPolyLine(n, Overplot_X_Coords.data(), Overplot_Y_Coords.data());
  plot3->SetLineColor(kGreen);
  plot3->SetLineWidth(2);
  plot3->Draw();
  
  /*************************/
  /* Plot 1 defined origin */
  /*************************/
  x_reference_point = a.GetImage1_upper_left_x();
  y_reference_point = a.GetImage1_upper_left_y();
  dot = 0.01*abs(a.GetImage1_upper_left_x()-a.GetImage1_upper_right_x());
  el1 = new TEllipse(x_reference_point, y_reference_point, dot);
  el1->SetFillColorAlpha(kBlue, 0.50);
  el1->SetFillStyle(4050);
  el1->SetLineColor(kRed);
  el1->Draw();

  /*************************/
  /* Plot 2 defined origin */
  /*************************/
  x_reference_point = a.GetImage2_upper_left_x();
  y_reference_point = a.GetImage2_upper_left_y();
  dot = 0.01*abs(a.GetImage2_upper_left_x()-a.GetImage2_upper_right_x());
  el2 = new TEllipse(x_reference_point, y_reference_point, dot);
  el2->SetFillColorAlpha(kGreen, 0.50);
  el2->SetFillStyle(4050);
  el2->SetLineColor(kRed);
  el2->Draw();
  
  /**********/
  /* Legend */
  /**********/
  leg = new TLegend(0.7,0.7,0.9,0.9);
  //leg->SetHeader("","C"); // option "C" allows to center the header
  buffer = "Sub-image: "+image1_name;
  leg->AddEntry(plot1, buffer.c_str(), "f");
  buffer = "Sub-image: "+image2_name;
  leg->AddEntry(plot2, buffer.c_str(), "f");
  buffer = "Overplot Region";
  leg->AddEntry(plot3, buffer.c_str(), "f");
  leg->AddEntry(el1, "Image 1 Origin", "f");
  leg->AddEntry(el2, "Image 2 Origin", "f");
  leg->Draw();

  /*********************/
  /* Save plot to file */
  /*********************/
  filename = image1_name+"_vs_"+image2_name+"_Graphic.ps";
  can->SaveAs(filename.c_str());

  /*******************************/
  /* Print coordinates to screen */
  /*******************************/
  if(print_coordinates)
  {
    printf("Coordinates for image 1 %s.\n", image1_name.c_str());
    for(int i=0; i<n; i++)
    {
      printf("Corner %d: %lf meters longitude and %lf meters latitude\n", i+1, Image1_X_Coords[i], Image1_Y_Coords[i]);
    }
    printf("\nCoordinates for image 2 %s.\n", image2_name.c_str());
    for(int i=0; i<n; i++)
    {
      printf("Corner %d: %lf meters longitude and %lf meters latitude\n", i+1, Image2_X_Coords[i], Image2_Y_Coords[i]);
    }
    printf("\nCoordinates for overplot region.\n");
    for(int i=0; i<n; i++)
    {
      printf("Corner %d: %lf meters longitude and %lf meters latitude\n", i+1, Overplot_X_Coords[i], Overplot_Y_Coords[i]);
    }
  }
  
  /***********************************/
  /* Free memory reserved for canvas */
  /***********************************/
  delete plot1;
  delete plot2;
  delete plot3;
  delete el1;
  delete el2;
  delete leg;
  delete can;
}

void IncidenceAngleAnalysis_Plot::RelativeCraterDensity(TH1F *h, double area, vector <double> &R, vector <double> &R_err)
{
  int nbins = h->GetNbinsX();
  double binwidth = h->GetBinWidth(0);
  R.resize(nbins);
  R_err.resize(nbins);
  
  for(int i=1; i<=nbins; i++) {
    double D_a = pow(10, h->GetXaxis()->GetBinLowEdge(i));
    double D_b = D_a+pow(10, binwidth);
    double D = sqrt(D_a*D_b);
    int N = h->GetBinContent(i);
    double numerator = pow(D, 3.0)*N;
    double denominator = area*(D_b-D_a);
    R[i-1] = numerator/denominator;
    R_err[i-1] = (N != 0) ? R[i-1]/sqrt(N) : 0;
  }
}

void IncidenceAngleAnalysis_Plot::SubImage(Images a, bool selenographic, bool print_coordinates)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double dot;
  double lower_left_latitude;
  double lower_left_longitude;
  double lower_left_x;
  double lower_left_y;
  double lower_right_latitude;
  double lower_right_longitude;
  double lower_right_x;
  double lower_right_y;
  double spacing;
  double upper_left_latitude;
  double upper_left_longitude;
  double upper_left_x;
  double upper_left_y;
  double upper_right_latitude;
  double upper_right_longitude;
  double upper_right_x;
  double upper_right_y;
  double x_high;
  double x_low;
  double x_reference_point;
  double y_high;
  double y_low;
  double y_reference_point;
  int canheight;
  int canwidth;
  int n;
  string buffer;
  string filename;
  string image_name;
  TCanvas *can;
  TPolyLine *plot;
  TEllipse *el;
  TH1F *h1;
  TLegend *leg;
  vector <double> X_Coords;
  vector <double> Y_Coords;
    
  /******************************/
  /* Retrieve image information */
  /******************************/
  image_name = a.GetName();
  lower_left_latitude = a.GetLower_left_latitude();
  lower_left_longitude = a.GetLower_left_longitude();
  lower_left_x = a.GetLower_left_x();
  lower_left_y = a.GetLower_left_y();
  lower_right_latitude = a.GetLower_right_latitude();
  lower_right_longitude = a.GetLower_right_longitude();
  lower_right_x = a.GetLower_right_x();
  lower_right_y = a.GetLower_right_y();
  upper_left_latitude = a.GetUpper_left_latitude();
  upper_left_longitude = a.GetUpper_left_longitude();
  upper_left_x = a.GetUpper_left_x();
  upper_left_y = a.GetUpper_left_y();
  upper_right_latitude = a.GetUpper_right_latitude();
  upper_right_longitude = a.GetUpper_right_longitude();
  upper_right_x = a.GetUpper_right_x();
  upper_right_y = a.GetUpper_right_y();

  /*********************/
  /* Initialize Canvas */
  /*********************/
  canheight = 1200;
  canwidth = 600;
  can = new TCanvas("Canvas", "", canheight, canwidth);
  can->SetGridx();
  can->SetGridy();

  /*************/
  /* Draw axes */
  /*************/
  if(selenographic)
  {
    buffer = image_name+"; X [Degree]; Y [Degree]";
    x_high = a.GetMaximum_longitude();
    x_low = a.GetMinimum_longitude();
    x_reference_point = upper_left_longitude;
    y_high = a.GetMaximum_latitude();
    y_low = a.GetMinimum_latitude();
    y_reference_point = upper_left_latitude;
    spacing = 1E-4;
  }
  else
  {
    buffer = image_name+"; X [m]; Y [m]";
    x_high = a.GetMaximum_x();
    x_low = a.GetMinimum_x();
    x_reference_point = upper_left_x;
    y_high = a.GetMaximum_y();
    y_low = a.GetMinimum_y();
    y_reference_point = upper_left_y;
    spacing = 1E3;
  }
  h1 = can->DrawFrame(x_low-spacing, y_low-spacing, x_high+spacing, y_high+spacing, buffer.c_str());
  h1->GetYaxis()->SetNdivisions(10);
  h1->GetXaxis()->SetNdivisions(10);

  /**************/
  /* Plot image */
  /**************/
  if(selenographic)
  {
    X_Coords.push_back(upper_left_longitude);
    Y_Coords.push_back(upper_left_latitude);
    X_Coords.push_back(upper_right_longitude);
    Y_Coords.push_back(upper_right_latitude);    
    X_Coords.push_back(lower_right_longitude);
    Y_Coords.push_back(lower_right_latitude);
    X_Coords.push_back(lower_left_longitude);
    Y_Coords.push_back(lower_left_latitude);
    X_Coords.push_back(upper_left_longitude);
    Y_Coords.push_back(upper_left_latitude);
    dot = 0.01*abs(upper_left_longitude-upper_right_longitude);
  }
  else
  {
    X_Coords.push_back(upper_left_x);
    Y_Coords.push_back(upper_left_y);
    X_Coords.push_back(upper_right_x);
    Y_Coords.push_back(upper_right_y);
    X_Coords.push_back(lower_right_x);
    Y_Coords.push_back(lower_right_y);
    X_Coords.push_back(lower_left_x);
    Y_Coords.push_back(lower_left_y);
    X_Coords.push_back(upper_left_x);
    Y_Coords.push_back(upper_left_y);
    dot = 0.01*abs(upper_left_x-upper_right_x);
  }
  n = (int)X_Coords.size();
  plot = new TPolyLine(n, X_Coords.data(), Y_Coords.data());
  plot->SetLineColor(kGreen);
  plot->SetLineWidth(2);
  plot->Draw();

  /***********************/
  /* Plot defined origin */
  /***********************/
  el = new TEllipse(x_reference_point, y_reference_point, dot);
  el->SetFillColorAlpha(kRed, 0.50);
  el->SetFillStyle(4050);
  el->SetLineColor(kRed);
  el->Draw();

  /**********/
  /* Legend */
  /**********/
  leg = new TLegend(0.7,0.7,0.9,0.9);
  //leg->SetHeader("","C"); // option "C" allows to center the header
  buffer = "Sub-image: "+image_name;
  leg->AddEntry(plot, buffer.c_str(), "f");
  leg->AddEntry(el, "Image Origin", "f");
  leg->Draw();

  /*********************/
  /* Save plot to file */
  /*********************/
  filename = image_name+"_Graphic.ps";
  can->SaveAs(filename.c_str());

  /*******************************/
  /* Print coordinates to screen */
  /*******************************/
  if(print_coordinates)
  {
    printf("Coordinates for image %s.\n", image_name.c_str());
    for(int i=0; i<n; i++)
    {
      if(selenographic)
	printf("Corner %d: %lf degrees longitude and %lf degrees latitude\n", i+1, X_Coords[i], Y_Coords[i]);
      else
	printf("Corner %d: %lf meters in x and %lf meters in y\n", i+1, X_Coords[i], Y_Coords[i]);
    }
  }
  
  /***********************************/
  /* Free memory reserved for canvas */
  /***********************************/
  delete plot;
  delete el;
  delete leg;
  delete can;
}

void IncidenceAngleAnalysis_Plot::SubImages(Images a, Images b, bool selenographic, bool print_coordinates)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double image1_dot;
  double image1_x_high;
  double image1_x_low;
  double image1_x_reference;
  double image1_y_high;
  double image1_y_low;
  double image1_y_reference;
  double image2_dot;
  double image2_x_high;
  double image2_x_low;
  double image2_x_reference;
  double image2_y_high;
  double image2_y_low;
  double image2_y_reference;
  double spacing;
  double x_high;
  double x_low;
  double y_high;
  double y_low;
  int canheight;
  int canwidth;
  int n;
  string buffer;
  string filename;
  string image1_name;
  string image2_name;
  TCanvas *can;
  TPolyLine *plot1;
  TPolyLine *plot2;
  TEllipse *el1;
  TEllipse *el2;
  TH1F *h1;
  TLegend *leg;
  vector <double> Image1_X_Coords;
  vector <double> Image1_Y_Coords;
  vector <double> Image2_X_Coords;
  vector <double> Image2_Y_Coords;

  /***********************/
  /* Image 1 Information */
  /***********************/
  image1_name = a.GetName();
  if(selenographic)
  {    
    Image1_X_Coords.push_back(a.GetUpper_left_longitude());
    Image1_Y_Coords.push_back(a.GetUpper_left_latitude());
    Image1_X_Coords.push_back(a.GetUpper_right_longitude());
    Image1_Y_Coords.push_back(a.GetUpper_right_latitude());    
    Image1_X_Coords.push_back(a.GetLower_right_longitude());
    Image1_Y_Coords.push_back(a.GetLower_right_latitude());
    Image1_X_Coords.push_back(a.GetLower_left_longitude());
    Image1_Y_Coords.push_back(a.GetLower_left_latitude());
    Image1_X_Coords.push_back(a.GetUpper_left_longitude());
    Image1_Y_Coords.push_back(a.GetUpper_left_latitude());
    image1_x_reference = a.GetUpper_left_longitude();
    image1_y_reference = a.GetUpper_left_latitude();
    image1_dot = 0.01*abs(a.GetUpper_left_longitude()-a.GetUpper_right_longitude());
  }
  else
  {
    Image1_X_Coords.push_back(a.GetUpper_left_x());
    Image1_Y_Coords.push_back(a.GetUpper_left_y());
    Image1_X_Coords.push_back(a.GetUpper_right_x());
    Image1_Y_Coords.push_back(a.GetUpper_right_y());    
    Image1_X_Coords.push_back(a.GetLower_right_x());
    Image1_Y_Coords.push_back(a.GetLower_right_y());
    Image1_X_Coords.push_back(a.GetLower_left_x());
    Image1_Y_Coords.push_back(a.GetLower_left_y());
    Image1_X_Coords.push_back(a.GetUpper_left_x());
    Image1_Y_Coords.push_back(a.GetUpper_left_y());
    image1_x_reference = a.GetUpper_left_x();
    image1_y_reference = a.GetUpper_left_y();
    image1_dot = 0.01*abs(a.GetUpper_left_x()-a.GetUpper_right_x());
  }
  
  /***********************/
  /* Image 2 Information */
  /***********************/
  image2_name = b.GetName();
  if(selenographic)
  {
    Image2_X_Coords.push_back(b.GetUpper_left_longitude());
    Image2_Y_Coords.push_back(b.GetUpper_left_latitude());
    Image2_X_Coords.push_back(b.GetUpper_right_longitude());
    Image2_Y_Coords.push_back(b.GetUpper_right_latitude());    
    Image2_X_Coords.push_back(b.GetLower_right_longitude());
    Image2_Y_Coords.push_back(b.GetLower_right_latitude());
    Image2_X_Coords.push_back(b.GetLower_left_longitude());
    Image2_Y_Coords.push_back(b.GetLower_left_latitude());
    Image2_X_Coords.push_back(b.GetUpper_left_longitude());
    Image2_Y_Coords.push_back(b.GetUpper_left_latitude());
    image2_x_reference = b.GetUpper_left_longitude();
    image2_y_reference = b.GetUpper_left_latitude();
    image2_dot = 0.01*abs(b.GetUpper_left_longitude()-b.GetUpper_right_longitude());
  }
  else
  {
    Image2_X_Coords.push_back(b.GetUpper_left_x());
    Image2_Y_Coords.push_back(b.GetUpper_left_y());
    Image2_X_Coords.push_back(b.GetUpper_right_x());
    Image2_Y_Coords.push_back(b.GetUpper_right_y());    
    Image2_X_Coords.push_back(b.GetLower_right_x());
    Image2_Y_Coords.push_back(b.GetLower_right_y());
    Image2_X_Coords.push_back(b.GetLower_left_x());
    Image2_Y_Coords.push_back(b.GetLower_left_y());
    Image2_X_Coords.push_back(b.GetUpper_left_x());
    Image2_Y_Coords.push_back(b.GetUpper_left_y());
    image2_x_reference = b.GetUpper_left_x();
    image2_y_reference = b.GetUpper_left_y();
    image2_dot = 0.01*abs(b.GetUpper_left_longitude()-b.GetUpper_right_longitude());
  }
  
  /*********************/
  /* Initialize Canvas */
  /*********************/
  canheight = 1200;
  canwidth = 500;
  can = new TCanvas("Canvas", "", canheight, canwidth);
  can->SetGridx();
  can->SetGridy();

  /***************************/
  /* Determine plotting area */
  /***************************/
  if(Image1_X_Coords[0] < Image1_X_Coords[1])
  {
    image1_x_high = (Image1_X_Coords[1] > Image1_X_Coords[2]) ? Image1_X_Coords[1] : Image1_X_Coords[2];
    image1_x_low  = (Image1_X_Coords[0] < Image1_X_Coords[3]) ? Image1_X_Coords[0] : Image1_X_Coords[3];
  }
  else
  {
    image1_x_high = (Image1_X_Coords[0] > Image1_X_Coords[3]) ? Image1_X_Coords[0] : Image1_X_Coords[3];
    image1_x_low  = (Image1_X_Coords[1] < Image1_X_Coords[2]) ? Image1_X_Coords[1] : Image1_X_Coords[2];
  }
  if(Image1_Y_Coords[0] < Image1_Y_Coords[3])
  {
    image1_y_high = (Image1_Y_Coords[2] > Image1_Y_Coords[3]) ? Image1_Y_Coords[2] : Image1_Y_Coords[3];
    image1_y_low  = (Image1_Y_Coords[0] < Image1_Y_Coords[1]) ? Image1_Y_Coords[0] : Image1_Y_Coords[1];
  }
  else
  {
    image1_y_high = (Image1_Y_Coords[0] > Image1_Y_Coords[1]) ? Image1_Y_Coords[0] : Image1_Y_Coords[1];
    image1_y_low  = (Image1_Y_Coords[2] < Image1_Y_Coords[3]) ? Image1_Y_Coords[2] : Image1_Y_Coords[3];
  }
  if(Image2_X_Coords[0] < Image2_X_Coords[1])
  {
    image2_x_high = (Image2_X_Coords[1] > Image2_X_Coords[2]) ? Image2_X_Coords[1] : Image2_X_Coords[2];
    image2_x_low  = (Image2_X_Coords[0] < Image2_X_Coords[3]) ? Image2_X_Coords[0] : Image2_X_Coords[3];
  }
  else
  {
    image2_x_high = (Image2_X_Coords[0] > Image2_X_Coords[3]) ? Image2_X_Coords[0] : Image2_X_Coords[3];
    image2_x_low  = (Image2_X_Coords[1] < Image2_X_Coords[2]) ? Image2_X_Coords[1] : Image2_X_Coords[2];
  }
  if(Image2_Y_Coords[0] < Image2_Y_Coords[3])
  {
    image2_y_high = (Image2_Y_Coords[2] > Image2_Y_Coords[3]) ? Image2_Y_Coords[2] : Image2_Y_Coords[3];
    image2_y_low  = (Image2_Y_Coords[0] < Image2_Y_Coords[1]) ? Image2_Y_Coords[0] : Image2_Y_Coords[1];
  }
  else
  {
    image2_y_high = (Image2_Y_Coords[0] > Image2_Y_Coords[1]) ? Image2_Y_Coords[0] : Image2_Y_Coords[1];
    image2_y_low  = (Image2_Y_Coords[2] < Image2_Y_Coords[3]) ? Image2_Y_Coords[2] : Image2_Y_Coords[3];
  }
  x_high = (image1_x_high > image2_x_high) ? image1_x_high : image2_x_high;
  x_low = (image1_x_low < image2_x_low) ? image1_x_low : image2_x_low;
  y_high = (image1_y_high > image2_y_high) ? image1_y_high : image2_y_high;
  y_low = (image1_y_low < image2_y_low) ? image1_y_low : image2_y_low;
  
  /*************/
  /* Draw axes */
  /*************/
  buffer = image1_name+" vs "+image2_name+"; X [Degree]; Y [Degree]";
  spacing = (selenographic) ? 1E-4 : 1E3;
  h1 = can->DrawFrame(x_low-spacing, y_low-spacing, x_high+spacing, y_high+spacing, buffer.c_str());
  h1->GetYaxis()->SetNdivisions(10);
  h1->GetXaxis()->SetNdivisions(10);
  
  /****************/
  /* Plot image 1 */
  /****************/
  n = (int)Image1_X_Coords.size();
  plot1 = new TPolyLine(n, Image1_X_Coords.data(), Image1_Y_Coords.data());
  plot1->SetLineColor(kBlue);
  plot1->SetLineWidth(2);
  plot1->Draw();

  /****************/
  /* Plot image 2 */
  /****************/
  n = (int)Image2_X_Coords.size();
  plot2 = new TPolyLine(n, Image2_X_Coords.data(), Image2_Y_Coords.data());
  plot2->SetLineColor(kGreen);
  plot2->SetLineWidth(2);
  plot2->Draw();
  
  /*************************/
  /* Plot 1 defined origin */
  /*************************/
  el1 = new TEllipse(image1_x_reference, image1_y_reference, image1_dot);
  el1->SetFillColorAlpha(kBlue, 0.50);
  el1->SetFillStyle(4050);
  el1->SetLineColor(kRed);
  el1->Draw();

  /*************************/
  /* Plot 2 defined origin */
  /*************************/
  el2 = new TEllipse(image2_x_reference, image2_y_reference, image2_dot);
  el2->SetFillColorAlpha(kGreen, 0.50);
  el2->SetFillStyle(4050);
  el2->SetLineColor(kRed);
  el2->Draw();
  
  /**********/
  /* Legend */
  /**********/
  leg = new TLegend(0.7,0.7,0.9,0.9);
  //leg->SetHeader("","C"); // option "C" allows to center the header
  buffer = "Sub-image: "+image1_name;
  leg->AddEntry(plot1, buffer.c_str(), "f");
  buffer = "Sub-image: "+image2_name;
  leg->AddEntry(plot2, buffer.c_str(), "f");
  leg->AddEntry(el1, "Image 1 Origin", "f");
  leg->AddEntry(el2, "Image 2 Origin", "f");
  leg->Draw();

  /*********************/
  /* Save plot to file */
  /*********************/
  filename = image1_name+"_vs_"+image2_name+"_Graphic.ps";
  can->SaveAs(filename.c_str());

  /*******************************/
  /* Print coordinates to screen */
  /*******************************/
  if(print_coordinates)
  {
    printf("Coordinates for image 1 %s.\n", image1_name.c_str());
    for(int i=0; i<n; i++)
      printf("Corner %d: %lf degrees longitude and %lf degrees latitude\n", i+1, Image1_X_Coords[i], Image1_Y_Coords[i]);
    printf("\nCoordinates for image 2 %s.\n", image2_name.c_str());
    for(int i=0; i<n; i++)
      printf("Corner %d: %lf degrees longitude and %lf degrees latitude\n", i+1, Image2_X_Coords[i], Image2_Y_Coords[i]);
  }
  
  /***********************************/
  /* Free memory reserved for canvas */
  /***********************************/
  delete plot1;
  delete plot2;
  delete el1;
  delete el2;
  delete leg;
  delete can;
}

void IncidenceAngleAnalysis_Plot::TestOverlap(string imagename1, string imagename2, vector <ImageSets> &imagesets, vector <Images> &images, bool selenographic)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double max_area;
  double spacing;
  double x_high;
  double x_low;
  double x_max;
  double x_min;
  double xrange;
  double y_high;
  double y_low;
  double y_min;
  double y_max;
  double yrange;
  int canheight;
  int canwidth;
  int first_index;
  int last_index;
  int n;
  int value;
  string delay;
  string dir;
  string buffer;
  string field;
  string filename;
  string format;
  TCanvas *can;
  TH1F *h1;
  vector <double> master_image_areas;
  vector <double> maximum_latitude;
  vector <double> maximum_longitude;
  vector <double> maximum_x;
  vector <double> maximum_y;
  vector <double> minimum_latitude;
  vector <double> minimum_longitude;
  vector <double> minimum_x;
  vector <double> minimum_y;
  vector <int> master_image_id;
  vector <string> image_directories;
  vector <string> image_files;
  vector <string> master_image_names(2);
  vector <TCanvas *> multiCan;
  vector < vector <TASImage *> > tasimages(6, vector <TASImage *> ());
  vector < vector <TPad *> > pads(2, vector <TPad *> ());

  /************************************/
  /* Sub-image directory (Hard coded) */
  /************************************/
  dir="/Users/MRichardson/Desktop/Incidence_Angle_Analysis/scripts/";

  /*****************************************/
  /* Record master image names into vector */
  /*****************************************/
  master_image_names[0] = imagename1;
  master_image_names[1] = imagename2;

  /*********************************/
  /* Sort imagesets vector by name */
  /*********************************/
  field = "name";
  SortData <ImageSets> sortimagesets(imagesets, field);
  sortimagesets.arrange();
  imagesets = sortimagesets.GetData();

  /**************************/
  /* Retrieve master images */
  /**************************/
  max_area = -std::numeric_limits<double>::infinity();
  n = (int)imagesets.size();
  for(int i=0; i<(int)master_image_names.size(); i++)
  {
    /******************************/
    /* Identify master image name */
    /******************************/
    string master_image_name = master_image_names[i];
    
    /*********************************************/
    /* Find master image within imagesets vector */
    /*********************************************/
    int index = SearchData<ImageSets>::BinarySearch(imagesets, 0, n-1, field, &master_image_name);

    /****************/
    /* Verify image */
    /****************/
    if(index == -1)
    {
      printf("Invalid image: %s.\nTerminating program...\n", master_image_name.c_str());
      exit(1);
    }

    /******************************/
    /* Retrieve image information */
    /******************************/
    master_image_areas.push_back(imagesets[index].GetArea());
    master_image_id.push_back(imagesets[index].GetId());
    maximum_latitude.push_back(imagesets[index].GetMaximum_latitude());
    maximum_longitude.push_back(imagesets[index].GetMaximum_longitude());
    maximum_x.push_back(imagesets[index].GetMaximum_x());
    maximum_y.push_back(imagesets[index].GetMaximum_y());
    minimum_latitude.push_back(imagesets[index].GetMinimum_latitude());
    minimum_longitude.push_back(imagesets[index].GetMinimum_longitude());
    minimum_x.push_back(imagesets[index].GetMinimum_x());
    minimum_y.push_back(imagesets[index].GetMinimum_y());

    /**************************/
    /* Determine maximum area */
    /**************************/
    max_area = (master_image_areas.back() > max_area) ? master_image_areas.back() : max_area;
  }
  
  /*****************/
  /* Axes settings */
  /*****************/
  if(selenographic)
  {
    buffer = "; X [Degree]; Y [Degree]";
    x_high = -std::numeric_limits<double>::infinity();
    x_low = std::numeric_limits<double>::infinity();
    y_high = -std::numeric_limits<double>::infinity();
    y_low = std::numeric_limits<double>::infinity();
    for(int i=0; i<(int)master_image_id.size(); i++)
    {
      x_high = (maximum_longitude[i] > x_high) ? maximum_longitude[i] : x_high;
      x_low = (minimum_longitude[i] < x_low) ? minimum_longitude[i] : x_low;
      y_high = (maximum_latitude[i] > y_high) ? maximum_latitude[i] : y_high;
      y_low = (minimum_latitude[i] < y_low) ? minimum_latitude[i] : y_low;
    }
    spacing = 1.0E-2;
  }
  else
  {
    buffer = "; X [m]; Y [m]";
    x_high = -std::numeric_limits<double>::infinity();
    x_low = std::numeric_limits<double>::infinity();
    y_high = -std::numeric_limits<double>::infinity();
    y_low = std::numeric_limits<double>::infinity();
    for(int i=0; i<(int)master_image_id.size(); i++)
    {
      x_high = (maximum_x[i] > x_high) ? maximum_x[i] : x_high;
      x_low = (minimum_x[i] < x_low) ? minimum_x[i] : x_low;
      y_high = (maximum_y[i] > y_high) ? maximum_y[i] : y_high;
      y_low = (minimum_y[i] < y_low) ? minimum_y[i] : y_low;
    }
    spacing = 1.0E3;
  }

  /**********************/
  /* Sort images vector */
  /**********************/
  field = "image_set_id";
  SortData <Images> sortimages(images, field);
  sortimages.arrange();
  images = sortimages.GetData();

  /*********************/
  /* Initialize Canvas */
  /*********************/
  canheight = 1200;
  canwidth = 800;
  can = new TCanvas("Canvas", "", canheight, canwidth);
  can->SetGridx();
  can->SetGridy();

  /**************/
  /* Draw frame */
  /**************/
  h1 = can->DrawFrame(x_low-spacing, y_low-spacing, x_high+spacing, y_high+spacing, buffer.c_str());
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetNdivisions(5);
  h1->GetXaxis()->CenterTitle();
  h1->GetXaxis()->SetNdivisions(5);
  gPad->GetRange(x_min, y_min, x_max, y_max);
  xrange = x_max-x_min;
  yrange = y_max-y_min;  

  /*******************************/
  /* Transparent TPad for canvas */
  /*******************************/
  TPad *CanPad = new TPad("CanPad", "CanPad", 0, 0, 1, 1);
  CanPad->SetFillColorAlpha(kWhite, 0.);

  /*********************************/
  /* Iterate through master images */
  /*********************************/
  for(int i=0; i<(int)master_image_id.size(); i++)
  {
    /*******************************************************************/
    /* Find first and last occurrence of image_set_id in images vector */
    /*******************************************************************/
    n = (int)images.size();
    value = master_image_id[i];
    first_index = SearchData<Images>::FirstOccurence(images, 0, n-1, field, &value);
    last_index = SearchData<Images>::LastOccurence(images, 0, n-1, field, &value);

    /*****************************************************/
    /* Iterate through images vector and plot sub-images */
    /*****************************************************/
    for(int j=first_index; j<=last_index; j++)
    {
      /*****************************/
      /* Determine sub-image scale */
      /*****************************/
      string sub_image_name = images[j].GetName();
      int p1 = sub_image_name.find("_")+1;
      int scl = stoi(sub_image_name.substr(p1, 1), nullptr);
      if(scl == 0)
      {
	/*********************************/
	/* Construct image full filename */
	/*********************************/
	int p2 = sub_image_name.rfind("_")+1;
	int p3 = sub_image_name.length();
	int length = p3-p2;
	string isn = sub_image_name.substr(p2, length);
	isn = string(5-length, '0').append(isn);
	filename = dir+"images_"+master_image_names[i]+"/"+master_image_names[i]+"_0_"+isn+".png";
	if(!FileExists(filename))
	{
	  printf("Image file %s does not exist!\n", filename.c_str());
	  continue;
	}

	/*************************************************/
	/* Retrieve positional information for sub-image */
	/*************************************************/
	double sub_image_lower_left_latitude = images[j].GetLower_left_latitude();
	double sub_image_lower_left_y = images[j].GetLower_left_y();
	double sub_image_maximum_latitude = images[j].GetMaximum_latitude();
	double sub_image_maximum_longitude = images[j].GetMaximum_longitude();
	double sub_image_maximum_x = images[j].GetMaximum_x();
	double sub_image_maximum_y = images[j].GetMaximum_y();
	double sub_image_minimum_latitude = images[j].GetMinimum_latitude();
	double sub_image_minimum_longitude = images[j].GetMinimum_longitude();
	double sub_image_minimum_x = images[j].GetMinimum_x();
	double sub_image_minimum_y = images[j].GetMinimum_y();
	double sub_image_upper_left_latitude = images[j].GetUpper_left_latitude();
	double sub_image_upper_left_longitude = images[j].GetUpper_left_longitude();
	double sub_image_upper_left_x = images[j].GetUpper_left_x();
	double sub_image_upper_left_y = images[j].GetUpper_left_y();
	double sub_image_upper_right_longitude = images[j].GetUpper_right_longitude();
	double sub_image_upper_right_x = images[j].GetUpper_right_x();

	/******************/
	/* Initialize pad */
	/******************/
	double x1 = 0;
	double x2 = 0;
	double y1 = 0;
	double y2 = 0;
	if(selenographic)
	{
	  x2 = (sub_image_maximum_longitude-x_min)/xrange;
	  x1 = (sub_image_minimum_longitude-x_min)/xrange;
	  y2 = (sub_image_maximum_latitude-y_min)/yrange;
	  y1 = (sub_image_minimum_latitude-y_min)/yrange;
	}
	else
	{
	  x2 = (sub_image_maximum_x-x_min)/xrange;
	  x1 = (sub_image_minimum_x-x_min)/xrange;
	  y2 = (sub_image_maximum_y-y_min)/yrange;
	  y1 = (sub_image_minimum_y-y_min)/yrange;
	}
	TPad *pad = new TPad(filename.c_str(), filename.c_str(), x1, y1, x2, y2);
	
	/************************/
	/* Make pad transparent */
	/************************/
	pad->SetFillColorAlpha(kWhite, 0.);

	/********************************/
	/* Record current sub-image pad */
	/********************************/	
	if(max_area == master_image_areas[i])
	  pads[0].push_back(pad);
	else
	  pads[1].push_back(pad);

	/**************************/
	/* Open current sub-image */
	/**************************/
	TASImage *img = new TASImage(filename.c_str());
	if (!img)
	{
	  printf("Could not open image %s.\nTerminating program...\n", filename.c_str());
	  exit(1);
	}
	img->SetConstRatio(kFALSE);
	img->SetImageQuality(TAttImage::kImgBest);

	/*****************************/
	/* Correct image orientation */
	/*****************************/
	if(selenographic)
	{
	  if(sub_image_upper_left_longitude > sub_image_upper_right_longitude)
	  {
	    if(sub_image_upper_left_latitude < sub_image_lower_left_latitude)
	      img->Flip(180);
	    else	    
	      img->Mirror(true);
	  }
	}
	else
	{
	  if(sub_image_upper_left_x > sub_image_upper_right_x)
	  {
	    if(sub_image_upper_left_y < sub_image_lower_left_y)
	      img->Flip(180);
	    else
	      img->Mirror(true);
	  }
	}
	img->SetEditable(kTRUE);

	/***************************************/
	/* Make overlapping images transparent */
	/***************************************/
	if(max_area == master_image_areas[i])
	{
	  tasimages[0].push_back(img);
	}
	else
	{
	  /*******************/
	  /* Clone sub-image */
	  /*******************/
	  vector <TASImage *> cloned_images(5);
	  for(int k=0; k<5; k++)
	  {
	    buffer = "img_clone_"+to_string(k);
	    cloned_images[k] = (TASImage *)img->Clone(buffer.c_str());
	  }

	  int image_transparency_level = 0;
	  while(image_transparency_level < 5)
	  {
	    /***********************/
	    /* Retrieve ARGB array */
	    /***********************/
	    unsigned int *argb = (unsigned int *)cloned_images[image_transparency_level]->GetArgbArray();
	    int w = cloned_images[image_transparency_level]->GetWidth();
	    int h = cloned_images[image_transparency_level]->GetHeight();
	    
	    /****************************************/
	    /* Scan all pixels in current image and */
	    /* make rgb1, rgb2 colors transparent.  */
	    /****************************************/
	    for(int k=0; k<h; k++)
	    {
	      for(int l=0; l<w; l++)
	      {
		int idx = k*w + l;
		
		/**************************/
		/* RGB part of ARGB color */
		/**************************/
		unsigned int col = argb[idx] & 0xffffff;
		
		/******************************/
		/* Alpha channel modification */
		/******************************/
		switch(image_transparency_level)
		{
		  case 0: argb[idx] = 0x00000000 + col; // 100 percent transparency
		    break;
		  case 1: argb[idx] = 0x3F000000 + col; // 75 percent transparency
		    break;
		  case 2: argb[idx] = 0x7F000000 + col; // 50 percent transparency
		    break;
		  case 3: argb[idx] = 0xBF000000 + col; // 25 percent transparency
		    break;
		  case 4: argb[idx] = 0xFF000000 + col; // 0 percent transparency
		    break;
		}
	      }
	    }
	    
	    /********************/
	    /* Record sub-image */
	    /********************/
	    tasimages[image_transparency_level+1].push_back(cloned_images[image_transparency_level]);

	    /**********************************/
	    /* Update image tranparency level */
	    /**********************************/
	    image_transparency_level++;
	  }
	}
      }
    }
  }

  /********************/
  /* Speed up drawing */
  /********************/
  gStyle->SetCanvasPreferGL(kTRUE);

  /*************************************/
  /* Remove past instance of animation */
  /*************************************/
  filename = "TestGraphic.gif";
  remove(filename.c_str());

  /*************************/
  /* Draw background image */
  /*************************/
  for(int j=0; j<(int)pads[0].size(); j++)
  {	
    pads[0][j]->Draw();
    pads[0][j]->cd();
    tasimages[0][j]->Draw("X");
    can->cd();
  }

  /*****************/
  /* Overplot pads */
  /*****************/
  for(int j=0; j<(int)pads[1].size(); j++)
  {
    pads[1][j]->Draw();
    can->cd();
  }

  /*********************/
  /* Save plot to file */
  /*********************/
  delay = "100";
  filename = "TestGraphic.gif+"+delay;
  //can->Print(filename.c_str());

  /***************/
  /* Test points */
  /***************/
  double px_1; //M109215691LE
  double py_1; //M109215691LE
  double px_2; //M109215691LE
  double py_2; //M109215691LE
  double px_3; //M109215691LE
  double py_3; //M109215691LE
  double px_4; //M109215691LE
  double py_4; //M109215691LE
  double px_5; //M109215691RE
  double py_5; //M109215691RE
  double px_6; //M109215691RE
  double py_6; //M109215691RE
  double px_7; //M109215691RE
  double py_7; //M109215691RE
  double px_8; //M109215691RE
  double py_8; //M109215691RE
  double px_9; //M109215691RE
  double py_9; //M109215691RE
  if(selenographic)
  {
    px_1 = (3.63700-x_min)/xrange;
    py_1 = (26.10290-y_min)/yrange;
    px_2 = (3.63770-x_min)/xrange;
    py_2 = (26.19795-y_min)/yrange;
    px_3 = (3.68560-x_min)/xrange;
    py_3 = (26.20835-y_min)/yrange;
    px_4 = (3.68540-x_min)/xrange;
    py_4 = (26.10235-y_min)/yrange;
    px_5 = (3.63295-x_min)/xrange;
    py_5 = (26.10005-y_min)/yrange;
    px_6 = (3.61250-x_min)/xrange;
    py_6 = (26.15665-y_min)/yrange;
    px_7 = (3.59070-x_min)/xrange;
    py_7 = (26.15050-y_min)/yrange;
    px_8 = (3.56628-x_min)/xrange;
    py_8 = (26.20895-y_min)/yrange;
    px_9 = (3.56976-x_min)/xrange;
    py_9 = (26.13033-y_min)/yrange;
  }
  else
  {
    px_1 = (6318923.8-x_min)/xrange;
    py_1 = (45351178.46-y_min)/yrange;
    px_2 = (6320139.98-x_min)/xrange;
    py_2 = (45516318.33-y_min)/yrange;
    px_3 = (6403361.44-x_min)/xrange;
    py_3 = (45534387.29-y_min)/yrange;
    px_4 = (6403013.96-x_min)/xrange;
    py_4 = (45350222.89-y_min)/yrange;
    px_5 = (6311887.33-x_min)/xrange;
    py_5 = (45346226.87-y_min)/yrange;
    px_6 = (6276357.5-x_min)/xrange;
    py_6 = (45444563.71-y_min)/yrange;
    px_7 = (6238482.18-x_min)/xrange;
    py_7 = (45433878.7-y_min)/yrange;
    px_8 = (6196054.872-x_min)/xrange;
    py_8 = (45535429.73-y_min)/yrange;
    px_9 = (6202101.024-x_min)/xrange;
    py_9 = (45398835.342-y_min)/yrange;
  }
  TEllipse *dot1 = new TEllipse(px_1, py_1, 0.001);
  TEllipse *dot2 = new TEllipse(px_2, py_2, 0.001);
  TEllipse *dot3 = new TEllipse(px_3, py_3, 0.001);
  TEllipse *dot4 = new TEllipse(px_4, py_4, 0.001);
  TEllipse *dot5 = new TEllipse(px_5, py_5, 0.001);
  TEllipse *dot6 = new TEllipse(px_6, py_6, 0.001);
  TEllipse *dot7 = new TEllipse(px_7, py_7, 0.001);
  TEllipse *dot8 = new TEllipse(px_8, py_8, 0.001);
  TEllipse *dot9 = new TEllipse(px_9, py_9, 0.001);
  dot1->SetFillColor(kRed);
  dot1->SetFillStyle(1001);
  dot2->SetFillColor(kRed);
  dot2->SetFillStyle(1001);
  dot3->SetFillColor(kRed);
  dot3->SetFillStyle(1001);
  dot4->SetFillColor(kRed);
  dot4->SetFillStyle(1001);
  dot5->SetFillColor(kBlue);
  dot5->SetFillStyle(1001);
  dot6->SetFillColor(kBlue);
  dot6->SetFillStyle(1001);
  dot7->SetFillColor(kBlue);
  dot7->SetFillStyle(1001);
  dot8->SetFillColor(kBlue);
  dot8->SetFillStyle(1001);
  dot9->SetFillColor(kBlue);
  dot9->SetFillStyle(1001);

  /******************************/
  /* Overplot foreground images */
  /******************************/
  int imagenumber = 1;
  while(imagenumber < (int)tasimages.size())
  {
    for(int j=0; j<(int)pads[1].size(); j++)
    {
      pads[1][j]->cd();
      tasimages[imagenumber][j]->Draw("X");
      can->cd();
    }

    /********************/
    /* Draw test points */
    /********************/
    CanPad->Draw("same");
    CanPad->cd();
    dot1->Draw("same");
    dot2->Draw("same");
    dot3->Draw("same");
    dot4->Draw("same");
    dot5->Draw("same");
    dot6->Draw("same");
    dot7->Draw("same");
    dot8->Draw("same");
    dot9->Draw("same");
    can->cd();

    /*********************/
    /* Save plot to file */
    /*********************/
    if((imagenumber == 2) || (imagenumber == 3) || (imagenumber == 4))
      can->Print(filename.c_str());

    /**********************/
    /* Update imagenumber */
    /**********************/
    imagenumber++;
  }

  /*********************/
  /* Save plot to file */
  /*********************/
  filename = "TestGraphic.gif++";
  //can->Print(filename.c_str());

  return;
}

void IncidenceAngleAnalysis_Plot::Visualization1(vector <double> &selected_angles, vector <ImageSets> &imagesets, vector <Images> &images, vector <IncidenceAngles> &incidenceangles)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  string imdir;

  // Hard coded for now
  imdir = "/Users/MRichardson/Desktop/Incidence_Angle_Analysis/images/";
  
  for (int i = 0; i < (int)selected_angles.size(); i++) {
    PlotRealMasterImage(imdir, selected_angles[i], incidenceangles, imagesets, images);
    /*for (int j = 0; j < (int)selected_angles.size(); j++) {
      if(i == j)
	continue;
      PlotRealMasterImage(imdir, selected_angles[i], incidenceangles, imagesets, images, selected_angles[j]);
      }*/
  }
}
