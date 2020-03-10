#include "LeastSquares.h"
/* Procedure outlined at https://sites.math.washington.edu/~conroy/m112-general/leastSquaresExample */
/* https://en.wikipedia.org/wiki/Linear_least_squares#Example */

using namespace std;

LeastSquares::LeastSquares()
{
}

LeastSquares::LeastSquares(const vector <double> &x, const vector <double> &y, const vector <double> &s)
{
  /****************************************/
  /* Verify and obtain number of elements */
  /****************************************/
  if(x.size() == y.size())
    ndatapoints = (int)x.size();
  else
  {
    cout << "Data array sizes differ\n Terminating program..." << endl;
    exit(1);
  }

  /***********************/
  /* Retrieve parameters */
  /***********************/
  x_data = x;
  y_data = y;
  if(!s.empty())
    sigma = s;
  else
    sigma.assign(ndatapoints, 1.0);
  
  /************************/
  /* Initialize variables */
  /************************/
  modelselection = 0;
  niterations = 0;
  nparameters = 0;
}

double LeastSquares::CalculateChiSquare()
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double ChiSquare = 0;

  /************************/
  /* Calculate chi square */
  /************************/
  for(int i=0; i<ndatapoints; i++)
    ChiSquare += (y_data[i]-model[i])*(y_data[i]-model[i])/pow(sigma[i], 2.0);

  /*************************************/
  /* Increase the number of iterations */
  /*************************************/
  niterations++;
  
  return ChiSquare;
}

double LeastSquares::CommonLogarithmFunction(double x, double *params)
{
  /***********************/
  /* Retrieve parameters */
  /***********************/
  double a = params[0];

  /*******************/
  /* Return function */
  /*******************/
  return a*log10(x);
}

double LeastSquares::ExponentialFunction(double x, double *params)
{
  /***********************/
  /* Retrieve parameters */
  /***********************/
  double a = params[0];

  /*******************/
  /* Return function */
  /*******************/
  return a*exp(x);
}

double LeastSquares::GaussianDistribution(double x, double *params)
{
  /***********************/
  /* Retrieve parameters */
  /***********************/
  double mu = params[0];
  double sd = params[1];

  /***************************/
  /* Function simplification */
  /***************************/
  double variance = sd*sd;
  double amplitude = pow(2.0*M_PI*variance, -0.5);
  double numerator = (x-mu)*(x-mu);
  double denominator = 2.0*variance;

  /*******************/
  /* Return function */
  /*******************/
  return amplitude*exp(numerator/denominator);
}

double LeastSquares::GetChiSquare()
{
  return chiSquare;
}

double LeastSquares::LinearFunction(double x, double *params)
{
  /***********************/
  /* Retrieve parameters */
  /***********************/
  double b = params[1];
  double m = params[0];

  /*******************/
  /* Return function */
  /*******************/
  return m*x+b;
}

double LeastSquares::NaturalLogarithmFunction(double x, double *params)
{
  /***********************/
  /* Retrieve parameters */
  /***********************/
  double a = params[0];

  /*******************/
  /* Return function */
  /*******************/
  return a*log(x);
}

double LeastSquares::PoissonDistribution(double x, double *params)
{
  /***********************/
  /* Retrieve parameters */
  /***********************/
  int k = static_cast<int>(x);
  double lambda = params[0];

  /*******************/
  /* Return function */
  /*******************/
  return pow(lambda, k)*exp(-lambda)/Factorial(k);
}

double LeastSquares::Polynomial(double x, double *params)
{
  /******************/
  /* Build function */
  /******************/
  double y = 0;
  for(int i=0; i<nparameters; i++)
    y += params[i]*pow(x, i);
  
  /*******************/
  /* Return function */
  /*******************/
  return y;
}

double LeastSquares::PowerLaw(double x, double *params)
{
  /***********************/
  /* Retrieve parameters */
  /***********************/
  double a = params[1];
  double k = params[0]; 

  /*******************/
  /* Return function */
  /*******************/
  return a*pow(x, -k);
}

