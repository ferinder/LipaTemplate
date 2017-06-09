#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

class Corelation
{
private:
	std::vector<std::vector<double>> _corelTab;
	int _width = 0;
	int _height = 0;
	std::vector<std::vector<int>> _corelMask= { //15x19 - size;
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },		//9x7 position of center
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,0,0,0 },
		{ 0,0,0,0,0,0,0,5,2,2,2,2,2,2,2,2,5,0,0 },
		{ 0,0,0,0,0,5,2,1,1,1,1,1,1,1,1,1,2,5,0 },
		{ 0,0,0,0,5,2,1,1,1,1,1,1,1,1,1,1,2,5,0 },
		{ 0,0,0,5,2,1,1,1,1,1,1,1,1,1,1,1,2,5,0 },
		{ 0,0,0,5,2,1,1,1,1,1,1,1,1,1,1,1,2,5,0 },
		{ 0,0,5,2,1,1,1,1,1,1,1,1,1,1,1,1,2,5,0 },
		{ 0,0,5,1,1,1,1,1,1,1,1,1,1,1,1,2,5,0,0 },
		{ 0,0,5,2,1,1,1,1,1,1,1,1,1,1,2,5,0,0,0 },
		{ 0,0,5,2,1,1,1,1,1,1,1,1,1,2,5,0,0,0,0 },
		{ 0,0,5,2,2,2,2,2,2,2,2,2,2,5,0,0,0,0,0 },
		{ 0,0,0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
	std::vector<std::pair<int, int>> _notesCenters;
public:
	Corelation();
	Corelation(Image1CH & image);
	~Corelation();
	void calcCorelation(Image1CH & image);
	void findNotesCenters();
private:
	void allocateMemory();
	void printNotesCenters();
};
