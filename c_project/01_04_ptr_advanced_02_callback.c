// https://mp.weixin.qq.com/s/6RO0S68tSHs-WlddZg-PSQ

#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

int Callback_1(int a)   // /< 回调函数1
{
    printf("Hello, this is Callback_1: a = %d \n", a);
    return 0;
}

int Callback_2(int b)  // /< 回调函数2
{
    printf("Hello, this is Callback_2: b = %d \n", b);
    return 0;
}

int Callback_3(int c)   // /< 回调函数3
{
    printf("Hello, this is Callback_3: c = %d \n", c);
    return 0;
}

int Handle(int x, int (*Callback)(int))  // /< 注意这里用到的函数指针定义
{
    Callback(x);
}


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/****************************************
 * 函数指针结构体
 ***************************************/
typedef struct _OP {
    float (*p_add)(float, float);

    float (*p_sub)(float, float);

    float (*p_mul)(float, float);

    float (*p_div)(float, float);
} OP;

/****************************************
 * 加减乘除函数
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
 * 初始化函数指针
 ***************************************/
void init_op(OP *op) {
    op->p_add = ADD;
    op->p_sub = SUB;
    op->p_mul = &MUL;
    op->p_div = &DIV;
}

/****************************************
 * 库函数
 ***************************************/
float add_sub_mul_div(float a, float b, float (*op_func)(float, float)) {
    return (*op_func)(a, b);
}

int arithmetic() {
    OP *op = (OP *) malloc(sizeof(OP));
    init_op(op);

    /* 直接使用函数指针调用函数 */
    printf("ADD = %f, SUB = %f, MUL = %f, DIV = %f\n", (op->p_add)(1.3, 2.2), (*op->p_sub)(1.3, 2.2),
           (op->p_mul)(1.3, 2.2), (*op->p_div)(1.3, 2.2));

    /* 调用回调函数 */
    printf("ADD = %f, SUB = %f, MUL = %f, DIV = %f\n",
           add_sub_mul_div(1.3, 2.2, ADD),
           add_sub_mul_div(1.3, 2.2, SUB),
           add_sub_mul_div(1.3, 2.2, MUL),
           add_sub_mul_div(1.3, 2.2, DIV));

    return 0;
}
/*

*/
/*********  工作状态处理  *********//*

typedef struct
{
    uint8_t mStatus;
    uint8_t (* Funtion)(void); //函数指针的形式
} M26_WorkStatus_TypeDef;   //M26的工作状态集合调用函数


*/
/**********************************************
** >M26工作状态集合函数
***********************************************//*

M26_WorkStatus_TypeDef M26_WorkStatus_Tab[] =
        {
                {GPRS_NETWORK_CLOSE,  M26_PWRKEY_Off  },    //模块关机
                {GPRS_NETWORK_OPEN,  M26_PWRKEY_On  },      //模块开机
                {GPRS_NETWORK_Start,   M26_Work_Init  },    //管脚初始化
                {GPRS_NETWORK_CONF,  M26_NET_Config  },     //AT指令配置
                {GPRS_NETWORK_LINK_CTC,  M26_LINK_CTC  },   //连接调度中心
                {GPRS_NETWORK_WAIT_CTC, M26_WAIT_CTC  },    //等待调度中心回复
                {GPRS_NETWORK_LINK_FEM, M26_LINK_FEM  },    //连接前置机
                {GPRS_NETWORK_WAIT_FEM, M26_WAIT_FEM  },    //等待前置机回复
                {GPRS_NETWORK_COMM,  M26_COMM   },          //正常工作
                {GPRS_NETWORK_WAIT_Sig,  M26_WAIT_Sig  },   //等待信号回复
                {GPRS_NETWORK_GetSignal,  M26_GetSignal  }, //获取信号值
                {GPRS_NETWORK_RESTART,  M26_RESET   },      //模块重启
        }
*/
/**********************************************
** >M26模块工作状态机，依次调用里面的12个函数
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
    // 1. 回调函数
    // Handle(4, Callback_1);
    // Handle(5, Callback_2);
    // Handle(6, Callback_3);

    // 2.四则运算
    arithmetic();

    // 3.回调函数实例 策略模式 状态机
    // M26模块工作状态机，依次调用里面的12个函数
    // M26_WorkStatus_Call(xx)
    return 0;
}