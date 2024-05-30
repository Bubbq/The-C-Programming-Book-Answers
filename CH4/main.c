#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 1000

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

// returns the pos of the rightmost t in s
int strrindex(char str[MAX], char t[MAX])
{
    reverse(t);
    for(int i = (strlen(str) - 1); i >= 0; i--)
    {
        int sim = 0;
        // iterates while we're in bounds and characters match
        for(int j = 0, n = i; (n >= 0) && (str[n] == t[j]) && (j < strlen(t)); j++, n--) sim++;
        
        if(sim == strlen(t)) return (i - (strlen(t) - 1));
    }

    // if we don't have t in s
    return -1;
}

// converts a string to float equivalent -123.45e-2
float atof(char str[MAX])
{
    float val = 0.00, pwr = 0.10;
    int i = 0, e = 0, sign = 0;

    // check if number is negative or positive
    if(str[i] == '-')
    {
        sign = -1;
        i++;
    }

    else sign = 1;

    // get the numbers after the sign
    for(; isdigit(str[i]); i++) val = (val * 10.00) + (str[i] - '0');

    // getting decimals, if any
    if(str[i] == '.') i++;
    else return (val * sign);

    // adding decimal values
    for(; isdigit(str[i]); pwr /= 10, i++) val += (pwr * (str[i] - '0'));

    // scientific rep. if any
    if(str[i] == 'e' || str[i] == 'E') i++;
    else return (val * sign);

    // getting sign
    pwr = (str[i] == '-') ? 0.10 : 10.00; i++;

    // how may times we need to multiply val w pwr
    for(; isdigit(str[i]); i++) e = (e * 10) + (str[i] - '0');

    for(int i = 0; i < e; i++) val *= pwr;

    return val;
}

int main()
{
    // int (*e4_1)(char[MAX], char[MAX]) = strrindex;
    // float (*e4_2)(char[MAX]) = atof;
    // e4_1("", "");
    // e4_2("");

    return 0;
}