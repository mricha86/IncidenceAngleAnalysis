/* Purpose: Algorithms used to select which part of the analysis to perform. */

/* Include header */
#include "AnalysisSelection.h"

using namespace std;

map <int, vector <string> > AnalysisSelection::Selector(int argc, char *argv[]) {
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  map <int, vector <string> > analysis_selection;
  string auxilarydatafile;
  string cratercatalog1;
  string cratercatalog2;
  string dataset_name;
  string imgdirlist;

  // Select analysis
  int nparams = argc-1;
  string command = argv[0];
  if(nparams == 1) {
    auxilarydatafile = argv[1];
    vector <string> params{auxilarydatafile};
    if(FileExists(auxilarydatafile))
      analysis_selection[1] = params;
    else
      Usage(command);
  }
  else if(nparams == 2) {
    dataset_name = argv[1];
    auxilarydatafile = argv[2];
    vector <string> params{dataset_name, auxilarydatafile};
    if(FileExists(auxilarydatafile))
      analysis_selection[2] = params;
    else
      Usage(command);
  }
  else if(nparams == 3) {
    dataset_name = argv[1];
    auxilarydatafile = argv[2];
    imgdirlist = argv[3];
    vector <string> params{dataset_name, auxilarydatafile, imgdirlist};
    if(FileExists(vectorSlice(params, 1, 2)))
      analysis_selection[3] = params;
    else
      Usage(command);
  }
  else if(nparams == 5) {
    dataset_name = argv[1];
    auxilarydatafile = argv[2];
    imgdirlist = argv[3];
    cratercatalog1 = argv[4];
    cratercatalog2 = argv[5];
    vector <string> params{dataset_name, auxilarydatafile, imgdirlist, cratercatalog1, cratercatalog2};
    if(FileExists(vectorSlice(params, 1, 4)))
      analysis_selection[4] = params;
    else
      Usage(command);
  }
  else
    Usage(command);

  return analysis_selection;
}

