#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int* items;
    int head, tail, capacity, noofelements;
} Queue;

typedef struct
{
    int items[20];
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

int isempty(Stack*s)
{
    return s->top==0;
}

Queue* init(int n)
{
    Queue* q = malloc (sizeof(Queue));
    q->items = malloc (n*sizeof(int));
    q->head = 0;
    q->tail = 0;
    q->capacity = n;
    q->noofelements = 0;
    return q;
}

void enqueue (Queue* q, int x)
{
    q->items[q->tail] = x;
    q->tail = (q->tail + 1) % q->capacity;
    q->noofelements++;
}

int dequeue (Queue* q)
{
    int x = q->items[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->noofelements--;
    return x;
}

int isEmpty (Queue* q)
{
    return q->noofelements == 0;
}

int getHead(Queue* q)
{
    return q->items[q->head];
}

int getTail(Queue *q)
{
    return q->items[q->tail-1];
}

void display(Queue* q)
{
    Queue* temp = init(20);
    while(!isEmpty(q))
    {
        int x = dequeue(q);
        printf("%d ", x);
        enqueue(temp,x);
    }
    while(!isEmpty(temp))
        enqueue(q, dequeue(temp));
}

int getMax (Queue *q)
{
    Queue *temp = init(20);
    int max = dequeue(q);
    enqueue(temp, max);
    while (!isEmpty(q))
    {
        int x = dequeue(q);
        if (x > max)
            max = x;
        enqueue(temp, x);
    }
    while (!isEmpty(temp))
        enqueue(q, dequeue(temp));
    return max;
}

void swap(Queue* q)
{
    Queue* temp = init (20);
    int x = dequeue(q);
    while(!isEmpty(q) && getHead(q) != getTail(q))
        enqueue(temp, dequeue(q));
    int y = dequeue(q);
    enqueue(q,y);
    while(!isEmpty(temp))
        enqueue(q,dequeue(temp));
    enqueue(q, x);
}

void insertNewValue(Queue* q, int val, int index)
{
    Queue *temp = init(20);
    int i = 0;
    while (!isEmpty(q) && i != index)
    {
        enqueue(temp, dequeue(q));
        i++;
    }
    enqueue(temp, val);
    while(!isEmpty(q))
        enqueue(temp, dequeue(q));
    while (!isEmpty(temp))
        enqueue(q, dequeue(temp));
}

Queue* reverseOdd (Queue *q)
{
    Queue* temp = init(20);
    Stack* odd = initialize();
    int count = 0;
    while (!isEmpty(q))
    {
        int x = dequeue(q);
        if (x % 2 != 0)
            push(odd, x);
        enqueue(temp, x);
    }
    while(!isEmpty(temp))
    {
        int y = dequeue(temp);
        if (y % 2 == 0)
            enqueue(q, y);
        else if(y % 2 != 0)
            enqueue(q, pop(odd));
    }
    return q;
}

Queue* reverse(Queue *q, int k)
{
    int x, i = 0;
    char fileName[20];
    Stack* s = initialize();
    Queue* temp = init(20);
    Queue* qRet = init(20);
    printf("\nEnter the file name in the form of '.txt':\n");
    gets(fileName);
    FILE* f = fopen(fileName, "r");
    if(!f)
    {
        printf("Error in opening the file.\n");
        exit(-1);
    }
    while(!feof(f))
    {
        fscanf(f, "%d ", &x);
        enqueue(q, x);
    }
    fclose(f);
    printf("Queue from the file:\n");
    display(q);
    while(!isEmpty(q))
    {
        while(i++ < k)
            push(s, dequeue(q));
        enqueue(temp, dequeue(q));
    }
    while(!isempty(s))
        enqueue(q, pop(s));
    while(!isEmpty(temp))
        enqueue(q, dequeue(temp));
    FILE* ff = fopen(fileName, "w");
    if(!f)
    {
        printf("Error in opening the file.\n");
        exit(-1);
    }
    while(!isEmpty(q))
    {
        int y = dequeue(q);
        fprintf(ff, "%d ", y);
        enqueue(qRet, y);
    }
    fclose(ff);
    return qRet;
}

int main()
{
    Queue* q = init(20);
    enqueue(q,4);
    enqueue(q,8);
    enqueue(q,7);
    enqueue(q,22);
    enqueue(q,14);
    enqueue(q,5);
    printf("The Queue:\n");
    display(q);
    printf("\nThe maximum value in the Queue:\n%d", getMax(q));
    swap(q);
    printf("\nThe Queue after swapping the value of head and tail:\n");
    display(q);
    insertNewValue(q,18,3);
    printf("\nThe Queue after inserting the value (18) in the index (3):\n");
    display(q);
    Queue* q2 = init(20);
    enqueue(q2,14);
    enqueue(q2,13);
    enqueue(q2,17);
    enqueue(q2,8);
    enqueue(q2,4);
    enqueue(q2,10);
    enqueue(q2,11);
    enqueue(q2,4);
    enqueue(q2,15);
    enqueue(q2,18);
    enqueue(q2,19);
    printf("\nThe second Queue:\n");
    display(q2);
    printf("\nThe Queue after reversing the odd numbers:\n");
    display(reverseOdd(q2));
    Queue* q3 = init(20);
    q3 = reverse(q3, 4);
    printf("\nReversed Queue from the file:\n");
    display(q3);
    return 0;
}
