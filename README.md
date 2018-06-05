## 介绍/Introduction
**用途**：此程序为《计算机图形学》课程设计，作用和画图类似。  
  
**代码框架**：代码主要分为MainWindow和OpenGLWindow两个大类，前者是UI界面及交互相关，后者为画板图形处理相关。

**开发工具**：Qt5，OpenGL-glut

**界面**：  
![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image001.png)  
## 操作/Operation
#### 一、图形数据的输入和编辑功能
**画点**  
用户可以通过“插入-画点”或者工具栏的![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image003.gif)按钮进入画点模式左键按下即可画点，按下不松开并以中到慢的速度拖动可以画出自由曲线，效果如图所示。  
![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image004.png)
 
**画线**  
用户可以通过“插入-直线”或者工具栏的按钮![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image006.gif)进入画线模式，左键第一次按下即为开始点，第二次按下即为结束点，如果第二次不松开并拖动可以修改结束点的位置为当前鼠标位置。松开后，依然可以通过按下右键并拖动鼠标修改结束点的位置。效果如图所示。  
![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image007.png)
  
**画曲线**  
用户可以通过“插入-曲线”或者工具栏的按钮![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image009.gif)进入画曲线模式，单击四次即为选择了四个点，选择了四个点后自动画曲线。如果第四次不松开并拖动可以修改最后一个点的位置为当前鼠标位置。松开后，依然可以通过按下右键并拖动鼠标修改最后一个点的位置。效果如图所示。  
![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image010.png)
  
**画矩形/填充矩形**  
用户可以通过“插入-矩形/填充矩形”或者工具栏的![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image012.gif)或![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image013.gif)按钮进入画矩形或填充矩形模式，左键第一次按下即为对角线起点，第二次按下即为终点。如果第二次不松开并拖动可以修改终点的位置为当前鼠标位置。松开后，依然可以通过按下右键并拖动鼠标修改终点的位置。效果如下图所示。  
![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image014.png)
  
**画多边形/填充多边形**  
用户可以通过“插入-多边形/填充多边形”或者工具栏的![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image016.gif)或![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image017.gif)按钮进入画多边形或填充多边形模式，单击即为选定一个顶点，直到按下右键为止并至少有三个顶点将开始画多边形。若按住右键不松，则可以修改最后一个顶点的位置为当前鼠标位置，并重新绘制。效果如图所示。  
![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image018.png)
  
**画椭圆**  
用户可以通过“插入-椭圆”或者工具栏的按钮![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image020.gif)进入画椭圆模式，左键第一次按下即为椭圆心，第二次按下即为长轴的一个端点，第三次按下即为短轴的一个端点，如果第三次不松开并拖动可以修改短轴上的点的位置为当前鼠标位置。松开后，依然可以通过按下右键并拖动鼠标修改短轴上的点的位置。效果如图所示。  
![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image021.png)
 
**画圆**  
用户可以通过“插入-圆形”或者工具栏的按钮![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image023.gif)进入画圆模式，左键第一次按下即为圆心，第二次按下即为圆周上的点，如果第二次不松开并拖动可以修改圆周上的点的位置为当前鼠标位置。松开后，依然可以通过按下右键并拖动鼠标修改圆周上的点的位置。效果如图所示。  
![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image024.png)
 
**改变画笔颜色**  
用户可以通过工具栏的按钮![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image026.gif)来选择画笔颜色，将会弹出一个选择颜色对话框，效果如图所示。  
![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image027.png)
![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image029.png)
  
**改变画笔粗细**  
用户可以通过工具栏的下拉选单![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image031.png)选择画笔粗细（单位：像素），效果如图所示。  
![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image033.png)
  
#### 二、图形数据的选择和裁剪功能  
**选取图元**  
用户可以通过“选择-选择”或者工具栏的![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image035.gif)按钮，然后左键点击需要选择的图元的轮廓来选择一个同时画好的基本图元，从直线和曲线中选择曲线前后变化如图所示（被选择区域标记为黑色）。  
选择前：![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image036.png)  
选择直线：![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image038.png)  
选择曲线：  ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image040.png) 

**选取矩形区域**  
用户可以通过“选择-矩形区域”或者工具栏的![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image042.gif)按钮，然后鼠标左键单击选择矩形对角线的两个点来选择矩形区域，从填充多边形中选择矩形区域如图所示（被选择区域标记为黑色）。  
选择前：![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image043.png)  
选择后： ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image045.png)  

**选取多边形区域**  
用户可以通过“选择-多边形区域”或者工具栏的![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image047.gif)按钮，然后鼠标左键单击选择多边形的顶点（最后一个点右键单击选择）来选择多边形区域，从填充矩形中选择一块不规则的多边形区域如图所示（被选择区域标记为黑色）。  
选择前：![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image048.png)  
选择后： ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image050.png)  

**反选**  
用户可以通过“选择-反选”来反选选区，或者通过工具栏的![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image052.png)按钮进行反选操作，反选前后的效果如图所示。（被选择区域标记为黑色）  
反选前：![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image054.png)  
反选后： ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image056.png)   

