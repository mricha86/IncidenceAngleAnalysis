/* HEADER FILE: LeastSquares.h */

#ifndef LEASTSQUARES_H
#define LEASTSQUARES_H
#include <iomanip>
#include <iostream>
#include <limits>
#include <math.h>
#include <string>
#include <vector>

#include "AuxilaryFunctions.h"
#include "Constants.h"
#include "RandGen.h"
#include "Utilities.h"

class LeastSquares
{
  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  private:
    double (LeastSquares::*GeneralFunction)(double, double *);
    double chiSquare;
    int methodselection;
    int modelselection;
    int ndatapoints;
    int ndatatablecolumns;
    int ndatatablerows;
    int niterations;
    int nparameters;
    std::string methodname;
    std::vector <double> delta_parameter;
    std::vector <double> mean_vector;
    std::vector <double> model;
    std::vector <double> parameters;
    std::vector <double> sigma;
    std::vector <double> x_data;
    std::vector <double> y_data;
    std::vector < std::vector <double> > covariance_matrix;
    std::vector < std::vector <double> > data_table;
    std::vector < std::vector <double> > deviation_vector;
    void (LeastSquares::*GeneralMethod)(int, std::vector <double> &, std::vector <double> &, double &);
  
  public:
    LeastSquares();
    LeastSquares(const std::vector <double> &, const std::vector <double> &, const std::vector <double> & = std::vector <double> ());
    double CalculateChiSquare();
    double CommonLogarithmFunction(double, double *);
    double ExponentialFunction(double, double *);
    double GaussianDistribution(double, double *);
    double GetChiSquare();
    double LinearFunction(double, double *);
    double NaturalLogarithmFunction(double, double *);
    double Polynomial(double, double *);
    double PoissonDistribution(double, double *);
    double PowerLaw(double, double *);
    double YFunction(double, double *);
    int GetModelselection();
    int GetNdatapoints();
    int GetNiterations();
    int GetNparameters(); 
    std::vector <double> GetDelta_parameter();
    std::vector <double> GetMean_vector();
    std::vector <double> GetModel();
    std::vector <double> GetParameters();
    std::vector <double> GetSigma();
    std::vector <double> GetX_data();
    std::vector <double> GetY_data();
    std::vector <int> SelectRandomIndicies();
    std::vector < std::vector <double> > GetCovariance_matrix();
    std::vector < std::vector <double> > GetData_table();
    void CalculateGradient(double &, double &, std::vector <double> &);
    void ChangeParameterDeltaValue(int, double = 0);
    void ChangeParameterValue(int, double = 0);
    void ChooseMethod();
    void ChooseModel();
    void ComputeCovarianceMatrix();
    void ComputeDeviationVector();
    void ComputeMeanVector();
    void FillModelVector();
    void Fit(int, int, double &, std::vector <double> &, std::vector <double> &);
    void Fit(int, int, double &, std::vector <double> &, std::vector <double> &, std::vector <double> &);
    void LeastSquaresGradientSearch(int, std::vector <double> &, std::vector <double> &, double &);
    void LeastSquaresGridSearch(int, std::vector <double> &, std::vector <double> &, double &);
    void Method(int, std::vector <double> &, std::vector <double> &, double &);
    void SetData_table(std::vector < std::vector <double> > &);
    void SetNparameters(int);
    static void OrdinaryLeastSquares(std::vector <double> &, std::vector <double> &, double &, double &, double &, double &);
    static void Test();
};

#endif
