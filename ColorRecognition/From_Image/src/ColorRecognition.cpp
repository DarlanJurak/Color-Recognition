/*
*	@author:		Darlan Alves Jurak
*	@date:			17 may 2017
*	@brief:			Change red color in a image to white and any other color to black.
* 	@limitation:	Fixed range.
*	@improve:		1 - Identify other colors;
*/
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]){

	string	imagePath;

	if ( argc == 1 ) // No argument
	{

		cout 	<< "Next time you can run this app passing a image path as argument." << endl;
		cout 	<< "Insert a image path: " << endl;
		cin 	>> imagePath;

	}else{ // Probably a image path argument	

		imagePath = argv[1];

	}
	
	Mat image = imread(imagePath, 1);
	namedWindow("Image", CV_WINDOW_FREERATIO);
	imshow("Image", image);
	waitKey(0);

	//Blue Green Red
	Mat outputImg;
	inRange(image, Scalar(10, 10, 100), Scalar(100, 100, 255), outputImg);

	namedWindow("Output", CV_WINDOW_FREERATIO);
	imshow("Output", outputImg);
	waitKey(0);

	return 0;
}
