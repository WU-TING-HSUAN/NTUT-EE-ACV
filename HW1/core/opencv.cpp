#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
Mat Img,F1,F2;

int main()
{
    int pixelR, pixelG, pixelB, pixelR1, pixelG1, pixelB1;
    //���J��v��(���@�w�nŪ�ɡA�v���ӷ��i�H�Owebcam�ε{��ø�X)
    Img = imread("lena_cropped.bmp");

    //�H�U�O�������B�z�L�{
    //cvtColor(Img, Img, COLOR_BGR2GRAY); //�ର�Ƕ�
    //�H�W�O�������B�z�L�{

   
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
    //�Ncv::Mat���O������Img�s���v����P�@�ؿ��U,
    //�ɦWResult,�榡JPG
    
    imwrite("Opencv.bmp", F1);

    //�{�������b���A�����N���~��(�D���n)
    waitKey(0);
}