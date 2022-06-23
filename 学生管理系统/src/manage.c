#pragma once
#include "manage.h"

void Manage(void)
{
	ManageMenuUI();		//打印主菜单
	srand(time(NULL));	//随机数种子

	struct Node stHead;	//空头 及其初始化			注意这是局部变量，程序结束会自动释放，不需要我们手动释放
	stHead.stMe.iNumber = 3178902200;
	stHead.stMe.iSocre = 0;
	stHead.iCount = 0;	//忘记了字符数组怎么赋值了
	stHead.pPre = &stHead;
	stHead.pNext = &stHead;

	struct Message ME;	//用于输入的临时存储


	ReadToFile(&stHead);	//测试成功，成功读取 就不用每次都手动输入了

	while (1)
	{
		int iOrder = -1;
		scanf_s("%d", &iOrder);
		switch (iOrder)
		{
		case 0:			//退出系统	
			QuitSystemUI();
			Free(&stHead);									//退出循环前释放链表
			return;
			break;

		case 1:			//添加学生
			AddStuUI();
			scanf_s("%s", ME.cName, 15);					//输入姓名
			GoToXY(20, 64);
			scanf_s("%d", &ME.iSocre);						//输入成绩
			if (true == Add(&stHead, &ME))
			{
				ProduceNumber(&stHead);						//生成学号
				AddStuSucessUI();
			}
			else
				AddStuFailUI();
			break;

		case 2:			//保存数据进文件
			if (true == SaveInFile(&stHead))
				SaveInFileSucessUI();
			else
				SaveInFileFailUI();
			break;

		case 3:			//查找指定姓名的学生
			StuNameUI();
			scanf_s("%s", ME.cName, 15);	//ME 是上面定义的临时存储用结构体
			LookOne(&stHead, &ME);
			break;

		case 4:			//查询所有学生的信息
			LookAll(&stHead);
			break;

		case 5:
			ChangeUI();
			scanf_s("%s", ME.cName, 15);
			GoToXY(20, 64);
			scanf_s("%u", &ME.iSocre);
			if (true == Change(&stHead, &ME))
				ChangeSucessUI();
			else
				ChangeFailUI();
			break;

		case 6:
			DeleteNameUI();
			scanf_s("%s", ME.cName, 15);
			if (true == Delete(&stHead, &ME))
				DeleteSucessUI();
			else
				DeleteFailUI();
			break;

		case 7:
			Test(&stHead);
			TestSucessUI();
			break;

		case 8:
			SortBySocre(&stHead);
			SortOkUI();
			LookAll(&stHead);
			break;

		case 9:
			RangeUI();
			unsigned int a, b;
			scanf_s("%u %u", &a, &b);
			LookRange(&stHead, a, b);
			break;

		default:											//输入指令有误
		{
			char c = 0 ;									// switch中不能直接声明定义，但加上{}就可以了
			while ('\n' != (c = getchar()) && EOF != c);	// 清空缓冲区，避免字符型输入导致卡住
			OrderFailUI();
		}
		}
	}
	Free(&stHead);		//释放，其实这里多余了，循环中return前加的 Free 才是有效的
}

