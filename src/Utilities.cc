#include "Utilities.h"

using namespace boost;
using namespace std;

bool Utilities::do_LinesIntersect(double x, double y, double x1, double y1, double x2, double y2)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double Ax;
  double Ay;
  double Bx;
  double By;
  double Px;
  double Py;
  double max_x;
  double min_x;
  double slope_line_segment;
  double slope_test_line;
  
  /****************************************************************************/
  /* Determine which point is the highest point and set test point coordinate */
  /****************************************************************************/
  if(y1 < y2)
  {
    Ax = x1;
    Ay = y1;
    Bx = x2;
    By = y2;
    Px = x;
    Py = y;
  }
  else
  {
    Ax = x2;
    Ay = y2;
    Bx = x1;
    By = y1;
    Px = x;
    Py = y;
  }
  
  /***************************************/
  /* Determine max and min x coordinates */
  /***************************************/
  if(Ax < Bx)
  {
    max_x = Bx;
    min_x = Ax;
  }
  else
  {
    max_x = Ax;
    min_x = Bx;
  }
  
  /************************************/
  /* Adjust test point's y coordinate */
  /************************************/
  if((Py == Ay) || (Py == By))
    Py += 1.0;

  /*************************************************************/
  /* 1) If test point is lower than point A or higher than point */
  /*    B, then horizontal ray to infinity from test point can   */
  /*    not intersect line AB.                                   */
  /* 2) If test point lies between the y bounds of line AB but   */
  /*    exceeds the maximum x coordinate of line AB, then        */
  /*    horizontal ray to infinity from test point can not       */
  /*    intersect line AB.                                       */
  /* 3) If test point lies between the y bounds of line AB and   */
  /*    does not exceed the maximum x coordinate of line AB,     */
  /*    then horizontal ray to infinity from test point must     */
  /*    intersect line AB.                                       */
  /*************************************************************/
  if((Py < Ay) || (Py > By))
    return false;
  else if(Px >= max_x)
    return false;
  else
    if(Px < min_x)
      return true;
    else
    {
      if(Ax != Bx)
	slope_line_segment = (By-Ay)/(Bx-Ax);
      else
	slope_line_segment = numeric_limits<double>::infinity();
      if(Ax != Px)
	slope_test_line = (Py-Ay)/(Px-Ax);
      else
	slope_test_line = numeric_limits<double>::infinity();
      if(slope_test_line >= slope_test_line)
	return true;
      else
	return false;
    }
}

bool Utilities::is_PointContained(double x, double y, vector < vector <double> > &Polygon)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  int nedges;
  int n_intersections;

  /******************************************************/
  /* Determine if point (x,y) resides inside of Polygon */
  /******************************************************/
  nedges = (int)Polygon.size();
  n_intersections = 0;
  for(int j=0; j<nedges; j++)
  {
    int k = (j+1)%nedges;
    if(do_LinesIntersect(x, y, Polygon[j][0], Polygon[j][1], Polygon[k][0], Polygon[k][1]))
      n_intersections++;
  }
  if(n_intersections%2 == 1)
    return true;
  
  return false;
}

