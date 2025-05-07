#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//先构建二叉查找树，insert
//非递归实现查找（队列）
// int++ ??? OK
//!ptr 表示为NULL
struct Node{
    int val ;
    struct Node *left , *right ;
};
typedef struct Node Node ;
Node* initNode(int val) ;
Node* insert(Node* root , int item) ;   //非递归实现
int* findAncestors(Node* root , int item) ;
int num[1000] ;
int main(void)
{
    srand(time(NULL)) ;
    int i = 0; 
    Node* root = NULL ;
    while(1)
    {
        int number = rand() % 10000 ;
        if(i == 1000 || number == 627) break ;

        num[i++] = number ;
        root = insert(root , number) ;
    }

    int search = rand() % 1000 ;
    int* ans = findAncestors(root , num[search]) ;
    while(ans && *(ans) != num[search])
    {
        printf("%d " , *ans) ;
        ans++ ;
    }

    return 0 ;
}

Node* initNode(int val)
{
    Node* node = (Node*)malloc(sizeof(Node)) ;
    node -> val = val ;
    node -> left = node -> right = NULL ;

    return node ;
}
Node* insert(Node* root , int item)
{
    if(!root) return initNode(item) ;

    Node* ptr = root ;
    Node* parent = NULL ;

    while(ptr)
    {
        parent = ptr ;

        if(item >= ptr -> val) ptr = ptr -> right ;
        else ptr = ptr -> left ;
    }

    ptr = initNode(item) ;
    if(item >= parent -> val) parent -> right = ptr ;
    else parent -> left = ptr ;

    return root ;
}
int* findAncestors(Node* root , int item)
{
    // 找到item祖先序列存入队列中并返回队列
    //为了标识结束位，将item也存入队列中
    int *ans = (int* )malloc(sizeof(int) * 1000) ;  
    int top = 0 ;
    //memset(ans , 0 , sizeof(ans)) ;//这种写法仅仅初始化了第一个元素
    memset(ans , 0 , sizeof(int) * 1000) ;

    Node* ptr = root ; 
    while(ptr && ptr -> val != item)
    {
        ans[top++] = ptr -> val ;
        if(item > ptr -> val) ptr = ptr -> right ;
        else ptr = ptr -> left ;
    }

    if(ptr == NULL) return NULL ; // 查找失败
    ans[top++] = ptr -> val ;
    return ans ;
} 
/*对于一般二叉树的实现
void preorder(BTNodeptr t, Datatype item)
{
    if (t != NULL) {
        push(t);
        if (item == t->data) {
            printStack(); // 打印所有祖先（除 item 自身）
            return;       // 提前结束递归
        }
        preorder(t->left, item);
        preorder(t->right, item);
        pop();
    }
}
*/