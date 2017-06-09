#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
struct note
{
	int number;
	double value;
	char pitch;
	std::pair<int, int> position;
};
class Notes
{
private:
	std::vector<note> _notes;

public:
	Notes();
	Notes(Corelation & corel, Image1CH & edges);
	~Notes();

private:
	//przesortowanie nut i dodanie ich w kolejno�ci
	void sortNotesAndAdd(std::vector<std::pair<int, int>> & noteVec);
	//wy�wietlenie nut w konsoli
	void printNotes();
	//obliczenie czasu trwania d�wi�ku
	void findValue();
	//obliczanie wysoko�ci dzwi�ku
	void findPitch(Image1CH & edges);
	//zapisuje nuty do pliku .txt
	void saveNotesToFIle();
};