void AnalysisSelection::Execute(map <int, vector <string> > sel) {
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  string buffer;
  
  /*************************/
  /* Initialize checkpoint */
  /*************************/
  Checkpoint myCheckpoint;
  
  // Analysis selection
  if(sel.count(1) == 1) {
    
    /**************************************************************/
    /* Cumulative Frequency versus Size Distributions and R-plots */
    /**************************************************************/ 
    IncidenceAngleAnalysis_Plot::PaperPlots(sel[1][0]);

    /**************/
    /* Checkpoint */
    /**************/
    buffer = "Elapsed time to plot cumulative frequency versus size distributions and r-plots:";
    myCheckpoint.ElapsedTime(buffer);
  }
  else {
    
    /*************************************/
    /* Declaration of function variables */
    /*************************************/
    vector <Images> images;
    vector <ImageSets> imagesets;
    vector <IncidenceAngles> incidenceangles;
    vector <Marks> marks;

    /****************************************************/
    /* If enabled, calculation of raw crater catalogues */
    /****************************************************/
    if(sel.count(2) == 1) {

      /****************************/
      /* Declaration of variables */
      /****************************/
      double AreaofAnalysis;
      vector <OverlappedImages> different_incidence_angle_overlappedimages;
      vector <OverlappedImages> overlappedimages;
      vector <OverlappedImages> TotalOverlapImages;
      vector <OverlappedImages> scale_0_different_incidence_angle_overlappedimages;

      /******************/
      /* Ready the data */
      /******************/
      vector <string> params{sel[2][0], sel[2][1]};
      ReadyData(myCheckpoint, params, imagesets, images, marks, incidenceangles);
      
      /**********************************************************/
      /* Calculate and display area of region used for analysis */
      /**********************************************************/
      vector <double> selected_angles{27.50, 38.00, 58.00, 77.50, 83.00};
      AreaofAnalysis = Utilities::ImageTotalArea(selected_angles, incidenceangles, imagesets)*(m2km)*(m2km); // Unit: km^2
      cout << "Area of region used for analysis: " << AreaofAnalysis << " square kilometers" << endl;

      /**************/
      /* Checkpoint */
      /**************/
      buffer = "Elapsed time to calculate area of region used for analysis:";
      myCheckpoint.ElapsedTime(buffer);
      
      /***********************************/
      /* Identify overlapping sub-images */
      /***********************************/
      //overlappedimages = Utilities::FindOverlappingImages(images, incidenceangles);

      /**************/
      /* Checkpoint */
      /**************/
      buffer = "Elapsed time to identify overlapping images:";
      myCheckpoint.ElapsedTime(buffer);
      
      /*******************************************************************/
      /* Identify overlapping sub-images with different incidence angles */
      /*******************************************************************/
      //different_incidence_angle_overlappedimages = Utilities::FindDifferentIncidenceAngleOverlappingImages(overlappedimages);

      /**************/
      /* Checkpoint */
      /**************/
      buffer = "Elapsed time to identify overlapping images with different incidence angles:";
      myCheckpoint.ElapsedTime(buffer);

      /***************************************************************************************/
      /* Identify overlapping sub-images with different incidence angles at the same "scale" */
      /***************************************************************************************/
      //scale_0_different_incidence_angle_overlappedimages = Utilities::FindSameScaleOverlappingImages(different_incidence_angle_overlappedimages, 0);
      
      /**************/
      /* Checkpoint */
      /**************/
      buffer = "Elapsed time to identify overlapping images with different incidence angles that are at the same scale:";
      myCheckpoint.ElapsedTime(buffer);

      /***************************************************************/
      /* Retrieve marks from overlapping regions for different pairs */
      /* of incidence angles to produce raw crater catalogs          */
      /***************************************************************/
      int n = (int)selected_angles.size();
      int run = 0;
      for(int i = 0; i < n; i++) {
	double incidence_angle_1 = selected_angles[i];
	for(int j = i+1; j < n; j++) {
	  double incidence_angle_2 = selected_angles[j];
	  // Utilities::PrintCraterCatalog(incidence_angle_1, incidence_angle_2, incidenceangles, scale_0_different_incidence_angle_overlappedimages, marks, run, true);
	  //Utilities::PrintCraterCatalog(incidence_angle_1, incidence_angle_2, incidenceangles, different_incidence_angle_overlappedimages, marks, run, true);
	  run++;
	}
      }

      /**************/
      /* Checkpoint */
      /**************/
      buffer = "Elapsed time to retrieve marks contained within wanted overlapping images:";
      myCheckpoint.ElapsedTime(buffer);

      /*******************************************************************/
      /* Visualization of region imaged at each selected incidence angle */
      /*******************************************************************/
      IncidenceAngleAnalysis_Plot::Visualization1(selected_angles, imagesets, images, incidenceangles);
  
      /**************/
      /* Checkpoint */
      /**************/
      buffer = "Elapsed time to plot each region per selected incidence angle:";
      myCheckpoint.ElapsedTime(buffer);
    }

    /****************************************/
    /* If enabled, creation of image mosaic */
    /****************************************/
    if(sel.count(3) == 1) {

      /******************/
      /* Ready the data */
      /******************/
      vector <string> params{sel[3][0], sel[3][1]};
      ReadyData(myCheckpoint, params, imagesets, images, marks, incidenceangles);
      
      /*********************/
      /* Plot image mosaic */
      /*********************/
      string imgdirlist = sel[3][2];
      IncidenceAngleAnalysis_Plot::ImageMosaic(imgdirlist, imagesets, images, incidenceangles);

      /**************/
      /* Checkpoint */
      /**************/
      buffer = "Elapsed time to make image mosaic:";
      myCheckpoint.ElapsedTime(buffer);
    }

    /********************************************/
    /* If enabled, creation of image comparison */
    /********************************************/
    if(sel.count(4) == 1) {
      
      /******************/
      /* Ready the data */
      /******************/
      vector <string> params{sel[4][0], sel[4][1]};
      ReadyData(myCheckpoint, params, imagesets, images, marks, incidenceangles);
      
      /*************************/
      /* Plot image comparison */
      /*************************/
      string cratercatalog1 = sel[4][2];
      string cratercatalog2 = sel[4][3];
      string imgdirlist = sel[4][4];
      IncidenceAngleAnalysis_Plot::ImageComparison(3.64, 3.66, 26.14, 26.16, cratercatalog1, cratercatalog2, imgdirlist, imagesets, images, incidenceangles);

      /**************/
      /* Checkpoint */
      /**************/
      buffer = "Elapsed time to make image comparison:";
      myCheckpoint.ElapsedTime(buffer);
    }
  }
}
  
void AnalysisSelection::ReadyData(Checkpoint &myCheckpoint, vector <string> &params, vector <ImageSets> &imagesets, vector <Images> &images, vector <Marks> &marks, vector <IncidenceAngles> &incidenceangles) {
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  string buffer;

  /*****************/
  /* Retrieve data */
  /*****************/
  string dataset_name = params[0];
  string auxilarydatafile = params[1];
  DataRetrieval dataRetrieval(dataset_name, auxilarydatafile, imagesets, images, marks, incidenceangles);
  
  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Total elapsed time to retrieve data:";
  myCheckpoint.ElapsedTime(buffer);
  
  /******************************************************/
  /* Execute data auxilary functions (Data preparation) */
  /******************************************************/
  DataPreparation dataPreparation(imagesets, images, marks);
  
  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Total elapsed time to execute auxilary functions:";
  myCheckpoint.ElapsedTime(buffer);
}

void AnalysisSelection::Usage(string com) {
  // Print incidence angle accepted parameters and end program 
  cout << "Invalid parameters." << endl;
  cout << "USAGE 1: " << com << " [Crater datafile]" << endl;
  cout << "USAGE 2: " << com << " [Data set name] [Auxilary datafile]" << endl;
  cout << "USAGE 3: " << com << " [Data set name] [Auxilary datafile] [Image Directory List]" << endl;
  cout << "USAGE 4: " << com << " [Data set name] [Auxilary datafile] [Crater Catalog 1] [Crater Catalog 2] [Image Directory List]" << endl;
  exit(EXIT_FAILURE);
}
