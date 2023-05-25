#ifndef Classifier_h
#define Classifier_h

#include "common.h"

#define COLA 'c'
#define PEPSI 'p'
#define TRAINED_FILE "trained_set.txt"

void setDistanceFunc(float (*dist)(std::vector<float>, std::vector<float>));
void setSampleSize(int ssize);
void setFunc(std::vector<float>(*f)(const Mat&));

int size(const Mat &matrix);

void train(const char* folderName, const char* dstName, int rangeStart, int rangeEnd, char tag, bool append = false);

std::vector<ClassifiedPoint> readTaggedSet(const char* fileName);

char knn(std::vector<ClassifiedPoint> pnts, std::vector<float> point);

void classifyDemo(const char* trainedSet);

char classify(std::vector<ClassifiedPoint> tags, const Mat& src);

void testBatch(const char* trainedSet, const char* testDir, int rangeStart, int rangeEnd, char expected);

#endif