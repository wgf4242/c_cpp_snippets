#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(void)
{
	float BankCard = 100;
	float Yukebao = 10000.0f;
	float YuE = 0.0f;
	float OutMoeny;
	float a = 0.0f;

	//scanf("%f", &a);
	//printf("%f\n", a);

	//��ͱ�===>����˻�===>���п�
	printf("����ǰ��ͱ��˻����Ϊ[%.2f]\r\n����ǰ���п����Ϊ[%.2f]", Yukebao, BankCard);
	printf("��������Ҫ��ȡ������˻��Ľ��:\r\n");
	// ����nan��������  nan > Yukebao == false,  nan < Yukebao == false
	scanf("%f", &OutMoeny);
	if (OutMoeny > Yukebao)
	{
		printf("��ȡ�����ʧ��!\r\n��ͱ��˻�����!\r\n");
		return 1;
	}

	Yukebao = Yukebao - OutMoeny;
	YuE = YuE + OutMoeny;

	printf("��ȡ�����ɹ�!\r\n������Ҫ��ȡ�����п��Ľ��:\r\n");
	scanf("%f", &OutMoeny);
	if (OutMoeny > YuE)
	{
		printf("��ȡ�����п�ʧ��!\r\n����˻�����!");
		return 1;
	}

	YuE -= OutMoeny;
	BankCard += OutMoeny;
	printf("��ϲ!ȡ��[%.2f]�ɹ�,���п����Ϊ[%.2f]", OutMoeny, BankCard);
	return 1;

}