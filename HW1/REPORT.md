# NTUT EE ACV HW1
## :heart_eyes: Introduction my self
大家好，我是吳定軒，目前就讀於國立台北科技大學電機工程系碩士班，我將在我的github上分享我所實作的Project，內容也有許多需要改進的地方，如果你有甚麼建議歡迎寫信到我的信箱t109318095@ntut.org.tw。   

Hello everyone, I am TINGHSUAN-WU. I am currently studying in the Master's Program of the Department of Electrical Engineering, National Taipei University of Technology. I will share the projects I have done on my Github. There are many areas for improvement in the content. If you have any suggestions, welcome Write to my mailbox.

## :yum: Introduction this project
這份作業是ACV(高等電腦視覺)，我使用C++及opencv來撰寫。

This assignment is ACV (Advanced Computer Vision), I use C++ and opencv to write.

## :books: Source
1. Opencv4.4.0
2. Visual Studio 2019
3. Opencv_world440d.dll

## :book: Method

### Question 1 : Image Read/Write
Write a program to implement “bmp” format image reading and writing.

### Question 2 : Image Rotation
Do a 180-degree clockwise rotation over the input image to generate the output image.

### Question 3 : Image Channel Interchange
Interchange the channels of the rotated image,i.e., R > G, G > B, B > R.

### Bonus : 
Read and rotate the image with different size.(lena1024.bmp,lena_cropped.bmp)
### Discussion:
**(無使用opencv程式碼)**

我將它分為五大部份，第一部分為讀檔，第二部分為開設三維陣列，第三部分為將bmp值儲存至陣列裡，第四部份為運算(rotation、changecolor、bonus)，第五部份為寫入。

**一、 讀檔**

![](https://i.imgur.com/KBqGNIn.png)

宣告 *fpin及 *fpout以及unsigned char header來儲存bmp標頭檔前的54個數值

**二、 三維陣列**

![](https://i.imgur.com/8c4ASLF.png)

在這部份我是開設了兩個三維陣列 第一個為p[i][j][k]，第二個為image[i][j][k]

**三、 將bmp值存入三維陣列**

我先將前面54個表頭檔用fgetc存入header陣列裡

![](https://i.imgur.com/XP5exz8.png)

剩下來的值全數使用fgetc存入三維陣列image[i][j][k]

![](https://i.imgur.com/V9QaKvo.png)


**四、 運算**

**Rotation:**

![](https://i.imgur.com/AQsaiWH.png)

由於要上下顛倒，所以我開了一個空白的tmp來儲存原本的image，並將image陣列的頭尾互相交換


These are just to provide my own ideas, and the code is not written very rigorously. I hope that there will be no plagiarism.

**Changecolor:**

![](https://i.imgur.com/R8dfyeF.png)

開設三個空白的tmp0~tmp2，並將image的RGB值輪流存入，之後在將R轉G，G轉B，B轉R。

**五、 寫入**

![](https://i.imgur.com/7ATtaXw.png)

由於我最後寫入的檔案為一維陣列，所以我必須在前面先將三維陣列轉乘一維陣列，之後依序先將前54個標頭檔寫入，再把三維轉一維的陣列寫入，最後使用fwrite即可寫入。

**Bonus**

接下來是bonus的部份，我前面有先將54個標頭檔給讀出來，並且第18格矩陣至第21格矩陣維WIDTH，第19格矩陣至第25格陣列維HEIGHT，所以我就將它們個別讀出並且乘上該值，最後加總，即可得到圖片的長寬，在依序修改原先程式裡的512*512的值

![](https://i.imgur.com/5cgW0QW.png)

**使用opencv程式碼**

最後是Opencv的部份，非常的簡短，有三部份分別為讀檔、運算及寫檔。

**一、 讀檔**

![](https://i.imgur.com/bVIwxb9.png)

宣告一個Mat，並使用imread及可讀檔

**二、 運算**

**Rotation:**

![](https://i.imgur.com/ow1xyol.png)

Flip(Input檔，Output檔，-1為旋轉180)

**Changecolor:Changecolor:**

![](https://i.imgur.com/JJ0I7mh.png)

使用at<Vec3b>(座標)[顏色]，即可獲得該座標的r、g、b值，在將數值存入暫存器，並依序將R改成G、G改成B、B改成R即可完成

**三、 寫檔**

![](https://i.imgur.com/m7f6CKf.png)

Imwrite即可完成。

### Figure

**一、Rotation:**

![](https://i.imgur.com/KByg2az.png)

**二、 Changecolor:**

![](https://i.imgur.com/f6ycmdW.png)

**三、任意size:**

![](https://i.imgur.com/JZrJov0.png)

![](https://i.imgur.com/nBPZd5N.jpg)

**(使用opencv函式)**

![](https://i.imgur.com/5bXzX2o.png)


## :warning:嚴禁抄襲
這些只是提供我自己的想法而已，程式碼撰寫得也沒有到很嚴謹，禁止抄襲。

These are just to provide my own ideas, and the code is not written very rigorously. I hope that there will be no plagiarism.

## :smile: Owner
Made by https://github.com/WU-TING-HSUAN

## :+1: School
:point_right:National Taipei University of Technology	:point_left:
