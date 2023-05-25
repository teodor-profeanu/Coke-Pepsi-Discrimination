#include "stdafx.h"

#include "common.h"
#include "Descriptors.h"
#include "Classifier.h"
#include<fstream>

void doesThisWork() {
	setDistanceFunc(euclidianDistance);
	setSaturationThreshold(0);
	setBins(1);
	setFunc(hueDescriptor);
	setSampleSize(1);

	train("images/train/cola", TRAINED_FILE, 30, 199, COLA);
	train("images/train/pepsi", TRAINED_FILE, 30, 199, PEPSI, true);

	testBatch(TRAINED_FILE, "images/test/cola", 0, 29, COLA);
	testBatch(TRAINED_FILE, "images/test/pepsi", 0, 29, PEPSI);
}

void plotPoints() {
	setDistanceFunc(euclidianDistance);
	setSaturationThreshold(170);
	setBins(60);
	setFunc(hueDescriptor);
	setSampleSize(3);

	//train("images/train/cola", "plot_points.csv", 30, 199, COLA, false, ',');
	train("images/train/pepsi", "plot_points.csv", 30, 199, PEPSI, false, ',');
}

void changeSampleSize() {
	setDistanceFunc(euclidianDistance);
	setSaturationThreshold(0);
	setBins(1);
	setFunc(hueDescriptor);

	train("images/train/cola", TRAINED_FILE, 30, 199, COLA, false);
	train("images/train/pepsi", TRAINED_FILE, 30, 199, PEPSI, true);

	std::ofstream g("sampleSize.csv");

	for (int i = 1; i < 29; i+=2) {
		setSampleSize(i);
		float successCola = testBatch(TRAINED_FILE, "images/test/cola", 0, 29, COLA);
		float successPepsi = testBatch(TRAINED_FILE, "images/test/pepsi", 0, 29, PEPSI);

		g << i << "," << successCola << "," << successPepsi << "\n";
	}

	g.close();
}

void changeSaturation() {
	setDistanceFunc(euclidianDistance);
	setBins(1);
	setFunc(hueDescriptor);
	setSampleSize(13);

	std::ofstream g("threshold.csv");

	for (int i = 0; i < 180; i += 10) {
		setSaturationThreshold(i);
		train("images/train/cola", TRAINED_FILE, 30, 199, COLA, false);
		train("images/train/pepsi", TRAINED_FILE, 30, 199, PEPSI, true);

		float successCola = testBatch(TRAINED_FILE, "images/test/cola", 0, 29, COLA);
		float successPepsi = testBatch(TRAINED_FILE, "images/test/pepsi", 0, 29, PEPSI);

		g << i << "," << successCola << "," << successPepsi << "\n";
	}

	g.close();
}

void changeBins() {
	setDistanceFunc(euclidianDistance);
	setBins(1);
	setFunc(hueDescriptor);
	setSampleSize(13);
	setSaturationThreshold(150);

	std::ofstream g("bins.csv");

	for (int i = 0; i <= 90; i += 5) {
		if(i==0)
			setBins(1);
		else
			setBins(i);

		train("images/train/cola", TRAINED_FILE, 30, 199, COLA, false);
		train("images/train/pepsi", TRAINED_FILE, 30, 199, PEPSI, true);

		float successCola = testBatch(TRAINED_FILE, "images/test/cola", 0, 29, COLA);
		float successPepsi = testBatch(TRAINED_FILE, "images/test/pepsi", 0, 29, PEPSI);

		if(i == 0)	
			g << 1 << "," << successCola << "," << successPepsi << "\n";
		else
			g << i << "," << successCola << "," << successPepsi << "\n";
	}

	g.close();
}

void findBest() {
	
	
	//for (int h = 0; h < 2; h++) {
	//	if (h == 0)
	//		setDistanceFunc(euclidianDistance);
	//	else
	//		setDistanceFunc(cosineDistance);
	//	for (int i = 1; i <= 29; i += 2) {
	//		setSampleSize(i);
	//		for (int j = 5; j <= 90; j += 5) {
	//			setBins(j);
	//			for (int k = 125; k <= 175; k += 5) {
	//				


	//				setSaturationThreshold(k);

	//				train("images/train/cola", TRAINED_FILE, 30, 199, COLA, false);
	//				train("images/train/pepsi", TRAINED_FILE, 30, 199, PEPSI, true);

	//				float successCola = testBatch(TRAINED_FILE, "images/test/cola", 0, 29, COLA);
	//				float successPepsi = testBatch(TRAINED_FILE, "images/test/pepsi", 0, 29, PEPSI);

	//				float averageSucc = (successCola + successPepsi) / 2.0;
	//				if (averageSucc > maxSucc) {
	//					maxSucc = averageSucc;
	//					bestSample = i;
	//					bestBin = j;
	//					bestThresh = k;
	//					bestFunc = h;
	//				}

	//				std::cout << h << " " << i << " " << j << " " << k << " = " << averageSucc <<"%\n";
	//			}
	//		}
	//	}
	//}

	setFunc(hueDescriptor);
	setDistanceFunc(euclidianDistance);
	setSaturationThreshold(170);

	float maxSucc = 0;
	int bestSample, bestBin, bestThresh, bestFunc;

	for (int i = 5; i <= 90; i += 5) {
		setBins(i);
		train("images/train/cola", TRAINED_FILE, 30, 199, COLA, false);
		train("images/train/pepsi", TRAINED_FILE, 30, 199, PEPSI, true);
		for (int j = 3; j <= 29; j+=2) {
			setSampleSize(j);
			float successCola = testBatch(TRAINED_FILE, "images/test/cola", 0, 29, COLA);
			float successPepsi = testBatch(TRAINED_FILE, "images/test/pepsi", 0, 29, PEPSI);

			float averageSucc = (successCola + successPepsi) / 2.0;
			if (averageSucc >= maxSucc) {
				std::cout << i << " " << j << " = " << averageSucc << "%\n";
				maxSucc = averageSucc;
				bestSample = j;
				bestBin = i;
				bestThresh = 170;
				bestFunc = 0;
			}
		}
	}

	std::cout << maxSucc << "%, samples: " << bestSample << ", bins: " << bestBin << ", threshold: " << bestThresh << ", function: "<<bestFunc<<"\n";
}