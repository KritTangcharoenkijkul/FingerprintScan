#include "GaborFilterbank.hpp"

GaborFilterbank::GaborFilterbank(double fv, int ks, double sg){

	sigma = sg;
	kernelSize = ks;
	freq = fv;

	generateFilter();
}

cv::Mat GaborFilterbank::getFilter(float theta){

	return gbs.at(theta / 22.5).getKernel();

}

void GaborFilterbank::generateFilter(){

	gbs.clear();

	// kernel size 17, freq 1/6, sigma 3.5
	// convert to degree

	for (int i = 0; i < 8; i++){

		double theta = (22.5*i);
		gbs.push_back(GaborFilter(cv::Size(kernelSize, kernelSize), sigma, theta, freq));
	}
}
