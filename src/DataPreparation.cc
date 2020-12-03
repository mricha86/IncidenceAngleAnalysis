/* Purpose: Functions used to calculate . */

/* Include header file */
#include "DataPreparation.h"

using namespace std;

DataPreparation::DataPreparation(vector <ImageSets> &IMAGESETS, vector <Images> &IMAGES, std::vector <Marks> &MARKS)
{
  /***************************************/
  /* Initialization of class variable(s) */
  /***************************************/
  imss = IMAGESETS;
  ims = IMAGES;
  mks = MARKS;

  /***********************************/
  /* Execute data auxilary functions */
  /***********************************/
  ExecuteAuxilaryFunctions(imss, ims, mks);

  /************************************/
  /* Overwrite originial data vectors */
  /************************************/
  IMAGESETS = imss;
  IMAGES = ims;
  MARKS = mks;
}

void DataPreparation::ExecuteAuxilaryFunctions(vector <ImageSets> &imagesets, vector <Images> &images, vector <Marks> &marks)
{
  /***************************************/
  /* Declaration of function variable(s) */
  /***************************************/
  string buffer;
  
  /*************************/
  /* Initialize checkpoint */
  /*************************/
  Checkpoint myCheckpoint;
  
  /****************************************/
  /* Execute imagesets auxilary functions */
  /****************************************/
  ExecuteImageSetsAuxilaryFunction(imagesets);

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to execute imagesets auxilary function:";
  myCheckpoint.ElapsedTime(buffer);

  /*************************************/
  /* Execute images auxilary functions */
  /*************************************/
  ExecuteImagesAuxilaryFunction(images, imagesets);
  
  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to execute images auxilary function:";
  myCheckpoint.ElapsedTime(buffer);

  /************************************/
  /* Execute marks auxilary functions */
  /************************************/
  ExecuteMarksAuxilaryFunction(marks, images);

  /**************/
  /* Checkpoint */
  /**************/
  buffer = "Elapsed time to execute marks auxilary function:";
  myCheckpoint.ElapsedTime(buffer);
  
  return;
}

void DataPreparation::ExecuteImagesAuxilaryFunction(vector <Images> &images, vector <ImageSets> &imagesets)

{
  /**********************************************/
  /* Sort imagesets vector based on name column */
  /**********************************************/
  SortData<ImageSets> sortimagesets(imagesets, "name");
  sortimagesets.arrange();
  imagesets = sortimagesets.GetData();
  
  /*******************************************/
  /* Sort images vector based on name column */
  /*******************************************/
  SortData<Images> sortimages(images, "name");
  sortimages.arrange();
  images = sortimages.GetData();
  
  /****************/
  /* Images index */
  /****************/
  int index = 0;

  /************************************/
  /* Iterate through imagesets vector */
  /************************************/
  for(int i=0; i<(int)imagesets.size(); i++)
  {
    /**************************************/
    /* Retrieve current master image name */
    /**************************************/
    string master_image_name = imagesets[i].GetName();
   
    /************************************************************************************/
    /* Retrieve x and y conditions for master image upper left corner as viewed by user */
    /************************************************************************************/
    string upper_left_x = imagesets[i].GetUpper_left_corner_x_status();
    string upper_left_y = imagesets[i].GetUpper_left_corner_y_status();

    /*************************************/
    /* Retrieve transformation matricies */
    /*************************************/
    ProjectiveTransformation pt = imagesets[i].GetProjective_transformation();
    
    /**************************************************/
    /* Determine length of current sub-image basename */
    /**************************************************/
    int p1 = images[index].GetName().find("_");
    
    /*********************************/
    /* Iterate through images vector */
    /*********************************/
    while(master_image_name.compare(images[index].GetName().substr(0, p1)) == 0)
    {
      /****************************/
      /* Execute AuxilaryFunction */
      /****************************/
      images[index].AuxilaryFunction(upper_left_x, upper_left_y, pt);
      
      /**************************/
      /* Increment images index */
      /**************************/
      index++;
    }
  }
  
  if((int)imagesets.size() == 0)
  {
    cout << "Error in \"ExecuteImagesAuxilaryFunction\". ImageSets array has zero elements!\n Now terminating program ..." << endl;
    exit(EXIT_FAILURE);
  }

  return;
}

