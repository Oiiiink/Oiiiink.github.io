#include <stdio.h>
#include <stdlib.h>

struct Node{
    int val ; 
    struct Node* next ;
} ;
typedef struct Node Node ;
typedef struct Node* Nodeptr ;
typedef int ElemType ;

ElemType getVal()
{
    ElemType val ; 
    scanf("%d" , &val) ;

    return val ;
}
Nodeptr createList(int n) // 创建一个具有n个结点的链表，这里没有写返回值
{
    Nodeptr head , ptr;
    head = (Nodeptr)malloc(sizeof(Node)) ;
    head -> val = 0 ;
    head -> next = NULL ;

    for(int i = 0 ; i < n ; ++i )
    {
        Nodeptr node = (Nodeptr)malloc(sizeof(Node)) ;
        node -> next = NULL ;
        node -> val = getVal() ;    //getVal() , 一个用于读入值的函数

        if(head == NULL){
            head -> next = node ;
            ptr = node ;
        }
        else{
            ptr -> next = node ;
            ptr = ptr -> next ;
        }

        head -> val ++ ;
    }

    return head ;
} 
int getLength(Nodeptr list) // 获得链表的长度 
{
    return list -> val ;
}
void headInsert(Nodeptr list , ElemType elem)
{
    Nodeptr node = (Nodeptr)malloc(sizeof(Node)) ;
    node -> val = elem ;
    node -> next = NULL ;

    node -> next = list -> next ;
    list -> next = node ;
}
void tailInsert(Nodeptr list , ElemType elem)
{
    Nodeptr node = (Nodeptr)malloc(sizeof(Node)) ;
    node -> val = elem ;
    node -> next = NULL ;

    //尾插法采用遍历方式，时间复杂度为O(n)
    Nodeptr ptr = list ;
    while(ptr -> next != NULL) ptr = ptr -> next ;
    ptr -> next = node ;

    list -> val ++ ;
}
void insertNode(Nodeptr list, Nodeptr* p, ElemType elem)
{
    Nodeptr node = (Nodeptr)malloc(sizeof(Node)) ;
    node -> val = elem ;
    node -> next = NULL ;

    //尾插法采用遍历方式，时间复杂度为O(n)
    Nodeptr ptr = list;
    //找到特定结点，若未找到则插入尾端
    while(ptr -> next != NULL && ptr != p) ptr = ptr -> next ;
    node -> next = ptr -> next ;
    ptr -> next = node ;

    list -> val ++ ;
}
void printList(Nodeptr list) // 打印输出一个链表的data域 
{
    Nodeptr ptr = list;
    while(ptr -> next != NULL)
    {
        printf("%d -> " , ptr -> next -> val); 
        ptr = ptr -> next ;
    }
    ptr = ptr -> next ;
    printf("%d\n" , ptr -> val ) ;
}
int searchNode(Nodeptr list, ElemType elem) // 在链表中查找某一数据元素
{
    Nodeptr ptr = list -> next ;
    int k = 1 ;
    while(ptr != NULL && ptr -> val != elem) {
        ptr = ptr -> next ;
        k++ ;
    }

    if(ptr == NULL){
        printf("No target\n") ;
        return -1 ;
    }
    else return k ;
} 
void deleteNode(Nodeptr list, ElemType elem) // 在链表中删除包含某一数据元素的结点 
{
    Nodeptr ptr = list;
    while(ptr -> next != NULL && ptr -> next -> val != elem) ptr = ptr -> next ;

    if(ptr -> next == NULL) printf("Err : delete failure \n") ;
    else{
        Nodeptr remove = ptr -> next ;
        ptr -> next = remove -> next ;

        free(remove) ;
    }
}


int main()
{


    return 0 ;
}