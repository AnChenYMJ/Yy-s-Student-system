#include "login.h"

//用户信息结构体 全局变量
struct User g_user = { "游客" };		//好处很多，管理的课程会讲

//登陆函数
bool Login(void)
{
	LoginMenuUI();		//打印主菜单
	while (1)
	{
		int iOrder = 0;
		scanf_s("%d", &iOrder);				//输入主菜单指令
		switch (iOrder)
		{
		//登陆界面
		case 1:
			LoginUI();						//显示子菜单
			scanf_s("%s", g_user.name, 15);	//输入用户名
			GoToXY(12, 61);					//输入完之后，光标跳转到指定位置继续输入
			scanf_s("%s", g_user.Key, 20);	//输入密码
											//登陆成功
			if (true == IsRight(&g_user))
			{
				LoginSucessUI();
				return true;
			}
			else							//登陆失败
				LoginFailUI();				//失败后退出switch 回到while开头继续输入
			break;
		//注册界面
		case 2:
			LoginUI();			
			GoToXY(11, 61);				
			scanf_s("%s", g_user.name, 15);
			GoToXY(12, 61);				
			scanf_s("%s", g_user.Key, 20);
											//后台没找到对应信息，可以注册
			if (false == IsRight(&g_user) || false == IsUserExist(&g_user))
			{
				SaveUser(&g_user);			//向后台添加这个用户信息
				RegisterSucessUI();			//注册成功
				return true;
			}
			else							//后台有对应的用户了，注册失败
				RegisterFailUI();
			break;
		//游客登陆
		case 3:
			strcpy_s(g_user.name, 15, "游客");	//千万注意，user.name是数组，不能直接赋值，只能通过函数与循环
			VIsitorLoginUI();
			return true;
			break;
		//退出系统
		case 4:
			QuitLoginUI();					
			return false;					//Login函数返回false，就直接结束程序了，当然因为main有system("pause>0"); 要按任意键继续才完全关闭
			break;
		default:							//默认，上面的分类都没有匹配的，则执行这一步，意思是输入的指令超出我们设定的范围了
		{
			char c = 0;						//switch中不能直接声明定义，但加上{}就可以了		EOF是文件的结尾
			while ((c = getchar()) != '\n' && c != EOF);	//清空缓冲区，避免字符型输入导致卡住，这种方式也有弊端，比如清空过程中，又不断极快速输入，会导致问题
			OrderWrongUI();					//指令失效，重新输入指令
											//但是有个问题，接收指令的int iOrder 是整形，假设客户输入字符，会发现程序卡住，不能输入了
											//原因是：字符型不能被装到整形中，会一直存在于缓冲区（类似内存条），下次循环来读缓冲区，还是这个字符型，再一轮还是
											//这样这个字符型就进退两难了，不能被存进int 读不出来我们就没办法继续输入
											//解决办法：清空缓冲区，上百度找，老师的第一种在VC有效，VS就没用了
		}
		}
	}



	//查找代码的测试
	/*struct User uc = { "小头" };
	if (true == IsUserExist(&uc))
		printf("找到了");
	else
		printf("没找到");*/

	//添加用户信息
	/*struct User ue = { "大头", "654321" };
	SaveUser(&ue);
	struct User ue = { "小偷", "123456" };
	SaveUser(&ue);*/

}


void LoginMenuUI(void)		
{
	//起始行输出
	GoToXY(0, 0);
	printf("\n\n");		//可以指定光标从低3行开始的，就不必俩\n 了
	printf("\t\t\t\t\t**************************************\n");
	printf("\t\t\t\t\t※           欢迎使用本系统         ※\n");
	printf("\t\t\t\t\t※      (相关操作请输入对应指令)    ※\n");
	printf("\t\t\t\t\t※           1：用户登录            ※\n");
	printf("\t\t\t\t\t※           2：账号注册            ※\n");
	printf("\t\t\t\t\t※           3：游客登陆            ※\n");
	printf("\t\t\t\t\t※           4：退出系统            ※\n");
	printf("\t\t\t\t\t※      请输入指令(1/2/3/4)：       ※\n");
	printf("\t\t\t\t\t**************************************\n");

	//将光标移动到 “请输入指令(1/2/3/4)：” 的后面，方便输入
	GoToXY(9, 69);
}
void GoToXY(short sHang, short sLie)
{
	COORD CD = { sLie , sHang };									//下面的函数所需要的结构体
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CD);	//参数1是句柄（每个窗口都有唯一对应的ID）
}
void CountDown(short hang, short lie, int iTime, char Count)
{
	for (int i = 0; i <= (Count - '0'); i++)
	{
		//Count是字符型，想要数值，比如'3' 那么 减去 '0' 就得到数值了,因为字符有唯一对应的编号（数值）且是按规律排序的
		GoToXY(hang, lie);
		putchar(Count - i);		//此处应该是把i转成 'i' 然后再 Count - 'i' 因为不这样，结果就是错的
		Sleep(iTime);
	}
}

