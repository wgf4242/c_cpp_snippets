// https://mp.weixin.qq.com/s/6RO0S68tSHs-WlddZg-PSQ

#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

// ����ú���ָ����ú���
void ptr_run_func() {
    int Func(int x);   /*����һ������*/
    int (*p)(int x);  /*����һ������ָ��*/
    p = Func;          /*��Func�������׵�ַ����ָ�����p*/
    p = &Func;         /*��Func�������׵�ַ����ָ�����p*/
}

int Max(int x, int y)  //����Max����
{
    int z;
    if (x > y) {
        z = x;
    } else {
        z = y;
    }
    return z;
}

void ptr_run_func2() {
    int (*p)(int, int);  //����һ������ָ��
    int a, b, c;
    p = Max;  //�Ѻ���Max����ָ�����p, ʹpָ��Max����
    /*
     p = Max���Ըĳ� p = &Max
     c = (*p)(a, b) ���Ըĳ� c = p(a, b)
    */
    printf("please enter a and b:");
    scanf("%d%d", &a, &b);
    c = (*p)(a, b);  //ͨ������ָ�����Max����
    printf("a = %d\nb = %d\nmax = %d\n", a, b, c);
}

typedef void(*FunType)(int);

//ǰ��һ��typedef�ؼ��֣������Ͷ���һ����ΪFunType����ָ�����ͣ�������һ��FunType������
//��ʽͬ typedef int* PINT;
void callFun(FunType fp, int x) {
    fp(x);//ͨ��fp��ָ��ִ�д��ݽ����ĺ�����ע��fp��ָ�ĺ�����һ������
}

void myFun(int x) {
    printf("myFun: %d\n", x);
}

void hisFun(int x) {
    printf("hisFun: %d\n", x);
}

void herFun(int x) {
    printf("herFun: %d\n", x);
}

void (* func5(int, int, float ))(int, int)
{
}
int main(void) {
    // 1. ����ú���ָ����ú���
    // ptr_run_func();
    // ptr_run_func2();

    // 3. ����ָ����Ϊĳ�������Ĳ���
    callFun(myFun, 100);//���뺯��ָ�볣������Ϊ�ص�����
    callFun(hisFun, 200);
    callFun(herFun, 300);

    // 4. ����ָ����Ϊ������������
    // func5

    // 5. ����ָ������
    /* ����1 */
    void (*func_array_1[5])(int, int, float);

    /* ����2 */
    typedef void (*p_func_array)(int, int, float);
    p_func_array func_array_2[5];

    return 0;
}
