#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

// tranfsorm color image to grayscale
void rgbTogray(Image3CH & rgbImg, Image1CH & grayImg);

//binarization
void binarization(Image1CH &input, double threshold);

void binarization2(Image1CH & image, double threshold);

//filtr medianowy
void median(Image1CH & image);

//expand histogram
void histo(Image1CH & image);

//fining notes in image
void correlation(Image1CH & image);

bool findZeros(std::vector<int>& vec);

void erode(Image1CH & input);

bool findOnes(std::vector<int>& vec);

void dilatation(Image1CH & input);
