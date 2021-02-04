#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include<math.h>
using namespace cv;

void main3()
{
	int x0 = 360,y0 = 240,xu,yu, x_max = 0, y_max = 0,xd,yd,new_i,new_j,n;
	double rd,ru,w=0.0036,theta,x0new,y0new;
	Mat distortion_Mat = imread("distortion.bmp");
	/*printf("row:%d,col:%d", distortion_Mat.rows, distortion_Mat.cols);*/
	for (int i = 0; i < distortion_Mat.rows; i++) {
		for (int j = 0; j < distortion_Mat.cols; j++) {
			rd = sqrt(pow(j - x0, 2) + pow(i - y0, 2));
			ru = tan(rd * w) / (2 * tan(w / 2));
			theta = atan((i - y0)/(double)(j - x0));
			if (x_max < ru * cos(theta)) {
				x_max = ru * cos(theta);
			}
			if (y_max < ru * sin(theta)) {
				y_max = ru * sin(theta);
			}
		}
	}
	x0new = x_max;
	y0new = y_max;
	n = 40;
	x_max = x_max*2 /n;
	y_max = y_max*2 /n;
	printf(" xmax:%d,ymax:%d", x_max*n, y_max*n);
	Mat distortion_Mat_new = Mat(y_max, x_max, CV_8UC3);
	for (int i = 0; i < distortion_Mat_new.rows; i++) {
		for (int j = 0; j < distortion_Mat_new.cols; j++) {
			distortion_Mat_new.at<Vec3b>(i, j)[0] = 128;
			distortion_Mat_new.at<Vec3b>(i, j)[1] = 128;
			distortion_Mat_new.at<Vec3b>(i, j)[2] = 128;
		}
	}

	for (int i = 0; i < y_max; i++) {
		for (int j = 0; j < x_max; j++) {
			new_i = i * n; 
			new_j = j * n;
			ru = sqrt(pow(new_j- x0new,2)+pow(new_i - y0new,2));
			rd = (1 / 0.0036) * atan(2 * ru * tan(0.0036 / 2));
			theta = atan2((new_i - y0new),(new_j - x0new));
			xd = round(rd * cos(theta))+x0;
			yd = round(rd * sin(theta))+y0;
			if (xd >= 0 && xd < 720 && yd >= 0 && yd < 480) {
				distortion_Mat_new.at<Vec3b>(i, j)[0] = distortion_Mat.at<Vec3b>(yd, xd)[0];
				distortion_Mat_new.at<Vec3b>(i, j)[1] = distortion_Mat.at<Vec3b>(yd, xd)[1];
				distortion_Mat_new.at<Vec3b>(i, j)[2] = distortion_Mat.at<Vec3b>(yd, xd)[2];
			}
		}
	}
	int inverse_y = 1200, inverse_x = 900;
	Mat inverse(inverse_x, inverse_y, CV_8UC3);
	int x00 = x0new- inverse_y /2, y00 = y0new- inverse_x /2;
	int nx, ny;
	for (int i = 0; i < inverse_x; i++) {
		for (int j = 0; j < inverse_y; j++) {
			nx = j + x00;
			ny = i + y00;
			ru = sqrt(pow(nx - x0new, 2) + pow(ny - y0new, 2));
			theta = atan2(ny - y0new, nx - x0new);
			rd = (1 / 0.0036) * atan(2 * ru * tan(0.0036 / 2));
			xd = round(rd * cos(theta)) + x0;
			yd = round(rd * sin(theta)) + y0;
			if (xd >= 0 && xd < 720 && yd >= 0 && yd < 480) {
				inverse.at<Vec3b>(i, j)[0] = distortion_Mat.at<Vec3b>(yd, xd)[0];
				inverse.at<Vec3b>(i, j)[1] = distortion_Mat.at<Vec3b>(yd, xd)[1];
				inverse.at<Vec3b>(i, j)[2] = distortion_Mat.at<Vec3b>(yd, xd)[2];
			}
		}
	}
	//printf(" xmax:%d,ymax:%d", x_max, y_max);
	imshow("distortion_Mat", distortion_Mat);
	imshow("distortion_Mat_new", distortion_Mat_new);
	imshow("inverse", inverse);
	waitKey(0);
}