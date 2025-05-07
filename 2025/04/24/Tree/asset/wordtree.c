/*
编写程序统计一个英文文本文件中每个单词的出现次数（词频统计），并将统计结果按单词字典序输出到屏幕上。
要求：程序应用二叉排序树（BST）来存储和统计读入的单词。
注：在此单词为仅由字母组成的字符序列。包含大写字母的单词应将大写字母转换为小写字母后统计。在生成二叉排序树不做平衡处理。
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Node{
    char* name ;
    int times ;
    struct Node *right , *left ;
};
typedef struct Node Node ;
Node* initNode(char* str) ;
Node* insert(Node* root , char* str) ;//插入BST树中，根据字典序排序
Node* findword() ;  //返回根结点
int searchNode(Node* root , char* str) ; //找到则直接times++，否则创建新结点
void printTree(Node* root) ;
void freeTree(Node* root) ;

int main(void)
{
    Node* root = findword() ;
    if(root){
        printf("%s" , root -> name) ;
        if(root -> right){
            printf(" %s" , root -> right -> name) ;
            if(root -> right -> right){
                printf(" %s" , root -> right -> right -> name) ;
            }
        }
    }
    printf("\n") ;

    printTree(root) ;
    freeTree(root) ;

    return 0 ;
}

Node* initNode(char* str)
{
    Node* node = (Node*)malloc(sizeof(Node)) ;
    node -> times = 1 ;
    node -> right = node -> left = NULL ;
    int len = strlen(str) ;
    node -> name = (char*)malloc(sizeof(char) * (len + 1)) ;
    strcpy(node -> name , str) ;

    return node ;
}
Node* insert(Node* root , char* str)
{
    int flag = searchNode(root , str) ;
    if(flag) return root ;

    Node* parent = NULL ;
    Node* ptr = root ;

    while(ptr)
    {
        parent = ptr ;
        if(strcmp(str , ptr -> name) > 0) ptr = ptr -> right ;
        else ptr = ptr -> left ;
    }
    ptr = initNode(str) ;
    if(!parent) root = ptr ; 
    else if(strcmp(str , parent -> name) > 0) parent -> right = ptr ;
    else parent -> left = ptr ;

    return root ;
}
Node* findword()
{
    Node* root = NULL ;
    FILE* fin = fopen("article.txt" , "r") ;

    char* line = (char* )malloc(sizeof(char) * 1000) ;
    while(fgets(line , 1000 , fin) != NULL)
    {
        char* ptr = line ;
        int i = 0 ;
        int flag = 0 ;  //1 标识正在读入
        char* s = (char* )malloc(sizeof(char) * 20) ;
        memset(s , 0 , sizeof(char) * 20) ;
        while(*ptr != '\0')
        {
            char c = *ptr; 
            if(!flag){
                if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ) flag = 1 ;
            }
            if(flag){
                if(c >= 'a' && c <= 'z') s[i++] = c ;
                else if(c >= 'A' && c <= 'Z') s[i++] = c + 'a' - 'A' ;
                else {
                    flag = 0 ;
                    root = insert(root , s) ;
                    i = 0 ;
                    memset(s , 0 , sizeof(char) * 20) ;
                }
            }
            ptr++ ;
        }
        free(s) ;
    }
    free(line) ;

    return root ;
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