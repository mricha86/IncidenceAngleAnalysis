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

vector <MasterImageOrientation> ReadAuxilaryData::GetMasterImageOrientationData()
{
  return masterimageorientationdata;
}

vector <PixelResolution> ReadAuxilaryData::GetPixelResolutionData()
{
  return pixelresolutiondata;
}

void ReadAuxilaryData::Display(vector <IncidenceAngles> &list)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  int nelements;

  /********************/
  /* Print header row */
  /********************/
  printf("%-12s %-15s\n", "NAME", "Incidence_Angle");
  
  /********************/
  /* Print data rows */
  /********************/
  nelements = (int)list.size();
  for(int i=0; i<nelements; i++)
    printf("%-12s %-15.2lf\n", list[i].GetName().c_str(), list[i].GetIncidence_angle());

  return;
}

void ReadAuxilaryData::Display(vector <MasterImageOrientation> &list)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  int nelements;

  /********************/
  /* Print header row */
  /********************/
  printf("%-12s %-20s %-20s\n", "NAME", "Upper_Left_Latitude", "Upper_Left_Longitude");
  
  /********************/
  /* Print data rows */
  /********************/
  nelements = (int)list.size();
  for(int i=0; i<nelements; i++)
    printf("%-12s %-20s %-20s\n", list[i].GetName().c_str(), list[i].GetUpper_left_latitude().c_str(), list[i].GetUpper_left_longitude().c_str());

  return;
}

void ReadAuxilaryData::Display(vector <PixelResolution> &list)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  int nelements;

  /********************/
  /* Print header row */
  /********************/
  printf("%-12s %-20s %-20s\n", "NAME", "Vertical_Resolution", "Horizontal_Resolution");
  
  /********************/
  /* Print data rows */
  /********************/
  nelements = (int)list.size();
  for(int i=0; i<nelements; i++)
    printf("%-12s %-5.2lf %-5.2lf\n", list[i].GetName().c_str(), list[i].GetVertical_resolution(), list[i].GetHorizontal_resolution());

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
  if(Utilities::FileExists(AuxilaryDataFile))
    InFile.open(AuxilaryDataFile.c_str());
  else
  {
    printf("Error in function ReadAuxilaryData::Read(): File %s does not exist! Now terminating simulation ...\n", AuxilaryDataFile.c_str());
    exit(EXIT_FAILURE);
  }

  /*********************/
  /* Read-in data file */
  /*********************/
  format = "%s %lf %s %s %lf %lf";
  while(getline(InFile, buffer))
  {
    char str1[250];
    char str2[250];
    char str3[250];
    double d1;
    double d2;
    double d3;
    int nelements = sscanf(buffer.c_str(), format.c_str(), str1, &d1, str2, str3, &d2, &d3);
    if(nelements == 6)
    { 
      IncidenceAngles myDatapoint1(static_cast<string>(str1), d1);
      incidenceangledata.push_back(myDatapoint1);
      MasterImageOrientation myDatapoint2(static_cast<string>(str1), static_cast<string>(str2), static_cast<string>(str3));
      masterimageorientationdata.push_back(myDatapoint2);
      PixelResolution myDatapoint3(static_cast<string>(str1), d2, d3);
      pixelresolutiondata.push_back(myDatapoint3);
    }
  }
  InFile.close();
}
