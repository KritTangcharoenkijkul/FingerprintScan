#ifndef GABOR_FILTER
#define GABOR_FILTER

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;

//----------------------------------------------------------------------
//Gabor filter
//----------------------------------------------------------------------

class GaborFilter : public cv::Mat {
public:
   //constructors & destructor
   GaborFilter(cv::Size size,double sigma, double orientVal, double freqVal);

   //getters & setters
   double getTheta(){ return theta; }
   Mat getKernel(){ return kernel; }
   //key methods
   //operators

private:
   //attributes
	Mat kernel;
	double theta;
   //helper (private) methods

};
//----------------------------------------------------------------------
#endif
