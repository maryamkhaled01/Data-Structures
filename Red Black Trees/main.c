#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////// Implementation Of Red Black Tree //////////
typedef struct node
{
    char * data ;
    struct node * left ;
    struct node * right ;
    struct node * parent;
    int color;
} node;

node * newnode (char * n, int c)
{
    node * name = malloc(sizeof(node));
    name->data = malloc(strlen(n)+1);
    strcpy (name->data, n );
    name->left =NULL ;
    name->right =NULL;
    name->parent= NULL;
    name->color = c;
    return name;
}
// RBT search
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

// RBT insertion
node * insert (node * root, node* n )
{
    if (root == NULL)
        return n;
    if (strcasecmp(n->data,root ->data)<0){
        root -> left = insert(root -> left, n );
        root->left->parent = root;
    }
    else if (strcasecmp(n->data, root -> data)>0){
        root -> right =insert(root -> right, n );
        root->right->parent = root;
    }
    return root ;
}

node* left_rotate(node* root, node* x){
    node* y = x->right;
    x->right = y->left;
    if(y->left)
        x->left->parent = x;
    y->parent = x->parent;
    if(!x->parent)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
    return root;
}

node* right_rotate(node* root, node* x){
    node* y = x->left;
    x->left = y->right;
    if(y->right)
        y->right->parent = x;
    y->parent = x->parent;
    if(!x->parent)
        root = y;
    else if(x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
    return root;
}

node* fix_up(node* root, node* n)
{
    node* y;
    while(n != root && n->parent->color == 1 && n->parent->parent != NULL){ //1 RED, 0 BLACK
        if(n->parent == n->parent->parent->left){ //if parent is the left child
            y = n->parent->parent->right;
            if(y != NULL && y->color == 1){// if uncle is RED (Case 1)
                n->parent->color = 0;
                y->color = 0;
                n->parent->parent->color = 1;
                n = n->parent->parent;
            }
            else { // if uncle is BLACK
                if(n == n->parent->right){ //Case 2
                    n = n->parent;
                    root = left_rotate(root, n);
                } //Case 3
                n->parent->color = 0;
                n->parent->parent->color = 1;
                root = right_rotate(root, n->parent->parent);
            }
        }
        else if(n->parent == n->parent->parent->right){ // if parent is the right child
            y = n->parent->parent->left;
            if(y != NULL && y->color == 1){// if uncle is RED (Case 1)
                n->parent->color = 0;
                y->color = 0;
                n->parent->parent->color = 1;
                n = n->parent->parent;
            }
            else{ //if uncle is BLACK
                if(n == n->parent->left){ //Case 2
                    n = n->parent;
                    root = right_rotate(root, n);
                } //Case 3
                n->parent->color = 0;
                n->parent->parent->color = 1;
                root = left_rotate(root, n->parent->parent);
            }
        }
    }
    root->color = 0;
    return root;
}

// RBT size
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
// RBT height
int height(node* root)
{
    if(!root)
        return -1;
    return 1 + max(height(root->left), height(root->right));
}

/////// Dictionary Implementation /////////
// Load Dictionary
node* loadDictionary(node* root, char* filename)
{
    char s[30];
    FILE * f= fopen(filename,"r");
    if (f!=NULL)
    {
        while (!feof(f))
        {
            fscanf(f,"%s", s);
            node *n = newnode(s,1);
            root=insert(root, n);
            root = fix_up(root, n);
        }
        printf("Dictionary is Loaded Successfully.\n");
    }
    else printf("Dictionary is not found\n");
    fclose(f);
    return root;
}
// print size
void printDictionarySize(node* root){
    printf("\nSize = %d\n", count(root));
}
// print height
void printDictionaryHeight(node* root){
    printf("Height = %d\n\n", height(root));
}
// insert word
node* insertWord(node* root, char* word){
    if(search(root, word) == NULL){
        node* n = newnode(word, 1);
        root = insert(root, n);
        root = fix_up(root, n);
        printf("\nWord is inserted Successfully.");
        printDictionarySize(root);
        printDictionaryHeight(root);
    }
    else
        printf("\nERROR: Word already in the dictionary!\n\n");
    return root;
}
// look up a word
void lookUpaWord(node* root, char *word){
    node* n = search(root, word);
    if(n == NULL)
        printf("\nNO\n");
    else
        printf("\nYES\n");
}

//////// MAIN /////////
int main()
{
    node * root = NULL ;
    root = loadDictionary(root, "EN-US-Dictionary.txt");
    printDictionarySize(root);
    printDictionaryHeight(root);

    char word[30];
    printf("Enter a word to insert:\n");
    gets(word);
    root = insertWord(root, word);

    printf("Enter a word to look up:\n");
    gets(word);
    lookUpaWord(root, word);

    return 0;
}
