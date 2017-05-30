/*
*	@author:		Darlan Alves Jurak
*	@date:			17 may 2017
*	@brief:			Change red color in a image to white and any other color to black.
* 	@limitation:	Fixed range.
*	@improve:		1 - Identify other colors;
*					2 -	Image as input arg. 
*/
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(){

	Mat image = imread("repo/img/RedBall.png", 1);
	namedWindow("Image", CV_WINDOW_FREERATIO);
	imshow("Image", image);
	waitKey(0);

	//Blue Green Red
	Mat outputImg;
	inRange(image, Scalar(10, 10, 100), Scalar(100, 100, 255), outputImg);

	namedWindow("Output", CV_WINDOW_FREERATIO);
	imshow("Output", outputImg);
	waitKey(0);

	cout << "Hello World" << endl;


	return 0;
}
