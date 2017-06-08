#include "lipa.h"
#include "operations.h"


void rgbTogray(Image3CH& rgbImg, Image1CH& grayImg) // arguments with & because we want to save changes to images after performing funtion
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

void binarization(Image1CH &image, double threshold) {
	threshold = threshold / 256;
	Image1CH output(image.width(), image.height());
	for (int i = 0; i < image.width(); ++i)
		for (int j = 0; j < image.height(); ++j)
			if (image(i, j).I() <= threshold) output(i, j).I() = 0;
			else output(i, j).I() = 1;
			image = output;
};

void median(Image1CH &image) {
	std::vector<double> surrending;
	Image1CH output(image.width(), image.height());
	for (int i = 1; i < image.width() - 3; ++i) {
		for (int j = 1; j < image.height() - 3; ++j) {
			for (int k = -1; k < 2; ++k) {
				for (int l = -1; l < 2; ++l) {
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

void histo(Image1CH& image) {
	Image1CH in(image.width(),image.height());
	in = image;
	double fmin = 1;
	double fmax = 0;
	for (int i = 0; i < in.width(); ++i)  //iterate by rows
		for (int j = 0; j < in.height(); ++j)  //iterate by cols
			if (fmin > in(i, j).Intensity())
				fmin = in(i, j).Intensity();
	for (int i = 0; i < in.width(); ++i)  //iterate by rows
		for (int j = 0; j < in.height(); ++j)  //iterate by cols
			if (fmax < in(i, j).Intensity())
				fmax = in(i, j).Intensity();
	double C = 1/(fmax - fmin);
	for (int i = 0; i < image.width(); ++i)  //iterate by rows
		for (int j = 0; j < image.height(); ++j)  //iterate by cols
			image(i, j).Intensity() = in(i, j).Intensity() - fmin;
	for (int i = 0; i < image.width(); ++i)  //iterate by rows
		for (int j = 0; j < image.height(); ++j)  //iterate by cols
			image(i, j).Intensity() = image(i, j).Intensity()*C;
}

void correlation(Image1CH &image)
{
	std::vector<std::vector<int>> correlationMask = { //14x18;
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,0,0,0 },
		{0,0,0,0,0,0,5,2,2,2,2,2,2,2,2,5,0,0 },
		{0,0,0,0,5,2,1,1,1,1,1,1,1,1,1,2,5,0 },
		{0,0,0,5,2,1,1,1,1,1,1,1,1,1,1,2,5,0 },
		{0,0,5,2,1,1,1,1,1,1,1,1,1,1,1,2,5,0 },
		{0,0,5,2,1,1,1,1,1,1,1,1,1,1,1,2,5,0 },
		{0,5,2,1,1,1,1,1,1,1,1,1,1,1,1,2,5,0 },
		{0,5,1,1,1,1,1,1,1,1,1,1,1,1,2,5,0,0 },
		{0,5,2,1,1,1,1,1,1,1,1,1,1,2,5,0,0,0 },
		{0,5,2,1,1,1,1,1,1,1,1,1,2,5,0,0,0,0 },
		{0,5,2,2,2,2,2,2,2,2,2,2,5,0,0,0,0,0 },
		{0,0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};
	Image1CH output(image.width(), image.height());
	double temp = 0;
	for (int i = 9; i < image.width() - 18; ++i) {
		for (int j = 0; j < image.height() - 14; ++j) {
			temp = 0;
			for (int k=0;k<18;++k)
			{
				for (int l=0;l<14;++l) 
				{
 					temp += image(i + k,j + l).I() *correlationMask[k][l];
				}
			}
			output(i, j).I() = temp / 346;
		}
	}
	output.ShowImage("bin");

};