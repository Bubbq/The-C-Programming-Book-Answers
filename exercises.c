#include <math.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define LIMIT 10

// Commonly used functions //

int readLine(char line[LIMIT])
{
    int c;
    int i = 0;
    int size = 0;

    while((c = getchar()) != '\n')
    {
        size++;
        if(i < LIMIT) line[i++] = c;
    }

    line[(i < LIMIT) ? i : LIMIT] = '\0';
    return size;
}

void cpystr(char src[LIMIT], char dst[LIMIT])
{
    int i = 0;
    
    for(; (src[i] != '\0'); i++) dst[i] = src[i];
    dst[i] = '\0';
}

void reverse(char str[LIMIT])
{
    int n = strlen(str) - 1;
    for(int i = 0; i < ((n + 1) / 2); i++)
    {
        char temp = str[i];
        str[i] = str[n - i];
        str[n - i] = temp;
    }
}

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

#define MAX_LEN 100

void e1_13()
{
    int c;
    int nc = 0;
    int state = OUT;
    int frqList[MAX_LEN] = { 0 };

    while((c = getchar()) != EOF)
    {
        if((c == ' ') || (c == '\n') || (c == '\t'))
        {
            if(state == IN)
            {
                frqList[nc - 1]++;
                nc = 0;
            }
            state = OUT;
        }

        else
        {
            nc++;
            state = IN;
        }
    }

    printf("\nNUMBER OF CHARS FREQUENCY HISTOGRAM\n");

    for(int i = 0; i < MAX_LEN; i++)
    {
        if(frqList[i] > 0)
        {
            printf("%d ", (i + 1));
            for(int j = 0; j < frqList[i]; j++) printf("%c", '|');
            printf("\n");
        }
    }
}

#define ASCII 128

void e1_14()
{
    int freqList[ASCII] = { 0 };
    int c;

    while((c = getchar()) != EOF) freqList[c]++;

    printf("\nCHARACTER FREQUENCY HISTOGRAM\n");

    for(int i = 0; i < ASCII; i++)
    {
        printf("%c ", (char)i);
        for(int j = 0; j < freqList[i]; j++) printf("%c", '|');
        printf("\n");
    }
}

void e1_16()
{
    int length;
    char line[LIMIT];

    int max = 0;
    char longestLine[LIMIT];

    while((length = readLine(line)) > 0)
    {
        if(length > max)
        {
            max = length;
            cpystr(line, longestLine);
        }
    }

    if(max > 0) printf("The longest line was \"%s\" and is %d characters long!", longestLine, max);
}

void e1_17(int printlen)
{
    int len;
    char line[LIMIT];

    while((len = readLine(line)) > 0) if(len > printlen) printf("\"%s\" has more than %d characters\n", line, printlen);
}

void e1_18()
{
    int len;
    char line[LIMIT];

    while((len = readLine(line)) > 0)
    {
        int scnt = 0;
        int tcnt = 0;
        char lc = '\0';
        
        int idx = 0;
        char fline[LIMIT];

        for(int i = 0; i < len; i++)
        {
            if(line[i] == ' ')
            {
                scnt++;
                if(lc != ' ') fline[idx++] = ' ';
            }
            else if(line[i] == '\t')
            {
                tcnt++;
                if(lc != '\t') fline[idx++] = '\t';
            }
            else fline[idx++] = line[i];

            lc = line[i];
        }

        fline[idx] = '\0';
        if((scnt != len) && (tcnt != len)) printf("\"%s\" is the formatted string\n", fline);
    }
}

void e1_19()
{
    int len;
    char line[LIMIT];

    while((len = readLine(line) > 0))
    {
        reverse(line);
        printf("\"%s\" is the reverse\n", line);
    }
}

# define TAB 8

