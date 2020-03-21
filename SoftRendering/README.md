#### 光栅化理解

Bresenham直线算法、重心坐标插值算法
##### 3条直线隐函数
![image-20191205175632577](https://user-images.githubusercontent.com/37433487/77224972-aa59a900-6ba5-11ea-8b1e-74e0e15dc84d.png)

1. 这里我使用Bresenham直线算法

  * 通过确定两点画直线的方式填充三角形

1. 对color、normal、worldpos进行加权，*w表示透视距离比例

#### phong光照模型


#### blinn-phong光照模型

镜面反射分量+散射分量+环境分量

#### 投影变换

摄像机会看着处于3D世界的3D物体，它最终的投影会以2D形式呈现在你的屏幕上。

back buffer（离屏  front buffer 正在画的帧

首先我们需要定义一些摄像机和图形需要的细节参数

摄像机有2个属性：3D世界坐标和 where it’s looking at, the target

Mesh需要一连串的顶点用来建立3D对象，属性：3D世界位置和旋转状态

Device组件，3D引擎的核心，通过它的渲染方法，我们将基于前面设定好的摄像机建立起view矩阵和projection矩阵

```
Matrix wvp = worldMatrix * viewMatrix * projectionMatrix
```

刷新过程：

1. 清屏
2. 更新meshes
3. back buffer渲染
4. 呈现 swap back buffer 和front buffer

两点画线：

1. 如果2个点间隔像素小于2，return
2. 否则取中点，drawpoint
3. 区域划分point0，middlepoint and middlepoint， point1 递归画点

3D里面使用三角形组合成所有的网格

Rasterization & Zbuffer（光栅化和深度缓冲

Boustrophedon 牛耕式转行书写法，牛耕式是一起连着书写，即若第一行是由左到右书写，第二行则由右至左书写，下一行又是由左至右。

光栅化：将3个顶点根据y轴排序	P1.Y-P2.Y drawLine	P2.Y-P3.Y drawLine

深度缓冲：

如果目前pixel的z值小于原来的，那么就表示现在画的，在以前画的点的前面，直接覆盖，

如果z值大于原来的，则表示画的点在以前的后面，我们就放弃操作

我们要始终保持在屏幕上的像素点的z值索引的历史记录，所以我们要建立一个数组来存储着个数据，这个数组的大小和屏幕上所有的像素点数量有关，（width * height )

#### compute the FPS

我们需要知道渲染帧间隔

平面渲染和顶点渲染

flat shading： color = color * Math.Max(0, cos(angle))

纹理设计

```C#
public class Texture
{
	private byte[] internalBuffer;
	private int width;
	private int height;
	
	public Texture(string filename, int width, int height)
    {
    	this.width = width;
    	this.height = height;
    	Load(filename);
    }
    
    async void Load(string filename)
    {
    	var file = await Windows.ApplicationModel.Package.Current
    	.InstalledLocation.GetFileAsync(filename);
    	
    	using (var steam = await file.OpenReadAsync())
    	{
    		var bmp = new WriteableBitmap(width, height);
    		bmp.SetSource(stream);
    		
    		internalBuffer = bmp.PixelBuffer.ToArray();
    	}
    }
    
    public Color4 Map(float tu, float tv)
    {
    	if(internalBuffer == null)
    	{
    		return Color4.White;
    	}
    	
    	int u = Math.Abs(int) (tu * width) % width);
    	int v = Math.Abs(int) (tv * height) % height);
    	
    	int pos = (u + v * width) * 4;
    	byte b = internalBuffer[pos];
    	byte g = internalBuffer[pos + 1];
    	byte r = internalBuffer[pos + 2];
    	byte a = internalBuffer[pos + 3];
    	
    	return new Color4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }
}
```

#### windows.h

[BitBlt function]: https://docs.microsoft.com/zh-cn/windows/win32/api/wingdi/nf-wingdi-bitblt

The **BitBlt** function performs a bit-block transfer of the color data corresponding to a rectangle of pixels from the specified source device context into a destination device context.

```C++
BOOL BitBlt(
  HDC   hdc,
  int   x,
  int   y,
  int   cx,
  int   cy,
  HDC   hdcSrc,
  int   x1,
  int   y1,
  DWORD rop
);
```

[AdjustWindowRect function]: https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-adjustwindowrect

