#pragma once

//公共头文件，即各个文件都要用到的头文件，放到此处，其他文件调用它即可

#include <stdio.h>
#include <stdlib.h>
#include <string.h>			//strcmp 字符集比较函数 要用
#include <stdbool.h>
#include <windows.h>		//设置光标位置要用到	
#include <time.h>			// 随机数种子要用

void GoToXY(short sHang, short sLie);	//设置控制台光标位置
//用户信息结构体声明		(每个文件都能存在一个同名的结构体声明，作用域就是它所在的文件，同个文件下不能有两个结构体声明)
struct User
{
	char name[15];			//数组具体大小可自定义宏来操控
	char Key[20];
};



