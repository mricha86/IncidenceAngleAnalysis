/* Purpose: Main function used to execute incidence angle analysis.
   Analysis studies the affect of solar incidence angle on the 
   general publics ability to identify and measure craters in 
   images of the lunar surface. All images used in analysis were
   acquired by the Lunar Reconaissance Orbiter (LRO). */

// Included libraries
#include <stdlib.h>
#include <vector>

#include "AnalysisSelection.h"

using namespace std;

int main(int argc, char *argv[])
{
  /*******************************************/
  /* Declaration/Initialization of variables */
  /*******************************************/
  map <int, vector <string> > selection;

  /**********************/
  /* Analysis selection */
  /**********************/
  selection  = AnalysisSelection::Selector(argc, argv);
  
  /*****************************/
  /* Execute selected analysis */
  /*****************************/
  AnalysisSelection::Execute(selection);
  
  return 0;
}
