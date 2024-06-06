#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define  MAX 1000


// exr4_14
#define swap(t, x, y) t temp = x; x = y; y = temp;

typedef struct node
{
    int val;
    struct node* next;
} Node;

typedef struct
{
    int size;
    Node* head;
} LinkedList;

typedef struct
{
    LinkedList ll;
} Stack;

LinkedList createLinkedList()
{
    return (LinkedList){0, NULL};
}

// adds node to the front of some linked list
void addFront(LinkedList* ll, int val)
{
    Node* nn = malloc(sizeof(Node));
    nn->val = val;
    nn->next = ll->head;
    ll->head = nn;
    ll->size++;
}

int removeFront(LinkedList* ll)
{
    Node* oh = ll->head;
    int ohv = oh->val;
    ll->head = ll->head->next;
    free(oh);
    return ohv;    
}

void deleteLinkedList(LinkedList* ll)
{
    Node* prev = NULL;
    while(ll->head != NULL)
    {
        prev = ll->head;
        ll->head = ll->head->next;
        free(prev);
    }
}

Stack createStack()
{
    return (Stack){createLinkedList()};
}

void push(Stack* st, int val)
{
    addFront(&st->ll, val);
}

int pop(Stack* st)
{
    return removeFront(&st->ll);
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
float asciitof(char str[MAX])
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

// evaluates a cstring in reverse polish notation
int calculate(char expr[MAX])
{
    Stack st = createStack();

    for(int i = 0; i < strlen(expr); i++)
    {
        if(isdigit(expr[i])) push(&st, (expr[i] - '0'));
        else
        {
            // get the operators
            int b = pop(&st); int a = pop(&st);

            // evaluate expr based on operand (current char)
            switch (expr[i]) 
            {
                case '+': push(&st, (a + b)); break;
                case '-': push(&st, (a - b)); break;
                case '*': push(&st, (a * b)); break;
                case '/': push(&st, (a / b)); break;
                case '%': push(&st, (a % b)); break;
                default:
                    break;
            }
        }
    }

    int ans = pop(&st);

    // free allocations
    deleteLinkedList(&st.ll);
    
    return ans;
}

// recursivley convert an int n into some str
void itoa(int n, int i, char str[MAX])
{
    // base case, reverse the number
    if(n == 0)
    {
        reverse(str);
        str[i] = '\0';
        printf("%s\n", str);
        return;
    }

    // get last char and put in ith pos of c str
    str[i] = (n % 10) + '0';
    itoa((n / 10), (i + 1), str);
}

void reverseRecursive(char str[MAX], int i)
{
    // base case
    if(i == (strlen(str) / 2)) 
    {
        printf("%s\n", str);
        return;
    }

    // swap the corrsponding ith and n-ith characters
    int n = strlen(str) - 1;
    char tmp = str[i];
    str[i] = str[n - i];
    str[n - i] = tmp;

    reverseRecursive(str, (i + 1));
}

int main()
{
    // int (*e4_1)(char[MAX], char[MAX]) = strrindex;
    // float (*e4_2)(char[MAX]) = asciitof;
    // int (*e4_3)(char[MAX]) = calculate;
    // void (*e4_12)(int, int, char[MAX]) = itoa;
    // void (*e4_13)(char[MAX], int) = reverseRecursive;
    // e4_1("", "");
    // e4_2("");
    // e4_3("23+45-*");
    // e4_12(0, 0, "");
    // e4_13("", 0);
    
    return 0;
}