#ifndef FP_ENHANCER
#define FP_ENHANCER

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "OfDetector.hpp"
#include "GaborFilterbank.hpp"
using namespace std;

//----------------------------------------------------------------------
//Fingerprint (FP) Enhancer
//----------------------------------------------------------------------
class FpEnhancer {
public:
   //constructors & destructor
	FpEnhancer();
	FpEnhancer(double lam, int size, double sigma);
   //getters & setters
   
   //key methods
   void enhance(const cv::Mat& fpImg, cv::Mat& enhancedImg);
   
   //operators

private:
   //attributes
	int blockSize;
	double l; //lamda
	double s; // sigma
	OfDetector orientationFieldDetecter;
	GaborFilterbank filterbank;
   //helper (private) methods

};
//----------------------------------------------------------------------
#endif