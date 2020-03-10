#include <stdlib.h>
#include <vector>

#include "Checkpoint.h"
#include "Images.h"
#include "ImageSets.h"
#include "IncidenceAngles.h"
#include "Marks.h"
#include "OverlappedImages.h"
#include "Plot.h"
#include "ReadAuxilaryData.h"
#include "RetrieveData.h"
#include "SortImages.h"
#include "Utilities.h"

using namespace std;

int main(int argc, char *argv[])
{
  /*******************************************/
  /* Declaration/Initialization of variables */
  /*******************************************/
  double AreaofAnalysis;
  double incidence_angle_1;
  double incidence_angle_2;
  int run_mode;
  string auxilarydatafile;
  string dataset_name;
  string buffer;
  string cratercatalog1;
  string cratercatalog2;
  string imgdirlist;
  string rejectedimage;
  vector <double> selected_angles = {27.50, 38.00, 58.00, 77.50, 83.00};
  vector <double> unique_incidenceangles;
  vector <Images> images;
  vector <ImageSets> imagesets;
  vector <IncidenceAngles> incidenceangles;
  vector <Marks> marks;
  vector <OverlappedImages> different_incidence_angle_overlappedimages;
  vector <OverlappedImages> overlappedimages;
  vector <OverlappedImages> TotalOverlapImages;
  vector <OverlappedImages> scale_0_different_incidence_angle_overlappedimages;

  /***********************/
  /* Retrieve arguements */
  /***********************/
  if(argc == 3)
  {
    run_mode = 0;
    dataset_name = argv[1];
    auxilarydatafile = argv[2];
  }
  else if(argc == 4)
  {
    dataset_name = argv[1];
    auxilarydatafile = argv[2];
    run_mode = atoi(argv[3]);
  }
  else if(argc == 5)
  {
    dataset_name = argv[1];
    auxilarydatafile = argv[2];
    imgdirlist = argv[3];
    run_mode = atoi(argv[4]);
  }
  else if(argc == 7)
  {   
    dataset_name = argv[1];
    auxilarydatafile = argv[2];
    cratercatalog1 = argv[3];
    cratercatalog2 = argv[4];
    imgdirlist = argv[5];
    run_mode = atoi(argv[6]);
  }
  else
  {
    printf("Invalid number of arguments (%d).\nUSAGE 1: %s [Data set name] [Auxilary datafile]\nUSAGE 2: %s [Data set name] [Auxilary datafile] [Run mode]\nUSAGE 3: %s [Data set name] [Auxilary datafile] [Crater Catalog 1] [Crater Catalog 2] [Image Directory List] [Run mode]\nUSAGE 4: %s [Data set name] [Auxilary datafile] [Image Directory List] [Run mode]\n", argc, argv[0], argv[0], argv[0], argv[0]);
    exit(EXIT_FAILURE);
  }

  /*************************/
  /* Initialize checkpoint */
  /*************************/
  Checkpoint myCheckpoint;

  if(run_mode == 1)
  { 
    /**************************************************************/
    /* Cumulative Frequency versus Size Distributions and R-plots */
    /**************************************************************/
    Plot::PaperPlots(auxilarydatafile);
      
    /**************/
    /* Checkpoint */
    /**************/
    buffer = "Elapsed time to plot cumulative frequency versus size distributions and r-plots:";
    // myCheckpoint.ElapsedTime(buffer);
 
    return 0;
  }

  /*****************/
  /* Retrieve data */
  /*****************/
  Utilities::ObtainData(dataset_name, imagesets, images, marks, auxilarydatafile, incidenceangles);
  
  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Total elapsed time to retrieve data:";
  myCheckpoint.ElapsedTime(buffer);

  /******************************************************/
  /* Execute data auxilary functions (Data preparation) */
  /******************************************************/
  Utilities::ExecuteAuxilaryFunctions(imagesets, images, marks);
  
  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Total elapsed time to execute auxilary functions:";
  myCheckpoint.ElapsedTime(buffer);
  
  /**********************************/
  /* Size of area used for analysis */
  /**********************************/
  AreaofAnalysis = Utilities::ImageTotalArea(selected_angles, incidenceangles, imagesets)*(m2km)*(m2km); // Unit: km^2
  cout << "Area of region used for analysis: " << AreaofAnalysis << " square kilometers" << endl;

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to calculate area of region used for analysis:";
  myCheckpoint.ElapsedTime(buffer);

  /*******************************************************************/
  /* Visualization of region imaged at each selected incidence angle */
  /*******************************************************************/
  string imdir = "/Users/MRichardson/Desktop/Incidence_Angle_Analysis/images/";
  for (int i = 0; i < (int)selected_angles.size(); i++) {
    Plot::PlotRealMasterImage(imdir, selected_angles[i], incidenceangles, imagesets, images);
    for (int j = 0; j < (int)selected_angles.size(); j++) {
      if(i == j)
	continue;
      Plot::PlotRealMasterImage(imdir, selected_angles[i], incidenceangles, imagesets, images, selected_angles[j]);
    }
  }
  
  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to plot each region per selected incidence angle:";
  myCheckpoint.ElapsedTime(buffer);
  exit(0);
  
  /***************************/
  /* Create image comparison */
  /***************************/
  if(run_mode == 2)
  {
    Plot::ImageComparison(3.64, 3.66, 26.14, 26.16, cratercatalog1, cratercatalog2, imgdirlist, imagesets, images, incidenceangles);

    /**************/
    /* Checkpoint */
    /**************/
    buffer = "Elapsed time to make image comparison:";
    myCheckpoint.ElapsedTime(buffer);

    return 0;
  }

  /***********************/
  /* Create image mosaic */
  /***********************/
  if(run_mode == 3)
  {
    Plot::ImageMosaic(imgdirlist, imagesets, images, incidenceangles);

    /**************/
    /* Checkpoint */
    /**************/
    buffer = "Elapsed time to make image mosaic:";
    myCheckpoint.ElapsedTime(buffer);

    return 0;
  }
  
  /***********************************/
  /* Identify overlapping sub-images */
  /***********************************/
  overlappedimages = Utilities::FindOverlappingImages(images, incidenceangles);
  // OverlappedImages::Display(overlappedimages); exit(0);

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to identify overlapping images:";
  // myCheckpoint.ElapsedTime(buffer);

  /*******************************************************************/
  /* Identify overlapping sub-images with different incidence angles */
  /*******************************************************************/
  different_incidence_angle_overlappedimages = Utilities::FindDifferentIncidenceAngleOverlappingImages(overlappedimages);
  // OverlappedImages::Display(different_incidence_angle_overlappedimages); exit(0);

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to identify overlapping images with different incidence angles:";
  // myCheckpoint.ElapsedTime(buffer);

  /****************************************************************************************/
  /* Identify overlapping sub-images with difference incidence angles at the same "scale" */
  /****************************************************************************************/
  scale_0_different_incidence_angle_overlappedimages = Utilities::FindSameScaleOverlappingImages(different_incidence_angle_overlappedimages, 0);
  // OverlappedImages::Display(scale_0_different_incidence_angle_overlappedimages); exit(0);

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to identify overlapping images with different incidence angles that are at the same scale:";
  // myCheckpoint.ElapsedTime(buffer);
  
  /************************************************************************************/
  /* Retrieve marks from overlapping regions for a pair of different incidence angles */
  /************************************************************************************/
  int n = (int)selected_angles.size();
  int run = 0;
  for(int i=0; i<n; i++)
  {
    incidence_angle_1 = selected_angles[i];
    for(int j=i+1; j<n; j++)
    {
      incidence_angle_2 = selected_angles[j];
      Utilities::PrintCraterCatalog(incidence_angle_1, incidence_angle_2, incidenceangles, scale_0_different_incidence_angle_overlappedimages, marks, run, true);
      run++;
    }
  }

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to retrieve marks contained within wanted overlapping images:";
  // myCheckpoint.ElapsedTime(buffer);
  
  return 0;
}
