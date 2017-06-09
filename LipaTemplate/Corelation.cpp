#include "lipa.h"
#include "Corelation.h"



Corelation::Corelation()
{
}

Corelation::Corelation(Image1CH &image)
{
	this->_width = image.width();
	this->_height = image.height();
	this->allocateMemory();
}

Corelation::~Corelation()
{
	this->_corelTab.clear();
	this->_corelMask.clear();
}

void Corelation::allocateMemory()
{
	for (int i = 0; i < _width; ++i) 
	{
		_corelTab.push_back(std::vector<double>(_height));
	}
}

void Corelation::calcCorelation(Image1CH & image) {
	double temp;
	int distX, distY;
	for (int i = 9; i < _width - 9; i++)
	{
		for (int j = 7; j < _height/2 - 7; ++j)
		{
			temp = 0;
			for (auto rowIt = _corelMask.cbegin(); rowIt != _corelMask.cend(); ++rowIt)
			{
				distY = std::distance(_corelMask.cbegin(), rowIt);
				for (auto columnIt = rowIt->cbegin(); columnIt != rowIt->cend(); ++columnIt)
				{
					distX = std::distance(rowIt->cbegin(), columnIt);
					temp += image(i - 9 + distX, j - 7 + distY).I() * *columnIt;
				}
			}
			_corelTab[i][j] = temp / 346;
		}
	}
}

std::vector<std::pair<int, int>> Corelation::findNotesCenters()
{
	//znajdowanie maksimum lokalnego
	double r = 0;
	for (int i = 3; i < _width - 3; ++i)
	{
		for (int j = 3; j < _height/2 - 3; ++j)
		{
			if (_corelTab[i][j]>0.7)
			{
				if ([&]() ->bool{
					for (int k = -3; k < 4; ++k)
						for (int l = -3; l < 4; ++l)
							if (_corelTab[i + k][j + l] > _corelTab[i][j]) return false;
					return true;
				} ())
					_notesCenters.push_back(std::make_pair(i, j));
				else _corelTab[i][j] = 0;
			}
		}
	}

	//usuwanie punktów z otoczenia i pierwszych zbêdnych z piêciolinii
	for (auto it = _notesCenters.begin(); it != _notesCenters.end() - 1; ++it)
	{
		if (it->first < 48
			||(it->first > 55 
				&& it->first < 75 
				&& it->second>200 
				&& it->second < 300) 
			)
		{
			_notesCenters.erase(it);
			it = std::prev(it);
		}
	}
	for (auto iter = _notesCenters.begin(); iter != _notesCenters.end(); ++iter)
	{
		for (auto iter2 = _notesCenters.begin(); iter2 != _notesCenters.end(); ++iter2)
		{
			if (iter != iter2)
			{
				if (hypot((iter2->first - iter->first), (iter2->second - iter->second)) < 12)
				{
					_notesCenters.erase(iter2);
					iter2 = std::prev(iter2);
				}
			}
		}
	}
	this->printNotesCenters();
	return _notesCenters;
}

void Corelation::printNotesCenters() {
	for (auto it : _notesCenters)
	{
		std::cout << it.first << "  " << it.second << std::endl;
	}
	Image3CH image(1200, 1920);
	image.LoadImage("img\\ideal.png");
	for (auto it : _notesCenters)
	{
		//image(it.first, it.second).Red() = 1;

		image(it.first, it.second).G() = 1;

		image(it.first, it.second).B() = 1;
	}
	image.ShowImage("img\\i_think_centers.png");
}