double LeastSquares::YFunction(double x, double *params)
{
  return (this->*GeneralFunction)(x, params);
}

int LeastSquares::GetModelselection()
{
  return modelselection;
}

int LeastSquares::GetNdatapoints()
{
  return ndatapoints;
}

int LeastSquares::GetNiterations()
{
  return niterations;
}

int LeastSquares::GetNparameters()
{
  return nparameters;
}

vector <double> LeastSquares::GetDelta_parameter()
{
  return delta_parameter;
}

vector <double> LeastSquares::GetMean_vector()
{
  return mean_vector;
}

vector <double> LeastSquares::GetModel()
{
  return model;
}

vector <double> LeastSquares::GetParameters()
{
  return parameters;
}

vector <double> LeastSquares::GetSigma()
{
  return sigma;
}

vector <double> LeastSquares::GetX_data()
{
  return x_data;
}

vector <double> LeastSquares::GetY_data()
{
  return y_data;
}

vector < vector <double> > LeastSquares::GetCovariance_matrix()
{
  return covariance_matrix;
}

vector < vector <double> > LeastSquares::GetData_table()
{
  return data_table;
}

void LeastSquares::CalculateGradient(double &chiSquare1, double &chiSquare2, vector <double> &Gradient)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  double frac;
  double sum;
  vector <double> grad(nparameters);

  /*****************************/
  /* Calculation of chi-square */
  /*****************************/
  chiSquare2 = CalculateChiSquare();
  
  frac = 1.0E-3;
  sum = 0;
  for(int i=0; i<nparameters; i++)
  {
    /**************************/
    /* Calculate differential */
    /**************************/
    double differential = frac*delta_parameter[i];

    /******************************/
    /* Change ith parameter value */
    /******************************/
    ChangeParameterValue(i, differential);

    /****************************/
    /* Recalculate model values */
    /****************************/
    FillModelVector();
    
    /**************************/
    /* Recalculate chi-square */
    /**************************/
    chiSquare1 = CalculateChiSquare();

    /******************************/
    /* Change ith parameter value */
    /******************************/
    ChangeParameterValue(i, -1.0*differential);

    /****************************************/
    /* Calculate gradient for ith parameter */
    /****************************************/
    grad[i] = chiSquare2-chiSquare1;

    /*************************************/
    /* Calculate sum of gradient squared */
    /*************************************/
    sum += grad[i]*grad[i];
  }

  for(int i=0; i<nparameters; i++)
    grad[i] = delta_parameter[i]*grad[i]/(sum*sum);
  Gradient = grad;
  
  return;
}


void LeastSquares::ChangeParameterDeltaValue(int index, double delta)
{
  delta_parameter[index] = (delta == 0) ? -1.0*delta_parameter[index] : delta;
}

void LeastSquares::ChangeParameterValue(int index, double delta)
{
  parameters[index] += (delta == 0) ? delta_parameter[index] : delta;
}

void LeastSquares::ChooseMethod()
{
  /********************************/
  /* Set function to use as model */
  /********************************/
  switch(methodselection)
  {
    case 1:
      GeneralMethod = &LeastSquares::LeastSquaresGradientSearch;
      methodname = "gradient search";
      break;
    case 2:
      GeneralMethod = &LeastSquares::LeastSquaresGridSearch;
      methodname = "grid search";
      break;
  }
  
  return;
}

void LeastSquares::ChooseModel()
{
  /********************************/
  /* Set function to use as model */
  /********************************/
  switch(modelselection)
  {
    case 1:
      GeneralFunction = &LeastSquares::CommonLogarithmFunction;
      break;
    case 2:
      GeneralFunction = &LeastSquares::ExponentialFunction;
      break;
    case 3:
      GeneralFunction = &LeastSquares::GaussianDistribution;
      break;
    case 4:
      GeneralFunction = &LeastSquares::LinearFunction;
      break;
    case 5:
      GeneralFunction = &LeastSquares::NaturalLogarithmFunction;
      break;
    case 6:
      GeneralFunction = &LeastSquares::PoissonDistribution;
      break;
    case 7:
      GeneralFunction = &LeastSquares::Polynomial;
      break;
    case 8:
      GeneralFunction = &LeastSquares::PowerLaw;
      break;
  }
  nparameters = (int)parameters.size();
  ndatatablecolumns = 1+nparameters;
  
  return;
}

