#include <iostream>
#include <cstring>
using namespace std;
int string_to_int(string str){
    //避免字符串是全0
    if(str.find_first_not_of('0') == string::npos)return 0;
    str = str.substr(str.find_first_not_of('0'));
    int a;
    sscanf(str.c_str(),"%d",&a);
    return a;
}
int main(){
    setbuf(stdout, 0);
    string str1,str2;
    cin>>str1>>str2;
    int a = string_to_int(str1);
    int b = string_to_int(str2);
    int c = a+b;
    cout<<c;
    return 0;
}