void e1_20()
{
    int c;
    int pos = 1;
    
    while((c = getchar()) != EOF)
    {
        if(c == '\t')
        {
            int nb = TAB - ((pos - 1) % TAB);
            while(nb > 0)
            {
                putchar(' ');
                nb--;
                pos++;
            }
        }

        else if(c == '\n')
        {
            putchar(c); 
            pos = 1;
        }

        else
        {
            putchar(c);
            pos++;
        }
    }
}

void e_21(){}
void e_22(){}
void e_23(){}
void e_24(){}

// Chapter 2 - Types, Operators, and Expressions

void e2_1()
{
    printf("char: %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("short: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("int: %d to %d\n", INT_MIN, INT_MAX);
}

void e2_2()
{
    bool iterate = true;
    int i = 0;
    int c;

    while(iterate)
    {
        if(i >= LIMIT - 1) iterate = false;
        
        c = getchar();
        if(c == '\n') iterate = false;
        else if(c == EOF) iterate = false;
    }
}

int e2_3(const char* hex)
{
    int sum = 0;
    for(int i = 0; i < strlen(hex); i++) sum += (hex[i] - '0') * (pow(16, (strlen(hex)) - (i + 1)));
    return sum;
}

void e2_4(char s1[LIMIT], const char* s2)
{
    int j = 0;
    
    for(int i = 0; i < strlen(s1); i++)
    {
        bool add = true;
        for(int k = 0; k < strlen(s2); k++) if(s1[i] == s2[k]) add = false;

        if(add) s1[j++] = s1[i];
    }

    s1[j] = '\0';
    printf("%s\n", s1);
}

int e2_5(const char* s1, const char* s2)
{
    for(int i = 0; i < strlen(s1); i++)
    {
        for(int j = 0; j < strlen(s2); j++)  if(s1[i] == s2[j]) return i;
    }

    return -1;
}

unsigned e2_6(int x, int y, int n,  int p)
{
    // clears pos p to p + n in x
    unsigned l = ~((~(~0 << n)) << ((p + 1) - n));

    // clears everything execpt bits 0 to n
    unsigned k = ~(~0 << n);

    return (x & l) | ((y & k) << ((p + 1) - n)); 
}

unsigned e2_7(int x, int p, int n)
{
    // extracts the portion we want to inverse 
    unsigned k = ~0 << p;

    // return the x with range p to p + n empty, and OR it with p to p + n inversed, retaining all other bits
    return ((x & ~k) | (~(x & k) & k));
}

// number of bits in unsigned int
#define WORDLENGTH 32

unsigned e2_8(int x, int n)
{
    unsigned k = ~0 >> (WORDLENGTH - n);

    return ((x >> n) | (x & k) << (WORDLENGTH - n));
}

int e2_9(int x)
{
    int count = 0;
    for(unsigned int one = 1; x != 0; x >>= 1) if((x & one) == one) count++;
    return count;
}

void e2_10(char word[LIMIT])
{
    for(int i = 0; i < strlen(word); i++) word[i] += ((word[i] >= 65) && (word[i] <= 90)) ? 32 : 0;
}

// Chapter 3 - Control Flow

int e3_1(int list[LIMIT], int x, int n)
{
    int low = 0; 
    int high = n - 1;
    int mid = (high + low) / 2;

    while(low <= high && (x != list[mid]))
    {
        if(x > list[mid]) low = mid + 1;
        else high = mid - 1;
    }

    if(x == list[mid]) return mid;
    else return -1;
}

void e3_2(const char* s, char t[LIMIT])
{
    int j = 0;
    for(int i = 0; i < strlen(s); i++)
    {
        switch(s[i])
        {
            case '\n': t[j++] = '\\'; t[j++] = 'n'; break;
            case '\t': t[j++] = '\\'; t[j++] = 't'; break;
            default:
                t[j++] = s[i];
        }   
    }
}

void e3_3(const char* s1, char s2[LIMIT])
{
    // read a-z as a...z 0-9 the same way, and leading and trailing '-' taken literally
    int l = -1;
    int r = -1;    
    int idx = 0;
    
    for(int i = 0; i < strlen(s1); i++)
    {
        if((s1[i] == '-') && ((l < 0) && (r < 0))) s2[idx++] = s1[i];
        else
        {
            if(l < 0) l = s1[i];
            else if((r < 0) && (s1[i - 1] == '-')) r = s1[i];       
            
            if((l > 0) && (r > 0))
            {
                for(int j = l; j <= r; j++) s2[idx++] = (char)j; 
                l = r = -1;
            }
        } 
    }
}

#define abs(x) (x < 0) ? -(x) : (x)

void e3_4(int i, char s[LIMIT])
{
    bool negative = i < 0;
    int idx = 0;
    i = abs(i);

    for(int r = i % 10; i != 0;  (i/= 10), r = (i % 10)) s[idx++] = (r + '0');
    if(negative) s[idx++] = '-';
    s[idx] = '\0';
    reverse(s);
}

void e3_5(int i, int b, char s[LIMIT])
{
    bool neagtive = i < 0;
    int idx = 0;
    i = abs(i);

    for(int r = (i % b); (i > 0); (i /= b), r = (i % b)) s[idx++] = (r + '0');
    if(neagtive) s[idx++] = '-';
    s[idx] = '\0';
    reverse(s);
}

void e3_6(int k, int p, char s[LIMIT])
{
    bool neagtive = k < 0;
    int idx = 0;
    k = abs(k);

    for(int r = k % 10; k > 0; (k /= 10), r = (k % 10)) s[idx++] = (r + '0');

    int rsp = ((p - idx) > 0) ? (p - idx) : 0;
    for(; rsp > 0; rsp--) s[idx++] = '0';
    if(neagtive) s[idx++] = '-';
    reverse(s);
    s[idx] = '\0';
}

// Chapter 4 - Functions and Program Structure

int e4_1(const char* s, const char* t)
{
    int n = strlen(t) - 1;
    
    for(int i = (strlen(s) - 1); i >= 0; i--)
    {
        int c_match = 0;

        for(int j = n, k = i; (j >= 0) && (k >= 0); j--, k--)
        {
            if(s[k] == t[j]) c_match++;
        }

        if(c_match == strlen(t)) return (i - n);
    }

    return -1;
}

float e4_2(const char* s)
{
    float value = 0.0f;
    int i = 0;

    // normal numbers
    for(; i < strlen(s) && isdigit(s[i]); i++)
    {
        value *= 10;
        value += (s[i] - '0');
    }

    // floating point
    if(s[i] == '.')
    {
        i++;
        for(float delta = 0.1f; (i < strlen(s)) && isdigit(s[i]); i++, (delta /= 10)) value += (delta * (s[i] - '0'));
    }

    // exponential
    if((s[i] == 'e') || (s[i] == 'E'))
    {
        i++;
        float exponent = 0.0f;
        bool is_negative = (s[i] == '-');

        if(is_negative) i++;

        for(; (i < strlen(s)) && isdigit(s[i]); i++)
        {
            exponent *= 10;
            exponent += (s[i] - '0');
        }
        if(is_negative) exponent *= -1;

        value *= powf(10.0f, exponent);
    }

    return value;
}

int e4_12(const char* cstr, int n)
{
    if(n == strlen(cstr)) return 0;
    else return (cstr[n] - '0') * pow(10, strlen(cstr) - n - 1) + e4_12(cstr, (n + 1));
}

void e4_13(char cstr[LIMIT], int l, int r)
{
    if((strlen(cstr) % 2 == 0) && l == (r + 1))
        return;
    else if((strlen(cstr) % 2 != 0) && (l == r))
        return;
    else
    {
        char t = cstr[l];
        cstr[l] = cstr[r];
        cstr[r] = t;
        e4_13(cstr, (l + 1), (r - 1));
    }
}

int main()
{
}