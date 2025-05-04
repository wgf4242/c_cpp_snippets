#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main(void) {
	float weight = 0, height = 0;
	float bmi = 0;
	
	float max = 1e39;
	float min = -1e-39;
	printf("%f\r\n", max); // 最大值
	printf("%f\r\n", min); // 负0

	printf("请输入你的体重 (单位kg) :\r\n");
	scanf("%f", &weight);
	printf("请输入你的身高 (单位m)  :\r\n");
	scanf("%f", &height);
	bmi = weight / (height * height);
	
	printf("你的BMI为[%f]\r\n", bmi);
	printf("18.4以下  [消瘦]\r\n");
	printf("18.5-33.9 [正常]\r\n");
	printf("34.5-37.9 [超重]\r\n");
	printf("37.9以上  [肥胖]\r\n");

	return 0;

}