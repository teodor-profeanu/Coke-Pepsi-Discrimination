#ifndef Classifier_h
#define Classifier_h

#include <string>

#define COLA "c"
#define PEPSI "p"

int size(Mat matrix);
void train(const char* folderName, const char* dstName, int rangeStart, int rangeEnd, const char* tag, int (*func)(Mat), bool append = false);

#endif