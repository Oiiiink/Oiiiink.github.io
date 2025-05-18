#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// 需要构建Node数组 
struct Node{
    int val ; // 对于非叶结点，记录其两个子结点权值之和
    struct Node *left , *right ;
};
typedef struct Node Node ;
Node* initNode(int val) ;
void bubblesort(Node*** numptr , int n) ;
void sink(Node*** numptr , int top) ;
Node* buildSubTree(Node* left , Node* right) ;
void printTree(Node* root) ;
Node* buildHuffmanTree(int* weight , int n) ;

int main(void)
{
    srand(time(NULL)) ;
    int n ; // n个权值
    int i = 0 ;
    n = rand() % 20 ;
    int* weight = (int*)malloc(sizeof(int) * n) ;
    for(i = 0 ; i < n ; ++i ) weight[i] = rand() % 1000 ;

    Node* root = buildHuffmanTree(weight , n) ;
    printTree(root) ;
    free(weight) ;

    return 0 ;
}

Node* initNode(int val)
{
    Node* node = (Node* )malloc(sizeof(Node)) ;
    node -> val = val ;
    node -> left = node -> right = NULL ;

    return node; 
}
void bubblesort(Node*** numptr , int n)
{
    Node** num = *numptr ;
    for(int i = n - 1 ; i > 0 ; --i)
        for(int j = 0 ; j < i ; ++j)
        {
            if(num[j] -> val < num[j + 1] -> val){
                Node* ptr = num[j] ;
                num[j] = num[j + 1] ;
                num[j + 1] = ptr ;
            }
        }
}
void sink(Node*** numptr , int top)
{
    Node** num = *numptr ;
    int i = top ;
    Node* sinkone = num[top] ;
    for(i = top - 1 ; i >= 0 ; i--)
    {
        if(num[i] -> val < sinkone -> val) num[i + 1] = num[i] ;
        else break ;
    }
    num[i + 1] = sinkone ;
}
Node* buildSubTree(Node* left , Node* right)
{
    Node* root = initNode(left -> val + right -> val) ;
    root -> left = left ;
    root -> right = right ;

    return root ;
}
void printTree(Node* root)
{
    if(!root) return ;
    if(!root -> left && !root -> right) printf("%d " , root -> val) ;

    else {
        printTree(root -> left) ;
        printTree(root -> right) ;
    }
}
Node* buildHuffmanTree(int* weight , int n)
{
    Node** node = (Node** )malloc(sizeof(Node*) * n) ;
    for(int i = 0 ; i < n ; i++) node[i] = initNode(weight[i]) ;
    bubblesort(&node , n) ;

    while(n > 1)
    {
        Node* node1 = initNode(node[n - 1] -> val + node[n - 2] -> val) ;
        node1 -> left = node[n - 2] ;
        node1 -> right = node[n - 1] ;
        n -= 2 ;
        node[n++] = node1 ;
        sink(&node , n - 1) ;
    }

    return node[0] ;
}