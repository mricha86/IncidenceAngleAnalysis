/* HEADER FILE: AuxilaryFunctions.h */

#ifndef AUXILARYFUNCTIONS_H
#define AUXILARYFUNCTIONS_H

// Custom definitions
#define quit exit(0);

// Included libraries
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*********************/
/* Generic functions */
/*********************/
template <typename T>
inline std::vector < std::vector <T> > mat2vec(boost::numeric::ublas::matrix <T> &m)
{
  /**************/
  /* Dimensions */
  /**************/
  unsigned cols = m.size2();
  unsigned rows = m.size1();

  /**************************/
  /* 2D vector construction */
  /**************************/
  std::vector < std::vector <T> > v (cols, std::vector <T> (rows));
  for(unsigned i = 0; i < cols; i++)
    for(unsigned j = 0; j < rows; j++)
       v[i][j] = m(j, i);

  return v;
}

template <typename T>
inline boost::numeric::ublas::matrix <T> vec2mat(std::vector < std::vector <T> > & v)
{
  /**************/
  /* Dimensions */
  /**************/
  unsigned cols = v.size();
  unsigned rows = v[0].size();
  
  /***********************/
  /* Matrix construction */
  /***********************/
  boost::numeric::ublas::matrix <T> m (rows, cols);
  for(unsigned i = 0; i < m.size1(); i++)
    for(unsigned j = 0; j < m.size2(); j++)
      m(i, j) = v[j][i];

  return m;
}

template <typename T>
inline std::vector < std::vector <T> > vec2dtrans(std::vector < std::vector <T> > & v)
{
  /*********************/
  /* Convert to matrix */
  /*********************/
  boost::numeric::ublas::matrix <T> m = vec2mat(v);
  
  /****************************/
  /* Perform matrix transpose */
  /****************************/
  boost::numeric::ublas::matrix <T> M = boost::numeric::ublas::trans(m);

  return mat2vec(M);
}

template <typename T>
inline void TransposeVector2D(vector < vector <T> > &v)
{
  /***********************************/
  /* Create temporary copy of vector */
  /***********************************/
  vector < vector <T> > temp = v;

  /*************************************/
  /* Swap dimensions of orginal vector */
  /*************************************/
  int cols = (int)v.size();
  int rows = (int)v[0].size();
  v.resize(rows);
  for(int i = 0; i < (int)v.size(); i++)
  v[i].resize(cols);

  /*********************/
  /* Execute transpose */
  /*********************/
  v = vec2dtrans(temp);
}

inline bool is_double(string const & str) 
{
    double result;
    istringstream i (str);
    if(!(i >> result))
      return false;
    return true;
}

inline bool is_integer(string const & str) 
{
    int result;
    istringstream i (str);
    if(!(i >> result))
      return false;
    return true;
}

