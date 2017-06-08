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
	for (int i = 0; i < _width; ++i) {
		_corelTab.push_back(std::vector<int>(_height));
	}
}