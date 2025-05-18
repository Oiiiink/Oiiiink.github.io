/*利用多叉树来进行大规模的字符串查找，同时有利于字符串排序*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ALPHA_SIZE 26

struct Node{
    struct Node* children[ALPHA_SIZE] ;
    int times ;
} ;
typedef struct Node Node ;
Node* initNode() ;
void insert(Node* root , const char* str) ;
int search(Node* root , const char* str) ;
void printTree(Node* root , int h , char *str)  ;
int isChr(char c) ;
void freeTree(Node* root) ;
int main(void)
{
    FILE* fin = fopen("article.txt" , "r") ;
    Node* root = initNode() ;
    char* s = (char*)malloc(sizeof(char) * 30) ;
    memset(s , 0 , sizeof(char) * 30) ;
    int i = 0 ;

    char c ;
    int flag = 0 ;
    while((c = fgetc(fin)) && c != EOF)
    {
        if(isChr(c)){
            if(!flag) flag = 1 ;
            if(c >= 'A' && c <= 'Z') c = c + 'a' - 'A' ;
            s[i++] = c ;
        }
        else{
            if(flag){
                flag = 0 ;
                i = 0 ;
                insert(root , s) ;
                memset(s , 0 , sizeof(char) * 30) ;
            }
        }
    }
    if(flag && i != 0) insert(root , s) ;
    memset(s , 0 , sizeof(char) * 30) ;
    printTree(root , 0 , s) ;
    free(s) ;
    freeTree(root) ;
    fclose(fin) ;

    return 0 ;
}

Node* initNode() 
{
    Node* node = (Node* )malloc(sizeof(Node)) ;
    node -> times = 0 ;
    for(int i = 0 ; i < ALPHA_SIZE ; ++i)
        node -> children[i] = NULL ;

    return node ;
}
void insert(Node* root , const char* str) 
{
    Node* ptr = root ;
    int i = 0 ;
    for(; str[i] != '\0' ; ++i)
    {
        int index = str[i] - 'a' ;
        if(!ptr -> children[index]) ptr -> children[index] = initNode() ;

        ptr = ptr -> children[index] ;
    }
    ptr -> times ++ ;
}
int search(Node* root , const char* str) 
{
    Node* ptr = root ;

    for(int i = 0 ; str[i] != '\0' ; ++i)
    {
        int index = str[i] - 'a' ;
        if(!ptr -> children[index]) return 0 ;

        ptr = ptr -> children[index] ;
    }

    return 1 ; 
}
void printTree(Node* root , int h , char *str) 
{
    if(!root) return ;
    if(root -> times) printf("%s , %d\n" , str , root -> times) ;
    for(int i = 0 ; i < ALPHA_SIZE ; ++i)
    {
        if(root -> children[i] == NULL) continue ;

        str[h] = i + 'a' ;
        printTree(root -> children[i] , h + 1 , str) ;
        str[h] = 0 ;
    }
}
int isChr(char c) 
{
    return (c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') ;
}
void freeTree(Node* root) 
{
    for(int i = 0 ; i < ALPHA_SIZE ; ++i)
        if(root -> children[i]) freeTree(root -> children[i]) ;

    free(root) ;
}