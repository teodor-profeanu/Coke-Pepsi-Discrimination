#ifndef Classifier_h
#define Classifier_h

#include "common.h"

#define COLA 'c'
#define PEPSI 'p'

struct Tagged {
	Tagged(char tag, int value) {
		this->value = value;
		this->tag = tag;
	}
	int value;
	char tag;
};

int size(Mat matrix);
void train(const char* folderName, const char* dstName, int rangeStart, int rangeEnd, const char* tag, int (*func)(Mat), bool append = false);
std::vector<Tagged> readTaggedSet(const char* fileName);
void classify(const char* trainedSet, int (*func)(Mat), int sampleSize);

#endif