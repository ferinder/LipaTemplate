#pragma once
#include "Corelation.h"
#include <iostream>
#include <vector>
#include <algorithm>

// zamiana obrazu kolorowego na obraz w skali szaroœci
void rgbTogray(Image3CH & rgbImg, Image1CH & grayImg);

//binarization
void binarization(Image1CH & image, double threshold);

//filtr medianowy
void median(Image1CH & image);

//wyrównanie histogram
void histo(Image1CH & image);

//wyszukanie nut na podstawie korelacji
void findNotes(Corelation & cor, Image1CH & edges);

//wyszukanie nut w obrazie
void findNotesInImage(Image1CH & image, Image1CH & edges);

//filtracja, w wyniku której otrzymujemy zbinaryzowany obraz z poziomymi krawêdziami
void findHorizontalEdges(Image1CH & image);

//Algorytm binaryzacji obrazu White'a Rhorer'a
void rhorerBinarization(Image1CH & image, double k);