double Utilities::ImageTotalArea(vector <double> &selected_incidence_angles, vector <IncidenceAngles> &ia, vector <ImageSets> &imagesets)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double total_area;
  int n;
  int npolygons;
  string field;
  vector < vector <double> > Polygon_Overlap(4, vector <double> (2));

  /*******************************************/
  /* Resultant overlapping polygon variables */
  /*******************************************/
  vector <polygon> input;
  vector <polygon> output;

  /*********************************************************/
  /* Sort incidence angle (ia) vector based on name column */
  /*********************************************************/
  field = "name";
  SortData <IncidenceAngles> sortincidenceangles(ia, field);
  sortincidenceangles.arrange();
  ia = sortincidenceangles.GetData();

  /************************************************************/
  /* Calculate total area by iterating through the image sets */
  /* vector and selecting regions used for the analysis       */
  /************************************************************/
  n = (int)ia.size();
  npolygons = 0;
  for(int i=0; i<(int)imagesets.size(); i++)
  {
    /**********************/
    /* Current image name */
    /**********************/
    string image_name = imagesets[i].GetName();

    /**********************************************/
    /* Retrieve incidence angle for current image */
    /**********************************************/
    int nth_element = SearchData<IncidenceAngles>::BinarySearch(ia, 0, n-1, field, &image_name);
    double angle = ia[nth_element].GetIncidence_angle();
    
    /********************************************************/
    /* Include region in area calculation if it's incidence */
    /* angle is within the selected incidence angle list    */
    /********************************************************/
    bool skip = true;
    for(int j=0; j<(int)selected_incidence_angles.size(); j++)
      if(angle == selected_incidence_angles[j])
      {
	skip = false;
	break;
      }
    if(skip)
      continue;

    /****************************/
    /* Region shape information */
    /****************************/
    Polygon_Overlap[0][0] = imagesets[i].GetUpper_left_x();
    Polygon_Overlap[0][1] = imagesets[i].GetUpper_left_y();
    Polygon_Overlap[1][0] = imagesets[i].GetUpper_right_x();
    Polygon_Overlap[1][1] = imagesets[i].GetUpper_right_y();
    Polygon_Overlap[2][0] = imagesets[i].GetLower_right_x();
    Polygon_Overlap[2][1] = imagesets[i].GetLower_right_y();
    Polygon_Overlap[3][0] = imagesets[i].GetLower_left_x();
    Polygon_Overlap[3][1] = imagesets[i].GetLower_left_y();

    /******************************/
    /* Gather overlapping regions */
    /******************************/
    string buffer = "POLYGON(("+to_string(Polygon_Overlap[0][0])+" "+to_string(Polygon_Overlap[0][1])+","+
                                to_string(Polygon_Overlap[1][0])+" "+to_string(Polygon_Overlap[1][1])+","+
	                        to_string(Polygon_Overlap[2][0])+" "+to_string(Polygon_Overlap[2][1])+","+
	                        to_string(Polygon_Overlap[3][0])+" "+to_string(Polygon_Overlap[3][1])+","+
	                        to_string(Polygon_Overlap[0][0])+" "+to_string(Polygon_Overlap[0][1])+"))";
    polygon current_polygon;
    boost::geometry::read_wkt(buffer.c_str(), current_polygon);
    boost::geometry::correct(current_polygon);
    input.push_back(current_polygon);

    /***********************************/
    /* Update number of polygons added */
    /***********************************/
    npolygons++;
  }

  /******************/
  /* Calculate Area */
  /******************/
  int i = 0;
  total_area = 0;
  union_polys(input, output);
  BOOST_FOREACH(polygon const& p, output)
  {
    //cout << i++ << ": " << boost::geometry::area(p) << endl;
    i++;
    total_area += boost::geometry::area(p);
  }

  return total_area;
}

vector <double> Utilities::RetrieveUniqueIncidenceAngles(vector <IncidenceAngles> &incidenceangles)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  set <double> input;
  vector <double> unique_incidence_angles;

  /**************************************************************/
  /* Sort incidenceangles vector based on incidenceangle column */
  /**************************************************************/
  SortData <IncidenceAngles> sortincidenceangles(incidenceangles, "incidence_angle");
  sortincidenceangles.arrange();
  incidenceangles = sortincidenceangles.GetData();

  /******************************************/
  /* Retrieve unique incidence angle values */
  /******************************************/
  for(int i=0; i<(int)incidenceangles.size(); i++)
    input.insert(incidenceangles[i].GetIncidence_angle());

  /*****************************/
  /* Copy set values to vector */
  /*****************************/
  copy(input.begin(), input.end(), back_inserter(unique_incidence_angles));
  
  return unique_incidence_angles;
}

