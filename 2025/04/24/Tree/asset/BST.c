// BinarySearchTree : L < D < R
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define MAXSIZE 100

struct Node{
    int val ;
    struct Node *left , *right ;
};
typedef struct Node Node ;
Node* initNode(int val)
{
    Node* node = (Node* )malloc(sizeof(Node)) ;
    node -> val = val ;
    node -> left = node -> right = NULL ;

    return node ;
}
void inorder(Node* root)
{
    if(!root) return ;

    inorder(root -> left) ;
    printf("%d " , root -> val) ;
    inorder(root -> right) ;
}
void insertBST(Node** root , int num)
{
    if(!*root) {*root = initNode(num) ; return ;}

    if(num < (*root) -> val) insertBST(&(*root) -> left , num) ;
    else insertBST(&(*root) -> right , num) ;
}
Node* deleteBST(Node* root , int num)
{
    // 实际上，当删除次数不多时，常采用“懒惰删除” ，即只需标记被删除元素

    Node* ptr = root ;
    Node* parent = NULL ;
    while(1)
    {
        //未查询到
        if(!ptr) return root;

        if(ptr -> val == num) break ;
        parent = ptr ;

        if(ptr -> val > num) ptr = ptr -> left ;
        else ptr = ptr -> right ;
    }

    // ptr 至多有一个子结点
    if(!(ptr -> left && ptr -> right))
    {
        Node* replace = (ptr -> left) ? ptr -> left : ptr -> right ;

        // 更新双亲结点
        if(!parent){
            // 删除的是根结点
            free(root) ;
            return replace ;
        }
        else if(parent -> left == ptr) parent -> left = replace ;
        else parent -> right = replace ;

        free(ptr) ;
    }

    // ptr 有两个子结点 ， 找到右子树的最小值
    else{
        Node* successor = ptr -> right ;
        Node* successorP = ptr ;

        while(successor -> left) {
            successorP = successor ;
            successor = successor -> left ;
        }

        // ptr的右子树无左子树
        if(successorP == ptr){
            ptr -> right = successor -> right ;
            ptr -> val = successor -> val ;
        }
        else{
            ptr -> val = successor -> val ;
            successorP -> left = successor -> right ;
        }

        free(successor) ;
    }

    return root ;
}
Node* searchBST(Node* root , int target)
{
    Node* ptr = root ;
    while(!ptr){
        if(ptr -> val == target) break ;

        if(target > ptr -> val) ptr = ptr -> right ;
        else ptr = ptr -> left ;
    }
    return ptr ;
}
int main(void)
{
    int num ;
    Node* root = NULL ;
    int size = 0 ;
    srand(time(NULL)) ;
    while( size != 10 && (num = rand() % 1000) )
    {
        insertBST(&root , num) ;
        size++ ;
    }

    inorder(root) ;
    printf("\n") ;
    deleteBST(root , num) ;
    inorder(root) ;
    return 0 ;
}