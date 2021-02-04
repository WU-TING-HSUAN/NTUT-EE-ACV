#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <time.h>
#include<math.h>
using namespace cv;
int map[512][512];
int binary_erosion(int a, int b,Mat c);
int binary_dilation(int a, int b, Mat c);
int range_reserch(Mat a,int b);
int count = 0;
int coun = 0;
int array[512];
int x[512];
int y[512];
int hand_x_point[5];
int hand_y_point[5];
int finger_count[5];
int hand_x_count = 0;
int hand_y_count = 0;
int finger_x_point[15];
int finger_y_point[15];
int finger_x_count = 0;
int finger_y_count = 0;
int min_x, min_y, max_x, max_y;
int dis;
int min_finger[15];
clock_t t1, t2;
Mat handmat = imread("hand.bmp");
int main() {
	
	Mat handmat_gray = Mat(handmat.rows, handmat.cols, CV_8UC1);
	Mat handmat_gray_no = Mat(handmat.rows, handmat.cols, CV_8UC1);
	Mat handmat_gray_no1 = Mat(handmat.rows, handmat.cols, CV_8UC1);
	Mat handmat_gray_finger = Mat(handmat.rows, handmat.cols, CV_8UC1);

	for (int i = 0; i < handmat.cols; i++) {
		for (int j = 0; j < handmat.rows; j++) {
			handmat_gray.at<uchar>(i, j) = (handmat.at<Vec3b>(i, j)[0] + handmat.at<Vec3b>(i, j)[1] + handmat.at<Vec3b>(i, j)[2]) / (float)3;
			handmat_gray_no.at<uchar>(i, j) = (handmat.at<Vec3b>(i, j)[0] + handmat.at<Vec3b>(i, j)[1] + handmat.at<Vec3b>(i, j)[2]) / (float)3;
			handmat_gray_no1.at<uchar>(i, j) = (handmat.at<Vec3b>(i, j)[0] + handmat.at<Vec3b>(i, j)[1] + handmat.at<Vec3b>(i, j)[2]) / (float)3;
			handmat_gray_finger.at<uchar>(i, j) = (handmat.at<Vec3b>(i, j)[0] + handmat.at<Vec3b>(i, j)[1] + handmat.at<Vec3b>(i, j)[2]) / (float)3;
		}
	}
	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			map[i][j] = 0;
			if (handmat_gray.at<uchar>(i, j) >= 225) {
				handmat_gray.at<uchar>(i, j) = 0;
				handmat_gray_no.at<uchar>(i, j) = 0;
				handmat_gray_no1.at<uchar>(i, j) = 0;
				handmat_gray_finger.at<uchar>(i, j) = 0;
			}
			else {
				handmat_gray.at<uchar>(i, j) = 255;
				handmat_gray_no.at<uchar>(i, j) = 255;
				handmat_gray_no1.at<uchar>(i, j) = 255;
				handmat_gray_finger.at<uchar>(i, j) = 255;
			}
		}
	}
	printf("手的重心");
	printf("\n");
	t1 = clock();
	range_reserch(handmat_gray,1);
	for (int i = 0; i < 512; i++) {

		if (array[i] > 500 && x[i] != 0 && y[i] != 0) {
			printf("%d,", hand_y_point[hand_y_count] = y[i] / array[i]);
			printf("%d", hand_x_point[hand_y_count] = x[i] / array[i]);
			printf("\n");
			hand_x_count += 1;
			hand_y_count += 1;
		}
	}
	t2 = clock();
	printf("手的connected component時間%lf\n", (t2 - t1) / (double)(CLOCKS_PER_SEC));
	t1 = clock();
	binary_erosion(25, 25, handmat_gray_no);

	binary_dilation(25, 25, handmat_gray_no);
	t2 = clock();
	printf("手的形態學時間:%lf\n", (t2 - t1) / (double)(CLOCKS_PER_SEC));
	//imshow("handmat", handmat);

	//waitKey(0);
	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			handmat_gray_no1.at<uchar>(i, j) = handmat_gray_no1.at<uchar>(i, j) - handmat_gray_no.at<uchar>(i, j);
		}
	}
	t1 = clock();
	binary_erosion(10,10, handmat_gray_no1);
	binary_dilation(10,10, handmat_gray_no1);
	t2 = clock();
	printf("手指頭的形態學時間:%lf\n", (t2 - t1) / (double)(CLOCKS_PER_SEC));
	printf("手指頭的重心");
	printf("\n");
	t1 = clock();
	range_reserch(handmat_gray_no1,3);
	for (int i = 0; i < 512; i++) {
		if (array[i] > 500 && x[i] != 0 && y[i] != 0) {
			printf("%d,", finger_y_point[finger_y_count] = y[i] / array[i]);
			printf("%d", finger_x_point[finger_x_count] = x[i] / array[i]);
			printf("\n");
			finger_y_count += 1;
			finger_x_count += 1;
		}
	}

	for (int i = 0; i < 15; i++) {
		int min = 1000;
		for (int j = 0; j < 5; j++) {
			dis = abs(hand_y_point[j] - finger_y_point[i]) + abs((hand_x_point[j] - finger_x_point[i]));
			if (min > dis) {
				coun = j;
				min = dis;
				min_finger[i] = min;
			}
		}
		finger_count[coun] += 1;
	}
	
	for (int i = 0; i < 5; i++) {
		printf("每隻手臂的手指頭數量:");
		printf("%d,", finger_count[i]);
		printf("\n");
	}
	t2 = clock();
	printf("手指頭的connected component時間%lf\n", (t2 - t1) / (double)(CLOCKS_PER_SEC));
	imshow("hand", handmat);

	waitKey(0);
	
}
int range_reserch(Mat a, int b) {
	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			map[i][j] = 0;
		}
	}
	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			if (a.at<uchar>(i, j) == 255 && i == 0 && j != 0) {
				if (a.at<uchar>(i, j - 1) != 255) {
					count += 1;
					map[i][j] = count;
				}
				else {
					map[i][j] = count;
				}
			}
			if (a.at<uchar>(i, j) == 255 && i != 0 && j == 0) {
				if (a.at<uchar>(i - 1, j) != 255) {
					count += 1;
					map[i][j] = count;
				}
				else {
					map[i][j] = count;
				}
			}
			if (a.at<uchar>(i, j) == 255 && i >= 1 && j >= 1) {
				if (a.at<uchar>(i, j - 1) != 255 && a.at<uchar>(i - 1, j) != 255) {
					count += 1;
					map[i][j] = count;
				}
				if (a.at<uchar>(i, j - 1) == 255 && a.at<uchar>(i - 1, j) != 255) {
					map[i][j] = map[i][j - 1];
				}
				if (a.at<uchar>(i, j - 1) != 255 && a.at<uchar>(i - 1, j) == 255) {
					map[i][j] = map[i - 1][j];
				}
				if (a.at<uchar>(i, j - 1) == 255 && a.at<uchar>(i - 1, j) == 255) {
					if (map[i][j - 1] >= map[i - 1][j]) {
						map[i][j] = map[i - 1][j];
					}
					if (map[i][j - 1] <= map[i - 1][j]) {
						map[i][j] = map[i][j - 1];
					}
				}
			}
		}
	}
	for (int x = 0; x < 1000; x++) {
		for (int i = 511; i >= 0; i--) {
			for (int j = 511; j >= 0; j--) {
				if (map[i][j] != 0 && i < 511 && j < 511) {
					if (map[i][j] <= map[i][j + 1]) {
						map[i][j + 1] = map[i][j];
					}
					if (map[i][j] <= map[i + 1][j]) {
						map[i + 1][j] = map[i][j];
					}
				}
			}
		}

		for (int i = 0; i < 512; i++) {
			for (int j = 0; j < 512; j++) {
				if (map[i][j] != 0 && i > 0 && j > 0) {
					if (map[i][j] <= map[i][j - 1]) {
						map[i][j - 1] = map[i][j];
					}
					if (map[i][j] <= map[i - 1][j]) {
						map[i - 1][j] = map[i][j];
					}
				}
			}
		}
		x += 1;
	}
	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			a.at<uchar>(i, j) = map[i][j];
			if (a.at<uchar>(i, j) == 0) {
				a.at<uchar>(i, j) = 255;
			}
		}
	}

	for (int i = 0; i < 512; i++) {
		array[i] = 0;
		x[i] = 0;
		y[i] = 0;
	}
	for (int i = 1; i <= count; i++) {
		max_x = 0;
		max_y = 0;
		min_x = 5000;
		min_y = 5000;
		for (int j = 0; j < 512; j++) {
			for (int k = 0; k < 512; k++) {
				if (map[j][k] == i) {
					array[i] += 1;
					x[i] = x[i]+k;
					y[i] = y[i] + j;
					if (max_x <= k) {
						max_x = k;
					}
					if (min_x >= k) {
						min_x = k;
					}
					if (max_y <= j) {
						max_y = j;
					}
					if (min_y >= j) {
						min_y = j;
					}

				}
			}
		}
	
		
		if (max_x >= min_x && max_y >= min_y && array[i]>500) {
			if (b == 1) {
				rectangle(handmat, Rect(min_x, min_y, max_x - min_x, max_y - min_y), Scalar(0, 0, 255));
			
				
			}
			if (b == 2) {
				rectangle(handmat, Rect(min_x, min_y, max_x - min_x, max_y - min_y), Scalar(0, 255, 0));
			}
			if (b == 3) {
				rectangle(handmat, Rect(min_x, min_y, max_x - min_x, max_y - min_y), Scalar(255, 0, 0));
			}
		}

	}
	return 0;
}
int binary_erosion(int a, int b,Mat c) {
	Mat handmat_erosion = Mat(c.rows, c.cols, CV_8UC1);
	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			handmat_erosion.at<uchar>(i, j) = c.at<uchar>(i, j);
			c.at<uchar>(i, j) = 0;
		}
	}
	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			int count = 0;
			for (int k = i - (a - 1) / 2; k <= i + (a - 1) / 2; k++) {
				for (int l = j - (b - 1) / 2; l <= j + (b - 1) / 2; l++) {
					if (k >= 0 && l >= 0 && k < 512 && l < 512) {
						if (handmat_erosion.at<uchar>(k, l) != 255) {
							count += 1;
						}
					}
				}
			}
			if (count == 0) {
				c.at<uchar>(i, j) = 255;
			}
			else {
				c.at<uchar>(i, j) = 0;
			}
		}
	}
	return 0;
}
int binary_dilation(int a, int b, Mat c) {
	Mat handmat_dilation = Mat(c.rows, c.cols, CV_8UC1);
	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			handmat_dilation.at<uchar>(i, j) = c.at<uchar>(i, j);
			c.at<uchar>(i, j) = 0;
		}
	}
	for (int i = 0; i < 512; i++) {
		for (int j =0; j < 512; j++) {
			int count = 0;
				for (int k = i - (a - 1) / 2; k <= i + (a - 1) / 2; k++) {
					for (int l = j - (b - 1) / 2; l <= j + (b - 1) / 2; l++) {
						if (k>=0 &&l>=0&&k<512&&l<512) {
							if (handmat_dilation.at<uchar>(k, l) == 255) {
								count += 1;
							}
						}
					}
				}
			if (count != 0) {
				c.at<uchar>(i, j) = 255;
			}
			else {
				c.at<uchar>(i, j) = 0;
			}
		}
	}
	return 0;
}
