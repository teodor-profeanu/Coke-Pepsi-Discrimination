#include "stdafx.h"
#include "common.h"
#include "Descriptors.h"
#include <opencv2/core/utils/logger.hpp>
#include "Classifier.h"
#include "Descriptors.h"
#include <filesystem>


int main() 
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_FATAL);

	//train("images/train/cola", "trained_set.txt", 30, 199, COLA, hueDescriptor);
	//train("images/train/pepsi", "trained_set.txt", 30, 199, PEPSI, hueDescriptor, true);

	classifyDemo("trained_set.txt", hueDescriptor, 7);

	//testBatch("trained_set.txt", hueDescriptor, 7, "images/test/cola", 0, 29, COLA);
	//testBatch("trained_set.txt", hueDescriptor, 7, "images/test/pepsi", 0, 29, PEPSI);

	return 0;
}