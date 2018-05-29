/* HEADER FILE: ReadAuxilaryData.h */

#ifndef READAUXILARYDATA_H
#define READAUXILARYDATA_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "IncidenceAngles.h"
#include "MasterImageOrientation.h"
#include "PixelResolution.h"
#include "Utilities.h"

class ReadAuxilaryData
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    std::string AuxilaryDataFile;
    std::vector <IncidenceAngles> incidenceangledata;
    std::vector <MasterImageOrientation> masterimageorientationdata;
    std::vector <PixelResolution> pixelresolutiondata;

  /***********************************/
  /* Declaration of class functions */
  /***********************************/
  public:
    ReadAuxilaryData(std::string);
    std::vector <IncidenceAngles> GetIncidenceAngleData();
    std::vector <MasterImageOrientation> GetMasterImageOrientationData();
    std::vector <PixelResolution> GetPixelResolutionData();
    void Read();
    static void Display(std::vector <IncidenceAngles> &);
    static void Display(std::vector <MasterImageOrientation> &);
    static void Display(std::vector <PixelResolution> &);
};

#endif
