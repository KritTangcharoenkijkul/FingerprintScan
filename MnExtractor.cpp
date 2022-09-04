#include "MnExtractor.h"
#include "MnSet.h"
#include <iostream>
#include <stdio.h>

//----------------------------------------------------------------------


using namespace std;
using namespace cv;



  void MnExtractor::extract(const cv::Mat& enhancedImg, MnSet& mnSet) {
	int border = 30;
	cv::Mat bif;
	cvtColor(enhancedImg, bif, cv::COLOR_GRAY2RGB);
	int ridgeEndingCount = 0;
	int bifurcationCount = 0;
      
	for (int i = border; i <= (enhancedImg.cols - border); i++) {
        
		for (int j = border; j <= (enhancedImg.rows - border); j++) {
			int cn = 0;
            
			if (enhancedImg.at<uchar>(cv::Point(i, j)) == 0) {
				//iterate through 8-Neighborhood and count all transitions from black to white and reverse
				cn = cn + abs(enhancedImg.at<uchar>(cv::Point(i - 1, j - 1)) - enhancedImg.at<uchar>(cv::Point(i, j - 1)));
				cn = cn + abs(enhancedImg.at<uchar>(cv::Point(i, j - 1)) - enhancedImg.at<uchar>(cv::Point(i + 1, j - 1)));
				cn = cn + abs(enhancedImg.at<uchar>(cv::Point(i + 1, j - 1)) - enhancedImg.at<uchar>(cv::Point(i + 1, j)));
				cn = cn + abs(enhancedImg.at<uchar>(cv::Point(i + 1, j)) - enhancedImg.at<uchar>(cv::Point(i + 1, j + 1)));
				cn = cn + abs(enhancedImg.at<uchar>(cv::Point(i + 1, j + 1)) - enhancedImg.at<uchar>(cv::Point(i, j + 1)));
				cn = cn + abs(enhancedImg.at<uchar>(cv::Point(i, j + 1)) - enhancedImg.at<uchar>(cv::Point(i - 1, j + 1)));
				cn = cn + abs(enhancedImg.at<uchar>(cv::Point(i - 1, j + 1)) - enhancedImg.at<uchar>(cv::Point(i - 1, j)));
				cn = cn + abs(enhancedImg.at<uchar>(cv::Point(i - 1, j)) - enhancedImg.at<uchar>(cv::Point(i - 1, j - 1)));
				cn = (cn/255)/2;

				if (cn == 1) {
					//  Ridge end
					cv::Point2f posval(i, j);
					Minutiae minut(posval,1);
					mnSet.push_back(minut);

					ridgeEndingCount++;

					circle(bif, cv::Point(i, j), 5, Scalar(255, 0, 255), 0, 8, 0);
				}
				else if (cn == 3) {
					//  bifurcation
					cv::Point2d posval(i, j);
					Minutiae minut(posval, 2);
					mnSet.push_back(minut);
					bifurcationCount++;
					circle(bif, cv::Point(i, j), 5, Scalar(0, 255, 0), 0, 8, 0);

				}

			}
		}

	}


	std::cout << "Number of Ridge-Endings: " << ridgeEndingCount << std::endl;
	std::cout << "Number of Bifurcations: " << bifurcationCount << std::endl;
      stringstream ss;
      string s;
      char c = 'a'+rand()%26;
      ss << c;
      ss >> s;
	cv::imshow(s, bif);
	//cv::imwrite("Minutiae.bmp", bif);



}

















//----------------------------------------------------------------------
