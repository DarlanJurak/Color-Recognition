/*
*	@author:		Darlan Alves Jurak
*	@created:		17 may 2017
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

	//--------------------- Input Parameter ------------------------------------------------------

	string	imagePath;

	if ( argc == 1 ) // No argument
	{

		cout 	<< "\n Next time you can run this app passing a image path as argument." << endl;
		cout 	<< "Insert a image path: " << endl;
		cin 	>> imagePath;

	}else{ // Probably a image path argument	

		imagePath = argv[1];

	}
	
	//--------------------- Load Original Image---------------------------------------------------

	// Original image
	Mat imgOriginal = imread(imagePath, 1);

	//--------------------- Conversion to HSV image ----------------------------------------------

	// HSV format image
	Mat imgHSV;
	cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

	//--------------------- Build Image Mask for specific color ----------------------------------

	// Image mask
	Mat mask;

	// Image mask boundaries
	// Blue Values
	int mask_hue_LoBound = 95;
	int mask_hue_HiBound = 126;

	int mask_sat_LoBound = 63; 
	int mask_sat_HiBound = 186;

	int mask_val_LoBound = 114;
	int mask_val_HiBound = 255;

	// Maked Image
	Mat imgMask;

	// Apply mask
	inRange(imgHSV, Scalar(mask_hue_LoBound, mask_sat_LoBound, mask_val_LoBound), Scalar(mask_hue_HiBound, mask_sat_HiBound, mask_val_HiBound), imgMask);

	// Masked Image
	Mat imgMasked;

	// Creates masked image
	bitwise_and(imgOriginal, imgOriginal, imgMasked, imgMask);

	//--------------------- Windows Creation ------------------------------------------------------

	namedWindow("Original_Image", CV_WINDOW_FREERATIO);
	imshow("Original_Image", imgOriginal);
	waitKey(0);

	namedWindow("HSV_Image", CV_WINDOW_FREERATIO);
	imshow("HSV_Image", imgHSV);
	waitKey(0);

	namedWindow("Masked_Image", CV_WINDOW_FREERATIO);
	imshow("Masked_Image", imgMask);
	waitKey(0);

	namedWindow("BW_Image", CV_WINDOW_FREERATIO);
	imshow("BW_Image", imgMasked);
	waitKey(0);

	//--------------------- Color Detection ------------------------------------------------------

	Vec3d  pix;
    double hue;
	double sat;
	double val;

	// cout << "Row: " << imgMasked.rows << "\nColumn: " << imgMasked.cols << endl;

	for( int i = 0; i < imgMask.rows; i++){
		for( int j = 0; j < imgMask.cols; j++){

			pix = imgMask.at<Vec3d>(i,j);
			hue = pix.val[0];
			sat = pix.val[1];
			val = pix.val[2];

			if( (val > 0)){

				// cout << "Hue: " << hue << ". Sat: " << sat << ". Val: " << val << "." << endl;
				// cout << "PIX: " << pix << endl;
				cout << "Row: " << i << " Column: " << j << endl;
			}
		}				
	}

	return 0;
}