void Utilities::RetrieveCraterCatalog(double incidence_angle_1, double incidence_angle_2, vector <OverlappedImages> &OI, vector <Marks> &marks, vector < vector <string> > &imagenames, vector <Marks> &RM1, vector <Marks> &RM2, vector <double> &OA1, vector <double> &OA2, vector <int> &AID1, vector <int> &AID2)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  double incidence_angle_sum;
  double total_area;
  int counter;
  int npolygons;
  int old_image_id1;
  int old_image_id2;
  int point_set_size;
  set <string> imagenames1;
  set <string> imagenames2;
  set < pair < int, pair <double, double> > > point;
  string field;
  vector <double> overlap_area_1;
  vector <double> overlap_area_2;
  vector <int> area_id_1;
  vector <int> area_id_2;
  vector <int> overlap_entry;
  vector <Marks> retained_marks_1;
  vector <Marks> retained_marks_2;
  vector < vector <double> > Polygon_Overlap(4, vector <double> (2));
  vector < vector <string> > imgnames(2, vector <string> ());
  
  /*******************************************/
  /* Resultant overlapping polygon variables */
  /*******************************************/
  vector <polygon> input;
  vector <polygon> output;

  /***********************/
  /* Sort overlap vector */
  /***********************/
  field = "overlap_minimum_x";
  SortData <OverlappedImages> sortoverlap(OI, field);
  sortoverlap.arrange();
  OI = sortoverlap.GetData();
  
  /*********************/
  /* Sort marks vector */
  /*********************/
  field = "image_id";
  SortData <Marks> sortmarks(marks, field);
  sortmarks.arrange();
  marks = sortmarks.GetData();

  /******************************************************/
  /* Used as rejection criterion for overlapping images */
  /******************************************************/
  incidence_angle_sum = incidence_angle_1+incidence_angle_2;
  
  /*********************************************/
  /* Iterate through overlapping images vector */
  /*********************************************/
  counter = 0;
  point_set_size = 0;
  total_area = 0;
  npolygons = 0;
  old_image_id1 = -1;
  old_image_id2 = -1;
  int n = (int)marks.size();
  for(int i=0; i<(int)OI.size(); i++)
  {
    /*********************************************/
    /* Reject overlapping images whose incidence */
    /* angle sum doesn't match the sum above     */
    /*********************************************/
    if(incidence_angle_sum != OI[i].GetImage1_incidence_angle()+OI[i].GetImage2_incidence_angle())
      continue;
    if((incidence_angle_1 != OI[i].GetImage1_incidence_angle()) && (incidence_angle_1 != OI[i].GetImage2_incidence_angle()))
      continue;
    
    /*************/
    /* Image ids */
    /*************/
    int image1_id;
    int image2_id;
    string image1_name;
    string image2_name;
    if(incidence_angle_1 == OI[i].GetImage1_incidence_angle())
    {
      image1_id = OI[i].GetImage1_id();
      image1_name = OI[i].GetImage1_name().substr(0, 12);
      image2_id = OI[i].GetImage2_id();
      image2_name = OI[i].GetImage2_name().substr(0, 12);
    }
    else
    {
      image1_id = OI[i].GetImage2_id();
      image1_name = OI[i].GetImage2_name().substr(0, 12);
      image2_id = OI[i].GetImage1_id();
      image2_name = OI[i].GetImage1_name().substr(0, 12);
    }

    /****************************************/
    /* Reject moon_mappers_tutorial_4 image */
    /****************************************/
    if((image1_id == 60639) || (image2_id == 60639))
      continue;

    /******************/
    /* Overlap region */
    /******************/
    Polygon_Overlap[0][0] = OI[i].GetOverlap_upper_left_x();
    Polygon_Overlap[0][1] = OI[i].GetOverlap_upper_left_y();
    Polygon_Overlap[1][0] = OI[i].GetOverlap_upper_right_x();
    Polygon_Overlap[1][1] = OI[i].GetOverlap_upper_right_y();
    Polygon_Overlap[2][0] = OI[i].GetOverlap_lower_right_x();
    Polygon_Overlap[2][1] = OI[i].GetOverlap_lower_right_y();
    Polygon_Overlap[3][0] = OI[i].GetOverlap_lower_left_x();
    Polygon_Overlap[3][1] = OI[i].GetOverlap_lower_left_y();

    /*********************************************************************/
    /* Isolate marks that are associated with current overlapping images */
    /*********************************************************************/
    int index1 = SearchData<Marks>::FirstOccurence(marks, 0, n-1, field, &image1_id);
    int index2 = SearchData<Marks>::LastOccurence(marks, 0, n-1, field, &image1_id);

    /***********************************************************************/
    /* Determine which marks are in overlap region and record unique marks */
    /***********************************************************************/
    bool include_area = false;
    if(index1 != -1)
    {
      for(int j=index1; j<=index2; j++)
      {
	double x = marks[j].GetPhysical_x();
	double y = marks[j].GetPhysical_y();
	int id = marks[j].GetId();
	pair <double, double> position(x, y);
	pair < double, pair <double, double> > entry(id, position);
	if(point.find(entry) == point.end())
	{
	  if(is_PointContained(x, y, Polygon_Overlap))
	  {
	    retained_marks_1.push_back(marks[j]);
	    area_id_1.push_back(OI[i].GetId());
	    imagenames1.insert(image1_name);
	    point.insert(entry);
	    include_area = true;
	  }
	}
      }
    }
    
    /*********************************************************************/
    /* Isolate marks that are associated with current overlapping images */
    /*********************************************************************/
    index1 = SearchData<Marks>::FirstOccurence(marks, 0, n-1, field, &image2_id);
    index2 = SearchData<Marks>::LastOccurence(marks, 0, n-1, field, &image2_id);

    /***********************************************************************/
    /* Determine which marks are in overlap region and record unique marks */
    /***********************************************************************/
    if(index1 != -1)
    {
      for(int j=index1; j<=index2; j++)
      {
	double x = marks[j].GetPhysical_x();
	double y = marks[j].GetPhysical_y();
	int id = marks[j].GetId();
	pair <double, double> position(x, y);
	pair < int, pair <double, double> > entry(id, position);
	if(point.find(entry) == point.end())
	{
	  if(is_PointContained(x, y, Polygon_Overlap))
	  {
	    retained_marks_2.push_back(marks[j]);
	    area_id_2.push_back(OI[i].GetId());
	    imagenames2.insert(image2_name);
	    point.insert(entry);
	    include_area = true;
	  }
	}
      }
    }
    
    /****************************************************************/
    /* Include surface area as we iterate through overlapping pairs */
    /* if a mark has been added to the list of raw user markings    */
    /****************************************************************/
    if(include_area)
    {
      /******************************/
      /* Gather overlapping regions */
      /******************************/
      string buffer = "POLYGON(("+to_string(Polygon_Overlap[0][0])+" "+to_string(Polygon_Overlap[0][1])+","+
	                          to_string(Polygon_Overlap[1][0])+" "+to_string(Polygon_Overlap[1][1])+","+
	                          to_string(Polygon_Overlap[2][0])+" "+to_string(Polygon_Overlap[2][1])+","+
	                          to_string(Polygon_Overlap[3][0])+" "+to_string(Polygon_Overlap[3][1])+","+
	                          to_string(Polygon_Overlap[0][0])+" "+to_string(Polygon_Overlap[0][1])+"))";
      polygon current_polygon;
      boost::geometry::read_wkt(buffer.c_str(), current_polygon);
      boost::geometry::correct(current_polygon);
      input.push_back(current_polygon);

      /***********************************/
      /* Update number of polygons added */
      /***********************************/
      npolygons++;
    }
  }

  /*******************************/
  /* Retrieve master image names */
  /*******************************/
  copy(imagenames1.begin(), imagenames1.end(), back_inserter(imgnames[0]));
  copy(imagenames2.begin(), imagenames2.end(), back_inserter(imgnames[1]));
  imagenames = imgnames;

  /******************/
  /* Calculate Area */
  /******************/
  int i = 0;
  union_polys(input, output);
  BOOST_FOREACH(polygon const& p, output)
  {
    //cout << i++ << ": " << boost::geometry::area(p) << endl;
    i++;
    total_area += boost::geometry::area(p);
  }

  //cout << "True total area: " << total_area*(m2km*m2km) << " km^2" << endl;
  //cout << "Number of polygons used: " << npolygons << " : " << output.size() << endl;

  /****************************/
  /* Record surviving craters */
  /****************************/
  RM1 = retained_marks_1;
  RM2 = retained_marks_2;

  /**************************************************/
  /* Record area of overlapping region between both */
  /* NACs from which marks are associated with      */
  /**************************************************/
  int n1 = (int)retained_marks_1.size();
  int n2 = (int)retained_marks_2.size();
  overlap_area_1.assign(n1, total_area);
  overlap_area_2.assign(n2, total_area);
  OA1 = overlap_area_1;
  OA2 = overlap_area_2;

  /***************************************************/
  /* Record which areas are contributing to analysis */
  /***************************************************/
  AID1 = area_id_1;
  AID2 = area_id_2;

  return;
}

