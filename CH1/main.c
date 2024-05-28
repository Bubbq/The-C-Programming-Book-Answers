#include <stdio.h> // standard input and output library
#include <stdbool.h>

#define MAXLINE 100000

void breakWords()
{
    int c = 0;
    while((c = getchar()) != EOF)
    {
        // print letters to screen 
        if((c >= 97 && c <= 122) || (c >= 65 && c <= 90)) putchar(c);
        // anything else just print as a new line
        else putchar('\n');
        
        if(c == 'q') break;
    }

}

void standardInputStats()
{
    // if the char is a letter, print to screen, if not , put new line to screen
    int c = 0;
    int nt = 0;
    int ns = 0;
    int nl = 0;

    while((c = getchar()) != EOF)
    {
        switch (c)
        {
            // tab
            case 9: nt++; break;
            // space
            case 32: ns++; break;
            // new line
            case 10: nl++; break;
            default: break;
        }

        if(c == 'q') break;
    }

    printf("\nSTATS:\nTabs: %d\nBlanks: %d\nLines: %d\n", nt, ns, nl);
}

// get and display the freq of the lengths of every world typeds
void wordLengthFreq()
{
    int c, nc = 0;
    int lens [10] = {0};

    while((c = getchar()) != EOF)
    {
        if((c >= 97 && c <= 122) || (c >= 65 && c <= 90)) nc++;
        else if((c == ' ' || c == '\t' || c == '\n') && nc > 0)
        {
            lens[nc - 1]++;
            nc = 0;
        }

        if(c == 'q') break; 
    }

    for(int i = 0; i < 10; i++)
    {
        printf("\nLENGTH %d: %d\n", (i + 1), lens[i]);
    }

}

// converts farenheit to celcius from some lower to upper bound with step of size k
void tempatureConversion(int lb, int ub, int k)
{
    printf("F\tC\n");
    
    // current tempature
    float ct = lb;

    while(ct <= ub)
    {
        // celsius
        float c = (ct - 32) * (5.00 / 9.00);
        printf("%3.0f\t%6.2f\n", ct, c);
        ct += k;
    }
}

// gets the frequncy of characters in one line
void charFreq()
{
    int c = 0;
    int chars [26] = {0};
    while ((c = getchar()) != EOF)
    {
        // uppercase
        if(c <= 90 && c >= 65) chars[c - 65]++;
        // lowercase
        if(c <= 122 && c >= 97) chars[c - 97]++;

        if(c == '.') break;
     
    }

    printf("\nCHARACTER FREQ:\n");
    for(int i = 0; i < 26; i++)
    {
        printf("%c: %d\n", (char)(97 + i), chars[i]);
    }
}

// reads a line from standard input into char array 'line' and returns size
int getLineSize(char line[MAXLINE])
{
    char cc;
    int i = 0;

    while(((cc = getchar()) != EOF))
    {
        if(cc == ':') break;
        if(cc == '|') return 0;
        if(i < MAXLINE) line[i++] = cc;
        else i++;
    }

    // adding null terminated character, if text stream is larger than max capacity than arr[n + 1] is the terminated character as we want to stop a the one before, or n
    if(i < MAXLINE) line[i++] = '\0';
    else line[MAXLINE] = '\0';

    return i;
}

// copies array 'a' into b
void copy(char a[MAXLINE], char b[MAXLINE])
{
    int i = 0;
    // assigns ith element of a into b, including the null terminated character '\0'
    while((b[i] = a[i]) != '\0') i++;
}

// prints words that are greater than n
void printWordsOfLengthN(int n)
{
    // length of ith line
    int len = 0;
    // ith line
    char line[MAXLINE];

    while((len = getLineSize(line)) > 0)
    {
        if(len > n) printf("%s\n", line);

        // esc seq
        if(len == 1) break;
    }
}