Calculates the required size of the window rectangle, based on the desired client-rectangle size. The window rectangle can then be passed to the [CreateWindow](https://docs.microsoft.com/windows/desktop/api/winuser/nf-winuser-createwindowa) function to create a window whose client area is the desired size.

To specify an extended window style, use the [AdjustWindowRectEx](https://docs.microsoft.com/windows/desktop/api/winuser/nf-winuser-adjustwindowrectex) function.

```C++
BOOL AdjustWindowRect(
  LPRECT lpRect,
  DWORD  dwStyle,
  BOOL   bMenu
);
```

[SetWindowPos]: https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-setwindowpos

Changes the size, position, and Z order of a child, pop-up, or top-level window. These windows are ordered according to their appearance on the screen. The topmost window receives the highest rank and is the first window in the Z order.

```C++
BOOL SetWindowPos(
  HWND hWnd,
  HWND hWndInsertAfter,
  int  X,
  int  Y,
  int  cx,
  int  cy,
  UINT uFlags
);
```

[ShowWindow]: https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-showwindow

Sets the specified window's show state.

[GetSystemMetrics]: https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getsystemmetrics

Retrieves the specified system metric or system configuration setting.

Note that all dimensions retrieved by **GetSystemMetrics** are in pixels.

[CreateDIBSection]: https://docs.microsoft.com/zh-cn/windows/win32/api/wingdi/nf-wingdi-createdibsection

The **CreateDIBSection** function creates a DIB that applications can write to directly. The function gives you a pointer to the location of the bitmap bit values. You can supply a handle to a file-mapping object that the function will use to create the bitmap, or you can let the system allocate the memory for the bitmap.

```C++
HBITMAP CreateDIBSection(
  HDC              hdc,
  const BITMAPINFO *pbmi,
  UINT             usage,
  VOID             **ppvBits,
  HANDLE           hSection,
  DWORD            offset
);
```

[CreateCompatibleDC]: https://docs.microsoft.com/zh-cn/windows/win32/api/wingdi/nf-wingdi-createcompatibledc

The **CreateCompatibleDC** function creates a memory device context (DC) compatible with the specified device.

```C++
HDC CreateCompatibleDC(
  HDC hdc
);
```

[SelectObject]: https://docs.microsoft.com/zh-cn/windows/win32/api/wingdi/nf-wingdi-selectobject

The **SelectObject** function selects an object into the specified device context (DC). The new object replaces the previous object of the same type.

![image-20191214153709900](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20191214153709900.png)

#### D3DXMatrixLookatLH

#### 软渲染过程

1. 建立framebuffer[y\][x]数组，分别使用屏幕最大高度和宽度作为索引值初始化数组，每一个索引位置的值代表屏幕上该像素点的颜色;

![image-20191220103730893](https://user-images.githubusercontent.com/37433487/77224614-73ce5f00-6ba2-11ea-82a8-71e4ce74407e.png)

2. 一条线根据起始点start和终止点end的位置确定，线上每一个点point都可以根据point到start距离和start到end距离的比值，获得point坐标，同理颜色也通过线性比值获得，所以输入2个点就能够得到如下图一条2D线：

![image-20191220105307024](https://user-images.githubusercontent.com/37433487/77224617-75982280-6ba2-11ea-9832-525cecef95f6.png)

3. 相对于2D直线，3D直线就是将世界坐标转换成屏幕上的2D坐标，再连成线的过程。3D世界坐标到屏幕坐标的过程：

   wvpMatrix = worldMatrix * viewMatrix * projectionMatrix；顶点世界坐标通过wvp变换得到一个全新的向量( x'w, y'w, z'w, w )

   * worldMatrix代表世界，默认是单位矩阵，可以通过平移旋转，来改变世界的位置

   * viewMatrix代表着摄像机视角，通过摄像机的位置eye，看向的目标target，摄像机的垂直方向up，在这里我建立了一个左手坐标系，确定摄像机坐标系的z轴为目标指向摄像机，通过垂直方向up与z轴叉乘得到法向量为x轴，z轴与x轴叉乘的法向量为y轴，组成一个4X4齐次旋转矩阵，然后摄像机位于eye，所以需要再平移到eye位置处，也就是-eye的4X4平移矩阵

   * projectionMatrix代表透视变换，透视变换是类似于金字塔形的变换方式，区别于正交变换直接将3D图形拍扁成2D，透视变换是一个相似三角形大变小的过程，根据相似三角形得到新的坐标，运用正交变换的裁剪方式：
  ![image-4](https://user-images.githubusercontent.com/37433487/77225322-fb1ed100-6ba8-11ea-8f49-27639aa7c1af.png)
     通过已知点（n, 0 ) 、( f, 1 )求得：
       ![image-5](https://user-images.githubusercontent.com/37433487/77225330-08d45680-6ba9-11ea-8118-3f03f8b179c6.png)
     令裁剪矩形对称即r= -l, t = -b得到透视变换矩阵：
       ![image-5](https://user-images.githubusercontent.com/37433487/77225332-0c67dd80-6ba9-11ea-9f81-73bcbe2acd65.png)
     由垂直可视范围角度a得$cot\frac{a}{2}=\frac{2n}{h}$
       ![image-5](https://user-images.githubusercontent.com/37433487/77225345-23a6cb00-6ba9-11ea-9887-5b70494bbfc5.png)
     得到新向量( x'w, y'w, z'w, w )，通过透视除法得到wvp变换后的新坐标，将该坐标按照左手坐标系屏幕width、height比例放大到屏幕上，就完成了整个3D转2D过程，下图是一条3D直线：

![image-2011](https://user-images.githubusercontent.com/37433487/77224622-7df05d80-6ba2-11ea-8caa-7e4e1735f4b2.png)

5. 光栅化三角形填充，首先将三角形的三个顶点通过wvp和世界坐标转屏幕坐标过程后，将三个顶点按照p1.Y <= P2.Y <= P3.Y进行排序，以y = p2.Y作为分界线，将三角形分为两个三角形分别进行处理。根据Y的变化，找到点在p1p2、p1p3、p2p3线上y梯度变化，例如y=p2.Y上方三角形，这里假设p2.x < p3.x即p2在p3的左边，根据p1p2的梯度求得直线起点，p1p3的梯度求得直线的终点，这两个点的y值相同，连接2个点画直线，同理整个三角形的绘制，就是不断梯度下降找到新的起始点和终点画线的过程，得到如下图效果：

   ![image-20191220142340216](https://user-images.githubusercontent.com/37433487/77224623-7e88f400-6ba2-11ea-8f41-e62b02fcf773.png)

这里y梯度也就是，点到起始点的距离与整条线长度的比值。

6. 漫反射光分量diffuse = lightColor * saturate( n * l )

   * lightColor:光的颜色，白色( 1, 1, 1 )
   * l:光线的反方向
   * n:顶点的法向量

7. phong光照模型，镜面反射光分量： 

![image-20191220142340216](https://user-images.githubusercontent.com/37433487/77225427-e4c54500-6ba9-11ea-8574-6766a1b42f38.PNG)

#### 封装Camera类

在上述光栅化和各种画点、线、三角形过程中，我使用的都是D3DXMatrixLookAtLH函数，也就是左手坐标系建立摄像机坐标系，由eye、target、up这3个参数构成：

* eye：摄像机位置
* target：看向的目标
* up：摄像机的垂直方向

坐标系由x、y、z三个轴构成，这里我把向量( target - eye )作为z轴，也就是look轴，接下来通过叉乘获得法向量得到另外2个轴，建立起坐标系。通过这种方式建立的坐标系移动起来很不方便，主要表现在，移动eye位置，z轴并不是平行移动的，而是呈现一个角度旋转，非常不符合一般FPS理解，所以我重新对摄像机坐标系进行定义。

摄像机坐标系包括4个参数：

* position：摄像机的位置
* look：摄像机看向的方向，在这里也就是z轴
* up：摄像机垂直方向，也就是y轴
* right：摄像机左右方向，也就是x轴

这里的向量都是单位向量，我们可以通过给position向量加上一个平移向量，达到运动效果：

```c++
position = position + translateVector;
```

只要传入一个位移向量，就能够实现WASDJK控制摄像机的前后左右上下移动，也就完成了camera类walk功能。

这里的walk方法只会改变position的值，并不会改变look、up、right，人头固定死，脚会四处走，这显然还没有达到要求，接下来我就要让头动起来：

```c++
yaw( Vector rotateAxis, float theta )	// 偏航 绕up轴旋转 左右转头
```

左右摆头的过程就是 y轴不变，x轴和z轴绕y轴旋转一定角度，所以我们需要2个参数，旋转所绕的轴和旋转角度，注意在这个过程中position是不变的。

```c++
pitch( Vector rotateAxis, float theta )	// 倾斜 绕right轴旋转 抬头/低头
roll( Vector rotateAxis, float theta )	// 滚转	绕look轴旋转 侧头
```

```C++
position = position + x * right + y * up + z * look;
```

这里的x, y, z代表着摄像机坐标系三个轴的分量，控制x, y, z变化就是在这三个方向移动，实现了第一人称视角。

世界、视角、投影矩阵资料

[World, View and Projection Matrix Unveiled](http://web.archive.org/web/20131222170415/http:/robertokoci.com/world-view-projection-matrix-unveiled/)

[Tutorial 3 : Matrices](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/)

 [Cameras on OpenGL ES 2.x – The ModelViewProjection Matrix](http://db-in.com/blog/2011/04/cameras-on-opengl-es-2-x/)

[Transforms (Direct3D 9)](http://msdn.microsoft.com/en-us/library/windows/desktop/bb206269(v=vs.85).aspx)

[A brief introduction to 3D](http://inear.se/talk/a_brief_introduction_to_3d.pptx)

[OpenGL Transformation](http://www.songho.ca/opengl/gl_transform.html)