vector <OverlappedImages> Utilities::FindDifferentIncidenceAngleOverlappingImages(vector <OverlappedImages> &OI)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  string field;
  vector <OverlappedImages> DIA;

  /**************************************/
  /* Extracting overlapping images that */
  /* are at different incidence angles  */
  /**************************************/
  for(int i=0; i<(int)OI.size(); i++)
  {
    double incidenceangle1 = OI[i].GetImage1_incidence_angle();
    double incidenceangle2 = OI[i].GetImage2_incidence_angle();
    if(incidenceangle1 != incidenceangle2)
      DIA.push_back(OI[i]);
  } 
  
  return DIA;
}

vector <OverlappedImages> Utilities::FindOverlappingImages(vector <Images> &images, vector <IncidenceAngles> &incidenceangles)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  int counter;
  int n1;
  int n2;
  string field1;
  string field2;
  vector <OverlappedImages> OLImages;

  /***********************/
  /* Define field values */
  /***********************/
  field1 = "minimum_x";
  field2 = "name";

  /***********************************************/
  /* Sort images vector based on "field1" column */
  /***********************************************/
  SortData <Images> sortimages(images, field1);
  sortimages.arrange();
  images = sortimages.GetData();
  
  /********************************************************/
  /* Sort incidenceangles vector based on "field2" column */
  /********************************************************/
  SortData <IncidenceAngles> sortincidenceangles(incidenceangles, field2);
  sortincidenceangles.arrange();
  incidenceangles = sortincidenceangles.GetData();
  
  /*******************************/
  /* Iterate over all sub-images */
  /*******************************/
  counter = 0;
  n1 = (int)images.size();
  n2 = (int)incidenceangles.size();
  for(int i=0; i<n1; i++)
  { 
    /******************************************/
    /* Retrieve pertinent image 1 information */
    /******************************************/
    int image1_id = images[i].GetId();
    string image1_name = images[i].GetName();
    double image1_upper_left_x = images[i].GetUpper_left_x();
    double image1_upper_left_y = images[i].GetUpper_left_y();
    double image1_upper_right_x = images[i].GetUpper_right_x();
    double image1_upper_right_y = images[i].GetUpper_right_y();
    double image1_lower_right_x = images[i].GetLower_right_x();
    double image1_lower_right_y = images[i].GetLower_right_y();
    double image1_lower_left_x = images[i].GetLower_left_x();
    double image1_lower_left_y = images[i].GetLower_left_y();
    double image1_minimum_x = images[i].GetMinimum_x();
    double image1_minimum_y = images[i].GetMinimum_y();
    double image1_maximum_x = images[i].GetMaximum_x();
    double image1_maximum_y = images[i].GetMaximum_y();
    double image1_area = images[i].GetArea();
    vector < vector <double> > image1_shape_vector = images[i].GetShape_vector();
    int length = image1_name.find_first_of("_");
    string basename = image1_name.substr(0, length);
    int nth_element = SearchData<IncidenceAngles>::BinarySearch(incidenceangles, 0, n2-1, field2, &basename);
    double image1_incidence_angle = incidenceangles[nth_element].GetIncidence_angle();
    
    /**************************************************/
    /* Determine ending index of optimal search range */
    /**************************************************/
    int index = SearchData<Images>::LastNearestValue(images, i+1, n1-1, field1, &image1_maximum_x);
    
    /************************************/
    /* Ensure index is not out of range */
    /************************************/
    if (index >= n1)
      index = n1-1;
    
    /************************************************************/
    /* Iterate over a select few sub-images after the ith image */
    /************************************************************/
    for(int j=i+1; j<=index; j++)
    {
      /**************************************/
      /* Retrieve image 2 shape information */
      /**************************************/
      double image2_minimum_x = images[j].GetMinimum_x();
      double image2_minimum_y = images[j].GetMinimum_y();
      double image2_maximum_x = images[j].GetMaximum_x();
      double image2_maximum_y = images[j].GetMaximum_y();
      double image2_area = images[j].GetArea();
      vector < vector <double> > image2_shape_vector = images[j].GetShape_vector();
      
      /*******************************/
      /* Check if two images overlap */
      /*******************************/
      CheckOverlap OL(image1_shape_vector,
		      image1_minimum_x, image1_minimum_y,
		      image1_maximum_x, image1_maximum_y,
		      image1_area,
		      image2_shape_vector,
		      image2_minimum_x, image2_minimum_y,
		      image2_maximum_x, image2_maximum_y,
		      image2_area);
      
      if(OL.are_Overlapping())
      {	
	/*****************************************************/
	/* Retrieve additional pertinent image 2 information */
	/*****************************************************/
	int image2_id = images[j].GetId();
	string image2_name = images[j].GetName();
	double image2_upper_left_x = images[j].GetUpper_left_x();
	double image2_upper_left_y = images[j].GetUpper_left_y();
	double image2_upper_right_x = images[j].GetUpper_right_x();
	double image2_upper_right_y = images[j].GetUpper_right_y();
	double image2_lower_right_x = images[j].GetLower_right_x();
	double image2_lower_right_y = images[j].GetLower_right_y();
	double image2_lower_left_x = images[j].GetLower_left_x();
	double image2_lower_left_y = images[j].GetLower_left_y();
        length = image2_name.find_first_of("_");
	basename = image2_name.substr(0, length);
	nth_element = SearchData<IncidenceAngles>::BinarySearch(incidenceangles, 0, n2-1, field2, &basename);
	double image2_incidence_angle = incidenceangles[nth_element].GetIncidence_angle();
	
	/**********************************************/
	/* Calculate overlap bounding region and area */
	/**********************************************/
	OL.AuxilaryFunction();	
	vector < vector <double> > OverlappingBoundary = OL.GetPolygon_Overlap();
	double overlap_area = OL.GetPolygon_Overlap_Area();

	/*************************************/
	/* In case overlap exists on an edge */
	/*************************************/
	if(OverlappingBoundary.size() != 4)
	  continue;
	
	/***************************************/
	/* Retrieve overlap region information */
	/***************************************/
	double overlap_upper_left_x = OverlappingBoundary[0][0];
	double overlap_upper_left_y = OverlappingBoundary[0][1];
	double overlap_upper_right_x = OverlappingBoundary[1][0];
	double overlap_upper_right_y = OverlappingBoundary[1][1];
	double overlap_lower_right_x = OverlappingBoundary[2][0];
	double overlap_lower_right_y = OverlappingBoundary[2][1];
	double overlap_lower_left_x = OverlappingBoundary[3][0];
	double overlap_lower_left_y = OverlappingBoundary[3][1];
	
	/*****************************************/
	/* Record overlapping images information */
	/*****************************************/
	OLImages.push_back(OverlappedImages(counter,
					    image1_id,
					    image1_name,
					    image1_upper_left_x,
					    image1_upper_left_y,
					    image1_upper_right_x,
					    image1_upper_right_y,
					    image1_lower_right_x,
					    image1_lower_right_y,
					    image1_lower_left_x,
					    image1_lower_left_y,
					    image1_area,
					    image1_incidence_angle,
					    image2_id,
					    image2_name,
					    image2_upper_left_x,
					    image2_upper_left_y,
					    image2_upper_right_x,
					    image2_upper_right_y,
					    image2_lower_right_x,
					    image2_lower_right_y,
					    image2_lower_left_x,
					    image2_lower_left_y,
					    image2_area,
					    image2_incidence_angle,
					    overlap_upper_left_x,
					    overlap_upper_left_y,
					    overlap_upper_right_x,
					    overlap_upper_right_y,
					    overlap_lower_right_x,
					    overlap_lower_right_y,
					    overlap_lower_left_x,
					    overlap_lower_left_y,
					    overlap_area));
	counter++;
      }
    }
  }

  return OLImages;
}

