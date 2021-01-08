/* Purpose: Attempts to perform same function as IDL's Readcol command. */

/***********************/
/* Include header file */
/***********************/
#include "Readcol.h"

using namespace std;

int Readcol::Read(string filename, string format, ...)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  ifstream InFile;
  string buffer;
  va_list vargs;
  vector <string> fmt;
  
  /************************************/
  /* Convert format string to vector. */
  /************************************/
  fmt = FormatParser(format);

  /*************************/
  /* Open file for reading */
  /*************************/
  if(FileExists(filename))
    InFile.open(filename.c_str());
  else {
    cout << "Error in Readcol::Read(): File " << filename << " does not exist!" << endl;
    exit(EXIT_FAILURE);
  }
  
  /**************************/
  /* Read in data from file */
  /**************************/
  unsigned rownum = 0;
  while(getline(InFile, buffer)) {
    double *double_vector;
    int *integer_vector;
    string *string_vector;
    istringstream iss (buffer);
    bool keep = true;
    va_start(vargs, format);
    for (int n = 0; n < (int)fmt.size(); n++) {
      if((fmt[n].compare("%*") == 0) || (fmt[n].compare("X") == 0))
	continue;
      switch(str2int(fmt[n].c_str())) {
      case str2int("%lf"): {
  	double d;
	  if(!(iss >> d))
  	  keep = false;
	double_vector = va_arg(vargs, double *);
	double_vector[rownum] = d;
  	break;
      }
      case str2int("%d"): {
  	int i;
  	if(!(iss >> i))
  	  keep = false;
	integer_vector = va_arg(vargs, int *);
	integer_vector[rownum] = i;
  	break;
      }
      case str2int("%s"): {
  	string s;
  	if(!(iss >> s))
  	  keep = false;
	string_vector = va_arg(vargs, string *);
	string_vector[rownum] = s;
  	break;
      }
      default:
  	cout << "Error in Readcol::Read(): Unsupported data format." << endl;
  	exit(EXIT_FAILURE);
      }
    }

    /************************************************/
    /* Establish conditions to remove unwanted data */
    /************************************************/
    if(keep)
      rownum++;
    if(InFile.eof() && !keep) {
      double_vector[rownum] = 0;
      integer_vector[rownum] = 0;
      string_vector[rownum] = "";
    }
    va_end(vargs);
  }
  
  /**************/
  /* Close file */
  /**************/
  InFile.close();

  return rownum;
}

int Readcol::Read(string filename, string skipline, int offset, string format, ...)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  ifstream InFile;
  string buffer;
  va_list vargs;
  vector <string> fmt;
  
  /************************************/
  /* Convert format string to vector. */
  /************************************/
  fmt = FormatParser(format);

  /*************************/
  /* Open file for reading */
  /*************************/
  if(FileExists(filename))
    InFile.open(filename.c_str());
  else {
    cout << "Error in Readcol::Read(): File " << filename << " does not exist!" << endl;
    exit(EXIT_FAILURE);
  }
  
  /**************************/
  /* Read in data from file */
  /**************************/
  unsigned rownum = 0;
  while(getline(InFile, buffer)) {
    // Apply simple skipline condition
    if (offset >= 0) {
      if (((int)buffer.length() >= offset) && buffer.compare(offset, skipline.length(), skipline) == 0)
	continue;
    }
    else {
      if (buffer.compare(buffer.length()-skipline.length(), skipline.length(), skipline) == 0)
	continue;
    }
      
    

    // Continue reading line
    double *double_vector;
    int *integer_vector;
    string *string_vector;
    istringstream iss (buffer);
    bool keep = true;
    va_start(vargs, format);
    for (int n = 0; n < (int)fmt.size(); n++) {
      if((fmt[n].compare("%*") == 0) || (fmt[n].compare("X") == 0))
	continue;
      switch(str2int(fmt[n].c_str())) {
      case str2int("%lf"): {
  	double d;
	  if(!(iss >> d))
  	  keep = false;
	double_vector = va_arg(vargs, double *);
	double_vector[rownum] = d;
  	break;
      }
      case str2int("%d"): {
  	int i;
  	if(!(iss >> i))
  	  keep = false;
	integer_vector = va_arg(vargs, int *);
	integer_vector[rownum] = i;
  	break;
      }
      case str2int("%s"): {
  	string s;
  	if(!(iss >> s))
  	  keep = false;
	string_vector = va_arg(vargs, string *);
	string_vector[rownum] = s;
  	break;
      }
      default:
  	cout << "Error in Readcol::Read(): Unsupported data format." << endl;
  	exit(EXIT_FAILURE);
      }
    }

    /************************************************/
    /* Establish conditions to remove unwanted data */
    /************************************************/
    if(keep)
      rownum++;
    if(InFile.eof() && !keep) {
      double_vector[rownum] = 0;
      integer_vector[rownum] = 0;
      string_vector[rownum] = "";
    }
    va_end(vargs);
  }
  
  /**************/
  /* Close file */
  /**************/
  InFile.close();

  return rownum;
}

vector <string> Readcol::FormatParser(string format)
{
  /*************************************/
  /* Declaration of function variables */
  /*************************************/
  vector <string> fmt;
  
  /***********************/
  /* Parse format string */
  /***********************/
  istringstream iss_fmt (format);
  for(unsigned i = 0; i < format.length(); i++) {
    int pos = format.find('%', i);
    if(pos == -1) break;
    string a;
    iss_fmt >> a;
    fmt.push_back(a);
    i = pos;
  }

  return fmt;
}
