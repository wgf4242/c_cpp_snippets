// https://zhuanlan.zhihu.com/p/663587156
// VStudio »ò g++ -fdump-lang-class main.cpp


#include <iostream>
using namespace std;

class base
{
private:
   char c;
   int i = 2;
   float f;
   double d;

public:
   virtual void fun()
   {
   }

   int getnum()
   {
       return i;
   }
};


class derive : public base
{
private:
   int j = 3;
};


int main()
{
   cout << sizeof(base) << endl;
   cout << sizeof(derive) << endl;
   base b;
   int* p1 = (int*)&b;
   cout << "Address of vfptr in base: " << p1 << endl;
   derive d;
   int* p2 = (int*)&d;
   cout << "Address of vfptr in derive: " << p2 << endl;
   printf("Address of fun() in base: %p\n", &base::fun);
   printf("Address of fun() in derive: %p\n", &derive::fun);
}