//============================================================================
// Name        : asciiart.cpp
// Author      : Sam Button
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//#include <iostream>
//using namespace std;

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace cv;
int main(int argc, char **argv) {
	Mat inImage;
	Mat image;
	inImage = imread(argv[1], 1);
	resize(inImage, image, Size(), 0.40, 0.40);
	cout << argv[1] << endl;
	if (argc != 2 || !image.data) {
		printf("No image data \n");
		return -1;
	}

	printf("Successfully loaded image!\n");
	printf("Image size: %d x %d\n", image.cols, image.rows);

//  cout << "Channels: " << image.channels() << endl;
//  cout << "Blue: " << (uint) image.data[image.channels()*(image.cols*40 + 100) + 0] << endl;
//  cout << "Green: " << (uint) image.data[image.channels()*(image.cols*40 + 100) + 1] << endl;
//  cout << "Red: " << (uint) image.data[image.channels()*(image.cols*40 + 100) + 2] << endl;

//  cout << image.at<cv::Vec3b>(100,100)[0] << endl;
//  cout << image.at<cv::Vec3b>(100,100)[1] << endl;
//  cout << image.at<cv::Vec3b>(100,100)[2] << endl;

	unsigned char *brightness = new unsigned char[sizeof(unsigned char)
			* image.cols * image.rows];

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {

			int blue = image.data[image.channels() * (image.cols * i + j) + 0];
			int green = image.data[image.channels() * (image.cols * i + j) + 1];
			int red = image.data[image.channels() * (image.cols * i + j) + 2];

			brightness[image.cols * i + j] = (unsigned char) ((blue + green
					+ red) / 3);

//			printf("(%d, %d, %d) \n", red, green, blue);
//    	  image.at<cv::Vec3b>(i,j);
//          cout << image.at<unsigned int>(i,j);
		}
	}

	printf("Successfully constructed brightness matrix!");
	printf("Brightness matrix size: %d x %d\n", image.cols, image.rows);

	char *newCharacters = new char[sizeof(char) * image.cols * image.rows];

	const char *map =
			"`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

	int length = strlen(map);

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			int adjustedVal = (((double) brightness[image.cols * i + j] / (256.0))
					* ((double) length)) / 1;
			newCharacters[image.cols * i + j] = map[adjustedVal];
		}
	}

	printf("Successfully constructed ASCII matrix!");

	printf("Iterating!");
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			printf("%c", newCharacters[image.cols * i + j]);
			printf("%c", newCharacters[image.cols * i + j]);
		}
		printf("\n");
	}

//  printf( "At: %d\n", *image.at(0,0));

//  namedWindow( "Display Image", WINDOW_AUTOSIZE );
//  imshow( "Display Image", image );
//  waitKey(0);

	delete[] brightness;

	return 0;
}

