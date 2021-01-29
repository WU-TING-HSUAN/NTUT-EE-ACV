#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
Mat Img,F1,F2;

int main()
{
    int pixelR, pixelG, pixelB, pixelR1, pixelG1, pixelB1;
    //載入原影像(不一定要讀檔，影像來源可以是webcam或程式繪出)
    Img = imread("lena_cropped.bmp");

    //以下是中間的處理過程
    //cvtColor(Img, Img, COLOR_BGR2GRAY); //轉為灰階
    //以上是中間的處理過程

   
    for (int i = 0; i < Img.rows; i++)
    {
        for (int j = 0; j < Img.cols; j++)
        {
            pixelR = Img.at<Vec3b>(i, j)[0];
            pixelG= Img.at<Vec3b>(i, j)[1];
            pixelB = Img.at<Vec3b>(i, j)[2];
            Img.at<Vec3b>(i, j)[0] = pixelG;
            Img.at<Vec3b>(i, j)[1] = pixelB;
            Img.at<Vec3b>(i, j)[2] = pixelR;
        }
    }
    flip(Img, F1, -1);
    //將cv::Mat型別的物件Img存為影像到同一目錄下,
    //檔名Result,格式JPG
    
    imwrite("Opencv.bmp", F1);

    //程式停滯在此，按任意鍵繼續(非必要)
    waitKey(0);
}