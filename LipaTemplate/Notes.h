#pragma once
#include <vector>
#include <algorithm>
struct note
{
	int number;
	int value;
	int pitch;
	std::pair<int, int> position;

};
class Notes
{
private:
	std::vector<note> _notes;
	
public:
	Notes();
	Notes(Corelation & corel);
	~Notes();

private:
	void sortNotesAndAdd(std::vector<std::pair<int, int>> & noteVec);
	void printNotes();
	void findValue();

};

