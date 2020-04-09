/* HEADER FILE: DataPreparation.h */

/* Included libraries */
#include <string>
#include <vector>
#include "Checkpoint.h"
#include "Images.h"
#include "ImageSets.h"
#include "Marks.h"
#include "ProjectiveTransformation.h"
#include "RetrieveData.h"
#include "SortData.h"

class DataPreparation
{
  /******************************************/
  /* Declaration of class members/functions */
  /******************************************/
  private:
    std::vector <ImageSets> imss;
    std::vector <Images> ims;
    std::vector <Marks> mks;
  public:
    DataPreparation(std::vector <ImageSets> &, std::vector <Images> &, std::vector <Marks> &);
    static void ExecuteAuxilaryFunctions(std::vector <ImageSets> &, std::vector <Images> &, std::vector <Marks> &);
    static void ExecuteImagesAuxilaryFunction(std::vector <Images> &, std::vector <ImageSets> &);
    static void ExecuteImageSetsAuxilaryFunction(std::vector <ImageSets> &);
    static void ExecuteMarksAuxilaryFunction(std::vector <Marks> &, std::vector <Images> &);
};
