#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max(x , y) (((x) > (y)) ? (x) : (y))
//哪里需要updateH：insert之后，rotate之后，delete之后

struct Node{
    char* name ;
    int times ;
    int height ;
    struct Node *right , *left ;
};
typedef struct Node Node ;
Node* initNode(char* str) ;
int searchNode(Node* root , char* str) ; //找到则直接times++，否则创建新结点
void printTree(Node* root) ;
void freeTree(Node* root) ;
int getHeight(Node* node) ;
int getBalanceFactor(Node* node) ;
Node* buildTree() ;
Node* leftRotate(Node* root) ;
Node* rightRotate(Node* root) ;
Node* adjust(Node* root) ;
void updateH(Node* root) ;
Node* insert(Node* root , char* str) ;//插入BST树中，根据字典序排序

int main()
{
    Node* root = buildTree() ;
    printTree(root) ;
    freeTree(root) ;

    return 0 ;
}

Node* initNode(char* str)
{
    Node* node = (Node*)malloc(sizeof(Node)) ;
    node -> height = 1 ;
    node -> times = 1 ;
    node -> right = node -> left = NULL ;
    int len = strlen(str) ;
    node -> name = (char*)malloc(sizeof(char) * (len + 1)) ;
    strcpy(node -> name , str) ;

    return node ;
}
int searchNode(Node* root , char* str)
{
    Node* ptr = root ;
    int ret = 0 ;
    while(ptr)
    {
        if(strcmp(str , ptr -> name) > 0) ptr = ptr -> right ;
        else if(strcmp(str , ptr -> name) < 0) ptr = ptr -> left ;
        else break ;
    }
    if(ptr) {
        ptr -> times ++ ;
        ret = 1 ;
    }

    return ret ;
}
void printTree(Node* root)
{
    if(!root) return ;
    printTree(root -> left) ;
    printf("%s %d\n" , root -> name , root -> times) ;
    printTree(root -> right) ;
}
void freeTree(Node* root)
{
    if(!root) return ;
    freeTree(root -> left) ;
    freeTree(root -> right) ;
    free(root) ;
}
int getHeight(Node* node)
{
    if(!node) return 0 ;
    return node -> height ;
}
int getBalanceFactor(Node* node)
{
    if(!node) return 0 ;

    return getHeight(node -> left) - getHeight(node -> right) ;
}
Node* buildTree()
{
    //先search
    Node* root = NULL ;
    FILE* fin = fopen("article.txt" , "r") ;

    char* str = (char*)malloc(sizeof(char) * 20) ;
    memset(str , 0 , sizeof(char) * 20) ;
    char c ; int i = 0 ;
    while((c = fgetc(fin)) != EOF)
    {
        if((c <= 'z' && c >= 'a')){
            str[i++] = c ;
        }
        else if(c <= 'Z' && c >= 'A'){
            str[i++] = c + 'a' - 'A' ;
        }
        else if(i > 0){
                //说明已有字符读入且当前结束该单词
                if(!searchNode(root , str)) root = insert(root , str) ;
                memset(str , 0 , sizeof(char) * 20) ;
                i = 0 ;
        }
    }
    if(i > 0 && !searchNode(root , str)) root = insert(root , str) ;

    return root ;
}
Node* leftRotate(Node* root)
{
    if(!root) return NULL ;
    Node* newroot = root -> right ;
    Node* root_right = root -> right -> left ;
    if(!newroot) return root ;

    root -> right = root_right ;
    newroot -> left = root ;

    updateH(root) ;
    updateH(newroot) ;

    return newroot ;
}
Node* rightRotate(Node* root)
{
    if(!root) return NULL ;
    Node* newroot = root -> left ;
    Node* root_left = root -> left -> right ;
    if(!newroot) return root ;

    root -> left = root_left ;
    newroot -> right = root ;

    updateH(root) ;
    updateH(newroot) ;

    return newroot ;
}
Node* adjust(Node* root)
{
    if(!root) return NULL ;

    int fac = getBalanceFactor(root) ;
    if(fac > 1)
    {
        int subfac = getBalanceFactor(root -> left) ;

        //LL
        if(subfac > 0){
            root = rightRotate(root) ;
        }
        //LR
        else {
            root -> left = leftRotate(root -> left) ;
            root = rightRotate(root) ;
        }
    }
    else if(fac < -1)
    {
        int subfac = getBalanceFactor(root -> right) ;

        //RR
        if(subfac < 0){
            root = leftRotate(root) ;
        }
        //RL
        else {
            root -> right = rightRotate(root -> right) ;
            root = leftRotate(root) ;
        }
    }

    return root ;
}
void updateH(Node* root)
{
    if(!root) return ;
    root -> height = 1 + max(getHeight(root -> left) , getHeight(root -> right)) ;
}
Node* insert(Node* root , char* str)
{
    if(!root) return initNode(str) ;

    if(strcmp(str , root -> name) > 0) root -> right = insert(root -> right , str) ;
    else root -> left = insert(root -> left , str) ;

    updateH(root) ;
    root = adjust(root) ;

    return root ;
}