inline constexpr unsigned int str2int(const char* str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

inline bool FileExists(string Filename) { 
  /***************************/
  /* Check existance of file */
  /***************************/
  ifstream InFile(Filename.c_str());
  if(InFile)
  { 
    InFile.close();
    return true; // If file exists
  }
  InFile.close();

  return false; // If file does not exist
}

inline bool FileExists(std::vector <string> Filenames) { 
  /*********************************************/
  /* Checks existance of filename in a vector. */
  /* If all files exists, return true else     */
  /* false.                                    */
  /*********************************************/
  for(int i = 0; i<(int)Filenames.size(); i++ ) {
    if(FileExists(Filenames[i]))
      continue;
    else
      return false; // One file does not exist
  }

  return true; // All files exist
}

template <typename T>
inline T Max(T a, T b) { return (a > b) ? a : b; }

template <typename T>
inline T Min(T a, T b) { return (a < b) ? a : b; }

template <typename T>
inline T ArrayAverage(unsigned n, T *arr) {
  T sum = 0;
  for(unsigned i=0; i<n; i++)
    if(!isnan(arr[i]))
      sum += arr[i];
  T avg = sum / n;
  
  return avg;
}

template <typename T>
inline T ArrayMaximum(unsigned n, T *arr) {
  T max = arr[0];
  for(unsigned i=1; i<n; i++)
    if(!std::isnan(arr[i]))
      max = Max(max, arr[i]);
  
  return max;
}

template <typename T>
inline T ArrayMinimum(unsigned n, T *arr) {
  T min = arr[0];
  for(unsigned i=1; i<n; i++)
    if(!isnan(arr[i]))
      min = Min(min, arr[i]);
  
  return min;
}

template <typename T>
inline T ArraySum(unsigned n, T *arr) {
  T sum = 0;
  for(unsigned i=0; i<n; i++)
    if(!isnan(arr[i]))
      sum += arr[i];
  
  return sum;
}

template <typename T>
inline T * ArrayDifference(unsigned n, T *arr1, T *arr2) {
  vector <T> diff(n);
  for(unsigned i=0; i<n; i++)
    if(!isnan(arr1[i]) && !isnan(arr2[i]))
      diff[i] = arr1[i] - arr2[i];
  
  return diff.data();
}

template <typename T>
inline T * ArraySum(unsigned n, T *arr1, T *arr2) {
  vector <T> sum(n);
  for(unsigned i=0; i<n; i++)
    if(!isnan(arr1[i]) && !isnan(arr2[i]))
      sum[i] = arr1[i] + arr2[i];
  
  return sum.data();
}

inline long unsigned int Factorial(int n) {
  if (n < 0) {
    std::cout << "Error in function FACTORIAL. Unable to compute factoral of: " << n << ".\nTerminating program ..." << std::endl;
    exit(EXIT_FAILURE);
  }
  
  if ((n == 0) || (n == 1)) 
      return 1;
  
  long unsigned int product = 1;
  for(int i=0; i<n-1; i++)
    product *= n-i;
  
  return product;
}

inline double MaxNearestMultiple(double n, double multiple) {
  if(multiple == 0)
    return n;
  
  double remainder = fmod(fabs(n),multiple);
  if(remainder == 0)
    return n;

  return (remainder < 0) ? n+remainder : n+multiple-remainder;
}

template <typename T>
inline void printVector(std::vector <T> const &v)
{
  for (unsigned i = 0; i < v.size(); i++)
    cout << v[i] << ' ';
  cout << endl;
}

template <typename T>
inline void printVector(std::vector <std::vector <T> > const &v, bool correct_orientation = false)
{
  if(correct_orientation) {
    for(unsigned i = 0; i < v[0].size(); i++) {
      for(unsigned j = 0; j < v.size(); j++)
	cout << v[j][i] << " ";
      cout << endl;
    }
  }
  else {
    cout << "Printing column vectors" << endl;
    for(unsigned i = 0; i < v.size(); i++) {
      for(unsigned j = 0; j < v[i].size(); j++)
	cout << v[i][j] << " ";
      cout << endl << "----------" << endl;
    }
  }
}

template <typename T>
inline void vswap(T &a, T &b)
{
  T c = a;
  a = b;
  b = c;
}

template<typename T>
inline std::vector <T> vectorLogarithm(std::vector <T> const &v, double base = 10.0)
{
  unsigned n = v.size();
  std::vector <T> sol(n);
  double factor = 1.0/log10(base);
  for(unsigned i = 0; i < n; i++)
    sol[i] = factor*log10(v[i]);
  return sol;
}

template<typename T>
inline std::vector <T> vectorMultiplication(std::vector <T> const &v, double d)
{
  unsigned n = v.size();
  std::vector <T> sol(n);
  for(unsigned i = 0; i < n; i++)
    sol[i] = d*v[i];
  return sol;
}

template<typename T>
inline std::vector <T> vectorSlice(std::vector <T> const &v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;

    std::vector<T> vec(first, last);
    return vec;
}

inline double RoundtoNearest(double val, double place)
{ 
  return floor(val/place + 0.5)*place;
}

#endif
