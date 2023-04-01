#ifndef Descriptors_h
#define Descriptors_h

#include "common.h"

void showHistogram(const std::string& name, int* hist, const int  hist_cols, const int hist_height);
Mat_<uchar> convertBGR2HSV(Mat src);
std::vector<int> hirtogramFromHSV(Mat src);
int hueDescriptor(Mat src);

#endif
