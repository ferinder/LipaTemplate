#include "lipa.h"
#include "operations.h"
#include <iostream>

//LipaLib - Learning Image Processing Autonomic Library

int main()
{
	Image3CH colourImage(1200, 1920);
	colourImage.LoadImage("img\\gained.png");
	Image1CH image(colourImage.width(), colourImage.height());
	rgbTogray(colourImage, image);
	Image1CH edges(image.width(), image.height());
	median(image);
	histo(image);
	edges = image;
	rhorerBinarization(image, 2); //po binaryzacji z tym wsp�czynnikiem zostaj� widoczne nuty prawie bez pi�ciolinii
	rhorerBinarization(edges, 1.2); // po binaryzacji z tym wsp�czynnikiem zostaj�widoczne pi�ciolinie
	findHorizontalEdges(edges);
	close(edges);
	findNotesInImage(image, edges);
	system("pause");

	return 0;
}