#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10000

int head , tail ;
int num[MAXSIZE] ;
int isFull()
{
    return tail == MAXSIZE - 1 ;
}
void initList()
{
    tail = head = 0 ;
}
int insert(int* List , int pos)
{
    if(isFull() || pos >= MAXSIZE){
        printf("insert error !\n") ;
        return -1 ;
    }

    tail ++ ;
    for(int i = tail ; i >= pos ; i++) num[i] = num[i - 1] ; 
    scanf("%d" , &num[pos - 1]) ;
}
int tailInsert()
{
    if(isFull()) {
        printf("insert error !\n") ;
        return -1 ;
    }
    scanf("%d" , &num[tail++]) ;

    return 0 ;
}

int main(void)
{
    while(1)
    {
        int ret = tailInsert() ;

        if(!ret) break ; 
    }

    return 0 ;
}