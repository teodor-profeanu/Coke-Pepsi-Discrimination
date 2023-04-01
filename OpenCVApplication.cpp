// OpenCVApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "common.h"
#include "Descriptors.h"
#include <opencv2/core/utils/logger.hpp>
#include "Classifier.h"

//wchar_t* projectPath;

int main() 
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_FATAL);

	//train("images/train/cola", "trained_set.txt", 30, 199, COLA, size);
	//train("images/train/pepsi", "trained_set.txt", 30, 199, PEPSI, size, true);
	//std::vector<Tagged> tags = readTaggedSet("trained_set.txt");
	//for (int i = 0; i < tags.size(); i++) {
	//	std::cout << tags.at(i).tag << " " << tags.at(i).value << "\n";
	//}

	classify("trained_set.txt", size, 5);

	return 0;
}