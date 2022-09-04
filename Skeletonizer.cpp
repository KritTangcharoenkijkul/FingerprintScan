#include "Skeletonizer.h"

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;


////////////////// num_one_pixel_neighbours//////////////////////////
int num_one_pixel_neighbours(const cv::Mat& image, const Point& point)
{
	int ret = 0, r = point.first, c = point.second;
	for (int i = r - 1; i <= r + 1; i++)
		for (int j = c - 1; j <= c + 1; j++)
			if (i != r || j != c)
				if (image.at<uchar_t>(i, j) >= 1) ret++;
	return ret;
}
//-------------------------------------------------------------------------
////////////////// connectivity //////////////////////////

int connectivity(const cv::Mat& image, const Point& point)
{
	int r = point.first, c = point.second, ret = 0;
	if (image.at<uchar_t>(r, c + 1) >= 1 && image.at<uchar_t>(r - 1, c + 1) == 0)
		ret++;
	if (image.at<uchar_t>(r - 1, c + 1) >= 1 && image.at<uchar_t>(r - 1, c) == 0)
		ret++;
	if (image.at<uchar_t>(r - 1, c) >= 1 && image.at<uchar_t>(r - 1, c - 1) == 0)
		ret++;
	if (image.at<uchar_t>(r - 1, c - 1) >= 1 && image.at<uchar_t>(r, c - 1) == 0)
		ret++;
	if (image.at<uchar_t>(r, c - 1) >= 1 && image.at<uchar_t>(r + 1, c - 1) == 0)
		ret++;
	if (image.at<uchar_t>(r + 1, c - 1) >= 1 && image.at<uchar_t>(r + 1, c) == 0)
		ret++;
	if (image.at<uchar_t>(r + 1, c) >= 1 && image.at<uchar_t>(r + 1, c + 1) == 0)
		ret++;
	if (image.at<uchar_t>(r + 1, c + 1) >= 1 && image.at<uchar_t>(r, c + 1) == 0)
		ret++;
	return ret;
}
//-------------------------------------------------------------------------

////////////////// delete pixels//////////////////////////

void delete_pixels(cv::Mat& image, std::set<Point>& points)
{
	for (auto& point : points)
	{
		image.at<uchar_t>(point.first, point.second) = 0;
	}
	points.clear();
}
//-------------------------------------------------------------------------
////////////////// Remove staircases //////////////////////////

void remove_staircases(cv::Mat& image)
{
	std::set<Point> points;
	for (int i = 0; i < 2; i++)
	{
		for (int i = 1; i < image.rows - 1; i++)
		{
			for (int j = 1; j < image.cols - 1; j++)
			{
				int c = image.at<uchar_t>(i, j);
				if (!c) continue;
				int e = image.at<uchar_t>(i, j + 1),
					ne = image.at<uchar_t>(i - 1, j + 1),
					n = image.at<uchar_t>(i - 1, j),
					nw = image.at<uchar_t>(i - 1, j - 1),
					w = image.at<uchar_t>(i, j - 1),
					sw = image.at<uchar_t>(i + 1, j - 1),
					s = image.at<uchar_t>(i + 1, j),
					se = image.at<uchar_t>(i + 1, j + 1);

				if (i == 0)
				{
					// North biased staircase removal
					if (!(c && !(n &&
						((e && !ne && !sw && (!w || !s)) ||
						(w && !nw && !se && (!e || !s))))))
					{
						points.insert({ i, j });
					}
				}
				else
				{
					// South bias staircase removal
					if (!(c && !(s &&
						((e && !se && !nw && (!w || !n)) ||
						(w && !sw && !ne && (!e || !n))))))
					{
						points.insert({ i, j });
					}

				}
			}
		}
		delete_pixels(image, points);
	}
}
//-------------------------------------------------------------------------

////////////////// thinning Iteration//////////////////////////

