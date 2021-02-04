#include <opencv2/opencv.hpp>
#include <algorithm>
#include <iostream>
#include <time.h>
using namespace std;
using namespace cv;
clock_t t1, t2;
int main()
{
    Mat img_1 = imread("hand.bmp");
    Mat  src_img, edge, map, area, point, finger, finger_map, finger_area, finger_point;
    if ((src_img = cv::imread("hand.bmp", 0)).empty())
    {
        cout << "load image error！";
        return -1;
    }
    threshold(src_img, edge, 225, 255, THRESH_BINARY_INV);

    t1 = clock();
    int i, j, nccomps = connectedComponentsWithStats(edge, map, area, point);
    t2 = clock();
    printf("connect component時間%f\n", (t2 - t1) / (double)(CLOCKS_PER_SEC));
    printf("\n");
    
    t1 = clock();
    for (i = 0; i < nccomps; i++) {
        if (area.at<int>(i, CC_STAT_AREA) < 50000) {
            rectangle(img_1, Rect(area.at<int>(i, CC_STAT_LEFT), area.at<int>(i, CC_STAT_TOP), area.at<int>(i, CC_STAT_WIDTH), area.at<int>(i, CC_STAT_HEIGHT)), Scalar(0, 0, 255), 1, 1, 0);
            circle(img_1, Point((int)round(point.at<double>(i, 0)), (int)round(point.at<double>(i, 1))), 1, Scalar(0, 0, 255), 3);
        }

    }
    t2 = clock();
    printf("手的畫圖時間%f\n", (t2 - t1) / (double)(CLOCKS_PER_SEC));
    printf("\n");
    Mat element = getStructuringElement(MORPH_RECT, Size(25, 25));
    morphologyEx(edge, finger, MORPH_OPEN, element);
    Mat image = edge - finger;


    i, j, nccomps = connectedComponentsWithStats(image, finger_map, finger_area, finger_point);
    t1 = clock();
    for (i = 0; i < nccomps; i++) {
        if (finger_area.at<int>(i, CC_STAT_AREA) > 500 && finger_area.at<int>(i, CC_STAT_AREA) < 50000) {
            rectangle(img_1, Rect(finger_area.at<int>(i, CC_STAT_LEFT), finger_area.at<int>(i, CC_STAT_TOP), finger_area.at<int>(i, CC_STAT_WIDTH), finger_area.at<int>(i, CC_STAT_HEIGHT)), Scalar(255, 0, 0), 1, 1, 0);
            circle(img_1, Point((int)round(finger_point.at<double>(i, 0)), (int)round(finger_point.at<double>(i, 1))), 1, Scalar(255, 0, 0), 3);
        }

    }
    t2 = clock();
    printf("手指頭的畫圖時間%f\n", (t2 - t1) / (double)(CLOCKS_PER_SEC));
    printf("\n");
    imshow("圖片.jpg", img_1);
    waitKey(0);
}
