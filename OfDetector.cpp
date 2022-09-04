#include "OfDetector.hpp"

void OfDetector::adjustGxGy(cv::Mat& gx,cv::Mat& gy){
	for (int i = 0; i < gx.rows; i++){
		for (int j = 0; j < gx.cols; j++){
			if (gx.at<float>(i, j) == gy.at<float>(i, j)){
				int r = rand() % 2;
				if (r == 0){
					r = -1;
				}
				gx.at<float>(i, j) += r;
			}
			else if (gx.at<float>(i, j) == 0){
				int r = rand() % 2;
				if (r == 0){
					r = -1;
				}
				gx.at<float>(i, j) += r;
			}
			else if (gy.at<float>(i, j) == 0){
				int r = rand() % 2;
				if (r == 0){
					r = -1;
				}
				gy.at<float>(i, j) += r;
			}
		}
	}
}

float OfDetector::calculateBlockAngle(cv::Mat& gx,cv::Mat& gy){
	float res = 0;
	float n = 0;
	for (int i = 0; i< gx.rows; ++i)
	{
		for (int j = 0; j< gx.cols; ++j)
		{
			res += 2 * gx.at<float>(i, j)*gy.at<float>(i, j);
			n += gx.at<float>(i, j)*gx.at<float>(i, j) - gy.at<float>(i, j)*gy.at<float>(i, j);
		}
	}
	res /= gx.rows*gx.rows;
	n /= gx.rows*gx.rows;
	float orr = atan2(res, n) / 2;
	if ((orr < 0)  && (res < 0 )|| (orr > 0) && (res>0)){
		orr -= CV_PI / 2;
	}
	else{
		orr += CV_PI / 2;
	}

	return orr;

}

void OfDetector::plotOfGraph(const cv::Mat& fpImg, cv::Mat& OfGraph){
	OfGraph = cv::Mat::zeros(fpImg.rows, fpImg.cols, CV_8UC1);
	for (int i = 0; i < fpImg.rows - blockSize; i += blockSize){
		for (int j = 0; j < fpImg.cols - blockSize; j += blockSize){
			float a = calculateBlockAngle(gx,gy);
			cout << a << " ";
			float dx = blockSize*cos(a);
			float dy = blockSize*sin(a);
			int x = j;
			int y = i;
			cv::line(OfGraph, cv::Point(x, y), cv::Point(x + dx, y + dy), cv::Scalar::all(255), 1, CV_AA);
		}
	}
}
//----------------------------------------------------------------------
void OfDetector::detect(const cv::Mat& fpImg, cv::Mat& ofImg) {
	getGx(fpImg, gx);
	getGy(fpImg, gy);
	adjustGxGy(gx, gy);
	ofImg = cv::Mat::zeros(fpImg.rows, fpImg.cols, CV_32FC1);
	for (int i = 0; i < fpImg.rows - blockSize; i += blockSize){
		for (int j = 0; j < fpImg.cols - blockSize; j += blockSize){
			float a = calculateBlockAngle(gx, gy);
			float angle = a * 180 / CV_PI;
			while (angle < 0) angle += 360;
			while (angle > 180) angle -= 180;
			double quantize = 8;
			double quanval = 180.0 / quantize;
			for (int q = 1; q < quantize; q++){
				if (angle < (quanval * q) && (angle - quanval*(q - 1)) < (quanval / 2)){
					angle = quanval*(q - 1);
					break;
				}
				else if (q == quantize - 1)
					angle = quanval * (quantize - 1);}
			for (int x = 0; x < blockSize; x++){
				for (int y = 0; y < blockSize; y++){
					ofImg.at<float>(x + i, y + j) = angle;

				}
			}

		}
	}





}
//----------------------------------------------------------------------
