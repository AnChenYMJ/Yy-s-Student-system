#pragma once
				//VS���������Զ����ϴ���  ��ֹͷ�ļ��ظ����� ����Ҳ�����Լ��ֶ�����һ�֣�����ͨ���Բ���һ��
#include "common.h"



//��½����
bool Login(void);

//��½����
void LoginMenuUI(void);					//��ӡ��ʼ�����˵�
void CountDown(short hang, short lie, int iTime, char Count);		//����ʱ��װ����  ������ĵ�¼��ע���ж����õ����ʵ�����װ

void SaveUser(struct User* user);		//�����û���Ϣ���ļ��У��û��������룩
bool IsRight(struct User* user);		//����һ���û������Һ�̨�Ƿ���ƥ����û���Ϣ���û��������룩
bool IsUserExist(struct User* user);	//����һ���û�,���Һ�̨�Ƿ���ƥ����û����������û�����

void LoginUI(void);						//��¼���棬�����˵��� 1 ѡ��
void LoginFailUI(void);					//��¼ʧ�� ��ʾ
void LoginSucessUI(void);				//��¼�ɹ� ��ʾ

void RegisterUI(void);					//ע����棬�����˵��� 1 ѡ��
void RegisterFailUI(void);				//ע��ʧ�� ��ʾ
void RegisterSucessUI(void);			//ע��ɹ� ��ʾ

void VIsitorLoginUI(void);				//�ο͵�¼����
void QuitLoginUI(void);					//�ο��˳�����
void OrderWrongUI(void);				//ָ�������������
	