void thinIter(cv::Mat& image)
{
	while (true)
	{
		std::set<Point> points;
		for (int i = 1; i < image.rows - 1; i++)
		{
			for (int j = 1; j < image.cols - 1; j++)
			{
				if (image.at<uchar_t>(i, j) != 1) continue;
				Point p(i, j);
				int k = num_one_pixel_neighbours(image, p);
				if ((k >= 2 && k <= 6) && connectivity(image, p) == 1)
				{
					int p1 = image.at<uchar_t>(i, j + 1) *
						image.at<uchar_t>(i - 1, j) *
						image.at<uchar_t>(i, j - 1),

						p2 = image.at<uchar_t>(i - 1, j) *
						image.at<uchar_t>(i + 1, j) *
						image.at<uchar_t>(i, j - 1);

					if (p1 == 0 && p2 == 0)
					{
						points.insert(p);
					}
				}
			}
		}
		if (points.size() == 0)
			break;
		delete_pixels(image, points);
		for (int i = 1; i < image.rows; i++)
		{
			for (int j = 1; j < image.cols; j++)
			{
				if (image.at<uchar_t>(i, j) != 1) continue;
				Point p(i, j);
				int k = num_one_pixel_neighbours(image, p);
				if ((k >= 2 && k <= 6) && connectivity(image, p) == 1)
				{
					int p1 = image.at<uchar_t>(i - 1, j) *
						image.at<uchar_t>(i, j + 1) *
						image.at<uchar_t>(i + 1, j),

						p2 = image.at<uchar_t>(i, j + 1) *
						image.at<uchar_t>(i + 1, j) *
						image.at<uchar_t>(i, j - 1);
					if (p1 == 0 && p2 == 0)
					{
						points.insert(p);
					}
				}
			}
		}
		if (points.size() == 0)
			break;
		delete_pixels(image, points);
	}
}

//-------------------------------------------------------------------------




////////////////// Thinning //////////////////////////



//-------------------------------------------------------------------------


//----------------------------------------------------------------------
void Skeletonizer::skeletonize(cv::Mat& img) {
    
   

		bool destair = false;
		
		// Making everything either 0 or 1
		for (int i = 0; i < img.rows; i++)
		{
			uchar_t *iter = img.ptr<uchar_t>(i);
			for (int j = 0; j < img.cols; j++, iter++)
				*iter = (uchar_t)(*iter != 0);
		}
		//  create a M + 2 x N + 2 image that is
		// essentially the same image, bordered by 1 white pixels.
		cv::Mat image = cv::Mat::ones(img.rows + 2, img.cols + 2, CV_8U);
		for (int i = 0; i < img.rows; i++)
		{
			uchar_t *src_iter = img.ptr<uchar_t>(i),
				*dst_iter = image.ptr<uchar_t>(i + 1);


			// Advance from the 0th to the 1st column.
			++dst_iter;
			for (int j = 0; j < img.cols; j++)
			{
				*dst_iter++ = *src_iter++;
			}
		}

		for (int i = 0; i < image.rows; i++)
		{
			uchar_t *iter = image.ptr<uchar_t>(i);
			for (int j = 0; j < image.cols; j++, iter++)
			{
				if (*iter > 0)
					*iter = 0;
				else
					*iter = 1;
			}
		}
		// we call the thinning iteration method 
		thinIter(image);
		//  staircase removal
		if (destair)
			remove_staircases(image);
		// 1 means black and 0 means white
		//change to 255 for white and 0 for black
		
		for (int i = 0; i < img.rows; i++)
		{
			uchar_t *dst_iter = img.ptr<uchar_t>(i),
				*src_iter = image.ptr<uchar_t>(i + 1);
			++src_iter;
			for (int j = 0; j < img.cols; j++)
			{
				*dst_iter++ = (*src_iter++ > 0) ? 0 : 255;
			}
		}
	

	







}
//----------------------------------------------------------------------
