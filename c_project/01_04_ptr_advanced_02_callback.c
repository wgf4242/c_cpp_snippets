// https://mp.weixin.qq.com/s/6RO0S68tSHs-WlddZg-PSQ

#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

int Callback_1(int a)   // /< �ص�����1
{
    printf("Hello, this is Callback_1: a = %d \n", a);
    return 0;
}

int Callback_2(int b)  // /< �ص�����2
{
    printf("Hello, this is Callback_2: b = %d \n", b);
    return 0;
}

int Callback_3(int c)   // /< �ص�����3
{
    printf("Hello, this is Callback_3: c = %d \n", c);
    return 0;
}

int Handle(int x, int (*Callback)(int))  // /< ע�������õ��ĺ���ָ�붨��
{
    Callback(x);
}


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/****************************************
 * ����ָ��ṹ��
 ***************************************/
typedef struct _OP {
    float (*p_add)(float, float);

    float (*p_sub)(float, float);

    float (*p_mul)(float, float);

    float (*p_div)(float, float);
} OP;

/****************************************
 * �Ӽ��˳�����
 ***************************************/
float ADD(float a, float b) {
    return a + b;
}

float SUB(float a, float b) {
    return a - b;
}

float MUL(float a, float b) {
    return a * b;
}

float DIV(float a, float b) {
    return a / b;
}

/****************************************
 * ��ʼ������ָ��
 ***************************************/
void init_op(OP *op) {
    op->p_add = ADD;
    op->p_sub = SUB;
    op->p_mul = &MUL;
    op->p_div = &DIV;
}

/****************************************
 * �⺯��
 ***************************************/
float add_sub_mul_div(float a, float b, float (*op_func)(float, float)) {
    return (*op_func)(a, b);
}

int arithmetic() {
    OP *op = (OP *) malloc(sizeof(OP));
    init_op(op);

    /* ֱ��ʹ�ú���ָ����ú��� */
    printf("ADD = %f, SUB = %f, MUL = %f, DIV = %f\n", (op->p_add)(1.3, 2.2), (*op->p_sub)(1.3, 2.2),
           (op->p_mul)(1.3, 2.2), (*op->p_div)(1.3, 2.2));

    /* ���ûص����� */
    printf("ADD = %f, SUB = %f, MUL = %f, DIV = %f\n",
           add_sub_mul_div(1.3, 2.2, ADD),
           add_sub_mul_div(1.3, 2.2, SUB),
           add_sub_mul_div(1.3, 2.2, MUL),
           add_sub_mul_div(1.3, 2.2, DIV));

    return 0;
}
/*

*/
/*********  ����״̬����  *********//*

typedef struct
{
    uint8_t mStatus;
    uint8_t (* Funtion)(void); //����ָ�����ʽ
} M26_WorkStatus_TypeDef;   //M26�Ĺ���״̬���ϵ��ú���


*/
/**********************************************
** >M26����״̬���Ϻ���
***********************************************//*

M26_WorkStatus_TypeDef M26_WorkStatus_Tab[] =
        {
                {GPRS_NETWORK_CLOSE,  M26_PWRKEY_Off  },    //ģ��ػ�
                {GPRS_NETWORK_OPEN,  M26_PWRKEY_On  },      //ģ�鿪��
                {GPRS_NETWORK_Start,   M26_Work_Init  },    //�ܽų�ʼ��
                {GPRS_NETWORK_CONF,  M26_NET_Config  },     //ATָ������
                {GPRS_NETWORK_LINK_CTC,  M26_LINK_CTC  },   //���ӵ�������
                {GPRS_NETWORK_WAIT_CTC, M26_WAIT_CTC  },    //�ȴ��������Ļظ�
                {GPRS_NETWORK_LINK_FEM, M26_LINK_FEM  },    //����ǰ�û�
                {GPRS_NETWORK_WAIT_FEM, M26_WAIT_FEM  },    //�ȴ�ǰ�û��ظ�
                {GPRS_NETWORK_COMM,  M26_COMM   },          //��������
                {GPRS_NETWORK_WAIT_Sig,  M26_WAIT_Sig  },   //�ȴ��źŻظ�
                {GPRS_NETWORK_GetSignal,  M26_GetSignal  }, //��ȡ�ź�ֵ
                {GPRS_NETWORK_RESTART,  M26_RESET   },      //ģ������
        }
*/
/**********************************************
** >M26ģ�鹤��״̬�������ε��������12������
***********************************************//*

uint8_t M26_WorkStatus_Call(uint8_t Start)
{
    uint8_t i = 0;
    for(i = 0; i < 12; i++)
    {
        if(Start == M26_WorkStatus_Tab[i].mStatus)
        {
            return M26_WorkStatus_Tab[i].Funtion();
        }
    }
    return 0;
}
*/

int main() {
    // 1. �ص�����
    // Handle(4, Callback_1);
    // Handle(5, Callback_2);
    // Handle(6, Callback_3);

    // 2.��������
    arithmetic();

    // 3.�ص�����ʵ�� ����ģʽ ״̬��
    // M26ģ�鹤��״̬�������ε��������12������
    // M26_WorkStatus_Call(xx)
    return 0;
}