void LeastSquares::ComputeCovarianceMatrix()
{
  /********************************/
  /* Number of rows in data table */
  /********************************/
  ndatatablerows = (int)data_table.size();

  /*************************/
  /* Calculate mean vector */
  /*************************/
  ComputeMeanVector();

  /******************************/
  /* Calculate deviation vector */
  /******************************/
  ComputeDeviationVector();

  /*******************************/
  /* Calculate covariance matrix */
  /*******************************/
  vector < vector <double> > cov(nparameters, vector <double> (nparameters, 0.0));
  for(int i=0; i<nparameters; i++)
    for(int j=i; j<nparameters; j++)
    {
      double sum = 0.0;
      for(int k=0; k<ndatatablerows; k++)
      {
	sum += deviation_vector[k][i]*deviation_vector[k][j];
      }
      cov[i][j] = cov[j][i] = sum/(ndatatablerows-1.0);
    }
  covariance_matrix = cov;
}

void LeastSquares::ComputeDeviationVector()
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  vector < vector <double> > deviations(ndatatablerows, vector <double> (nparameters, 0.0));

  for(int i=0; i<ndatatablerows; i++)
  {
    for(int j=0; j<nparameters; j++)
    {
      deviations[i][j] = data_table[i][j]-mean_vector[j];
    }
  }
  deviation_vector = deviations;
}

void LeastSquares::ComputeMeanVector()
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  vector <double> means(nparameters, 0.0);

  for(int i=0; i<ndatatablerows; i++)
  {
    for(int j=0; j<nparameters; j++)
    {
      means[j] += data_table[i][j];
    }
  }
  for(int j=0; j<nparameters; j++)
    means[j] /= ndatatablerows;
  mean_vector = means;
}

void LeastSquares::FillModelVector()
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  vector <double> m(ndatapoints);
  
  /******************************************************/
  /* Populate model with estimates of y values of model */
  /******************************************************/
  for(int i=0; i<ndatapoints; i++)
    m[i] = YFunction(x_data[i], parameters.data());
  
  /****************/
  /* Record model */
  /****************/
  model = m;

  return;
}

void LeastSquares::Fit(int method, int modelchoice, vector <double> &params, vector <double> &stepsizes, double &stepDown)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double epsilon = 1.0E-12;
  
  /************************************************/
  /* Clears data table and sets number of columns */
  /************************************************/
  data_table.clear();

  /*******************************/
  /* Select least squares method */
  /*******************************/
  methodselection = method;
  ChooseMethod();   
  
  /************************************/
  /* Initialize least squares routine */
  /************************************/
  Method(modelchoice, params, stepsizes, stepDown);
  double cs_old = GetChiSquare();
  vector <double> params_before = params;
  vector <double> stepsizes_before = stepsizes;
  
  /********************************/
  /* Determine minimum chi square */
  /********************************/
  while(true)
  {
    /************************/
    /* Calculate chi square */
    /************************/
    Method(modelchoice, params, stepsizes, stepDown);
    double cs_new = GetChiSquare();
    double cs_diff = fabs(cs_old-cs_new);
    vector <double> params_after = params;
    vector <double> stepsizes_after = stepsizes;
    
    /***********************************/
    /* Ensure chi square is decreasing */
    /***********************************/
    if(cs_new > cs_old)
    {
      /*************************************************************/
      /* Determine which parameter experienced the greatest change */
      /*************************************************************/
      int index_greatestChange = 0;
      double greatestChange = 0;
      for(int i=0; i<GetNparameters(); i++)
      {
    	double param_diff = params_after[i]-params_before[i];
    	if(fabs(param_diff) > fabs(greatestChange))
    	{
    	  index_greatestChange = i;
    	  greatestChange = param_diff;
    	}
      }
      
      /********************************************************************/
      /* Modify parameter with greatest change and recalculate chi square */
      /********************************************************************/
      for(int i=0; i<(int)params.size(); i++)
      {
    	params[i] = (i == index_greatestChange) ? params_before[i]-greatestChange : params_after[i];
    	stepsizes[i] = (i == index_greatestChange) ? stepsizes_before[i] : stepsizes_after[i];
      }
      
      /********************************/
      /* Rerun chi square calculation */
      /********************************/
      continue;
    }

    /***********************************/
    /* Exit loop when chi square has a */ 
    /* difference less than epsilon    */
    /***********************************/
    if(cs_diff <= epsilon)
      break;
    else
    {
      cs_old = cs_new;
      params_before = params_after;
      stepsizes_before = stepsizes_after;
    }
  }

  /*******************************/
  /* Calculate covariance matrix */
  /*******************************/
  ComputeCovarianceMatrix();

  return;
}