void removeTrailing()
{
    char line[MAXLINE];
    int len = 0;

    while((len = getLineSize(line)) > 0)
    {
        // going in reverse order
        for(int i = len - 2; i >= 0; i--)
        {
            if(line[i] == ' ' || line[i] == '\t') line[i] = '\0';
            else break;
        }

        printf("%s", line);
        
        if(len == 1) break;
    }
}

// reverses a line of
void reverseLine()
{
    int len = 0;
    char line[MAXLINE];

    while((len = getLineSize(line)) > 0)
    {
        // print in reverse order
        for(int i = len - 2; i >= 0; i--) putchar(line[i]);

        if(len == 1) break;
    }
}

// finds the longest line and prints it
void longestLine()
{
    int len, max = 0;
    char cline[MAXLINE];
    char lline[MAXLINE];

    while((len = getLineSize(cline)) > 1)
    {
        printf("%d\n", len);
        if(len > max)
        {
            max = len;
            copy(cline, lline);
        }
    }

    if(max > 0) printf("The longest line is %s with a length of %d\n", lline, max);
}

// replace every tab with 4 spaces in output
void detab()
{
    int len = 0;
    char line[MAXLINE];

    while((len = getLineSize(line)) > 1)
    {
        for(int i = 0; i < len - 1; i++)
        {
            // replacing the tab
            if(line[i] == '\t')
            {
                for(int i = 0; i < 4; i++) putchar(' ');
            }

            else putchar(line[i]);
        }

        putchar('\n');
    }
}

// replaces strings of ' ' with tabs
void entab()
{
    int len = 0;
    char line[MAXLINE];

    while((len = getLineSize(line)) > 1)
    {
        for(int i = 0; i < len - 2; i++)
        {
           // find space substr
           if(line[i] == ' ')
           {
                int si = i;
                while((line[i] == ' ') && (i < len - 1)) i++;

                int slen = (i - si);

                // tab is 4 spaces, space is 1 
                while(slen != 0)
                {
                    if(slen >= 4)
                    {
                        putchar('t');
                        putchar('a');
                        putchar('b');
                        slen -= 4;
                    }

                    else if(slen >= 1)
                    {
                        putchar('s');
                        slen--;
                    }
                }
           }

           else putchar(line[i]);
        }

        putchar('\n');
    }
}
 
// removes single and multi-line comments after being read code in the terminal
void removeComments()
{
    char line[MAXLINE];
    int len = 0;
    bool print_char = true;
    while((len = getLineSize(line)) > 0)
    {
        for(int i = 0; i < len - 1; i++)
        {
            // removes entire commented line
            if(line[i] == '/' && line[i + 1] == '/')
            {
                while((line[i] != '\n') && (i <= len - 2)) i++;
            } 

            // ignores multi-line comment content
            else if(line[i] == '/' && line[i + 1] == '*') print_char = false;
            else if(line[i] == '*' && line[i + 1] == '/')
            {
                i += 2;
                print_char = true;
            }

            // print code content to terminal
            if(print_char) putchar(line[i]);
        }
        
        putchar('\n');
    } 
}

int main()
{
    // void (*e1_8)() = standardInputStats;
    // void (*e1_12)() = breakWords;
    // void (*e1_13)() = wordLengthFreq;
    // void (*e1_14)() = charFreq;
    // void (*e1_15)(int, int, int) = tempatureConversion;
    // void (*e1_16)() = longestLine;
    // void (*e1_17)(int) = printWordsOfLengthN;
    // void (*e1_18)() = removeTrailing;
    // void (*e1_19)() = reverseLine;
    // void (*e1_20)() = detab;
    // void (*e1_21)() = entab;
    // void (*e1_22)() = removeComments;
    // e1_8();
    // e1_12();
    // e1_13();
    // e1_14();
    // e1_15(0, 300, 20);
    // e1_16();
    // e1_17(80)
    // e1_18();
    // e1_19();
    // e1_20();
    // e1_21();
    // e1_22();
    return 0;
}