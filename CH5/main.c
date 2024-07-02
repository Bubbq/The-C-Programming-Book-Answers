#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMIT 1000

typedef struct node
{
    int val;
    struct node* next;
} Node; 

Node* createNode(int val, Node* next)
{
    Node* nn = malloc(sizeof(Node));
    *nn = (Node){val, next};
    return nn;
}

typedef struct
{
	int size;
	Node* head;
	Node* tail;
} LinkedList;

LinkedList createLinkedList()
{
    return (LinkedList){0, NULL, NULL};
}

void deleteLinkedList(LinkedList* ll)
{
    for(Node* prev = NULL; ll->head != NULL; prev = ll->head, ll->head = ll->head->next, free(prev));
}

bool isEmpty(LinkedList ll)
{
    return (ll.size == 0);
}

void addFront(LinkedList* ll, int val)
{
    Node* nh = createNode(val, ll->head);
    ll->head = nh;
    ll->size++;
}

void deleteNode(LinkedList* ll, int pos)
{
    if((pos < 0) || (pos > ll->size)) return;
    else if(isEmpty(*ll)) return;
    else
    { 
        Node* prev = NULL;
        Node* cn = ll->head;

        for(int i = 0; i < pos; i++, prev = cn, cn = cn->next);

        if(prev == NULL) 
        {
            prev = ll->head;
            ll->head = ll->head->next;
            free(prev);
        }
        
        else 
        {
            prev->next = cn->next;
            free(cn);
        }

        ll->size--;
    }
}

typedef struct
{
	LinkedList elements;
} Stack;

Stack createStack()
{
    return (Stack){createLinkedList()};
}

void deleteStack(Stack* st) {deleteLinkedList(&st->elements);}
void push(Stack* st, int val) {addFront(&st->elements, val);}

int pop(Stack* st)
{
    if(isEmpty(st->elements)) return -1;

    else
    {
        int ret = st->elements.head->val;
        deleteNode(&st->elements, 0);
        return ret;
    }
}

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
int atoii(char* s)
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

int dayOfYear(int y, int m, int d)
{
    int calender[][13] = 
    {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };

    int* b[13];
    *b = *calender; // b points to the  first array of calender

    int leap = ((y % 4 == 0) && ((y % 100 != 0) || (y % 400 == 0)));
    if((d > calender[leap][m]) || (m > 12) || (y < 0)) return -1;

    for(int i = 0; i < m; i++) d += b[leap][i];
    return d;
}

int reversePolish(int argc, char* argv[])
{
    Stack st = createStack();

    for(int i = 1; i < argc; i++)
    {
        if((strcmp(argv[i], "0") >= 0) && (strcmp(argv[i], "9") <= 0)) push(&st, (argv[i][0] - '0'));
        else
        {
            int val;
            int op2 = pop(&st), op1 = pop(&st);
            
            switch (argv[i][0])
            {
                case '+': val = op1 + op2; break;
                case '-': val = op1 - op2; break;
                case '*': val = op1 * op2; break;
                case '/': val = op1 / op2; break;
                default:    
                    break;
            }

            push(&st, val);
        }
    }

    int ret = pop(&st);
    deleteStack(&st);
    return ret;
}

int compareNum(char* a, char* b, bool reverse)
{
    float v1 = atof(a);
    float v2 = atof(b);

    if(v1 < v2) return -1;
    else if(v1 > v2) return 1;
    else return 0;
}

void swapElement(void** base, int i, int j)
{
    void* t = base[i];
    base[i] = base[j];
    base[j] = t;
}

int partition(void** base, int s, int e, int(*compare)(void*, void*), bool reverse)
{
    int i = s - 1;
    for(int j = s; j < e; j++)
    {
        int cv = compare(base[j], base[e]);

        if(reverse && (cv > 0)) swapElement(base, ++i, j);
        else if(cv < 0) swapElement(base, ++i, j);
    }

    swapElement(base, i + 1, e);

    return i;
}

void quicksort(void** base, int s, int e, int(*compare)(void*, void*), bool reverse)
{
    // base case
    if(s >= e) return;

    // split the unsorted list in random sizes
    int p = partition(base, s, e, compare, reverse);

    // sort left and right recursivley
    quicksort(base, s, p - 1, compare, reverse);
    quicksort(base, p + 1, e, compare, reverse);
}

void sortLines(void** lines, char* op, int n)
{
    bool r;
    int (*cmp)(void*, void*);

    for(int i = 1; i < strlen(op); i++)
    {
        if (op[i] == 'r') r = true;
        else if (op[i] == 'a') cmp = (int(*)(void*, void*))strcmp;
        else if (op[i] == 'n') cmp = (int(*)(void*, void*))compareNum;
    }

    quicksort((void**)lines, 0, n, (int(*)(void*, void*))cmp, r);

    for(int i = 0; i < (n + 1); i++) printf("%s\n", (char*)lines[i]);
}

int main(int argc, char* argv[])
{
    // void (*e5_3)(char*, char*) = concat;
    // bool (*e5_4)(char*, char*) = strend;
    // void (*e5_7)(void**, char*, int) = sortLines;
    // int (*e5_8)(int, int, int) = dayOfYear;
    // int (*e5_11)(int, char*[]) = reversePolish;
    // e5_3("", "");
    // e5_4("", "");
    // e5_7((char){"", "", ""}, 3);
    // e5_8(0, 0, 0);
    // e5_11(0, {"", "", ""});
    return 0;
}