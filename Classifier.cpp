#include "stdafx.h"

#include "Classifier.h"

#define folderFileJpg(x,y) (std::string(x) + "/" + std::to_string(y) + ".jpg").c_str()

int size(const Mat &matrix) {
	return matrix.cols * matrix.rows;
}

void train(const char* folderName, const char* dstName, int rangeStart, int rangeEnd, char tag, Vec2f (*func)(const Mat&), bool append) {
	std::ofstream output;
	if(append)
		output = std::ofstream("trained_set.txt", std::ios_base::app);
	else
		output = std::ofstream("trained_set.txt");

	for (int i = rangeStart; i <= rangeEnd; i++) {
		Mat src = imread(folderFileJpg(folderName, i));
		Vec2f point = func(src);
		output << tag << " " << point[0] << " " << point[1] << "\n";
	}
	output.close();
}

std::vector<Tagged> readTaggedSet(const char* fileName) {
	std::ifstream input(fileName);
	std::vector<Tagged> tags;

	float pointX, pointY;
	char tag;

	while (input >> tag >> pointX >> pointY) {
		tags.push_back(Tagged(tag, Vec2f(pointX, pointY)));
	}

	input.close();

	return tags;
}

char knn(std::vector<Tagged> tags, Vec2f point, int sampleSize) {
	char freq[27] = {'\0'};
	for (int i = 0; i < sampleSize; i++) {
		float minDst = 1000.0;
		int foundIndex = 0;
		for (int j = 0; j < tags.size(); j++) {
			float dst = distance(tags.at(j).point, point);
			if (dst < minDst) {
				minDst = dst;
				foundIndex = j;
			}
		}
		
		freq[tags.at(foundIndex).tag - 'a']++;
		tags.erase(tags.begin() + foundIndex);
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

char classify(std::vector<Tagged> tags, const Mat& src, Vec2f(*func)(const Mat&), int sampleSize) {
	return knn(tags, func(src), sampleSize);
}

void classifyDemo(const char* trainedSet, Vec2f (*func)(const Mat&), int sampleSize) {
	char fname[MAX_PATH];
	std::vector<Tagged> tags = readTaggedSet(trainedSet);
	while (openFileDlg(fname)){
		Mat src = imread(fname);

		char result = classify(tags, src, func, sampleSize);
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

void testBatch(const char* trainedSet, Vec2f(*func)(const Mat&), int sampleSize, const char* testDir, int rangeStart, int rangeEnd, char expected) {
	std::cout << "\n------------------------\n";
	if (expected == PEPSI)
		std::cout << "Testing for PEPSI";
	if (expected == COLA)
		std::cout << "Testing for COLA";
	std::cout << "\n------------------------\n";

	std::vector<Tagged> tags = readTaggedSet(trainedSet);
	int positive = 0, negative = 0;

	for (int i = rangeStart; i <= rangeEnd; i++) {
		Mat src = imread(folderFileJpg(testDir, i));
		char result = classify(tags, src, func, sampleSize);
		if (result == expected)
			positive++;
		else
			negative++;
	}

	std::cout << "Positive results: " << positive << "\n";
	std::cout << "Negative results: " << negative << "\n";
	std::cout << "Success rate: " << ((float)positive / (positive + negative))*100 << "%\n\n";
}