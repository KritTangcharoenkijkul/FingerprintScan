#ifndef MN_EXTRACTOR
#define MN_EXTRACTOR

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "MnSet.hpp"
using namespace std;

//----------------------------------------------------------------------
//Minutiae Extractor
//----------------------------------------------------------------------
class MnExtractor {
public:
   //constructors & destructor
   
   //getters & setters
   
   //key methods
   void extract(const cv::Mat& enhancedImg, MnSet& mnSet);
   
   //operators

private:
   //attributes
   
   //helper (private) methods

};
//----------------------------------------------------------------------
#endif