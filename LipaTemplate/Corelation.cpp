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
}

void Corelation::allocateMemory()
{
	for (int i = 0; i < _width; ++i)
	{
		_corelTab.push_back(std::vector<double>(_height));
	}
}

void Corelation::calcCorelation(Image1CH & image)
{
	double temp;
	int maskVal = [&]()->int {int val = 0; for (auto iterator : _corelMask) for (auto iterator2 : iterator) val += iterator2; return val; }();
	int distX, distY;
	for (int i = 8; i < _width - 8; i++)
	{
		for (int j = 6; j < _height / 2 - 6; ++j)
		{
			temp = 0;
			for (auto rowIt = _corelMask.cbegin(); rowIt != _corelMask.cend(); ++rowIt)
			{
				distY = std::distance(_corelMask.cbegin(), rowIt);
				for (auto columnIt = rowIt->cbegin(); columnIt != rowIt->cend(); ++columnIt)
				{
					distX = std::distance(rowIt->cbegin(), columnIt);
					temp += image(i - 8 + distX, j - 6 + distY).I() * *columnIt;
				}
			}
			_corelTab[i][j] = temp / maskVal;
		}
	}
}

void Corelation::findNotesCenters()
{	
	//znajdowanie maksimum lokalnego
	double r = 0;
	for (int i = 3; i < _width - 3; ++i)
	{
		for (int j = 3; j < _height / 2 - 3; ++j)
		{
			if (_corelTab[i][j] > 0.40)
			{
				if ([&]()->bool {
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
	//printNotesCenters();

	//usuwanie niew³aœciwych maksimów z piêciolinii le¿¹cych poza ni¹, lub na meritum
	for (auto it = _notesCenters.begin(); it != _notesCenters.end(); ++it)
	{
		if (it->first < 48
			|| (it->first > 55
				&& it->first < 75
				&& it->second > 200
				&& it->second < 300
				|| it->second < 100)
			)
		{
			_notesCenters.erase(it);
			it = std::prev(it);
		}
	}
	//usuwanie punktów z otoczenia maksimów
	for (auto iter = _notesCenters.begin(); iter != _notesCenters.end(); ++iter)
	{
		for (auto iter2 = _notesCenters.begin(); iter2 != _notesCenters.end(); ++iter2)
		{
			if (iter != iter2)
			{
				if (hypot((iter2->first - iter->first), (iter2->second - iter->second)) < 25)
				{
					_notesCenters.erase(iter2);
					iter2 = std::prev(iter2);
				}
			}
		}
	}

//	printNotesCenters();
}

void Corelation::printNotesCenters() {
	Image3CH image(1200, 1920);
	image.LoadImage("img\\ideal.png");
	for (auto it : _notesCenters)
	{
		image(it.first, it.second).G() = 1;
		image(it.first - 1, it.second).G() = 1;
		image(it.first, it.second - 1).G() = 1;
		image(it.first, it.second + 1).G() = 1;
		image(it.first + 1, it.second).G() = 1;
		image(it.first, it.second).B() = 1;
		image(it.first - 1, it.second).B() = 1;
		image(it.first, it.second - 1).B() = 1;
		image(it.first, it.second + 1).B() = 1;
		image(it.first + 1, it.second).B() = 1;
	}
	image.SaveImage("img\\i_think_centers.png");
}