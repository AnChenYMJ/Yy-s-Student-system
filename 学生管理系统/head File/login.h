#pragma once
				//VS编译器会自动加上此行  防止头文件重复包含 我们也可以自己手动加另一种，这种通用性差了一点
#include "common.h"



//登陆函数
bool Login(void);

//登陆界面
void LoginMenuUI(void);					//打印初始的主菜单
void CountDown(short hang, short lie, int iTime, char Count);		//倒计时封装函数  在下面的登录、注册中都有用到，故单独封装

void SaveUser(struct User* user);		//保存用户信息到文件中（用户名、密码）
bool IsRight(struct User* user);		//输入一个用户，查找后台是否有匹配的用户信息（用户名、密码）
bool IsUserExist(struct User* user);	//输入一个用户,查找后台是否有匹配的用户名（仅查用户名）

void LoginUI(void);						//登录界面，即主菜单的 1 选项
void LoginFailUI(void);					//登录失败 提示
void LoginSucessUI(void);				//登录成功 提示

void RegisterUI(void);					//注册界面，即主菜单的 1 选项
void RegisterFailUI(void);				//注册失败 提示
void RegisterSucessUI(void);			//注册成功 提示

void VIsitorLoginUI(void);				//游客登录界面
void QuitLoginUI(void);					//游客退出界面
void OrderWrongUI(void);				//指令输入有误界面
	