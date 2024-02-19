#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct
{
    int items[SIZE];
    int top;
} Stack;

Stack* initialize()
{
    Stack*s=malloc(sizeof(Stack));
    s->top=0;
    return s;
}

void push(Stack*s,int x)
{
    s->items[s->top++] = x;
}

int pop(Stack*s)
{
    return s->items[--s->top];
}

int isEmpty(Stack*s)
{
    return s->top==0;
}

int isFull(Stack*s)
{
    return s->top == SIZE;
}

int peek(Stack*s)
{
    return s->items[s->top-1];
}

int isprime(int x)
{
    int i;
    if(x == 0 || x == 1)
        return 0;
    for(i=2; i<=x/2; i++)
        if(x%i == 0)
            return 0;
    return 1;
}

void display(Stack*s)
{
    Stack*temp=initialize();
    while(!isEmpty(s))
    {
        int x=pop(s);
        printf("%d ",x);
        push(temp,x);
    }
    while(!isEmpty(temp))
        push(s,pop(temp));
}

char* reverseStr(Stack* s,char* str)
{
    char* str2 = malloc(strlen(str) + 1);
    int i;
    for(i=0; i<strlen(str); i++)
        push(s, str[i]);
    for(i=0; i<strlen(str); i++)
        str2[i] = pop(s);
    return str2;
}

int isSorted(Stack*s)
{
    int x, a = 0, d = 0, count = 0;
    Stack* temp = initialize();
    while(!isEmpty(s))
    {
        x = pop(s);
        if(isEmpty(s))
            break;
        if(x < peek(s) || x == peek(s))
            a++;
        else if(x > peek(s) || x == peek(s))
            d++;
        count++;
        push(temp, x);
    }
    push(temp, x);
    while(!isEmpty(temp))
        push(s, pop(temp));
    if(a == count)
        return 1;
    if(d == count)
        return 2;
    return 0;
}

void delNonPrime(Stack*s)
{
    Stack* temp = initialize();
    while(!isEmpty(s))
    {
        int x = pop(s);
        if(isprime(x))
            push(temp, x);
    }
    while(!isEmpty(temp))
        push(s, pop(temp));
}

int sortStack(Stack* s)
{
    if(isSorted(s))
        return 1;
    int x;
    Stack* temp = initialize();
    while(!isEmpty(s))
    {
        x = pop(s);
        while (!isEmpty(temp) && x < peek(temp))
            push(s, pop(temp));
        push(temp, x);
    }
    while(!isEmpty(temp))
        push(s, pop(temp));
    return 0;
}

Stack* mergeStacks(Stack* s1, Stack* s2)
{
    Stack* temp = initialize();
    Stack* s = initialize();
    while(!isEmpty(s1) && !isEmpty(s2))
        if(peek(s1) < peek(s2))
            push(temp, pop(s1));
        else if (peek(s2) < peek(s1))
            push(temp, pop(s2));
        else if (peek(s2) == peek(s1))
        {
            push(temp, pop(s1));
            push(temp, pop(s2));
        }
    if(isEmpty(s1) && !isEmpty(s2))
        while(!isEmpty(s2))
            push(temp, pop(s2));
    else if(isEmpty(s2) && !isEmpty(s1))
        while(!isEmpty(s1))
            push(temp, pop(s1));
    while(!isEmpty(temp))
        push(s, pop(temp));
    return s;
}

int main()
{
    int i;
    Stack*s=initialize();
    char* str = "abcd";
    printf("String: %s\n", str);
    char* str2 = reverseStr(s, str);
    printf("\nReversed String: %s\n", str2);

    Stack*s2 = initialize();
    push(s2,2);
    push(s2,4);
    push(s2,5);
    push(s2,9);
    printf("\nStack (s2) elements: ");
    display(s2);
    delNonPrime(s2);
    printf("\n\nAfter deleting the non-prime numbers in stack (s2): ");
    display(s2);

    Stack* s3 = initialize();
    push(s3,9);
    push(s3,8);
    push(s3,7);
    push(s3,6);
    push(s3,5);
    printf("\n\nStack (s3) elements: ");
    display(s3);
    if(isSorted(s3) == 1)
        printf("\n\nStack (s3) is Sorted (min in top).\n");
    else if(isSorted(s3) == 2)
        printf("\n\nStack (s3) is Sorted (max on top).\n");
    else
        printf("\n\nStack (s3) is not sorted.\n");

    if(!sortStack(s3))
    {
        printf("\nAfter sorting stack (s3) (min on top): ");
        display(s3);
    }
    else
        printf("\nStack (s3) is already sorted.");
    printf("\n");

    Stack* s4 = initialize();
    push(s4,4);
    push(s4,3);
    push(s4,2);
    push(s4,1);
    printf("\nStack (s4) elements: ");
    display(s4);
    printf("\n");
    Stack* s5 = initialize();
    s5 = mergeStacks(s3, s4);
    printf("\nThe merged stack of sorted (s3) & (s4): ");
    display(s5);
    printf("\n");
    return 0;
}
