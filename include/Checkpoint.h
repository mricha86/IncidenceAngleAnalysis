/* HEADER FILE: Checkpoint.h */

#ifndef CHECKPOINT_H
#define CHECKPOINT_H
#include <mach/clock.h>
#include <mach/mach.h>
#include <string>

class Checkpoint
{
  /***********************************/
  /* Declaration of class variables */
  /***********************************/
  private:
    static const double NanoConverter; // Nano seconds to seconds
    double start_time;
    double time_later1;
    double time_later2;
    int ncheckpoints;
    timespec ts;

  /**********************************/
  /* Declaration of class functions */
  /**********************************/
  public:
    Checkpoint();
    void ElapsedTime(std::string);
    void GetMacTime();
    void Interpreter(double &);
    void TotalElapsedTime();
};

#endif
