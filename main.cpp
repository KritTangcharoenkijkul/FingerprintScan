#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "FpSegmentator.hpp"
#include "FpMatcher.hpp"
#include "FpMatchingEvaluator.hpp"
using namespace std;

//----------------------------------------------------------------------
int main() {
    
    FpMatcher fpMatcher;
    FpMatchingEvaluator evl("matching_result.txt");
    evl.evaluate("/Users/Renaud/Documents/KMITL/Computer_Vision/Source Fingerprint (Stub)/figerPrint/figerPrint/data/DB_Info.txt", fpMatcher);
    
    cv::waitKey();
}
//----------------------------------------------------------------------
