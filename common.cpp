#include "stdafx.h"

#include "common.h"
#include <CommDlg.h>
#include <ShlObj.h>

FileGetter::FileGetter(char* folderin,char* ext){		
	strcpy(folder,folderin);
	char folderstar[MAX_PATH];	
	if( !ext ) strcpy(ext,"*");
	sprintf(folderstar,"%s\\*.%s",folder,ext);
	hfind = FindFirstFileA(folderstar,&found);
	hasFiles= !(hfind == INVALID_HANDLE_VALUE);
	first = 1;
	//skip .
	//FindNextFileA(hfind,&found);		
}

int FileGetter::getNextFile(char* fname){
	if (!hasFiles)
		return 0;
	//skips .. when called for the first time
	if( first )
	{
		strcpy(fname, found.cFileName);				
		first = 0;
		return 1;
	}
	else{
		chk=FindNextFileA(hfind,&found);
		if (chk)
			strcpy(fname, found.cFileName);				
		return chk;
	}
}

int FileGetter::getNextAbsFile(char* fname){
	if (!hasFiles)
		return 0;
	//skips .. when called for the first time
	if( first )
	{
		sprintf(fname, "%s\\%s", folder, found.cFileName);			
		first = 0;
		return 1;
	}
	else{
		chk=FindNextFileA(hfind,&found);
		if (chk)
			sprintf(fname, "%s\\%s", folder, found.cFileName);				
		return chk;
	}
}

char* FileGetter::getFoundFileName(){
	if (!hasFiles)
		return 0;
	return found.cFileName;
}


int openFileDlg(char* fname)
{
	char *filter = "All Files (*.*)\0*.*\0";
	HWND owner = NULL;
	OPENFILENAME ofn;
	char fileName[MAX_PATH];
	strcpy(fileName,"");
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	GetOpenFileName(&ofn); 
	strcpy(fname,ofn.lpstrFile); 
	return strcmp(fname,"");
}

int openFolderDlg(char *folderName)
{
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	SHGetPathFromIDList(SHBrowseForFolder(&bi),folderName);
	return strcmp(folderName,"");
}

void resizeImg(Mat src, Mat &dst, int maxSize, bool interpolate)
{
	double ratio = 1;
	double w = src.cols;
	double h = src.rows;
	if (w>h)
		ratio = w/(double)maxSize;
	else
		ratio = h/(double)maxSize;
	int nw = (int) (w / ratio);
	int nh = (int) (h / ratio);
	Size sz(nw,nh);
	if (interpolate)
		resize(src,dst,sz);
	else
		resize(src,dst,sz,0,0,INTER_NEAREST);
}

float distance(std::vector<float> point1, std::vector<float> point2) {
	if (point1.size() != point2.size())
		return -1;

	float result = 0;

	for (int i = 0; i < point1.size(); i++) {
		float a = point1.at(i);
		float b = point2.at(i);
		result += (a - b) * (a - b);
	}

	return sqrt(result);
}

std::vector<float>  normalizeFromAngle(float angle) {
	angle = angle/360*2*PI;
	std::vector<float>  point;
	point.push_back(cos(angle));
	point.push_back(sin(angle));
	normalize(point);
	return point;
}

void normalize(std::vector<float>& point) {
	float length = sqrt(point.at(0) * point.at(0) + point.at(1) * point.at(1));
	point.at(0) /= length;
	point.at(1) /= length;
}