void ManageMenuUI(void)
{
	system("cls");					//加上这个逻辑上会更严密
	GoToXY(0, 0);
	printf("\n\n");
	printf("\t\t\t\t\t*******************************************\n");
	printf("\t\t\t\t\t※         欢 迎 使 用 本 系 统          ※\n");
	printf("\t\t\t\t\t※             操作员：                  ※\n");
	GoToXY(4, 65);					//光标转到 操作员： 后
	printf("%s", g_user.name);		//因为登录的那套逻辑中，不论是注册、登录、游客，都是用g_user这个全局变量来操作的，那此他就代表着用户的信息
	GoToXY(5, 0);					//光标回到正常继续打印剩余界面
	printf("\t\t\t\t\t※             (指令集如下)              ※\n");
	printf("\t\t\t\t\t※          0.退出系统                   ※\n");
	printf("\t\t\t\t\t※          1.添加一名学生               ※\n");
	printf("\t\t\t\t\t※          2.保存数据进文件             ※\n");
	printf("\t\t\t\t\t※          3.显示指定学生信息           ※\n");
	printf("\t\t\t\t\t※          4.显示所有学生信息           ※\n");
	printf("\t\t\t\t\t※          5.修改指定学生信息           ※\n");
	printf("\t\t\t\t\t※          6.删除指定学生信息           ※\n");
	printf("\t\t\t\t\t※          7.考试                       ※\n");
	printf("\t\t\t\t\t※          8.根据成绩顺序查看           ※\n");
	printf("\t\t\t\t\t※          9.统计(显示不及格学生)       ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	printf("\t\t\t\t\t※          输入指令：                   ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);					//光标转到 输入指令
}
void OrderFailUI(void)
{
	system("cls");		//清屏
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t※    指令输入失败，请重新输入指令！！   ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 65);
	putchar(' ');		//清掉原先输入的痕迹
	GoToXY(17, 65);
}
void QuitSystemUI(void)
{
	system("cls");		//清屏
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t※            谢谢使用，再见！           ※\n");
	printf("\t\t\t\t\t※        3 秒后自动退出系统！！！       ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	CountDown(20, 50, 1000, '3');
}

void AddStuUI(void)
{
	system("cls");		//清屏
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t※          学生名字：                   ※\n");
	printf("\t\t\t\t\t※          学生分数：                   ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(19, 64);
}
void AddStuSucessUI(void)
{
	//此处不必清屏，因为是在上面的学生添加信息下的补充
	GoToXY(22, 0);
	printf("\t\t\t\t\t※          学生信息添加成功！           ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);		//光标转到输入指令位置（不用清残留，上面添加学生时清过了）
}
void AddStuFailUI(void)
{
	GoToXY(22, 0);
	printf("\t\t\t\t\t※    学生信息添加失败，请重新输入指令   ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);		//光标转到输入指令位置（不用清残留，上面添加学生时清过了）
}
bool Add(struct Node* stHead, struct Message* Me)
{
	//参数合法性检测
	if (NULL == stHead || NULL == Me)
		return false;
	//创建新节点
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (NULL == pTemp)
		return false;
	//新节点赋值
	pTemp->stMe = *Me;			//C语言中，同类型的结构体可以直接赋值，无需运算符重载
	stHead->iCount++;			//++ 与 -> 的运算符优先级 查表得知他俩从左向右，意味着->先起作用，那么我们就不用加小括号了	（空头来计数，普通节点不计数）
	pTemp->pNext = NULL;
	pTemp->pPre = NULL;
	//新节点连接到链表上（尾添加）(注意这是循环双向链表)
	pTemp->pNext = stHead;
	pTemp->pPre = stHead->pPre;	//这个添加到两节点间的逻辑，在数据结构线性表的课里讲过了，写过了，不难
	stHead->pPre->pNext = pTemp;
	stHead->pPre = pTemp;

	return true;
}
void ProduceNumber(struct Node* stHead)
{
	//参数合法性检测
	if (NULL == stHead || 0 >= stHead->iCount)
		return;
	//让每个添加的学生的学号，比上一次添加的学生学号+1
	stHead->pPre->stMe.iNumber = stHead->pPre->pPre->stMe.iNumber + 1;
	//这种方式对1个节点，2个节点的情况下都有效
}
void Free(struct Node* stHead)
{
	//参数合法性检测
	if (NULL == stHead || 0 >= stHead->iCount)
		return;
	//创建临时地址记录头节点
	struct Node* pT = stHead->pNext;	//空头是局部变量，会自动释放，手动释放剩下的节点
	if (NULL == pT)
		return;
	//循环释放
	while (pT != stHead)
	{
		struct Node* pP = pT;
		pT = pT->pNext;
		free(pP);						//注意，pP已经是地址了，不需加取地址符，否则引发断点
	}
	//脑袋晕给忘了，这很重要，释放后要初始化
	stHead->iCount = 0;
	stHead->stMe.iNumber = 3178902200;
	stHead->pNext = stHead;		//注意：传进来的时候就是地址形态了，不用像在外面一样加取地址符
	stHead->pPre = stHead;
}

bool SaveInFile(struct Node* stHead)
{
	//参数合法性检测
	if (NULL == stHead || 0 >= stHead->iCount)
		return false;
	//打开文件
	FILE* pFile = NULL;
	FILE* pFile1 = NULL;
	errno_t re = fopen_s(&pFile, "students.dat", "w");	//"w" 只保存一次，下次就将覆盖上一次的
	errno_t rs = fopen_s(&pFile1, "students1.dat", "w");	//怕丢失就备份
	if (0 != re || 0 != rs || NULL == pFile || NULL == pFile1)
		return false;
	//写入文件
	struct Node* pT = stHead->pNext;
	while (pT != stHead)
	{
		fwrite(&(pT->stMe), sizeof(struct Message), 1, pFile);		//将当前遍历到的节点的学生信息保存到文件中
		fwrite(&(pT->stMe), sizeof(struct Message), 1, pFile1);
		pT = pT->pNext;
	}
	//关闭文件
	fclose(pFile);
	fclose(pFile1);

	return true;
}
void SaveInFileSucessUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t※            保存到文件成功！           ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);	

}
void SaveInFileFailUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t※             保 存 失 败 ！            ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);	
}
void ReadToFile(struct Node* stHead)
{
	//参数合法性检测			//此处就不进行数量检测了，因为是读取嘛，从无到有
	if (NULL == stHead)
		return;
	//打开文件
	FILE* pFile = NULL;
	errno_t ra = fopen_s(&pFile, "students.dat", "r");
	if (0 != ra || NULL == pFile)
		return;
	//读取文件
	struct Message sr;		//临时记录的作用
	while (0 != fread(&sr, sizeof(struct Message), 1, pFile))
		Add(stHead, &sr);	//每读取一组，就给链表添加一个节点
	
	//关闭文件
	fclose(pFile);
}

