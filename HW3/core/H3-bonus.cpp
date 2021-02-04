#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include<math.h>
using namespace cv;
int def(int a, int b, int c, int d);
void main() {
	double x0 = 130, y0 = 250, x1 = 470, y1 = 310, x2 = 475, y2 = 900, x3 = 0, y3 = 770, x_total = x0 - x1 + x2 - x3, y_total = y0 - y1 + y2 - y3, dx1 = x1 - x2, dx2 = x3 - x2, dy1 = y1 - y2, dy2 = y3 - y2;
	double X0 = 0, Y0 = 0, X1 = 370, Y1 = 0, X2 = 370, Y2 = 510, X3 = 0, Y3 = 510, X_total = X0 - X1 + X2 - X3, Y_total = Y0 - Y1 + Y2 - Y3, dX1 = X1 - X2, dX2 = X3 - X2, dY1 = Y1 - Y2, dY2 = Y3 - Y2;
	double u, v, q,X,Y,W;
	double a, b, c, d, e, f, g, h,A,B,C,D,E,F,G,H,I, a_f, b_f, c_f, d_f, e_f, f_f, g_f, h_f;
	double a1, b1, c1, d1, e1, f1, g1, h1, i1;
	double i = 1, w = 1;
	double x, y;
	Mat left_Mat = imread("left.bmp");
	Mat right_Mat = imread("right.bmp");
	Mat ans = Mat(480, 900, CV_8UC3);
	c = x0;
	f = y0;
	g = def(x_total, dx2, y_total, dy2) / (double)def(dx1, dx2, dy1, dy2);
	h = def(dx1, x_total, dy1, y_total) / (double)def(dx1, dx2, dy1, dy2);
	a = x1 - x0 + g * x1;
	b = x3 - x0 + h * x3;
	d = y1 - y0 + g * y1;
	e = y3 - y0 + h * y3;

	A = e * i - f * h;
	B = c * h - b * i;
	C = b * f - c * e;
	D = f * g - d * i;
	E = a * i - c * g;
	F = c * d - a * f;
	G = d * h - e * g;
	H = b * g - a * h;
	I = a * e - b * d;
	printf("%f,%f,%f\n",A,B,C);
	printf("%f,%f,%f\n", D, E, F);

	c_f = X0;
	f_f = Y0;
	g_f = def(X_total, dX2, Y_total, dY2) / (double)def(dX1, dX2, dY1, dY2);
	h_f = def(dX1, X_total, dY1, Y_total) / (double)def(dX1, dX2, dY1, dY2);
	a_f = X1 - X0 + g_f * X1;
	b_f = X3 - X0 + h_f * X3;
	d_f = Y1 - Y0 + g_f * Y1;
	e_f = Y3 - Y0 + h_f * Y3;

	a1 = A * a_f + D * b_f + G * c_f;
	b1 = B * a_f + E * b_f + H * c_f;
	c1 = C * a_f + F * b_f + I * c_f;
	d1 = A * d_f + D * e_f + G * f_f;
	e1 = B * d_f + E * e_f + H * f_f;
	f1 = C * d_f + F * e_f + I * f_f;
	g1 = A * g_f + D * h_f + G * 1;
	h1 = B * g_f + E * h_f + H * 1;
	i1 = C * g_f + F * h_f + I * 1;

	for (int i = 80; i < 449; i++) {
		for (int j = 0; j < 509; j++) {
			ans.at<Vec3b>(i, j)[0] = left_Mat.at<Vec3b>(i-80, j)[0];
			ans.at<Vec3b>(i, j)[1] = left_Mat.at<Vec3b>(i-80, j)[1];
			ans.at<Vec3b>(i, j)[2] = left_Mat.at<Vec3b>(i-80, j)[2];
		}
	}
	for (int X=0; X < ans.rows; X++) {
		for (int Y=0; Y < ans.cols; Y++) {
			x = (a1 * X + b1 * Y + c1) / (g1 * X + h1 * Y + i1);
			y = (d1 * X + e1 * Y + f1) / (g1 * X + h1 * Y + i1);
			if (x >= 0 && x < right_Mat.rows && y >= 0 && y < right_Mat.cols) {
				ans.at<Vec3b>(X, Y)[0] = right_Mat.at<Vec3b>(x, y)[0];
				ans.at<Vec3b>(X, Y)[1] = right_Mat.at<Vec3b>(x, y)[1];
				ans.at<Vec3b>(X, Y)[2] = right_Mat.at<Vec3b>(x, y)[2];
			}
		}
	}
	/*imshow("right_Mat", right_Mat);*/
	imshow("right", ans);
	waitKey(0);
}
int def(int a, int b, int c, int d) {
	int left, right, answer;
	left = a * d;
	right = b * c;
	answer = left - right;
	return answer;
}