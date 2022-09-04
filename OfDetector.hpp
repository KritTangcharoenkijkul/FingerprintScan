#ifndef OF_DETECTOR
#define OF_DETECTOR

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;

//----------------------------------------------------------------------
//Orientation Field (OF) Detector
//----------------------------------------------------------------------
class OfDetector {
public:
   //constructors & destructor
   
   //getters & setters
	void setBlockSize(int bs){ blockSize = bs; }
	int getBlockSize(){ return blockSize; }
   //key methods
   void detect(const cv::Mat& fpImg, cv::Mat& ofImg);
   
   //operators

private:
   //attributes
	cv::Mat gx;
	cv::Mat gy;
	int blockSize;
   //helper (private) methods
	float calculateBlockAngle(cv::Mat& gx, cv::Mat& gy);
	void getGx(const cv::Mat& inImg, cv::Mat& gx){ cv::Sobel(inImg, gx, CV_32FC1, 1, 0); }
	void getGy(const cv::Mat& inImg, cv::Mat& gy){ cv::Sobel(inImg, gy, CV_32FC1, 0,1); }
	void adjustGxGy(cv::Mat& gx, cv::Mat& gy);
	void plotOfGraph(const cv::Mat& inImg, cv::Mat& OfGraph);
};
//----------------------------------------------------------------------
#endif