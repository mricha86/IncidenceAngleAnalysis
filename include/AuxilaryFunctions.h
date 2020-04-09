/* HEADER FILE: AuxilaryFunctions.h */

#ifndef AUXILARYFUNCTIONS_H
#define AUXILARYFUNCTIONS_H
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*********************/
/* Generic functions */
/*********************/
inline constexpr unsigned int str2int(const char* str, int h = 0)
{
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

inline bool FileExists(vector <string> Filenames) { 
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
inline T ArrayMaximum(T *arr, int n) {
  T max = arr[0];
  for(int i=1; i<n; i++)
    if(!std::isnan(arr[i]))
      max = Max(max, arr[i]);
  
  return max;
}

template <typename T>
inline T ArrayMinimum(T *arr, int n) {
  T min = arr[0];
  for(int i=1; i<n; i++)
    if(!isnan(arr[i]))
      min = Min(min, arr[i]);
  
  return min;
}

template <typename T>
inline T ArraySum(T *arr, int n) {
  T sum = 0;
  for(int i=0; i<n; i++)
    sum += arr[i];
  
  return sum;
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

template<typename T>
inline void printVector(std::vector<T> const &v)
{
    for (auto i: v) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

template<typename T>
inline std::vector<T> vectorSlice(std::vector<T> const &v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;

    std::vector<T> vec(first, last);
    return vec;
}

#endif
