#include "lipa.h"
#include "Corelation.h"
#include "Notes.h"
#include "operations.h"


void rgbTogray(Image3CH& rgbImg, Image1CH& grayImg) 
{
	for (int i = 0; i < rgbImg.width(); i++) //iterate by rows
		for (int j = 0; j < rgbImg.height(); j++) //iterate by cols
		{
			grayImg(i, j).Intensity() = (rgbImg(i, j).Red() + rgbImg(i, j).Green() + rgbImg(i, j).Blue()) / 3;
		}
}


void binarization(Image1CH &image, double threshold) 
{
	threshold = threshold / 256;
	for (int i = 0; i < image.width(); ++i)
		for (int j = 0; j < image.height(); ++j)
			if (image(i, j).I() <= threshold) image(i, j).I() = 0;
			else image(i, j).I() = 1;
};


void median(Image1CH &image)
{
	std::vector<double> surrending(9);
	Image1CH output(image.width(), image.height());
	for (int i = 1; i < image.width() - 1; ++i) 
	{
		for (int j = 1; j < image.height() - 1; ++j) 
		{
			for (int k = -1; k < 2; ++k) 
			{
				for (int l = -1; l < 2; ++l)
				{
					surrending.push_back(image(i + k, j + l).I());
				}
			}
			std::sort(surrending.begin(), surrending.end());
			output(i, j).I() = surrending[4];
			surrending.clear();
		}
	}
	image = output;
}

void histo(Image1CH& image) 
{
	double fmin = 1;
	double fmax = 0;
	for (int i = 0; i < image.width(); ++i)  //iterate by rows
		for (int j = 0; j < image.height(); ++j)  //iterate by cols
			if (fmin > image(i, j).Intensity())
				fmin = image(i, j).Intensity();
	for (int i = 0; i < image.width(); ++i)  //iterate by rows
		for (int j = 0; j < image.height(); ++j)  //iterate by cols
			if (fmax < image(i, j).Intensity())
				fmax = image(i, j).Intensity();
	double C = 1 / (fmax - fmin);
	for (int i = 0; i < image.width(); ++i)  //iterate by rows
		for (int j = 0; j < image.height(); ++j)  //iterate by cols
			image(i, j).Intensity() = image(i, j).Intensity() - fmin;
	for (int i = 0; i < image.width(); ++i)  //iterate by rows
		for (int j = 0; j < image.height(); ++j)  //iterate by cols
			image(i, j).Intensity() = image(i, j).Intensity()*C;
}

void findNotesInImage(Image1CH &image, Image1CH &edges)
{
	Corelation Corel(image);
	Corel.calcCorelation(image);
	Corel.findNotesCenters();
	findNotes(Corel, edges);
};

void findNotes(Corelation & cor, Image1CH &edges)
{
	Notes notes(cor, edges);
}

void findHorizontalEdges(Image1CH & image)
{
	Image1CH out(image.width(), image.height());
	double kernel[3][3] = { -1,  0,  1,
							-2,  0, 2,
							-1, 0, 1 };
	double temp;
	for (int i = 1; i < image.width() - 1; i++)
	{
		for (int j = 100; j < image.height() / 2 - 1; j++)
		{													 //podano takie zakresy, aby operacja by³a 
			temp = 0;										 //przeprowadzana jedynie na interesuj¹cym nas obszarze
			for (int k = 0; k < 3; k++) 
			{
				for (int l = 0; l < 3; l++) 
				{
					temp += image(i + k - 1, j + l - 1).I() *kernel[k][l];
				}
			}
			out(i, j).I() = temp;
		}
	}
	binarization(out, 25);
	image = out;

}

void rhorerBinarization(Image1CH & image, double k)
{
	Image1CH output(image.width(), image.height());
	for (int i = 12; i < image.width() - 12; ++i)
	{
		for (int j = 12; j < image.height() - 12; ++j)
		{
			double avarge = 0;
			for (int k = -12; k < 13; ++k)
			{
				for (int l = -12; l < 13; ++l)
				{
					avarge += image(i + k, j + l).I();
				}
			}
			avarge = avarge / (625 * k); //625 - iloœæ pikseli w otoczeniu
			if (image(i, j).I() >= avarge)
			{
				output(i, j).I() = 0;
			}
			else
			{
				output(i, j).I() = 1;
			}
		}
	}
	image = output;
}

