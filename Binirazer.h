#ifndef BINARIZER
#define BINARIZER

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;

//----------------------------------------------------------------------
//Binarizer
//----------------------------------------------------------------------
class Binarizer {
public:
	//constructors & destructor

	//getters & setters

	//key methods
	static void binarize(const cv::Mat& fpImg, cv::Mat& binaryImg);


	//operators

private:
	//attributes

	//helper (private) methods

};
//----------------------------------------------------------------------
#endif