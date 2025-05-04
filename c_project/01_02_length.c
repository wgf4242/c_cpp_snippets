# include <stdio.h>
int main(void)
{
    int a[10] = {0};
    printf("bytes³¤¶È sizeof(a) = %d\n", sizeof(a));
    int cnt = sizeof(a) / sizeof(a[0]);
    printf("°´int cnt = %d\n", cnt);
    return 0;
}