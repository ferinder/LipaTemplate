#include "lipa.h"
#include "Corelation.h"
#include "Notes.h"



Notes::Notes()
{
}

Notes::Notes(Corelation & corel)
{
	std::vector<std::pair<int, int>> tempVec;
	for (auto it : corel.findNotesCenters())
	{
		tempVec.push_back(it);
	}
	sortNotesAndAdd(tempVec);
	printNotes();

}


Notes::~Notes()
{
}

void Notes::sortNotesAndAdd(std::vector<std::pair<int, int>> & noteVec)
{
	std::sort(noteVec.begin(), noteVec.end(),
		[](std::pair<int, int> a, std::pair<int, int> b) {return a.second < b.second; });
	int num = 1;
	for (int i = 150; i < 850; )
	{
		std::vector<note> tempNoteVec;
		for (auto it : noteVec)
		{
			if (it.second > i && it.second < i + 190)
			{
				note tempNote;
				std::cout << "note pos" << it.first << "  " << it.second << std::endl;
				tempNote.position = it;
				tempNoteVec.push_back(tempNote);
			}
		}
		i += 190;
		std::sort(tempNoteVec.begin(), tempNoteVec.end(), [](note a, note b) {return a.position.first < b.position.first; });

		for (auto it : tempNoteVec)
		{
			it.number = num;
			_notes.push_back(it);
			++num;
		}
		tempNoteVec.clear();
	}
}

void Notes::printNotes()
{
	for (auto it : _notes)
	{
		std::cout << it.number << "\t" << it.position.first 
			<< ':' << it.position.second << std::endl;
	}
}

void Notes::findValue()
{
	for (auto it= _notes.cbegin();it!=_notes.cend();++it)
	{
		int distance = hypot((it->position.first - (it + 1)->position.first), (it->position.second - (it + 1)->position.second));
		if (distance < )
	}
}