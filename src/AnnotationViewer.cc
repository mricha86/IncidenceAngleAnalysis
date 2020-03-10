/* Purpose: View user annotations */

// Include Libraries
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <TASImage.h>
#include <TEllipse.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TFrame.h>
#include <TH1.h>
#include <TStyle.h>
#include <vector>

#include "Images.h"
#include "ImageSets.h"
#include "Marks.h"
#include "MySQLConnection.h"
#include "RetrieveImages.h"
#include "RetrieveImageSets.h"
#include "RetrieveMarks.h"
#include "SearchImageSets.h"
#include "Utilities.h"

using namespace std;
using namespace sql;


int main()
{
  // Declaration/Initialization of function variables  
  Connection *conn;
  double min_x;
  double min_y;
  double spacing;
  double x_high;
  double x_low;
  double x_max;
  double x_min;
  double xrange;
  double y_high;
  double y_low;
  double y_max;
  double y_min;
  double yrange;
  ifstream infile;
  int canheight;
  int canwidth;
  int dataset_id;
  int m;
  int n;
  string database;
  string buffer;
  string field;
  string filename;
  string format;
  string option;
  string password;
  string table;
  string url;
  string user;
  TCanvas *can1;
  TCanvas *can2;
  TCanvas *can3;
  TH1F *h1;
  vector <double> d;
  vector <double> d_annotations;
  vector <double> d_reduced;
  vector <double> lower_left_latitude;
  vector <double> lower_left_y;
  vector <double> maximum_latitude;
  vector <double> maximum_longitude;
  vector <double> maximum_x;
  vector <double> maximum_y;
  vector <double> minimum_latitude;
  vector <double> minimum_longitude;
  vector <double> minimum_x;
  vector <double> minimum_y;
  vector <double> upper_left_latitude;
  vector <double> upper_left_longitude;
  vector <double> upper_left_x;
  vector <double> upper_left_y;
  vector <double> upper_right_longitude;
  vector <double> upper_right_x;
  vector <double> x;
  vector <double> x_annotations;
  vector <double> x_reduced;
  vector <double> y;
  vector <double> y_annotations;
  vector <double> y_reduced;
  vector <Images> images;
  vector <ImageSets> imagesets;
  vector <int> imagenumbers;
  vector <int> imagescales;
  vector <int> sub_image_ids;
  vector <Marks> marks;
  vector <string> files;
  vector <string> imagenames;
  vector <string> sub_image_names;
  vector <TASImage *> imgs;
  vector <TEllipse *> craters;
  vector <TPad *> pads;
  
  /*************************************/
  /* Determine which dataset to access */
  /*************************************/
  dataset_id = Utilities::DataSetSelector("moon");

  /*****************************************************/
  /* Establish connection to CosmoQuest MySQL database */
  /*****************************************************/
  url = "tcp://localhost:3306";
  user = "root";
  password = "00000000";
  database = "cosmoquest_matts_version";
  MySQLConnection myConnection(url, user, password, database);
  myConnection.Connect();
  conn = myConnection.GetConnection();

  /*********************************/
  /* Read data from MySQL database */
  /*********************************/
  table = "image_sets";
  field = "id, name, application_id, upper_left_latitude, upper_left_longitude, upper_right_latitude, upper_right_longitude, lower_right_latitude, lower_right_longitude, lower_left_latitude, lower_left_longitude, pixel_resolution, details";
  RetrieveImageSets myImageSets(conn, dataset_id, table, field, option);
  myImageSets.Fetch();
  imagesets = myImageSets.GetData();
  table = "images";
  field = "id, image_set_id, application_id, name, details";
  RetrieveImages myImages(conn, dataset_id, table, field, option);
  myImages.Fetch();
  images = myImages.GetData();
  table = "marks";
  field = "id, image_id, application_id, x, y, diameter";
  option = "";
  RetrieveMarks myMarks(conn, dataset_id, table, field, option);
  myMarks.Fetch();
  marks = myMarks.GetData();
  
  /****************************************/
  /* Execute imagesets auxilary functions */
  /****************************************/
  Utilities::ExecuteImageSetsAuxilaryFunction(imagesets);

  /*************************************/
  /* Execute images auxilary functions */
  /*************************************/
  Utilities::ExecuteImagesAuxilaryFunction(images, imagesets);

  /************************************/
  /* Execute marks auxilary functions */
  /************************************/
  Utilities::ExecuteMarksAuxilaryFunction(marks, images);

  /***************/
  /* Images used */
  /***************/
  files.push_back("/Users/MRichardson/Desktop/Incidence_Angle_Analysis/scripts/images_M109215691LE/M109215691LE_0_00093.png");
  files.push_back("/Users/MRichardson/Desktop/Incidence_Angle_Analysis/scripts/images_M109215691LE/M109215691LE_0_00094.png");
  files.push_back("/Users/MRichardson/Desktop/Incidence_Angle_Analysis/scripts/images_M109215691LE/M109215691LE_0_00095.png");
  files.push_back("/Users/MRichardson/Desktop/Incidence_Angle_Analysis/scripts/images_M109215691LE/M109215691LE_0_00096.png");
  files.push_back("/Users/MRichardson/Desktop/Incidence_Angle_Analysis/scripts/images_M109215691LE/M109215691LE_0_00103.png");
  files.push_back("/Users/MRichardson/Desktop/Incidence_Angle_Analysis/scripts/images_M109215691LE/M109215691LE_0_00104.png");
  files.push_back("/Users/MRichardson/Desktop/Incidence_Angle_Analysis/scripts/images_M109215691LE/M109215691LE_0_00105.png");
  files.push_back("/Users/MRichardson/Desktop/Incidence_Angle_Analysis/scripts/images_M109215691LE/M109215691LE_0_00106.png");
  files.push_back("/Users/MRichardson/Desktop/Incidence_Angle_Analysis/scripts/images_M109215691LE/M109215691LE_0_00113.png");
  files.push_back("/Users/MRichardson/Desktop/Incidence_Angle_Analysis/scripts/images_M109215691LE/M109215691LE_0_00114.png");
  files.push_back("/Users/MRichardson/Desktop/Incidence_Angle_Analysis/scripts/images_M109215691LE/M109215691LE_0_00115.png");
  files.push_back("/Users/MRichardson/Desktop/Incidence_Angle_Analysis/scripts/images_M109215691LE/M109215691LE_0_00116.png");
  
  /********************************************/
  /* Retrieve image name, scaling, and number */
  /********************************************/
  n = (int)files.size();
  for (int i=0; i < n; i++) {
    string file = files[i];
    int pos1 = file.rfind("/")+1;
    int pos2 = file.rfind(".");
    int len = pos2-pos1;
    string filename = file.substr(pos1, len);
    pos1 = 0;
    pos2 = filename.find("_");
    imagenames.push_back(filename.substr(pos1, pos2));
    pos1 = filename.find("_")+1;
    pos2 = filename.rfind("_");
    imagescales.push_back(stoi(filename.substr(pos1, pos2)));
    pos1 = filename.rfind("_")+1;
    imagenumbers.push_back(stoi(filename.substr(pos1)));
    string sub_image_name = imagenames.back()+"_"+to_string(imagescales.back())+"_"+to_string(imagenumbers.back());
    sub_image_names.push_back(sub_image_name);
  }

  /**********************/
  /* Sort images vector */
  /**********************/
  field = "name";
  SortImages sortimages(images, field);
  sortimages.arrange();
  images = sortimages.GetImages();
  //RetrieveImages::Display(images); exit(0);
  
  /************************************/
  /* Find sub-images in images vector */
  /************************************/
  double constant = 1.0E-3;
  n = (int)sub_image_names.size();
  m = (int)images.size();
  for (int i = 0; i < n; ++i) {
    string sub_image_name = sub_image_names[i];
    int sub_image_index = SearchImages::BinarySearch(images, 0, m-1, field, &sub_image_name);
    if (sub_image_index == -1) {
      printf("Could not find data for image %s.\n Terminating program...\n", sub_image_name.c_str());
      exit(EXIT_FAILURE);
    }
    sub_image_ids.push_back(images[sub_image_index].GetId());
    lower_left_latitude.push_back(images[sub_image_index].GetLower_left_latitude()); // Unit: degree
    lower_left_y.push_back(images[sub_image_index].GetLower_left_y()); // Unit: meter
    upper_left_latitude.push_back(images[sub_image_index].GetUpper_left_latitude()); // Unit: degree
    upper_left_y.push_back(images[sub_image_index].GetUpper_left_y()); // Unit: meter
    upper_left_longitude.push_back(images[sub_image_index].GetUpper_left_longitude()); // Unit: degree
    upper_left_x.push_back(images[sub_image_index].GetUpper_left_x()); // Unit: meter
    upper_right_longitude.push_back(images[sub_image_index].GetUpper_right_longitude()); // Unit: degree
    upper_right_x.push_back(images[sub_image_index].GetUpper_right_x()); // Unit: meter
    maximum_latitude.push_back(images[sub_image_index].GetMaximum_latitude()); // Unit: degree
    maximum_longitude.push_back(images[sub_image_index].GetMaximum_longitude()); // Unit: degree
    maximum_x.push_back(images[sub_image_index].GetMaximum_x()); // Unit: meter
    maximum_y.push_back(images[sub_image_index].GetMaximum_y()); // Unit: meter
    minimum_latitude.push_back(images[sub_image_index].GetMinimum_latitude()); // Unit: degree
    minimum_longitude.push_back(images[sub_image_index].GetMinimum_longitude()); // Unit: degree
    minimum_x.push_back(images[sub_image_index].GetMinimum_x()); // Unit: meter
    minimum_y.push_back(images[sub_image_index].GetMinimum_y()); // Unit: meter
  }
  
  /***************/
  /* Corrections */
  /***************/
  min_x = *min_element(minimum_x.begin(), minimum_x.end())*constant;
  min_y = *min_element(minimum_y.begin(), minimum_y.end())*constant;
  for (int i = 0; i < n; i++) {
    lower_left_y[i] *= constant; // Unit: kilometer
    maximum_x[i] *= constant; // Unit: kilometer
    minimum_x[i] *= constant; // Unit: kilometer
    maximum_y[i] *= constant; // Unit: kilometer
    minimum_y[i] *= constant; // Unit: kilometer
    upper_left_y[i] *= constant; // Unit: kilometer
    upper_left_x[i] *= constant; // Unit: kilometer
    upper_right_x[i] *= constant; // Unit: kilometer
    lower_left_y[i] -= min_y; // Applying y-offset
    maximum_x[i] -= min_x; // Applying x-offset
    minimum_x[i] -= min_x; // Applying x-offset
    maximum_y[i] -= min_y; // Applying y-offset
    minimum_y[i] -= min_y; // Applying y-offset
    upper_left_y[i] -= min_y; // Applying y-offset
    upper_left_x[i] -= min_x; // Applying x-offset
    upper_right_x[i] -= min_x; // Applying x-offset
  }
  
  /***************************************/
  /* Sort marks vector based on image_id */
  /***************************************/
  field = "image_id";
  SortMarks sortmarks(marks, field);
  sortmarks.arrange();
  marks = sortmarks.GetMarks();

  /*********************************************/
  /* Read data in from user annotation catalog */
  /*********************************************/
  string file = "/Users/MRichardson/Desktop/Incidence_Angle_Analysis/testing/Crater_catalog_2_M109215691LERE_27.500000.txt";
  if(Utilities::FileExists(file))
    infile.open(file.c_str());
  else
  {
    printf("Error: File %s does not exist!\n", file.c_str());
    exit(EXIT_FAILURE);
  }
  while(getline(infile, buffer))
  {
    double v1; // X coordinate. Unit: meter
    double v2; // Y coordinate. Unit: meter
    double v3; // Diameter. Unit: meter
    format = "%lf %lf %lf %*d %*d %*d";
    sscanf(buffer.c_str(), format.c_str(), &v1, &v2, &v3);
    x_annotations.push_back(v1*constant-min_x); // Unit: kilometer
    y_annotations.push_back(v2*constant-min_y); // Unit: kilometer
    d_annotations.push_back(v3*constant); // Unit: kilometer
  }
  infile.close();

  /********************************************/
  /* Read data in from reduced crater catalog */
  /********************************************/
  file = "/Users/MRichardson/Desktop/Incidence_Angle_Analysis/testing/Reduced_crater_catalog_2_M109215691LERE_27.500000.txt";
  if(Utilities::FileExists(file))
    infile.open(file.c_str());
  else
  {
    printf("Error: File %s does not exist!\n", file.c_str());
    exit(EXIT_FAILURE);
  }
  while(getline(infile, buffer))
  {
    double v1; // X coordinate. Unit: meter
    double v2; // Y coordinate. Unit: meter
    double v3; // Diameter. Unit: meter
    format = "%*d %lf %*lf %lf %*lf %lf %*lf %*lf %*lf %*d";
    sscanf(buffer.c_str(), format.c_str(), &v1, &v2, &v3);
    x_reduced.push_back(v1*constant-min_x); // Unit: kilometer
    y_reduced.push_back(v2*constant-min_y); // Unit: kilometer
    d_reduced.push_back(v3*constant); // Unit: kilometer
  }
  infile.close();
    
  
  // /**********************/
  // /* Retrieve all marks */
  // /**********************/
  // m = (int)marks.size();
  // for (int i = 0; i < n; i++) {

  //   // Retrieve all marks for current sub-image
  //   int sub_image_id = sub_image_ids[i];
  //   mark_first_index = SearchMarks::FirstOccurence(marks, 0, m-1, field, &sub_image_id);
  //   mark_last_index = SearchMarks::LastOccurence(marks, 0, m-1, field, &sub_image_id);
  //   for(int j=mark_first_index; j<=mark_last_index; j++) {
  //     d.push_back(marks[j].GetPhysical_diameter()*constant);
  //     x.push_back(marks[j].GetPhysical_x()*constant-min_x);
  //     y.push_back(marks[j].GetPhysical_y()*constant-min_y);
  //   }
  // }
  
  /*****************/
  /* Axes settings */
  /*****************/
  bool selenographic = false;
  if(selenographic)
  {
    buffer = "; X [Degree]; Y [Degree]";
    x_high = *max_element(maximum_longitude.begin(), maximum_longitude.end());
    x_low = *min_element(minimum_longitude.begin(), minimum_longitude.end());
    y_high = *max_element(maximum_latitude.begin(), maximum_latitude.end());
    y_low = *min_element(minimum_latitude.begin(), minimum_latitude.end());
    spacing = 1.0E-2;
  }
  else
  {
    buffer = "; X [km]; Y [km]";
    x_high = *max_element(maximum_x.begin(), maximum_x.end());
    x_low = *min_element(minimum_x.begin(), minimum_x.end());
    y_high = *max_element(maximum_y.begin(), maximum_y.end());
    y_low = *min_element(minimum_y.begin(), minimum_y.end());
    spacing = 0.0E1;
  }
  
  /*********************/
  /* Initialize Canvas */
  /*********************/
  canheight = 800;
  canwidth = 800;
  //can = new TCanvas("Canvas", "", canheight, canwidth);
  can1 = new TCanvas("Original Image");
  can1->SetGridx();
  can1->SetGridy();
  can1->SetRightMargin(0.09);
  can1->SetLeftMargin(0.15);
  can1->SetBottomMargin(0.15);
  
  /**************/
  /* Draw frame */
  /**************/
  h1 = can1->DrawFrame(x_low-spacing, y_low-spacing, x_high+spacing, y_high+spacing, buffer.c_str());
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetNdivisions(5);
  h1->GetXaxis()->CenterTitle();
  h1->GetXaxis()->SetNdivisions(5);
  gPad->GetRange(x_min, y_min, x_max, y_max);
  xrange = x_max-x_min;
  yrange = y_max-y_min;

  /**************************/
  /* Define pads and images */
  /**************************/
  n = (int)files.size();
  for (int i=0; i < n; i++) {
    
    /******************/
    /* Initialize pad */
    /******************/
    double x1 = 0;
    double x2 = 0;
    double y1 = 0;
    double y2 = 0;
    if(selenographic) {
      x2 = (maximum_longitude[i]-x_min)/xrange;
      x1 = (minimum_longitude[i]-x_min)/xrange;
      y2 = (maximum_latitude[i]-y_min)/yrange;
      y1 = (minimum_latitude[i]-y_min)/yrange;
    }
    else {
      x2 = (maximum_x[i]-x_min)/xrange;
      x1 = (minimum_x[i]-x_min)/xrange;
      y2 = (maximum_y[i]-y_min)/yrange;
      y1 = (minimum_y[i]-y_min)/yrange;
    }
    TPad *pad = new TPad(sub_image_names[i].c_str(), "", x1, y1, x2, y2);
    pad->SetFillColorAlpha(kWhite, 0.); // Make pad transparent
    pads.push_back(pad);
  
    /*****************/
    /* Read in image */
    /*****************/
    TASImage *img = new TASImage(files[i].c_str());
    if (!img) {
      printf("Could not open image %s.\n Terminating program...\n", files[i].c_str());
      exit(EXIT_FAILURE);
    }
    img->SetConstRatio(kTRUE);
    img->SetImageQuality(TAttImage::kImgBest);

    /*****************************/
    /* Correct image orientation */
    /*****************************/
    if(selenographic) {
      if(upper_left_longitude[i] > upper_right_longitude[i]) {
	if(upper_left_latitude[i] < lower_left_latitude[i])
	  img->Flip(180);
      else	    
	img->Mirror(true);
      }
    }
    else {
    if(upper_left_x[i] > upper_right_x[i]) {
      if(upper_left_y[i] < lower_left_y[i])
	img->Flip(180);
      else
	img->Mirror(true);
    }
    img->SetEditable(kTRUE);
    imgs.push_back(img);
    }
  }
  
  /********************/
  /* Speed up drawing */
  /********************/
  gStyle->SetCanvasPreferGL(kTRUE);
  
  /**************/
  /* Draw image */
  /**************/
  n = (int)pads.size();
  for (int i = 0; i < n; i++) {
    can1->cd();
    pads[i]->Draw();
    pads[i]->cd();
    imgs[i]->Draw("X");
  }

  /*************************/
  /* Initialize new canvas */
  /*************************/
  can2 = new TCanvas("Annotated Image");
  can1->DrawClonePad();
  
  /*********************************************/
  /* Plot image with user annotations included */
  /*********************************************/
  can2->cd();
  n=(int)x_annotations.size();
  for (int i = 0; i < n; i++) {
    /*******************************************************/
    /* Determine if current point lies with image boundary */
    /*******************************************************/
    if ((x_annotations[i] < x_low) || (x_high < x_annotations[i])) {
      continue;
    }
    if ((y_annotations[i] < y_low) || (y_high < y_annotations[i])) {
      continue;
    }
    /**************/
    /* Plot point */
    /**************/
    double phi_min = 0;
    double phi_max = 360;
    TEllipse *el = new TEllipse(x_annotations[i], y_annotations[i], d_annotations[i]/2.0, d_annotations[i]/2.0, phi_min, phi_max);
    el->SetFillStyle(0);
    el->SetLineColor(kRed);
    el->SetNoEdges();
    el->Draw();
  }

  /*************************/
  /* Initialize new canvas */
  /*************************/
  can3 = new TCanvas("Crater Image");
  can1->DrawClonePad();

  /*********************************************/
  /* Plot image with user annotations included */
  /*********************************************/
  can3->cd();
  n=(int)x_reduced.size();
  for (int i = 0; i < n; i++) {
    /*******************************************************/
    /* Determine if current point lies with image boundary */
    /*******************************************************/
    if ((x_reduced[i] < x_low) || (x_high < x_reduced[i])) {
      continue;
    }
    if ((y_reduced[i] < y_low) || (y_high < y_reduced[i])) {
      continue;
    }
    /**************/
    /* Plot point */
    /**************/
    double phi_min = 0;
    double phi_max = 360;
    TEllipse *el = new TEllipse(x_reduced[i], y_reduced[i], d_reduced[i]/2.0, d_reduced[i]/2.0, phi_min, phi_max);
    el->SetFillStyle(0);
    el->SetLineColor(kGreen);
    el->SetNoEdges();
    el->Draw();
  }
  
  /*******************************/
  /* Save original image to file */
  /*******************************/
  filename = "OriginalImage.png";
  can1->Print(filename.c_str());

  /********************************/
  /* Save annotated image to file */
  /********************************/
  filename = "AnnotatedImage.png";
  can2->Print(filename.c_str());

  /***********************************/
  /* Save final crater image to file */
  /***********************************/
  filename = "CraterImage.png";
  can3->Print(filename.c_str());
  
  return 0;
}
