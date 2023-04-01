#include "Classifier.h"
#include "stdafx.h"
#include "common.h"
#include <opencv2/core/utils/logger.hpp>
#include <fstream>

#define folderFileJpg(x,y) (std::string(x) + "/" + std::to_string(y) + ".jpg").c_str()

int size(Mat matrix) {
	return matrix.cols * matrix.rows;
}

void train(const char* folderName, const char* dstName, int rangeStart, int rangeEnd, const char* tag, int (*func)(Mat), bool append = false) {
	std::ofstream output;
	if(append)
		output = std::ofstream("trained_set.txt", std::ios_base::app);
	else
		output = std::ofstream("trained_set.txt");

	for (int i = rangeStart; i <= rangeEnd; i++) {
		Mat src = imread(folderFileJpg(folderName, i));
		int value = func(src);
		output << tag << " " << value << "\n";
	}
	output.close();
}