void SaveUser(struct User* user)
{
	//参数合法性检测
	if (NULL == user)
		return;
	//打开文件
	FILE* pFile = NULL;
	errno_t res = fopen_s(&pFile, "user.dat", "a");		//"user.dat" 我们随便起什么名，什么后缀都可以，只要我们自己知道就行 “a” 是接着写，没有对应文件，就创建对应文件
	if (0 != res || NULL == pFile)
		return;
	//写入文件
	fwrite(user, sizeof(struct User), 1, pFile);		//结构体user向文件中文件指针 pFile 指向的位置写入 1 组大小为 sizeof(struct User) 的数据
	//关闭文件		（有fopen_s就一定要fclose 否则会有fopen_s的13错误码，下次fopen_s就用不了了）
	fclose(pFile);
}
bool IsRight(struct User* user)
{
	//参数合法性检测
	if (NULL == user)
		return false;
	//打开文件
	FILE* pFile = NULL;
	errno_t res = fopen_s(&pFile, "user.dat", "r");
	if (0 != res || NULL == pFile)
		return false;
	//循环读取文件
	while (!feof(pFile))		//feof会依次从给的地址开始向后遍历，没到结尾返回0，遍历到结尾返回1
	{
		struct User ue = { 0 };
		fread(&ue, sizeof(ue), 1, pFile);
		if (strcmp(user->name, ue.name) == 0 && strcmp(user->Key, ue.Key) == 0)	//注意比较用函数：strcmp
			return true;		//用传进来的信息，与保存到文件中的信息进行比较，当用户名与密码都相同，说明查到了，有注册过
	}
	//关闭文件
	fclose(pFile);
	//经过循环。还没查到，说明没有注册过
	return false;
}
bool IsUserExist(struct User* user)
{
	//参数合法性检测
	if (NULL == user)
		return false;
	//打开文件
	FILE* pFile = NULL;
	errno_t res = fopen_s(&pFile, "user.dat", "r");
	if (0 != res || NULL == pFile)
		return false;
	//循环读取文件
	while (!feof(pFile))		//feof会依次从给的地址开始向后遍历，没到结尾返回0，遍历到结尾返回1
	{
		struct User ue = { 0 };
		fread(&ue, sizeof(ue), 1, pFile);
		if (strcmp(user->name, ue.name) == 0)	//注意比较用函数：strcmp
			return true;		//用传进来的信息，与保存到文件中的信息进行比较，当用户名与密码都相同，说明查到了，有注册过
	}
	//关闭文件
	fclose(pFile);
	//经过循环。还没查到，说明没有注册过
	return false;
}

void LoginUI(void)
{
	GoToXY(11, 0);
	printf("\t\t\t\t\t※           登录名：               ※\n");
	printf("\t\t\t\t\t※	   登陆密码：               ※\n");
	printf("\t\t\t\t\t**************************************\n");
	GoToXY(11, 61);			//光标跳到登录名后
}
void LoginFailUI(void)
{
	GoToXY(14, 0);
	printf("\t\t\t\t\t※   登陆失败，请重新输入指令！！！ ※\n");
	printf("\t\t\t\t\t**************************************\n");
	GoToXY(9, 69);			//光标跳到输入指令位置
	putchar(' ');			//将此前该位置的指令抹掉
	GoToXY(9, 69);			//光再回到输入指令位置
}
void LoginSucessUI(void)
{
	GoToXY(14, 0);
	printf("\t\t\t\t\t※   登陆成功，3 秒后跳转界面！！！ ※\n");
	printf("\t\t\t\t\t**************************************\n");
	CountDown(14, 55, 1000, '3');		//将倒计时封装到函数里，方便调用

	//Sleep(1000);			//停1秒
	//GoToXY(14, 55);
	//putchar('2');			//让剩余跳转时间更新到提示里
	//Sleep(1000);
	//GoToXY(14, 55);
	//putchar('1');
	//Sleep(1000);
	//GoToXY(14, 55);
	//putchar('0');
}

void RegisterUI(void)
{
	GoToXY(11, 0);
	printf("\t\t\t\t\t※           注册名：               ※\n");
	printf("\t\t\t\t\t※	   注册密码：               ※\n");
	printf("\t\t\t\t\t**************************************\n");
	GoToXY(11, 61);			//光标跳到注册名后
}
void RegisterFailUI(void)
{
	GoToXY(14, 0);
	printf("\t\t\t\t\t※   注册失败，请重新输入指令！！！ ※\n");
	printf("\t\t\t\t\t**************************************\n");
	GoToXY(9, 69);			//光标跳到输入指令位置
	putchar(' ');			//将此前该位置的指令抹掉
	GoToXY(9, 69);			//光再回到输入指令位置
}
void RegisterSucessUI(void)
{
	GoToXY(14, 0);
	printf("\t\t\t\t\t※   注册成功，3 秒后跳转界面！！！ ※\n");
	printf("\t\t\t\t\t**************************************\n");
	CountDown(14, 55, 1000, '3');		//将倒计时封装到函数里，方便调用
}

void VIsitorLoginUI(void)
{
	system("cls");		//清屏，防止此前其它操作界面的残留
	LoginMenuUI();		//重绘主菜单
	GoToXY(11, 0);
	printf("\t\t\t\t\t※     3 秒后将以游客身份登录！！！ ※\n");
	printf("\t\t\t\t\t**************************************\n");
	CountDown(11, 47, 1000, '3');
}
void QuitLoginUI(void)
{
	system("cls");		
	LoginMenuUI();	
	GoToXY(11, 0);
	printf("\t\t\t\t\t※    退出系统，3 秒后进行跳转！！！※\n");
	printf("\t\t\t\t\t**************************************\n");
	CountDown(11, 56, 1000, '3');
}
void OrderWrongUI(void)
{
	system("cls");
	LoginMenuUI();
	GoToXY(11, 0);
	printf("\t\t\t\t\t※  指令输入失败，请重新输入指令！！※\n");
	printf("\t\t\t\t\t**************************************\n");
	GoToXY(9, 69);			//光标跳到输入指令位置
	putchar(' ');			//将此前该位置的指令抹掉
	GoToXY(9, 69);			//光再回到输入指令位置
}