void LeastSquares::LeastSquaresGradientSearch(int modelchoice, vector <double> &params, vector <double> &stepsizes, double &stepDown)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  double chiSquare1;
  double chiSquare2;  
  double chiSquare3;
  double stepSum;
  vector <double> gradient;  

  /***********************************/
  /* Initialize important parameters */
  /***********************************/
  niterations = 0;
  modelselection = modelchoice;
  parameters = params;
  delta_parameter = stepsizes;
  
  /***********************************/
  /* Choose model (fitting function) */
  /***********************************/
  ChooseModel();

  /***************************************/
  /* Initial calculation of model values */
  /***************************************/
  FillModelVector();
  
  /***************************/
  /* Calculate the gradients */
  /***************************/
  CalculateGradient(chiSquare1, chiSquare2, gradient);

  do
  { 
    /******************************/
    /* Change ith parameter value */
    /******************************/
    for(int i=0; i<nparameters; i++)
      ChangeParameterValue(i, stepDown*gradient[i]);

    /****************************/
    /* Recalculate model values */
    /****************************/
    FillModelVector();

    /**************************/
    /* Recalculate Chi Square */
    /**************************/
    chiSquare3 = CalculateChiSquare();

    if(chiSquare3 >= chiSquare2)
    {
      /******************************/
      /* Change ith parameter value */
      /******************************/
      for(int i=0; i<nparameters; i++)
	ChangeParameterValue(i, -1.0*stepDown*gradient[i]);

      /**********************/
      /* Decrease step size */
      /**********************/
      stepDown /= 2.0;
    }
  } while(chiSquare3 > chiSquare2);

  stepSum = 0;
  do
  {      
    /*************************************/
    /* Set stepSum and chi square points */
    /*************************************/
    stepSum += stepDown;
    chiSquare1 = chiSquare2;
    chiSquare2 = chiSquare3;

    /******************************/
    /* Change ith parameter value */
    /******************************/
    for(int i=0; i<nparameters; i++)
      ChangeParameterValue(i, stepDown*gradient[i]);
    
    /****************************/
    /* Recalculate model values */
    /****************************/
    FillModelVector();

    /**************************/
    /* Recalculate Chi Square */
    /**************************/
    chiSquare3 = CalculateChiSquare();
    
  } while(chiSquare3 < chiSquare2);

  /**************************************/
  /* Calculate minimum local chi square */
  /**************************************/
  double delta_chiSquare_1 = chiSquare3-chiSquare2;
  double delta_chiSquare_2 = chiSquare3-2.0*chiSquare2+chiSquare1;
  double new_parameter_delta = stepDown*(delta_chiSquare_1/delta_chiSquare_2+0.5);

  /******************************/
  /* Change ith parameter value */
  /******************************/
  for(int i=0; i<nparameters; i++)
    ChangeParameterValue(i, -1.0*new_parameter_delta*gradient[i]);

  /****************************/
  /* Recalculate model values */
  /****************************/
  FillModelVector();

  /********************************/
  /* Calculate minimum Chi Square */
  /********************************/
  chiSquare = CalculateChiSquare();

  /*********************/
  /* Change parameters */
  /*********************/
  params = parameters;
  
  /***************************/
  /* Change global step size */
  /***************************/
  stepDown = stepSum;
  
  return;
}

