#ifndef Classifier_h
#define Classifier_h

#include "common.h"

#define COLA 'c'
#define PEPSI 'p'
#define TRAINED_FILE "trained_set.txt"

int size(const Mat &matrix);
void train(const char* folderName, const char* dstName, int rangeStart, int rangeEnd, char tag, std::vector<float>(*func)(const Mat&), bool append);

std::vector<ClassifiedPoint> readTaggedSet(const char* fileName);

char knn(std::vector<ClassifiedPoint> pnts, std::vector<float> point, int sampleSize);

void classifyDemo(const char* trainedSet, std::vector<float>(*func)(const Mat&), int sampleSize);

char classify(std::vector<ClassifiedPoint> tags, const Mat& src, std::vector<float>(*func)(const Mat&), int sampleSize);

void testBatch(const char* trainedSet, std::vector<float>(*func)(const Mat&), int sampleSize, const char* testDir, int rangeStart, int rangeEnd, char expected);

#endif