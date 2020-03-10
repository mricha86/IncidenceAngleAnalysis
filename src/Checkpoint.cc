#include "Checkpoint.h"

using namespace std;

const double Checkpoint::NanoConverter= 1.0E-9;

Checkpoint::Checkpoint()
{
  /********************/
  /* Initialize timer */
  /********************/
  GetMacTime();

  /****************/
  /* Store result */
  /****************/
  Interpreter(start_time);

  /*********************************/
  /* Initialize checkpoint counter */
  /*********************************/
  ncheckpoints = 0;
}

void Checkpoint::ElapsedTime(string statement)
{
  /******************/
  /* Get clock time */
  /******************/
  GetMacTime();

  /************************************************/
  /* Calculate elapsed time since last checkpoint */
  /************************************************/
  if(ncheckpoints == 0)
  {
    Interpreter(time_later1);
    printf("%s %lf seconds\n", statement.c_str(), (time_later1-start_time));
    ncheckpoints++;
  }
  else
  {
    Interpreter(time_later2);
    printf("%s %lf seconds\n", statement.c_str(), (time_later2-time_later1));
    time_later1 = time_later2;
    ncheckpoints++;
  }

  return;
}

void Checkpoint::GetMacTime()
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  clock_serv_t cclock;
  mach_timespec_t mts;

  /*****************************************/
  /* Get time using Mac built-in functions */
  /*****************************************/
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts.tv_sec = mts.tv_sec;
  ts.tv_nsec = mts.tv_nsec;
}

void Checkpoint::Interpreter(double &current_time)
{
  /*******************************************************************/
  /* Convert most recent call to clock_gettime into units of seconds */
  /*******************************************************************/
  current_time = ts.tv_sec+(NanoConverter*ts.tv_nsec);

  return;
}

void Checkpoint::TotalElapsedTime()
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  string statement;

  /******************/
  /* Get clock time */
  /******************/
  GetMacTime();
  
  /********************************/
  /* Calculate total elapsed time */
  /********************************/
  Interpreter(time_later1);
  statement = "Elapsed time since start of program:";
  printf("%s %lf seconds\n", statement.c_str(), (time_later1-start_time));
  ncheckpoints++;

  return;
}