void LeastSquares::LeastSquaresGridSearch(int modelchoice, vector <double> &params, vector <double> &stepsizes, double &dummyVariable)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  double chiSquare1 = 0;
  double chiSquare2 = 0;  
  double chiSquare3 = 0;

  /***********************************/
  /* Initialize important parameters */
  /***********************************/
  modelselection = modelchoice;
  parameters = params;
  delta_parameter = stepsizes;
  dummyVariable = 0.5;
  
  /***********************************/
  /* Choose model (fitting function) */
  /***********************************/
  ChooseModel();
  
  /****************************************/
  /* Vector to record parameter selection */
  /* and corresponding chi square value   */
  /****************************************/
  vector <double> row(ndatatablecolumns);

  /***************************************/
  /* Initial calculation of model values */
  /***************************************/
  FillModelVector();
  
  /*************************************/
  /* Initial calculation of chi-square */
  /*************************************/
  chiSquare2 = CalculateChiSquare();

  /*****************************************/
  /* Find local minimum for each parameter */
  /* which in turn minimizes chi squared   */
  /* and yields the best fit               */
  /*****************************************/
  for(int i=0; i<nparameters; i++)
  {
    /******************************/
    /* Change ith parameter value */
    /******************************/
    ChangeParameterValue(i);

    /****************************/
    /* Recalculate model values */
    /****************************/
    FillModelVector();
    
    /**************************/
    /* Recalculate Chi Square */
    /**************************/
    chiSquare3 = CalculateChiSquare();

    /*********************************************************/
    /* Determine parameter change that minimizes Chi Squared */
    /*********************************************************/
    if(chiSquare3 > chiSquare2)
    {
      /************************************/
      /* Change ith parameter delta value */
      /************************************/
      ChangeParameterDeltaValue(i);

      /******************************/
      /* Change ith parameter value */
      /******************************/
      ChangeParameterValue(i);

      /**********************************/
      /* Swap chiSquare2 and chiSquare3 */
      /**********************************/
      double chiSquare_temp = chiSquare3;
      chiSquare3 = chiSquare2;
      chiSquare2 = chiSquare_temp;
    }
    
    /**********************************************************************/
    /* Calculate three chi square values to determine minimum of parabola */
    /**********************************************************************/
    do
    {
      /******************************/
      /* Change ith parameter value */
      /******************************/
      ChangeParameterValue(i);

      /****************************/
      /* Recalculate model values */
      /****************************/
      FillModelVector();
      
      /**************************/
      /* Recalculate Chi Square */
      /**************************/
      chiSquare1 = chiSquare2;
      chiSquare2 = chiSquare3;
      chiSquare3 = CalculateChiSquare();

      /***************/ 
      /* Record data */
      /***************/
      // for(int i=0; i<nparameters; i++)
      // 	row[i] = parameters[i];
      // row[ndatatablecolumns-1] = chiSquare3;
      // data_table.push_back(row);
    } while(chiSquare3 < chiSquare2);

    /********************************/
    /* Remove last data table entry */
    /********************************/
    //data_table.pop_back();

    /**************************************/
    /* Calculate minimum local chi square */
    /**************************************/
    double delta_chiSquare_1 = chiSquare2-chiSquare1;
    double delta_chiSquare_2 = chiSquare3-2.0*chiSquare2+chiSquare1;
    double new_parameter_delta = delta_parameter[i]*(delta_chiSquare_1/delta_chiSquare_2+1.5);

    /******************************/
    /* Change ith parameter value */
    /******************************/
    ChangeParameterValue(i, -1.0*new_parameter_delta);

    /****************************/
    /* Recalculate model values */
    /****************************/
    FillModelVector();

    /********************************/
    /* Calculate Minimum Chi Square */
    /********************************/
    chiSquare2 = CalculateChiSquare();
    
    /***************/ 
    /* Record data */
    /***************/
    for(int i=0; i<nparameters; i++)
      row[i] = parameters[i];
    row[ndatatablecolumns-1] = chiSquare2;
    data_table.push_back(row);
    
    /****************************************/
    /* Adjust step size (needs to be fixed) */
    /****************************************/
    double a = delta_chiSquare_2/2.0;
    double b = delta_chiSquare_1-a;
    double c = chiSquare1-chiSquare2;
    double discriminant = b*b-4.0*a*(c-2);
    if(discriminant > 0)
    {
      discriminant = sqrt(discriminant);
      double root = (-b-discriminant)/(2.0*a);
      double x1 = root*delta_parameter[i]+parameters[i]-2.0*delta_parameter[i];
      discriminant = b*b-4.0*a*c;
      if(discriminant > 0)
	discriminant = sqrt(discriminant);
      else
	discriminant = 0;
      root = (-b-discriminant)/(2.0*a);
      double x2 = root*delta_parameter[i]+parameters[i]-2.0*delta_parameter[i];

      /************************************/
      /* Change ith parameter delta value */
      /************************************/
      ChangeParameterDeltaValue(i, x1-x2);
    }
  }
  chiSquare = chiSquare2;

  /*****************************/
  /* Retrieve Parameter Values */
  /*****************************/
  params = parameters;

  /***********************************/
  /* Retrieve Parameter Delta Values */
  /***********************************/
  //stepsizes = delta_parameter;
  
  return;
}

