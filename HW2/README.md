# NTUT EE ACV HW2
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
### Topic : Connected components
### Question 1 : Label the five hands with 4-connected neighbor
1. Label each connected component (large area) with a RED bounding box in output image.
2. Compute the centroid and area of each hand, and print the data on output image or win32 window

### Question 2 : Use the morphology algorithms to reserve the fingers

### Question 3 : Label the fingers with 4-connected neighbor
1. Label each finger with a BLUE bounding box in output image.
2. Compute the centroid and area of each finger, and print the data on output image or win32 window
### Question 4 : Analyze and print the computational time of your program
connected component, morphology, property analysis, drawing,etc.

### Bonus Question 1 : Report the following properties of each finger
the length and orientation of the longest axis

### Bonus Question 2 : Report the numbers indicated by each hand
### Discussion:
**(無使用opencv程式碼)**

我將它分為五大部份，第一部分為讀檔，第二部分為開設三維陣列，第三部分為將bmp值儲存至陣列裡，第四部份為運算(rotation、changecolor、bonus)，第五部份為寫入。

**一、 Connected components**

我使用的 connected components 是老師上課教學的第二種方法，也就是不斷的去掃描尋找關係，而我起初先開了一張圖片轉二值化之後先掃描一次，只要它的左邊上面沒有標籤那就把當作新如果面有標籤，就把覆蓋過去這樣掃完一遍之後我可以得到張擁不同標籤的圖片(圖一)。

![](https://i.imgur.com/wKNoTUt.png)(圖一)

之後我在用這張圖片來回掃描，往下的時候判斷左邊上面的時候判斷右邊下面，只要旁數值比它小就一直覆蓋過去到剩5個標籤為止(手臂五隻)，如圖二。

![](https://i.imgur.com/2cJrwob.png)(圖二)

這個方法完成之後，我就將它寫副函式樣子待會手指的型態學處理完畢之後，就能直接call了。
**二、 形態學**

**Erosion:** erosion方面我也是把它寫成副函式，輸入為多少乘的方面我也是把它寫成副函式，輸入為多少乘的 框，類似卷積的那樣寫法如果是 5 x 5 的， x,y 軸就是從 -2到 2，當然要給他限制範圍，不能小於 或大於邊界條件，那 erosion 我是按照老師上課說的 erosion 類似AND閘，每一格都要有數值中心點才能夠留下我寫了個 Count 在每次掃描下一個的 時候都會歸零，如果秒像素點沒有數值count就+1 ，如果有數值 count 不變，也就是說這 5 x 5 掃描完之後，如果都有數值的 化， count就是0，也就代表這個中心點是可以留下的，反之只要count不是 0，那這點就是不能留下的，樣完成了erosion (如圖三)。

![](https://i.imgur.com/qJ3GwPw.png)(圖三)
圖三中我是採用25 x 25的尺寸來做erosion

**Dilation:** dilation 方面我是直接把方面我是直接把erosion直接複製下來做修改， dilation是像OR閘，所以只要掃瞄25 x 25內的點有像素值就留下，如果都沒有才不用留下，我沿erosion的count一樣只要掃瞄的點有數值就+1，沒有數值就不動，只是在判斷式上做了一些改變要 count有數值就代表這個像速點可以留下，反之count是零就代表這個像速點不能留下，其結果如圖四。

![](https://i.imgur.com/JMFbk97.png)(圖四)

**三、 手指頭**

至於我怎麼把手指頭給單獨取出來得，先使用原圖二值化後的圖片，對他進行膨脹以及收縮並且mask的 大小選為比手指大一點mask，這樣膨脹收縮出來的結果就是沒有手指頭只掌心及臂圖片，接下來我就把原圖 (整隻手的 )減掉我處理出來的圖片，這樣就能得到只有手指頭的圖片了，接下來就是把只有丟入形態學處裡由於我形態學寫成了一個函式，所以直接 call 他就好了，結果如圖五。

![](https://i.imgur.com/ExkvT8r.png)(圖五)




**四、 畫圖**

畫圖我是把他寫在 connect components裡， 在connect components 中我已經將區域做分類，接下來只要找到每個中的最大以及最小的數值了，所以我寫兩個變分別是max和min在每一次的區塊中分類時，都去找這樣就知道個區塊的最大與小數值再拿畫圖 rect ，就可以畫出框手掌及指頭的圖片了(圖六)。

![](https://i.imgur.com/TJ7P7Hd.png)(圖六)


**五、 重心**

重心的部份我是將他每一個區塊座標總合除與面積，即可獲得他的重心。

![](https://i.imgur.com/6Udn03g.png) ![](https://i.imgur.com/Tv9h8zm.png)

**六、 時間**

使用time.h分別計算

![](https://i.imgur.com/7qxtLVw.png)

![](https://i.imgur.com/ro2egNV.png)

**使用opencv程式碼**

**一、 Connected components**

![](https://i.imgur.com/lc2dWDv.png)

使用opencv內建的函式，從左至右分別是，輸入圖標籤面積、重心。

**二、 Opening**

![](https://i.imgur.com/zFy5dV9.png)

使用opencv內建的函式，getStructuringElement( MORPH_RECT,SIZE )，MORPH_RECT為方形的意思，內建有十字型、橢圓等SIZE為Mask的size，morphologyEx為形態學，MORPH_OPEN意思為 Opening，可以修改為MORPH_CLOSEING_為Closing。

**三、 畫圖**

![](https://i.imgur.com/9HCmm7V.png)

使用opencv內建的函式，即可畫出圈手指頭及整隻臂並且使用circle函式畫出重心。

**四、 重心**

函式內建即可算出。

![](https://i.imgur.com/XjfXK23.png)

**Bonus**

**手指頭數量**

在形態學中，我將整隻手與指頭做分類時來計算整隻手臂裡，有幾隻手指頭的標記，這樣就能知道每總共有了。

![](https://i.imgur.com/gRfNZIM.png)

至於為什麼是42315這個順序呢?，由於整隻手臂在做標籤時，右上的第一隻手臂會先被標記起來，再是左上接下面的三中由於這支手指頭較長會在這三隻臂中先被標記，再來是左下及右所以順序才42315。

## :warning:嚴禁抄襲
這些只是提供我自己的想法而已，程式碼撰寫得也沒有到很嚴謹，禁止抄襲。

These are just to provide my own ideas, and the code is not written very rigorously. I hope that there will be no plagiarism.

## :smile: Owner
Made by https://github.com/WU-TING-HSUAN

## :+1: School
:point_right:National Taipei University of Technology	:point_left:
