#include "ReadAuxilaryData.h"

using namespace std;

ReadAuxilaryData::ReadAuxilaryData(string AUXILARYDATAFILE)
{
  /*********************/
  /* Retrieve filename */
  /*********************/
  AuxilaryDataFile = AUXILARYDATAFILE;
}

vector <IncidenceAngles> ReadAuxilaryData::GetIncidenceAngleData()
{
  return incidenceangledata;
}

void ReadAuxilaryData::DisplayData(vector <double> &list)
{
  /********************/
  /* Print header row */
  /********************/
  cout << setprecision(0) << setw(15) << left << "Incidence_Angle" << endl;
  
  /********************/
  /* Print data rows */
  /********************/
  for(int i=0; i<(int)list.size(); i++)
    cout << setprecision(4) << setw(15) << left << list[i] << endl;
  
  return;
}

void ReadAuxilaryData::DisplayData(vector <IncidenceAngles> &list)
{
  /********************/
  /* Print header row */
  /********************/
  cout << setprecision(0) << setw(12) << left << "Name" << " ";
  cout << setprecision(0) << setw(15) << left << "Incidence_Angle" << endl;
    
  /********************/
  /* Print data rows */
  /********************/
  for(int i=0; i<(int)list.size(); i++)
    cout << setprecision(0) << setw(12) << left << list[i].GetName() << " " << setprecision(4) << setw(15) << left << list[i].GetIncidence_angle() << endl;

  return;
}

void ReadAuxilaryData::Read()
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  ifstream InFile;
  int n;
  string format;

  /***********************************/
  /* Request memory for data vectors */
  /***********************************/
  n = 26;
  vector <double> incidenceangles_value(n);
  vector <string> incidenceangles_name(n);

  /****************/
  /* Read in data */
  /****************/
  format = "%s %lf";
  Readcol::Read(AuxilaryDataFile, format, incidenceangles_name.data(), incidenceangles_value.data());
  for(int i = 0; i < n; i++) {
    IncidenceAngles myDatapoint1(incidenceangles_name[i], incidenceangles_value[i]);
    incidenceangledata.push_back(myDatapoint1);
  }
}
