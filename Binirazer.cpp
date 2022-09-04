#include "Binirazer.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


//----------------------------------------------------------------------
void Binarizer::binarize(const cv::Mat& fpImg, cv::Mat& binaryImg) {
    cv::Mat imgTst;
	cv::threshold(fpImg, binaryImg, 128, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::Mat M = (cv::Mat_<double>(2,2) << 1, 1,1,1);
    cv::morphologyEx(binaryImg, imgTst,  cv::MORPH_CLOSE,  M);
    cv::dilate(imgTst, binaryImg, M);
    //cv::dilate(imgTst, binaryImg, M);
    
}
//----------------------------------------------------------------------
