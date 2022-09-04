#ifndef MINUTIAE_SET
#define MINUTIAE_SET

#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
using namespace std;

//----------------------------------------------------------------------
const int M_TYPE_UNKNOWN      = 0;
const int M_TYPE_ENDPOINT     = 1;
const int M_TYPE_BIFURCATION  = 2;
//----------------------------------------------------------------------
struct Minutiae {
   //constructors & destructor
   Minutiae( cv::Point2f posVal, int typeVal = M_TYPE_UNKNOWN ) : pos(posVal), type(typeVal) {}
   
   //attributes
   cv::Point2f pos;
   int type;   //M_TYPE_UNKNOWN, M_TYPE_ENDPOINT, M_TYPE_BIFURCATION
};
//----------------------------------------------------------------------
typedef vector<Minutiae> MnSet;
//----------------------------------------------------------------------
#endif