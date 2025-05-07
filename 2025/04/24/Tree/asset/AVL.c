#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define max(x , y) (((x) > (y)) ? (x) : (y))
// AVL树由于需要对祖先结点进行updateHeight操作，往往采用递归实现
struct Node{
    int val ;
    struct Node *left , *right ;
    int height ;
} ;
typedef struct Node Node ;
typedef Node AVLNode ;
Node* initNode(int val)
{
    Node* node = (Node*) malloc(sizeof(Node)) ;
    node -> height = 1 ;
    node -> val = val ;
    node -> left = node -> right = NULL ;

    return node ;
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
void updateHeight(Node* node)
{
    node -> height = 1 + max(getHeight(node -> right) , getHeight(node -> left)) ;
}
Node* leftRotate(Node* root)
{
    Node* newRoot = root -> right ;

    root -> right = newRoot -> left ;
    newRoot -> left = root ;

    // 该过程中，仅有root和newRoot的深度发生了改变
    updateHeight(root) ;
    updateHeight(newRoot) ;

    return newRoot ;
}
Node* rightRotate(Node* root)
{
    Node* newRoot = root -> left ; 

    root -> left = newRoot -> right ;
    newRoot -> right = root ;

    updateHeight(root) ; 
    updateHeight(newRoot) ;

    return newRoot ;
}
Node* adjust(Node* root)
{
    int fac = getBalanceFactor(root) ;
    if(fac > 1) {
        int subfac = getBalanceFactor(root -> left) ;
        // LL
        if(subfac >= 0) root = rightRotate(root) ;
        // LR
        else {
            root -> left = leftRotate(root -> left) ;
            root = rightRotate(root) ;
        } 
    }
    else if (fac < -1){
        int subfac = getBalanceFactor(root -> right) ;
        // RR
        if(subfac <= 0) root = leftRotate(root) ;
        // RL
        else {
            root -> right = rightRotate(root -> right) ;
            root = leftRotate(root) ;
        } 
    }

    return root ;
}
Node* insert(Node* root , int val)
{
    if(!root)
        return initNode(val) ;
    else if(val >= root -> val) root -> right = insert(root -> right , val) ;
    else root -> left = insert(root -> left , val) ;

    //操作
    updateHeight(root) ;
    root = adjust(root) ;

    return root ;
}
Node* deleteNode(Node* root , int val)
{
    if(!root) return NULL ;

    if(val > root -> val ) root -> right = deleteNode(root -> right , val) ;
    else if(val < root -> val) root -> left = deleteNode(root -> left , val) ;
    else{
        if(!(root -> left && root -> right)){
            Node* remove = root ;
            root =  (root -> left) ? root -> left : root -> right ;
            free(remove) ;
        }
        else {
            //将第二种情况转换为第一种情况
            Node* ptr = root -> right ;
            while(ptr -> left) ptr = ptr -> left ;

            root -> val = ptr -> val ;
            root -> right = deleteNode(root -> right , root -> val) ;
        }
    }

    if(!root) return root ;

    updateHeight(root) ;
    root = adjust(root) ;

    return root ;
}
void inorder(Node* root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}
void freeTree(Node* root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
int main(void)
{
    Node* root = NULL ;
    int num[20] ;
    srand(time(NULL)) ;
    for(int i = 0 ; i <= 20 ; ++i)
    {
        num[i] = rand() % 1000 ;
        root = insert(root , num[i]) ;
    }
    
    deleteNode(root , num[3]) ;
    
    freeTree(root) ;

    return  0 ;
}