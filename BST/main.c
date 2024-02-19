#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char * data ;
    struct node * left ;
    struct node * right ;
} node;

node * newnode (char * n)
{
    node * name = malloc(sizeof(node));
    name->data = malloc(strlen(n)+1);
    strcpy (name->data, n );
    name->left =NULL ;
    name->right =NULL;
    return name;
}

node* search (node * root, char * key )
{
    if (root == NULL )
        return NULL ;
    if(strcasecmp (root->data, key )==0)
        return root ;
    if (strcasecmp (key, root -> data)<0)
        return search (root-> left, key);
    return search(root -> right, key);
}

node * insert (node * root, char * key )
{
    if (root == NULL)
        return newnode(key);
    if (strcasecmp(key,root ->data)<0)
        root -> left = insert(root -> left, key );
    else if (strcasecmp(key, root -> data)>0)
        root -> right =insert(root -> right, key );
    return root ;
}

int count(node* root)
{
    if(!root)
        return 0;
    return 1 + count(root->left) + count(root->right);
}

int max(int a, int b)
{
    return a>b?a:b;
}

int height(node* root)
{
    if(!root)
        return -1;
    return 1 + max(height(root->left), height(root->right));
}

node* addFileToTree(node* root, char* filename)
{
    char s[30];
    FILE * f= fopen(filename,"r");
    if (f!=NULL)
    {
        while (!feof(f))
        {
            fscanf(f,"%s", s);
            root=insert(root, s);
        }
        printf("Dictionary is Loaded Successfully\n\n");
    }
    else printf("Dictionary is not found\n\n");
    fclose(f);
    return root;
}
node* findMin(node* root)
{
    while(root && root->left)
        root = root->left;
    return root;
}

node* findMax(node* root)
{
    while(root && root->right)
        root = root->right;
    return root;
}

char* inorderSuccessor(node* root, char* word)
{
    node* current = root;
    node* successor = NULL;
    if (!root) return NULL;
    while(current && strcasecmp(word, current->data) != 0)
    {
        if(strcasecmp(word,current->data) < 0)
        {
            successor = current;
            current = current->left;
        }
        else
            current = current->right;
    }
    if(!current)
        return NULL;
    if(current && current->right)
        successor = findMin(current->right);
    return successor->data;
}

char* inorderPredecessor(node* root, char* word)
{
    node* current = root;
    node* pre = NULL;
    if (!root) return NULL;
    while(current && strcasecmp(word, current->data) != 0)
    {
        if(strcasecmp(word,current->data) > 0)
        {
            pre = current;
            current = current->right;
        }
        else
            current = current->left;
    }
    if(!current)
        return NULL;
    if(current && current->left)
        pre = findMax(current->left);
    return pre->data;
}

char* findLeaf(node*root, char* word)
{
    node* parent = NULL;
    if(!root)
        return 0;
    while(root)
    {
        if(strcasecmp(word, root->data) < 0)
        {
            parent = root;
            root = root->left;
        }
        else if(strcasecmp(word, root->data) > 0)
        {
            parent = root;
            root = root->right;
        }
    }
    return parent->data;
}

int main()
{
    node * root = NULL ;
    root = addFileToTree(root, "EN-US-Dictionary.txt");
    printf("Size = %d\n\n", count(root));
    printf("Height = %d\n\n", height(root));
    char sentence[200];
    char leaf[50];
    printf("Enter a sentence:\n");
    gets(sentence);
    char* token = strtok(sentence, " ");
    while(token)
    {
        if(search(root, token))
            printf("%s: CORRECT\n", token);
        else
        {
            strcpy(leaf, findLeaf(root, token));
            printf("%s: INCORRECT, Suggestions: %s %s %s\n",token,leaf,inorderSuccessor(root,leaf),inorderPredecessor(root,leaf));
        }
        token = strtok(NULL, " ");
    }
    return 0;
}
