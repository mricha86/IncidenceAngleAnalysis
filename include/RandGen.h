/* HEADER FILE: RandGen.h */

#ifndef RANDGEN_H
#define RANDGEN_H
#include <random>

class RandGen
{
  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  private:
    std::mt19937_64 eng;
    unsigned seed;
    
  public:
    RandGen();
    RandGen(unsigned);
    double Norm_Dist(double = 0, double = 1);
    double Uniform_Dist(double = 0, double = 1);
    int Uniform_Dist(int = 1, int = 10);
};

#endif