void LeastSquares::SetData_table(vector < vector <double> > &DT)
{
  data_table = DT;
}

void LeastSquares::SetNparameters(int n)
{
  nparameters = n;
}

void LeastSquares::LeastSquaresLinear(vector <double> x, vector <double> y, double &slope, double &y_intercept)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  int nelements;
  double constant;
  double m;
  double b;

  /********************************************/
  /* Step 1: Determine the number of elements */
  /********************************************/
  if(x.size() == y.size())
    nelements = (int)x.size();
  else
  {
    cout << "Invalid array sizes: " << x.size() << " does not equal " << y.size() << endl;
    cout << "Terminating program..." << endl;
    exit(1);
  }
  
  /********************************************/
  /* Step 2: Determine the following products */
  /********************************************/
  vector <double> x_squared(nelements);
  vector <double> xy(nelements);
  vector <double> y_squared(nelements);
  for(int i=0; i<nelements; i++)
  {
    x_squared[i] = x[i]*x[i];
    xy[i] = x[i]*y[i];
    y_squared[i] = y[i]*y[i];
  }
    
  /************************************/
  /* Step 3: Solve the following sums */
  /************************************/
  vector <double> sum(5);
  sum[0] = ArraySum(y_squared.data(), nelements);
  sum[1] = ArraySum(xy.data(), nelements);
  sum[2] = ArraySum(y.data(), nelements);
  sum[3] = ArraySum(x_squared.data(), nelements);
  sum[4] = ArraySum(x.data(), nelements);
  
  /*************************************************************************/
  /* Step 4: Calculate the coefficients of the Mean Squared Error function */
  /*************************************************************************/
  vector <double> MSE_coefficient(6);
  constant = 1.0/nelements;
  MSE_coefficient[0] = constant*sum[0]; 
  MSE_coefficient[1] = -2.0*constant*sum[1]; // This term is multiplied by a factor of m (slope)
  MSE_coefficient[2] = -2.0*constant*sum[2]; // This term is multiplied by a factor of b (y-intercept)
  MSE_coefficient[3] = constant*sum[3]; // This term is multiplied by a factor of m^2 (slope squared)
  MSE_coefficient[4] = 2.0*constant*sum[4]; // This term is multiplied by a factor of mb (slope times y-intercept)
  MSE_coefficient[5] = 1.0; // This term is multiplied by a factor of b^2 (y-intercept squared)
  
  /***********************************************************/
  /* Step 5: Use partial derivates of the Mean Squared Error */
  /* function to determine the slope and y-intercept of fit  */
  /* line                                                    */
  /***********************************************************/

  /**************************************************/
  /* Step 5.1: Partial of MSE with respect to slope */
  /* Note: This derivative is set equal to zero     */
  /**************************************************/
  vector <double> MSE_partial_m_coefficient(3);
  MSE_partial_m_coefficient[0] = MSE_coefficient[1];
  MSE_partial_m_coefficient[1] = 2.0*MSE_coefficient[3]; // This term is multiplied by a factor of m (slope)
  MSE_partial_m_coefficient[2] = MSE_coefficient[4]; // This term is multiplied by a factor of b (y-intercept)
  
  /********************************************************/
  /* Step 5.2: Partial of MSE with respect to y-intercept */
  /* Note: This derivative is set equal to zero           */
  /********************************************************/
  vector <double> MSE_partial_y_intercept_coefficient(3);
  MSE_partial_y_intercept_coefficient[0] = MSE_coefficient[2];
  MSE_partial_y_intercept_coefficient[1] = MSE_coefficient[4]; // This term is multiplied by a factor of m (slope)
  MSE_partial_y_intercept_coefficient[2] = 2.0; // This term is multiplied by a factor of b (y-intercept)
  
  /**********************************************************/
  /* Step 6: Solve for coefficients of y-intercept equation */
  /**********************************************************/
  vector <double> y_intercept_coefficient(2);
  y_intercept_coefficient[0] = -0.5*MSE_partial_y_intercept_coefficient[0];
  y_intercept_coefficient[1] = -0.5*MSE_partial_y_intercept_coefficient[1]; //This term is multiplied by a factor of m (slope)
  
  /***************************/
  /* Step 7: Solve for slope */
  /***************************/
  vector <double> m_coefficient(2);
  m_coefficient[0] = MSE_partial_m_coefficient[0]+MSE_partial_m_coefficient[2]*y_intercept_coefficient[0];
  m_coefficient[1] = MSE_partial_m_coefficient[1]+MSE_partial_m_coefficient[2]*y_intercept_coefficient[1];
  m = -1.0*m_coefficient[0]/m_coefficient[1];
  
  /*********************************/
  /* Step 8: Solve for y-intercept */
  /*********************************/
  b = y_intercept_coefficient[0]+y_intercept_coefficient[1]*m;
  
  /********************************/
  /* Record slope and y-intercept */
  /********************************/
  slope = m;
  y_intercept = b;
  
  return;
}

