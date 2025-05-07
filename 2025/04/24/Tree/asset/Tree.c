#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 检查二叉树是否为空             ok
 在二叉树中查找给定元素
 获得二叉树中包含给定元素路径    ok
 在二叉树中插入一个元素
 从二叉树中删除一个元素
 获得二叉树的高度               ok
 获得二叉树的节点数目            ok
 获得二叉树叶节点的数目          ok
 遍历二叉树                     ok
 拷贝二叉树                     ok
 删除二叉树                     ok

*/

struct Node{
    int val ;
    struct Node *left , *right ;
};
typedef struct Node Node ;
Node* initNode()
{
    Node* node = (Node* )malloc(sizeof(Node)) ;

    node -> val = 0;
    node -> left = node -> right = NULL ;

    return node ;
}
Node* copyTree(Node* src)
{
    //递归思想
    Node* obj ;

    if(!src) obj = NULL ;
    else {
        obj = initNode() ;
        obj -> val = src -> val ;
        obj -> left = copyTree(src -> left) ;
        obj -> right = copyTree(src -> right) ;
    }

    return obj ;
}
int isEmpty(Node* tree)
{
    return tree == NULL ;
}
void deleteTree(Node** root)
{
    if(!*root) return ;

    deleteTree(&(*root) -> left) ;
    deleteTree(&(*root) -> right) ;
    free((*root)) ;

    //root = NULL ;   //这里将root改为NULL没有意义，因为是局部变量
    *root = NULL ;
}
int getHeight(Node* tree)
{
    if(!tree) return 0 ;

    int hl , hr ;
    hl = getHeight(tree -> left) + 1 ;
    hr = getHeight(tree -> right) + 1 ;

    return (hl > hr ) ? hl : hr ;
}
int getNodeNum(Node* root)
{
    if(!root) return 0 ; 

    return 1 + (getNodeNum(root -> left) > getNodeNum(root -> right)) ? getNodeNum(root -> left) : getNodeNum(root -> right) ;

}
int getLeaf(Node* root)
{
    if(!root) return 0 ;
    else if(!root -> left && !root -> right) return 1 ;
    else return getLeaf(root -> left ) + getLeaf(root -> right) ;
}
int nodePath(Node* root , Node* target)
{
    //使用ret来表示该路径是否能找到
    //该方法仅能逆向输出路径，如果有正向输出的需求可另外设计，思路包括数组储存，使用栈等
    if(!root) return 0 ;
    else if(root == target) {
        printf("%p\n" , target) ;
        return 1 ;
    }

    int ret = nodePath(root -> left , target) ;
    if(ret) {printf(" <- %p" , root) ; return 1 ;}
    ret = nodePath(root -> right , target) ;
    if(ret) {printf(" <- %p" , root) ; return 1 ;}
}

int main(void)
{


    return 0 ;
}