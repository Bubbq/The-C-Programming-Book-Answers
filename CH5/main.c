#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// concatenate t to s
void concat(char* s, const char* t)
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

int main()
{
    // void (*e5_3)(char*, const char*) = concat;
    // bool (*e5_4)(char*, char*) = strend;
    // e5_3("", "");
    // e5_4("", "");

    return 0;
}
