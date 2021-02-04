# NTUT EE ACV HW3
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
### Discussion:

**H3-1**

**1.建立新圖:** 按照pdf上的步驟實作，先算出rd,ru,theta(pdf上有計算的公式)在找出x,y的最大值，並將最大值*2除與n倍，取得新圖的size。

**2.Forward:** 新圖找到之後就進行forward運算，計算出ru,rd,theta,xd,yd，之後將原圖的(yd,xd)座標上的RGB像素點丟入新圖的(i,j)，但在這時有許多數值帶入會導致爆掉，所以要限制範圍(x在720,y在480)，不過在此的atan會有象限問題，所以在此要使用atan2，這樣子就完成了Forward。

**3.Inverse:** 在將圖片inverse的時候，先開一張大小隨意的圖片，並且設定一個初始值x0,y0，在運算的時候加回，並且與Forward計算一樣找出ru,rd,theta,xd,yd,將原圖的(yd,xd)座標上的RGB像素點丟入inverse圖片的(i,j)，同時也會有數值問題，需要設定範圍，即可完成。

![](https://i.imgur.com/v4OkI77.png)

![](https://i.imgur.com/ImxYuBQ.png)

**H3-2**

**1.建立新圖:** 從pdf上可得知許多參數，並接這些參數帶入公式中求出(x,y)的最大最小值，並將最大與最小值相減，除上一個n倍數之後，即可獲得新圖的size。

![](https://i.imgur.com/DXlVLn3.png)

**2.Forward:** 新圖找到之後就進行forward運算，帶入下列的公式即可或的forwaed的(U,V)
之後將原圖的(U,V)座標上的RGB像素點丟入新圖的(i,j)，但在這時有許多數值帶入會導致爆掉，所以要限制範圍，不過在此的atan不會有象限問題，所以可以直接使用atan這樣子就完成了Forward。

![](https://i.imgur.com/3EB6WYb.png)


**3.Inverse:** 在將圖片inverse的時候，先開一張大小隨意的圖片，並    且設定一個初始值x0,y0，在運算的時候加回，並且與Forward計算一樣算出(U,V),將原圖的(U,V)座標上的RGB像素點丟入inverse圖片的(i,j)，同時也會有數值問題，需要設定範圍，即可完成。

![](https://i.imgur.com/Qyvssp8.png)

![](https://i.imgur.com/WPt4F6E.png)

**Bonus**

加分題比較複雜的地方是在理解論文在寫甚麼，其實只要看懂論文之後，按照上面的做法就好做好多。

![](https://i.imgur.com/izRCWD9.png)

case2>case1為forward，case3也是forward，但此題如果使用forward圖片出來會破圖，所以要使用inverse來完成，其餘的部份與第一題跟第二題相同，學生在此就不多加贅述，以防增加助教的工作量。

![](https://i.imgur.com/EcvEXPP.png)

## :warning:嚴禁抄襲
這些只是提供我自己的想法而已，程式碼撰寫得也沒有到很嚴謹，禁止抄襲。

These are just to provide my own ideas, and the code is not written very rigorously. I hope that there will be no plagiarism.

## :smile: Owner
Made by https://github.com/WU-TING-HSUAN

## :+1: School
:point_right:National Taipei University of Technology	:point_left:
