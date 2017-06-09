#include "lipa.h"
#include "operations.h"
#include <iostream>

//LipaLib - Learning Image Processing Autonomic Library

int main()
{
	Image1CH image(1200, 1920);
	{
		Image3CH colourImage(1200, 1920);
		colourImage.LoadImage("img\\ideal.png");
		rgbTogray(colourImage, image);
	}
	Image1CH Edges(1200, 1920);

	median(image);
	histo(image);
	Edges = image;
	binarization(image, 165);
	correlation(image);
	binarization2(image,170);
	findVerticalEdges(Edges);
	binarization2(Edges,25);
	dilatation(Edges);
	erode(Edges);
	Edges.ShowImage("bin");

	return 0;
}