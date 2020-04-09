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
  string buffer;
  string format;

  /*****************/
  /* Retrieve file */
  /*****************/
  if(FileExists(AuxilaryDataFile))
    InFile.open(AuxilaryDataFile.c_str());
  else
  {
    printf("Error in function ReadAuxilaryData::Read(): File %s does not exist! Now terminating simulation ...\n", AuxilaryDataFile.c_str());
    exit(EXIT_FAILURE);
  }

  /*********************/
  /* Read-in data file */
  /*********************/
  format = "%s %lf";
  while(getline(InFile, buffer))
  {
    char str[250];
    double d1;
    int nelements = sscanf(buffer.c_str(), format.c_str(), str, &d1);
    if(nelements == 2)
    { 
      IncidenceAngles myDatapoint1(static_cast<string>(str), d1);
      incidenceangledata.push_back(myDatapoint1);
    }
  }
  InFile.close();
}
