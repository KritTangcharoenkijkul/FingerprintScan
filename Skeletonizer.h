
#ifndef SKELETONIZER
#define SKELETONIZER
#include <set>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;



typedef std::pair<int, int> Point;
typedef unsigned char uchar_t;

int num_one_pixel_neighbours(const cv::Mat& image, const Point& point);



int connectivity(const cv::Mat& image, const Point& point);



void delete_pixels(const cv::Mat& image, const std::set<Point>& points);

void remove_staircases(cv::Mat& image);

void thinIter(cv::Mat& img);

void thin(cv::Mat& img, bool destair);



//----------------------------------------------------------------------
//Skeletonizer
//----------------------------------------------------------------------
class Skeletonizer {
public:
	//constructors & destructor

	//getters & setters

	//key methods
	static void skeletonize(cv::Mat& img);

	//operators

private:
	//attributes

	//helper (private) methods

};
//----------------------------------------------------------------------
#endif





