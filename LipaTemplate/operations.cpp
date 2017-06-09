#include "lipa.h"
#include "Corelation.h"
#include "Notes.h"
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
			if (image(i, j).I() <= threshold) output(i, j).I() = 1;
			else output(i, j).I() = 0;
			image = output;
};

void binarization2(Image1CH &image, double threshold) {
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
	Image1CH in(image.width(), image.height());
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
	double C = 1 / (fmax - fmin);
	for (int i = 0; i < image.width(); ++i)  //iterate by rows
		for (int j = 0; j < image.height(); ++j)  //iterate by cols
			image(i, j).Intensity() = in(i, j).Intensity() - fmin;
	for (int i = 0; i < image.width(); ++i)  //iterate by rows
		for (int j = 0; j < image.height(); ++j)  //iterate by cols
			image(i, j).Intensity() = image(i, j).Intensity()*C;
}

void correlation(Image1CH &image, Image1CH &bin,Image1CH &edges)
{
	Corelation Corel(image);
	Corel.calcCorelation(image);
	Corel.findNotesCenters();
	findNotes(Corel, bin,edges);
};

void findNotes(Corelation & cor,Image1CH & bin, Image1CH &edges)
{
	Notes notes(cor,bin,edges);
}

bool findZeros(std::vector<int> &vec) {

	for (auto it = vec.cbegin(); it != vec.cend(); ++it)
	{
		if (!*it) return true;
	}
	return false;
}


void erode(Image1CH & input)
{
	Image1CH output(input.width(), input.height());
	std::vector<int> surrending;
	for (int i = 1; i < input.width() - 1; ++i)
	{
		for (int j = 1; j < input.height() - 1; ++j)
		{
			for (int k = -1; k < 2; ++k)
			{
				for (int l = -1; l < 2; ++l)
				{
					surrending.push_back(input(i + k, j + l).I());
				}
			}
			if (findZeros(surrending)) output(i, j).I() = 0;
			else output(i, j).I() = 1;
			surrending.clear();
		}
	}
	input = output;
}

bool findOnes(std::vector<int> &vec) {

	for (auto it = vec.cbegin(); it != vec.cend(); ++it)
	{
		if (*it) return true;
	}
	return false;
}

void dilatation(Image1CH & input)
{
	Image1CH output(input.width(), input.height());
	std::vector<int> surrending(9);
	for (int i = 1; i < input.width() - 1; ++i)
	{
		for (int j = 1; j < input.height() - 1; ++j)
		{
			for (int k = -1; k < 2; ++k)
				for (int l = -1; l < 2; ++l)
				{
					surrending.push_back(input(i + k, j + l).I());
				}
			if (findOnes(surrending)) output(i, j).I() = 1;
			else output(i, j).I() = 0;
			surrending.clear();
		}
	}
	input = output;
}

void findVerticalEdges(Image1CH & image)
{
	Image1CH out(image.width(), image.height());
	double kernel[3][3] = { -1,  0,  1,
							-2,  0, 2,
							-1, 0, 1 };
	double temp;
	for (int i = 1; i < image.width() - 1; i++) { //iterate by rows
		for (int j = 100; j < image.height()/2 - 1; j++) { //iterate by cols
			temp = 0;
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					temp += image(i + k - 1, j + l - 1).I() *kernel[k][l];
				}
			}
			out(i, j).I() = temp;
		}
	}
	image = out;

}


void rhorerBinarization(Image1CH & image,double k)
{
	Image1CH output(image.width(), image.height());
	for (int i = 12; i < image.width()-12; ++i)
	{
		for (int j = 12; j < image.height()-12; ++j)
		{
			double avarge = 0;
			for (int k = -12; k < 13; ++k)
			{
				for (int l = -12; l < 13; ++l) 
				{
					avarge += image(i + k, j + l).I();
				}
			}
			avarge = avarge / (625*k);
			if (image(i,j).I()>=avarge)
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

void close(Image1CH & image)
{
	dilatation(image);
	erode(image);
}

