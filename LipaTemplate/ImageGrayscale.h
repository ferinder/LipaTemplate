#pragma once
#include <iostream>

class ImageGrayscale
{
private:
	Image1CH _image(int i=1200,int j=1920);
public:
	ImageGrayscale();
	~ImageGrayscale();
	void ShowImage();
private:
	void rgbTogray(Image3CH& rgbImg, Image1CH& grayImg);
};

