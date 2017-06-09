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
	std::pair<std::vector<int>, std::vector<int>> localHisto;

};
class Notes
{
private:
	std::vector<note> _notes;
	
public:
	Notes();
	Notes(Corelation & corel,Image1CH &bin,Image1CH & edges);
	~Notes();
	void calcLocalHisto(Image1CH & image);

private:
	void sortNotesAndAdd(std::vector<std::pair<int, int>> & noteVec);
	void printNotes();
	void findValue();
	void findPitch(Image1CH & edges);
	void saveNotesToFIle();

};

