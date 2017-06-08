#include "lipa.h"
#include "ImageGrayscale.h"



ImageGrayscale::ImageGrayscale()
{
	//Image3CH colourImage(1200, 1920);
	Image1CH img(1200, 1920);
	//colourImage.LoadImage("img\\ideal.png");
	//rgbTogray(colourImage, img);
	_image = img;
}


ImageGrayscale::~ImageGrayscale()
{
}

void ImageGrayscale::ShowImage()
{
	this->_image.ShowImage("Obraz");
}

void ImageGrayscale::rgbTogray(Image3CH & rgbImg, Image1CH & grayImg)
{
	//Check if image sizes are equal
	if (rgbImg.width() == grayImg.width() && rgbImg.height() == grayImg.height())
	{
		for (int i = 0; i < rgbImg.width(); i++) //iterate by rows
			for (int j = 0; j < rgbImg.height(); j++) //iterate by cols
			{
				grayImg(i, j).Intensity() = (rgbImg(i, j).Red() + rgbImg(i, j).Green() + rgbImg(i, j).Blue()) / 3; // I = (1/3)*(R+G+B) (i,j) - (number of row, number of col)
			}
	}
	else
	{
		std::cerr << "Image sizes mismatch" << std::endl; //print error
		return;
	}
}
