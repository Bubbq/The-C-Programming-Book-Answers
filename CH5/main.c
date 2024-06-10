#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define LIMIT 1000


// concatenate t to s
void concat(char* s, char* t)
{
    // move to the end of s
    while (*s++ != '\0');      

    // copy t to the end of s
    while ((*s++ = *t++) != '\0');

    printf("%s\n", s);
}

// returns true if t is occurs at the end of s 
bool strend(char* s, char* t)
{
    // move to the last t characters to check similarity
    s+= (strlen(s) - strlen(t)); 

    // while they both have chars left, if not equal return false;
    while((*s && *t)) if(*s++ != *t++) return false;

    // if every character is the same
    return true;
} 

// copies the first n characters of t into s (e5_5)
void stringcpy(char* s, char* t, int n)
{
    while((--n >= 0) && (*s++ = *t++))
        ;
}

// concatanates the first n chars of t onto s (e5_5)
void stringcat(char* s, char* t, int n)
{
    // move s to point to the next availible character
    s += strlen(s);

    // copy the remaining characters
    while((--n >= 0) && (*s++ = *t++))
        ;
}

// converts a c string into an integer (e5_6)
int atoi(char* s)
{
    int i = 0;

    while(*s != '\0')
    {
        i = (i * 10) + (*s - '0');
        s++;
    }

    return i;
}

// converts int to some cstring (e5_6)
void itoa(int n, char* s)
{

    while(n != 0)
    {
        *s = (n % 10) + '0';
        n /= 10;
        s++;
    }
    
    *s = '\0';  
}

// reverses a cstr (e5_6)
void reverse(char* s)
{
    // make ptr pointing to last character
    char* t = s + (strlen(s) - 1);

    for(int i = 0; i < (strlen(s) / 2); i++)
    {
        char c = *s;
        *s++ = *t;
        *t-- = c;
    }
}

void swap(char** ptrs, int i, int j) {
    char* tmp = ptrs[i];
    ptrs[i] = ptrs[j];
    ptrs[j] = tmp;
}

int pivot(char** ptrs, int start, int end) {
    int i = start - 1;
    char* s = ptrs[end];

    for (int j = start; j < end; j++)
    { 
        if(strcmp(ptrs[j], s) < 0)
        {
            i++;
            swap(ptrs, i, j);
        }
    }

    swap(ptrs, i + 1, end);
    return i; 
}

void quicksort(char** ptrs, int start, int end) {
    // base case
    if (start >= end) return;

    int p = pivot(ptrs, start, end);
    quicksort(ptrs, start, p - 1);
    quicksort(ptrs, p + 1, end);
}

void sortLines(char lines[LIMIT][LIMIT], int n)
{
    // an array of ptrs that point to the 1st char for n lines
    char* ptrs[n];

    // assign each ptr to a seperate string
    for(int i = 0; i < n; i++) ptrs[i] = lines[i];
    quicksort(ptrs, 0, (n - 1));

    for(int i = 0; i < n; i++) printf("%s\n", ptrs[i]);
}

int main()
{
    // void (*e5_3)(char*, char*) = concat;
    // bool (*e5_4)(char*, char*) = strend;
    // void (*e5_7)(char*[LIMIT], int) = sortLines;
    // e5_3("", "");
    // e5_4("", "");
    // e5_7((char){"", "", ""}, 3);
    return 0;
}
