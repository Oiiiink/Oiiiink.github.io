#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 1000
//使用union，flag标识
//不转化为后缀表达式，而是直接压入栈中。
//栈用数组实现。
/*读入一个符号：
如果是操作数，则建立一个单节点树并将指向他的指针推入栈中；
如果是运算符，就从栈中弹出指向两棵树T1和T2的指针（T1先弹出）并形成一棵新树，树根为该运算符，它的左、右子树分别指向T2和T1，然后将新树的指针压入栈中。
*/
typedef union sym{
    int num ;
    char ope ;
} sym;
struct Node{
    sym val ;
    int flag ;// 0 表示 符号 ， 1 表示数字
    struct Node *left , *right ;
};
typedef struct Node Node ;
Node* initNode(sym val , int flag) ;
int isNum(char c) ;
int isOpe(char c) ;
int postorder(Node* root) ;
Node* buildTree() ;
// 表达树栈的构建
Node* ans[MAXSIZE] ;
int top ;
void push(Node* node) ;
// 运算符栈的构建
char ope[MAXSIZE] ;
int opeTop ;
void printT(Node* root) ;
void inorder(Node* root) ;
void preorder(Node* root) ;

int main(void)
{
    Node* root = buildTree() ;
    Node* left = root -> left ;
    Node* right = root -> right ;
    if(root) {
        Node* ptr = root ;
        if(ptr -> flag) printf("%d " , ptr -> val.num) ;
        else printf("%c " , ptr -> val.ope) ;   
    }
    if(left) {
        Node* ptr = left ;
        if(ptr -> flag) printf("%d " , ptr -> val.num) ;
        else printf("%c " , ptr -> val.ope) ;   
    }
    if(right){
        Node* ptr = right ;
        if(ptr -> flag) printf("%d " , ptr -> val.num) ;
        else printf("%c " , ptr -> val.ope) ;   
    }
    printf("\n%d" , postorder(root)) ;
    //printT(root) ;

    return 0 ;
}

Node* initNode(sym val , int flag)
{
    Node* node = (Node* )malloc(sizeof(Node)) ;
    node -> val = val ;
    node -> flag = flag ;
    node -> right = node -> left = NULL ;

    return node ;
}
int isNum(char c)
{
    return (c <= '9') && (c >= '0') ;
}
int isOpe(char c)
{
    return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '(') || (c == ')');
}
int postorder(Node* root)
{
    if(root -> flag) return root -> val.num ;
    else {
        switch(root -> val.ope)
        {
            case '+' : return postorder(root -> left) + postorder(root -> right) ;
            case '-' : return postorder(root -> left) - postorder(root -> right) ;
            case '*' : return postorder(root -> left) * postorder(root -> right) ;
            case '/' : return postorder(root -> left) / postorder(root -> right) ;
        }
    }

    return 0 ;
}
Node* buildTree()
{
    char c ;
    int num = 0 , flag = 0 ;
    while((c = getchar()) && c != '=')
    {
        if(!flag){
            if(isNum(c)) flag = 1 ;
            else{
                if(isOpe(c)){
                    switch(c)
                    {
                        case '(' : ope[opeTop++] = c ;
                                    break ;
                        case ')' : while(opeTop > 0 && ope[opeTop - 1] != '(')
                                    {
                                        sym val ;
                                        val.ope = ope[--opeTop] ;
                                        Node* node = initNode(val , 0) ;
                                        push(node) ;
                                    }
                                    opeTop-- ;
                                    break ;
                        case '+' :
                        case '-' : while(opeTop > 0 && ope[opeTop - 1] != '(')
                                    {
                                        sym val ;
                                        val.ope = ope[--opeTop] ;
                                        Node* node = initNode(val , 0) ;
                                        push(node) ;
                                    }
                                    ope[opeTop++] = c ;
                                    break ;
                        case '*' :
                        case '/' : while(opeTop > 0 && (ope[opeTop - 1] == '*' || ope[opeTop - 1] == '/') && ope[opeTop - 1] != '(')
                                    {
                                        sym val ;
                                        val.ope = ope[--opeTop] ;
                                        Node* node = initNode(val , 0) ;
                                        push(node) ;
                                    }
                                    ope[opeTop++] = c ;
                                    break ;
                    }
                    
                }
            }
        }
        if(flag){
            if(isNum(c)){
                num *= 10 ;
                num += c - '0' ;
            }
            else{
                sym val;
                val.num = num ;
                Node* node = initNode(val , 1) ;
                push(node) ;
                num = 0 ;
                flag = 0 ;
                if(isOpe(c)){
                    switch(c)
                    {
                        case '(' : ope[opeTop++] = c ;
                                    break ;
                        case ')' : while(opeTop > 0 && ope[opeTop - 1] != '(')
                                    {
                                        sym val ;
                                        val.ope = ope[--opeTop] ;
                                        Node* node = initNode(val , 0) ;
                                        push(node) ;
                                    }
                                    opeTop-- ;
                                    break ;
                        case '+' :
                        case '-' : while(opeTop > 0 && ope[opeTop - 1] != '(')
                                    {
                                        sym val ;
                                        val.ope = ope[--opeTop] ;
                                        Node* node = initNode(val , 0) ;
                                        push(node) ;
                                    }
                                    ope[opeTop++] = c ;
                                    break ;
                        case '*' :
                        case '/' : while(opeTop > 0 && (ope[opeTop - 1] == '*' || ope[opeTop - 1] == '/') && ope[opeTop - 1] != '(')
                                    {
                                        sym val ;
                                        val.ope = ope[--opeTop] ;
                                        Node* node = initNode(val , 0) ;
                                        push(node) ;
                                    }
                                    ope[opeTop++] = c ;
                                    break ;
                    }
                    
                }
            }
        }
    }

    if(num != 0 && flag){
        sym val;
        val.num = num ;
        Node* node = initNode(val , 1) ;
        push(node) ;
    }
    while(opeTop > 0)
    {
        sym val ;
        val.ope = ope[--opeTop] ;
        Node* node = initNode(val , 0) ;
        push(node) ;
    }

    return ans[0] ;
}
void push(Node* node)
{
    if(node -> flag) ans[top++] = node ;
    else{
        node -> right = ans[--top] ;
        node -> left = ans[--top] ;
        ans[top++] = node ;
    }
}
void printT(Node* root)
{
    inorder(root) ;
    printf("\n") ;
    preorder(root) ;
}
void inorder(Node* root)
{
    if(!root) return ;
    inorder(root -> left) ;
    Node* ptr = root ;
    if(ptr -> flag) printf("%d " , ptr -> val.num) ;
    else printf("%c " , ptr -> val.ope) ;   
    inorder(root -> right) ;
}
void preorder(Node* root)
{
    if(!root) return ;
    preorder(root -> left) ;
    preorder(root -> right) ;
    
    Node* ptr = root ;
    if(ptr -> flag) printf("%d " , ptr -> val.num) ;
    else printf("%c " , ptr -> val.ope) ;   
}