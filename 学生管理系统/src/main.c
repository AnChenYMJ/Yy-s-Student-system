#pragma once
#include "common.h"
//#include "login.h"
//#include "manage.h"

//登陆函数	(统筹函数)
bool Login(void);						//登陆相关的逻辑，全放到这里，主函数调用它一个就行了
//管理函数	（统筹函数）
void Manage(void);

int main(void)
{
	if (true == Login())		//登录函数
	{
		Manage();
	}
	else
	{
		system("cls");
		GoToXY(10, 20);
		printf("已退出系统，按任意键继续");
	}



	system("pause>0");		//system仅对windows有效 getchar比较通用
	return 0;
}