void LookAll(struct Node* stHead)
{
	//参数合法性检测
	if (NULL == stHead || 0 == stHead->iCount)
		return;
	//创建临时指针
	struct Node* pT = stHead->pNext;
	if (pT == NULL)
		return;
	//刷新屏幕,打印学生信息的相关表头
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t※       学号       姓名       成绩      ※\n");
	printf("\t\t\t\t\t※  -----------------------------------  ※\n");
	int hang = 21,
		lie1 = 46,
		lie2 = 60,
		lie3 = 72;
	//读取学生信息,并打印
	//while (pT != stHead)
	//{
	//	GoToXY(hang, 0);					//打印边框
	//	printf("\t\t\t\t\t※                                       ※\n");
	//	GoToXY(hang, lie1);					//打印学号，注意unsigned int 用 %u
	//	printf("%u", pT->stMe.iNumber);
	//	GoToXY(hang, lie2);					//打印姓名
	//	printf("%s", pT->stMe.cName);
	//	GoToXY(hang, lie3);					//打印成绩
	//	printf("%d", pT->stMe.iSocre);
	//	pT = pT->pNext;
	//	hang++;								//行+1
	//}
	//读取学生信息,并打印（老师的方法）
	while (pT != stHead)
	{
		//老师的代码更简洁，- 号 是指定右对齐（默认左对齐）；10 是限定这个数或字符只能在10字符范围内，且数值变化如‘小华’ 到‘杨韵音’ 多出来的字不会顶掉后面的空格让边框超出去
		//不加字符限定，那么名字的大小，就会影响打印的整齐度
		printf("\t\t\t\t\t※    %-10u    %-10s  %-3d      ※\n", pT->stMe.iNumber, pT->stMe.cName, pT->stMe.iSocre);
		pT = pT->pNext;
	}
	//打印结尾
	//GoToXY(hang, 0);
	printf("\t\t\t\t\t※  -----------------------------------  ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	//回到指令输入位置
	GoToXY(17, 64);
}
void StuNameUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t※          搜索名字：                   ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(19, 64);		//光标转到搜索名字 后
}
void LookOne(struct Node* stHead, struct Message* Me)
{
	//参数合法性检测
	if (NULL == stHead || NULL == Me || 0 >= stHead->iCount)
		return false;
	//创建临时指针
	struct Node* pT = stHead->pNext;
	if (pT == NULL)
		return;
	//打印学生信息的相关表头，接在查找框的下方
	GoToXY(21, 0);
	printf("\t\t\t\t\t※       学号       姓名       成绩      ※\n");
	printf("\t\t\t\t\t※  -----------------------------------  ※\n");

	int i = 0;	//用来计数，看是否有查到
	//循环查找
	while (pT != stHead)
	{
		if (0 == strcmp(Me->cName, pT->stMe.cName))
		{
			i++;
			printf("\t\t\t\t\t※    %-10u    %-10s  %-3d      ※\n", pT->stMe.iNumber, pT->stMe.cName, pT->stMe.iSocre);
		}
		pT = pT->pNext;
	}

	//没有查到信息，则打印提示
	if (i == 0)
		printf("\t\t\t\t\t※            没有该学生信息！！         ※\n");

	//打印结尾
	printf("\t\t\t\t\t※  -----------------------------------  ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	//回到指令输入位置
	GoToXY(17, 64);
}
void RangeUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t※    需要搜索的分数范围：               ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(19, 67);		//光标转到搜索范围 后
}
void LookRange(struct Node* stHead, unsigned int iScore1, unsigned int iScore2)
{
	//参数合法性检测
	if (NULL == stHead || 0 >= stHead->iCount)
		return false;
	//解决a b 大小不确定情况(方式1)
	unsigned int Min, Max;
	if (iScore1 >= iScore2)		//这种方法下面就使用俩临时变量就可以了
	{
		Min = iScore2;
		Max = iScore1;			
	}
	else
	{
		Min = iScore1;
		Max = iScore2;
	}
	//创建临时指针
	struct Node* pT = stHead->pNext;
	if (pT == NULL)
		return;
	//打印学生信息的相关表头，接在查找框的下方
	GoToXY(21, 0);
	printf("\t\t\t\t\t※       学号       姓名       成绩      ※\n");
	printf("\t\t\t\t\t※  -----------------------------------  ※\n");

	int i = 0;	//用来计数，看是否有查到
	//循环查找
	while (pT != stHead)
	{		
		if (iScore1 <= pT->stMe.iSocre && iScore2 >= pT->stMe.iSocre || iScore1 >= pT->stMe.iSocre && iScore2 <= pT->stMe.iSocre)	//解决a b 大小不确定情况(方式2)
		{
			i++;
			printf("\t\t\t\t\t※    %-10u    %-10s  %-3u      ※\n", pT->stMe.iNumber, pT->stMe.cName, pT->stMe.iSocre);
		}
		pT = pT->pNext;
	}

	//没有查到信息，则打印提示
	if (i == 0)
		printf("\t\t\t\t\t※           没有对应学生信息！！        ※\n");

	//打印结尾
	printf("\t\t\t\t\t※  -----------------------------------  ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	//回到指令输入位置
	GoToXY(17, 64);
}

void DeleteNameUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t※          删除学生：                   ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(19, 64);
}
void DeleteSucessUI(void)
{
	GoToXY(21, 0);	//无需清屏，是上一界面的补充
	printf("\t\t\t\t\t※              成功删除！！             ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);	//回到指令输入位置
}
void DeleteFailUI(void)
{
	GoToXY(21, 0);
	printf("\t\t\t\t\t※              删除失败！！             ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);
}
bool Delete(struct Node* stHead, struct Message* Me)
{
	//参数合法性检测
	if (NULL == stHead || NULL == Me || 0 >= stHead->iCount)
		return false;
	//临时指针记录
	struct Node* pT = stHead->pNext;
	if (NULL == pT)
		return;
	//记录删除前的节点数
	unsigned int iCount = stHead->iCount;
	//查找学生并删除
	while (pT != stHead)
	{
		if (0 == strcmp(Me->cName, pT->stMe.cName))
		{
			//将对应节点从链表上拿掉释放
			struct Node* pP = pT->pPre;	//记录是为了还原pT，让pT继续参与循环，注意此处，pP记录的是pT->pNext 还是 pT->pPre 整体逻辑有很大改变，自己推理
			pT->pNext->pPre = pT->pPre;
			pT->pPre->pNext = pT->pNext;
			stHead->iCount--;
			free(pT);
			//还原，很重要，不要搞错，这不是正常的删中间节点逻辑，还有要继续循环遍历的条件
			pT = pP;
		}
		pT = pT->pNext;		//这句只能写在外面的while里，否则就是死循环了，这点的前提下去写if语句
	}

	//根据是否有删除学生，而返回不同结果
	if (iCount == stHead->iCount)
		return false;
	else
		return true;
}

void ChangeUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t※          搜索名字：                   ※\n");
	printf("\t\t\t\t\t※          修改分数：                   ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(19, 64);		//光标跳到 搜索后
}
void ChangeSucessUI(void)
{
	GoToXY(22, 0);	//无需清屏，是上一界面的补充
	printf("\t\t\t\t\t※              成功修改！！             ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);	//回到指令输入位置
}
void ChangeFailUI(void)
{
	GoToXY(22, 0);	
	printf("\t\t\t\t\t※              修改失败！！             ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);	
}
bool Change(struct Node* stHead, struct Message* Me)
{
	//参数合法性检测
	if (NULL == stHead || NULL == Me || 0 >= stHead->iCount)
		return false;
	//临时记录指针
	struct Node* pT = stHead->pNext;
	if (NULL == pT)
		return false;

	//循环遍历查找并修改
	int iCount = 0;		//用于记录修改的次数
	while (pT != stHead)
	{
		if (0 == strcmp(Me->cName, pT->stMe.cName))
		{
			iCount++;
			pT->stMe.iSocre = Me->iSocre;
		}
		pT = pT->pNext;
	}

	//根据是否修改过，决定返回值
	if (iCount > 0)
		return true;
	else
		return false;
}

void Test(struct Node* stHead)
{
	//参数合法性检测
	if (NULL == stHead || 0 >= stHead->iCount)
		return;
	//临时记录指针
	struct Node* pT = stHead->pNext;
	if (NULL == pT)
		return;
	//遍历
	while (pT != stHead)
	{
		//挨个用随机数重新生成成绩 %101 就产生0~100的分数，可自行修改
		pT->stMe.iSocre = (unsigned int)rand() % 101;
		pT = pT->pNext;
	}
}
void TestSucessUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t※              考试完毕！！             ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);	//回到指令输入位置
}

void SortOkUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t※    排序完毕！！ 3 秒后查看排序结果    ※\n");
	printf("\t\t\t\t\t*******************************************\n");
	CountDown(19, 59, 1000, '3');
}
void SortBySocre(struct Node* stHead)
{
	//参数合法性检测
	if (NULL == stHead || 0 >= stHead->iCount)
		return false;
	//冒泡排序
	for (unsigned int i = 0; i < stHead->iCount; i++)				//冒泡排序最多冒泡stHead->iCount - 1 次即可，比如10个元素，前9个都排好了，那么最后一个也确定了
	{
		//内层循环是一次冒泡
		struct Node* pT = stHead->pNext;
		while (pT->pNext != stHead)
		{
			if (pT->stMe.iSocre < pT->pNext->stMe.iSocre)	//此处要与pT->pNext作比较，那循环控制条件就应该用pT->pNext，否则pT->pNext == stHead的时候就越界了
			{
				//这时候要交换两节点（正常的改变节点间连线会比较麻烦）
				//另一种方式就是交换两节点的数据
				//我们采用后者，这也是一开始用结构体里放结构体成员的原因
				struct Message Ge;		//临时记录用的
				Ge = pT->stMe;			//C语言结构体能够相互赋值	
				pT->stMe = pT->pNext->stMe;
				pT->pNext->stMe = Ge;
			}
			pT = pT->pNext;
		}
	}
}
void SortByNumber(struct Node* stHead)
{
	//参数合法性检测
	if (NULL == stHead || 0 >= stHead->iCount)
		return false;
	
	//冒泡排序
	for (unsigned int i = 0; i < stHead->iCount; i++)
	{
		//内层循环是一次冒泡
		struct Node* pT = stHead->pNext;
		while (pT->pNext != stHead)
		{
			if (pT->stMe.iNumber < pT->pNext->stMe.iNumber)	
			{
				struct Message Ge;	
				Ge = pT->stMe;			
				pT->stMe = pT->pNext->stMe;
				pT->pNext->stMe = Ge;
			}
			pT = pT->pNext;
		}
	}
}