void LeastSquares::Method(int modelchoice, vector <double> &params, vector <double> &stepsizes, double &stepDown)
{
  (this->*GeneralMethod)(modelchoice, params, stepsizes, stepDown);
}

void LeastSquares::Test()
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  const double epsilon = 1.0E-6;
  double cs1;
  double sd;
  double slope;
  double yintercept;
  int modelchoice;
  int nchisquare_evaluations;
  vector <double> xpoints = {1, 2, 3, 4}; // Test Vector
  vector <double> ypoints = {6, 5, 7, 10}; // Test Vector
  vector <double> params = {100, 100};
  vector <double> params2 = {100, 100};
  vector <double> stepsizes = {0.01, 0.01};
  vector <double> stepsizes2 = {0.01, 0.01};
  
  /**************************************/
  /* Least Squares Linear Test Method 1 */
  /**************************************/
  LeastSquares::LeastSquaresLinear(xpoints, ypoints, slope, yintercept);
  cout << "Solution: slope = 1.4, y-intercept = 3.5" << endl;
  cout << "Simple linear regression yields: m = " << slope << ", y-intercept = " << yintercept << endl << endl;

  /**************************************/
  /* Least Squares Linear Test Method 2 */
  /**************************************/
  nchisquare_evaluations = 0;
  modelchoice = 4;
  LeastSquares Tester(xpoints, ypoints);
  Tester.LeastSquaresGridSearch(modelchoice, params, stepsizes, sd);
  nchisquare_evaluations += Tester.GetNiterations();
  cs1 = Tester.GetChiSquare();
  while(true)
  {
    /************************/
    /* Calculate chi square */
    /************************/
    Tester.LeastSquaresGridSearch(modelchoice, params, stepsizes, sd);
    nchisquare_evaluations += Tester.GetNiterations();
    double cs2 = Tester.GetChiSquare();
    double cs_diff = fabs(cs1-cs2);

    cout << "Solution: slope = 1.4, y-intercept = 3.5" << endl;
    cout << "Least Squares fit by the grid search method yields: m = " << params[0] << ", y-intercept = " << params[1] <<  ", chi-square = " << cs2 << endl;
    
    if(cs_diff < epsilon)
    {
      cout << endl;
      break;
    }
    else
      cs1 = cs2;
  }
  cout << "Grid search method total number of chi square evaluations: " << nchisquare_evaluations << endl << endl;
  
  /**************************************/
  /* Least Squares Linear Test Method 3 */
  /**************************************/
  nchisquare_evaluations = 0;
  sd = 0.5;
  Tester.LeastSquaresGradientSearch(modelchoice, params2, stepsizes2, sd);
  nchisquare_evaluations += Tester.GetNiterations();
  cs1 = Tester.GetChiSquare();
  while(true)
  {
    /************************/
    /* Calculate chi square */
    /************************/
    Tester.LeastSquaresGradientSearch(modelchoice, params2, stepsizes2, sd);
    nchisquare_evaluations += Tester.GetNiterations();
    double cs2 = Tester.GetChiSquare();
    double percent_diff = (cs1-cs2)/cs1;

    cout << "Solution: slope = 1.4, y-intercept = 3.5" << endl;
    cout << "Least Squares fit by the gradient search method yields: m = " << params2[0] << ", y-intercept = " << params2[1] <<  ", chi-square = " << cs2 << endl;
    
    if(percent_diff < epsilon)
    {
      cout << endl;
      break;
    }
    else
      cs1 = cs2;
  }
  cout << "Gradient search method total number of chi square evaluations: " << nchisquare_evaluations << endl << endl;
  
  return;
}

