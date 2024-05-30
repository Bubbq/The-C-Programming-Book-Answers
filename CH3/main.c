#include <stdio.h>
#include <string.h>
#define MAX 1024

// converts all \n and \ts to their char literal
void replaceEscapeSequence(char input[MAX])
{
    char ans[MAX];
    int j = 0;
    for(int i = 0; i < strlen(input); i++)
    {
        switch (input[i])
        {
            case '\n': ans[j++] = '\\'; ans[j++] = 'n'; break;
            case '\t': ans[j++] = '\\'; ans[j++] = 't'; break;
            default:
                ans[j++] = input[i];
        }
    }

    ans[j] = '\0';
    printf("%s\n", ans);    
}

int fillgaps(char arr[MAX], int idx, int fc, int lc)
{
    for(int i = fc; i < (lc + 1); i++) arr[idx++] = (char)i;
    return idx;
}

// expands the for x..y by filling the gaps between x and y and printing out the result
void expand(char input[MAX])
{
    int d1 = -1;
    int d2 = -1;    
    int idx = 0;
    char ans[MAX];

    for(int i = 0; i < strlen(input); i++)
    {
        // get first char
        if((d1 == -1) && (d2 == -1)) d1 = input[i];

        else if(input[i] == '-') continue;

        else d2 = input[i];

        // filling the gap between x..y
        if((d1 > -1) && (d2 > -1))
        {
            idx = fillgaps(ans, idx, d1, d2);
            d1 = d2 = -1;
        }
    }

    ans[idx] = '\0';
    printf("%s\n", ans);
}

// reverses the content of a c-str
void reverse(char str[MAX])
{
    // len of str (0-indexed)
    int n = strlen(str) - 1;

    for(int i = 0; i < ((n + 1) / 2); i++)
    {
        char tmp = str[i];
        str[i] = str[n - i];
        str[n - i] = tmp;
    }
}

// convert any int 'k' to a number with base 'b'
void itob(int k, int b, char ans[MAX])
{
    int idx = 0;

    while(k != 0)
    {
        int rem = (k % b);
        char c;
        
        // hexadecimal case
        if((rem > 9) && (b == 16))
        {
            switch (rem) 
            {
                case 10: c = 'A'; break;
                case 11: c = 'B'; break;
                case 12: c = 'C'; break;
                case 13: c = 'D'; break;
                case 14: c = 'E'; break;
                case 15: c = 'F'; break;
            }
        }

        // other case(s)
        else c =  rem + '0';

        // store the remainder into ans string
        ans[idx++] = c;
        
        // divide k by base
        k /= b;
    }

    ans[idx] = '\0';
    reverse(ans);
    printf("%s\n", ans);
}

// convert some int 'k' to a c-str with padding 'p'
void itoa(int k, int p)
{
    char str[MAX];
    int idx = 0;

    while(k != 0)
    {
        // get last digit and append to ans str
        str[idx++] = (k % 10) + '0';
        // divide to get next number
        k /= 10;
    }

    // adding remaining space(s)
    int rsp = ((p - idx) > 0) ? (p - idx) : 0;
    for(int i = 0; i < rsp; i++) str[idx++] = ' ';

    reverse(str);

    str[idx] = '\0';
    printf("%s \n", str);
}

int main()
{
    // void (*e3_2)(char[MAX]) = replaceEscapeSequence;
    // void (*e3_3)(char[MAX]) = expand;
    // void (*e3_5)(int, int, char[MAX]) = itob;
    // void (*e3_6)(int, int) = itoa;
    // e3_2("");
    // e3_3("a-z0-9");
    // e3_5(729, 16, "");
    // e3_6(123, 6);

    return 0;
}