vector <OverlappedImages> Utilities::FindSameScaleOverlappingImages(vector <OverlappedImages> &OI, int scale)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  int p1;
  int p2;
  int length;
  string field;
  vector <OverlappedImages> SameScaleOverlappingImages;

  /*************************************************************/
  /* Retrieve all overlapping images with the same scale value */
  /*************************************************************/
  for(int i=0; i<(int)OI.size(); i++)
  {
    string image1_name = OI[i].GetImage1_name();
    string image2_name = OI[i].GetImage2_name();
    p1 = image1_name.find("_")+1;
    p2 = image1_name.rfind("_");
    length = p2-p1;
    int scale1 = stoi(image1_name.substr(p1, length), nullptr);
    p1 = image2_name.find("_")+1;
    p2 = image2_name.rfind("_");
    length = p2-p1;
    int scale2 = stoi(image2_name.substr(p1, length), nullptr);
    if(scale1 == scale2)
    {
      if(scale < 3)
      {
	if(scale1 == scale)
	  SameScaleOverlappingImages.push_back(OI[i]);
      }
      else
	SameScaleOverlappingImages.push_back(OI[i]);
    }
  }

  return SameScaleOverlappingImages;
}

vector <OverlappedImages> Utilities::FindTotalOverlappingImages(vector <OverlappedImages> &OI)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  string field;
  vector <OverlappedImages> TOI;

  /****************************/
  /* Retrieve neccessary data */
  /****************************/
  for(int i=0; i<(int)OI.size(); i++)
  {
    double imagearea1 = OI[i].GetImage1_area();
    double imagearea2 = OI[i].GetImage2_area();
    double oarea = OI[i].GetOverlap_area();
    double overlap_percentage = 100*oarea/Min(imagearea1, imagearea2);
    if(overlap_percentage == 100)
      TOI.push_back(OI[i]);
  }

  return TOI;
}

