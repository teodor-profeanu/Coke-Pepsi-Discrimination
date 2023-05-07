#ifndef Descriptors_h
#define Descriptors_h

#include "common.h"

void showHistogram(const std::string& name, int* hist, const int  hist_cols, const int hist_height);
Mat_<Vec3b> convertBGR2HSV(const Mat &src);
std::vector<int> hirtogramFromHSV(const Mat &src);
std::vector<float> hueDescriptor(const Mat& src);

#endif
