#include "login.h"

//�û���Ϣ�ṹ�� ȫ�ֱ���
struct User g_user = { "�ο�" };		//�ô��ܶ࣬����Ŀγ̻ὲ

//��½����
bool Login(void)
{
	LoginMenuUI();		//��ӡ���˵�
	while (1)
	{
		int iOrder = 0;
		scanf_s("%d", &iOrder);				//�������˵�ָ��
		switch (iOrder)
		{
		//��½����
		case 1:
			LoginUI();						//��ʾ�Ӳ˵�
			scanf_s("%s", g_user.name, 15);	//�����û���
			GoToXY(12, 61);					//������֮�󣬹����ת��ָ��λ�ü�������
			scanf_s("%s", g_user.Key, 20);	//��������
											//��½�ɹ�
			if (true == IsRight(&g_user))
			{
				LoginSucessUI();
				return true;
			}
			else							//��½ʧ��
				LoginFailUI();				//ʧ�ܺ��˳�switch �ص�while��ͷ��������
			break;
		//ע�����
		case 2:
			LoginUI();			
			GoToXY(11, 61);				
			scanf_s("%s", g_user.name, 15);
			GoToXY(12, 61);				
			scanf_s("%s", g_user.Key, 20);
											//��̨û�ҵ���Ӧ��Ϣ������ע��
			if (false == IsRight(&g_user) || false == IsUserExist(&g_user))
			{
				SaveUser(&g_user);			//���̨�������û���Ϣ
				RegisterSucessUI();			//ע��ɹ�
				return true;
			}
			else							//��̨�ж�Ӧ���û��ˣ�ע��ʧ��
				RegisterFailUI();
			break;
		//�ο͵�½
		case 3:
			strcpy_s(g_user.name, 15, "�ο�");	//ǧ��ע�⣬user.name�����飬����ֱ�Ӹ�ֵ��ֻ��ͨ��������ѭ��
			VIsitorLoginUI();
			return true;
			break;
		//�˳�ϵͳ
		case 4:
			QuitLoginUI();					
			return false;					//Login��������false����ֱ�ӽ��������ˣ���Ȼ��Ϊmain��system("pause>0"); Ҫ���������������ȫ�ر�
			break;
		default:							//Ĭ�ϣ�����ķ��඼û��ƥ��ģ���ִ����һ������˼�������ָ��������趨�ķ�Χ��
		{
			char c = 0;						//switch�в���ֱ���������壬������{}�Ϳ�����		EOF���ļ��Ľ�β
			while ((c = getchar()) != '\n' && c != EOF);	//��ջ������������ַ������뵼�¿�ס�����ַ�ʽҲ�б׶ˣ�������չ����У��ֲ��ϼ��������룬�ᵼ������
			OrderWrongUI();					//ָ��ʧЧ����������ָ��
											//�����и����⣬����ָ���int iOrder �����Σ�����ͻ������ַ����ᷢ�ֳ���ס������������
											//ԭ���ǣ��ַ��Ͳ��ܱ�װ�������У���һֱ�����ڻ������������ڴ��������´�ѭ����������������������ַ��ͣ���һ�ֻ���
											//��������ַ��;ͽ��������ˣ����ܱ����int �����������Ǿ�û�취��������
											//����취����ջ��������ϰٶ��ң���ʦ�ĵ�һ����VC��Ч��VS��û����
		}
		}
	}



	//���Ҵ���Ĳ���
	/*struct User uc = { "Сͷ" };
	if (true == IsUserExist(&uc))
		printf("�ҵ���");
	else
		printf("û�ҵ�");*/

	//����û���Ϣ
	/*struct User ue = { "��ͷ", "654321" };
	SaveUser(&ue);
	struct User ue = { "С͵", "123456" };
	SaveUser(&ue);*/

}


