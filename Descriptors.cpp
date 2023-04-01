#include "Descriptors.h"
#include "stdafx.h"
#include "common.h"

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

Mat_<uchar> convertBGR2HSV(Mat src)
{
	int height = src.rows;
	int width = src.cols;

	// HSV components
	Mat_<uchar> h(height, width);

	Mat_<Vec3b> hsvImg;
	cvtColor(src, hsvImg, COLOR_BGR2HSV);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{

			h(i, j) = hsvImg(i, j)[0];
		}
	}

	return h;
}

std::vector<int> hirtogramFromHSV(Mat src) {
	std::vector<int> histogram(180, 0);
	Mat_<uchar> hImage = convertBGR2HSV(src);
	int rows = hImage.rows;
	int cols = hImage.cols;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			histogram[hImage(i, j)]++;
		}
	}
	
	showHistogram("Histograma", &histogram[0], 180, 180);
	return histogram;
	waitKey(0);
}

int hueDescriptor(Mat src) {
	std::vector<int> histogram(180, 0);
	histogram = hirtogramFromHSV(src);
	int result;
	int sumaProduse = 0, suma = 0;
	for (int i = 0; i < 180; i++) {
		sumaProduse += i * histogram[i];
		suma += histogram[i];
	}
	
	result = sumaProduse / suma;
	return result;
}