**取消选择**  
用户可以通过在画板中按下“中键”来取消选择，按下中键前后效果如图所示。  
按下前（被选中）：![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image058.png)  
按下后（取消选中）：![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image060.png)  


**裁剪**  
选择一块区域后，若需要裁剪，可以通过4.4所示“删除区域”方法删除选中的选区，以达到裁剪的目的，在填充多边形中裁剪一块三角形区域如图所示。  
裁剪前：![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image062.png)  
选择后：![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image064.png)  
裁剪后: ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image066.png)  

#### 三、图形数据的变换功能
**移动区域**  
用户可以通过“选择-移动”或者工具栏的![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image068.gif)按钮，然后鼠标拖动来进行移动操作，即可将之前被选择的区域按照鼠标拖动的距离进行移动，移动前后的效果如下图所示（三角形作为参照）。  
拖动前: ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image069.png)  
拖动时: ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image071.png)  
拖动后:  ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image073.png)  


**旋转区域**  
用户可以通过“选择-旋转”或者工具栏的![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image075.gif)按钮来进行旋转操作，然后会弹出一个对话框，输入旋转角度（-180~180度）后即可将之前被选择的区域按照输入的角度进行旋转，旋转前后的效果如下图所示。  
旋转前： ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image076.png)  
旋转-45°后： ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image078.png)  
再次旋转135°后：![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image080.png)  


**缩放区域**  
用户可以通过“选择-缩放”或者工具栏的![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image082.gif)按钮来进行缩放操作，然后会弹出一个对话框，输入缩放比例后即可将之前被选择的区域按照输入的比例进行缩放，缩放前后的效果如下图所示。  
缩放前：![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image083.png)  
缩放50%后： ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image085.png)   
缩放200%后： ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image087.png)  

**删除区域**  
用户可以通过“选择-删除”或者工具栏的![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image089.gif)按钮来进行删除操作，此操作将删除之前被选择的区域，删除前后的效果如前面的裁剪所示。  

#### 四、图形数据的显示功能
用户可以通过“在一开始的对话框中选择3D模式”进入此功能。本功能主要体现在3维6面体的显示和变换上。
显示出来的效果如图所示。  
 ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image090.png)   
 
通过拖动鼠标可以旋转立方体，通过Ctrl+Z快捷键或者![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image092.gif)按钮进行放大，通过Ctrl+X快捷键或者![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image093.gif)按钮进行缩小操作。旋转和缩放效果如图所示。  
 ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image094.png)  
 
#### 五、图形数据与文件的交互
**打开bmp文件**  
程序目前只支持打开bmp格式的文件，其他格式文件请转码成bmp再打开。默认的尺寸为600*400(像素)，如果超过了这个尺寸，可能会导致裁剪；如果小于此尺寸，可能会导致读取异常。
工具栏选择“文件-打开”后，会弹出选择文件对话框:  
 ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image096.png)   

选择要打开的文件后，点击“打开”，效果如图：  
 ![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image098.png)   

**保存为bmp文件**  
程序目前只支持保存为bmp文件，尺寸为600*400(像素)。工具栏选择“文件-保存”后，会弹出保存文件对话框:  
![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image100.png)   

选择“保存”后，文件将保存在所选路径下。  


#### 六、其他提供的交互
**新建画布**  
如果希望新建一块全新的画布，可以选择“文件-新建”，随后会弹出确认框询问是否保存:  
![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image102.png)  
 
Fig.25 新建画布对话框演示图
2D模式下，选择保存：请查看6.2小节，然后清空全部内容。
2D模式下，选择不保存：清空全部内容。
3D模式下，选择保存：请查看6.2小节，然后重置3维6面体。
3D模式下，选择不保存：重置3维6面体。
选择取消或关闭对话框：画布上的内容依然保存，可以继续编辑。

**撤销操作**  
如果不满意刚才所做的改变，可以选择“编辑-撤销”或者选择工具栏的![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image104.gif)图标进行撤销操作。

**恢复操作**  
如果希望恢复刚才撤销的操作，可以选择“编辑-恢复”或者选择工具栏的![image](https://github.com/triumphalLiu/DrawingBoard/blob/master/ScreenShot/image105.gif)图标进行恢复操作。

**查看源代码**  
如果希望查看本程序在github的源代码，可以通过“开发者工具-查看源代码”打开网页，此操作会打开默认的浏览器。

#### 七、快捷键
**2D模式下：**  
Ctrl+A：保存到文件操作；  
Ctrl+O：打开文件操作；  
Ctrl+W：新建画布操作；  
Ctrl+Z：撤销操作；  
Ctrl+Y：恢复操作；   
Ctrl+1 to 9分别对应：画点、画线、画曲线、画填充矩形、画矩形、画填充多边形、画多边形、画椭圆、画圆；  
Alt+1 to 9分别对应：选取矩形区域、选取多边形区域、反选、选择图元、移动选区、旋转选区、缩放选区、删除选区、选择画笔颜色。  

**3D模式下**  
Ctrl+A：保存到文件操作；  
Ctrl+W：重置3D图形操作；  
Ctrl+Z：放大操作；  
Ctrl+X：缩小操作；  
