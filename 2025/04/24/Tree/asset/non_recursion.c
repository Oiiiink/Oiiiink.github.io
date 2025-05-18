#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//核心：栈
struct Node{
    int val ;
    struct Node *left , *right ;
};
typedef struct Node Node ;
Node* initNode(int val) ;
Node* insert(Node* root , int val) ;
void traverse(Node* root) ;
int main(void)
{
    srand(time(NULL)) ;
    int n = 20 ;
    Node* root = NULL ;
    while(n--) root = insert(root , rand() % 1000) ;

    traverse(root) ;

    return 0 ;
}
Node* initNode(int val)
{
    Node* node = (Node* )malloc(sizeof(Node)) ;
    node -> val = val ;
    node -> left = node -> right = NULL ;

    return node ;
}
Node* insert(Node* root , int val)
{
    if(!root) return initNode(val) ;

    Node* ptr = root ;
    while(ptr -> left || ptr -> right)
    {
        if(ptr -> left == NULL) { ptr -> left = initNode(val) ; return root ;}
        else if(ptr -> right == NULL) {ptr -> right = initNode(val) ; return root ;}
        else {
            int dir = rand() % 2 ;
            ptr = (dir) ? ptr -> right : ptr -> left ;
        }
    }    
    int dir = rand() % 2 ;
    if(dir) ptr -> right = initNode(val) ;
    else ptr -> left = initNode(val) ;

    return root ;
}
void traverse(Node* root)
{
    //以中序遍历为例
    Node** stack = (Node**)malloc(sizeof(Node*) * 25) ;
    memset(stack , 0 , sizeof(Node*) * 25) ;
    int top = 0 ;
    Node* ptr = root ;

    while(ptr != NULL || top != 0)
    {
        if(ptr != NULL){
            stack[top++] = ptr ;
            ptr = ptr -> left ;
        }
        else{
            ptr = stack[--top] ;
            printf("%d " , ptr -> val) ;
            ptr = ptr -> right ;
        }
    }
    printf("\n") ;
    //前序遍历
    ptr = root ;
    while(ptr != NULL || top != 0)
    {
        if(ptr != NULL){
            printf("%d " , ptr -> val) ;
            stack[top++] = ptr -> right ;
            ptr = ptr -> left ;
        }
        else{
            ptr = stack[--top] ;
        }
    }
    printf("\n") ;
    //后序遍历
    ptr = root ;
    Node* last = NULL ;
    while(ptr != NULL || top != 0)
    {
        //先一步走到底
        while(ptr != NULL){
            stack[top++] = ptr ;
            ptr = ptr -> left ;
        }
        Node* peek = stack[top - 1] ;
        if(peek -> right && last != peek -> right) ptr = peek -> right ;
        else {
            printf("%d " , peek -> val) ;
            last = peek ;
            top-- ;
        } 
    }
}