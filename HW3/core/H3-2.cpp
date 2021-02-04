#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include<math.h>
using namespace cv;
double PI = 3.1415926;
double cot(double a);
void main6() {
	double a = 15 * PI / 180, dx = 4, dy = -10, dz = 5, r0 = 0, theta0 = 0.025,x,y,y0,U,V;

	Mat road_Mat = imread("road.bmp");
	int m = road_Mat.rows, n = road_Mat.cols, x0new, y0new, xmax = 0, xmin = 1000, ymax = 0, ymin = 1000,xx,yy;

	//y0 = (road_Mat.rows - 1) / (2 * a) * (-theta0 + a);
	//m = m - y0;
	//Mat road_test = Mat(m, n, CV_8UC3);
	////printf("row:%d,col:%d", road_test.rows, road_test.cols);
	//for (int i = 0; i < m; i++) {
	//	for (int j = 0; j < n; j++) {
	//		road_test.at<Vec3b>(i, j)[0] = road_Mat.at<Vec3b>(i+y0, j)[0];
	//		road_test.at<Vec3b>(i, j)[1] = road_Mat.at<Vec3b>(i+y0, j)[1];
	//		road_test.at<Vec3b>(i, j)[2] = road_Mat.at<Vec3b>(i+y0, j)[2];
	//	}
	//}
	//imshow("road_test", road_test);
	for (int u = 0; u < road_Mat.rows; u++) {
		for (int v = 0; v < road_Mat.cols; v++) {
			x = dz * cot(theta0 - a + u * (2 * a / (m - 1))) * sin(r0 - a + v * (2 * a / (n - 1))) + dx;
			y = dz * cot(theta0 - a + u * (2 * a / (m - 1))) * cos(r0 - a + v * (2 * a / (n - 1))) + dy;
			if (xmax < x) {
				xmax = x;
			}
			if (ymax < y) {
				ymax = y;
			}
			if (xmin > x) {
				xmin = x;
			}
			if (ymin > y) {
				ymin = y;
			}
		}
	}
	printf("xmax:%d,xmin:%d,ymax:%d,ymin:%d", xmax, xmin, ymax, ymin);
	x0new = xmax- xmin;
	y0new = ymax- ymin;
	int count = 100;
	Mat road_Mat_new = Mat(x0new/ count, y0new/ count, CV_8UC3);
	for (int x = 0; x < road_Mat_new.rows; x++) {
		for (int y = 0; y < road_Mat_new.cols; y++) {
			xx = x * count + xmin;
			yy = y * count;
			U = round(((m - 1) / (2 * a)) * (atan(dz*sin(atan((xx-dx)/(yy-dy)))/(double)(xx-dx))-theta0 + a));
			V = round(((n - 1) / (2 * a)) * (atan((xx - dx)/(double)(yy - dy)) - r0 + a));
		/*	printf("U=%f,V=%f\n", U, V);*/
			if (U >= 0 && U < m && V >= 0 && V < n) {
				road_Mat_new.at<Vec3b>(x, y)[0] = road_Mat.at<Vec3b>(U, V)[0];
				road_Mat_new.at<Vec3b>(x, y)[1] = road_Mat.at<Vec3b>(U, V)[1];
				road_Mat_new.at<Vec3b>(x, y)[2] = road_Mat.at<Vec3b>(U, V)[2];
			}
		}
	}
	Mat road_Mat_inverse = Mat(x0new / count, y0new / count, CV_8UC3);
	for (int x = 0; x < road_Mat_inverse.rows; x++) {
		for (int y = 0; y < road_Mat_inverse.cols; y++) {
			xx = x - x0new / count/2 + x0new/2+xmin;
			yy = y;
			U = round(((m - 1) / (2 * a)) * (atan(dz * sin(atan((xx - dx) / (yy - dy))) / (double)(xx - dx)) - theta0 + a));
			V = round(((n - 1) / (2 * a)) * (atan((xx - dx) / (double)(yy - dy)) - r0 + a));
			/*	printf("U=%f,V=%f\n", U, V);*/
			if (U >= 0 && U < m && V >= 0 && V < n) {
				road_Mat_inverse.at<Vec3b>(x, y)[0] = road_Mat.at<Vec3b>(U, V)[0];
				road_Mat_inverse.at<Vec3b>(x, y)[1] = road_Mat.at<Vec3b>(U, V)[1];
				road_Mat_inverse.at<Vec3b>(x, y)[2] = road_Mat.at<Vec3b>(U, V)[2];
			}
		}
	}
	imshow("road_Mat_new", road_Mat_new);
	imshow("road_Mat_inverse", road_Mat_inverse);
	waitKey(0);
}
double cot(double a) {
	a = 1 /(double) tan(a);
	return a;
}