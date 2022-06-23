#pragma once
#include "common.h"

//外部变量的引用方式  两个配套出现，（声明与声明）不能赋值	
//struct User
//{
//						//注意！！！有了这个引用，那么main.c里就不能同时包含有这结构体的两个.h了，详情看管理的第2次笔记
//	char name[15];		//简单解决方法：把类型放到common.h 公共头文件下 就完美解决所有问题了
//	char Key[20];
//};
extern struct User g_user;

//管理函数	（统筹函数）
void Manage(void);

//节点类
//学生信息节点
struct Message
{
	unsigned int iNumber;	//学号
	unsigned char cName[15];			//姓名
	unsigned int iSocre;				//成绩
};
//链表节点
struct Node
{
	struct Message stMe;	//学生信息
	unsigned int iCount;	//计数
	struct Node* pPre;		//前一节点地址
	struct Node* pNext;		//后一节点地址
};


//管理界面
void CountDown(short hang, short lie, int iTime, char Count);	//倒计时
void ManageMenuUI(void);	//管理界面的主菜单
void OrderFailUI(void);		//输入指令有误界面
void QuitSystemUI(void);	//退出系统界面

void AddStuUI(void);		//添加学生界面
void AddStuSucessUI(void);	//添加学生后，下方的成功提示
void AddStuFailUI(void);	//添加学生失败提示
bool Add(struct Node* stHead, struct Message* Me);	//学生链表添加节点（尾添加）
void ProduceNumber(struct Node* stHead);			//学生信息的学号生成机制
void Free(struct Node* stHead);						//释放链表

bool SaveInFile(struct Node* stHead);				//保存学生信息到文件中
void SaveInFileSucessUI(void);						//保存成功
void SaveInFileFailUI(void);						//保存失败
void ReadToFile(struct Node* stHead);				//从文件中读取数据,存到链表中

void LookAll(struct Node* stHead);					//查找所有的学生信息
void StuNameUI(void);								//查找名字界面
void LookOne(struct Node* stHead, struct Message* Me);//查找指定学生
void RangeUI(void);									//分数范围查找界面
void LookRange(struct Node* stHead, unsigned int iScore1, unsigned int iScore2);	//查找范围内分数的学生

void DeleteNameUI(void);	//删除指定学生界面
void DeleteSucessUI(void);	//成功提示	紧接上一个界面
void DeleteFailUI(void);		//失败提示
bool Delete(struct Node* stHead, struct Message* Me);//删除学生信息（节点）

void ChangeUI(void);								//修改界面
void ChangeSucessUI(void);							//成功提示
void ChangeFailUI(void);							//失败提示
bool Change(struct Node* stHead, struct Message* Me);

void Test(struct Node* stHead);						//进行考试
void TestSucessUI(void);							//成功提示

void SortOkUI(void);								//排序界面
void SortBySocre(struct Node* stHead);				//按成绩排序	 采用冒泡排序
void SortByNumber(struct Node* stHead);				//按学号排序


