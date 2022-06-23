#pragma once
#include "common.h"

//�ⲿ���������÷�ʽ  �������׳��֣������������������ܸ�ֵ	
//struct User
//{
//						//ע�⣡��������������ã���ômain.c��Ͳ���ͬʱ��������ṹ�������.h�ˣ����鿴����ĵ�2�αʼ�
//	char name[15];		//�򵥽�������������ͷŵ�common.h ����ͷ�ļ��� �������������������
//	char Key[20];
//};
extern struct User g_user;

//������	��ͳ�ﺯ����
void Manage(void);

//�ڵ���
//ѧ����Ϣ�ڵ�
struct Message
{
	unsigned int iNumber;	//ѧ��
	unsigned char cName[15];			//����
	unsigned int iSocre;				//�ɼ�
};
//����ڵ�
struct Node
{
	struct Message stMe;	//ѧ����Ϣ
	unsigned int iCount;	//����
	struct Node* pPre;		//ǰһ�ڵ��ַ
	struct Node* pNext;		//��һ�ڵ��ַ
};


//�������
void CountDown(short hang, short lie, int iTime, char Count);	//����ʱ
void ManageMenuUI(void);	//�����������˵�
void OrderFailUI(void);		//����ָ���������
void QuitSystemUI(void);	//�˳�ϵͳ����

void AddStuUI(void);		//���ѧ������
void AddStuSucessUI(void);	//���ѧ�����·��ĳɹ���ʾ
void AddStuFailUI(void);	//���ѧ��ʧ����ʾ
bool Add(struct Node* stHead, struct Message* Me);	//ѧ��������ӽڵ㣨β��ӣ�
void ProduceNumber(struct Node* stHead);			//ѧ����Ϣ��ѧ�����ɻ���
void Free(struct Node* stHead);						//�ͷ�����

bool SaveInFile(struct Node* stHead);				//����ѧ����Ϣ���ļ���
void SaveInFileSucessUI(void);						//����ɹ�
void SaveInFileFailUI(void);						//����ʧ��
void ReadToFile(struct Node* stHead);				//���ļ��ж�ȡ����,�浽������

void LookAll(struct Node* stHead);					//�������е�ѧ����Ϣ
void StuNameUI(void);								//�������ֽ���
void LookOne(struct Node* stHead, struct Message* Me);//����ָ��ѧ��
void RangeUI(void);									//������Χ���ҽ���
void LookRange(struct Node* stHead, unsigned int iScore1, unsigned int iScore2);	//���ҷ�Χ�ڷ�����ѧ��

void DeleteNameUI(void);	//ɾ��ָ��ѧ������
void DeleteSucessUI(void);	//�ɹ���ʾ	������һ������
void DeleteFailUI(void);		//ʧ����ʾ
bool Delete(struct Node* stHead, struct Message* Me);//ɾ��ѧ����Ϣ���ڵ㣩

void ChangeUI(void);								//�޸Ľ���
void ChangeSucessUI(void);							//�ɹ���ʾ
void ChangeFailUI(void);							//ʧ����ʾ
bool Change(struct Node* stHead, struct Message* Me);

void Test(struct Node* stHead);						//���п���
void TestSucessUI(void);							//�ɹ���ʾ

void SortOkUI(void);								//�������
void SortBySocre(struct Node* stHead);				//���ɼ�����	 ����ð������
void SortByNumber(struct Node* stHead);				//��ѧ������


