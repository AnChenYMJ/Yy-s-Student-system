#pragma once

//����ͷ�ļ����������ļ���Ҫ�õ���ͷ�ļ����ŵ��˴��������ļ�����������

#include <stdio.h>
#include <stdlib.h>
#include <string.h>			//strcmp �ַ����ȽϺ��� Ҫ��
#include <stdbool.h>
#include <windows.h>		//���ù��λ��Ҫ�õ�	
#include <time.h>			// ���������Ҫ��

void GoToXY(short sHang, short sLie);	//���ÿ���̨���λ��
//�û���Ϣ�ṹ������		(ÿ���ļ����ܴ���һ��ͬ���Ľṹ����������������������ڵ��ļ���ͬ���ļ��²����������ṹ������)
struct User
{
	char name[15];			//��������С���Զ�������ٿ�
	char Key[20];
};



