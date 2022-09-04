#ifndef FP_SEGMENTATOR
#define FP_SEGMENTATOR

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>
#include <regex>
using namespace std;

//----------------------------------------------------------------------
const int FP_AREA             = 0;
const int NON_FP_AREA         = 255;

const int BLOCK_SIZE_1          = 8;
const int BLOCK_SIZE_2			 = 8;
//----------------------------------------------------------------------
//Fingerprint (FP) Segmentator
//----------------------------------------------------------------------
class FpSegmentator {
public:
   //constructors & destructor
   
   //getters & setters
   
   //key methods
   void segment(const cv::Mat& fpImg, cv::Mat& maskImg, cv::Mat& outImg);
   void segment2(const cv::Mat& fpImg, cv::Mat& maskImg, cv::Mat& outImg);
   //operators

private:
   //attributes
   
   //helper (private) methods
   
};
//----------------------------------------------------------------------
#endif
