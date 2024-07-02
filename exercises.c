#include <stdio.h>
#define CHAR_LIMIT 1024
// Chapter 1 - Introduction
void e1_1() { printf("Hello World!"); }
void e1_2()
{
    int i = 1;
    char c = 'a';
    char* s = "a";
    float f = 1.0f;
    printf("%d, %c, %s, %.3f", i, c, s, f);
}
void e1_3(float l, float u, int k)
{
    printf("F TO C \n");
    for(; l<=u; l += k) printf("%.3f\t%.3f\n", l, ((l - 32) * ( 5.0f / 9 ))); 
}
void e1_4(float l, float u, int k)
{
    printf("C TO F \n");
    for(; l <= u; l += k) printf("%.3f\t%.3f\n", l, ((l * (9.0f / 5)) + 32));
}
void e1_6()
{
    int c = getchar();
    printf("%d\n", c != EOF);
}
void e1_7() { printf("%d\n", EOF); }
void e1_8()
{
    int c;
    int nb = 0;
    int nt = 0;
    int nl = 0;

    while((c = getchar()) != EOF)
    {
        if(c == ' ') nb++;
        else if(c == '\t') nt++;
        else if(c == '\n') nl++;
    }

    printf("you've entered %d blanks, %d tabs, and %d lines \n", nb, nt, nl);
}
void e1_9()
{
    int c;
    int lastc;
    while((c = getchar()) != EOF)
    {
        if((c != ' ') || ((c == ' ') && (lastc != ' '))) putchar(c);
        lastc = c;
    }
}
void e1_10()
{
    int c;
    while((c = getchar()) != EOF)
    {
        switch (c)
        {
            case ' ': printf("\\b"); break;
            case '\t': printf("\\t"); break;
            case '\\': printf("\\\\"); break;
            default: putchar(c);
        }
    }
}

#define IN 1
#define OUT 0

void e1_12()
{
    int state = OUT;
    int c;
    while((c = getchar()) != EOF)
    {
        if((c == ' ' || (c == '\t') || (c == '\n'))) state = OUT;

        else if(state == OUT)
        {
            putchar('\n');
            state = IN;
        }

        if (state == IN) putchar(c);
    }
}

int main()
{
    // e1_1();
    // e1_2();
    // e1_3(0, 300, 20);
    // e1_4(0, 30, 1);
    /* e1_5 is same as e1_3 and 4 just swap values of l and u params!*/
    // e1_6();
    // e1_7();
    // e1_8();
    // e1_9();
    // e1_10();
    /*e1_11 was not really a coding question*/
    // e1_12();
    return 0;
}