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

	//train("images/train/cola", TRAINED_FILE, 30, 199, COLA, hueDescriptor);
	//train("images/train/pepsi", TRAINED_FILE, 30, 199, PEPSI, hueDescriptor, true);

	classifyDemo("trained_set.txt", hueDescriptor, 5);

	//testBatch(TRAINED_FILE, hueDescriptor, 5, "images/test/cola", 0, 29, COLA);
	//testBatch(TRAINED_FILE, hueDescriptor, 5, "images/test/pepsi", 0, 29, PEPSI);

	//testBatch(TRAINED_FILE, hueDescriptor, 5, "images/train/cola", 30, 199, COLA);
	//testBatch(TRAINED_FILE, hueDescriptor, 5, "images/train/pepsi", 30, 199, PEPSI);

	return 0;
}