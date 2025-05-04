// 10_SignedDivMul
```
int IntegerMulDiv(int a, int b, int* prod, int* quo, int* rem);
int a = 21, b = 9;
int prod = 0, quo = 0, rem = 0;
int rv;
rv = IntegerMulDiv(a, b, &prod, &quo, &rem);
```

| High Memory |                |      |
| ----------- | -------------- | ---- |
|             | rem            | +24  |
|             | quo            | +20  |
|             | prod           | +16  |
|             | b              | +12  |
|             | a              | +8   |
|             | Return address | +4   |
|             | Old EBP        | EBP  |
| Low Memory  | OLD EBX        | ESP  |