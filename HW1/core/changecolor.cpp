#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
		/*每一列有 m 行(columns); array[i] 指向新 new 出的 m 個 int*/
	
	FILE* fpin, * fpout;
	unsigned char header[54];
	/*fpin = fopen("InputImage1.bmp", "rb");
	fpout = fopen("InputImage_out.bmp", "wb");*/
	fpin = fopen("InputImage1.bmp", "rb");
	fpout = fopen("InputImageChangeColor_out.bmp", "wb");
	/*unsigned char* lenai = new unsigned char[512*512*3];*/
	int i, j, k;   //p[2][3][4]
	for (int i = 0; i < 54; i++)
	{
		header[i] = fgetc(fpin);
		printf("%d,", header[i]);
	}

	unsigned char*** p = (unsigned char***)malloc(512 * sizeof(unsigned char**));
	unsigned char*** image = (unsigned char***)malloc(512 * sizeof(unsigned char**));
	unsigned char* I = (unsigned char*)calloc(54 + 512 * 512 * 3, sizeof(unsigned char*));
	unsigned char* ans = (unsigned char*)calloc(54 + 512 * 512 * 3, sizeof(unsigned char*));



	for (i = 0; i < 512; i++)
	{
		p[i] = (unsigned char**)malloc(512 * sizeof(unsigned char*));
		image[i] = (unsigned char**)malloc(512 * sizeof(unsigned char*));
		for (j = 0; j < 512; j++)
		{
			p[i][j] = (unsigned char*)malloc(3 * sizeof(unsigned char));
			image[i][j] = (unsigned char*)malloc(3 * sizeof(unsigned char));
		}
	}
	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			for (int k = 0; k < 3; k++) {
				image[i][j][k] = fgetc(fpin);
				/*printf("%d", image);*/
			}
		}
	}
	unsigned char tmp, tmp0, tmp1,tmp2;

	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			tmp0 = image[i][j][0];
			tmp1 = image[i][j][1];
			tmp2 = image[i][j][2];
			image[i][j][0] = tmp1;
			image[i][j][1] = tmp2;
			image[i][j][2] = tmp0;
		}
	}

	for (int i = 0; i < 512 / 2; i++) {
		for (int j = 0; j < 512; j++) {
			for (int k = 0; k < 3; k++) {
				tmp = image[i][j][k];
				image[i][j][k] = image[511 - i][511 - j][k];
				image[511 - i][511 - j][k] = tmp;
			}
		}
	}

	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			for (int k = 0; k < 3; k++) {
				I[512*i*3+j*3+k] = image[i][j][k];
				/*printf("%d", image);*/
			}
		}
	}

	ans = (unsigned char*)calloc(54 + 512 * 512 * 3, sizeof(unsigned char));
	for (i = 0; i < 54; i++) {
		ans[i] = header[i];
	}
	for (i = 54; i < 512 * 512 * 3 + 54; i++) {
		ans[i] = I[i - 54];
	}
	fwrite(ans, sizeof(unsigned char),512*512 * 3 + 54, fpout);
	
	fclose(fpin);
	fclose(fpout);
	free(p);
	free(image);
	system("pause");
	return 0;
}
