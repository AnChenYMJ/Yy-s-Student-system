#pragma once
#include "manage.h"

void Manage(void)
{
	ManageMenuUI();		//��ӡ���˵�
	srand(time(NULL));	//���������

	struct Node stHead;	//��ͷ �����ʼ��			ע�����Ǿֲ�����������������Զ��ͷţ�����Ҫ�����ֶ��ͷ�
	stHead.stMe.iNumber = 3178902200;
	stHead.stMe.iSocre = 0;
	stHead.iCount = 0;	//�������ַ�������ô��ֵ��
	stHead.pPre = &stHead;
	stHead.pNext = &stHead;

	struct Message ME;	//�����������ʱ�洢


	ReadToFile(&stHead);	//���Գɹ����ɹ���ȡ �Ͳ���ÿ�ζ��ֶ�������

	while (1)
	{
		int iOrder = -1;
		scanf_s("%d", &iOrder);
		switch (iOrder)
		{
		case 0:			//�˳�ϵͳ	
			QuitSystemUI();
			Free(&stHead);									//�˳�ѭ��ǰ�ͷ�����
			return;
			break;

		case 1:			//���ѧ��
			AddStuUI();
			scanf_s("%s", ME.cName, 15);					//��������
			GoToXY(20, 64);
			scanf_s("%d", &ME.iSocre);						//����ɼ�
			if (true == Add(&stHead, &ME))
			{
				ProduceNumber(&stHead);						//����ѧ��
				AddStuSucessUI();
			}
			else
				AddStuFailUI();
			break;

		case 2:			//�������ݽ��ļ�
			if (true == SaveInFile(&stHead))
				SaveInFileSucessUI();
			else
				SaveInFileFailUI();
			break;

		case 3:			//����ָ��������ѧ��
			StuNameUI();
			scanf_s("%s", ME.cName, 15);	//ME �����涨�����ʱ�洢�ýṹ��
			LookOne(&stHead, &ME);
			break;

		case 4:			//��ѯ����ѧ������Ϣ
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

		default:											//����ָ������
		{
			char c = 0 ;									// switch�в���ֱ���������壬������{}�Ϳ�����
			while ('\n' != (c = getchar()) && EOF != c);	// ��ջ������������ַ������뵼�¿�ס
			OrderFailUI();
		}
		}
	}
	Free(&stHead);		//�ͷţ���ʵ��������ˣ�ѭ����returnǰ�ӵ� Free ������Ч��
}

