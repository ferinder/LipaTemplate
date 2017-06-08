#include "lipa.h"
#include <iostream>
#include "operations.h"

//LipaLib - Learning Image Processing Autonomic Library



int main()
{
	Image1CH image(1200, 1920);
	{
		Image3CH colourImage(1200, 1920);
		colourImage.LoadImage("img\\ideal.png");
		rgbTogray(colourImage, image);
	}

	median(image);
	histo(image);
	binarization(image, 165);
	correlation(image);
	std::cout << "a tu nie";
	binarization2(image,170);
	image.ShowImage("bin");
	//image.SaveImage("img\\bin.png");






	//Image3CH ColourImage(600, 800); // Create new image Image3CH - three channels image (width,height)

	//ColourImage.LoadImage("img\\lena512.jpg", LPL_LOAD_FITTED); //Load image, (path, flag) flags : LPL_LOAD_ORIGINAL - size of image same as in file, LPL_LOAD_FITTED - resize loaded image to container dimensions
	////ColourImage.LoadImage("img\\lena512.jpg",LPL_LOAD_ORIGINAL);
	//
	//Image1CH GrayscaleImage(600, 800); //Load image, (path, flag), default flag is LPL_LOAD_FITTED, no need to pass it every time
	////Image1CH GrayscaleImage(ColourImage.width(), ColourImage.height());

	////easy version, no function creation needed
	//for (int i = 0; i < ColourImage.width(); i++)
	//	for (int j = 0; j < ColourImage.height(); j++)
	//	{
	//		GrayscaleImage(i, j).Intensity() =  (ColourImage(i, j).Red() + ColourImage(i, j).Green() + ColourImage(i, j).Blue()) / 3;
	//	}

	////version with custom function
	////rgbTogray(ColourImage, GrayscaleImage);

	////GrayscaleImage.DrawPoint(110, 110); //Draw point in image (x,y)
	//ColourImage.ShowImage("res"); //Show image
	//GrayscaleImage.ShowImage("res"); //Show image
	//ColourImage.ShowHistogram(); // Show image histograms

	return 0;
}