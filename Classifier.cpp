#include "stdafx.h"

#include "Classifier.h"

#define folderFileJpg(x,y) (std::string(x) + "/" + std::to_string(y) + ".jpg").c_str()

int size(Mat matrix) {
	return matrix.cols * matrix.rows;
}

void train(const char* folderName, const char* dstName, int rangeStart, int rangeEnd, char tag, int (*func)(Mat), bool append = false) {
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

std::vector<Tagged> readTaggedSet(const char* fileName) {
	std::ifstream input(fileName);
	std::vector<Tagged> tags;

	int value;
	char tag;

	while (input >> tag >> value) {
		tags.push_back(Tagged(tag, value));
	}

	input.close();

	return tags;
}

char knn(std::vector<Tagged> tags, int value, int sampleSize) {
	char freq[27] = {'\0'};
	for (int i = 0; i < sampleSize; i++) {
		int minDistance = INT_MAX;
		int foundIndex = 0;
		for (int j = 0; j < tags.size(); j++) {
			if (abs(value - tags.at(j).value) < minDistance) {
				minDistance = abs(value - tags.at(j).value);
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

void classify(const char* trainedSet, int (*func)(Mat), int sampleSize) {
	char fname[MAX_PATH];
	while (openFileDlg(fname)){
		Mat src = imread(fname);

		char result = knn(readTaggedSet(trainedSet), func(src), sampleSize);
		if (result == 'c')
			std::cout << "Coca Cola";
		else if(result == 'p')
			std::cout << "Pepsi";
		else
			std::cout << "Other";
		std::cout << "\n";

		imshow("image", src);
		waitKey();
	}
}