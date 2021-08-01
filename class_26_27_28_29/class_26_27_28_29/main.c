﻿#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>

////判断当前机器的字节序，即判断小端和大端①
//int check_sys()
//{
//	int a = 1;//字节是00 00 00 01，储存是01 00 00 00
//	char* p = (char*)&a;//只取一个字节，故强制类型转化为char	
//	if (*p == 1)
//		return 1;
//	else
//		return 0;
//}
//int main()
//{
//	int ret = check_sys();
//	if (ret == 1)
//	{
//		printf("小端\n");
//	}
//	else
//	{
//		printf("大端\n");
//	}
//	return 0;
//}



////判断当前机器的字节序，即判断小端和大端②高效版
//int check_sys()
//{
//	int a = 1;
//	return *(char*)&a;//上面版本的浓缩，结合上面理解
//}
//int main()
//{
//	int ret = check_sys();
//	if (ret == 1)
//	{
//		printf("小端\n");
//	}
//	else
//	{
//		printf("大端\n");
//	}
//	return 0;
//}



////char a = -1;	signed char b = -1;	unsigned char c = -1;
//int main()
//{
//	char a = -1;
//	signed char b = -1;
//	unsigned char c = -1;
//	printf("%d %d %d\n", a, b, c);//-1,-1,255,
//	//都先取出 - 1的首字节补码存储，即11111111
//	//但是拿出来的定义标准不一样，
//	//①前2者是发生整型提升，再还原回原码，
//	//即11111111->11111111111111111111111111111111
//	//提升的数是符号位1，原码仍然是 - 1
//	//②第3者是无符号数，无符号位的话，整型提升补的是0，
//	//即11111111->00000000000000000000000011111111，
//	//（正数 / 无符号数）原反补相同即100000000 - 1得256 - 1得255
//	return 0;
//}



////char a = -128		printf("%u\n",a);
//int main()
//{
//	char a = -128;
//	printf("%u\n", a);
//	//-128是
//	//10000000 00000000 00000000 10000000
//	//反码
//	//11111111 11111111 11111111 01111111
//	//补码
//	//11111111 11111111 11111111 10000000
//
//	//取char，一个字节
//	//10000000
//	//打印需要整型提升，因为定义时char是signed类型，所以按符号位提升
//	//11111111 11111111 11111111 10000000提升符号位，也即0
//	//打印是无符号类型，所以原反补相同，直接打印上数
//	return 0;
//}



////char 128相当于char 127+1，实际上signed char 127+1就是-128
//int main()
//{
//	char a = -128;
//	char b = 128;
//	printf("%u\n%u\n", a, b);//结果相同
//	return 0;
//}



////	int i = -20;  unsigned int j = 10; 	printf("%d\n", i + j);
//int main()
//{
//	int i = -20;
//	unsigned int j = 10;
//	printf("%d\n", i + j);//-10
//	//i
//	//10000000 00000000 00000000 00010100 源码
//	//11111111 11111111 11111111 11101011 反码
//	//11111111 11111111 11111111 11101100 补码
//	//j
//	//00000000 00000000 00000000 00001010 原反补相同
//	//i+j 用补码计算
//	//11111111 11111111 11111111 11110110
//	//%d用原码打印
//	//11111111 11111111 11111111 11110101 反码
//	//10000000 00000000 00000000 00001010 原码
//	//原码打印结果 -10
//	return 0;
//}



////unsigned int i;  for (i = 9; i >= 0; i--)  printf("%u\n", i);
//int main()//似乎无法执行
//{
//	unsigned int i;
//	for(i = 9; i >= 0; i--)//无符号数恒>=0死循环
//	{
//		printf("%u\n", i);//先打完9~0，之后打印超大数
//		//因为0-1=-1补码存储全为4个11111111，是4294967295,之后一直减小
//		Sleep(100);//每次打印后停100ms即0.1秒，方便观察，头文件#include<windows.h>
//	}
//	return 0;
//}



////char a[1000];  for (i = 0; i < 1000; i++)  a[i] = -1 - i;
//int main()
//{
//	char a[1000];//char范围-128~127
//	int i = 0;
//	for (i = 0; i < 1000; i++)//char (-128-1) == char 127
//	{
//		a[i] = -1 - i;
//	}//实际上遍历了char取值范围，除了0用作结束，剩下就是255个数
//	printf("%d\n", strlen(a));
////a[0]=-1
////a[1]=-2
////a[2]=-3
////……
////a[127]=-128
////a[128]=127
////a[129]=126
////a[130]=125
////……
////a[254]=1
////a[255]=0='\0'
////strlen到'\0'停止，就有共255的长度
//	return 0;
//}



////unsigned char i = 0;  for (i = 0; i <= 255; i++)
////死循环，实际上报错了
//int main()
//{
//	unsigned char i = 0;
//	for (i = 0; i <= 255; i++)
//	{//255+1之后回到0，继续循环
//		printf("test\n");
//	}
//	return 0;
//}



//float例题
//int main()
//{
//	int n = 9;
//	float* p = (float*)&n;
//	printf("n的值为：%d\n", n);//9
//	printf("*p的值为：%f\n", *p);//0.000000
//	*p = 9.0;
//	printf("n的值为：%d\n", n);//1091567616
//	printf("*p的值为：%f\n", *p);//9.000000
//	//①整型存储，整型取出，还是9
//	//②
//	return 0;
//}



////举例详解float 5.5的储存法
//int main()
//{
//	float  f = 5.5;
////5.5的二进制是101.1
////注意整数部分正常二进制，小数部分0.1就是二分之一
////得到float标准格式：
////(-1)^0 * 1.011*2^2
////得到关键数据SEM：
////S=0  E=2  M=1.011
////相当于 0 2+127 2
////即 0 10000001 011
////二进制实际存储（注意后面用0补齐23bit）
////0100 0000 1011 0000 0000 0000 0000 0000
////十六进制查看
////0x40b00000
//	return 0;
//}