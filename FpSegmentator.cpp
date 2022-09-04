#include "FpSegmentator.hpp"

//----------------------------------------------------------------------
void FpSegmentator::segment(const cv::Mat& fpImg, cv::Mat& maskImg, cv::Mat& outImg) { 
   
   //cout << "Stub: fingerprint segmentation" << endl; 

   cv::Mat nImg;
   cv::normalize(fpImg, nImg, 0, 255, cv::NORM_MINMAX, CV_8UC1);

   cv::Mat Highpass(3, 3, CV_16S, -1);
   Highpass.at<short>(1, 1) = 8;

   cv::Mat filteroutput;

   cv::filter2D(nImg, filteroutput, CV_8U, Highpass);

   cv::addWeighted(nImg, 0.4, filteroutput, 0.6, 0, maskImg);
   cv::Mat filterimg = maskImg.clone();

   for (int i = 0; i < maskImg.cols; i += BLOCK_SIZE_1) {
		for (int j = 0; j < maskImg.rows; j += BLOCK_SIZE_1) {
			cv::Rect rectangle(i, j, BLOCK_SIZE_1, BLOCK_SIZE_1);
			cv::Mat imgBlock = maskImg(rectangle);
			cv::Mat m(1, 4, CV_64F), stdv(1, 4, CV_64F);
			cv::meanStdDev(imgBlock, m, stdv);
			if (stdv.at<double>(0) <= 32) {
				maskImg(rectangle) = NON_FP_AREA;

			}
			else {
				maskImg(rectangle) = FP_AREA;
			}
		}
	}

   int noise_re_size = 9;
   cv::Mat noise_reduce = cv::getStructuringElement(cv::MORPH_RECT,
	   cv::Size(2 * noise_re_size + 1, 2 * noise_re_size + 1),
	   cv::Point(noise_re_size, noise_re_size));
   cv::dilate(maskImg, maskImg, noise_reduce);

   int hole_re_size = 15;
   cv::Mat hole_remove = cv::getStructuringElement(cv::MORPH_RECT,
	   cv::Size(2 * hole_re_size + 1, 2 * hole_re_size + 1),
	   cv::Point(hole_re_size, hole_re_size));
   cv::erode(maskImg, maskImg, hole_remove);

   int en_roi_size = 1;
   cv::Mat en_roi = cv::getStructuringElement(cv::MORPH_RECT,
	   cv::Size(2 * en_roi_size + 1, 2 * en_roi_size + 1),
	   cv::Point(en_roi_size, en_roi_size));
   dilate(maskImg, maskImg, en_roi);
/**/
   outImg = filterimg.clone();
    
    std::regex pattern { "^[a-zA-Z]+$" }; // we search this motif
    std::string target;
    
    for (int i = 0; i < maskImg.cols; i++) {
        for (int j = 0; j < maskImg.rows; j++) {
            if (maskImg.at<char>(i, j) == '\377') {
                outImg.at<char>(i, j) = 255;
            }
        }
    }
   int dilation_size = 23;
   cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,
	   cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
	   cv::Point(dilation_size, dilation_size));
   dilate(maskImg, maskImg, element);

	cv::threshold(outImg, outImg, 50 ,255, cv::THRESH_BINARY); 

}

void FpSegmentator::segment2(const cv::Mat& fpImg, cv::Mat& maskImg, cv::Mat& outImg) {

	//cout << "Stub: fingerprint segmentation" << endl;

	cv::Mat nImg;
	cv::normalize(fpImg, nImg, 0, 255, cv::NORM_MINMAX, CV_8UC1);
	cv::equalizeHist(nImg, fpImg);

	cv::Mat Highpass(3, 3, CV_16S, -1);
	Highpass.at<short>(1, 1) = 8;

	cv::Mat filteroutput;

	cv::filter2D(nImg, filteroutput, CV_8U, Highpass);

	cv::addWeighted(nImg, 0.4, filteroutput, 0.6, 0, maskImg);
	cv::Mat filterimg = maskImg.clone();

	for (int i = 0; i < maskImg.cols; i += BLOCK_SIZE_2) {
		for (int j = 0; j < maskImg.rows; j += BLOCK_SIZE_2) {
			cv::Rect rectangle(i, j, BLOCK_SIZE_2, BLOCK_SIZE_2);
			cv::Mat imgBlock = maskImg(rectangle);
			cv::Mat m(1, 4, CV_64F), stdv(1, 4, CV_64F);
			cv::meanStdDev(imgBlock, m, stdv);
			if (stdv.at<double>(0) <= 30) {
				maskImg(rectangle) = NON_FP_AREA;

			}
			else {
				maskImg(rectangle) = FP_AREA;
			}
		}
	}

	int noise_re_size = 7;
	cv::Mat noise_reduce = cv::getStructuringElement(cv::MORPH_RECT,
		cv::Size(2 * noise_re_size + 1, 2 * noise_re_size + 1),
		cv::Point(noise_re_size, noise_re_size));
	cv::dilate(maskImg, maskImg, noise_reduce);

	int hole_re_size = 29;
	cv::Mat hole_remove = cv::getStructuringElement(cv::MORPH_RECT,
		cv::Size(2 * hole_re_size + 1, 2 * hole_re_size + 1),
		cv::Point(hole_re_size, hole_re_size));
	cv::erode(maskImg, maskImg, hole_remove);

	int en_roi_size = 21;
	cv::Mat en_roi = cv::getStructuringElement(cv::MORPH_RECT,
		cv::Size(2 * en_roi_size + 1, 2 * en_roi_size + 1),
		cv::Point(en_roi_size, en_roi_size));
	dilate(maskImg, maskImg, en_roi);

	outImg = filterimg.clone();
    std::regex pattern { "a-zA-Z]+$" }; // we search this motif
    std::string target;
    for (int i = 0; i < maskImg.cols; i++) {
        for (int j = 0; j < maskImg.rows; j++) {
            if (maskImg.at<char>(i, j) == '\377') {
                outImg.at<char>(i, j) = 255;
            }
        }
    }
	int dilation_size = 23;
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,
		cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		cv::Point(dilation_size, dilation_size));
	dilate(maskImg, maskImg, element);

	cv::threshold(outImg, outImg, 40, 255, cv::THRESH_BINARY);

}

/*  cv::erode(maskImg, maskImg, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
   cv::erode(maskImg, maskImg, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
   cv::erode(maskImg, maskImg, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
   cv::erode(maskImg, maskImg, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
   cv::erode(maskImg, maskImg, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
   cv::erode(maskImg, maskImg, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
   cv::erode(maskImg, maskImg, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
   cv::erode(maskImg, maskImg, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);

   cv::dilate(maskImg, maskImg, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
   cv::dilate(maskImg, maskImg, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
   cv::dilate(maskImg, maskImg, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
*/

//----------------------------------------------------------------------
