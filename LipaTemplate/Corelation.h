#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

class Corelation
{
private:
	std::vector<std::vector<double>> _corelTab;
	std::vector<std::pair<int, int>> _notesCenters;
	int _width = 0;
	int _height = 0;
	std::vector<std::vector<int>> _corelMask = { //13x17- size
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,0,0 },
		{0,0,0,0,0,0,5,5,4,2,2,2,2,2,5,0,0 },
		{0,0,0,0,0,5,4,3,1,1,1,1,4,5,5,0,0 },
		{0,0,0,0,5,5,4,1,1,1,1,1,3,4,5,0,0 },
		{0,0,0,5,5,4,1,1,1,1,1,1,3,4,5,0,0 },
		{0,0,5,5,4,1,1,1,1,1,1,5,5,5,0,0,0 },
		{0,0,5,2,1,1,1,1,1,1,1,4,5,5,0,0,0 },
		{0,5,2,1,1,1,1,1,1,1,4,5,5,0,0,0,0 },
		{0,5,2,1,1,1,1,1,1,1,5,5,0,0,0,0,0 },
		{0,5,2,2,2,2,2,2,2,2,5,0,0,0,0,0,0 },
		{0,0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };
public:
	Corelation();
	Corelation(Image1CH & image);
	~Corelation();
	//obliczenie korelacji obrazu z mask¹
	void calcCorelation(Image1CH & image);
	//znajduje œrodki nut na podstawie vecotra maksimów korelacji
	void findNotesCenters();
	//zwraca vector par bêd¹cyh wspó³rzêdnymi œrodków nut
	std::vector<std::pair<int, int>> getNotesCenters() { return _notesCenters; };
private:
	//alokuje pamiêæ na tablicê korelacji
	void allocateMemory();
	//tworzy plik obrazu z zaznaczonymi œrodkami wyszukanych nut na tle obrazu idealnego
	void printNotesCenters();
};
