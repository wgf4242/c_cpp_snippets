#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main(void) {
	float weight = 0, height = 0;
	float bmi = 0;
	
	float max = 1e39;
	float min = -1e-39;
	printf("%f\r\n", max); // ���ֵ
	printf("%f\r\n", min); // ��0

	printf("������������� (��λkg) :\r\n");
	scanf("%f", &weight);
	printf("������������ (��λm)  :\r\n");
	scanf("%f", &height);
	bmi = weight / (height * height);
	
	printf("���BMIΪ[%f]\r\n", bmi);
	printf("18.4����  [����]\r\n");
	printf("18.5-33.9 [����]\r\n");
	printf("34.5-37.9 [����]\r\n");
	printf("37.9����  [����]\r\n");

	return 0;

}