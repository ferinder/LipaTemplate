#include "lipa.h"
#include "operations.h"
#include <iostream>

//LipaLib - Learning Image Processing Autonomic Library

int main()
{
	Image1CH image(1200, 1920);
	{
		Image3CH colourImage(1200, 1920);
		colourImage.LoadImage("img\\noised.png");
		rgbTogray(colourImage, image);
	}

	median(image);
	histo(image);
	binarization(image, 165);
	correlation(image);
	binarization2(image,170);
	image.ShowImage("bin");

	return 0;
}