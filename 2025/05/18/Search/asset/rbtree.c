#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define Color int
#define Black 0
#define Red 1
/*红黑树*/
/*特点：
    1. 每个结点，要么是黑色，要么是红色。
    2. 根结点和叶子结点（nil）一定是黑色
    3. 红色结点的孩子一定是黑结点。
    4. 从根结点到叶子结点的任意路径其黑色结点数相同（该性质决定了红黑树的最长路径和最短路径相差不会超过两倍）
*/

struct Node{
    int val ;
    Color color ;
    struct Node *left , *right , *parent ;
} ;
typedef struct Node Node ;
Node* nil ;
Node* initNil() ;
Node* initNode(int num) ;
Node* insert(Node* root , int val) ;
Node* insert_fixup(Node* root , Node* curr) ;
Node* search(Node* root , int key) ;
Node* RBdelete(Node* root , int key) ;
Node* delete_fixup(Node* root , Node* curr) ;
Node* Rrotate(Node* root ) ;
Node* Lrotate(Node* root) ;
void printTree(Node* root) ;
int main(void)
{
    nil = initNil() ;
    Node* root = nil ;

    int len ;
    scanf("%d" , &len) ;
    srand(time(NULL)) ;

    while(len--) root = insert(root , rand() % 100) ;
    printTree(root) ;

    return 0 ;
}

