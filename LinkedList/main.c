#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define maxsize 100

///////////PART ONE//////////
typedef struct
{
    float data ;
    struct node * next ;
} node;

typedef struct
{
    node *top ;
} Stack;

node * newnode(float x)
{
    node *n= malloc(sizeof(node));
    n->data=x;
    n->next=NULL;
    return n ;
}

Stack * initialize()
{
    Stack *s = malloc (sizeof(Stack));
    s->top = NULL;
    return s ;
}

void push(Stack *s, float val)
{
    node * p = newnode(val);
    p->next=s->top;
    s->top=p;
}

float pop(Stack *s)
{
    node * p = s-> top ;
    float data = p-> data ;
    s-> top =p->next;
    free(p);
    return data ;
}

float peek(Stack *s)
{
    return s->top->data;
}

int isEmpty(Stack *s)
{

    if (s-> top == NULL)
        return 1;
    else
        return 0 ;
}
///////////PART TWO//////////
int priority (char c)
{
    switch (c)
    {
    case'(':
        return 3;
    case'^':
        return 2;
    case '*':
    case '/':
        return 1;
    case '+':
    case '-':
        return 0 ;
    }
}

int isNumber(char* str)
{
    if(strlen(str) == 1 && !isdigit(str[0]))
        return 0;
    return 1;
}

char*  infixToPostfix(char* infix)
{
    Stack *s = initialize();
    int i = 0, j;
    char* retPost = malloc(strlen(infix));
    char postfix[100];
    postfix[0] = '#';
    char *token = strtok (infix," ");
    while(token != NULL)
    {
        if (isNumber(token))
        {
            if(postfix[0] == '#')
                strcpy(postfix, token);
            else
                strcat(postfix, token);
            for(j=0; j<strlen(token); j++)
                i++;
            postfix[i++] = ' ';
            postfix[i] = '\0';
        }
        else if (isEmpty(s))
            push (s, *token);
        else if (*token == ')')
        {
            while (peek(s) != '(')
            {
                postfix[i++] = pop(s);
                postfix[i++] = ' ';
            }
            postfix[i] = '\0';
            pop(s);
        }
        else
        {
            while(!isEmpty(s) && *token != '(' && peek(s) != '(' && priority (*token) <= priority(peek(s)))
            {
                postfix[i++] = pop(s);
                postfix[i++] = ' ';
            }
            postfix[i] = '\0';
            push(s, *token);
        }
        token = strtok (NULL, " ");
    }
    while(!isEmpty(s))
    {
        postfix[i++] = pop(s);
        postfix[i++] = ' ';
    }
    postfix[i]='\0';
    strcpy(retPost, postfix);
    return retPost;
}
///////////PART THREE//////////
float calculate(float x, float y, char op )
{
    if (op=='+')
        return x+y;
    if (op=='-' )
        return x-y;
    if (op=='*')
        return x*y;
    if (op=='/')
        return x/y ;
    if (op == '^')
        return pow(x,y) ;
}

float evaluatePostfix(char* postfix)
{
    float x,y;
    Stack * s = initialize();
    char * token = strtok (postfix," ");
    while(token !=NULL)
    {
        if (isdigit (*token))    //*token
            push (s,atof(token));
        else if(token[0] == '-' && strlen(token) != 1)
            push(s, atof(token));
        else
        {
            x= pop(s);
            y= pop(s);
            push(s,calculate(y,x,*token));
        }
        token = strtok (NULL, " ");
    }
    return pop(s);
}
///////////PART FOUR//////////
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}

int main()
{
    char infixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        char*postfix=infixToPostfix(infixExpr);
        printf("Postfix : %s\n", postfix);
        float result = evaluatePostfix(postfix);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0 ;
}
