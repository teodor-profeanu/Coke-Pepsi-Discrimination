#include "stdafx.h"

#include "Classifier.h"

#define folderFileJpg(x,y) (std::string(x) + "/" + std::to_string(y) + ".jpg").c_str()

int size(const Mat &matrix) {
	return matrix.cols * matrix.rows;
}

void train(const char* folderName, const char* dstName, int rangeStart, int rangeEnd, char tag, std::vector<float> (*func)(const Mat&), bool append) {
	std::ofstream output;
	if(append)
		output = std::ofstream(dstName, std::ios_base::app);
	else 
		output = std::ofstream(dstName);
		

	for (int i = rangeStart; i <= rangeEnd; i++) {
		Mat src = imread(folderFileJpg(folderName, i));
		std::vector<float> point = func(src);
		if (!append && i == rangeStart)
			output << point.size()<<"\n";
		output << tag << " " << point[0] << " " << point[1] << "\n";
	}
	output.close();
}

std::vector<ClassifiedPoint> readTaggedSet(const char* fileName) {
	std::ifstream input(fileName);
	std::vector<ClassifiedPoint> points;

	int dimension;
	input >> dimension;
	char tag;
	while (input >> tag) {
		std::vector<float> point;
		for (int i = 0; i < dimension; i++) {
			float coord;
			input >> coord;
			point.push_back(coord);
		}
		points.push_back(ClassifiedPoint(tag, point));
	}

	input.close();

	return points;
}

char knn(std::vector<ClassifiedPoint> pnts, std::vector<float> point, int sampleSize) {
	char freq[27] = {'\0'};
	std::vector<ClassifiedPoint> points(pnts);
	for (int i = 0; i < sampleSize; i++) {
		float minDst = 1e20;
		int foundIndex = 0;
		for (int j = 0; j < points.size(); j++) {
			float dst = distance(points.at(j).point, point);
			if (dst < minDst) {
				minDst = dst;
				foundIndex = j;
			}
		}
		
		freq[points.at(foundIndex).tag - 'a']++;
		points.erase(points.begin() + foundIndex);
	}

	int maxFreq = 0;
	char finalTag;
	for (int i = 0; i < 27; i++) {
		if (freq[i] > maxFreq) {
			maxFreq = freq[i];
			finalTag = i + 'a';
		}
	}

	return finalTag;
}

char classify(std::vector<ClassifiedPoint> tags, const Mat& src, std::vector<float> (*func)(const Mat&), int sampleSize) {
	return knn(tags, func(src), sampleSize);
}

void classifyDemo(const char* trainedSet, std::vector<float> (*func)(const Mat&), int sampleSize) {
	char fname[MAX_PATH];
	std::vector<ClassifiedPoint> points = readTaggedSet(trainedSet);
	while (openFileDlg(fname)){
		Mat src = imread(fname);

		char result = classify(points, src, func, sampleSize);
		if (result == COLA)
			std::cout << "Coca Cola";
		else if(result == PEPSI)
			std::cout << "Pepsi";
		else
			std::cout << "Other";
		std::cout << "\n";

		imshow("image", src);
		waitKey();
	}
}

void testBatch(const char* trainedSet, std::vector<float> (*func)(const Mat&), int sampleSize, const char* testDir, int rangeStart, int rangeEnd, char expected) {
	std::cout << "\n------------------------\n";
	if (expected == PEPSI)
		std::cout << "Testing for PEPSI";
	if (expected == COLA)
		std::cout << "Testing for COLA";
	std::cout << "\n------------------------\n";

	std::vector<ClassifiedPoint> points = readTaggedSet(trainedSet);
	int positive = 0, negative = 0;

	for (int i = rangeStart; i <= rangeEnd; i++) {
		Mat src = imread(folderFileJpg(testDir, i));
		char result = classify(points, src, func, sampleSize);
		if (result == expected)
			positive++;
		else
			negative++;
	}

	std::cout << "Positive results: " << positive << "\n";
	std::cout << "Negative results: " << negative << "\n";
	std::cout << "Success rate: " << ((float)positive / (positive + negative))*100 << "%\n\n";
}