void ManageMenuUI(void)
{
	system("cls");					//��������߼��ϻ������
	GoToXY(0, 0);
	printf("\n\n");
	printf("\t\t\t\t\t*******************************************\n");
	printf("\t\t\t\t\t��         �� ӭ ʹ �� �� ϵ ͳ          ��\n");
	printf("\t\t\t\t\t��             ����Ա��                  ��\n");
	GoToXY(4, 65);					//���ת�� ����Ա�� ��
	printf("%s", g_user.name);		//��Ϊ��¼�������߼��У�������ע�ᡢ��¼���οͣ�������g_user���ȫ�ֱ����������ģ��Ǵ����ʹ������û�����Ϣ
	GoToXY(5, 0);					//���ص�����������ӡʣ�����
	printf("\t\t\t\t\t��             (ָ�����)              ��\n");
	printf("\t\t\t\t\t��          0.�˳�ϵͳ                   ��\n");
	printf("\t\t\t\t\t��          1.���һ��ѧ��               ��\n");
	printf("\t\t\t\t\t��          2.�������ݽ��ļ�             ��\n");
	printf("\t\t\t\t\t��          3.��ʾָ��ѧ����Ϣ           ��\n");
	printf("\t\t\t\t\t��          4.��ʾ����ѧ����Ϣ           ��\n");
	printf("\t\t\t\t\t��          5.�޸�ָ��ѧ����Ϣ           ��\n");
	printf("\t\t\t\t\t��          6.ɾ��ָ��ѧ����Ϣ           ��\n");
	printf("\t\t\t\t\t��          7.����                       ��\n");
	printf("\t\t\t\t\t��          8.���ݳɼ�˳��鿴           ��\n");
	printf("\t\t\t\t\t��          9.ͳ��(��ʾ������ѧ��)       ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	printf("\t\t\t\t\t��          ����ָ�                   ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);					//���ת�� ����ָ��
}
void OrderFailUI(void)
{
	system("cls");		//����
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t��    ָ������ʧ�ܣ�����������ָ���   ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 65);
	putchar(' ');		//���ԭ������ĺۼ�
	GoToXY(17, 65);
}
void QuitSystemUI(void)
{
	system("cls");		//����
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t��            ллʹ�ã��ټ���           ��\n");
	printf("\t\t\t\t\t��        3 ����Զ��˳�ϵͳ������       ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	CountDown(20, 50, 1000, '3');
}

void AddStuUI(void)
{
	system("cls");		//����
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t��          ѧ�����֣�                   ��\n");
	printf("\t\t\t\t\t��          ѧ��������                   ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(19, 64);
}
void AddStuSucessUI(void)
{
	//�˴�������������Ϊ���������ѧ�������Ϣ�µĲ���
	GoToXY(22, 0);
	printf("\t\t\t\t\t��          ѧ����Ϣ��ӳɹ���           ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);		//���ת������ָ��λ�ã�������������������ѧ��ʱ����ˣ�
}
void AddStuFailUI(void)
{
	GoToXY(22, 0);
	printf("\t\t\t\t\t��    ѧ����Ϣ���ʧ�ܣ�����������ָ��   ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);		//���ת������ָ��λ�ã�������������������ѧ��ʱ����ˣ�
}
bool Add(struct Node* stHead, struct Message* Me)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || NULL == Me)
		return false;
	//�����½ڵ�
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (NULL == pTemp)
		return false;
	//�½ڵ㸳ֵ
	pTemp->stMe = *Me;			//C�����У�ͬ���͵Ľṹ�����ֱ�Ӹ�ֵ���������������
	stHead->iCount++;			//++ �� -> ����������ȼ� ����֪�����������ң���ζ��->�������ã���ô���ǾͲ��ü�С������	����ͷ����������ͨ�ڵ㲻������
	pTemp->pNext = NULL;
	pTemp->pPre = NULL;
	//�½ڵ����ӵ������ϣ�β��ӣ�(ע������ѭ��˫������)
	pTemp->pNext = stHead;
	pTemp->pPre = stHead->pPre;	//�����ӵ����ڵ����߼��������ݽṹ���Ա�Ŀ��ｲ���ˣ�д���ˣ�����
	stHead->pPre->pNext = pTemp;
	stHead->pPre = pTemp;

	return true;
}
void ProduceNumber(struct Node* stHead)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || 0 >= stHead->iCount)
		return;
	//��ÿ����ӵ�ѧ����ѧ�ţ�����һ����ӵ�ѧ��ѧ��+1
	stHead->pPre->stMe.iNumber = stHead->pPre->pPre->stMe.iNumber + 1;
	//���ַ�ʽ��1���ڵ㣬2���ڵ������¶���Ч
}
void Free(struct Node* stHead)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || 0 >= stHead->iCount)
		return;
	//������ʱ��ַ��¼ͷ�ڵ�
	struct Node* pT = stHead->pNext;	//��ͷ�Ǿֲ����������Զ��ͷţ��ֶ��ͷ�ʣ�µĽڵ�
	if (NULL == pT)
		return;
	//ѭ���ͷ�
	while (pT != stHead)
	{
		struct Node* pP = pT;
		pT = pT->pNext;
		free(pP);						//ע�⣬pP�Ѿ��ǵ�ַ�ˣ������ȡ��ַ�������������ϵ�
	}
	//�Դ��θ����ˣ������Ҫ���ͷź�Ҫ��ʼ��
	stHead->iCount = 0;
	stHead->stMe.iNumber = 3178902200;
	stHead->pNext = stHead;		//ע�⣺��������ʱ����ǵ�ַ��̬�ˣ�������������һ����ȡ��ַ��
	stHead->pPre = stHead;
}