void LoginMenuUI(void)		
{
	//��ʼ�����
	GoToXY(0, 0);
	printf("\n\n");		//����ָ�����ӵ�3�п�ʼ�ģ��Ͳ�����\n ��
	printf("\t\t\t\t\t**************************************\n");
	printf("\t\t\t\t\t��           ��ӭʹ�ñ�ϵͳ         ��\n");
	printf("\t\t\t\t\t��      (��ز����������Ӧָ��)    ��\n");
	printf("\t\t\t\t\t��           1���û���¼            ��\n");
	printf("\t\t\t\t\t��           2���˺�ע��            ��\n");
	printf("\t\t\t\t\t��           3���ο͵�½            ��\n");
	printf("\t\t\t\t\t��           4���˳�ϵͳ            ��\n");
	printf("\t\t\t\t\t��      ������ָ��(1/2/3/4)��       ��\n");
	printf("\t\t\t\t\t**************************************\n");

	//������ƶ��� ��������ָ��(1/2/3/4)���� �ĺ��棬��������
	GoToXY(9, 69);
}
void GoToXY(short sHang, short sLie)
{
	COORD CD = { sLie , sHang };									//����ĺ�������Ҫ�Ľṹ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CD);	//����1�Ǿ����ÿ�����ڶ���Ψһ��Ӧ��ID��
}
void CountDown(short hang, short lie, int iTime, char Count)
{
	for (int i = 0; i <= (Count - '0'); i++)
	{
		//Count���ַ��ͣ���Ҫ��ֵ������'3' ��ô ��ȥ '0' �͵õ���ֵ��,��Ϊ�ַ���Ψһ��Ӧ�ı�ţ���ֵ�����ǰ����������
		GoToXY(hang, lie);
		putchar(Count - i);		//�˴�Ӧ���ǰ�iת�� 'i' Ȼ���� Count - 'i' ��Ϊ��������������Ǵ��
		Sleep(iTime);
	}
}

void SaveUser(struct User* user)
{
	//�����Ϸ��Լ��
	if (NULL == user)
		return;
	//���ļ�
	FILE* pFile = NULL;
	errno_t res = fopen_s(&pFile, "user.dat", "a");		//"user.dat" ���������ʲô����ʲô��׺�����ԣ�ֻҪ�����Լ�֪������ ��a�� �ǽ���д��û�ж�Ӧ�ļ����ʹ�����Ӧ�ļ�
	if (0 != res || NULL == pFile)
		return;
	//д���ļ�
	fwrite(user, sizeof(struct User), 1, pFile);		//�ṹ��user���ļ����ļ�ָ�� pFile ָ���λ��д�� 1 ���СΪ sizeof(struct User) ������
	//�ر��ļ�		����fopen_s��һ��Ҫfclose �������fopen_s��13�����룬�´�fopen_s���ò����ˣ�
	fclose(pFile);
}
bool IsRight(struct User* user)
{
	//�����Ϸ��Լ��
	if (NULL == user)
		return false;
	//���ļ�
	FILE* pFile = NULL;
	errno_t res = fopen_s(&pFile, "user.dat", "r");
	if (0 != res || NULL == pFile)
		return false;
	//ѭ����ȡ�ļ�
	while (!feof(pFile))		//feof�����δӸ��ĵ�ַ��ʼ��������û����β����0����������β����1
	{
		struct User ue = { 0 };
		fread(&ue, sizeof(ue), 1, pFile);
		if (strcmp(user->name, ue.name) == 0 && strcmp(user->Key, ue.Key) == 0)	//ע��Ƚ��ú�����strcmp
			return true;		//�ô���������Ϣ���뱣�浽�ļ��е���Ϣ���бȽϣ����û��������붼��ͬ��˵���鵽�ˣ���ע���
	}
	//�ر��ļ�
	fclose(pFile);
	//����ѭ������û�鵽��˵��û��ע���
	return false;
}
bool IsUserExist(struct User* user)
{
	//�����Ϸ��Լ��
	if (NULL == user)
		return false;
	//���ļ�
	FILE* pFile = NULL;
	errno_t res = fopen_s(&pFile, "user.dat", "r");
	if (0 != res || NULL == pFile)
		return false;
	//ѭ����ȡ�ļ�
	while (!feof(pFile))		//feof�����δӸ��ĵ�ַ��ʼ��������û����β����0����������β����1
	{
		struct User ue = { 0 };
		fread(&ue, sizeof(ue), 1, pFile);
		if (strcmp(user->name, ue.name) == 0)	//ע��Ƚ��ú�����strcmp
			return true;		//�ô���������Ϣ���뱣�浽�ļ��е���Ϣ���бȽϣ����û��������붼��ͬ��˵���鵽�ˣ���ע���
	}
	//�ر��ļ�
	fclose(pFile);
	//����ѭ������û�鵽��˵��û��ע���
	return false;
}

