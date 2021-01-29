#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main3()
{
	/*每一列有 m 行(columns); array[i] 指向新 new 出的 m 個 int*/

	FILE* fpin0, fpin1, fpin2, fpin3, * fpout0, * fpout1, * fpout2, * fpout3;
	unsigned char header[54];
	/*fpin = fopen("InputImage1.bmp", "rb");
	fpout = fopen("InputImage_out.bmp", "wb");*/
	fpin0 = fopen("lena_cropped.bmp", "rb");
	fpout0 = fopen("BONUS1_out.bmp", "wb");
	/*unsigned char* lenai = new unsigned char[512*512*3];*/
	int i, j, k;   //p[2][3][4]
	for (int i = 0; i < 54; i++)
	{
		header[i] = fgetc(fpin0);
		printf("%d,", header[i]);
	}
	int WIDTH = header[18] * 1 + header[19] * 256 + header[20] * 256*256 + header[21] * 256*256*256;
	int HEIGHT = header[22] * 1 + header[23] * 256 + header[24] * 256 * 256 + header[25] * 256 * 256 * 256;
	printf("%d,", HEIGHT);
	unsigned char*** p = (unsigned char***)calloc(HEIGHT,sizeof(unsigned char**));
	unsigned char*** image = (unsigned char***)calloc(HEIGHT , sizeof(unsigned char**));
	unsigned char* I = (unsigned char*)calloc(54 + WIDTH * HEIGHT * 3, sizeof(unsigned char));
	unsigned char* ans = (unsigned char*)calloc(54 + WIDTH * HEIGHT * 3, sizeof(unsigned char));

	for (i = 0; i < HEIGHT; i++)
	{
		p[i] = (unsigned char**)calloc(WIDTH , sizeof(unsigned char*));
		image[i] = (unsigned char**)calloc(WIDTH , sizeof(unsigned char*));
		for (j = 0; j < WIDTH; j++)
		{
			p[i][j] = (unsigned char*)calloc(3 , sizeof(unsigned char));
			image[i][j] = (unsigned char*)calloc(3 , sizeof(unsigned char));
		}
	}
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			for (int k = 0; k < 3; k++) {
				image[i][j][k] = fgetc(fpin0);
				/*printf("%d", image);*/
			}
		}
	}
	//unsigned char tmp, tmp0, tmp1, tmp2;

	//for (int i = 0; i < WIDTH; i++) {
	//	for (int j = 0; j < HEIGHT; j++) {
	//		tmp0 = image[i][j][0];
	//		tmp1 = image[i][j][1];
	//		tmp2 = image[i][j][2];
	//		image[i][j][0] = tmp1;
	//		image[i][j][1] = tmp2;
	//		image[i][j][2] = tmp0;
	//	}
	//}
	unsigned char tmp, tmp0, tmp1, tmp2;
	for (int i = 0; i < HEIGHT / 2; i++) {
		for (int j = 0; j < WIDTH; j++) {
			for (int k = 0; k < 3; k++) {
				tmp = image[i][j][k];
				image[i][j][k] = image[HEIGHT -1- i][WIDTH -1 - j][k];
				image[HEIGHT - 1 - i][WIDTH - 1 - j][k] = tmp;
			}
		}
	}

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			for (int k = 0; k < 3; k++) {
				I[WIDTH * i * 3 + j * 3 + k] = image[i][j][k];
				/*printf("%d", image);*/
			}
		}
	}
	ans = (unsigned char*)calloc(54 + WIDTH * HEIGHT * 3, sizeof(unsigned char));
	for (i = 0; i < 54; i++) {
		ans[i] = header[i];
	}
	for (i = 54; i < WIDTH * HEIGHT * 3 + 54; i++) {
		ans[i] = I[i - 54];
	}
	fwrite(ans, sizeof(unsigned char), WIDTH * HEIGHT * 3 + 54, fpout0);

	fclose(fpin0);
	fclose(fpout0);
	free(p);
	free(image);
	system("pause");
	return 0;
}
