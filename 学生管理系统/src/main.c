#pragma once
#include "common.h"
//#include "login.h"
//#include "manage.h"

//��½����	(ͳ�ﺯ��)
bool Login(void);						//��½��ص��߼���ȫ�ŵ����������������һ��������
//������	��ͳ�ﺯ����
void Manage(void);

int main(void)
{
	if (true == Login())		//��¼����
	{
		Manage();
	}
	else
	{
		system("cls");
		GoToXY(10, 20);
		printf("���˳�ϵͳ�������������");
	}



	system("pause>0");		//system����windows��Ч getchar�Ƚ�ͨ��
	return 0;
}

