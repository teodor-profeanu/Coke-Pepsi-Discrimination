#include "stdafx.h"

#include "Descriptors.h"

int _saturationThresh = 100;
int _samplesPerBin = 1;

void setSaturationThreshold(int saturation) {
	_saturationThresh = saturation;
}

void setBins(int bins) {
	_samplesPerBin = bins;
}

void showHistogram(const std::string& name, int* hist, const int  hist_cols, const int hist_height)
{
	Mat imgHist(hist_height, hist_cols, CV_8UC3, CV_RGB(255, 255, 255)); // constructs a white image

	//computes histogram maximum
	int max_hist = 0;
	for (int i = 0; i < hist_cols; i++)
		if (hist[i] > max_hist)
			max_hist = hist[i];
	double scale = 1.0;
	scale = (double)hist_height / max_hist;
	int baseline = hist_height - 1;

	for (int x = 0; x < hist_cols; x++) {
		Point p1 = Point(x, baseline);
		Point p2 = Point(x, baseline - cvRound(hist[x] * scale));
		line(imgHist, p1, p2, CV_RGB(255, 0, 255)); // histogram bins colored in magenta
	}

	imshow(name, imgHist);
}

Mat_<Vec3b> convertBGR2HSV(const Mat &src)
{
	int height = src.rows;
	int width = src.cols;

	// HSV components
	Mat_<uchar> h(height, width);

	Mat_<Vec3b> hsvImg;
	cvtColor(src, hsvImg, COLOR_BGR2HSV);

	return hsvImg;
}

std::vector<int> hirtogramFromHSV(const Mat &src) {
<<<<<<< Updated upstream
	std::vector<int> histogram(180/ _samplesPerBin, 0);
=======
	std::vector<int> histogram(18, 0);
>>>>>>> Stashed changes
	Mat_<Vec3b> hImage = convertBGR2HSV(src);
	int rows = hImage.rows;
	int cols = hImage.cols;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
<<<<<<< Updated upstream
			if(hImage(i, j)[1] > _saturationThresh)
				histogram[hImage(i, j)[0]/ _samplesPerBin]++;
=======
			if(hImage(i, j)[1]>100)
				histogram[hImage(i, j)[0]/10]++;
>>>>>>> Stashed changes
		}
	}
	
	return histogram;
	waitKey(0);
}

std::vector<float> hueDescriptor(const Mat &src) {
<<<<<<< Updated upstream
	std::vector<int> histogram = hirtogramFromHSV(src);
	int samples = 0;
	std::vector<float> sum(2);
	for (int i = 0; i < histogram.size(); i++) {
		std::vector<float>  point = normalizeFromAngle(i * 2 * _samplesPerBin);
		sum[0] += histogram[i] * point.at(0);
		sum[1] += histogram[i] * point.at(1);
=======
	std::vector<int> histogram;
	histogram = hirtogramFromHSV(src);
	int samples = 0;
	std::vector<float> sum(2);
	for (int i = 0; i < histogram.size(); i++) {
		std::vector<float>  point = normalizeFromAngle(i * 2);
		sum.at(0) += histogram[i] * point.at(0);
		sum.at(1) += histogram[i] * point.at(1);
>>>>>>> Stashed changes
		samples += histogram[i];
	}
	sum[0] /= samples;
	sum[1] /= samples;

	normalize(sum);

	return sum;
}

