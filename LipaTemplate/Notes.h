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
	//przesortowanie nut i dodanie ich w kolejnoœci
	void sortNotesAndAdd(std::vector<std::pair<int, int>> & noteVec);
	//wyœwietlenie nut w konsoli
	void printNotes();
	//obliczenie czasu trwania dŸwiêku
	void findValue();
	//obliczanie wysokoœci dzwiêku
	void findPitch(Image1CH & edges);
	//zapisuje nuty do pliku .txt
	void saveNotesToFIle();
};

