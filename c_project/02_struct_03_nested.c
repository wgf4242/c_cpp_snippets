struct complex
{
    int imag;
    float real;
};

struct number
{
    struct complex comp;
    int integers;
} num1, num2;
//Suppose, you want to set imag of num2 variable to 11. Here's how you can do it:

num2.comp.imag = 11;