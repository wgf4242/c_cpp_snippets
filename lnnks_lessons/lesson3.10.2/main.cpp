
#include<iostream>
using namespace std;
int main(void) {
	int v1 = 1000;
	cout  << v1 - 1500 << endl; // -500

	unsigned short v2 = 1000;
	cout << v2 - 1500 << endl; // -500 unsigned short ����Ϊint
	
	cout << sizeof(3.0 - 2) << endl; // 8 , 3 double 8 Bytes
	cout << sizeof(3.0f - 2LL) << endl; // 4 , 3 float 4 B, ������ʧ
	cout << sizeof((double)1 ) << endl; // 8
	
	
	int v3 = 1.3 + 1.7; // �Զ�(int)(1.3 + 1.7)
	cout << v3 << endl; // 3
	cout << (int)1.3 + (int)1.7 << endl; // 2


	// �͵ȼ����͸���ת��Ϊ�ߵȼ�����,��ͨ����1��������������
	char v4 = -1;
	int x = v4;
	cout << x << "," << hex <<  x << dec << endl;

	// ������תΪ�����ᶪ��С������,������������ı��淶Χ,��Ϊ��δ�����.
	float f = 30.123;
	int t = f;
	cout << t << endl; // ����С�� 30

	float f1 = 30000000000000.00;
	int t1 = f1;
	cout << t1 << endl; // ��ֵ


	return 0;

}