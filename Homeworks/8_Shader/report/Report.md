

# 着色器实验报告
###### PB17010383 肖海尧

本次实验要求熟悉着色器的原理并完成法线贴图以及置换贴图的基本功能，在此基础上对3D模型进行简单去噪

## 1. 实验原理

#### 1.1 法线贴图

法线贴图在渲染中用于改变原法向，从而影响着色效果。根据法线贴图，计算法线以及切线，传入顶点着色器中计算TBN矩阵，这个矩阵可以把切线坐标空间的向量转换到世界坐标空间。因此我们把它传给片段着色器中，把通过采样得到的法线坐标左乘上TBN矩阵，转换到世界坐标空间中，这样所有法线和其他光照变量就在同一个坐标系中了。在实际使用中，为优化性能，在计算TBN矩阵时，进行Gram-Schmidt正交化，保证向量间的垂直并传入片段着色器中进行计算。



#### 1.2 置换贴图

置换贴图用于改变顶点的位置，0 （黑色）表示不动，1（白色）表示沿着法向偏移。实验中取采样处的红色通道值pixel value，计算displacement = lambda * (bias + scale * pixel value)，并对顶点做偏移coefficient * displacement * Normal，实际计算中取bias为0，scale为1



#### 1.3运用置换贴图简单去噪

对3D模型加入随机噪声后，由于法线未发生改变，只要对顶点进行偏移就可达到一定的去噪效果

步骤如下：

- 计算每个顶点的偏移量

$$
\delta_i=p_i-\frac{1}{|N(i)|}\sum_{j\in N(i)}p_j
$$

- 将偏移量投影到法向上

$$
\bar{\delta}_i=\langle\delta_i,\pmb{n}_i\rangle \pmb{n}_i
$$

- 对每一个顶点进行偏移

$$
\bar{p}_i=p_i-\lambda \bar{\delta}_i=p_i-\lambda\langle\delta_i,\pmb{n}_i\rangle \pmb{n}_i
$$

在具体计算中，先计算出每点的$\langle\delta_i,\pmb{n}_i\rangle$ ，找出其中的最大\最小值min\max，做变换$\frac{\langle\delta_i,\pmb{n}_i\rangle-min}{max-min}$使得值取到0和1之间， 并作为Map红色通道值传入顶点着色器中进行计算，为此定义bias=min，scale=max-min，lambda=1.0f，同时对纹理图其他点处找最近邻点进行赋值



## 2. 程序说明

对于去噪程序，为方便观察重新设置按键，按下Z表示还原噪声，按下X表示消除噪声

因为算法原因，去噪需要运行30s左右才会出结果，之后按下Z，X进行变换不会有延迟



## 3.结果展示

#### 3.1 置换贴图以及法线贴图

<center>
	<img src="./1.1.png" title="display"  width=40%>
    <img src="./1.2.png" title="display"  width=40%>
</center>





#### 3.2简单去噪

保留噪声时模型如下

<center>
	<img src="./2.1.png" title="display"  width=60%>
</center>

置换后效果为

<center>
	<img src="./2.2.png" title="display"  width=60%>
</center>

<center>
	<img src="./2.3.png" title="display"  width=60%>
</center>



## 4. 不足

1.去噪时对map上所有点寻找最近点进行赋值，寻找最近邻点时没有调库，采取的算法比较暴力，所以运行效率较低

2.模型在去噪后存在空洞，实验中未能完成补洞操作