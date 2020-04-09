/* HEADER FILE: ReadAuxilaryData.h */

#ifndef READAUXILARYDATA_H
#define READAUXILARYDATA_H
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "AuxilaryFunctions.h"
#include "IncidenceAngles.h"
#include "Utilities.h"

class ReadAuxilaryData
{
  /**********************************/
  /* Declaration of class variables */
  /**********************************/
  private:
    std::string AuxilaryDataFile;
    std::vector <IncidenceAngles> incidenceangledata;

  /***********************************/
  /* Declaration of class functions */
  /***********************************/
  public:
    ReadAuxilaryData(std::string);
    std::vector <IncidenceAngles> GetIncidenceAngleData();
    void Read();
    static void DisplayData(std::vector <double> &);
    static void DisplayData(std::vector <IncidenceAngles> &);
};

#endif
