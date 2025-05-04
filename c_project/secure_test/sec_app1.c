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

	//余客宝===>余额账户===>银行卡
	printf("您当前余客宝账户余额为[%.2f]\r\n您当前银行卡余额为[%.2f]", Yukebao, BankCard);
	printf("请输入您要提取到余额账户的金额:\r\n");
	// 输入nan出问题了  nan > Yukebao == false,  nan < Yukebao == false
	scanf("%f", &OutMoeny);
	if (OutMoeny > Yukebao)
	{
		printf("提取到余额失败!\r\n余客宝账户余额不足!\r\n");
		return 1;
	}

	Yukebao = Yukebao - OutMoeny;
	YuE = YuE + OutMoeny;

	printf("提取到余额成功!\r\n请输入要提取到银行卡的金额:\r\n");
	scanf("%f", &OutMoeny);
	if (OutMoeny > YuE)
	{
		printf("提取到银行卡失败!\r\n余额账户不足!");
		return 1;
	}

	YuE -= OutMoeny;
	BankCard += OutMoeny;
	printf("恭喜!取现[%.2f]成功,银行卡余额为[%.2f]", OutMoeny, BankCard);
	return 1;

}