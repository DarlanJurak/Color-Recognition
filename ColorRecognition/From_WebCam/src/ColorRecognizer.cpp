#include <iostream>
#include <typeinfo>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "../include/color_recognizer_pkg.h"

using namespace cv;
using namespace std;


int main( int argc, char** argv )
{
    VideoCapture cap(0); //capture the video from web cam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }

    namedWindow("Control",CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 0;
	int iHighH = 179;

	int iLowS = 0; 
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
	
		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
      
		//morphological opening (removes small objects from the foreground)
		erode (imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5))); 

		//morphological closing (removes small holes from the foreground)
		dilate(imgThresholded, 	imgThresholded,	getStructuringElement(MORPH_ELLIPSE, Size(5, 5))); 
		erode (imgThresholded, 	imgThresholded,	getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		Mat bitWisedImage, mask;
		int mask_iLowH 	= mask_highBrightRubikCubeYellow_iLowH;
		int mask_iHighH = mask_highBrightRubikCubeYellow_iHighH;
		int mask_iLowS 	= mask_highBrightRubikCubeYellow_iLowS; 
		int mask_iHighS = mask_highBrightRubikCubeYellow_iHighS;
		int mask_iLowV 	= mask_highBrightRubikCubeYellow_iLowV;
		int mask_iHighV = mask_highBrightRubikCubeYellow_iHighV;

		// int mask_iLowH 	= iLowH;
		// int mask_iHighH = iHighH;
		// int mask_iLowS 	= iLowS; 
		// int mask_iHighS = iHighS;
		// int mask_iLowV 	= iLowV;
		// int mask_iHighV = iHighV;

		//Creates mask. Bounds defines chased color.
		inRange(imgHSV, Scalar(mask_iLowH, mask_iLowS, mask_iLowV), Scalar(mask_iHighH, mask_iHighS, mask_iHighV), mask);
		bitwise_and(imgOriginal, imgOriginal, bitWisedImage, mask);

		imshow("Thresholded Image", imgThresholded); 	//show the thresholded image
		imshow("Original", 			imgOriginal); 		//show the original image
		imshow("HSV Image", 		imgHSV); 			//show the HSV image
		imshow("Bitwised Image", 	bitWisedImage); 	//show the Filtered image

		Vec3d pix;
        double hue;
		double sat;
		double val;

		for( int i = 0; i < bitWisedImage.rows; i++){
			for( int j = 0; j < bitWisedImage.cols; j++){

				pix = bitWisedImage.at<typeof(pix)>(i,j);
				hue = pix.val[0];
				sat = pix.val[1];
				val = pix.val[2];

				// if( (hue > 1) && (sat > 1) && (val > 1)){

				// 	cout << "Hue: " << hue << ". Sat: " << sat << ". Val: " << val << "." << endl;
				// }
			}				
		}
	    
	   
    	if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
      	{
            cout << "esc key is pressed by user" << endl;

			// cout << "\nCanais: " << bitWisedImage.channels() << "\nLinhas: " << bitWisedImage.rows << "\nColunas: " << bitWisedImage.cols << endl;

            // Show last pixel info
			pix	= bitWisedImage.at<typeof(pix)>(bitWisedImage.rows -1, bitWisedImage.cols -1);
			hue = pix.val[0];
			sat = pix.val[1];
			val = pix.val[2];

			cout << "\nHue: " << hue << "\nSat: " << sat << "\nVal: " << val << endl;

            break; 
       	}

    }

   return 0;
}