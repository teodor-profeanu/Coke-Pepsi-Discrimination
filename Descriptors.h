#ifndef Descriptors_h
#define Descriptors_h

#include "common.h"

void showHistogram(const std::string& name, int* hist, const int  hist_cols, const int hist_height);
Mat_<Vec3b> convertBGR2HSV(Mat src);
std::vector<int> hirtogramFromHSV(Mat src);
Vec2f hueDescriptor(Mat src);

#endif
