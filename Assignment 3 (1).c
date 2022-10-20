#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define MAX 20

struct tree
{
    char data;
    struct tree *left,*right;
};

int top=-1;
struct tree *stack[20];
struct tree *node;

int check(char ch)
{
if(ch=='+'||ch=='-'||ch=='/'||ch=='*')
return 2;
else
return 1;
}

void push(struct tree* node)
{
    stack[++top]=node;
}

struct tree *pop()
{
    return(stack[top--]);
}

/* Calculating the value of postfix expression using recursion */

int cal(struct tree *node)
{
    int ch;
    ch=check(node->data);
    if(ch==1)
    return node->data-48;
    else if(ch==2)
    {
        if(node->data=='+')
            return cal(node->left)+cal(node->right);
        if(node->data=='-')
            return cal(node->left)-cal(node->right);
        if(node->data=='*')
            return cal(node->left)*cal(node->right);
        if(node->data=='/')
            return cal(node->left)/cal(node->right);
    }
}

/* Displaying all node in order */
void inorder(struct tree *node)
{
    if(node!=NULL)
    {
    inorder(node->left);
    printf("%c",node->data);
    inorder(node->right);
    }
}

/* making simple operand node and pushing into stack */
void operand(char b)
{
    node=(struct tree*)malloc(sizeof(struct tree));
    node->data=b;
    node->left=NULL;
    node->right=NULL;
    push(node);
}

/* making operator node than pop-up two nodes from stack and adding into operator node and finally push node into stack  */
void operators(char a)
{
    node=(struct tree*)malloc(sizeof(struct tree));
    node->data=a;
    node->right=pop();
    node->left=pop();
    push(node);
}


char stk[20];
int top1 = -1;

int isEmpty(){
    return top1 == -1;
}

int isFull(){
    return top1 == MAX - 1;
}

char peek(){
    return stk[top1];
}

char pop1(){
    /*if(isEmpty())
        return INT_MIN;*/

    char ch = stk[top1];
    top1--;
    return(ch);
}

void push1(char oper){
    if(isFull())
        printf("Stack Full!!!!");
   
    else{
        top1++;
        stk[top1] = oper;
    }
}

int checkIfOperand(char ch) 
{ 
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');
} 

int precedence(char ch) 
{ 
    switch (ch) 
    { 
    case '+': 
    case '-': 
        return 1; 

    case '*': 
    case '/': 
        return 2; 

    case '^': 
        return 3; 
    } 
    return -1; 
} 

int covertInfixToPostfix(char* expr) 
{ 
    int i, j;

    for (i = 0, j = -1; expr[i]; ++i){ 
        if (checkIfOperand(expr[i])) 
            expr[++j] = expr[i]; 

        else if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{')
            push1(expr[i]); 

        else if (expr[i]==')' || expr[i]=='}'  || expr[i]==']') 
        {
            if(expr[i]==')'){   
                while (!isEmpty() && peek() != '(') 
                    expr[++j] = pop1(); 
                pop1();
            }
            
            if(expr[i]==']'){   
                while (!isEmpty() && peek() != '[') 
                    expr[++j] = pop1(); 
                pop1();
            }
           if(expr[i]=='}'){
                while (!isEmpty() && peek() != '{') 
                    expr[++j] = pop1(); 
                pop1();
            }
        }
        else
        { 
            while (!isEmpty() && precedence(expr[i]) <= precedence(peek())) 
                expr[++j] = pop1(); 
            push1(expr[i]); 
        } 

    } 
    while (!isEmpty()) 
        expr[++j] = pop1(); 

    expr[++j] = '\0'; 
    printf( "%s", expr); 
} 

void main()
{
    printf("Enter expression : ");
    char expression[MAX];
    fgets(expression, MAX, stdin);
    covertInfixToPostfix(expression); 
     

    int i,p,k,ans;
    char s[20];
    printf("Enter the expression in postfix form \n");
    fflush(stdin);
    gets(s);
    k=strlen(s);
    i=0;
    for(i=0;s[i]!='\0';i++)
        {
            p=check(s[i]);
            if(p==1)
            operand(s[i]);
            else if(p==2)
            operators(s[i]);
        }
    ans=cal(stack[top]);
    printf("\nThe value of the postfix expression you entered is %d\n",ans);
    printf("\nThe inorder traversal of the tree is \n");
    inorder(stack[top]);
    //getch();
}