void DataPreparation::ExecuteImageSetsAuxilaryFunction(vector <ImageSets> &imagesets)
{  
  /*****************************************************************/
  /* Iterate through imagesets vector and execute AuxilaryFunction */
  /*****************************************************************/
  for(int i=0; i<(int)imagesets.size(); i++)
    imagesets[i].AuxilaryFunction();
  
  return;
}

void DataPreparation::ExecuteMarksAuxilaryFunction(vector <Marks> &marks, vector <Images> &images)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  int index;
  string field;
  
  /**********************************/
  /* Sort images vector based on id */
  /**********************************/
  field = "id";
  SortData<Images> sortimages(images, field);
  sortimages.arrange();
  images = sortimages.GetData();

  /*********************/
  /* Sort marks vector */
  /*********************/
  field = "image_id";
  SortData<Marks> sortmarks(marks, field);
  sortmarks.arrange();
  marks = sortmarks.GetData();

  /*********************************/
  /* Iterate through images vector */
  /*********************************/
  index = 0;
  for(int i=0; i<(int)images.size(); i++)
  {
    /********************/
    /* Current image id */
    /********************/
    int image_id = images[i].GetId();

    /****************************************************/
    /* Current image upper left corner pixel coordinate */
    /****************************************************/
    double x_offset = images[i].GetX_relative();
    double y_offset = images[i].GetY_relative();
    
    /************************************************/
    /* Retrieve current coordinate transform matrix */
    /************************************************/
    ProjectiveTransformation pt = images[i].GetProjective_transformation();

    /****************************************/
    /* Reject moon_mappers_tutorial_4 image */
    /****************************************/
    if(image_id == 60639)
      continue;
    
    /***************************************************************************************/
    /* Calculate selenographic coordinates for all marks associated with current sub-image */
    /***************************************************************************************/
    while(image_id == marks[index].GetImage_id())
    {
      /*****************************************************************************/
      /* Global pixel coordinates (Mark pixel coordinate relative to master image) */
      /*****************************************************************************/
      double x = static_cast<int>(x_offset+marks[index].GetX());
      double y = static_cast<int>(y_offset+marks[index].GetY());
      
      /*********************************************/
      /* Calculate mark diameter in physical units */
      /*********************************************/
      double r = 0.5*marks[index].GetDiameter(); // Unit: pixel
      double latitude_high = pt.ComputeTarget2SourceCoordinate_y(x, y+r); // Unit: degree
      double latitude_low = pt.ComputeTarget2SourceCoordinate_y(x, y-r); // Unit: degree
      double longitude_high = pt.ComputeTarget2SourceCoordinate_y(x+r, y); // Unit: degree
      double longitude_low = pt.ComputeTarget2SourceCoordinate_y(x-r, y); // Unit: degree
      double angular_change1 = fabs(latitude_high-latitude_low); // Unit: degree
      double angular_change2 = fabs(longitude_high-longitude_low); // Unit: degree
      double angular_change = (angular_change1 > angular_change2) ? angular_change1 : angular_change2; // Unit: degree
      double physical_diameter = EquirectangularProjection::CalculateY(angular_change, 0.0, R_moon); // Unit: meter
      //double physical_diameter2 = SphericalLawofCosines::CalculateDistance(latitude_low, latitude_high, longitude, longitude, R_moon); // Unit: meter
      
      /*****************************/
      /* Execute auxilary function */
      /*****************************/
      vector <double> adjustedpixelcoordinate{x, y}; // Units: pixel
      vector <double> selenographiccoordinate = pt.ComputeTarget2SourceCoordinates(x, y); // Units: degree
      double physical_x = EquirectangularProjection::CalculateX(selenographiccoordinate[0], 0.0, 0.0, R_moon); // Unit: meter
      double physical_y = EquirectangularProjection::CalculateY(selenographiccoordinate[1], 0.0, R_moon); // Unit: meter
      //double physical_x2 = SphericalLawofCosines::CalculateDistance(0.0, 0.0, 0.0, selenographiccoordinate[0], R_moon); // Unit: meter
      //double physical_y2 = SphericalLawofCosines::CalculateDistance(0.0, selenographiccoordinate[1], 0.0, 0.0, R_moon); // Unit: meter
      vector <double> cartesiancoordinate{physical_x, physical_y};
      marks[index].AuxilaryFunction(adjustedpixelcoordinate, selenographiccoordinate, cartesiancoordinate, physical_diameter);
      
      /****************/
      /* Update index */
      /****************/
      index++;
    }
  }

  return;
}
