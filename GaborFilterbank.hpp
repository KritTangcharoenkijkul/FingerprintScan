#ifndef GABOR_FILTERBANK
#define GABOR_FILTERBANK

#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "OfDetector.hpp"
#include "GaborFilter.hpp"
using namespace std;

//----------------------------------------------------------------------
//Gabor filterbank
//----------------------------------------------------------------------

class GaborFilterbank {
public:

   //constructors & destructor

	GaborFilterbank(double fv, int ks, double sg);

   //getters & setters

	void setFrequency(int f){ freq = f; }
	void setSigma(int ss){ kernelSize = ss; }
	void setKernelSize(int size){ kernelSize = size; }
	cv::Mat getFilter(float theta);

   //key methods

   void filter(const cv::Mat& fpImg, const cv::Mat& ofImg, cv::Mat& filteredImg);

   //operators

private:

   //attributes

	double ofBlocksize;
	double freq;
	int kernelSize;
	double sigma;

   vector<GaborFilter> gbs;

   //helper (private) methods

   void generateFilter();

};
//----------------------------------------------------------------------
#endif
