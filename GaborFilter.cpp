#include "GaborFilter.hpp"

//-------------------------------------------------------------------------------------------------------------------------------------------------------
GaborFilter::GaborFilter(cv::Size size,double sigma, double orientVal, double freqVal)
   : kernel(cv::Mat::zeros(size, CV_32FC1)) {
	theta = orientVal;
	orientVal = orientVal*CV_PI / 180;

	for (int i = -kernel.rows / 2; i < kernel.rows / 2; i++){
		for (int j = -kernel.cols / 2; j < kernel.cols / 2; j++){


			double y = (cos(orientVal)*i - sin(orientVal)*j);
			double x = (sin(orientVal)*i + cos(orientVal)*j);
			kernel.at<float>(i + kernel.rows / 2, j + kernel.cols / 2) = exp(-(x*x / (sigma*sigma) + y*y / (sigma*sigma)) / 2)*cos(2 * CV_PI*freqVal*y);

		}
	}




}
//------------------------------------------------------------------------------------------------------------------------------------------------------