void LeastSquares::Test2()
{
  /*****************/
  /* Fake data set */
  /*****************/
  vector <vector <double> > mock_data(5, vector <double> (3));
  mock_data[0][0] = 4.0;
  mock_data[0][1] = 2.0;
  mock_data[0][2] = 0.60;
  mock_data[1][0] = 4.2;
  mock_data[1][1] = 2.1;
  mock_data[1][2] = 0.59;
  mock_data[2][0] = 3.9;
  mock_data[2][1] = 2.0;
  mock_data[2][2] = 0.58;
  mock_data[3][0] = 4.3;
  mock_data[3][1] = 2.1;
  mock_data[3][2] = 0.62;
  mock_data[4][0] = 4.1;
  mock_data[4][1] = 2.2;
  mock_data[4][2] = 0.63;

  /*****************************************************/
  /* Initialize an instance of the least squares class */
  /*****************************************************/
  LeastSquares Tester;

  /******************************************************/
  /* Set values for data table and number of parameters */
  /******************************************************/
  Tester.SetNparameters(3);
  Tester.SetData_table(mock_data);

  /*****************************/
  /* Compute covariance matrix */
  /*****************************/
  Tester.ComputeCovarianceMatrix();

  /*******************/
  /* Print mock data */
  /*******************/
  for(int i=0; i<(int)mock_data.size(); i++)
  {
    for(int j=0; j<(int)mock_data[i].size(); j++)
      cout << mock_data[i][j] << " ";
  cout << endl;
  }

  /*********************/
  /* Print mean vector */
  /*********************/
  vector <double> mv = Tester.GetMean_vector();
  for(int i=0; i<(int)mv.size(); i++)
    cout << mv[i] << " "; 
  cout << endl;
 
  /***************************/
  /* Print covariance matrix */
  /***************************/
  vector < vector <double> > cov = Tester.GetCovariance_matrix();
  for(int i=0; i<(int)cov.size(); i++)
  {
    for(int j=0; j<(int)cov[i].size(); j++)
      cout << cov[i][j] << " ";
    cout << endl;
  }

  return;
}
