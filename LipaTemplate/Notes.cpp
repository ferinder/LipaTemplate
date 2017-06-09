#include "lipa.h"
#include "Corelation.h"
#include "Notes.h"

Notes::Notes()
{
}

Notes::Notes(Corelation & corel, Image1CH & edges)
{
	std::vector<std::pair<int, int>> tempVec;
	for (auto it : corel.getNotesCenters())
	{
		tempVec.push_back(it);
	}
	sortNotesAndAdd(tempVec);
	findValue();
	findPitch(edges);
	saveNotesToFIle();
	printNotes();

}


Notes::~Notes()
{
}

void Notes::saveNotesToFIle()
{
	std::ofstream file("notes.txt");
	file << "numer \t" << "dzwiek\t" << "dlugosc\t" << "pozycja x:y" << std::endl;
	for (auto it : _notes)
	{
		file << it.number << "\t" << it.pitch << "\t" << it.value << "\t" << it.position.first << ':' << it.position.second << std::endl;
		file.close();
	}
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
		std::cout << it.number << "\t" << it.pitch << "\t" << it.value << "\t" << it.position.first
			<< ':' << it.position.second << std::endl;
	}
}

void Notes::findValue()
{
	double val = 1;
	int dist = 1170;
	for (auto it = _notes.rbegin(); it != _notes.rend(); ++it)
	{
		dist = dist - it->position.first;
		if (dist < 0) //jeœli odleg³oœæ jest mniejsza od zera to znaczy, ¿e przeszliœmy do nuty z kolejnej pieciolinii
		{
			dist = 1170 - it->position.first;
		}

		if (dist <= 240 && dist > 138)
		{
			it->value = 1;
			dist = it->position.first;
			val -= 1;
		}
		else if (dist <= 138 && dist > 82)
		{
			it->value = 0.5;
			dist = it->position.first;
			val -= 0.5;
		}
		else if (dist <= 82 && dist > 50)
		{
			it->value = 0.25;
			dist = it->position.first;
			val -= 0.25;
		}
		else if (dist <= 50 && dist > 25)
		{
			it->value = 0.125;
			dist = it->position.first;
			val -= 0.125;
		}
		else
		{
			it->value = 10000;
			dist = it->position.first;
		}
		if (val == 0)
		{
			dist = dist - 24;
			val = 1;
		}
	}
}

void Notes::findPitch(Image1CH & edges)
{
	for (auto it = _notes.begin(); it != _notes.end(); ++it)
	{
		int upperLine = it->position.second;
		for (int i = 0; i > -80; --i)
		{
			for (int j = 0; j > -18; --j)
			{
				if (edges(it->position.first, it->position.second + i + j).I() == 1)
				{
					upperLine = it->position.second + i + j;
				}
			}
		}
		int dist = it->position.second - upperLine;
		if (dist > 20 && dist < 25)			it->pitch = 'B';
		else if (dist >= 25 && dist < 30)	it->pitch = 'A';
		else if (dist >= 30 && dist < 36)	it->pitch = 'G';
		else if (dist >= 36 && dist < 42)	it->pitch = 'F';
		else if (dist >= 42 && dist < 48)	it->pitch = 'E';
		else if (dist >= 48 && dist < 53)	it->pitch = 'D';
		else if (dist >= 53 && dist < 62)	it->pitch = 'C';
		else								it->pitch = 'O';
	}

}