void LoginUI(void)
{
	GoToXY(11, 0);
	printf("\t\t\t\t\t��           ��¼����               ��\n");
	printf("\t\t\t\t\t��	   ��½���룺               ��\n");
	printf("\t\t\t\t\t**************************************\n");
	GoToXY(11, 61);			//���������¼����
}
void LoginFailUI(void)
{
	GoToXY(14, 0);
	printf("\t\t\t\t\t��   ��½ʧ�ܣ�����������ָ����� ��\n");
	printf("\t\t\t\t\t**************************************\n");
	GoToXY(9, 69);			//�����������ָ��λ��
	putchar(' ');			//����ǰ��λ�õ�ָ��Ĩ��
	GoToXY(9, 69);			//���ٻص�����ָ��λ��
}
void LoginSucessUI(void)
{
	GoToXY(14, 0);
	printf("\t\t\t\t\t��   ��½�ɹ���3 �����ת���棡���� ��\n");
	printf("\t\t\t\t\t**************************************\n");
	CountDown(14, 55, 1000, '3');		//������ʱ��װ��������������

	//Sleep(1000);			//ͣ1��
	//GoToXY(14, 55);
	//putchar('2');			//��ʣ����תʱ����µ���ʾ��
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
	printf("\t\t\t\t\t��           ע������               ��\n");
	printf("\t\t\t\t\t��	   ע�����룺               ��\n");
	printf("\t\t\t\t\t**************************************\n");
	GoToXY(11, 61);			//�������ע������
}
void RegisterFailUI(void)
{
	GoToXY(14, 0);
	printf("\t\t\t\t\t��   ע��ʧ�ܣ�����������ָ����� ��\n");
	printf("\t\t\t\t\t**************************************\n");
	GoToXY(9, 69);			//�����������ָ��λ��
	putchar(' ');			//����ǰ��λ�õ�ָ��Ĩ��
	GoToXY(9, 69);			//���ٻص�����ָ��λ��
}
void RegisterSucessUI(void)
{
	GoToXY(14, 0);
	printf("\t\t\t\t\t��   ע��ɹ���3 �����ת���棡���� ��\n");
	printf("\t\t\t\t\t**************************************\n");
	CountDown(14, 55, 1000, '3');		//������ʱ��װ��������������
}

void VIsitorLoginUI(void)
{
	system("cls");		//��������ֹ��ǰ������������Ĳ���
	LoginMenuUI();		//�ػ����˵�
	GoToXY(11, 0);
	printf("\t\t\t\t\t��     3 ������ο���ݵ�¼������ ��\n");
	printf("\t\t\t\t\t**************************************\n");
	CountDown(11, 47, 1000, '3');
}
void QuitLoginUI(void)
{
	system("cls");		
	LoginMenuUI();	
	GoToXY(11, 0);
	printf("\t\t\t\t\t��    �˳�ϵͳ��3 ��������ת��������\n");
	printf("\t\t\t\t\t**************************************\n");
	CountDown(11, 56, 1000, '3');
}
void OrderWrongUI(void)
{
	system("cls");
	LoginMenuUI();
	GoToXY(11, 0);
	printf("\t\t\t\t\t��  ָ������ʧ�ܣ�����������ָ�����\n");
	printf("\t\t\t\t\t**************************************\n");
	GoToXY(9, 69);			//�����������ָ��λ��
	putchar(' ');			//����ǰ��λ�õ�ָ��Ĩ��
	GoToXY(9, 69);			//���ٻص�����ָ��λ��
}

