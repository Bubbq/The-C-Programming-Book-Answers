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
    // e2_2("", 0);
    // e2_4("", "");
    // e2_5("", "");
    // e2_6(0,0,0,0);
    // e2_7(0, 0, 0);
    // e2_8(0,0);
    // e2_9(0);
    // e2_10("");
    
    return 0;
}
