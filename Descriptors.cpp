#include "stdafx.h"

#include "Descriptors.h"

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

	//for (int i = 0; i < height; i++)
	//{
	//	for (int j = 0; j < width; j++)
	//	{

	//		h(i, j) = hsvImg(i, j)[0];
	//	}
	//}

	//imshow("hue", h);
	return hsvImg;
}

std::vector<int> hirtogramFromHSV(const Mat &src) {
	std::vector<int> histogram(180, 0);
	Mat_<Vec3b> hImage = convertBGR2HSV(src);
	int rows = hImage.rows;
	int cols = hImage.cols;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if(hImage(i, j)[1]>100)
				histogram[hImage(i, j)[0]]++;
		}
	}
	
	//showHistogram("Histograma", &histogram[0], 180, 180);
	return histogram;
	waitKey(0);
}

std::vector<float> hueDescriptor(const Mat &src) {
	std::vector<int> histogram(180, 0);
	histogram = hirtogramFromHSV(src);
	int samples = 0;
	std::vector<float> sum(2);
	for (int i = 0; i < 180; i++) {
		//sumaProduse += i * histogram[i];
		std::vector<float>  point = normalizeFromAngle(i * 2);
		sum.at(0) += histogram[i] * point.at(0);
		sum.at(1) += histogram[i] * point.at(1);
		samples += histogram[i];
	}
	sum.at(0) /= samples;
	sum.at(1) /= samples;

	normalize(sum);

	return sum;
}

