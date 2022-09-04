#include "FpEnhancer.hpp"

FpEnhancer::FpEnhancer(double lam,int size,double sigma) :filterbank(GaborFilterbank(lam, size, sigma)){

	blockSize = size;
	l = lam;
	s = sigma;
	orientationFieldDetecter.setBlockSize(11);
}
FpEnhancer::FpEnhancer() :filterbank(GaborFilterbank(1.0/6, 17, 3.5)){

	blockSize = 13;
	l = 1.0/6;
	s = 3.5;
	orientationFieldDetecter.setBlockSize(11);
}

//---------------------------------------------------------------------------------------

void FpEnhancer::enhance(const cv::Mat& fpImg, cv::Mat& enhancedImg)  {

	cv::Mat ofImg;
	enhancedImg = cv::Mat::zeros(fpImg.rows, fpImg.cols, CV_32FC1);
	orientationFieldDetecter.detect(fpImg, ofImg);



	for (int i = 0; i < fpImg.rows - blockSize; i += blockSize){
		for (int j = 0; j < fpImg.cols - blockSize; j += blockSize){

			cv::Mat temp = fpImg.clone();
			cv::Mat kernel = filterbank.getFilter(ofImg.at<float>(i, j));
			filter2D(temp, temp, CV_32FC1, kernel);

			for (int x = 0; x < blockSize; x++){
				for (int y = 0; y < blockSize; y++){
					enhancedImg.at<float>(i + x, j + y) = temp.at<float>(i + x, j + y);
				}
			}
		}
	}

	double minVal, maxVal;
	minMaxLoc(enhancedImg, &minVal, &maxVal); //find minimum and maximum intensities
	enhancedImg.convertTo(enhancedImg, CV_8U);
}
//-----------------------------------------------------------------------------------------
