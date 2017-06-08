#pragma once
#include <vector>
class Corelation
{
private:
	std::vector<std::vector<int>> _corelTab;
	int _width = 0;
	int _height = 0;
public:
	Corelation();
	Corelation(Image1CH & image);
	~Corelation();
private:
	void allocateMemory();

};

