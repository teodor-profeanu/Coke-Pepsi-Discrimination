#include "stdafx.h"
#include "common.h"
#include "Descriptors.h"
#include <opencv2/core/utils/logger.hpp>
#include "Classifier.h"
#include "Descriptors.h"
#include <filesystem>
#include "test.h"


int main() 
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_FATAL);

	doesThisWork();

	//train("images/train/cola", TRAINED_FILE, 30, 199, COLA, hueDescriptor, false);
	//train("images/train/pepsi", TRAINED_FILE, 30, 199, PEPSI, hueDescriptor, true);
	//testBatch(TRAINED_FILE, hueDescriptor, 9, "images/test/cola", 0, 29, COLA);
	//testBatch(TRAINED_FILE, hueDescriptor, 9, "images/test/pepsi", 0, 29, PEPSI);

	//classifyDemo(TRAINED_FILE, hueDescriptor, 5);

	//train("images/test/cola", TRAINED_FILE, 0, 29, COLA, hueDescriptor, false);
	//train("images/test/pepsi", TRAINED_FILE, 0, 29, PEPSI, hueDescriptor, true);
	//testBatch(TRAINED_FILE, hueDescriptor, 5, "images/train/cola", 30, 199, COLA);
	//testBatch(TRAINED_FILE, hueDescriptor, 5, "images/train/pepsi", 30, 199, PEPSI);

	return 0;
}