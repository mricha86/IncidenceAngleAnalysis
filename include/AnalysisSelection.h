/* HEADER FILE: AnalysisSelection.h */

#ifndef ANALYSISSELECTION_H
#define ANALYSISSELECTION_H
/* Included librariers */
#include <map>
#include <string>

#include "AuxilaryFunctions.h"
#include "Checkpoint.h"
#include "Constants.h"
#include "DataPreparation.h"
#include "DataRetrieval.h"
#include "Images.h"
#include "ImageSets.h"
#include "IncidenceAngles.h"
#include "Marks.h"
#include "OverlappedImages.h"
#include "Plot.h"
#include "Utilities.h"

class AnalysisSelection {
  public:
    static std::map <int, vector <string> > Selector(int, char *[]);
    static void Execute(std::map <int, std::vector <std::string> >);
    static void ReadyData(Checkpoint &, std::vector <std::string> &, std::vector <ImageSets> &, std::vector <Images> &, std::vector <Marks> &, std::vector <IncidenceAngles> &);
    static void Usage(std::string);
};

#endif