Node* initNil() 
{
    Node* nil = (Node* )malloc(sizeof(Node)) ;
    nil -> val = 0 ;
    nil -> color = Black ;
    nil -> left = nil -> right = nil -> parent = nil ;

    return nil ;
}
Node* initNode(int num) 
{
    Node* node = (Node*)malloc(sizeof(Node)) ;
    node -> val = num ; 
    node -> color = Red ;
    node -> parent = node -> left = node -> right = nil ;
    
    return node ;
}
/*插入操作：
    1. 首先，像bst一样正常插入。
    2. 判定是否破坏平衡（至多违反2，3）
    3. 四种情况，insert_fixup函数，传入参数root，pptr
*/
Node* insert(Node* root , int val) 
{
    Node* ptr = root ;
    Node* pptr = nil ;
    while(ptr != nil)
    {
        if(val >= ptr -> val){
            if(ptr -> right == nil){
                ptr -> right = initNode(val) ;
                pptr = ptr -> right ;
                pptr -> parent = ptr ;
                break ;
            }
            ptr = ptr -> right ;
        }
        else{
            if(ptr -> left == nil){
                ptr -> left = initNode(val) ;
                pptr = ptr -> left ;
                pptr -> parent = ptr ;
                break ;
            }
            ptr = ptr -> left ;
        }
    }
    if(ptr == nil) {root = initNode(val) ; pptr = root ;}

    return insert_fixup(root , pptr) ;
}
Node* insert_fixup(Node* root , Node* curr)
{
    /*四种情况*/

    // 1. curr就是根结点，则必然违反
    if(root == curr) {
        root -> color = Black ;
        return root ;
    }

    // 判断是否违反
    if(curr -> parent -> color == Black) return root ;

    //违反后有三种情况

    // 2. uncle is black
    while(1)
    {
        if(curr == root){
            curr -> color = Black ;
            break ;
        }
        else if(curr -> parent -> color == Black) break ;
        else{
            Node* grandpa = curr -> parent -> parent ;
            Node* parent = curr -> parent ;
            if(grandpa -> left == parent){
                Node* uncle = grandpa -> right ;
                if(uncle -> color == Red){// 需要回溯
                    uncle -> color = parent -> color = Black ;
                    grandpa -> color = Red ;
                    curr = grandpa ;
                }
                else {
                    if(curr == parent -> right){// LR
                        parent = Lrotate(parent) ;
                        grandpa -> left = parent ;
                    }
                    Node* old_grandpa = grandpa ;
                    grandpa = Rrotate(grandpa) ;
                    if(grandpa -> parent == nil) 
                        root = grandpa ;
                    else {
                        if(grandpa -> parent -> left == old_grandpa) grandpa -> parent -> left = grandpa ;
                        else grandpa -> parent -> right = grandpa ;
                    }
                    grandpa -> color = Black ;
                    grandpa -> right -> color = Red ;
                    break ;
                }
            }
            else{
                Node* uncle = grandpa -> left ;
                if(uncle -> color == Red){// 需要回溯
                    uncle -> color = parent -> color = Black ;
                    grandpa -> color = Red ;
                    curr = grandpa ;
                }
                else {
                    if(curr == parent -> left){// RL
                        parent = Rrotate(parent) ;
                        grandpa -> right = parent ;
                    }
                    Node* old_grandpa = grandpa ;
                    grandpa = Lrotate(grandpa) ;
                    if(grandpa -> parent == nil) 
                        root = grandpa ;
                    else {
                        if(grandpa -> parent -> left == old_grandpa) grandpa -> parent -> left = grandpa ;
                        else grandpa -> parent -> right = grandpa ;
                    }
                    grandpa -> color = Black ;
                    grandpa -> left -> color = Red ;
                    break ;
                }
            }
        }
    }

    return root ;
}
Node* search(Node* root , int key) 
{
    Node* ptr = root ; 
    while(ptr != nil)
    {
        if(key > ptr -> val) ptr = ptr -> right ;
        else if(key < ptr -> val) ptr = ptr -> left ;
        else return ptr ;
    }

    return nil ;    //表示没找到
}
Node* RBdelete(Node* root , int key) 
{
    Node* ptr = root ; 
    Node* curr = nil ;
    //找到ptr , curr:即真正需要删除的结点 和 补足的结点
    while(ptr != nil)
    {
        if(key > ptr -> val) ptr = ptr -> right ;
        else if(key < ptr -> val) ptr = ptr -> left ;
        else {
            if(ptr -> left != nil && ptr -> right != nil )
            {
                Node* pptr = ptr -> right ;
                while(pptr -> left != nil) pptr = pptr -> left ;

                ptr -> val = pptr -> val ;
                ptr = pptr ;
                curr = (ptr -> left != nil ) ? ptr -> left : ptr -> right ;
            }
            else curr = (ptr -> left != nil ) ? ptr -> left : ptr -> right ;
            break ;
        }
    }

    if(ptr -> color == Red ){//无需调整
        if(ptr -> parent == nil) return root = curr ;
        else{
            if(ptr == ptr -> parent -> right) ptr -> parent -> right = curr ;
            else ptr -> parent -> left = curr ;
        }
        free(ptr) ;
    }
    else{
        if(ptr -> parent == nil) return root = curr ;
        else{
            if(ptr == ptr -> parent -> right) ptr -> parent -> right = curr ;
            else ptr -> parent -> left = curr ;
        }
        free(ptr) ;
        // 删除结点为黑结点但补充节点是红节点，染黑即可
        if(curr -> color == Red) 
            curr -> color = Black ;
        else
            root = delete_fixup(root , curr) ;
    }

    return root ;
}
Node* delete_fixup(Node* root , Node* curr) 
{
    //curr代表双黑
    while(curr != root){
        Node* parent = curr -> parent ;
        if(curr == parent -> right){
            Node* bro = parent -> left ;
            //首先，判断是否可以通过兄弟结点补足黑色
            if(bro -> color == Red){
                // 变成兄弟是黑色的情况
                Node* old_parent = parent ;
                parent = Rrotate(parent) ;
                parent -> color = Black ;
                parent -> right -> color = Red ;
                if(parent -> parent == nil)
                    root = parent ;
                else if(parent -> parent -> left == old_parent) parent -> parent -> left = parent ;
                else parent -> parent -> right = parent ;
            }

            Node* son1 = bro -> left , *son2 = bro -> right ;
            if(son1 -> color == Black && son2 -> color == Black)
            {
                // 无法通过兄弟进行更改，那么将双黑上移
                bro -> color = Red ;
                curr = parent ;
                continue ;
            }
            else if(son1 -> color == Black && son2 -> color == Red)
            {
                //变为远端为红色的情况
                Node* old_bro = bro ;
                bro = Lrotate(bro) ;
                bro -> color = Black ;
                bro -> left -> color = Red ;
                parent -> left = bro ;
                son1 = bro -> left ;
            }

            bro -> color = parent -> color ;
            son1 -> color = Black ;
            parent -> color = Black ;
            Node* old_parent = parent ;
            parent = Lrotate(parent) ;
            if(parent -> parent == nil) root = parent ;
            else if (parent -> parent -> left == old_parent) parent -> parent -> left = parent ;
            else parent -> parent -> right = parent ;
            break ;
        }
        else{
            Node* bro = parent -> right ;
            //首先，判断是否可以通过兄弟结点补足黑色
            if(bro -> color == Red){
                // 变成兄弟是黑色的情况
                Node* old_parent = parent ;
                parent = Lrotate(parent) ;
                parent -> color = Black ;
                parent -> left -> color = Red ;
                if(parent -> parent == nil)
                    root = parent ;
                else if(parent -> parent -> left == old_parent) parent -> parent -> left = parent ;
                else parent -> parent -> right = parent ;
            }

            Node* son1 = bro -> right , *son2 = bro -> left ;
            if(son1 -> color == Black && son2 -> color == Black)
            {
                // 无法通过兄弟进行更改，那么将双黑上移
                bro -> color = Red ;
                curr = parent ;
                continue ;
            }
            else if(son1 -> color == Black && son2 -> color == Red)
            {
                //变为远端为红色的情况
                bro = Rrotate(bro) ;
                bro -> color = Black ;
                bro -> right -> color = Red ;
                parent -> right = bro ;
                son1 = bro -> right ;
            }

            bro -> color = parent -> color ;
            son1 -> color = Black ;
            parent -> color = Black ;
            Node* old_parent = parent ;
            parent = Rrotate(parent) ;
            if(parent -> parent == nil) root = parent ;
            else if (parent -> parent -> left == old_parent) parent -> parent -> left = parent ;
            else parent -> parent -> right = parent ;
            break ;
        }
    }

    root -> color = Black ;

    return root ;
}
Node* Rrotate(Node* root )
{
    Node* newroot = root -> left ;

    root -> left = newroot -> right ;
    newroot -> right = root ;
    newroot -> parent = root -> parent ;
    root -> parent = newroot ;
    if(root -> left != nil)root -> left -> parent = root ;

    return newroot ;
}
Node* Lrotate(Node* root) 
{
    Node* newroot = root -> right; 

    root -> right = newroot -> left ;
    newroot -> left = root ;
    newroot -> parent = root -> parent ;
    root -> parent = newroot ;
    if(root -> right != nil) root -> right -> parent = root ;

    return newroot ;
}
void printTree(Node* root) 
{
    Node* ptr = root ;
    Node* queue[1000] ;
    memset(queue , 0 , sizeof(Node*) * 1000) ;
    int top = 0 ;

    while(1)
    {
        while(ptr != nil){
            queue[top++] = ptr ;
            ptr = ptr -> left ;
        }

        if(top == 0) break ;
        ptr = queue[--top] ;
        printf("%d " , ptr -> val) ;
        ptr = ptr -> right ;
    }
}