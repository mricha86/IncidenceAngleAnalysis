#include "RandGen.h"

using namespace std;

RandGen::RandGen()
{
  random_device r;
  mt19937_64 engine(r());
  eng = engine;
}

RandGen::RandGen(unsigned SEED)
{
  seed = SEED;
  mt19937_64 engine(seed);
  eng = engine;
}

int RandGen::Uniform_Dist(int a, int b)
{
  uniform_int_distribution <int> uniform_dist(a, b);
  return uniform_dist(eng);
}

double RandGen::Uniform_Dist(double a, double b)
{
  uniform_int_distribution <double> uniform_dist(a, b);
  return uniform_dist(eng);
}

double RandGen::Norm_Dist(double mean, double sigma)
{
  normal_distribution <> norm_dist(mean, sigma);
  return norm_dist(eng);
}