bool SaveInFile(struct Node* stHead)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || 0 >= stHead->iCount)
		return false;
	//���ļ�
	FILE* pFile = NULL;
	FILE* pFile1 = NULL;
	errno_t re = fopen_s(&pFile, "students.dat", "w");	//"w" ֻ����һ�Σ��´ξͽ�������һ�ε�
	errno_t rs = fopen_s(&pFile1, "students1.dat", "w");	//�¶�ʧ�ͱ���
	if (0 != re || 0 != rs || NULL == pFile || NULL == pFile1)
		return false;
	//д���ļ�
	struct Node* pT = stHead->pNext;
	while (pT != stHead)
	{
		fwrite(&(pT->stMe), sizeof(struct Message), 1, pFile);		//����ǰ�������Ľڵ��ѧ����Ϣ���浽�ļ���
		fwrite(&(pT->stMe), sizeof(struct Message), 1, pFile1);
		pT = pT->pNext;
	}
	//�ر��ļ�
	fclose(pFile);
	fclose(pFile1);

	return true;
}
void SaveInFileSucessUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t��            ���浽�ļ��ɹ���           ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);	

}
void SaveInFileFailUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t��             �� �� ʧ �� ��            ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);	
}
void ReadToFile(struct Node* stHead)
{
	//�����Ϸ��Լ��			//�˴��Ͳ�������������ˣ���Ϊ�Ƕ�ȡ����޵���
	if (NULL == stHead)
		return;
	//���ļ�
	FILE* pFile = NULL;
	errno_t ra = fopen_s(&pFile, "students.dat", "r");
	if (0 != ra || NULL == pFile)
		return;
	//��ȡ�ļ�
	struct Message sr;		//��ʱ��¼������
	while (0 != fread(&sr, sizeof(struct Message), 1, pFile))
		Add(stHead, &sr);	//ÿ��ȡһ�飬�͸��������һ���ڵ�
	
	//�ر��ļ�
	fclose(pFile);
}

