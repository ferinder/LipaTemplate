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
	Image1CH idk(1200, 1920);
	median(image);
	histo(image);
	Edges = image;
	idk = image;
	rhorerBinarization(image,2);
//	close(image);
//	image.ShowImage("rhorer");
	image.SaveImage("img\\afterRhorer.png");
	rhorerBinarization(Edges, 1.2);
	rhorerBinarization(idk, 2.2);
	idk.SaveImage("img\\ziemniak.png");
	binarization2(image,170);
	findVerticalEdges(Edges);
	binarization2(Edges,25);
	close(Edges);
	Edges.SaveImage("img\\edges.png");
	correlation(image, idk,Edges);

	system("pause");

	return 0;
}