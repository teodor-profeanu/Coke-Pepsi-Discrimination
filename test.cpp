#include "stdafx.h"

#include "common.h"
#include "Descriptors.h"
#include "Classifier.h"

void doesThisWork() {
	setDistanceFunc(cosineDistance);
	setSaturationThreshold(100);
	setBins(1);
	setFunc(hueDescriptor);
	setSampleSize(11);

	train("images/train/cola", TRAINED_FILE, 30, 199, COLA);
	train("images/train/pepsi", TRAINED_FILE, 30, 199, PEPSI, true);

	testBatch(TRAINED_FILE, "images/test/cola", 0, 29, COLA);
	testBatch(TRAINED_FILE, "images/test/pepsi", 0, 29, PEPSI);
}