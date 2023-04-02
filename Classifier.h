#ifndef Classifier_h
#define Classifier_h

#include "common.h"

#define COLA 'c'
#define PEPSI 'p'

int size(Mat matrix);
void train(const char* folderName, const char* dstName, int rangeStart, int rangeEnd, char tag, Vec2f (*func)(Mat), bool append = false);

std::vector<Tagged> readTaggedSet(const char* fileName);

char knn(std::vector<Tagged> tags, Vec2f point, int sampleSize);

void classifyDemo(const char* trainedSet, Vec2f (*func)(Mat), int sampleSize);

char classify(std::vector<Tagged> tags, Mat src, Vec2f(*func)(Mat), int sampleSize);

void testBatch(const char* trainedSet, Vec2f(*func)(Mat), int sampleSize, const char* testDir, int rangeStart, int rangeEnd, char expected);

#endif