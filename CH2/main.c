#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000

// to convert a hexadecimal number to decimal form
double htoi(char hex[MAX], int len)
{
    int base = 16;
    double decimal = 0;
    double n = 0;

    for(int i = (len - 1); i >= 0; i--)
    {
        if(hex[i] >= '0' && hex[i] <= '9') decimal += pow(base, n) * (hex[i] - '0');
        else if(hex[i] >= 'A' && hex[i] <= 'Z') decimal += pow(base, n) * (10 + hex[i] - 'A');
        n++;
    }

    return decimal;
}

// creates string s1 that has characters not found in s2
void squeeze(char s1[MAX], char s2[MAX])
{
        int pos = 0;

        for(int i = 0; i < strlen(s1); i++)
        {
            // flag wether to add unique char
            bool add = true;
            // checking if unique
            for(int j = 0; j < strlen(s2); j++) if(s1[i] == s2[j]) add = false;
            // adding character
            if(add) s1[pos++] = s1[i];    
        }

        // cut off unused characters
        s1[pos] = '\0';
}

// returns the index of the first char s1 and s2 have in common
int any(char s1[MAX], char s2[MAX])
{
    for(int i = 0; i < strlen(s1); i++)
        for(int j = 0; j < strlen(s2); j++) 
            if(s1[i] == s2[j]) return i;

    return -1;
}

// to copy n bits to the right of p of y to x
unsigned setbits(int x, int p, int n, int y)
{
	// set bits to be change to 0
	// copy by ORing with y and x
	return ((x & ~(~(~0 << n) << ((p + 1) - n))) | (y & (~(~0 << n) << ((p + 1) - n))));
}

// inverse n bits to the right of pos p
unsigned invert(int x, int p, int n)
{
	// & w ~x to extract the inverse portion we want
	int k = (~(~0 << n)) << ((p + 1) - n);
	// & w x to get the non inversed portion
	int l = (~(~(~0 << n))) << ((p + 1) - n);

	return ((~x & k) | (x & l));
}

// finds the word length of the machine
int wordlength(void)
{
	int i;
	unsigned v = (unsigned) ~0;
	// keep shifting right until the value is 0 111 -> 011 -> 001 -> 000 needed 3 shifts, so word length is 3!
	for(i = 0; (v = v >> 1) > 0; i++)
		;
	return i;
}

// rotate n bits from right shift
unsigned rotate(int x, int n)
{
	// position of msb thats lost in right shift
	int p = (n - 1);
	// reverse order of extracted p bits (ie. x = 110 101 111, then k is 111 000 000)
	int k = ((~(~0 << n) & x) << (wordlength() - p));
	// ORing the 2 will make it where the p bits removed from n shifts are at the front of x:
	// 000 110 101
	// 111 000 000 
	// ------------
	// 111 110 101 gives us the correct answer!
	return ((x >> n) | k);
}

// count the number of '1' bits in x
int countbits(unsigned x)
{
    int ans = 0;
    unsigned k = 1;

    while(x != 0)
    {
        // if theres a '1' in the lsb, then inc the number of 1 bits we have
        if((x & k) == k) ans++;
        // lose the lsb
        x >>= 1; 
    }

    return ans;
}

// converts every uppercase letter to a lowercase one
void lower(char arr[MAX])
{
    for(int i = 0; i < strlen(arr); i++) arr[i] = (arr[i] >= 65 && arr[i] <= 90) ? arr[i] + 32 : arr[i];
}

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
    // double (*e2_2)(char[MAX], int) = htoi;
    // void (*e2_4)(char[MAX], char[MAX]) = squeeze;
    // int (*e2_5)(char[MAX], char[MAX]) = any;
    // unsigned (*e2_6)(int, int, int, int) = setbits;
    // unsigned (*e2_7)(int, int, int) = invert;
    // unsigned (*e2_8)(int, int) = rotate;
    // int (*e2_9)(unsigned) = countbits;
    // void (*e2_10)(char[MAX]) = lower;
    // void (*e3_2)(char[MAX]) = replaceEscapeSequence;
    // void (*e3_3)(char[MAX]) = expand;
    // void (*e3_5)(int, int, char[MAX]) = itob;
    // void (*e3_6)(int, int) = itoa;
    // e2_2("", 0);
    // e2_4("", "");
    // e2_5("", "");
    // e2_6(0,0,0,0);
    // e2_7(0, 0, 0);
    // e2_8(0,0);
    // e2_9(0);
    // e2_10("");
    // e3_2("");
    // e3_3("a-z0-9");
    // e3_5(729, 16, "");
    // e3_6(123, 6);
    return 0;
}
