#ifndef MN_MATCHER
#define MN_MATCHER

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/features2d.hpp>
# include "opencv2/core/core.hpp"
# include "opencv2/features2d/features2d.hpp"
# include "opencv2/highgui/highgui.hpp"
#include "features2d.hpp"
#include <stdio.h>     
#include <math.h>
#include "MnSet.hpp"
#include <cmath>
#include <vector>

using namespace std;

//----------------------------------------------------------------------
//Minutiae Matcher
//----------------------------------------------------------------------
class MnMatcher {
public:
   //constructors & destructor
   
   //getters & setters
   
   //key methods
    double match1(const MnSet& mnSet1, const MnSet& mnSet2,const cv::Mat skel1,const cv::Mat skel2  );
    double match(const MnSet& mnSet1, const MnSet& mnSet2);
    float getAngle(cv::Point2f vector1, cv::Point2f vector2);
    vector<cv::KeyPoint> convert(const MnSet& mnSet);


   //operators

private:
   //attributes
   
   //helper (private) methods

};
//----------------------------------------------------------------------
#endif
