#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{
    int mis;
    char name[100];
    struct Node *left;
    struct Node *right;
} Node;
typedef Node *BST;
typedef struct stack
{
    int top;
    int size;
    Node **arr;
}stack;
typedef stack* Stack;
void init_stack(Stack *stackName)
{
    *stackName = (Stack)malloc(sizeof(Stack));
    (*stackName)->top = -1;
    (*stackName)->size = 1000;
    (*stackName)->arr = (Node **)malloc(sizeof(Node *) * (*stackName)->size);
}
int isEmpty(Stack stackName)
{
    if ((stackName)->top == -1)
        return 1;
    else
        return 0;
}
int isFull(Stack stackName)
{
    if ((stackName)->top == (stackName)->size)
        return 1;
    else
        return 0;
}
void push(Stack *stackName, Node *a)
{
    if (a == NULL)
        return;
    if (isFull((*stackName)) == 1)
        return;
    else
    {
        (*stackName)->top++;
        (*stackName)->arr[(*stackName)->top] = a;
        return;
    }
}
void pop(Stack *stackName)
{
    if (isEmpty((*stackName)) == 1)
        return;
    else
    {
        (*stackName)->top--;
        return;
    }
}
Node *peek(Stack *stackName)
{
    return (*stackName)->arr[(*stackName)->top];
}
void init_bst(BST *bst)
{
    *bst = NULL;
}

Node* create(int Mis,char Name[]){
    Node *nn=(Node*)malloc(sizeof(Node));
    if(!nn) return NULL;
    nn->mis = Mis;
    strcpy(nn->name,Name);
    nn->left = NULL;
    nn->right = NULL;
    return nn;
}

void insert_(BST *bst, int Mis, char Name[])
{
    if (*bst == NULL)
    {
        (*bst) = create(Mis,Name);
        return;
    }
    if( Mis == (*bst)->mis){
        return ;
    }
    else if( Mis > (*bst)->mis){
        return insert_(&(*bst)->right,Mis,Name);
    }
    else if(Mis < (*bst)->mis){
        return insert_(&(*bst)->left,Mis,Name);
    }
    return ;
}

void delete_(BST *bst,int Mis){
    Node *p=*bst;
    Node *q=NULL;

    if(!*bst) return;

    while(p){
        if(p->mis==Mis){
            // node to be deleted is root node
            if(!q){
                *bst=NULL;
                free(p);
                return;
            }
         // node to be deleted is leaf node
            if(p->left==NULL && p->right ==NULL){
                if(q->left==p) q->left=NULL;
                else q->right=NULL;
                free(p);
                return;
            }

            // node to be deleted has only one child
            else if(p->left==NULL || p->right ==NULL){

                //only right child is present
                if(p->left==NULL){
                    if(q->left==p){
                        q->left=p->right;
                    }
                    else if(q->right==p){
                        q->right=p->right;
                    }
                }

                //only left child is present
                else {
                    if(q->left==p){
                        q->left=p->left;
                    }
                    else if(q->right==p){
                        q->right=p->left;
                    }
                }
                free(p);
                return;
          }

          //node to be deleted has both child
          else{
                Node *kp,*tmp;
                kp=tmp=p;
                p=p->left;
              //only left child with no right succesors
              if(! p->right){
                    tmp->mis=p->mis;
                    strcpy(tmp->name,p->name);
                    tmp->left=p->left;
                    free(p);
                    return;
                }
              //left child having right succesors
              else{
                    while(p->right){
                        kp=p;
                        p=p->right;
                    }
                    tmp->mis=p->mis;
                    strcpy(tmp->name,p->name);
                    kp->right=p->left;
                    free(p);
                    return;
              }
          }
        }

        else if (Mis < p->mis){
            q=p;
            p=p->left;
        }
        else {
            q=p;
            p=p->right;
        }

    }
     return;
}

int search_(BST bst, int mis)
{
    if (bst == NULL)
        return 0;
    if (bst->mis == mis)
        return 1;
    if (bst->mis < mis)
        search_(bst->right, mis);
    else
        search_(bst->left, mis);
}

void displayLevel(BST bst, int level)
{
    if (bst == NULL)
        return;
    if (level == 1)
    {
        printf("%d-%s ", bst->mis,bst->name);
        return;
    }

    displayLevel(bst->left, level - 1);
    displayLevel(bst->right, level - 1);
}

void postOrderTraversal(BST bst){
    if(bst == NULL)
        return;
    Stack s;
    init_stack(&s);
    BST p = NULL;
    while(bst || !isEmpty(s)){
        if(bst){
            push(&s,bst);
            bst = bst->left;
        }else{
            bst = peek(&s);
            if(bst->right == NULL || bst->right == p){
                printf("%d-%s ", bst->mis,bst->name);
                pop(&s);
                p = bst;
                bst = NULL;
            }else{
                bst = bst->right;
            }
        }
    }
}

void destroyAllNodes(BST *bst)
{
    if (*bst == NULL)
        return;
    destroyAllNodes(&((*bst)->left));
    destroyAllNodes(&((*bst)->right));
    free(*bst);
    *bst = NULL;
}

int main()
{
    int input,end,data;
    char name[100];
    BST bst;
    init_bst(&bst);

    while (1)
    {
        printf("To insert a Node press 1 \n");
        printf("To delete a Node press 2 \n");
        printf("For postOrderTraversal press 3 \n");
        printf("To search a Node press 4 \n");
        printf("To displayLevel press 5 \n");
        printf("To destroy press 6 \n");
        scanf("%d", &input);
        switch (input)
        {

        case 1:
            printf("Enter value to be inserted : \n");
            printf("MIS : ");
            scanf("%d", &data);
            printf("Name - ");
            scanf("%s",name);
            insert_(&bst, data,name);
            break;
        case 2:
            printf("Enter MIS to be deleted : \n");
            scanf("%d", &data);
            delete_(&bst, data);
            break;
        case 3:
            printf("Postorder traversal of BST :\n");
            postOrderTraversal(bst);
            break;
        case 4:
            printf("Enter MIS to be searched : \n");
            scanf("%d", &data);
            if (search_(bst, data) == 1)
                printf("mis is present in BST");
            else
                printf("mis not found");
            break;
        case 5:
            printf("Enter Level to printed : ");
            scanf("%d", &data);
            displayLevel(bst, data);
            break;
        case 6:
            printf("initializing destroy BST protocol\n");
            destroyAllNodes(&bst);
            printf("**BST destroyed**");
            end=1;
            break;
        }
        if (end==1) break;
        printf("\n******************************************\n");
    }
}