void LookAll(struct Node* stHead)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || 0 == stHead->iCount)
		return;
	//������ʱָ��
	struct Node* pT = stHead->pNext;
	if (pT == NULL)
		return;
	//ˢ����Ļ,��ӡѧ����Ϣ����ر�ͷ
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t��       ѧ��       ����       �ɼ�      ��\n");
	printf("\t\t\t\t\t��  -----------------------------------  ��\n");
	int hang = 21,
		lie1 = 46,
		lie2 = 60,
		lie3 = 72;
	//��ȡѧ����Ϣ,����ӡ
	//while (pT != stHead)
	//{
	//	GoToXY(hang, 0);					//��ӡ�߿�
	//	printf("\t\t\t\t\t��                                       ��\n");
	//	GoToXY(hang, lie1);					//��ӡѧ�ţ�ע��unsigned int �� %u
	//	printf("%u", pT->stMe.iNumber);
	//	GoToXY(hang, lie2);					//��ӡ����
	//	printf("%s", pT->stMe.cName);
	//	GoToXY(hang, lie3);					//��ӡ�ɼ�
	//	printf("%d", pT->stMe.iSocre);
	//	pT = pT->pNext;
	//	hang++;								//��+1
	//}
	//��ȡѧ����Ϣ,����ӡ����ʦ�ķ�����
	while (pT != stHead)
	{
		//��ʦ�Ĵ������࣬- �� ��ָ���Ҷ��루Ĭ������룩��10 ���޶���������ַ�ֻ����10�ַ���Χ�ڣ�����ֵ�仯�确С���� ������������ ��������ֲ��ᶥ������Ŀո��ñ߿򳬳�ȥ
		//�����ַ��޶�����ô���ֵĴ�С���ͻ�Ӱ���ӡ�������
		printf("\t\t\t\t\t��    %-10u    %-10s  %-3d      ��\n", pT->stMe.iNumber, pT->stMe.cName, pT->stMe.iSocre);
		pT = pT->pNext;
	}
	//��ӡ��β
	//GoToXY(hang, 0);
	printf("\t\t\t\t\t��  -----------------------------------  ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	//�ص�ָ������λ��
	GoToXY(17, 64);
}
void StuNameUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t��          �������֣�                   ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(19, 64);		//���ת���������� ��
}
void LookOne(struct Node* stHead, struct Message* Me)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || NULL == Me || 0 >= stHead->iCount)
		return false;
	//������ʱָ��
	struct Node* pT = stHead->pNext;
	if (pT == NULL)
		return;
	//��ӡѧ����Ϣ����ر�ͷ�����ڲ��ҿ���·�
	GoToXY(21, 0);
	printf("\t\t\t\t\t��       ѧ��       ����       �ɼ�      ��\n");
	printf("\t\t\t\t\t��  -----------------------------------  ��\n");

	int i = 0;	//�������������Ƿ��в鵽
	//ѭ������
	while (pT != stHead)
	{
		if (0 == strcmp(Me->cName, pT->stMe.cName))
		{
			i++;
			printf("\t\t\t\t\t��    %-10u    %-10s  %-3d      ��\n", pT->stMe.iNumber, pT->stMe.cName, pT->stMe.iSocre);
		}
		pT = pT->pNext;
	}

	//û�в鵽��Ϣ�����ӡ��ʾ
	if (i == 0)
		printf("\t\t\t\t\t��            û�и�ѧ����Ϣ����         ��\n");

	//��ӡ��β
	printf("\t\t\t\t\t��  -----------------------------------  ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	//�ص�ָ������λ��
	GoToXY(17, 64);
}
void RangeUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t��    ��Ҫ�����ķ�����Χ��               ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(19, 67);		//���ת��������Χ ��
}
void LookRange(struct Node* stHead, unsigned int iScore1, unsigned int iScore2)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || 0 >= stHead->iCount)
		return false;
	//���a b ��С��ȷ�����(��ʽ1)
	unsigned int Min, Max;
	if (iScore1 >= iScore2)		//���ַ��������ʹ������ʱ�����Ϳ�����
	{
		Min = iScore2;
		Max = iScore1;			
	}
	else
	{
		Min = iScore1;
		Max = iScore2;
	}
	//������ʱָ��
	struct Node* pT = stHead->pNext;
	if (pT == NULL)
		return;
	//��ӡѧ����Ϣ����ر�ͷ�����ڲ��ҿ���·�
	GoToXY(21, 0);
	printf("\t\t\t\t\t��       ѧ��       ����       �ɼ�      ��\n");
	printf("\t\t\t\t\t��  -----------------------------------  ��\n");

	int i = 0;	//�������������Ƿ��в鵽
	//ѭ������
	while (pT != stHead)
	{		
		if (iScore1 <= pT->stMe.iSocre && iScore2 >= pT->stMe.iSocre || iScore1 >= pT->stMe.iSocre && iScore2 <= pT->stMe.iSocre)	//���a b ��С��ȷ�����(��ʽ2)
		{
			i++;
			printf("\t\t\t\t\t��    %-10u    %-10s  %-3u      ��\n", pT->stMe.iNumber, pT->stMe.cName, pT->stMe.iSocre);
		}
		pT = pT->pNext;
	}

	//û�в鵽��Ϣ�����ӡ��ʾ
	if (i == 0)
		printf("\t\t\t\t\t��           û�ж�Ӧѧ����Ϣ����        ��\n");

	//��ӡ��β
	printf("\t\t\t\t\t��  -----------------------------------  ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	//�ص�ָ������λ��
	GoToXY(17, 64);
}

void DeleteNameUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t��          ɾ��ѧ����                   ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(19, 64);
}
void DeleteSucessUI(void)
{
	GoToXY(21, 0);	//��������������һ����Ĳ���
	printf("\t\t\t\t\t��              �ɹ�ɾ������             ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);	//�ص�ָ������λ��
}
void DeleteFailUI(void)
{
	GoToXY(21, 0);
	printf("\t\t\t\t\t��              ɾ��ʧ�ܣ���             ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);
}
bool Delete(struct Node* stHead, struct Message* Me)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || NULL == Me || 0 >= stHead->iCount)
		return false;
	//��ʱָ���¼
	struct Node* pT = stHead->pNext;
	if (NULL == pT)
		return;
	//��¼ɾ��ǰ�Ľڵ���
	unsigned int iCount = stHead->iCount;
	//����ѧ����ɾ��
	while (pT != stHead)
	{
		if (0 == strcmp(Me->cName, pT->stMe.cName))
		{
			//����Ӧ�ڵ���������õ��ͷ�
			struct Node* pP = pT->pPre;	//��¼��Ϊ�˻�ԭpT����pT��������ѭ����ע��˴���pP��¼����pT->pNext ���� pT->pPre �����߼��кܴ�ı䣬�Լ�����
			pT->pNext->pPre = pT->pPre;
			pT->pPre->pNext = pT->pNext;
			stHead->iCount--;
			free(pT);
			//��ԭ������Ҫ����Ҫ����ⲻ��������ɾ�м�ڵ��߼�������Ҫ����ѭ������������
			pT = pP;
		}
		pT = pT->pNext;		//���ֻ��д�������while����������ѭ���ˣ�����ǰ����ȥдif���
	}

	//�����Ƿ���ɾ��ѧ���������ز�ͬ���
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
	printf("\t\t\t\t\t��          �������֣�                   ��\n");
	printf("\t\t\t\t\t��          �޸ķ�����                   ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(19, 64);		//������� ������
}
void ChangeSucessUI(void)
{
	GoToXY(22, 0);	//��������������һ����Ĳ���
	printf("\t\t\t\t\t��              �ɹ��޸ģ���             ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);	//�ص�ָ������λ��
}
void ChangeFailUI(void)
{
	GoToXY(22, 0);	
	printf("\t\t\t\t\t��              �޸�ʧ�ܣ���             ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);	
}
bool Change(struct Node* stHead, struct Message* Me)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || NULL == Me || 0 >= stHead->iCount)
		return false;
	//��ʱ��¼ָ��
	struct Node* pT = stHead->pNext;
	if (NULL == pT)
		return false;

	//ѭ���������Ҳ��޸�
	int iCount = 0;		//���ڼ�¼�޸ĵĴ���
	while (pT != stHead)
	{
		if (0 == strcmp(Me->cName, pT->stMe.cName))
		{
			iCount++;
			pT->stMe.iSocre = Me->iSocre;
		}
		pT = pT->pNext;
	}

	//�����Ƿ��޸Ĺ�����������ֵ
	if (iCount > 0)
		return true;
	else
		return false;
}

void Test(struct Node* stHead)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || 0 >= stHead->iCount)
		return;
	//��ʱ��¼ָ��
	struct Node* pT = stHead->pNext;
	if (NULL == pT)
		return;
	//����
	while (pT != stHead)
	{
		//������������������ɳɼ� %101 �Ͳ���0~100�ķ������������޸�
		pT->stMe.iSocre = (unsigned int)rand() % 101;
		pT = pT->pNext;
	}
}
void TestSucessUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t��              ������ϣ���             ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	GoToXY(17, 64);	//�ص�ָ������λ��
}

void SortOkUI(void)
{
	system("cls");
	ManageMenuUI();
	GoToXY(19, 0);
	printf("\t\t\t\t\t��    ������ϣ��� 3 ���鿴������    ��\n");
	printf("\t\t\t\t\t*******************************************\n");
	CountDown(19, 59, 1000, '3');
}
void SortBySocre(struct Node* stHead)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || 0 >= stHead->iCount)
		return false;
	//ð������
	for (unsigned int i = 0; i < stHead->iCount; i++)				//ð���������ð��stHead->iCount - 1 �μ��ɣ�����10��Ԫ�أ�ǰ9�����ź��ˣ���ô���һ��Ҳȷ����
	{
		//�ڲ�ѭ����һ��ð��
		struct Node* pT = stHead->pNext;
		while (pT->pNext != stHead)
		{
			if (pT->stMe.iSocre < pT->pNext->stMe.iSocre)	//�˴�Ҫ��pT->pNext���Ƚϣ���ѭ������������Ӧ����pT->pNext������pT->pNext == stHead��ʱ���Խ����
			{
				//��ʱ��Ҫ�������ڵ㣨�����ĸı�ڵ�����߻�Ƚ��鷳��
				//��һ�ַ�ʽ���ǽ������ڵ������
				//���ǲ��ú��ߣ���Ҳ��һ��ʼ�ýṹ����Žṹ���Ա��ԭ��
				struct Message Ge;		//��ʱ��¼�õ�
				Ge = pT->stMe;			//C���Խṹ���ܹ��໥��ֵ	
				pT->stMe = pT->pNext->stMe;
				pT->pNext->stMe = Ge;
			}
			pT = pT->pNext;
		}
	}
}
void SortByNumber(struct Node* stHead)
{
	//�����Ϸ��Լ��
	if (NULL == stHead || 0 >= stHead->iCount)
		return false;
	
	//ð������
	for (unsigned int i = 0; i < stHead->iCount; i++)
	{
		//�ڲ�ѭ����һ��ð��
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