void Utilities::PrintCraterCatalog(double incidence_angle_1, double incidence_angle_2, vector <IncidenceAngles> &IA, vector <OverlappedImages> &OI, vector <Marks> &marks, int run, bool print)
{
  /****************************************************/
  /* Declaration/Initialization of function variables */
  /****************************************************/
  int nelements;
  ofstream File;
  string field;
  string filename;
  string master_image_1_name;
  string master_image_2_name;
  vector <double> OA1;
  vector <double> OA2;
  vector <int> AID1;
  vector <int> AID2;
  vector <Marks> RM1;
  vector <Marks> RM2;
  vector < vector <string> > imagenames(2, vector <string> ());
  
  /**********************/
  /* Retrieve NAC marks */
  /**********************/
  RetrieveCraterCatalog(incidence_angle_1, incidence_angle_2, OI, marks, imagenames, RM1, RM2, OA1, OA2, AID1, AID2);

  /****************************/
  /* Retrieve NAC image names */
  /****************************/
  if(imagenames[0].size() == 1)
    master_image_1_name = imagenames[0][0];
  else if(imagenames[0].size() == 2)
    master_image_1_name = imagenames[0][0].substr(0, 10)+"LERE";
  else
  {
    printf("Error in PrintCraterCatalog: Invalid number of imagenames (%d).\nNow terminating program...\n", (int)imagenames[0].size());
    for(int i=0; i<(int)imagenames[0].size(); i++)
      cout << imagenames[0][i] << endl;
    exit(EXIT_FAILURE);
  }
  if(imagenames[1].size() == 1)
    master_image_2_name = imagenames[1][0];
  else if(imagenames[1].size() == 2)
    master_image_2_name = imagenames[1][0].substr(0, 10)+"LERE";
  else
  {
    printf("Error in PrintCraterCatalog: Invalid number of imagenames (%d).\nNow terminating program...\n", (int)imagenames[1].size());
    for(int i=0; i<(int)imagenames[1].size(); i++)
      cout << imagenames[0][i] << endl;
    exit(EXIT_FAILURE);
  }

  /**************************/
  /* Create output filename */
  /**************************/
  filename = "Crater_catalog_"+to_string(run)+"_"+master_image_1_name+"_"+to_string(incidence_angle_1)+".txt";

  /***************************/
  /* Print to screen or file */
  /***************************/
  nelements = (int)RM1.size();
  if(print)
  {
    File.open(filename.c_str());
    File << "X\t\tY\t\tD\t\tC\t\tA\t\tID" << endl;
    for(int i=0; i<nelements; i++)
      File << setprecision(7) << setw(10) << left << RM1[i].GetPhysical_x() << "\t"
	   << setprecision(7) << setw(10) << left << RM1[i].GetPhysical_y() << "\t"
	   << setprecision(7) << setw(10) << left << RM1[i].GetPhysical_diameter() << "\t"
	   << setprecision(7) << setw(10) << left << 1 << "\t"
	   << setprecision(7) << setw(10) << left << OA1[i] << "\t"
	   << setprecision(7) << setw(10) << left << AID1[i]
	   << endl;
    File.close();
  }
  else
  {
    cout << "\nCrater Catalog 1: " << master_image_1_name << endl;
    cout << "Long\t\tLat\t\tX\t\tY\t\tD\t\tC\t\tA\t\tID" << endl;
    for(int i=0; i<nelements; i++)
      cout << setprecision(7) << setw(10) << left << RM1[i].GetLongitude() << "\t"
	   << setprecision(7) << setw(10) << left << RM1[i].GetLatitude() << "\t"
	   << setprecision(7) << setw(10) << left << RM1[i].GetPhysical_x() << "\t"
	   << setprecision(7) << setw(10) << left << RM1[i].GetPhysical_y() << "\t"
	   << setprecision(7) << setw(10) << left << RM1[i].GetPhysical_diameter() << "\t"
	   << setprecision(7) << setw(10) << left << 1 << "\t"
	   << setprecision(7) << setw(10) << left << OA1[i] << "\t"
	   << setprecision(7) << setw(10) << left << AID1[i] 
	   << endl;
  }

  /**************************/
  /* Create output filename */
  /**************************/
  filename = "Crater_catalog_"+to_string(run)+"_"+master_image_2_name+"_"+to_string(incidence_angle_2)+".txt";

  /***************************/
  /* Print to screen or file */
  /***************************/
  nelements = (int)RM2.size();
  if(print)
  {
    File.open(filename.c_str());
    File << "X\t\tY\t\tD\t\tC\t\tA\t\tID" << endl;
    for(int i=0; i<nelements; i++)
      File << setprecision(7) << setw(10) << left << RM2[i].GetPhysical_x() << "\t"
	   << setprecision(7) << setw(10) << left << RM2[i].GetPhysical_y() << "\t"
	   << setprecision(7) << setw(10) << left << RM2[i].GetPhysical_diameter() << "\t"
	   << setprecision(7) << setw(10) << left << 1 << "\t"
	   << setprecision(7) << setw(10) << left << OA2[i] << "\t"
	   << setprecision(7) << setw(10) << left << AID2[i] 
	   << endl;
    File.close();
  }
  else
  {
    cout << "\nCrater Catalog 2: " << master_image_2_name << endl;
    cout << "Long\t\tLat\t\tX\t\tY\t\tD\t\tC\t\tA\t\tID" << endl;
    for(int i=0; i<nelements; i++)
      cout << setprecision(7) << setw(10) << left << RM2[i].GetLongitude() << "\t"
	   << setprecision(7) << setw(10) << left << RM2[i].GetLatitude() << "\t"
	   << setprecision(7) << setw(10) << left << RM2[i].GetPhysical_x() << "\t"
	   << setprecision(7) << setw(10) << left << RM2[i].GetPhysical_y() << "\t"
	   << setprecision(7) << setw(10) << left << RM2[i].GetPhysical_diameter() << "\t"
	   << setprecision(7) << setw(10) << left << 1 << "\t"
	   << setprecision(7) << setw(10) << left << OA2[i] << "\t"
	   << setprecision(7) << setw(10) << left << AID2[i] 
	   << endl;
  }
  
  return;
}

void Utilities::union_polys(vector <polygon> In_polys, vector <polygon> &Out_polys)
{
    std::vector<polygon> temp_polys;
    bool *considered = new bool [In_polys.size()];
    for(unsigned i = 0 ; i < In_polys.size() ; i++) considered[i] = false;
    for(unsigned i = 0 ; i < In_polys.size()/2; i++)
    {
        if(!considered[i])
        {
            polygon inetr = In_polys.at(i);
            for(unsigned j = i + 1 ; j < In_polys.size() ; j++)
            {

                if(!considered[j])
                {
                    temp_polys.clear();
                    boost::geometry::union_(inetr, In_polys.at(j) , temp_polys);
                    if(temp_polys.size() == 1)
                    {
                        inetr = temp_polys.at(0);
                        considered[j] = true;
                        j = i;
                    }
                }
            }
            Out_polys.push_back(inetr);
        }
    }
}
